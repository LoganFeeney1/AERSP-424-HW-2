/************************************************************************************************************************
Logan Feeney
Homework 2
Probem 3
3/27/24
************************************************************************************************************************/

#include <iostream>
#include <string>    
#include <queue>     

using namespace std;

// Global variables
queue<int> landingQueue;  // Queue to hold the order of aircraft waiting to land
int patternCount = 0;     // Counter for the number of aircraft currently in the traffic pattern
int landedCount = 0;      // Counter for the number of aircraft that have landed
const int maxPattern = 3; // Maximum number of aircraft allowed in the traffic pattern at once

// Function to process landing requests
void process_landing(int aircraftNumber) 
{
    cout << "Aircraft #" << aircraftNumber << " requesting landing." << endl;  // Output landing request message
    if (patternCount < maxPattern) 
    {  // Check if the traffic pattern can accommodate more aircraft
        patternCount++;               // Increment the pattern counter
        landingQueue.push(aircraftNumber);  // Add the aircraft to the landing queue
    }
    else 
    {
        // Output messages if the traffic pattern is full and redirect the aircraft
        cout << "Approach pattern is full. Aircraft #" << aircraftNumber << " redirected to another airport." << endl;
        cout << "Aircraft #" << aircraftNumber << " flying to another airport." << endl;
    }
}

// Function to clear aircraft for landing
void clear_landing() 
{
    while (!landingQueue.empty() && patternCount > 0) 
    {  // Loop while the queue is not empty and the pattern is not full
        int aircraftNumber = landingQueue.front();  // Get the number of the next aircraft to land
        landingQueue.pop();                         // Remove the aircraft from the queue
        cout << "Aircraft #" << aircraftNumber << " is cleared to land." << endl;  // Output clearance message
        cout << "Runway is now free." << endl;  // Output runway clearance message
        patternCount--;  // Decrement the pattern counter as the aircraft has landed
        landedCount++;   // Increment the landed aircraft counter
    }
}

int main() 
{
    // Process landing for Aircraft 1 and 2 individually
    process_landing(1);  // Aircraft 1 requests to land
    clear_landing();     // Clear Aircraft 1 to land
    process_landing(2);  // Aircraft 2 requests to land
    clear_landing();     // Clear Aircraft 2 to land

    // Define and process simultaneous arrival of aircraft 4, 6, 8, 9, 7, 0, 3, 5
    int simultaneousAircraft[] = { 4, 6, 8, 9, 7, 0, 3, 5 };  // Array of aircraft numbers arriving simultaneously
    for (int aircraft : simultaneousAircraft) 
    {  // Loop through the array of simultaneously arriving aircraft
        process_landing(aircraft);  // Each aircraft in the array requests to land
    }

    clear_landing();  // Clear any remaining aircraft in the queue to land

    cout << "Total duration: " << landedCount << " seconds." << endl;  // Output the total duration of landings

    return 0;
}
