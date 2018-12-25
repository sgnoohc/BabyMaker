#!/bin/bash

##############################################################################################
#
# For pretty printing
#
##############################################################################################
#
# Set Colors
#

bold=$(tput bold)
underline=$(tput sgr 0 1)
reset=$(tput sgr0)

purple=$(tput setaf 7)
red=$(tput setaf 1)
green=$(tput setaf 2)
tan=$(tput setaf 3)
blue=$(tput setaf 4)
bluebkg=$(tput setab 4)

#
# Headers and  Logging
#

e_header() { printf "\n${bold}${purple}==========  %s  ==========${reset}\n" "$@"
}
e_arrow() { printf "➜ $@\n"
}
e_success() { printf "${green}✔ %s${reset}\n" "$@"
}
e_error() { printf "${red}✖ %s${reset}\n" "$@"
}
e_warning() { printf "${tan}➜ %s${reset}\n" "$@"
}
e_msg() { printf "${purple}➜ %s${reset}\n" "$@"
}
e_underline() { printf "${underline}${bold}%s${reset}\n" "$@"
}
e_bold() { printf "${bold}%s${reset}\n" "$@"
}
e_note() { printf "${underline}${bold}${blue}Note:${reset}  ${blue}%s${reset}\n" "$@"
}


##############################################################################################
#
# <3 of the code goes here
#
##############################################################################################

# Print header
e_header "Baby Maker Test Jobs"

help() {
    echo "Usage:"
    echo ""
    echo ""
    echo "    $ $0 NEVENTS TESTJOBCONFIGPATH"
    echo ""
    echo "NEVENTS               (e.g. =10000)          Number of events to process per test jobs."
    echo "TESTJOBCONFIGPATH     (e.g. =testjobs.txt)   The path to where the testjobs are defined."
    echo ""
    echo ""
    exit
}

# Create a directory to put all the test run log files
mkdir -p testjobs

# Get total entries if an argument is provided other wise set it to 10000
if [ -z $1 ]; then
    help
    #NEVENTS=10000
else
    NEVENTS=$1
    shift
fi

# if an alternative list of testjobs are to be run
if [ -z $1 ]; then
    help
    #TESTJOBCONFIGPATH="testjobs.txt"
else
    TESTJOBCONFIGPATH=$1
    shift
fi

echo ""
e_note "For each test job we will test n_evts=$NEVENTS"

# Create an array that will hold each sub process ids (i.e. an array called JOBS)
INDEX=1
declare -a JOBS
declare -a INPUTS
declare -a SHORTNAMES
run_test_job()
{
    ./processBaby "$1" $NEVENTS ${INDEX}  > testjobs/${2}.log 2>&1 &
    e_msg     "    ./processBaby "$1" $NEVENTS ${INDEX}  > testjobs/${2}.log 2>&1 &"
    JOBS[${INDEX}]=$!;
    INPUTS[${INDEX}]="$1";
#    BABYMODE[${INDEX}]="$2";
    SHORTNAMES[${INDEX}]="$2";
    e_warning "    Test job #"$INDEX" pid="${JOBS[${INDEX}]}" submitted "$1
    INDEX=$((INDEX + 1))
}

report_test_jobs()
{
    INDEX=1
    for job in "${JOBS[@]}"; do
        wait $job
        JOBSTATUS=$?
        if [ $JOBSTATUS -eq 0 ]; then
            e_success "    Test job #"$INDEX" pid="$job" success "${INPUTS[${INDEX}]}
            mv output_${INDEX}.root testjobs/output_${SHORTNAMES[${INDEX}]}.root
        else
            e_error "    Test job #"$INDEX" pid="$job" failure "${INPUTS[${INDEX}]}
            e_msg   "    log: "testjobs/${SHORTNAMES[${INDEX}]}.log
        fi
        INDEX=$((INDEX + 1))
    done
}

echo ""
e_note ">>> Issuing 'make' command for double check..."
echo "$ make"
make 2>&1 | tee .make.log

if [ ${PIPESTATUS[0]} -ne 0 ]; then
    e_error "Make failed! Please check your code."
    e_error "Following might give you a hint ..."
    e_warning "===================================="
    sed -n -e '/error:/,/warning:/ p' .make.log | head -n -1
    #grep -m1 -A5 "error: " .make.log
    e_warning "===================================="
    exit
fi

echo ""
e_note ">>> Retreiving last git commit hash"
echo "$ git log | head -n 1"
git log | head -n 1

echo ""
e_note ">>> Printing out current git status"
echo "$ git status"
git status

echo ""
grep -v -e ^# -e ^$ ${TESTJOBCONFIGPATH} > .testjobs.txt
e_note ">>> Submitting parallel test jobs..."
while read p; do
    run_test_job $p
done < .testjobs.txt

echo ""
e_note ">>> Waiting for test jobs to finish..."
report_test_jobs
