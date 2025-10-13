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

    newMap.printCheckpoints();

    return 0;
}