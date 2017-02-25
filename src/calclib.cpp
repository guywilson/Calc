#include <string>

#include "calc.h"
#include "calclib.h"

using namespace std;

namespace calc {
    string * calculate(const string & expression)
    {
        string * r;

        r = Calculator::evaluate(expression);

        return r;
    }
}
