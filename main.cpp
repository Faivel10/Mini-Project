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

    srand(time(0));
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
    // map each pair -> to 2 vector -> 1 vector of pairs smaller values and 1 vector of pairs bigger values.
    //  sort the pairs according to the x value
    //  O(nlogn)
    std::sort(points.begin(), points.end(), [](auto &left, auto &right)
              { return left.first <= right.first; });

    // O(n^2)
    for (auto &point : points)
    {
        auto it_point = std::find(points.begin(), points.end(), point);
        int max_val_small = 0;
        std::vector<Point> bigger;
        std::vector<Point> smaller;
        int max_val_big = 0;
        // first find smallest and length until point itself.
        for (auto p_res : res)
        {
            if (p_res.x < point.first && p_res.y < point.second)
            {
                // std::cout << "our point" <<  point.first << "," << point.second << " - ";
                // std::cout << "smaller point: " <<  ready_point.x << "," << ready_point.y << "\n";

                // insert the pair as it is smaller then the point.
                smaller.push_back(p_res);
                max_val_small = std::max(max_val_small, p_res.longest_smaller_length);
            }
        }
        // the bigger values will be created later.
        Point p = {point.first, point.second, smaller, bigger, max_val_small + 1, max_val_big + 1};
        res.push_back(p);
    }

    // now after creating all the points, we will sort the points in decreasing order and add the bigger ones
    std::sort(res.begin(), res.end(), [](Point &left, Point &right)
              { return left.x >= right.x; });

    // we go from biggest to smallest x values now
    for (auto it = res.begin(); it != res.end(); it++)
    {
        int max_val_big = 0;
        for (auto prev_it = res.begin(); prev_it != it; prev_it++)
        {
            if (prev_it->x > it->x && prev_it->y > it->y)
            {
                it->bigger.push_back((*prev_it));
                it->longest_bigger_length = std::max(it->longest_bigger_length, prev_it->longest_bigger_length + 1);
            }
        }
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
    // O(n^2)
    std::vector<Point> connected_points = ConnectDots(input);

    //for clean output
    std::sort(connected_points.begin(), connected_points.end(), [](auto &left, auto &right)
              { return left.x < right.x; });

    for (auto &item : connected_points)
    {
        std::cout << "item is:" << item.x << "," << item.y << "\n";
        std::cout << "smaller items: [";
        for (auto &small : item.smaller)
        {
            std::cout << "(" << small.x << "," << small.y << ") ";
        }
        std::cout << " ]\n";
        std::cout << "biggest smaller length: " << item.longest_smaller_length << "\n";
        std::cout << "bigger items: [";
        for (auto &bigger : item.bigger)
        {
            std::cout << "(" << bigger.x << "," << bigger.y << ") ";
        }
        std::cout << "]\n";
        std::cout << "biggest bigger length: " << item.longest_bigger_length << "\n";
    }
}