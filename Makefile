################################################################################
# © Copyright 2012, Rockwell Collins, Inc.  All rights reserved.
################################################################################

CC = $(TARGET_BIN)gcc
CFLAGS ?= -O2 -W -Wall
LDFLAGS ?=

CFLAGS += --sysroot=$(SYSROOT) -I$(SYSROOT)/../../../../staging/usr/include/

LIBS= -lopencv_core -lopencv_highgui

all: opencv_templatematch

template_match.o : template_match.c
	$(CC) $(CFLAGS) -c -o $@ $<

opencv_templatematch: template_match.o
	$(CC) $(LDFLAGS) -o $@ $^ $(LIBS)

clean:
	-rm -f *.o
	-rm -f opencv_templatematch

#########################################################################
#
#########################################################################
