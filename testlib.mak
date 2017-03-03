###############################################################################
#                                                                             #
# MAKEFILE for Calculator application                                         #
#                                                                             #
# © Guy Wilson 2013                                                           #
#                                                                             #
# Build using Visual Studio 2015 - Community Edition                          #
# Use 'nmake' to build with this makefile, 'nmake -a' to rebuild all          #
#                                                                             #
###############################################################################

# Source directory
SOURCE=src

# Build output directory
BUILD=build

# What is our target
TARGET=testlib

# C compiler
CPP=g++

# Linker
LINKER=g++

# C compiler flags (Release)
CPPFLAGS=-c -fpermissive -Wall -std=c++11 

# Target
all: $(TARGET)

# Compile C source files
#
$(BUILD)/testlib.o: $(SOURCE)/testlib.cpp $(SOURCE)/calclib.h
	$(CPP) $(CPPFLAGS) -o $(BUILD)/testlib.o $(SOURCE)/testlib.cpp

$(TARGET): $(BUILD)/testlib.o
	$(LINKER) -L/usr/lib/x86_64-linux-gnu -o $(TARGET) $(BUILD)/testlib.o -lcalc -lcln -lstdc++
