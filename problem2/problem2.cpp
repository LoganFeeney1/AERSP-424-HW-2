/************************************************************************************************************************
Logan Feeney
Homework 2
Probem 2
3/27/24
************************************************************************************************************************/

#include <iostream>
#include <vector>
#include <algorithm>
#include <chrono>
#include <ctime>

using namespace std;

struct Tool {
    bool taken;
};

struct Robot {
    int position;
    bool hasTool1;
    bool hasTool2;
    bool completedTask;
};

// Function to check if a robot can start a task
bool canStartTask(const Robot& robot, const vector<Tool>& tools) {
    return robot.hasTool1 && robot.hasTool2 && !tools[robot.position].taken;
}

int main() {
    const int numRobots = 5;
    const int numTools = 5;
    const int moveTime = 1;
    const int taskTime = 5;

    vector<Robot> robots(numRobots);
    vector<Tool> tools(numTools, { false }); // Initially, all tools are available

    // Initialize robots
    for (int i = 0; i < numRobots; ++i) {
        robots[i].position = i;
        robots[i].hasTool1 = false;
        robots[i].hasTool2 = false;
        robots[i].completedTask = false;
    }

    int totalTime = 0;

    // Simulate until all tasks are completed
    while (any_of(robots.begin(), robots.end(), [](const Robot& r) { return !r.completedTask; })) {
        // Move robots
        for (int i = 0; i < numRobots; ++i) {
            int nextPos = (robots[i].position + 1) % numRobots;
            robots[i].position = nextPos;
        }

        // Check if robots can grab tools and start tasks
        for (int i = 0; i < numRobots; ++i) {
            if (!robots[i].hasTool1 && !robots[i].hasTool2) {
                robots[i].hasTool1 = true;
                robots[i].hasTool2 = true;
                tools[robots[i].position].taken = true; // Robot takes both tools
                auto now = chrono::system_clock::to_time_t(chrono::system_clock::now());
                cout << "Robot " << i << " picks up tools at position " << robots[i].position << " at " << ctime(&now);
            }

            // Check if the robot can start a task
            if (canStartTask(robots[i], tools) && !robots[i].completedTask) {
                robots[i].completedTask = true;
                totalTime += taskTime; // Add task completion time
                auto now = chrono::system_clock::to_time_t(chrono::system_clock::now());
                cout << "Robot " << i << " starts task at position " << robots[i].position << " at " << ctime(&now);
            }
        }

        totalTime += moveTime; // Add time for robot movement
    }

    cout << "Total time taken: " << totalTime << " seconds\n";

    return 0;
}
