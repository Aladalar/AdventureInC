#include "utilities/logger.h"
#include <iostream>
#include <ctime>

void Logger::log(const std::string& message){
    std::cout << "[" << getTime() << "] " << "[LOG]: " << message << std::endl;  
}

void Logger::info(const std::string& message){
    std::cout << getTime() <<  "\033[36m" << "[INFO]" << "\033[0m"<< ": " << message << std::endl;  
}

void Logger::warn(const std::string& message){
    std::cout << "[" << getTime() << "] " <<  "\033[93m" << "[WARN]" << "\033[0m"<< ": " << message << std::endl;  
}

void Logger::error(const std::string& message){
    std::cout << "[" << getTime() << "] " <<  "\033[91m" << "[ERROR]" << "\033[0m"<< ": " << message << std::endl;  
}

std::string Logger::getTime(){
    std::time_t rawTimeResult = std::time(nullptr);
    std::tm* timeResult = std::localtime(&rawTimeResult);
    char timeBuffer[25];
    std::strftime(timeBuffer, sizeof(timeBuffer), "[%d/%m/%Y/%H:%M:%S]", timeResult);
    return timeBuffer;
}
