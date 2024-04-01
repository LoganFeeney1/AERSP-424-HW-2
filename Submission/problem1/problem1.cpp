/************************************************************************************************************************
Logan Feeney
Homework 2
Probem 1
3/27/24
************************************************************************************************************************/

#include <iostream>
#include <string>
#include <vector>

// abstract base class called "Sensor" (question 1.1)
class Sensor 
{
public:
    virtual void gatherData() const = 0;        // virtual funciton for data collection
    virtual void processData() const = 0;       // virtual function for data processing
    virtual ~Sensor() {}                        // virtual destructor
};

// derived class for temperature sensor (question 1.2)
class TemperatureSensor : public Sensor 
{
public:
    void gatherData() const override 
    {
        std::cout << "Gathering data from temperature sensor." << std::endl;
    }

    void processData() const override 
    {
        std::cout << "Processing data from temperature sensor." << std::endl;
    }
};

// derived class for heading sensor (question 1.2)
class HeadingSensor : public Sensor 
{
public:
    void gatherData() const override 
    {
        std::cout << "Gathering data from heading sensor." << std::endl;
    }

    void processData() const override 
    {
        std::cout << "Processing data from heading sensor." << std::endl;
    }
};

// derived class for attitude sensor (question 1.2)
class AttitudeSensor : public Sensor 
{
public:
    void gatherData() const override 
    {
        std::cout << "Gathering data from attitude sensor." << std::endl;
    }

    void processData() const override 
    {
        std::cout << "Processing data from attitude sensor." << std::endl;
    }
};

// another class name SensorFactory (question 1.3)
class SensorFactory 
{
public:
    static Sensor* createSensor(const std::string& sensorType) 
    {
        if (sensorType == "Temperature") 
        {
            return new TemperatureSensor();
        }
        else if (sensorType == "Heading") 
        {
            return new HeadingSensor();
        }
        else if (sensorType == "Attitude") 
        {
            return new AttitudeSensor();
        }
        else 
        {
            return nullptr; // return null pointer if input string does not match a sensor type
        }
    }
};

// control system class called "AerospaceControlSystem" (question 1.4)
class AerospaceControlSystem 
{
private:
    std::vector<Sensor*> sensors;

public:
    void addSensor(Sensor* sensor) 
    {
        sensors.push_back(sensor);
    }

    void monitorAndAdjust() 
    {
        for (Sensor* sensor : sensors) 
        {
            sensor->gatherData();
            sensor->processData();
            std::cout << "Adjusting controls based on sensor data.\n" << std::endl;
        }
    }

    ~AerospaceControlSystem()   // destructor
    {
        for (Sensor* sensor : sensors)
        {
            delete sensor;
        }
    }
};

// main function (question 1.5)
int main() 
{
    AerospaceControlSystem ctrlSys;

    // instantiating the objects from the aero class and invoking the addSensor function
    ctrlSys.addSensor(SensorFactory::createSensor("Temperature"));
    ctrlSys.addSensor(SensorFactory::createSensor("Heading"));
    ctrlSys.addSensor(SensorFactory::createSensor("Attitude"));

    // Invoking the monitor function
    ctrlSys.monitorAndAdjust();

    return 0;
}

