#pragma once
#include <string>
#include <unordered_map>

class Config {
public:
    bool LoadFromFile(const std::string& filename);

    std::string GetString(const std::string& sectionKey, const std::string& defaultValue = "") const;

    int GetInt(const std::string& sectionKey, int defaultValue = 0) const;

    bool GetBool(const std::string& sectionKey, bool defaultValue = false) const;

private:
    std::unordered_map<std::string, std::string> data_;

    static std::string Trim(const std::string& s);
};
