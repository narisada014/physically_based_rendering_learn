#ifndef HITABLEH
#define HITABLEH
#include "ray.h"

struct hit_record {
    double t;
    vec3 p;
    vec3 normal;
};

// virtual関数はポインタを渡された時しか上書き機能が機能しないのでhit_recordは参照が渡されている。
class hitable {
    public:
        virtual bool hit(const ray& r, double t_min, double t_max, hit_record& rec) const = 0;
};

#endif