#include "../include/invitation_system.hpp"
#include "../myTools/loggerTools/logger.hpp" // un module Logger que j'ai CREE pour suivre les evenements de la BDD

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

void InvitationSystem::loadInvitationsFromCSV(const std::string &filename){
	std::ifstream dbFile(filename);
	if(!dbFile.is_open()){
		Logger::logMessage("Could not open invitations.csv", "WARNING");
        std::cerr << "[Error while loading data] : could not open file:" << filename << std::endl;
        return;
	}else{
		Logger::logMessage("Loading invitations data from CSV", "INFO");

		std::string line;
		invitationsList.clear();
		while(std::getline(dbFile,line)){
			std::stringstream ss(line);
			std::string stringSenderID, stringReceiverID, status;
			std::getline(ss, stringSenderID, ',');
			std::getline(ss, stringReceiverID, ',');
			std::getline(ss, status, ',');
			
			if(stringSenderID.empty() || stringReceiverID.empty()){
				continue; // ignorer --> skipper si ligne corrompure/vide
			}
			// on verifie les dupliquees --> apres tests j'ai eu des comportements bizzares et des dupliquees
			bool dataAlreadyExists = false;
			for(const auto &inv : invitationsList){
				if(inv[0] == stringSenderID && inv[1] == stringReceiverID){
					dataAlreadyExists = true;
					break;
				}
			}
			if(!dataAlreadyExists){
				invitationsList.push_back({stringSenderID,stringReceiverID,status});
			}

		}
		Logger::logMessage("Loaded invitations data from CSV", "INFO");
		dbFile.close();
	}
}

void InvitationSystem::saveInvitationsToCSV(const std::string &filename){
	std::ofstream dbFile(filename);
	if(!dbFile.is_open()){
		Logger::logMessage("Could not open invitations.csv", "WARNING");
        std::cerr << "[Error while loading data] : could not open file:" << filename << std::endl;
    }else{
		Logger::logMessage("Saving invitations data to CSV", "INFO");
    	for(const auto &inv : invitationsList){
    		dbFile << inv[0] << "," << inv[1] << "," << inv[2] << "\n";
    	}
    	Logger::logMessage("Saved invitations data to CSV", "INFO");
    	dbFile.close();
    }
}



void InvitationSystem::sendInvitationToID(int senderID, int receiverID){
	std::string stringSenderID, stringReceiverID, status;
	stringSenderID = std::to_string(senderID);
	stringReceiverID = std::to_string(receiverID);

	for(const auto &inv : invitationsList){
		if(inv[0] == stringSenderID && inv[1] == stringReceiverID){
			if(inv[2] == "pending"){
				Logger::logMessage("Invitation from " + stringSenderID + " to " + stringReceiverID + " already pending. No new invitation sent.", "WARNING");
				std::cout << "[WARNING] Invitation already pending. No new invitation sent.\n";
				return;
			}else{
                Logger::logMessage("Invitation from " + stringSenderID + " to " + stringReceiverID + " was already " + inv[2], "WARNING");				
                std::cout << "[WARNING] Invitation already " << inv[2] << ".\n";
                return;				
			}
		}
	}
	status = "pending";
	invitationsList.push_back({stringSenderID,stringReceiverID,status});
	Logger::logMessage("Invitation sent from " + stringSenderID + " to " + stringReceiverID + " pending for acceptation", "DEBUG");
}


void InvitationSystem::accepteInvitation(int receiverID, int senderID){
	for(auto &inv : invitationsList){
		// en gros on regarde dans la liste des invitations si on a une sous-liste avec un status d'invitation pending
		// si tout de plus le receiverID et senderID match ceux donnes en params --> accepter l'invitation
		// en mettant 'pending' = 'accepted'
		if(std::stoi(inv[0]) == senderID  && std::stoi(inv[1]) == receiverID && inv[2] == "pending"){
			Logger::logMessage(inv[0] + " accepted invitation from " + inv[1], "INFO");
			inv[2] = "accepted";
			saveInvitationsToCSV("../database/invitations.csv"); // sauvegarder directemetn car sinon lors des tests
			return; 				// ca cree des choses imprevues et undefined behaviouur du genre duplicate... old entries etc
		}
	}
	Logger::logMessage("No pending invitation found", "WARNING");
	std::cout << "[WARNING] No pending invitation found.";
}


void InvitationSystem::declineInvitation(int receiverID, int senderID){
	for(auto &inv : invitationsList){
		// en gros on regarde dans la liste des invitations si on a une sous-liste avec un status d'invitation pending
		// si tout de plus le receiverID et senderID match ceux donnes en params --> accepter l'invitation
		// en mettant 'pending' = 'accepted'
		if(std::stoi(inv[0]) == senderID  && std::stoi(inv[1]) == receiverID && inv[2] == "pending"){
			Logger::logMessage(inv[0] + " declined invitation from " + inv[1], "INFO");
			inv[2] = "declined";
			saveInvitationsToCSV("../database/invitations.csv"); // sauvegarder directemetn car sinon lors des tests
			return; 				// ca cree des choses imprevues et undefined behaviouur du genre duplicate... old entries etc
		}
	}
	Logger::logMessage("No pending invitation found", "WARNING");
	std::cout << "[WARNING] No pending invitation found.";
}

void InvitationSystem::displayPlayerInvitations(int playerID){
	std::cout << "Displaying invitations to player " << playerID << std::endl;
	for(const auto &inv : invitationsList){
		if(std::stoi(inv[1]) == playerID){
			std::cout << "From " << inv[0] << ", - Invitation Status: " << inv[2] << std::endl;
		}
	}
}