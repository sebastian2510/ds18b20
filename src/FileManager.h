#include <string>
#include <Models/WeatherData.h>
#include <vector>
#include <nlohmann/json.hpp>

using json = nlohmann::json;

class FileManager {
public:
    static std::string FilePath;
    static bool AppendData(WeatherData data);
    static void GetData(std::vector<WeatherData>& data);
    static void setup();
    static void ClearData();
    static json ConvertDataToJson(std::vector<WeatherData>& data);
};