#!/bin/bash

# Run the loop.py to loop over with 5 different systematics settings (nominal, lepsf_up, lepsf_dn, jec_up, jec_dn)
for i in $(seq 0 4); do python loop.py $i; done

# For each variation create yield table output in cutflows/
python maketable.py output.root nominal
python maketable.py output_lepsf_up.root lepsf_up
python maketable.py output_lepsf_dn.root lepsf_dn
python maketable.py output_jec_up.root jec_up
python maketable.py output_jec_dn.root jec_dn

# each cutflow table in cutflows contain the alpha factor between N_lostlep,SR / N_lostlep,CR

# run plotter
python makeplot.py
