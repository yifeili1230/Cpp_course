#pragma once

#include <string>

namespace lecture01 {

// Declarations only: this header tells callers the functions exist.
void MakeItSunny();
void MakeItRain();

std::string BuildMessage(const std::string& weather);

}  // namespace lecture01
