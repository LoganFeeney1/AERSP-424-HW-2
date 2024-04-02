/************************************************************************************************************************
Logan Feeney
Homework 2
Probem 3
3/27/24
************************************************************************************************************************/

#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <vector>
#include <queue>

using namespace std;

// Declare global variables and synchronization primitives
mutex mtx;  // Mutex for synchronizing access to shared resources
condition_variable cv;  // Condition variable for managing landing queue
queue<int> landingQueue;  // Queue to keep track of aircraft waiting to land
int currentPattern = 0;  // Current number of aircraft in the landing pattern
const int maxPattern = 3;  // Maximum allowed aircraft in the landing pattern
int timeSeconds = 0;  // Simulation time in seconds

// Function for aircraft requesting to land
void request_landing(int id) {
    unique_lock<mutex> lock(mtx);  // Lock the mutex for thread-safe access
    cout << "Aircraft #" << id << " requesting landing." << endl;

    // Check if the landing pattern can accommodate the aircraft
    if (currentPattern < maxPattern) {
        currentPattern++;  // Increase the count of aircraft in the pattern
        landingQueue.push(id);  // Add the aircraft to the landing queue
        cv.notify_one();  // Notify the ATC thread if it's waiting for aircraft
    }
    else {
        // If the pattern is full, redirect the aircraft to another airport
        cout << "Approach pattern is full. Aircraft #" << id << " redirected to another airport." << endl;
        cout << "Aircraft #" << id << " flying to another airport." << endl;
    }
}

// ATC (Air Traffic Controller) function to manage aircraft landing
void atc_function() {
    unique_lock<mutex> lock(mtx);  // Lock the mutex for thread-safe access

    // Continue the simulation until the specified time is reached
    while (timeSeconds < 5) {
        // Wait for an aircraft to be added to the landing queue
        cv.wait(lock, [] { return !landingQueue.empty(); });

        // Exit if the simulation time has reached its limit
        if (timeSeconds >= 5) {
            break;
        }

        // Clear aircraft to land as long as there are aircraft in the queue and time allows
        while (!landingQueue.empty() && timeSeconds < 5) {
            int aircraftId = landingQueue.front();  // Get the ID of the next aircraft
            landingQueue.pop();  // Remove the aircraft from the queue
            cout << "Aircraft #" << aircraftId << " is cleared to land." << endl;
            currentPattern--;  // Decrease the count of aircraft in the pattern
            timeSeconds++;  // Increment the simulation time
            cout << "Runway is now free." << endl;
            this_thread::sleep_for(chrono::seconds(1));  // Simulate the time it takes to land
        }
    }
}

int main() {
    vector<thread> aircraftThreads;  // Vector to store aircraft threads

    // Process the first two aircraft requests exclusively
    aircraftThreads.push_back(thread(request_landing, 0));
    aircraftThreads.push_back(thread(request_landing, 1));
    aircraftThreads[0].join();  // Wait for the first aircraft thread to complete
    aircraftThreads[1].join();  // Wait for the second aircraft thread to complete

    // Start the ATC thread to manage the landing pattern
    thread atcThread(atc_function);

    // Create and start threads for the remaining aircraft
    for (int i = 2; i < 10; ++i) {
        aircraftThreads.push_back(thread(request_landing, i));
    }

    // Wait for all remaining aircraft threads to complete
    for (size_t i = 2; i < aircraftThreads.size(); ++i) {
        if (aircraftThreads[i].joinable()) {
            aircraftThreads[i].join();
        }
    }

    atcThread.join();  // Wait for the ATC thread to complete

    cout << "Duration: " << timeSeconds << " seconds." << endl;  // Print the total simulation time

    return 0;
}
