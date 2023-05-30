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

std::vector<std::shared_ptr<Point>> ConnectDots(std::vector<std::pair<int, int>> &points)
{
    std::vector<std::shared_ptr<Point>> res;
    // map each pair -> to 2 vector -> 1 vector of pairs smaller values and 1 vector of pairs bigger values.
    //  sort the pairs according to the x value
    //  O(nlogn)
    std::sort(points.begin(), points.end(), [](auto &left, auto &right)
              { return left.first <= right.first; });

    // O(n^2)
    for (auto &point : points)
    {
        std::vector<std::shared_ptr<Point>> bigger;
        std::vector<std::shared_ptr<Point>> smaller;
        std::shared_ptr<Point> curr_point = std::make_shared<Point>(Point(point.first, point.second));
        curr_point->max_finish_length  = 1;
        curr_point->max_start_length = 1;
        // go over prev points and add them if are lower in y also. (was sorted by x so no need for x check)
        for (auto &p_res : res)
        {
            if (p_res->y < curr_point->y)
            {
                // std::cout << "our point" <<  point.first << "," << point.second << " - ";
                // std::cout << "smaller point: " <<  ready_point.x << "," << ready_point.y << "\n";

                // insert the pair as it is smaller then the point.
                curr_point->smaller.push_back(p_res);
                if (p_res->max_finish_length + 1 > curr_point->max_finish_length)
                {
                    curr_point->longest_finish_point = p_res;
                    curr_point->max_finish_length = p_res->max_finish_length + 1;
                }
            }
        }
        // the bigger values will be created later.
        res.push_back(curr_point);
    }

    // now after creating all the points, we will go in decreesing order

    // we go from biggest to smallest x values now

    for (auto it = res.rbegin(); it != res.rend(); it++)
    {
        std::shared_ptr<Point> curr = (*it);

        for (auto prev_it = res.rbegin(); prev_it != it; prev_it++)
        {
            std::shared_ptr<Point> prev = (*prev_it);
            if (prev->y > curr->y)
            {
                curr->bigger.push_back(*prev_it);
                if (curr->max_start_length < prev->max_start_length + 1)
                {
                    curr->longest_start_point = prev;
                    curr->max_start_length = prev->max_start_length + 1;
                }
            }
        }
    }

    return res;
}

int LargestPathLength(std::vector<Point> &points)
{
    int max = 1;
    for (Point &p : points)
    {
        //    max = std::max(max, p.longest_bigger_length);
    }

    return max;
}

void PrintAll(std::vector<std::shared_ptr<Point>> &connected_points)
{

    for (auto &item : connected_points)
    {
        std::cout << "item is:" << item->x << "," << item->y << "\n";
        std::cout << "smaller items: [";
        for (auto &small : item->smaller)
        {
            std::cout << "(" << small->x << "," << small->y << ") ";
        }
        std::cout << " ]\n";

        std::cout << "bigger items: [";
        for (auto &big : item->bigger)
        {
            std::cout << "(" << big->x << "," << big->y << ") ";
        }
        std::cout << " ]\n";

        if (!item->smaller.empty())
        {
            auto &longest = item->longest_finish_point;
            std::cout << "max point until now: "
                      << "(" << longest->x << "," << longest->y << ")"
                      << "\n";
        }
        std::cout << "max finish legth: " << item->max_finish_length << "\n";
        if (!item->bigger.empty())
        {
            auto &longest = item->longest_start_point;
            std::cout << "max point from here: "
                      << "(" << longest->x << "," << longest->y << ")"
                      << "\n";
        }
        std::cout << "max start legth: " << item->max_start_length << "\n";
        std::cout << "\n";
    }
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
    std::vector<std::shared_ptr<Point>> connected_points = ConnectDots(input);

    PrintAll(connected_points);

    // int longest_path = LargestPathLength(connected_points);
}