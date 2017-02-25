# Calc
A command line scientific calculator written in C++. The calculator converts the entered calculation into Reverse Polish Notation (RPN) using the 'Shunting Yard' algorithm before evaluating the result.

Building Calc
-------------
Calc now has a dependency on CLN (Class Library for Numbers) http://www.ginac.de/CLN to allow arbitary precision decimal numbers. To compile CLN on Windows, use gcc on cygwin. I have provided makefiles for Windows (must be compiled using gcc under cygwin, tested on Windows 10 and requires the Cygwin DLLs to be present on the PATH), Unix (compiled using gcc and tested on Ubuntu 16.04 64-bit) and Mac OSX (compiled using gcc and tested on Mac OSX Sierra).

Using Calc
----------
The calcuator supports the standard trigometric functions sin(), cos(), tan(), asin(), acos(), atan() and also sqrt(), log(), ln() and fact() - factorial. The following numerical operators are supported: +, -, *, /, % and ^ (power), plus the following logical operators: &, | and ~ (XOR).

The calculator has a self-test mode, just type 'test' once you've entered the calculator in interactive mode. For help, just type 'help' in interactive mode. Debugging output can also be switched on and off with the 'dbgon' and 'dbgoff' commands.

Enjoy!
