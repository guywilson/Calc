# Calc
A command line scientific calculator written in C++. The calculator converts the entered calculation into Reverse Polish Notation (RPN) using the 'Shunting Yard' algorithm before evaluating the result.

Building Calc
-------------
I have provided makefiles for both Windows (compiled using MS Visual Studio C++ 2015 Community Edition and tested on Windows 10) and Unix (compiled using gcc and tested on Ubuntu 16.04 64-bit).

Using Calc
----------
The calcuator supports the standard trigometric functions sin(), cos(), tan(), asin(), acos(), atan() and also sqrt(), log(), log10() and fact() - factorial. The following operators are supported: +, -, *, / and ^ (power).

The calculator has a self-test mode, just type 'test' once you've entered the calculator in interactive mode. For help, just type 'help' in interactive mode. Debugging output can also be switched on and off with the 'dbgon' and 'dbgoff' commands.

Enjoy!
