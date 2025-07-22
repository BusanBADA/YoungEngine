#include "Config.h"
#include <fstream>
#include <sstream>
#include <iostream>
#include <algorithm>

bool Config::LoadFromFile(const std::string& filename)
{
    std::ifstream file(filename);
    if (!file.is_open()) return false;

    std::string line;
    std::string currentSection;

    while (std::getline(file, line)) {
        // 공백 제거 등 간단히 처리
        line = Trim(line);
        if (line.empty() || line[0] == ';' || line[0] == '#') continue; // 주석

        if (line.front() == '[' && line.back() == ']') {
            currentSection = line.substr(1, line.size() - 2);
        }
        else {
            auto pos = line.find('=');
            if (pos == std::string::npos) continue;

            std::string key = Trim(line.substr(0, pos));
            std::string value = Trim(line.substr(pos + 1));

            data_[currentSection + "." + key] = value;
        }
    }
    return true;
}

std::string Config::GetString(const std::string& sectionKey, const std::string& defaultValue) const
{
    auto it = data_.find(sectionKey);
    if (it != data_.end()) return it->second;
    return defaultValue;
}

int Config::GetInt(const std::string& sectionKey, int defaultValue) const
{
    auto it = data_.find(sectionKey);
    if (it != data_.end()) return std::stoi(it->second);
    return defaultValue;
}

bool Config::GetBool(const std::string& sectionKey, bool defaultValue) const
{
    auto it = data_.find(sectionKey);
    if (it != data_.end()) {
        std::string val = it->second;
        std::transform(val.begin(), val.end(), val.begin(), ::tolower);
        return (val == "true" || val == "1" || val == "yes");
    }
    return defaultValue;
}

std::string Config::Trim(const std::string& s)
{
    size_t start = s.find_first_not_of(" \t\r\n");
    size_t end = s.find_last_not_of(" \t\r\n");
    return (start == std::string::npos) ? "" : s.substr(start, end - start + 1);
}
