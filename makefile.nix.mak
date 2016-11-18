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
TARGET=calc

# C compiler
CPP=g++

# Linker
LINKER=g++

# C compiler flags (Release)
CPPFLAGS=-c -fpermissive -Wall -std=c++11 

# Object files (in linker ',' seperated format)
OBJFILES=$(BUILD)/main.o $(BUILD)/token.o $(BUILD)/calc.o $(BUILD)/stack.o $(BUILD)/exception.o $(BUILD)/test.o

# Target
all: $(TARGET)

# Compile C source files
#
$(BUILD)/main.o: $(SOURCE)/main.cpp $(SOURCE)/calc.h $(SOURCE)/token.h $(SOURCE)/types.h $(SOURCE)/exception.h
	$(CPP) $(CPPFLAGS) -o $(BUILD)/main.o $(SOURCE)/main.cpp

$(BUILD)/token.o: $(SOURCE)/token.cpp $(SOURCE)/token.h $(SOURCE)/types.h $(SOURCE)/exception.h
	$(CPP) $(CPPFLAGS) -o $(BUILD)/token.o $(SOURCE)/token.cpp

$(BUILD)/calc.o: $(SOURCE)/calc.cpp $(SOURCE)/calc.h $(SOURCE)/token.h $(SOURCE)/stack.h $(SOURCE)/types.h $(SOURCE)/exception.h
	$(CPP) $(CPPFLAGS) -o $(BUILD)/calc.o $(SOURCE)/calc.cpp

$(BUILD)/stack.o: $(SOURCE)/stack.cpp $(SOURCE)/stack.h $(SOURCE)/token.h $(SOURCE)/types.h $(SOURCE)/exception.h
	$(CPP) $(CPPFLAGS) -o $(BUILD)/stack.o $(SOURCE)/stack.cpp

$(BUILD)/exception.o: $(SOURCE)/exception.cpp $(SOURCE)/exception.h $(SOURCE)/types.h
	$(CPP) $(CPPFLAGS) -o $(BUILD)/exception.o $(SOURCE)/exception.cpp

$(BUILD)/test.o: $(SOURCE)/test.cpp $(SOURCE)/test.h $(SOURCE)/token.h $(SOURCE)/types.h
	$(CPP) $(CPPFLAGS) -o $(BUILD)/test.o $(SOURCE)/test.cpp

$(TARGET): $(OBJFILES)
	$(LINKER) -L/usr/local/lib -L/usr/lib/x86_64-linux-gnu -lstdc++ -o $(TARGET) $(OBJFILES) -lbsd
