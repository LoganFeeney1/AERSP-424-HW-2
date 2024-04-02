/************************************************************************************************************************
Logan Feeney
Homework 2
Probem 2
3/27/24
************************************************************************************************************************/

#include <iostream>
#include <vector>
#include <array>
#include <thread>
#include <mutex>

// global constants for the number of robots, time to reach the tools, and time to complete the tasks
const int num_robots = 5;
const int time_reach_tool = 1;
const int task_time = 5;

// mutexes for each tool to prevent concurrent access
std::array<std::mutex, num_robots> toolMutexes;
// mutex for synchronizing console output to prevent text blending
std::mutex coutMutex;

// structure named robot
struct Robot 
{
    int ID;             // robot ID
    bool has_tool;      // check if robot has tools
};

// function to simulate a robot performing its task
void perform_task(Robot& robot, int tool1, int tool2) 
{
    // lock the tools needed for the task to prevent other robots from using them
    std::lock(toolMutexes[tool1], toolMutexes[tool2]);

    // synchronize console output and display that the robot is collecting data
    {
        std::lock_guard<std::mutex> coutLock(coutMutex);
        std::cout << "Robot " << robot.ID << " is collecting data." << std::endl;
    }

    // simulate the time taken for the robot to reach the tools
    std::this_thread::sleep_for(std::chrono::seconds(time_reach_tool));
    robot.has_tool = true;

    // synchronize console output and display that the robot has started its task
    {
        std::lock_guard<std::mutex> coutLock(coutMutex);
        std::cout << "Robot " << robot.ID << " acquired tools and started performing the task." << std::endl;
    }

    // simulate the time taken for the robot to complete the task
    std::this_thread::sleep_for(std::chrono::seconds(task_time));
    robot.has_tool = false;

    // synchronize console output and display that the robot has finished its task
    {
        std::lock_guard<std::mutex> coutLock(coutMutex);
        std::cout << "Robot " << robot.ID << " finished the task and returned the tools." << std::endl;
    }

    // unlock the tools so other robots can use them
    toolMutexes[tool1].unlock();
    toolMutexes[tool2].unlock();
}

// function to initiate tasks for all robots and calculate the total time taken
int complete_task(std::vector<Robot>& robots) 
{
    int totalTime = 0;      // initialize the total time taken for all robots to complete their tasks

    // pairs of robots that can work simultaneously without interfering with each other
    std::array<std::array<int, 2>, 3> pairs = { {{0, 2}, {1, 3}, {4, -1}} };

    // process each pair of robots
    for (const auto& pair : pairs) 
    {
        std::vector<std::thread> threads;   // threads for concurrent task execution

        // start tasks for each robot in the pair
        if (pair[0] >= 0) 
        {
            threads.push_back(std::thread(perform_task, std::ref(robots[pair[0]]), pair[0], (pair[0] + 1) % num_robots));
        }
        if (pair[1] >= 0) 
        {
            threads.push_back(std::thread(perform_task, std::ref(robots[pair[1]]), pair[1], (pair[1] + 1) % num_robots));
        }

        // wait for the tasks of the current pair to complete before moving to the next pair
        for (auto& thread : threads) 
        {
            thread.join();
        }

        // update the total time after each pair of robots completes their tasks
        totalTime += time_reach_tool + task_time;
    }

    return totalTime;  // return the total time for all tasks
}

// main function to set up robots, start the task process, and display the total time taken
int main() 
{
    std::vector<Robot> robots(num_robots);      // initialize robots

    // set up each robot with an ID and initial tool status
    for (int i = 0; i < num_robots; ++i) 
    {
        robots[i].ID = i;
        robots[i].has_tool = false;
    }

    // calculate and display the total time taken for all robots to complete their tasks
    int totalTime = complete_task(robots);
    std::cout << "Total time for all robots to complete their tasks: " << totalTime << " seconds" << std::endl;

    return 0;
}