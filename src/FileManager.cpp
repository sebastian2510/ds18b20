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
        Serial.println("File does not exist, creating new file"); // Debugging statement
        File outFile = SPIFFS.open(FilePath.c_str(), FILE_WRITE);
        if (outFile) {
            outFile.print("[]"); // Initialize with an empty JSON array
            outFile.close();
        }
    }
    else {
        Serial.println("File exists");
    }
}

bool FileManager::AppendData(WeatherData data)
{
    if (data.getTemperature() == 0 || data.getTimeStamp().empty())
    {
        Serial.println("Invalid data: Temperature is 0 or TimeStamp is empty");
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
    else
    {
        Serial.println("Failed to open file for reading");
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
        Serial.println("Data appended successfully");
        return true;
    }

    Serial.println("Failed to open file for writing");
    return false;
}

/**
 * @brief Retrieves weather data from a file and populates the provided vector.
 * 
 * This function attempts to read weather data from a file specified by the FilePath member.
 * If the file does not exist, it creates an empty JSON array in the file. If the file is empty
 * or the JSON data is empty, the function returns without modifying the vector.
 * 
 * @param data A reference to a vector of WeatherData objects that will be populated with the data read from the file.
 * 
 * @note This function uses the SPIFFS library to handle file operations and the nlohmann::json library for JSON parsing.
 * 
 * @exception std::exception If any exception occurs during file operations or JSON parsing, it is caught and the error message is printed to the Serial monitor.
 */
void FileManager::GetData(std::vector<WeatherData>& data)
{
    try
    {
        if (FilePath.empty())
        {
            Serial.println("File path is empty"); // Debugging statement
            return;
        }

        File inFile = SPIFFS.open(FilePath.c_str(), FILE_READ);

        if (!inFile)
        {
            // File does not exist, create it
            Serial.println("File does not exist, creating new file"); // Debugging statement
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
            Serial.println("JSON data is empty"); // Debugging statement
            return;
        }

        for (const auto& item : jsonData)
        {
            WeatherData weatherData;
            weatherData.setTemperature(item["Temperature"]);
            weatherData.setTimeStamp(item["TimeStamp"]);
            data.push_back(weatherData);
        }

        Serial.println("Elements in vector: " + String(data.size()));
    }
    catch(const std::exception& e)
    {
        Serial.println(e.what());
    }
}

/**
 * @brief Clears the data in the specified file by initializing it with an empty JSON array.
 *
 * This function opens the file specified by the FilePath member variable in write mode.
 * If the file is successfully opened, it writes an empty JSON array ("[]") to the file
 * and then closes the file.
 */
void FileManager::ClearData()
{
    File outFile = SPIFFS.open(FilePath.c_str(), FILE_WRITE);
    if (outFile)
    {
        outFile.print("[]"); // Initialize with an empty JSON array
        outFile.close();
    }
}

/**
 * @brief Converts a vector of WeatherData objects to a JSON array.
 * 
 * This function iterates through a vector of WeatherData objects and converts each
 * object into a JSON object containing the temperature and timestamp. The resulting
 * JSON objects are then added to a JSON array, which is returned.
 * 
 * @param data A reference to a vector of WeatherData objects to be converted.
 * @return json A JSON array containing the converted WeatherData objects.
 */
json FileManager::ConvertDataToJson(std::vector<WeatherData>& data)
{
    json jsonData;
    for (const auto& item : data)
    {
        json newData = {
            {"Temperature", item.getTemperature()},
            {"TimeStamp", item.getTimeStamp()}
        };
        jsonData.push_back(newData);
    }
    return jsonData;
}