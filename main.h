#include <vector>
#include <memory>
#include <set>

struct Point
{
    double x;
    double y;
    int weight = 1;
    std::vector<std::shared_ptr<Point>> smaller;
    std::set<std::shared_ptr<Point>> smaller_path_connected;
    std::vector<std::shared_ptr<Point>> bigger;
    int heaviest_finish_weight;
    int heaviest_start_weight;
    std::shared_ptr<Point> heaviest_finish_point;
    std::shared_ptr<Point> heaviest_start_point;
    size_t heaviest_path_weight;
    size_t paths_ends_in_point;
    size_t paths_starts_in_point;
    size_t paths_with_point;

    Point(double x, double y) : x(x), y(y) {}
};