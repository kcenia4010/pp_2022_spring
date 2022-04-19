// Copyright 2022 Kutuev Roman
#ifndef MODULES_TASK_3_KUTUEV_R_JARVIS_JARIVS_H_
#define MODULES_TASK_3_KUTUEV_R_JARVIS_JARIVS_H_
#include <omp.h>

#include <algorithm>
#include <cmath>
#include <cstdlib>
#include <stack>
#include <vector>
#include <tbb/tbb.h>
#define collinear 0
#define left -1
#define right 1

struct Point {
    int x;
    int y;
    void set_point(int _x, int _y) {
        x = _x;
        y = _y;
    }
};

class jarvis {
public:
    std::vector<Point> set_points(int size);

    int find_lowest_left_most_point_index(const std::vector<Point>& points);

    std::vector<Point> convex_hull(const std::vector<Point>& points);

    std::vector<Point> convex_hull_tbb(const std::vector<Point>& points);
};


#endif  // MODULES_TASK_3_KUTUEV_R_JARVIS_JARIVS_H_
