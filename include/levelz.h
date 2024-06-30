#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <cstdio>
#include <unordered_map>
#include <algorithm>
#include <regex>

#include "levelz/coordinate.h"
#include "levelz/block.h"
#include "levelz/level.h"

using namespace LevelZ;

// Internal

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

    static std::vector<std::string> splitString(const std::string& str, const std::string& delimiter) {
        std::string str0 = str;

        std::vector<std::string> parts;
        size_t pos = 0;
        std::string token;
        while ((pos = str0.find(delimiter)) != std::string::npos) {
            token = str0.substr(0, pos);
            parts.push_back(token);
            str0.erase(0, pos + delimiter.length());
        }
        parts.push_back(str0);
        return parts;
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

    static std::string trim(const std::string& str) {
        size_t first = str.find_first_not_of(' ');
        if (std::string::npos == first) return str;

        size_t last = str.find_last_not_of(' ');
        return str.substr(first, (last - first + 1));
    }

    static std::unordered_map<std::string, std::string> readHeaders(const std::vector<std::string>& headers) {
        std::unordered_map<std::string, std::string> map;

        for (const std::string& header : headers) {
            if (header[0] != '@') throw (header);
            
            int i = header.find(' ');
            std::string key = trim(header.substr(1, i));
            std::string value = trim(header.substr(i));

            map[key] = value;
        }

        return map;
    }

    static std::vector<Coordinate2D> read2DPoints(const std::string& input) {
        std::vector<Coordinate2D> points;

        const std::regex matrix("[\\[\\]()]");
        const std::vector<std::string> split = splitString(input, "*");

        for (std::string s0 : split) {
            if (s0.empty()) continue;

            if (s0.rfind('(', 0) == 0 && s0.rfind(']') == s0.size() - 1) {
                s0 = std::regex_replace(s0, matrix, "");

                unsigned int i = 0;
                size_t cpos = 0;
                std::string s1;

                int x1, x2, y1, y2;
                double cx, cy;

                while ((cpos = s0.find(',')) != std::string::npos) {
                    s1 = s0.substr(0, cpos);
                    switch (i) {
                        case 0: x1 = std::stoi(s1); break;
                        case 1: x2 = std::stoi(s1); break;
                        case 2: y1 = std::stoi(s1); break;
                        case 3: y2 = std::stoi(s1); break;
                        case 4: cx = std::stod(s1); break;
                        case 5: cy = std::stod(s1); break;
                    }
                    
                    s0.erase(0, cpos + 1);
                    i++;
                }

                for (int x = x1; x < x2; x++)
                    for (int y = y1; y < y2; y++)
                        points.push_back(Coordinate2D(cx + x, cy + y));
            } else
                points.push_back(Coordinate2D::from_string(s0));
        }

        return points;
    }

    static std::vector<Coordinate3D> read3DPoints(const std::string& input) {
        std::vector<Coordinate3D> points;

        const std::regex matrix("[\\[\\]()]");
        const std::vector<std::string> split = splitString(input, "*");

        for (std::string s0 : split) {
            if (s0.empty()) continue;

            if (s0.rfind('(', 0) == 0 && s0.rfind(']') == s0.size() - 1) {
                s0 = std::regex_replace(s0, matrix, "");

                unsigned int i = 0;
                size_t cpos = 0;
                std::string s1;

                int x1, x2, y1, y2, z1, z2;
                double cx, cy, cz;

                while ((cpos = s0.find(',')) != std::string::npos) {
                    s1 = s0.substr(0, cpos);
                    switch (i) {
                        case 0: x1 = std::stoi(s1); break;
                        case 1: x2 = std::stoi(s1); break;
                        case 2: y1 = std::stoi(s1); break;
                        case 3: y2 = std::stoi(s1); break;
                        case 4: z1 = std::stoi(s1); break;
                        case 5: z2 = std::stoi(s1); break;
                        case 6: cx = std::stod(s1); break;
                        case 7: cy = std::stod(s1); break;
                        case 8: cz = std::stod(s1); break;
                    }
                    
                    s0.erase(0, cpos + 1);
                    i++;
                }

                for (int x = x1; x < x2; x++)
                    for (int y = y1; y < y2; y++)
                        for (int z = z1; z < z2; z++)
                            points.push_back(Coordinate3D(cx + x, cy + y, cz + z));
            } else
                points.push_back(Coordinate3D::from_string(s0));
        }

        return points;
    }

    static Block readBlock(std::string& input) {
        input.erase(std::remove(input.begin(), input.end(), ' '), input.end());
        input.erase(std::remove(input.begin(), input.end(), '>'), input.end());

        size_t pos = input.find('<');
        if (pos == std::string::npos)
            return Block(input);

        std::string name = input.substr(0, pos);
        std::string data = input.substr(pos + 1);

        std::unordered_map<std::string, std::string> properties;
        size_t cpos = 0;
        std::string s0, s1;
        while ((cpos = data.find(',')) != std::string::npos) {
            s0 = data.substr(0, cpos);
            data.erase(0, cpos + 1);

            if ((cpos = s0.find('=')) != std::string::npos) {
                s1 = s0.substr(0, cpos);
                s0.erase(0, cpos + 1);
                properties[s1] = s0;
            }
        }

        return Block(name, properties);
    }

    static std::pair<Block, std::vector<Coordinate2D>> read2DLine(std::string& line) {
        line.erase(std::remove(line.begin(), line.end(), ' '), line.end());

        size_t pos = line.find(':');
        std::string block = line.substr(0, pos);
        std::string points = line.substr(pos + 1);

        return {readBlock(block), read2DPoints(points)};
    }

    static std::pair<Block, std::vector<Coordinate3D>> read3DLine(std::string& line) {
        line.erase(std::remove(line.begin(), line.end(), ' '));
        
        size_t pos = line.find(':');
        std::string block = line.substr(0, pos);
        std::string points = line.substr(pos + 1);

        return {readBlock(block), read3DPoints(points)};
    }

}

