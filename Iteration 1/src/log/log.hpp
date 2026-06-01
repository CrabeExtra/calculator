#include <iostream>
#include <fstream>

class Log {
    public:
        static void info(const std::string& message) {
            trimLogFile("info.log");
            std::ofstream log("info.log", std::ios::app);
            std::cout << "[INFO] " << message << std::endl; // log
            log << "[INFO] " << message << std::endl; // log to file
        }

        static void warning(const std::string& message) {
            trimLogFile("warning.log");
            std::ofstream log("warning.log", std::ios::app);
            std::cout << "[WARNING] " << message << std::endl; // log
            log << "[WARNING] " << message << std::endl; // log to file
        }

        static void error(const std::string& message) {
            trimLogFile("error.log");
            std::ofstream log("error.log", std::ios::app);
            std::cout << "[ERROR] " << message << std::endl; // log
            log << "[ERROR] " << message << std::endl; // log to file
        }

        static void trimLogFile(const std::string& filename);
};