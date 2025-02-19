#pragma once

#include <string>

class WeatherData
{
private:
    double temperature;
    std::string timeStamp;

public:
    // Default constructor
    WeatherData() : temperature(0), timeStamp("") {}

    // Parameterized constructor
    WeatherData(double temp, const std::string& time) : temperature(temp), timeStamp(time) {}

    // Getter for Temperature
    double getTemperature() const { return temperature; }

    // Setter for Temperature
    void setTemperature(double temp) { temperature = temp; }

    // Getter for TimeStamp
    std::string getTimeStamp() const { return timeStamp; }

    // Setter for TimeStamp
    void setTimeStamp(const std::string& time) { timeStamp = time; }
};