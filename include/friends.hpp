#ifndef FREINDS_HPP
#define FREINDS_HPP

#include <vector>
#include <string>
#include <unordered_map>

// NOUVERAU : ADAPTATION du MODULE pour un autre format de stockage des donnees
// NOUVERAU : MATRIX D'INCIDENCE POUR GERER LES AMITIES ENTRE LES JOEURS
// EFFET : INDEPENANCE TOTALE DU MODULE INIVITATION_SYSTEM
// EFFET : DISPARUTION DES STATUS : ACCPETED ET DECLINED -> JUST PENDING Y EST ENCORE

class Friends{
	private:
		std::string filename = "../database/freinds.csv"; // PAR DEFAUT C'EST LE CHEMIN VERS LA DATABASE
		// NOUVEAU FORMAT : MATRIX D'INCIDENCE --> {playerID : {friendID1 : status1, friendID2 : status2, ...etc }..etc}
		std::unordered_map<int, std::unordered_map<int,int>> friendsIncidenceMatrix; 

	public:
		void loadFriendsFromCSV(const std::string &dbFile); // se charge de charger les donnes des amis
		void saveFriendsToCSV(const std::string &dbFile); // se charge de sauvegarder les donnes des amis

		void addFriend(int playerID, int friendID); // ajoute l'ami avec friendID au client playerID
		void removeFriend(int playerID, int friendID);

		void accepteFriend(int playerID, int friendID); // accepte l'ami avec friendID de client PlayerID

		std::vector<int> getFriends(int playerID); // renvoie l'ensemble d'amis du client avec PlayerID

		void displayFriends(int playerID); // affiche l'ensemble d'amis du client avec PlayerID

		bool isAFriend(int playerID, int friendID); // renvoie si oui ou non playerID est amis avec friendID
};


#endif