#ifndef _INCL_SYSTEM
#define _INCL_SYSTEM

#define BASE_HEX            16
#define BASE_DEC            10
#define BASE_OCT             8
#define BASE_BIN             2

#define FLOAT_PRECISION     80

class System
{
    public:
        static void    setPrecision(int p);
        static int     getPrecision();
};

#endif