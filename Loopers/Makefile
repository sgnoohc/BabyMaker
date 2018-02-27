#include Makefile.arch

# Extra Packages
PACKAGES = rooutil
TARGET = wwwana
SRCS = wwwana.C Functions.C
OBJS = $(SRCS:.C=.o)
OBJS100 = $(SRCS:.C=_100.o)
ROOTLIBS:= $(shell root-config --libs) -lTMVA -lEG -lGenVector -lXMLIO -lMLP -lTreePlayer -lRooFit -lRooFitCore

wwwana: $(PACKAGES) $(OBJS) CMS3_WWW0118.o
	g++ -o $(TARGET) $(OBJS) CMS3_WWW0118.o $(ROOTLIBS) $(addprefix -L,$(PACKAGES)) $(addprefix -l,$(PACKAGES))

wwwana100: $(PACKAGES) $(OBJS100) CMS3_WWW100.o
	g++ -o $(TARGET)100 $(OBJS100)  CMS3_WWW100.o $(ROOTLIBS) $(addprefix -L,$(PACKAGES)) $(addprefix -l,$(PACKAGES)) -DUSE_CMS3_WWW100

all: wwwana wwwana100

%.o : %.cc
	g++ -Wunused-variable -g -O2 -Wall -fPIC -Wshadow -Woverloaded-virtual $(shell root-config --cflags) -c $< -o $@

%.o : %.C
	g++ -Wunused-variable -g -O2 -Wall -fPIC -Wshadow -Woverloaded-virtual $(shell root-config --cflags) -c $< -o $@

%_100.o : %.C
	g++ -Wunused-variable -g -O2 -Wall -fPIC -Wshadow -Woverloaded-virtual $(shell root-config --cflags) -c $< -o $@ -DUSE_CMS3_WWW100

$(PACKAGES):
	make -j 15 -C $@
	ln -sf $(notdir $(shell ls $@/*$@.so | grep -v lib)) $@/lib$@.so
rename:
	g++  -Wunused-variable -g -O2 -Wall -fPIC -Wshadow -Woverloaded-virtual $(shell root-config --cflags) RenameMapping.C -o $@

.PHONY: $(PACKAGES)

clean:
	rm -f *.o
	rm -f wwwana
	rm -f wwwana100
