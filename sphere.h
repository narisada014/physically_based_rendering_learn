#ifndef SPHEREH
#define SPHEREH

#include "hitable.h"

// centerは球の中心の意味
class sphere: public hitable {
    public:
        sphere() {}
        sphere(vec3 cen, double r) : center(cen), radius(r) {};
        virtual bool hit(const ray& r, double t_min, double t_max, hit_record& rec) const;
        vec3 center;
        double radius;
};

// 球の計算の一般化
// tは線形補間が可能な範囲0~1の間
// hitbale_listのhit関数の中の要素のhitで呼ばれる
bool sphere::hit(const ray& r, double t_min, double t_max, hit_record& rec) const {
    vec3 oc = r.origin()-center;
    double a = dot(r.direction(), r.direction());
    double b = dot(oc, r.direction());
    double c = dot(oc, oc) - radius*radius;
    double discriminant = b*b - a*c;
    // 解を持たなければhit箇所は存在しない
    if (discriminant > 0) {
        double temp = (-b - sqrt(discriminant)) / a;
        if (temp < t_max && temp > t_min) {
            rec.t = temp;
            rec.p = r.point_at_parameter(rec.t);
            rec.normal = (rec.p - center) / radius;
            return true;
        }
        temp = (-b + sqrt(discriminant)) / a;
        if (temp < t_max && temp > t_min) {
            rec.t = temp;
            rec.p = r.point_at_parameter(rec.t);
            rec.normal = (rec.p - center) / radius;
            return true;
        }
    }
    return false;
}

#endif