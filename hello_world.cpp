#include <iostream>
#include "sphere.h"
#include "hitable_list.h"
#include "float.h"

// -------------------------------------------
// -------------------------------------------
// チャプタ5の抽象化前
// double hit_sphere(const vec3& center, double radius, const ray& r) {
//     vec3 oc = r.origin() - center;
//     double a = dot(r.direction(), r.direction());
//     double b = 2.0*dot(oc, r.direction());
//     double c = dot(oc, oc) - radius*radius;
//     double discrimination = b*b - 4*a*c;
//     if (discrimination < 0) {
//         return -1.0;
//     } else {
//         // 直線と球面が交わる交点の、原点に近い方の実数解
//         return (-b - sqrt(discrimination)) / (2.0*a);
//     }
// }
// -------------------------------------------
// -------------------------------------------

vec3 color(const ray& r, hitable_list *world) {
    hit_record rec;
    // worldはhit_record構造体を含むhitableクラス
    // virtual関数を上書きできるのはポインタが渡された時なのでここでもworldはmain関数でポインタとして渡されている。
    // recは一般化のためにhit_record構造体ということがわかるように定義
    // hitable_listの各要素のhitがtrueならば法線ベクトルを加味した球の色付けを返す
    // そうでなければ背景のグラデーション（線形補間）を変えす
    // hitable_listは*worldで、hitable_list::hit内でさらにsphere::hitが呼び出される
    if (world->hit(r,0.0,MAXFLOAT,rec)) {
        return 0.5*vec3(rec.normal.x()+1, rec.normal.y()+1, rec.normal.z()+1);
    } else {
        vec3 unit_direction = unit_vector(r.direction());
        double t = 0.5*(unit_direction.y() + 1.0);
        return (1.0-t)*vec3(1.0, 1.0, 1.0) + t*vec3(0.5, 0.7, 1.0);
    }
    // -------------------------------------------
    // -------------------------------------------
    // チャプタ5の抽象化前
    // // 中心を指定して、入力のrayがベクトル成分Bとなるように計算し、Trueならその部分を赤くするためのベクトル(1,0,0)=(255,0,0)を返す
    // double t = hit_sphere(vec3(0,0,-1),0.5,r);
    // if (t > 0.0) {
    //     // Nは、光線の球と接する近い方のベクトルから球の中心ベクトルを引いたものの単位ベクトル（球面の単位法線ベクトル）
    //     vec3 N = unit_vector(r.point_at_parameter(t) - vec3(0,0,-1));
    //     // 色の差が出やすいように1を足してスケーリングして2で割っている
    //     return 0.5*vec3(N.x()+1, N.y()+1, N.z()+1);
    // }
    // // 原点からのスクリーン向きのベクトルの単位ベクトル
    // vec3 unit_direction = unit_vector(r.direction());
    // // 単位ベクトルのy軸方向+1に0.5をかけたものが係数t
    // t = 0.5*(unit_direction.y() + 1.0);
    // // t=1.0の時は青にする。tが0の時は白になるように
    // // 線形補間（lerp）：線形のグラデーションを実現する関数
    // // blended_value = (1-t)*start_value + t*end_value
    // return (1.0-t)*vec3(1.0, 1.0, 1.0) + t*vec3(0.5, 0.7, 1.0);
    // -------------------------------------------
    // -------------------------------------------
}

int main() {
    int nx = 200;
    int ny = 100;
    std::cout << "P3\n" << nx << " " << ny << "\n255\n";
    vec3 lower_left_corner(-2.0, -1.0, -1.0);
    vec3 horizontal(4.0, 0.0, 0.0);
    vec3 vertical(0.0, 2.0, 0.0);
    vec3 origin(0.0,0.0,0.0);
    hitable *list[2];
    // listに球を格納し、hitable_listに代入
    list[0] = new sphere(vec3(0,0,-1), 0.5);
    list[1] = new sphere(vec3(0,-100.5,-1), 100);
    hitable_list *world = new hitable_list(list, 2);
    for (int j = ny-1; j >= 0; j--) {
        for (int i = 0; i < nx; i++) {
            double u = double(i) / double(nx);
            double v = double(j) / double(ny);
            // 左下の角から水平方向と垂直方向に光を走査してやる
            ray r(origin, lower_left_corner + u*horizontal + v*vertical);
            vec3 col = color(r, world);
            int ir = int(255.99*col[0]);
            int ig = int(255.99*col[1]);
            int ib = int(255.99*col[2]);
            std::cout << ir << " " << ig << " " << ib << "\n";
        }
    }
}