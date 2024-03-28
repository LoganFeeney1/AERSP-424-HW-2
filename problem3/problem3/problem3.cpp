/************************************************************************************************************************
Logan Feeney
Homework 2
Probem 3
3/27/24
************************************************************************************************************************/

#include <iostream>
#include <vector>
#include <thread>
#include <chrono>

void request_landing(int aircraft_number)
{
    std::cout << "Aircraft " << aircraft_number << " is requesting to land." << std::endl;
}

void cleared_landing(int aircraft_number)
{
    std::cout << "Aircraft " << aircraft_number << " is cleared to land." << std::endl;
}

void runway_clear()
{
    std::cout << "Runway is clear." << std::endl;
}

void redirect_to_other_airport(int aircraft_number)
{
    std::cout << "The approach pattern is full. Aircraft " << aircraft_number << " is redirected to another airport." << std::endl;
}

int main()
{
    std::vector<int>aircraft_in_queue = { 1,2,4,6,8,9,7,0,3,5 };  //update order of aircraft

    for (int aircraft_number : aircraft_in_queue)
    {
        if (aircraft_number == 9 || aircraft_number == 7 || aircraft_number == 0 || aircraft_number == 3 || aircraft_number == 5)
        {
            request_landing(aircraft_number);
        }
        else
        {
            redirect_to_other_airport(aircraft_number);
            cleared_landing(aircraft_number);
            runway_clear();

            std::this_thread::sleep_for(std::chrono::seconds(1));
        }
    }

    int total_duration = aircraft_in_queue.size();

    std::cout << "Total duration: " << total_duration - 5 << " seconds" << std::endl;

    return 0;
}