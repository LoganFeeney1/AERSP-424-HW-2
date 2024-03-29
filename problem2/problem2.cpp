/************************************************************************************************************************
Logan Feeney
Homework 2
Probem 2
3/27/24
************************************************************************************************************************/

#include <iostream>
#include <vector>
#include <array>

const int NUM_ROBOTS = 5; // Total number of robots
const int TOOL_REACH_TIME = 1; // Time taken for each robot to acquire tools
const int TASK_TIME = 5; // Time taken for each robot to perform the task

struct Robot {
    int id; // Robot's unique identifier
    bool hasTool; // Flag to check if the robot has acquired the tools
};

void processRobots(std::vector<Robot>& robots, const std::array<int, 2>& pair) {
    // Print "collecting data" messages
    for (int id : pair) {
        if (id >= 0) { // Ensure the robot ID is valid
            std::cout << "Robot " << robots[id].id << " is collecting data." << std::endl;
            robots[id].hasTool = true;
        }
    }

    // No actual delay for acquiring tools, but logic is retained
    // Print "acquired tools" messages
    for (int id : pair) {
        if (id >= 0) {
            std::cout << "Robot " << robots[id].id << " acquired tools and started performing the task." << std::endl;
        }
    }

    // No actual delay for task completion, but logic is retained
    // Print "finished task" messages
    for (int id : pair) {
        if (id >= 0) {
            robots[id].hasTool = false;
            std::cout << "Robot " << robots[id].id << " finished the task and returned the tools." << std::endl;
        }
    }
}

int completeTasks(std::vector<Robot>& robots) {
    int totalTime = 0; // Total time taken for all robots to complete their tasks
    std::array<std::array<int, 2>, 3> pairs = { {{0, 2}, {1, 3}, {4, -1}} }; // Pairs of robots working together

    // Process each pair of robots
    for (const auto& pair : pairs) {
        processRobots(robots, pair);
        totalTime += TOOL_REACH_TIME + TASK_TIME; // Calculate the total time
    }

    return totalTime;
}

int main() {
    std::vector<Robot> robots(NUM_ROBOTS); // Initialize the robots

    // Assign IDs and set tool flag to false
    for (int i = 0; i < NUM_ROBOTS; ++i) {
        robots[i].id = i;
        robots[i].hasTool = false;
    }

    // Complete tasks and calculate total time
    int totalTime = completeTasks(robots);
    std::cout << "Total time for all robots to complete their tasks: " << totalTime << " seconds" << std::endl;
    return 0;
}

