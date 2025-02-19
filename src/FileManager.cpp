#include <Arduino.h>
#include "FileManager.h"
#include <SPIFFS.h>
#include <nlohmann/json.hpp>
#include "Models/WeatherData.h"

using namespace std;
using json = nlohmann::json;

std::string FileManager::FilePath = "/data.json";

void FileManager::setup() {
    if (!SPIFFS.begin(true))
    {
        Serial.println("An Error has occurred while mounting SPIFFS");
        return;
    }

    // Create the file if it does not exist
    if (!SPIFFS.exists(FilePath.c_str())) {
        File outFile = SPIFFS.open(FilePath.c_str(), FILE_WRITE);
        if (outFile) {
            outFile.print("[]"); // Initialize with an empty JSON array
            outFile.close();
        }
    }
}

bool FileManager::AppendData(WeatherData data)
{
    if (data.getTemperature() == 0 || data.getTimeStamp().empty())
    {
        Serial.println(String(data.getTemperature()));
        Serial.println(data.getTimeStamp().c_str());
        return false;
    }

    json jsonData;
    File inFile = SPIFFS.open(FilePath.c_str(), FILE_READ);

    if (inFile)
    {
        String fileContent = inFile.readString();
        if (!fileContent.isEmpty())
        {
            jsonData = json::parse(fileContent.c_str());
        }
        inFile.close();
    }

    json newData = {
        {"Temperature", data.getTemperature()},
        {"TimeStamp", data.getTimeStamp()}
    };

    jsonData.push_back(newData);

    File outFile = SPIFFS.open(FilePath.c_str(), FILE_WRITE);
    if (outFile)
    {
        outFile.print(jsonData.dump(4).c_str());
        outFile.close();
        return true;
    }

    Serial.println("Failed to open file");
    return false;
}

void FileManager::GetData(std::vector<WeatherData>& data)
{
    try
    {
        if (FilePath.empty())
        {
            return;
        }

        File inFile = SPIFFS.open(FilePath.c_str(), FILE_READ);

        if (!inFile)
        {
            // File does not exist, create it
            File outFile = SPIFFS.open(FilePath.c_str(), FILE_WRITE);
            if (outFile)
            {
                outFile.print("[]"); // Initialize with an empty JSON array
                outFile.close();
            }
            return;
        }

        String fileContent = inFile.readString();
        inFile.close();

        if (fileContent.isEmpty())
        {
            Serial.println("File is empty");
            return;
        }

        json jsonData = json::parse(fileContent.c_str());

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
    }
    catch(const std::exception& e)
    {
        Serial.println(e.what());
    }
}