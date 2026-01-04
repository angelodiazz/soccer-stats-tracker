#include "Input.h"
#include <iostream>
#include <limits>

namespace Input {

    int readInt(const std::string& prompt, int minValue, int maxValue) {
        while (true) {
            std::cout << prompt;

            int value{};
            if (!(std::cin >> value)) {
                std::cout << "Invalid input. Please enter a number.\n";
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                continue;
            }

            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // flush rest of line

            if (value < minValue || value > maxValue) {
                std::cout << "Please enter a value between " << minValue << " and " << maxValue << ".\n";
                continue;
            }

            return value;
        }
    }

    std::string readLine(const std::string& prompt, std::size_t minLen, std::size_t maxLen) {
        while (true) {
            std::cout << prompt;
            std::string s;
            std::getline(std::cin, s);

            if (s.size() < minLen) {
                std::cout << "Input is too short. Minimum length is " << minLen << ".\n";
                continue;
            }
            if (s.size() > maxLen) {
                std::cout << "Input is too long. Maximum length is " << maxLen << ".\n";
                continue;
            }
            return s;
        }
    }

} // namespace Input
