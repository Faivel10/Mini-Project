#include <vector>
#include <memory>

struct Point
{
    int x;
    int y;
    std::vector<std::shared_ptr<Point>> smaller;
    std::vector<std::shared_ptr<Point>> bigger;
    int max_finish_length = 0;
    int max_start_length = 0;
    std::shared_ptr<Point> longest_finish_point;
    std::shared_ptr<Point> longest_start_point;

    Point(int x, int y) : x(x), y(y) {}

};