#include "routePlanner.h"

routePlanner::routePlanner(std::vector<checkpoint> checkpoints, int maxDistance): checkpoints(checkpoints), maxDistance(maxDistance) {}

double routePlanner::distanceBetweenPoints(const checkpoint& checkpoint1, const checkpoint& checkpoint2) {
    return (sqrt(pow(checkpoint1.x - checkpoint2.x, 2) + pow(checkpoint1.y - checkpoint2.y, 2)));
}

void routePlanner::addCheckpoint(checkpoint newCheckpoint) {
    checkpoints.push_back(newCheckpoint);
}

void routePlanner::printCheckpoints() {
    for (auto& point : checkpoints) {
        std::cout << point.checkpointID << ", (" << point.x << "," << point.y << "), " << point.value << std::endl;
    }
}

/* Generates all possible pathways then simulates each one and returns the largest */
routePlanner::routeResults routePlanner::optimalPath() {
    allPathOptions.clear();
    std::vector<bool> visited(checkpoints.size(), false);
    visited[0] = true;
    std::vector<int> currentPath = {0};
    routeResults optimalPath;
    int maxPoints = -1;
    double maxDistance;

    allPathOptions.clear();
    recursivePathGenerator(currentPath, visited);

    for (auto& path : allPathOptions) {
        if (maxPoints == -1) {
            optimalPath = simulateRoute(path);
        } else {
            routeResults results = simulateRoute(path);
            if (maxPoints < results.totalPoints) {
                optimalPath = results;
            }
        }
    }

    return optimalPath;
}


// Generates all possible paths that can be taken and adds them to vector
void routePlanner::recursivePathGenerator(std::vector<int> currentPath, std::vector<bool> visited) {
    // Check if all nodes have been visited
    bool visitedAll = true;
    for (bool v : visited) {
        if (!v) {
            visitedAll = false;
            break;
        }
    }
    
    if (visitedAll) {
        allPathOptions.push_back(currentPath);
        return;
    }
    
    for (int i = 0; i < checkpoints.size(); i++) {
        if (!visited[i]) {
            visited[i] = true;
            currentPath.push_back(i);

            recursivePathGenerator(currentPath, visited);

            currentPath.pop_back();
            visited[i] = false;
        }
    }

    return;
}

// Check how many points a certain route can score
routePlanner::routeResults routePlanner::simulateRoute(std::vector<int> currentPath) {
    routeResults results;

    for (int i = 1; i < currentPath.size(); i++) {
        double pointDistance = distanceBetweenPoints(checkpoints[currentPath[i]], checkpoints[currentPath[i-1]]);

        if (results.totalDistance + pointDistance > maxDistance) {
            return results;
        }
        results.totalDistance += pointDistance;
        results.totalPoints += checkpoints[currentPath[i]].value;
        results.visitedPath.push_back(i);

    }

    return results;
}

