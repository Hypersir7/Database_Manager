#ifndef LOGGER_HPP
#define LOGGER_HPP

#include <string>

class Logger{
	private:
		static std::string logginFilename;
		static std::string getCurrentTime();
	public:
		static void logMessage(const std::string &message, const std::string &levelType); // levelType : INFO, LOG, WARNING
		static void clearLogFile(); // va vider le contenu du fichier qui log les evenemetns de notre BDD

		void setLogginFilename(const std::string &newLogginFilename);
        static const std::string &getLogginFilename();
};



#endif