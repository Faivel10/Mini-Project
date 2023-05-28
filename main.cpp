#include <iostream>
#include <string>
#include <vector>
#include <unordered_set>
#include <algorithm>

#include "main.h"

// this function may have duplicates, fix
std::vector<std::pair<int, int>> CalculateRandoms(const int count)
{
    std::vector<int> xs;
    std::vector<int> ys;
    std::vector<std::pair<int, int>> res;

    for (int i = 0; i < count; i++)
    {
        xs.push_back(i);
        ys.push_back(i);
    }

    std::random_shuffle(xs.begin(), xs.end());
    std::random_shuffle(ys.begin(), ys.end());

    for (int i = 0; i < count; ++i)
    {
        res.push_back(std::pair(xs[i], ys[i]));
    }

    return res;
}

std::vector<Point> ConnectDots(std::vector<std::pair<int, int>> &points)
{
    std::vector<Point> res;
    // sort the pairs according to the x value
    std::sort(points.begin(), points.end(), [](auto &left, auto &right)
              { return left.first <= right.first; });

    for (auto &point : points)
    {
        int max_val = 1;
        // find all the points that are smaller
        std::vector<Point> smaller;
        for (auto &ready_point : res)
        {
            if (ready_point.x < point.first && ready_point.y < point.second)
            {
                std::cout << "test" <<  ready_point.x << "," << ready_point.y << "\n";
                std::cout << "test1 " <<  point.first << "," << point.second << "\n";
                smaller.push_back(ready_point);
                max_val = std::max(max_val, ready_point.longest_length);
            }
        }
        Point p = {point.first, point.second, smaller, max_val + 1};
        res.push_back(p);
    }

    return res;
}

int main()
{
    std::vector<std::pair<int, int>> input = CalculateRandoms(5);
    // for (auto &item : test)
    // {
    //     std::cout << item.first << "," << item.second << "\n";
    // }

    // step 1 - connect the dots
    std::vector<Point> connected_points = ConnectDots(input);

    for (auto &item : connected_points)
    {
        std::cout << "item is:" << item.x << "," << item.y << "\n";
        std::cout << "smaller items: [";
        for (auto &small : item.smaller)
        {
            std::cout << "(" << item.x << "," << item.y << ") ";
        }
        std::cout << " ]\n";
    }
}