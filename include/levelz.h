#include <string>
#include <vector>
#include <fstream>
#include <cstdio>
#include <unordered_map>

#include "levelz/coordinate.h"
#include "levelz/block.h"
#include "levelz/level.h"

namespace LevelZ {

    /**
     * Marks the end of the header section
     */
    const std::string HEADER_END = "---";

    /**
     * Marks the end of the file
     */
    const std::string END = "end";

}

namespace {

    static std::vector<std::string> lines(const std::string& file) {
        std::ifstream infile(file);
        std::vector<std::string> lines;

        std::string line;
        while (std::getline(infile, line)) {
            lines.push_back(line);
        }

        return lines;
    }

    static std::vector<std::vector<std::string>> split(const std::vector<std::string>& file) {
        int index = 0;
        for (int i = 0; i < file.size(); i++) {
            if (file[i] == LevelZ::HEADER_END) {
                index = i;
                break;
            }
        }

        std::vector<std::string> header(file.begin(), file.begin() + index);
        std::vector<std::string> body(file.begin() + index + 1, file.end());

        return {header, body};
    }

    static std::unordered_map<std::string, std::string> readHeaders(const std::vector<std::string>& headers) {
        std::unordered_map<std::string, std::string> map;

        for (const std::string& header : headers) {
            if (header[0] != '@') throw (header);
            
            int i = header.find(' ');
            std::string key = header.substr(1, i);
            std::string value = header.substr(i);

            map[key] = value;
        }

        return map;
    }

}