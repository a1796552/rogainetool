#include "routePlanner.h"

routePlanner::routePlanner(std::vector<checkpoint> checkpoints, int maxDistance): checkpoints(checkpoints), maxDistance(maxDistance) {}

double routePlanner::distanceBetweenPoints(const checkpoint& checkpoint1, const checkpoint& checkpoint2) {
    return (sqrt(pow(checkpoint1.x - checkpoint2.x, 2) + pow(checkpoint1.y - checkpoint2.y, 2)));
} 

void routePlanner::resetPointsToUnvisited() {
    for (auto& point : checkpoints) {
        point.visited = false;
    }
}

void routePlanner::addCheckpoint(checkpoint newCheckpoint) {
    checkpoints.push_back(newCheckpoint);
}

void routePlanner::printCheckpoints() {
    for (auto& point : checkpoints) {
        std::cout << point.checkpointID << ", (" << point.x << "," << point.y << "), " << point.value << std::endl;
    }
}

/* Still need to figure out an optimal path algorithm */
std::vector<int> routePlanner::optimalPath() {
    std::vector<int> path;



    return path;
}