// Implementation

namespace LevelZ {

    /**
     * Reads a level from the specified lines.
     * @param lines The contents to read the level from.
     * @return The level read from the lines.
     */
    Level parseLines(const std::vector<std::string>& lines) {
        std::vector<std::vector<std::string>> parts = split(lines);
        std::unordered_map<std::string, std::string> headers = readHeaders(parts[0]);

        bool is2D = headers.at("type") == "2";

        if (headers.find("spawn") == headers.end())
            headers["spawn"] = is2D ? "[0, 0]" : "[0, 0, 0]";

        if (is2D && headers.find("scroll") == headers.end())
            headers["scroll"] = "none";

        std::vector<LevelObject> blocks;
        for (std::string& line : parts[1]) {
            if (line[0] == '#') continue;
            if (line == END) break;

            int ci = line.find('#');
            std::string line0 = ci == std::string::npos ? line : line.substr(0, ci);
            line0.erase(line0.find_last_not_of(" \n\r\t") + 1);

            if (is2D) {
                std::pair<Block, std::vector<Coordinate2D>> pair = read2DLine(line0);
                for (Coordinate2D& point : pair.second)
                    blocks.push_back(LevelObject(pair.first, point));
            } else {
                std::pair<Block, std::vector<Coordinate3D>> pair = read3DLine(line0);
                for (Coordinate3D& point : pair.second)
                    blocks.push_back(LevelObject(pair.first, point));
            }
        }

        if (is2D)
            return Level2D(headers, blocks);
        else
            return Level3D(headers, blocks);
    }

        /**
     * Reads a level from the specified string.
     * @param string The contents to read the level from.
     * @return The level read from the contents.
     */
    Level parseContents(const std::string& string) {
        std::vector<std::string> lines;
        std::istringstream stream(string);

        while (stream.good()) {
            std::string line;
            std::getline(stream, line);
            lines.push_back(line);
        }

        return parseLines(lines);
    }

    /**
     * Parses a level from the specified file.
     * @param file The file to read the level from.
     * @return The level read from the file.
     */
    Level parseFile(const std::string& file) {
        std::vector<std::string> lines;
        std::fstream stream(file);

        std::string line;
        while (std::getline(stream, line)) {
            lines.push_back(line);
        }

        return parseLines(lines);
    }

}