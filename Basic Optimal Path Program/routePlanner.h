#ifndef ROUTEPLANNER_H
#define ROUTEPLANNER_H

#include <vector>
#include <unordered_map>
#include <cmath>
#include "checkpoint.h"
#include <iostream>


class routePlanner {
    private:
        /* First point in checkpoints is the starting position */
        std::vector<checkpoint> checkpoints;
        std::vector<std::vector<int>> allPathOptions;
        int maxDistance;
        int best;

    public:
        routePlanner(std::vector<checkpoint> checkpoints, int maxDistance);

        struct routeResults {
            int totalPoints = 0;
            double totalDistance = 0;
            std::vector<int> visitedPath;
        };

        double distanceBetweenPoints(const checkpoint& checkpoint1, const checkpoint& checkpoint2);

        void addCheckpoint(checkpoint newCheckpoint);

        void printCheckpoints();

        routeResults optimalPath();

        void recursivePathGenerator(std::vector<int> currentPath, std::vector<bool> visited);

        routeResults simulateRoute(std::vector<int> currentPath);
};

#endif