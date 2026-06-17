#include "lecture01/tools.hpp"

#include <cctype>
#include <iostream>
#include <string>

namespace {

// Anonymous namespace makes helper functions visible only inside this .cpp file.
std::string NormalizeWeather(std::string weather) {
    if (weather.empty()) {
        return "unknown";
    }

    weather.front() = static_cast<char>(
        std::toupper(static_cast<unsigned char>(weather.front())));
    return weather;
}

}  // namespace

namespace lecture01 {

void MakeItSunny() {
    // Public API: build a message and print it.
    std::cout << BuildMessage("sunny") << '\n';
}

void MakeItRain() {
    // Same public API, different argument.
    std::cout << BuildMessage("rainy") << '\n';
}

std::string BuildMessage(const std::string& weather) {
    // This function is defined in the .cpp and declared in the header.
    return "Weather tool says: " + NormalizeWeather(weather);
}

}  // namespace lecture01
