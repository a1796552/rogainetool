#include "routePlanner.h"

routePlanner::routePlanner(std::vector<checkpoint> checkpoints, int maxDistance): checkpoints(std::move(checkpoints)), maxDistance(maxDistance), best(0) {
    buildDistanceMatrix();   
}

double routePlanner::distanceBetweenPoints(const checkpoint& checkpoint1, const checkpoint& checkpoint2) {
    return (sqrt(pow(checkpoint1.x - checkpoint2.x, 2) + pow(checkpoint1.y - checkpoint2.y, 2)));
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
        routeResults r = simulateRoute(path);
        if (r.totalPoints > maxPoints ||
            (r.totalPoints == maxPoints && r.totalDistance < optimalPath.totalDistance)) {
            optimalPath = r;
            maxPoints = r.totalPoints;
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
    // All paths discovered
    if (visitedAll) {
        allPathOptions.push_back(currentPath);
        return;
    }
    
    // Recursively call for each possible paths
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

void routePlanner::buildDistanceMatrix() {
    int n = static_cast<int>(checkpoints.size());
    dist.assign(n, std::vector<double>(n, 0.0));
    for (int i = 0; i < n; ++i) {
        for (int j = i + 1; j < n; ++j) {
            double d = distanceBetweenPoints(checkpoints[i], checkpoints[j]);
            dist[i][j] = dist[j][i] = d;
        }
    }
}

routePlanner::routeResults routePlanner::greedyRoute() {
    routeResults r;
    if (checkpoints.empty()) return r;

    int n = static_cast<int>(checkpoints.size());
    std::vector<bool> used(n, false);
    used[0] = true;

    std::vector<int> order;
    order.reserve(n + 1);
    order.push_back(0);

    double total = 0.0;
    int points = 0;

    while (true) {
        int bestNext = -1;
        double bestScore = -1.0;

        int last = order.back();

        for (int j = 1; j < n; ++j) if (!used[j]) {
            double step = dist[last][j];
            double back = dist[j][0];

            // only consider j if we can still get home after taking it
            if (total + step + back > static_cast<double>(maxDistance)) continue;

            // objective: points gained per distance spent (small epsilon to avoid div0)
            double gain = static_cast<double>(checkpoints[j].value);
            double score = gain / (step + 1e-9);

            if (score > bestScore) {
                bestScore = score;
                bestNext = j;
            }
        }

        if (bestNext == -1) break;  // nothing else fits while allowing return

        total  += dist[last][bestNext];
        points += checkpoints[bestNext].value;
        used[bestNext] = true;
        order.push_back(bestNext);
    }

    // return to start (feasible by construction if we visited at least start)
    if (!order.empty()) {
        total += dist[order.back()][0];
        order.push_back(0);
    }

    r.totalDistance = total;
    r.totalPoints   = points;
    r.visitedPath   = std::move(order);
    return r;
}

