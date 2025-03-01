#ifndef MATCH_HPP
#define MATCH_HPP

#include <string>

// DONNEES relatives a une partie (match) 

struct Match{ // une simple structure: mais a voir ce soir si on l'adapte ou pas si c'est necessaire
	int gameID;
	std::string gameMode;
	int creatorID;
	int maxPlayers;
	std::string status; // genre : en cours / termine / pending? // [to delete]
	std::string creationDate;

	Match(int newGameID, std::string newGameMode, int newCreatorID, int newMaxPlayers,
 									std::string newStatus,std::string newCreationDate);
};

#endif

	