#include "logger.hpp"
#include <iostream>


using namespace std;

int main(){
	Logger::logMessage("Starting the program","INFO");
	Logger::logMessage("Connection sucessfull with the DATABSE","DEBUG");
	Logger::logMessage("Tried to read from empty file could crash program","WARNING");
	Logger::logMessage("Program crashing, getting unresponsive","CRITICAL");
	Logger::logMessage("Program just crashed","ERROR");
	cout << " DONE " << endl;
}