#include <vector>

struct Point
{
    int x;
    int y;
    std::vector<Point> smaller;
    int longest_length;
};