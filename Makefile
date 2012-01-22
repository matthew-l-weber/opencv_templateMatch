################################################################################
# © Copyright 2012, Rockwell Collins, Inc.  All rights reserved.
#
# Information contained herein is privileged or confidential information
# of Rockwell Collins, Inc. within the meaning of 5 USC 552, and as such
# is exempt from the public disclosure provisions thereof.
#
# Security classification: UNCLASSIFIED
#
################################################################################

CC = $(TARGET_BIN)gcc
CFLAGS ?= -O2 -W -Wall
LDFLAGS ?=

CFLAGS += --sysroot=$(SYSROOT)

LIBS= -lopencv_core -lopencv_highgui

all: opencv_templatematch

imageCapture.o : template_match.c
	$(CC) $(CFLAGS) -c -o $@ $<

imageCapture: template_match.o
	$(CC) $(LDFLAGS) -o $@ $^ $(LIBS)

clean:
	-rm -f *.o
	-rm -f opencv_templatematch

#########################################################################
#
# Security classification:  UNCLASSIFIED
#
#########################################################################
