#include "FileManager.h"
#include <fstream>
#include <iostream>
#include <ctime>
std::string FileManager::FilePath = "/data.json";
bool FileManager::AppendData(std::string data)
{
    if (data.empty())
    {
        return false;
    }
    return true;
}

std::vector<Data> FileManager::GetData()
{
    if (FilePath.empty())
    {
        return std::vector<Data>();
    }

    std::vector<Data> data;
    return data;
}