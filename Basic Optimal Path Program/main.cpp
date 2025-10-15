#include "routePlanner.h"
#include "checkpoint.h"

#include <vector>

int main() {
    std::vector<checkpoint> points {
        checkpoint(0, 1, 3, 0),
        checkpoint(1, 6, 4, 2),
        checkpoint(2, 6, 5, 3),
        checkpoint(3, 2, 7, 7),
    };

    routePlanner newMap(points, 170);

    routePlanner::routeResults optimalRoute = newMap.optimalPath();

    std::cout << "Route: ";

    if (!optimalRoute.visitedPath.empty()) {
        for (std::size_t i = 0; i < optimalRoute.visitedPath.size(); i++) {
            std::cout << optimalRoute.visitedPath[i] << " ";
        }
    }

    std::cout << "\nDistance: " << optimalRoute.totalDistance << std::endl;
    std::cout << "Points: " << optimalRoute.totalPoints << std::endl;

    return 0;
}