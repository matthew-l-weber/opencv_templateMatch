################################################################################
# © Copyright 2012, Rockwell Collins, Inc.  All rights reserved.
#
# This file is free software; you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation; either version 2 of the License, or
# (at your option) any later version.
# 
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
# 
# You should have received a copy of the GNU General Public License
# along with this program; see the file COPYING.  If not see
# <http://www.gnu.org/licenses/>.
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
