#ifndef ROUTEPLANNER_H
#define ROUTEPLANNER_H

#include <vector>
#include <unordered_map>
#include <cmath>
#include <iostream>
#include <map>
#include "checkpoint.h"




class routePlanner {
    public:
        struct routeResults {
            int totalPoints = 0;
            double totalDistance = 0;
            std::vector<int> visitedPath;
        };

    private:
        /* First point in checkpoints is the starting position */
        std::vector<checkpoint> checkpoints;
        std::vector<std::vector<int>> allPathOptions;
        int maxDistance;
        int best;

        std::map<std::pair<int, std::vector<bool>>, routePlanner::routeResults> DPcalculated;

        std::vector<std::vector<double>> dist;   // precomputed distances i<->j
        void buildDistanceMatrix();

    public:
        routePlanner(std::vector<checkpoint> checkpoints, int maxDistance);

        double distanceBetweenPoints(const checkpoint& checkpoint1, const checkpoint& checkpoint2);

        routeResults optimalPath();

        routeResults DPPathRecursive(int current, std::vector<bool> visited, double currentDistance, int currentPoints); 

        routeResults greedyRoute();
};

#endif