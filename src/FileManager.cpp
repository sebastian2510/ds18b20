#include <fstream>
#include <iostream>
#include <ctime>
#include <WeatherData.h>
#include <FileManager.h>
#include <nlohmann/json.hpp> 
#include <nlohmann/json_fwd.hpp>
#include <include/nlohmann/json_fwd.hpp>
#include <include/nlohmann/json.hpp>

using namespace std;
using json = nlohmann::json;

std::string FileManager::FilePath = "/data.json";

bool FileManager::AppendData(WeatherData data)
{
    if (data.Temperature == 0 || data.TimeStamp.empty())
    {
        return false;
    }

    json jsonData;
    ifstream File(FilePath);

    if (File.is_open())
    {
        File >> jsonData;
        File.close();
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

    ifstream File(FilePath);

    if (!File.is_open())
    {
        return;
    }

    json jsonData;
    File >> jsonData;

    if (jsonData.empty())
    {
        return;
    }

    for (const auto& item : jsonData)
    {
        data.emplace_back(item.dump());
    }

    File.close();
}