#include <vector>

struct Point
{
    int x;
    int y;
    std::vector<Point> smaller;
    std::vector<Point> bigger;
    int longest_smaller_length;
    int longest_bigger_length;
    Point* biggest_smaller;
    Point* biggest_bigger;
};