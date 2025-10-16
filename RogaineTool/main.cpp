#include "routePlanner.h"
#include "checkpoint.h"
#include <fstream>

int main(int argc, char* argv[]) {
    // Check for input file
    if (argc != 2) {
        std::cerr << "Missing file... Usage: " << argv[0] << " <filename>" << std::endl;
        return 1;
    }

    // Open file with error checking
    std::string filename = argv[1];
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Error: file could not be opened" << std::endl;
        return 1;
    }

    // Add each line of the file to vector lines
    std::string line;
    std::vector<std::string> lines;
    while (std::getline(file, line)) {
        lines.push_back(line);
    }

    file.close();

    // Add points from lines into the points vector
    std::vector<checkpoint> points;
    try {
        std::string token;
        size_t pos;
        for (auto& line : lines) {
            std::vector<int> checkpointArgs;
            while ((pos = line.find(", ")) != std::string::npos) {
                token = line.substr(0, pos);
                checkpointArgs.push_back(stoi(token));
                line.erase(0, pos + 2);
            }
            checkpointArgs.push_back(stoi(line));

            if (checkpointArgs.size() != 4) {
                std::cerr << "Error: Incorrect file format" << std::endl;
                return 1;
            }
            points.push_back(checkpoint(checkpointArgs[0], checkpointArgs[1], checkpointArgs[2], checkpointArgs[3]));
        }
    }
    catch (...) {
        std::cerr << "Error: Incorrect file format" << std::endl;
        return 1;
    }


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