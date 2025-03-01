#ifndef CLIENT_DATA_HPP
#define CLIENT_DATA_HPP

#include <string>

class ClientData{
	private:
		int clientID = 0; // sorte de cle de notre BDD pour le client
		static int nextClientID;
		std::string username;
		std::string ipAddress;
		std::string emailAddress; // voir ce soir pour decider de la suppression de cette attribue ou pas
		std::string password;

	public:
		ClientData(std::string InitUsername, std::string InitIpAddress,std::string InitEmailAdress, 
			                   								std::string InitPassword);

		//Methodes d'acces aux attribues privees (les getters)
		int getId() const; // METHODES etant constantes toutes, car ne modifient pas les donnees
		std::string getUsername() const; // les 'read' seulement! ;
		std::string getIpAddress() const;
		std::string getEmailAddress() const;
		std::string getPassword() const;

		//Methodes changement des attribues  privees(les setters) --> passage par &ref --> pas de copies
		void setUsername(const std::string &newUsername);
		void setIpAddress(const std::string &newIpAddress); // 
		void setEmailAddress(const std::string &newEmailAddress); // []
		void setPassword(const std::string &newPassword);

		// renvoie une chaine de chars --> contient les donnees concatenees en format csv --> voir test
		std::string buildCSVformat() const; // va concatener les donnees en format CSV

		void setId(int exitingID); // elle n'accepete pas d'argument mais va generer un ID unique en incrmente le ID pour le client suivant
						// car j'ai recherche rand() peut renvoyer des doubles 
};


#endif