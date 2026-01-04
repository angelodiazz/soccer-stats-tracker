#ifndef SOCCER_STATS_TRACKER_INPUT_H
#define SOCCER_STATS_TRACKER_INPUT_H
#pragma once
#include <string>


namespace Input {
    int readInt(const std::string& prompt, int minValue, int maxValue);
    std::string readLine(const std::string& prompt,
                               std::size_t minLen = 1,
                               std::size_t maxLen = 60);
}



#endif //SOCCER_STATS_TRACKER_INPUT_H