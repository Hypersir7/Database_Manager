#include "../include/match.hpp"


Match::Match(int newGameID, std::string newGameMode, int newCreatorID, int newMaxPlayers,
 									std::string newStatus,std::string newCreationDate){
	gameID = newGameID;
	gameMode = newGameMode;
	creatorID = newCreatorID;
	maxPlayers = newMaxPlayers;
	status = newStatus;
	creationDate = newCreationDate;
}

