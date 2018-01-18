#include Makefile.arch

# Extra Packages
PACKAGES = rooutil
TARGET = wwwana
SRCS = wwwana.C Functions.C
OBJS = $(SRCS:.C=.o) CMS3_WWW0117.o
ROOTLIBS:= $(shell root-config --libs) -lTMVA -lEG -lGenVector -lXMLIO -lMLP -lTreePlayer -lRooFit -lRooFitCore

all: $(PACKAGES) $(OBJS)
	g++ -o $(TARGET) $(OBJS) $(ROOTLIBS) $(addprefix -L,$(PACKAGES)) $(addprefix -l,$(PACKAGES))

CMS3_WWW0116.o : CMS3_WWW0116.cc
	g++ -Wunused-variable -g -O2 -Wall -fPIC -Wshadow -Woverloaded-virtual $(shell root-config --cflags) -c $< -o $@

CMS3_WWW0117.o : CMS3_WWW0117.cc
	g++ -Wunused-variable -g -O2 -Wall -fPIC -Wshadow -Woverloaded-virtual $(shell root-config --cflags) -c $< -o $@

%.o : %.C
	g++ -Wunused-variable -g -O2 -Wall -fPIC -Wshadow -Woverloaded-virtual $(shell root-config --cflags) -c $< -o $@

$(PACKAGES):
	make -j 15 -C $@
	ln -sf $(notdir $(shell ls $@/*$@.so | grep -v lib)) $@/lib$@.so
rename:
	g++  -Wunused-variable -g -O2 -Wall -fPIC -Wshadow -Woverloaded-virtual $(shell root-config --cflags) RenameMapping.C -o $@

.PHONY: $(PACKAGES)

clean:
	rm *.o
