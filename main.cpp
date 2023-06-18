#include <iostream>
#include <string>
#include <vector>
#include <unordered_set>
#include <algorithm>
#include <iomanip>
#include <memory>
#include <sstream>
#include <fstream>

#include "main.h"

size_t heaviest_path_weight = 0;

std::vector<std::pair<double, double>> GetPointsFromFile(const std::string &file_path)
{
    std::vector<std::pair<double, double>> res;
    std::string line;
    std::ifstream file(file_path);
    if (!file)
    {
        std::cerr << "Failed to open the file " << file_path << std::endl;
        throw;
    }

    while (std::getline(file, line))
    {
        std::pair<double, double> pair;
        std::istringstream stream(line);
        if (stream >> pair.first >> pair.second)
        {
            // std::cout << "Pair: (" << std::setprecision(15) << pair.first << ", " << std::setprecision(15)
            //           << pair.second << ")" << std::endl;
            res.push_back(pair);
        }
        else
        {
            std::cerr << "Failed to parse the line: " << line << std::endl;
        }
    }

    return res;
}

void print_vector_points(std::set<std::shared_ptr<Point>> &points_vector)
{
    std::cout << "[";
    for (auto &point : points_vector)
    {
        std::cout << "(" << point->x << "," << point->y << ") ";
    }
    std::cout << "]";
}

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

// if (p_res->heaviest_finish_weight + 1 > curr_point->heaviest_finish_weight)
// {
//     curr_point->heaviest_finish_point = p_res;
//     curr_point->heaviest_finish_weight = p_res->heaviest_finish_weight + 1;
// }

std::vector<std::shared_ptr<Point>> ConnectDots(std::vector<std::pair<double, double>> &points)
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
        // go over prev points and add them if are lower in y also. (was sorted by x so no need for x check)
        // std::cout << "***************\n";
        // std::cout << "point is :" << curr_point->x << "," << curr_point->y << "\n";

        for (auto it = res.rbegin(); it != res.rend(); it++)
        {
            auto p_res = *it;
            // std::cout << "point to check:" << p_res->x << "," << p_res->y << "\n";
            // std::cout << "points connected: ";
            // print_vector_points(curr_point->smaller_path_connected);
            // std::cout << "\n";
            bool is_point_connected = std::find(curr_point->smaller_path_connected.begin(), curr_point->smaller_path_connected.end(), p_res) != curr_point->smaller_path_connected.end();
            if (!is_point_connected && p_res->y < curr_point->y)
            {
                // std::cout << "connecting point!!!\n";
                // std::cout << "our point" <<  point.first << "," << point.second << " - ";
                // std::cout << "smaller point: " <<  ready_point.x << "," << ready_point.y << "\n";

                // insert the pair as it is smaller then the point.
                curr_point->smaller.push_back(p_res);
                p_res->bigger.push_back(curr_point);
                curr_point->smaller_path_connected.insert(p_res);
                curr_point->smaller_path_connected.insert(p_res->smaller_path_connected.begin(), p_res->smaller_path_connected.end());
            }
        }
        // the bigger values will be created later.
        res.push_back(curr_point);
    }
    return res;
}

void CalculateHeaviestPath(const std::vector<std::shared_ptr<Point>> &points_list)
{
    for (auto &point : points_list)
    {
        // go over prev points and add them if are lower in y also. (was sorted by x so no need for x check)
        point->heaviest_finish_weight = point->weight;
        for (auto &smaller_point : point->smaller)
        {
            if (smaller_point->heaviest_finish_weight + point->weight > point->heaviest_finish_weight)
            {
                point->heaviest_finish_weight = smaller_point->heaviest_finish_weight + point->weight;
                point->heaviest_finish_point = smaller_point;
            }
        }
    }

    for (auto it = points_list.rbegin(); it != points_list.rend(); it++)
    {
        auto point = *it;
        // go over prev points and add them if are lower in y also. (was sorted by x so no need for x check)
        point->heaviest_start_weight = point->weight;
        for (auto &bigger_point : point->bigger)
        {
            if (bigger_point->heaviest_start_weight + point->weight > point->heaviest_start_weight)
            {
                point->heaviest_start_weight = bigger_point->heaviest_start_weight + point->weight;
                point->heaviest_start_point = bigger_point;
            }
        }

        point->heaviest_path_weight = point->heaviest_finish_weight + point->heaviest_start_weight - point->weight;
        if (point->heaviest_path_weight > heaviest_path_weight)
        {
            heaviest_path_weight = point->heaviest_path_weight;
        }
    }
}

void ClaculateNumberOfPaths(const std::vector<std::shared_ptr<Point>> &points_list)
{

    for (auto &point : points_list)
    {
        point->paths_ends_in_point = point->smaller.empty();
        for (auto &smaller_point : point->smaller)
        {
            point->paths_ends_in_point += smaller_point->paths_ends_in_point;
        }
    }

    for (auto it = points_list.rbegin(); it != points_list.rend(); it++)
    {
        auto point = *it;
        point->paths_starts_in_point = point->bigger.empty();
        for (auto &bigger_point : point->bigger)
        {
            point->paths_starts_in_point += bigger_point->paths_starts_in_point;
        }
        point->paths_with_point = point->paths_ends_in_point * point->paths_starts_in_point;
    }
}

