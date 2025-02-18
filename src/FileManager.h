#include <string>
#include <WeatherData.h>
#include <vector>
class FileManager {
public:
    static std::string FilePath;
    static bool AppendData(WeatherData data);
    static void GetData(std::vector<WeatherData>& data);
};