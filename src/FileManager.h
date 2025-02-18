#include <string>
#include <Data.h>
#include <vector>
class FileManager {
public:
    static std::string FilePath;
    static bool AppendData(Data data);
    static void GetData(std::vector<Data>& data);
};