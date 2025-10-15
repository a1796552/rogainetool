#include "routePlanner.h"
#include "checkpoint.h"

#include <vector>

int main() {
    std::vector<checkpoint> points = {
        checkpoint(0, 0, 0, 0),
        checkpoint(1, 1, 3, 2),
        checkpoint(2, 3, 1, 3),
        checkpoint(3, 4, 6, 7),
        checkpoint(4, 6, 2, 5),
        checkpoint(5, 7, 7, 8),
        checkpoint(6, 2, 8, 6),
        checkpoint(7, 9, 3, 4),
        checkpoint(8, 10, 6, 5),
        checkpoint(9, 12, 2, 6),
        checkpoint(10, 13, 7, 7),
        checkpoint(11, 15, 4, 8),
        checkpoint(12, 16, 9, 9),
        checkpoint(13, 18, 2, 6),
        checkpoint(14, 19, 6, 7),
        checkpoint(15, 20, 10, 8),
        checkpoint(16, 5, 12, 6),
        checkpoint(17, 8, 13, 7),
        checkpoint(18, 11, 11, 8),
        checkpoint(19, 14, 12, 6),
        checkpoint(20, 3, 14, 7),
        checkpoint(21, 6, 16, 8),
        checkpoint(22, 10, 15, 9),
        checkpoint(23, 15, 16, 10),
    };

    routePlanner newMap(points, 14);

    // Run greedy algorithm if there are more than 9 checkpoints, else run brute
    if (points.size() < 10) {
        auto brute = newMap.optimalPath();
        std::cout << "Brute:  ";
        for (int id : brute.visitedPath) std::cout << id << ' ';
        std::cout << " | D=" << brute.totalDistance << " P=" << brute.totalPoints << "\n";
    } else {
        auto greedy = newMap.greedyRoute();
        std::cout << "Greedy: ";
        for (int id : greedy.visitedPath) std::cout << id << ' ';
        std::cout << " | D=" << greedy.totalDistance << " P=" << greedy.totalPoints << "\n";
    }

    return 0;
}