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
        int maxDistance;

    public:
        routePlanner(std::vector<checkpoint> checkpoints, int maxDistance);

        double distanceBetweenPoints(const checkpoint& checkpoint1, const checkpoint& checkpoint2);

        void resetPointsToUnvisited();

        void addCheckpoint(checkpoint newCheckpoint);

        void printCheckpoints();

        std::vector<int> optimalPath();
};

#endif