/************************************************************************************************************************
Logan Feeney
Homework 2
Probem 3
3/27/24
************************************************************************************************************************/
#include <iostream>
#include <string>
#include <vector>

// Abstract base class for sensors
class Sensor {
public:
    virtual void gatherData() const = 0;
    virtual void processData() const = 0;
    virtual ~Sensor() {}
};

// Derived class for temperature sensor
class TemperatureSensor : public Sensor {
public:
    void gatherData() const override {
        std::cout << "Gathering data from Temperature Sensor." << std::endl;
    }

    void processData() const override {
        std::cout << "Processing data from Temperature Sensor." << std::endl;
    }
};

// Derived class for pressure sensor
class PressureSensor : public Sensor {
public:
    void gatherData() const override {
        std::cout << "Gathering data from Pressure Sensor." << std::endl;
    }

    void processData() const override {
        std::cout << "Processing data from Pressure Sensor." << std::endl;
    }
};

// Derived class for position sensor
class PositionSensor : public Sensor {
public:
    void gatherData() const override {
        std::cout << "Gathering data from Position Sensor." << std::endl;
    }

    void processData() const override {
        std::cout << "Processing data from Position Sensor." << std::endl;
    }
};

// Factory class to create sensors
class SensorFactory {
public:
    static Sensor* createSensor(const std::string& sensorType) {
        if (sensorType == "Temperature") {
            return new TemperatureSensor();
        }
        else if (sensorType == "Pressure") {
            return new PressureSensor();
        }
        else if (sensorType == "Position") {
            return new PositionSensor();
        }
        else {
            return nullptr; // Unknown sensor type
        }
    }
};

// Control system class
class AerospaceControlSystem {
private:
    std::vector<Sensor*> sensors;

public:
    void addSensor(Sensor* sensor) {
        sensors.push_back(sensor);
    }

    void monitorAndAdjust() {
        for (Sensor* sensor : sensors) {
            sensor->gatherData();
            sensor->processData();
            std::cout << "Adjusting controls based on sensor data." << std::endl;
        }
    }

    ~AerospaceControlSystem()
    {
        for (Sensor* sensor : sensors)
        {
            delete sensor;
        }
    }
};

int main() {
    AerospaceControlSystem ctrlSys;

    // Add sensors to the control system
    ctrlSys.addSensor(SensorFactory::createSensor("Temperature"));
    ctrlSys.addSensor(SensorFactory::createSensor("Pressure"));
    ctrlSys.addSensor(SensorFactory::createSensor("Position"));

    // Monitor and adjust the control system based on sensor data
    ctrlSys.monitorAndAdjust();

    return 0;
}

