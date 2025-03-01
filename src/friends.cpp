#include "../include/friends.hpp"
#include "../myTools/loggerTools/logger.hpp" // un module Logger que j'ai CREE pour suivre les evenements de la BDD

#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>


void Friends::loadFriendsFromCSV(const std::string &filename){
	std::ifstream dbFile(filename);
	if(!dbFile.is_open()){
		Logger::logMessage("Could not open friends.csv", "WARNING");
        std::cerr << "[Error while loading data] : could not open file:" << filename << std::endl;
        return;
	}else{
		Logger::logMessage("Loading friends data from CSV", "INFO");

		std::string line;

		while(std::getline(dbFile,line)){
			std::stringstream ss(line);
			std::string stringPlayerID, stringAllFriends;
			std::getline(ss, stringPlayerID, ';');
			std::getline(ss, stringAllFriends, ';');
			
			if(stringPlayerID.empty() || stringAllFriends.empty()){
				Logger::logMessage("Skipping empty/corrupted line, content : " + line, "WARNING");
				continue; // ignorer --> skipper si ligne corrompure/vide
			}

			//conversion en INT des IDS
			int playerID = std::stoi(stringPlayerID);
			std::stringstream friendsStream(stringAllFriends);

			// traitement des amis
			std::string stringFriendID;
			while(std::getline(friendsStream, stringFriendID, ',')){
				if(!stringFriendID.empty()){
					int friendID = std::stoi(stringFriendID);
					friendsIncidenceMatrix[playerID][friendID] = 2; // le 2 --> signife amis accepte (genre ID et ID sont acceptes)
					friendsIncidenceMatrix[friendID][playerID] = 2; // " " AMITIEE DANS LES 2 SENS
				}
			}
		}
		Logger::logMessage("Loaded friends data from CSV", "INFO");
		dbFile.close();
	}
}



void Friends::saveFriendsToCSV(const std::string &filename){
	std::ofstream dbFile(filename);
	if(!dbFile.is_open()){
		Logger::logMessage("Could not open friends.csv", "ERROR");
        std::cerr << "[Error while loading data] : could not open file:" << filename << std::endl;
        return;
	}else{
		Logger::logMessage("Saving friends data to CSV", "INFO");
		for(const auto &player : friendsIncidenceMatrix){
			dbFile << player.first << ";";
			bool firstAction = true; // ecrire la cle --> playerID
			for(const auto &friendsData : player.second){
				if(friendsData.second == 2){ // c'est a dire sont amis car 2 je l'ai definie comme etant amis(accepte)
					if(!firstAction){
						dbFile << ",";
					}
					dbFile << friendsData.first;
					firstAction = false;
				}
			}
			dbFile << "\n" ; 
		}
		Logger::logMessage("Saved friends data to CSV", "INFO");
		dbFile.close();
	}
}


void Friends::addFriend(int playerID, int friendID){
	std::string stringPlayerID = std::to_string(playerID);
	std::string stringFriendID = std::to_string(friendID);

	if(friendsIncidenceMatrix[playerID][friendID] == 2){
		std::string friendshipExistsWarning = "Player " + stringPlayerID + " tried to add an existing friend " + stringFriendID;
		Logger::logMessage(friendshipExistsWarning, "WARNING");
		return;
	}

	friendsIncidenceMatrix[playerID][friendID] = 1; // pending request --> en attente de l'acceptance \
	friendsIncidenceMatrix[friendID][playerID] = 1; // pending request --> en attente de l'acceptance /
	std::string sentFriendshipRequest = "Player " + stringPlayerID + " tried to add an existing friend " + stringFriendID;
	Logger::logMessage(sentFriendshipRequest, "INFO");
}

void Friends::removeFriend(int playerID, int friendID){
	std::string stringPlayerID = std::to_string(playerID);
	std::string stringFriendID = std::to_string(friendID);

	if(friendsIncidenceMatrix[playerID][friendID] == 2){
		friendsIncidenceMatrix[playerID][friendID] = 0;
		friendsIncidenceMatrix[friendID][playerID] = 0;
		Logger::logMessage("Removed Friendship between " + stringPlayerID + " and " + stringFriendID, "INFO");
	}else{
		Logger::logMessage("No Friendship between " + stringPlayerID + " and " + stringFriendID, "WARNING");
	}
}

void Friends::accepteFriend(int playerID, int friendID){
	std::string stringPlayerID = std::to_string(playerID);
	std::string stringFriendID = std::to_string(friendID);
	std::string confirmedFriendship = "Player " + stringPlayerID + " and player " + stringFriendID + " are confirmed friends now";
	if(friendsIncidenceMatrix[playerID][friendID] == 1){ // donc friendship pending
		friendsIncidenceMatrix[playerID][friendID] = 2;
		friendsIncidenceMatrix[friendID][playerID] = 2;
		Logger::logMessage(confirmedFriendship, "INFO");
	}else{
		std::string warningNoPending = "No pending friendship request found between " + stringPlayerID + " and " + stringFriendID;
		Logger::logMessage(warningNoPending, "WARNING");		
	}
}



bool Friends::isAFriend(int playerID, int friendID){
	return friendsIncidenceMatrix[playerID][friendID] == 2;
}


void Friends::displayFriends(int playerID){
	std::vector<int> friendsList = getFriends(playerID);
	for(const auto & friendID : friendsList){
		std::cout << friendID << " " ;
	}
	std::cout << std::endl;
}


std::vector<int> Friends::getFriends(int playerID){
	std::vector<int> friendsList;
	for(const auto &friendsData : friendsIncidenceMatrix[playerID]){
		if(friendsData.second == 2){
			friendsList.push_back(friendsData.first);
		}
	}
	return friendsList;
}




