#include "core/Log.h"
#include <iostream>
#include <string>

void Log::info(const std::string& message) {
    std::cout << "[INFO] " << message << std::endl;
}

void Log::warn(const std::string& message) {
    std::cout << "[WARN] " << message << std::endl;
}

void Log::error(const std::string& message) {
    std::cerr << "[ERROR] " << message << std::endl;
} 