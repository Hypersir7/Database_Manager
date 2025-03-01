#include "../include/database_manager.hpp"
#include "../include/match.hpp"
#include "../myTools/loggerTools/logger.hpp" // un module Logger que j'ai CREE pour suivre les evenements de la BDD
#include <cctype>
#include <cstdio>
#include <string>
#include <vector>
#include <fstream>
#include <iostream>
#include <sstream>

DatabaseManager::DatabaseManager(){
	displayHelp();
}


std::vector<ClientData> DatabaseManager::loadClientsData(){
	std::vector<ClientData> clientData;
	const std::string filename = getClientDataFilename();
	std::ifstream dbFile(filename);
	if(!dbFile.is_open()){
		Logger::logMessage("Could not open clientData.csv", "ERROR");
        std::cerr << "[Error while loading data] : could not open file:" << filename << std::endl;
	}else{

		if(fileIsEmpty(dbFile)){ // methode auxilliaire --> helper function
			Logger::logMessage("ClientData.csv is empty", "WARNING");
			std::cerr << "[Warning] file is empty!(could crash program!)" << std::endl;
			return clientData;
		}

		Logger::logMessage("Loading client data from CSV", "INFO");

		std::string line;
		while(std::getline(dbFile, line)){
			std::stringstream ss(line);
			std::string stringID, username, ipAddress, emailAddress, password;

			std::getline(ss, stringID, ',');
			std::getline(ss, username, ',');
			std::getline(ss, ipAddress, ',');
			std::getline(ss, emailAddress, ',');
			std::getline(ss, password, ',');

			// verification: si la ligne est vide sino mon programm lance des 'std::stoi' crashes!
			if(stringID.empty() || !isNumber(stringID)){ // ou si la premiere entere(ID) n'est pas un chiffre
				continue; // skipper cette ligne probelmatique sans data ou data corrumpues!
			}
			int uniqueID = std::stoi(stringID); // donc convertir en int <==> isNumber renvoie true
			ClientData client(username, ipAddress, emailAddress, password);
			client.setId(uniqueID);
			clientData.push_back(client);
		}

		Logger::logMessage("Loaded client data from CSV", "INFO");
		dbFile.close();
	}

	return clientData;
}

void DatabaseManager::saveClientsData(const std::vector<ClientData> &clientsData){
	const std::string filename = getClientDataFilename();
	std::ofstream dbFile(filename);
	if(!dbFile.is_open()){
		Logger::logMessage("Could not open clientData.csv", "ERROR");
        std::cerr << "[Error while loading data] : could not open file:" << filename << std::endl;
	}else{
		Logger::logMessage("Saving client data to CSV", "INFO");
		for(const auto &client : clientsData){
			dbFile << client.buildCSVformat() << std::endl;
		}
		Logger::logMessage("Saved client data to CSV", "INFO");
		dbFile.close();
		// DEBUG / LOG
		//std::cout << "[LOG] Client data sucessfully saved to database: " << filename << std::endl;
	}
}


bool DatabaseManager::doesIpAddressExists(const std::string &ipAddress){
    std::vector <ClientData> clients = loadClientsData();
    for(const auto & client: clients){
        if(client.getIpAddress() == ipAddress){
            return true;
        }
    }
    return false; // alors on est sorti de la boucle sans trouver l'IP
}



// Mes fonctions auxilliarires pour la gestion et traitement des donnees

bool DatabaseManager::fileIsEmpty(std::ifstream &dbFile){
	return dbFile.peek() == std::fstream::traits_type::eof();
}

bool DatabaseManager::isNumber(const std::string &myString){
	if(myString.empty()) return false;
	for(char c : myString){
		if(!isdigit(c)) return false;
	}
	return true;
}



std::vector<Match> DatabaseManager::loadMatchData(){
	const std::string filename = getMatchDataFilename();
	std::vector<Match> matches;
	std::ifstream dbFile(filename);

	if(!dbFile.is_open()){
		Logger::logMessage("Could not open match.csv", "ERROR");
		std::cerr << "[Error] Could not open file: " << filename << std::endl;
		return matches;
	}else{
		Logger::logMessage("Loading match data from CSV", "INFO");
		std::string line;
		while(std::getline(dbFile, line)){
			std::stringstream ss(line);
			std::string gameId, creatorID, gameMode, maxPlayers, status, creationDate;
			std::getline(ss, gameId, ',');
			std::getline(ss, creatorID, ',');
			std::getline(ss, gameMode, ',');
			std::getline(ss, maxPlayers, ',');
			std::getline(ss, status, ',');
			std::getline(ss, creationDate, ',');

			if(gameId.empty() || !isNumber(gameId)){
				continue; // skipper cette ligne probelmatique sans data ou data corrumpues!
			}
			int intGameID = std::stoi(gameId);

			matches.push_back(Match(intGameID,gameMode, std::stoi(creatorID), std::stoi(maxPlayers), status, creationDate));
		}
		Logger::logMessage("Loaded match data to CSV", "INFO");
		dbFile.close();
		return matches;
	}
}


void DatabaseManager::saveMatchData(const std::vector<Match> &matches){
	const std::string filename = getMatchDataFilename();
	std::ofstream dbFile(filename);
	if(!dbFile.is_open()){
		Logger::logMessage("Could not open match.csv", "ERROR");
		std::cerr << "[Error] Could not open file: " << filename << std::endl;
	}else{
		Logger::logMessage("Saving match data to CSV", "INFO");
		for(const auto &match: matches){
			dbFile << match.gameID << "," << match.creatorID << "," << match.gameMode
			 << "," << match.maxPlayers << "," << match.status << "," << match.creationDate << "\n";
		}
		Logger::logMessage("Saved match data to CSV", "INFO");
		dbFile.close();
	}
}

void DatabaseManager::createMatch(int creatorID, std::string gameMode, int maxPlayers){
	// TO SEE WHAT TO DO WITH THAT
}





void DatabaseManager::displayHelp(){
	// TO SEE WHAT TO DO WITH THAT AT THE END OF BDD
}


// GESTION DES FICHIERS
void DatabaseManager::setClientDataFilename(const std::string &newClientDataFilename){
    clientDataFilename = newClientDataFilename;
}

// declaration du fichier static en aprtage par touotes les instances de la classe
std::string DatabaseManager::clientDataFilename = "../database/clientData.csv";
const std::string& DatabaseManager::getClientDataFilename(){
    return clientDataFilename;
}



void DatabaseManager::setMatchDataFilename(const std::string &newMatchDataFilename){
	matchDataFilename = newMatchDataFilename;
}

std::string DatabaseManager::matchDataFilename = "../database/match.csv";
const std::string& DatabaseManager::getMatchDataFilename(){
	return clientDataFilename;
}

