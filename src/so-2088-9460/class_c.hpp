#ifndef CLASS_C_HPP_INCLUDED
#define CLASS_C_HPP_INCLUDED

#include "class_a.hpp"
#include <cstdio>

class C
{
public:
    C();
private:
    class A *ap;
    FILE *fp;
};

#endif /* CLASS_C_HPP_INCLUDED */
