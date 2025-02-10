#include <string>
#include <Data.h>
#include <vector>
class FileManager {
public:
    static std::string FilePath;
    static bool AppendData(std::string data);
    static std::vector<Data> GetData();
};