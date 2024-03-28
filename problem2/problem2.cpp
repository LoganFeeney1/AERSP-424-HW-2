/************************************************************************************************************************
Logan Feeney
Homework 2
Probem 2
3/27/24
************************************************************************************************************************/

#include <iostream>
#include <vector>

using namespace std;

// Constants for the number of robots, tools, and times
const int NUM_ROBOTS = 5;
const int NUM_TOOLS = 5;
const int TOOL_REACH_TIME = 1;
const int TASK_TIME = 5;

// Struct to represent a robot
struct Robot 
{
    int id; // Robot ID
    int taskRemaining{ 1 }; // initial task for each robot
    bool hasTools; // check if the robot has tools
    int tasks_left{ 1 };
};

// Function to simulate the robot tasks
void simulateRobotTasks(vector<Robot>& robots) 
{
    int totalTime = 0; // Initialize total time
    bool allTasksCompleted = false; // check if all tasks are completed

    // loop will run until all tasks are completed
    while (!allTasksCompleted)
    {
        allTasksCompleted = true; // at the beginning of each while loop, set check to true and if a robot has not finished task, it will switch back to false
        
        // Loop through each robot
        for (int i = 0; i < NUM_ROBOTS; i++) 
        {
            // Check if the robot still has tasks to complete
            if (robots[i].tasks_left > 0) 
            {
                allTasksCompleted = false;  // Set the flag to false if any task is remaining

                // Check if the robot has tools
                if (robots[i].hasTools) 
                {
                    cout << "Robot " << robots[i].id << " is completing its task." << endl;
                    robots[i].tasks_left -= 1; // Decrease the remaining task time
                    totalTime += 1; // Increase the total time taken

                    // Check if the task is completed
                    if (robots[i].tasks_left == 0) 
                    {
                        robots[i].hasTools = false; // Robot no longer has tools
                        cout << "Robot " << robots[i].id << " has completed its task." << endl;
                    }
                }
                else 
                {
                    cout << "Robot " << robots[i].id << " is waiting for tools." << endl;
                    totalTime += TOOL_REACH_TIME; // Time to reach for tools
                    robots[i].hasTools = true; // Robot now has tools
                }
            }
        }

        // If not all tasks are completed, add time for the next round
        if (!allTasksCompleted) 
        {
            totalTime += TASK_TIME;

            // Adjust for pairs working together
            for (int i = 0; i < NUM_ROBOTS; i++) 
            {
                if (robots[i].hasTools && robots[(i + 2) % NUM_ROBOTS].hasTools) 
                {
                    totalTime -= TOOL_REACH_TIME; // Reduce time as both robots have tools
                    break;
                }
            }
        }
    }

    // Print the total time taken
    cout << "Total time taken: " << totalTime << " seconds." << endl;
}

int main() {
    // Create vector of robots and initialize their properties
    vector<Robot> robots(NUM_ROBOTS);
    for (int i = 0; i < NUM_ROBOTS; i++) 
    {
        robots[i].id = i + 1; // Assign robot ID
        robots[i].taskRemaining = TASK_TIME; // Set initial task time remaining
        robots[i].hasTools = false; // Initially, robots do not have tools
    }

    // Call the function to simulate robot tasks
    simulateRobotTasks(robots);

    return 0; // Exit program
}
