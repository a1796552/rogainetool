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
    
    for (std::size_t i = 0; i < checkpoints.size(); i++) {
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
    if (currentPath.empty()) return results;

    // record start
    results.visitedPath.reserve(currentPath.size() + 1);
    results.visitedPath.push_back(currentPath[0]);

    // walk the path BUT require that after each hop we can still return to 0
    for (int i = 1; i < static_cast<int>(currentPath.size()); ++i) {
        const int prevIdx = currentPath[i - 1];
        const int nextIdx = currentPath[i];

        const double step = distanceBetweenPoints(checkpoints[prevIdx], checkpoints[nextIdx]);
        const double backIfWeTakeNext = distanceBetweenPoints(checkpoints[nextIdx], checkpoints[0]);

        // only take this hop if we can still afford to return to start afterwards
        if (results.totalDistance + step + backIfWeTakeNext > static_cast<double>(maxDistance)) {
            break; // stop here; the current prefix is the best feasible with return
        }

        results.totalDistance += step;
        results.totalPoints += checkpoints[nextIdx].value; // score after start
        results.visitedPath.push_back(nextIdx);
    }

    // finally, return to start (always feasible by the check above)
    if (!results.visitedPath.empty()) {
        const int lastIdx = results.visitedPath.back();
        results.totalDistance += distanceBetweenPoints(checkpoints[lastIdx], checkpoints[0]);
        results.visitedPath.push_back(0);
    }

    return results;
}


