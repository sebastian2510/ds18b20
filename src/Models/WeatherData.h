#pragma once

#include <string>

class WeatherData
{
private:
    int temperature;
    std::string timeStamp;

public:
    // Default constructor
    WeatherData() : temperature(0), timeStamp("") {}

    // Parameterized constructor
    WeatherData(int temp, const std::string& time) : temperature(temp), timeStamp(time) {}

    // Getter for Temperature
    int getTemperature() const { return temperature; }

    // Setter for Temperature
    void setTemperature(int temp) { temperature = temp; }

    // Getter for TimeStamp
    std::string getTimeStamp() const { return timeStamp; }

    // Setter for TimeStamp
    void setTimeStamp(const std::string& time) { timeStamp = time; }
};