#include <algorithm>
#include <iostream>
#include <vector>
#include <ctime>
#include <fstream>

using namespace std;

struct pt {
    double x, y;
};

bool cmp (pt a, pt b) {             //  для сортировки по Х
    return a.x < b.x || a.x == b.x && a.y < b.y;
}

bool cw (pt a, pt b, pt c) {       //  для проверки, что точка В выше прямой АС
    return a.x*(b.y-c.y)+b.x*(c.y-a.y)+c.x*(a.y-b.y) < 0;
}

bool ccw (pt a, pt b, pt c) {      //  для проверки, что точка В ниже прямой АС
    return a.x*(b.y-c.y)+b.x*(c.y-a.y)+c.x*(a.y-b.y) > 0;
}

void convex_hull (vector<pt> & a) {
    if (a.size() == 1)  return;
    sort (a.begin(), a.end(), &cmp);   // сортировка по Х
    pt p1 = a[0],  p2 = a.back();      // создается две точки, p1 - левая нижняя, p2 - правая верхняя
    vector<pt> up, down;               // создается два множества,up - точки выше линии p1p2, down - ниже p1p2
    up.push_back (p1);
    down.push_back (p1);
    for (size_t i=1; i<a.size(); ++i) {
        if (i==a.size()-1 || cw (p1, a[i], p2)) {    // прохождение по точкам, которые выше p1p2
            while (up.size()>=2 && !cw (up[up.size()-2], up[up.size()-1], a[i]))
                up.pop_back();
            up.push_back (a[i]);
        }
        if (i==a.size()-1 || ccw (p1, a[i], p2)) {    // прохождение по точкам, которые ниже p1p2
            while (down.size()>=2 && !ccw (down[down.size()-2], down[down.size()-1], a[i]))
                down.pop_back();
            down.push_back (a[i]);
        }
    }
    a.clear();
    for (size_t i=0; i<up.size(); ++i)
        a.push_back (up[i]);
    for (size_t i=down.size()-2; i>0; --i)
        a.push_back (down[i]);
}

int main() {
    for (int i = 0; i < 60; i++) {
        int n;
        int k;

        ifstream fin("C://Users/raush/Desktop/HW_2/aisd/aicdTest/test" + to_string(i + 1) + ".txt");

        fin >> n;


        cout << "******************************" << endl;
        cout << "test #" << i+1 << endl;
        cout << "n: " << n << endl;

        std::vector<pt> a;

        double x,y;

        for (int j = 1; j <= n; ++j) {
            fin >> x;
            fin >> y;
            pt l = {x,y};
            a.insert(a.begin(),l);
        }

        std::clock_t start;
        double duration;

        start = clock();

        convex_hull(a);

        duration = ( clock() - start ) / (double) CLOCKS_PER_SEC;
        cout << "time: " << duration << "s" << endl;

        for (const auto& pt : a) {
            std::cout << pt.x << " " << pt.y << std::endl;
        }

    }

}