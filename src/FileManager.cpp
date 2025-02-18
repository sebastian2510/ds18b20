#include "FileManager.h"
#include <fstream>
#include <iostream>
#include <ctime>
#include <nlohmann/json.hpp>
#include "Models/WeatherData.h"

using namespace std;
using json = nlohmann::json;

std::string FileManager::FilePath = "/data.json";

bool FileManager::AppendData(WeatherData data)
{
    if (data.getTemperature() == 0 || data.getTimeStamp().empty())
    {
        return false;
    }

    json jsonData;
    ifstream inFile(FilePath);

    if (inFile.is_open())
    {
        inFile >> jsonData;
        inFile.close();
    }

    json newData = {
        {"Temperature", data.getTemperature()},
        {"TimeStamp", data.getTimeStamp()}
    };

    jsonData.push_back(newData);

    ofstream outFile(FilePath);
    if (outFile.is_open())
    {
        outFile << jsonData.dump(4);
        outFile.close();
        return true;
    }

    return false;
}

void FileManager::GetData(std::vector<WeatherData>& data)
{
    if (FilePath.empty())
    {
        return;
    }

    ifstream inFile(FilePath);

    if (!inFile.is_open())
    {
        return;
    }

    json jsonData;
    inFile >> jsonData;

    if (jsonData.empty())
    {
        return;
    }

    for (const auto& item : jsonData)
    {
        WeatherData weatherData;
        weatherData.setTemperature(item["Temperature"]);
        weatherData.setTimeStamp(item["TimeStamp"]);
        data.push_back(weatherData);
    }

    inFile.close();
}