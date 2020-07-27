#ifndef HITABLELISTH
#define HITABLELISTH

#include "hitable.h"

class hitable_list: public hitable {
    public:
        hitable_list() {}
        // **lはlistのポインタのポインタ、つまり要素のポインタを意味する
        // hitableクラスのオブジェクトをリストで引数で入れるよという意味
        hitable_list(hitable **l, int n) {list = l; list_size=n; }
        virtual bool hit(const ray& r, double t_min, double t_max, hit_record& rec) const;
        hitable **list;
        int list_size;
};

bool hitable_list::hit(const ray& r, double t_min, double t_max, hit_record& rec) const {
    hit_record temp_rec;
    bool hit_anything = false;
    double closest_so_far = t_max;
    // 何らかの球にhitすればtrueに変更
    for (int i = 0; i < list_size; i++) {
        // list[i]の要素はhitableクラスなのでhit関数がその要素の球に対して発火する
        // sphere.hのhit関数が呼ばれる
        if (list[i]->hit(r, t_min, closest_so_far, temp_rec)) {
            hit_anything = true;
            closest_so_far = temp_rec.t;
            rec = temp_rec;
        }
    }
    return hit_anything;
}

#endif