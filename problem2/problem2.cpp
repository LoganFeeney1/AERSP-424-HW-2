/************************************************************************************************************************
Logan Feeney
Homework 2
Probem 2
3/27/24
************************************************************************************************************************/

#include <iostream>
#include <algorithm>
#include <unordered_map>
#include <unordered_set>
#include <vector>
#include <string>

int main() {
    // Initialize an unordered map to track the time each robot starts a task
    std::unordered_map<std::string, int> started;

    // Initialize an unordered set to keep track of visited robots
    std::unordered_set<std::string> visited;

    // Initialize a vector to keep track of robots that have started a task
    std::vector<std::string> startedArray;

    // Initialize a variable to track the total time in seconds
    int seconds = 0;

    // Create a vector of robot names
    std::vector<std::string> robots = { "robot 0", "robot 1", "robot 2", "robot 3", "robot 4" };

    // Loop until all robots have completed their tasks
    while (visited.size() < 5) {
        // Increment the time for each robot that has started a task
        for (auto& pair : started) {
            pair.second++;
            // If a robot has just started a task, print a message
            if (pair.second == 1) {
                std::cout << pair.first << " acquired tools and starts performing a task" << std::endl;
            }
        }

        // Create a copy of the startedArray vector
        std::vector<std::string> startedArrayCopy = startedArray;

        // Iterate through the robots vector
        for (size_t i = 0; i < robots.size(); ++i) {
            const std::string& robot = robots[i];
            // Check if the robot has completed its task
            if (started.find(robot) != started.end() && started[robot] == 6) {
                // Print a message when the robot finishes the task
                std::cout << robot << " finished the task and returning the tools" << std::endl;
                // Remove the robot from the started map and robots vector
                started.erase(robot);
                auto it = std::find(robots.begin(), robots.end(), robot);
                robots.erase(it);
                // Determine the index of the previous robot in the circular arrangement
                size_t prev_index = (i == 0) ? robots.size() - 1 : i - 1;
                // If the previous robot has not been visited, mark it as visited and start its task
                if (visited.find(robots[prev_index]) == visited.end()) {
                    visited.insert(robots[prev_index]);
                    started[robots[prev_index]] = 0;
                    startedArray.push_back(robots[prev_index]);
                    std::cout << robots[prev_index] << " is collecting data" << std::endl;
                }
            }
        }

        // Iterate through the robots vector again
        for (size_t i = 0; i < robots.size(); ++i) {
            const std::string& robot = robots[i];
            // Check if the robot has not been visited and has not started a task
            if (visited.find(robot) == visited.end() && started.find(robot) == started.end()) {
                // Determine the index of the previous and next robots in the circular arrangement
                size_t prev_index = (i == 0) ? robots.size() - 1 : i - 1;
                size_t next_index = (i == robots.size() - 1) ? 0 : i + 1;
                // If the previous robot has not been visited and the next robot has not started a task
                if (visited.find(robots[prev_index]) == visited.end() && started.find(robots[next_index]) == started.end()) {
                    // Mark the robot as visited, start its task, and add it to the startedArray vector
                    visited.insert(robot);
                    started[robot] = 0;
                    startedArray.push_back(robot);
                    std::cout << robot << " is collecting data" << std::endl;
                }
            }
        }
        // Increment the seconds counter
        seconds++;
    }

    // Print messages for robots that are still performing tasks when all others have finished
    for (const auto& pair : started) {
        std::cout << pair.first << " acquired tools and starts performing a task" << std::endl;
        std::cout << pair.first << " finished the task and returning the tools" << std::endl;
    }
    // Print the total duration in seconds
    std::cout << "total duration: " << seconds << " seconds" << std::endl;

    return 0;
}