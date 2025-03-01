#ifndef DATABASE_MANAGER_HPP
#define DATABASE_MANAGER_HPP

#include <vector>
#include <string>
#include <fstream>

#include "client_data.hpp"
#include "match.hpp"

// ===================== DatabaseManager =====================
/*
    CETTE CLASSE FAIT LE LIEN INTERMEDIAIRE ENTRE NOTRE JEU ET LA BASE DE DONNES
    1) S'OCCUPE DES OPERATIONS INPUT/OUTPUT VERS/DEPUIS LES FICHIER DU DATABASE
	2) S'OCCUPE DES OPERATIONS SUR LE LEADERBOARD
    3) EN ANALOGIQUE AVEC L'OS , ELLE VA SEPERAER LA LOGIQUE ET LE STOCKAGE dans la BDD
    4) [IMPORTANT] : CLASSE UNCOMPLETE ENCORE --> certaine functionalites suspendues jusqu'a discussion ce soir
*/

class DatabaseManager{
	private:
		static std::string clientDataFilename;
		static std::string matchDataFilename;
		static bool fileIsEmpty(std::ifstream &dbFile);
		static bool isNumber(const std::string &myString);
	public:
		DatabaseManager();
		// Gestion des joeurs(donnees generales)
		static std::vector<ClientData> loadClientsData();
		static void saveClientsData(const std::vector<ClientData> &clientsData);

		void displayHelp();

		// METHODES de recherche
		static bool doesIpAddressExists(const std::string &ipAddress);

		//Gestion des matchs
		std::vector<Match> loadMatchData(); // deja faite qmm

		// METHODES EN COURS DE DEV --> DEV SUSPENDU JUSQU'A DISCUSSION CE SOIR
		void saveMatchData(const std::vector<Match> &matches); // deja fait qmm
		void createMatch(int creatorID, std::string gameMode, int maxPlayers); // pas faite
		void updateMatchStatus(int gameID, const std::string &newStatus); // pas faite

		//Gestion des donnees joeurs dans un match
		void addPlayerToMatch(int gameID, int playerID);
		void updateMatchScore(int gameID, int playerID, int newScore, int rank);

		// Communication avec leaderboard pour y mettre a jours les donnees
		void updateLeaderboard(); // non faite encore

		// GESTION DES FICHIERS
		void setClientDataFilename(const std::string &newClientDataFilename);
        static const std::string &getClientDataFilename();

        void setMatchDataFilename(const std::string &newMatchDataFilename);
        static const std::string &getMatchDataFilename();
};




#endif