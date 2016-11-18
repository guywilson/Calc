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
TARGET=calc.exe

# C compiler
CPP=cl

# Linker
LINKER=link

# C compiler flags (Debug)
#CFLAGS=-c -W3 -Ot -Zi -favor:INTEL64 -nologo -fp:precise 

# Linker flags (Debug)
#LFLAGS=/MACHINE:X64 /DEBUG:FULL /NOLOGO /OUT:$(TARGET)

# C compiler flags (Release)
CPPFLAGS_DBG=-c -W3 -Ot -Zi -Gs -EHsc -nologo -favor:INTEL64 -fp:precise 
CPPFLAGS_REL=-c -W3 -Ot -Gs -EHsc -nologo -favor:INTEL64 -fp:precise 
CPPFLAGS=$(CPPFLAGS_REL)

# Linker flags (Release)
LFLAGS_DBG=/MACHINE:X64 /NOLOGO /DEBUG /ASSEMBLYDEBUG /OUT:$(TARGET)
LFLAGS_REL=/MACHINE:X64 /NOLOGO /OUT:$(TARGET)
LFLAGS=$(LFLAGS_REL)

# Object files (in linker ',' seperated format)
OBJFILES=$(BUILD)\main.obj $(BUILD)\token.obj $(BUILD)\calc.obj $(BUILD)\stack.obj $(BUILD)\exception.obj $(BUILD)\test.obj

# Target
all: $(TARGET)

# Compile C source files
#
$(BUILD)\main.obj: $(SOURCE)\main.cpp $(SOURCE)\calc.h $(SOURCE)\token.h $(SOURCE)\types.h $(SOURCE)\exception.h
	$(CPP) $(CPPFLAGS) -Fd$(BUILD)\main.pdb -Fo$(BUILD)\main.obj $(SOURCE)\main.cpp

$(BUILD)\token.obj: $(SOURCE)\token.cpp $(SOURCE)\token.h $(SOURCE)\types.h $(SOURCE)\exception.h
	$(CPP) $(CPPFLAGS) -Fd$(BUILD)\token.pdb -Fo$(BUILD)\token.obj $(SOURCE)\token.cpp

$(BUILD)\calc.obj: $(SOURCE)\calc.cpp $(SOURCE)\calc.h $(SOURCE)\token.h $(SOURCE)\stack.h $(SOURCE)\types.h $(SOURCE)\exception.h
	$(CPP) $(CPPFLAGS) -Fd$(BUILD)\calc.pdb -Fo$(BUILD)\calc.obj $(SOURCE)\calc.cpp

$(BUILD)\stack.obj: $(SOURCE)\stack.cpp $(SOURCE)\stack.h $(SOURCE)\token.h $(SOURCE)\types.h $(SOURCE)\exception.h
	$(CPP) $(CPPFLAGS) -Fd$(BUILD)\stack.pdb -Fo$(BUILD)\stack.obj $(SOURCE)\stack.cpp

$(BUILD)\exception.obj: $(SOURCE)\exception.cpp $(SOURCE)\exception.h $(SOURCE)\types.h
	$(CPP) $(CPPFLAGS) -Fd$(BUILD)\exception.pdb -Fo$(BUILD)\exception.obj $(SOURCE)\exception.cpp

$(BUILD)\test.obj: $(SOURCE)\test.cpp $(SOURCE)\test.h $(SOURCE)\token.h $(SOURCE)\types.h
	$(CPP) $(CPPFLAGS) -Fd$(BUILD)\test.pdb -Fo$(BUILD)\test.obj $(SOURCE)\test.cpp

$(TARGET): $(OBJFILES)
	$(LINKER) $(LFLAGS) $(OBJFILES)
