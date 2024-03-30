/************************************************************************************************************************
Logan Feeney
Homework 2
Probem 2
3/27/24
************************************************************************************************************************/

#include <iostream> 
#include <vector>   
#include <array>    

// Define constants for the simulation
const int NUM_ROBOTS = 5; // Total number of robots
const int TOOL_REACH_TIME = 1; // Time taken for each robot to acquire tools
const int TASK_TIME = 5; // Time taken for each robot to perform the task

// Define a structure for the Robot
struct Robot {
    int id; // Robot's unique identifier
    bool hasTool; // Flag to check if the robot has acquired the tools
};

// Function to process the robots' actions
void processRobots(std::vector<Robot>& robots, const std::array<int, 2>& pair) {
    // Iterate over each robot in the pair to simulate data collection
    for (int id : pair) {
        if (id >= 0) { // Check if the robot ID is valid
            std::cout << "Robot " << robots[id].id << " is collecting data." << std::endl;
            robots[id].hasTool = true; // Simulate tool acquisition
        }
    }

    // Iterate over each robot in the pair to simulate tool acquisition and task start
    for (int id : pair) {
        if (id >= 0) {
            std::cout << "Robot " << robots[id].id << " acquired tools and started performing the task." << std::endl;
        }
    }

    // Iterate over each robot in the pair to simulate task completion
    for (int id : pair) {
        if (id >= 0) {
            robots[id].hasTool = false; // Simulate tool return
            std::cout << "Robot " << robots[id].id << " finished the task and returned the tools." << std::endl;
        }
    }
}

// Function to complete the tasks of all robots and calculate the total time
int completeTasks(std::vector<Robot>& robots) {
    int totalTime = 0; // Initialize total time
    // Define pairs of robots that will work together
    std::array<std::array<int, 2>, 3> pairs = { {{0, 2}, {1, 3}, {4, -1}} };

    // Process each pair of robots and update the total time
    for (const auto& pair : pairs) {
        processRobots(robots, pair);
        totalTime += TOOL_REACH_TIME + TASK_TIME; // Add time for each pair
    }

    return totalTime; // Return the total time
}

// Main function of the program
int main() {
    std::vector<Robot> robots(NUM_ROBOTS); // Create a vector of Robot objects

    // Initialize each robot with an ID and set hasTool to false
    for (int i = 0; i < NUM_ROBOTS; ++i) {
        robots[i].id = i;
        robots[i].hasTool = false;
    }

    // Execute the task completion process and calculate the total time
    int totalTime = completeTasks(robots);
    // Output the total time taken for all tasks
    std::cout << "Total time for all robots to complete their tasks: " << totalTime << " seconds" << std::endl;
    return 0; // End of the main function
}


