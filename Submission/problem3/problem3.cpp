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

// declare global variables and synchronization primitives
mutex mtx;                  // mutex for synchronizing access to shared resources
condition_variable cv;      // condition variable for managing landing queue
queue<int> landing_queue;   // queue to keep track of aircraft waiting to land
int current_pattern = 0;    // current number of aircraft in the landing pattern
const int max_pattern = 3;  // maximum allowed aircraft in the landing pattern
int time_seconds = 0;       // simulation time in seconds

// function for aircraft requesting to land
void request_landing(int id) 
{
    unique_lock<mutex> lock(mtx);   // lock the mutex for thread-safe access
    cout << "Aircraft #" << id << " requesting landing." << endl;

    // check if the landing pattern can accommodate the aircraft
    if (current_pattern < max_pattern) 
    {
        current_pattern++;       // increase the count of aircraft in the pattern
        landing_queue.push(id);  // add the aircraft to the landing queue
        cv.notify_one();        // notify the ATC thread if it's waiting for aircraft
    }
    else 
    {
        // if the pattern is full, redirect the aircraft to another airport
        cout << "Approach pattern is full. Aircraft #" << id << " redirected to another airport." << endl;
        cout << "Aircraft #" << id << " flying to another airport." << endl;
    }
}

// ATC controller function to manage aircraft landing
void atc_function() 
{
    unique_lock<mutex> lock(mtx);   // lock the mutex for thread-safe access

    // continue the simulation until the specified time is reached
    while (time_seconds < 5) 
    {
        // wait for an aircraft to be added to the landing queue
        cv.wait(lock, [] { return !landing_queue.empty(); });

        // exit if the simulation time has reached its limit
        if (time_seconds >= 5) 
        {
            break;
        }

        // clear aircraft to land as long as there are aircraft in the queue and time allows
        while (!landing_queue.empty() && time_seconds < 5) 
        {
            int aircraftId = landing_queue.front();      // get the ID of the next aircraft
            landing_queue.pop();                         // remove the aircraft from the queue
            cout << "Aircraft #" << aircraftId << " is cleared to land." << endl;
            current_pattern--;                           // decrease the count of aircraft in the pattern
            time_seconds++;                              // increment the simulation time
            cout << "Runway is now free." << endl;
            this_thread::sleep_for(chrono::seconds(1)); // simulate the time it takes to land
        }
    }
}

int main() {
    vector<thread> aircraftThreads; // vector to store aircraft threads

    // process the first two aircraft requests exclusively
    aircraftThreads.push_back(thread(request_landing, 0));
    aircraftThreads.push_back(thread(request_landing, 1));
    aircraftThreads[0].join();      // wait for the first aircraft thread to complete
    aircraftThreads[1].join();      // wait for the second aircraft thread to complete

    // start the ATC thread to manage the landing pattern
    thread atcThread(atc_function);

    // create and start threads for the remaining aircraft
    for (int i = 2; i < 10; ++i) 
    {
        aircraftThreads.push_back(thread(request_landing, i));
    }

    // wait for all remaining aircraft threads to complete
    for (size_t i = 2; i < aircraftThreads.size(); ++i) 
    {
        if (aircraftThreads[i].joinable()) 
        {
            aircraftThreads[i].join();
        }
    }

    atcThread.join();  // wait for the ATC thread to complete

    cout << "Duration: " << time_seconds << " seconds." << endl;  // print the total simulation time

    return 0;
}
