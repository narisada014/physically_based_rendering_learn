#include <math.h>
#include <stdlib.h>
#include <iostream>

class vec3 {
    public:
        vec3() : e{0,0,0} {}
        vec3(double e0, double e1, double e2) : e{e0, e1, e2} {}

        inline double x() const { return e[0]; }
        inline double y() const { return e[1]; }
        inline double z() const { return e[2]; }

        inline const vec3& operator+() const { return *this; }
    public:
        double e[3];
};