std::shared_ptr<Point> InceasePointWeight(const std::vector<std::shared_ptr<Point>> &points_list)
{
    std::shared_ptr<Point> next_point_to_increase_weight = NULL;

    for (auto &point : points_list)
    {
        bool can_incease_point_weight = (point->weight == 1) && (point->heaviest_path_weight < heaviest_path_weight);
        bool point_have_less_paths = (next_point_to_increase_weight == NULL) || (next_point_to_increase_weight->paths_with_point < point->paths_with_point);
        if (can_incease_point_weight && point_have_less_paths)
        {
            next_point_to_increase_weight = point;
        }
    }
    if (next_point_to_increase_weight != NULL)
    {
        next_point_to_increase_weight->weight++;
    }

    return next_point_to_increase_weight;
}

// void ClaculateNumberOfPaths(const std::vector<std::shared_ptr<Point>> &points_list)
// {
//     for (auto &point : points_list)
//     {
//         if (point->weight == 2 || point->heaviest_path_weight == heaviest_path_weight)
//         {
//             continue;
//         }

//     }

// }

void PrintAll(std::vector<std::shared_ptr<Point>> &connected_points)
{

    for (auto &point : connected_points)
    {
        std::cout << "point is:" << point->x << "," << point->y << "\n";
        std::cout << "weight: " << point->weight << "\n";
        std::cout << "smaller items: [";
        for (auto &small : point->smaller)
        {
            std::cout << "(" << small->x << "," << small->y << ") ";
        }
        std::cout << " ]\n";

        std::cout << "bigger items: [";
        for (auto &big : point->bigger)
        {
            std::cout << "(" << big->x << "," << big->y << ") ";
        }
        std::cout << " ]\n";

        if (!point->smaller.empty())
        {
            auto &longest = point->heaviest_finish_point;
            std::cout << "max point until now: "
                      << "(" << longest->x << "," << longest->y << ")"
                      << "\n";
        }
        std::cout << "max finish legth: " << point->heaviest_finish_weight << "\n";

        if (!point->bigger.empty())
        {
            auto &longest = point->heaviest_start_point;
            std::cout << "max point from here: "
                      << "(" << longest->x << "," << longest->y << ")"
                      << "\n";
        }
        std::cout << "max start legth: " << point->heaviest_start_weight << "\n";

        std::cout << "number of paths ends in point: " << point->paths_ends_in_point << "\n";
        std::cout << "number of paths starts in point: " << point->paths_starts_in_point << "\n";
        std::cout << "number of paths with point: " << point->paths_with_point << "\n";

        std::cout << "\n";
    }
}

int main()
{
    for (int i = 1; i <= 20; i++)
    {
        std::cout << "----------- Starting calculating from Sheet number: " << i << "-----------\n\n";
        int num_of_points_weight_increase = 0;
        const std::string file_path = "./parsed/parsed-" + std::to_string(i);
        std::cout << "file path: " << file_path;
        std::vector<std::pair<double, double>> input = GetPointsFromFile(file_path);
        // step 1 - connect the dots
        // O(n^2)
        // std::cout << "***** ConnectDots...\n";
        std::vector<std::shared_ptr<Point>> connected_points = ConnectDots(input);

        // std::cout << "***** CalculateHeaviestPath...\n";
        CalculateHeaviestPath(connected_points);
        std::cout << "\n\n heaviest path weight before: " << heaviest_path_weight << "\n";
        // std::cout << "***** ClaculateNumberOfPaths...\n";
        ClaculateNumberOfPaths(connected_points);
        // std::cout << "***** PrintAll:\n\n";
        //  PrintAll(connected_points);

        // std::cout << "***** InceasePointWeight...\n";
        std::shared_ptr<Point> next_point_to_increase_weight = InceasePointWeight(connected_points);
        while (next_point_to_increase_weight)
        {
            num_of_points_weight_increase++;
            //     std::cout << "\n*******************************************\n";
            //   std::cout << "Point increasing: (" << next_point_to_increase_weight->x << "," << next_point_to_increase_weight->y << ")\n";
            // std::cout << "***** CalculateHeaviestPath...\n";
            CalculateHeaviestPath(connected_points);
            // std::cout << "***** ClaculateNumberOfPaths...\n";
            ClaculateNumberOfPaths(connected_points);
            // std::cout << "***** PrintAll:\n\n";
            //   PrintAll(connected_points);
            // std::cout << "***** InceasePointWeight...\n";
            next_point_to_increase_weight = InceasePointWeight(connected_points);
        }

        CalculateHeaviestPath(connected_points);
        std::cout << "\n\n number of points increased = " << num_of_points_weight_increase << "\n";
        std::cout << "\n\n heaviest path weight after: " << heaviest_path_weight << "\n";

    std::cout << "\n!!!!!!!!!! Finished calculating from Sheet number: " << i << "!!!!!!!!!!\n\n";

    }
}