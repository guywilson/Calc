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

TOOLS=\Users\guy\devtools

# What is our target
TARGET=calc.exe

# C compiler
CPP=g++

# Linker
LINKER=g++

# C compiler flags (Release)
CPPFLAGS=-c -O3 -fpermissive -std=c++11 -O2 -I$(TOOLS)\include

# Object files (in linker ',' seperated format)
LIBFILES=$(BUILD)/calclib.o $(BUILD)/token.o $(BUILD)/calc.o $(BUILD)/stack.o $(BUILD)/exception.o $(BUILD)/debug.o $(BUILD)/test.o
OBJFILES=$(LIBFILES) $(BUILD)/main.o

# Target
all: $(TARGET)

# Compile C source files
#
$(BUILD)/calclib.o: $(SOURCE)/calclib.cpp $(SOURCE)/calclib.h $(SOURCE)/calc.h
	$(CPP) $(CPPFLAGS) -o $(BUILD)/calclib.o $(SOURCE)/calclib.cpp

$(BUILD)/main.o: $(SOURCE)/main.cpp $(SOURCE)/calc.h $(SOURCE)/token.h $(SOURCE)/types.h $(SOURCE)/exception.h $(SOURCE)/debug.h
	$(CPP) $(CPPFLAGS) -o $(BUILD)/main.o $(SOURCE)/main.cpp

$(BUILD)/token.o: $(SOURCE)/token.cpp $(SOURCE)/token.h $(SOURCE)/types.h $(SOURCE)/exception.h $(SOURCE)/debug.h
	$(CPP) $(CPPFLAGS) -o $(BUILD)/token.o $(SOURCE)/token.cpp

$(BUILD)/calc.o: $(SOURCE)/calc.cpp $(SOURCE)/calc.h $(SOURCE)/token.h $(SOURCE)/stack.h $(SOURCE)/types.h $(SOURCE)/exception.h $(SOURCE)/debug.h
	$(CPP) $(CPPFLAGS) -o $(BUILD)/calc.o $(SOURCE)/calc.cpp

$(BUILD)/stack.o: $(SOURCE)/stack.cpp $(SOURCE)/stack.h $(SOURCE)/token.h $(SOURCE)/types.h $(SOURCE)/exception.h
	$(CPP) $(CPPFLAGS) -o $(BUILD)/stack.o $(SOURCE)/stack.cpp

$(BUILD)/exception.o: $(SOURCE)/exception.cpp $(SOURCE)/exception.h $(SOURCE)/types.h
	$(CPP) $(CPPFLAGS) -o $(BUILD)/exception.o $(SOURCE)/exception.cpp

$(BUILD)/debug.o: $(SOURCE)/debug.cpp $(SOURCE)/debug.h
	$(CPP) $(CPPFLAGS) -o $(BUILD)/debug.o $(SOURCE)/debug.cpp

$(BUILD)/test.o: $(SOURCE)/test.cpp $(SOURCE)/test.h $(SOURCE)/token.h $(SOURCE)/types.h
	$(CPP) $(CPPFLAGS) -o $(BUILD)/test.o $(SOURCE)/test.cpp

$(TARGET): $(OBJFILES)
	$(LINKER) -O2 -o $(TARGET) -L$(TOOLS)\lib -lstdc++ $(OBJFILES) -lcln 
	ar rcs libcalc.a $(LIBFILES) $(TOOLS)\lib\libcln.a
