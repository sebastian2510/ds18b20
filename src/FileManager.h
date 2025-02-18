#include <string>
#include <TestWeatherData.h>
#include <vector>
class FileManager {
public:
    static std::string FilePath;
    static bool AppendData(TestWeatherData data);
    static void GetData(std::vector<TestWeatherData>& data);
};