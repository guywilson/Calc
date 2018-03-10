###############################################################################
#                                                                             #
# MAKEFILE for Calculator application                                         #
#                                                                             #
# � Guy Wilson 2013                                                           #
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
CPPFLAGS=-c -fpermissive -fPIC -Wall -std=c++11

# Object files (in linker ',' seperated format)
LIBFILES=$(BUILD)/calclib.o $(BUILD)/system.o $(BUILD)/token.o $(BUILD)/calc.o $(BUILD)/stack.o $(BUILD)/exception.o $(BUILD)/debug.o $(BUILD)/test.o
OBJFILES=$(LIBFILES) $(BUILD)/main.o

# Target
all: $(TARGET)

# Compile C source files
#
$(BUILD)/calclib.o: $(SOURCE)/calclib.cpp $(SOURCE)/calclib.h $(SOURCE)/calc.h
	$(CPP) $(CPPFLAGS) -o $(BUILD)/calclib.o $(SOURCE)/calclib.cpp

$(BUILD)/system.o: $(SOURCE)/system.cpp $(SOURCE)/system.h
	$(CPP) $(CPPFLAGS) -o $(BUILD)/system.o $(SOURCE)/system.cpp

$(BUILD)/main.o: $(SOURCE)/main.cpp $(SOURCE)/calc.h $(SOURCE)/system.h $(SOURCE)/token.h $(SOURCE)/types.h $(SOURCE)/exception.h $(SOURCE)/debug.h
	$(CPP) $(CPPFLAGS) -o $(BUILD)/main.o $(SOURCE)/main.cpp

$(BUILD)/token.o: $(SOURCE)/token.cpp $(SOURCE)/system.h $(SOURCE)/token.h $(SOURCE)/types.h $(SOURCE)/exception.h $(SOURCE)/debug.h
	$(CPP) $(CPPFLAGS) -o $(BUILD)/token.o $(SOURCE)/token.cpp

$(BUILD)/calc.o: $(SOURCE)/calc.cpp $(SOURCE)/calc.h $(SOURCE)/token.h $(SOURCE)/stack.h $(SOURCE)/types.h $(SOURCE)/exception.h $(SOURCE)/debug.h
	$(CPP) $(CPPFLAGS) -o $(BUILD)/calc.o $(SOURCE)/calc.cpp

$(BUILD)/stack.o: $(SOURCE)/stack.cpp $(SOURCE)/stack.h $(SOURCE)/token.h $(SOURCE)/types.h $(SOURCE)/exception.h
	$(CPP) $(CPPFLAGS) -o $(BUILD)/stack.o $(SOURCE)/stack.cpp

$(BUILD)/exception.o: $(SOURCE)/exception.cpp $(SOURCE)/exception.h $(SOURCE)/types.h
	$(CPP) $(CPPFLAGS) -o $(BUILD)/exception.o $(SOURCE)/exception.cpp

$(BUILD)/debug.o: $(SOURCE)/debug.cpp $(SOURCE)/debug.h
	$(CPP) $(CPPFLAGS) -o $(BUILD)/debug.o $(SOURCE)/debug.cpp

$(BUILD)/test.o: $(SOURCE)/test.cpp $(SOURCE)/test.h $(SOURCE)/system.h $(SOURCE)/token.h $(SOURCE)/types.h
	$(CPP) $(CPPFLAGS) -o $(BUILD)/test.o $(SOURCE)/test.cpp

$(TARGET): $(OBJFILES)
	$(LINKER) -L/usr/local/lib -lstdc++ -lcln -o $(TARGET) $(OBJFILES)
	$(LINKER) -dynamiclib -fPIC -o libcalc.so $(LIBFILES) -lcln
