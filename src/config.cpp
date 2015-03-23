#include <assert.h>
#include <fstream>
#include "config.hpp"
#include "util.hpp"

bool Config::load(const std::string& path, const std::map<std::string, std::string>& defaultValues)
{
    std::ifstream fin(path.c_str());
    if (fin.bad()) return false;

    std::string line;
    while (getline(fin, line)) {
        std::size_t idx = line.find("=");
        if (idx != std::string::npos) {
            std::string key = util::trim(line.substr(0, idx));
            std::string value = util::trim(line.substr(idx+1));
            db[key] = value;
        }
    }

    load(defaultValues, false);
    return true;
}

bool Config::load(const std::vector<std::string>& paths, const std::map<std::string, std::string>& defaultValues)
{
    bool flag = false;
    for (unsigned i = 0; i < paths.size(); i++) {
        if (!load(paths[i]))
            continue;
        flag = true;
    }
    load(defaultValues, false);
    return flag;
}

bool Config::load(const std::map<std::string, std::string>& data, bool overwrite)
{
    for (std::map<std::string, std::string>::const_iterator iter = data.begin(); iter != data.end(); iter++) {
        if (overwrite || db.find(iter->first) == db.end())
            db[iter->first] = iter->second;
    }
    return true;
}

bool Config::save(const std::string& path)
{
    std::ofstream fout(path.c_str());
    if (fout.bad()) return false;
    for (std::map<std::string, std::string>::iterator iter = db.begin(); iter != db.end(); iter++) {
        fout << iter->first << " = " << iter->second << "\n";
    }
    return true;
}

std::string Config::getStr(const std::string& key)
{
    std::map<std::string, std::string>::iterator iter = db.find(key);
    assert(iter != db.end());
    return iter->second;
}

std::string Config::getStr(const std::string& key, const std::string& defaultValue)
{
    std::map<std::string, std::string>::iterator iter = db.find(key);
    return iter != db.end() ? iter->second : defaultValue;
}

void Config::setStr(const std::string& key, const std::string& value)
{
    db[key] = value;
}

int Config::getInt(const std::string& key)
{
    std::map<std::string, std::string>::iterator iter = db.find(key);
    assert(iter != db.end());
    return util::atoi(iter->second);
}

int Config::getInt(const std::string& key, int defaultValue)
{
    std::map<std::string, std::string>::iterator iter = db.find(key);
    return iter != db.end() ? util::atoi(iter->second) : defaultValue;
}

void Config::setInt(const std::string& key, int value)
{
    db[key] = util::itoa(value);
}
