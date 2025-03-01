#include "logger.hpp"
#include <fstream>
#include <ctime>
#include <iostream>
#include <filesystem>

std::string Logger::logginFilename = "../logs/DB_events.log";

std::string Logger::getCurrentTime(){
	std::time_t current_time  = std::time(nullptr);
	char buffer[100];
	std::strftime(buffer, sizeof(buffer), "%d/%m/%Y at %H:%M:%S", std::localtime(&current_time));
	return buffer;
}



void Logger::logMessage(const std::string &message, const std::string &levelType){
	std::string filename = Logger::getLogginFilename();

	// creation du fodler logs avant de faire quoi que cela soit
	std::filesystem::path logFilePath(filename);
	std::filesystem::path logDir = logFilePath.parent_path();
	if(!std::filesystem::exists(logDir)){
		std::filesystem::create_directories(logDir);
	}
	// LOGGIN
	std::ofstream logFile(filename, std::ios::app);

	if(!logFile.is_open()){
		std::cerr << "[Error] : could not open file:" << filename << std::endl;
	}else{
		logFile <<"[" << getCurrentTime() << "] [" << levelType << "]" << " " << message << "\n";
	}
	logFile.close();
}


void Logger::clearLogFile(){
	std::string filename = Logger::getLogginFilename();
	std::ofstream logFile(filename, std::ios::trunc); // va override le fichir donc le vider en mettant a 0 bytes
	if(!logFile.is_open()){
		Logger::logMessage("Could not open Database Events file to clear the log", "[LOG]");
	}
}


const std::string &Logger::getLogginFilename(){
	return Logger::logginFilename;
}

void Logger::setLogginFilename(const std::string &newLogginFilename){
	Logger::logginFilename = newLogginFilename;	
}