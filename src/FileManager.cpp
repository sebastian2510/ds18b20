#include "FileManager.h"
#include <fstream>
#include <iostream>
#include <ctime>
#include <nlohmann/json.hpp> 
#include <nlohmann/json_fwd.hpp>
#include <include/nlohmann/json_fwd.hpp>

using namespace std;
using json = nlohmann::json;

std::string FileManager::FilePath = "/data.json";

bool FileManager::AppendData(std::string data)
{
    if (data.empty())
    {
        return false;
    }
    return true;
}

void FileManager::GetData(std::vector<Data>& data)
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