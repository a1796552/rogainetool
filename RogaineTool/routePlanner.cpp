#include "routePlanner.h"

routePlanner::routePlanner(std::vector<checkpoint> checkpoints, int maxDistance): checkpoints(std::move(checkpoints)), maxDistance(maxDistance), best(0) {
    buildDistanceMatrix();   
}

double routePlanner::distanceBetweenPoints(const checkpoint& checkpoint1, const checkpoint& checkpoint2) {
    return (sqrt(pow(checkpoint1.x - checkpoint2.x, 2) + pow(checkpoint1.y - checkpoint2.y, 2)));
}

/* Uses dynamic programming to find the best pathway between the points.
Only use if there are less than 20 points to search */
routePlanner::routeResults routePlanner::optimalPath() {
    std::vector<bool> visited(checkpoints.size(), false);
    visited[0] = true;
    DPcalculated.clear();

    return DPPathRecursive(0, visited, 0.0, 0);  
}

routePlanner::routeResults routePlanner::DPPathRecursive(int current, std::vector<bool> visited, double currentDistance, int currentPoints) {
    // If the best has already been calculated, return the best
    if (DPcalculated.count({current, visited})) {
        return DPcalculated[{current, visited}];
    }

    // Create best using current path
    routeResults best;
    best.totalDistance = currentDistance;
    best.totalPoints = currentPoints;
    best.visitedPath = {current};

    // Run for every unvisited next node
    for (int i=0; i < static_cast<int>(checkpoints.size()); i++) {
        if (!visited[i]) {
            // Check to make sure curent to next location to start can be reached
            if (currentDistance + dist[current][i] + dist[i][0] <= maxDistance) {
                visited[i] = true;

                // Call to recursively check path combinations adding to current distance and points
                routeResults rec = DPPathRecursive(i, visited, currentDistance + dist[current][i], currentPoints + checkpoints[i].value);
;
                
                // Reset to false for future recursive calls
                visited[i] = false;

                // If the total number of points is better than current best or if points are equal that distance is less than best
                if (rec.totalPoints > best.totalPoints || (rec.totalPoints == best.totalPoints && rec.totalDistance < best.totalDistance)) {
                    best = rec;
                    best.visitedPath.insert(best.visitedPath.begin(), current);
                }
            }
        }
    }

    // Add distance to return to start from current point if not already there
    if (best.visitedPath.back() != 0) {
        best.totalDistance += dist[best.visitedPath.back()][0];
        best.visitedPath.push_back(0);
    }



    // Store value in map for future recursive calls
    DPcalculated[{current, visited}] = best;
    return best;
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

