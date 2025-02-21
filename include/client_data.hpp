#ifndef CLIENT_DATA_HPP
#define CLIENT_DATA_HPP

#include <string>

class ClientData{
	private:
		int id;
		std::string username;
		std::string ipAddress;
		std::string emailAddress;
		std::string password;

		void setId(); // elle n'accepete pas d'argument mais va generer un ID a l'aide 'generateId()'
		int generateId(); // rand() : pour generer un ID unique associe a chaque client
						 // est ce 'rand' renvoie des dupliquees? si oui -> voir un autre mecanisem
	public:
		ClientData(std::string InitUsername, std::string InitIpAddress,std::string InitEmailAdress, 
			                   								std::string InitPassword);

		//Methodes d'acces aux attribues privees (les getters)
		int getId() const; // METHODES etant constantes toutes car ne modifient pas les donnees
		std::string getUsername() const; // les 'read' seulement! ;
		std::string getIpAddress() const;
		std::string getEmailAddress() const;
		std::string getPassword() const;

		//Methodes changement des attribues  privees(les setters)

		void setUsername(const std::string &newUsername);
		void setIpAddress(const std::string &newIpAddress);
		void setEmailAddress(const std::string &newEmailAddress);
		void setPassword(const std::string &newPassword);

		std::string buildCSVformat() const; // va concatener les donnes en format CSV 
};


#endif