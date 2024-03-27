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