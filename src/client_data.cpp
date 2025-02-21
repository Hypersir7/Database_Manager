#include "../include/client_data.hpp"
#include <string>


ClientData::ClientData(std::string InitUsername, std::string InitIpAddress,std::string InitEmailAdress, 
			                   								std::string InitPassword){
	// constructeur qui va initialiser les donnees 
	username = InitUsername;
	ipAddress = InitIpAddress;
	emailAddress = InitEmailAdress;
	password = InitPassword;
}


int ClientData::getId() const {
	return id;
}

std::string ClientData::getUsername() const {
	return username;
}

std::string ClientData::getIpAddress() const {
	return ipAddress;
}

std::string ClientData::getEmailAddress() const {
	return emailAddress;
}

std::string ClientData::getPassword() const {
	return password;
}


void ClientData::setUsername(const std::string &newUsername){
	username = newUsername;
}

void ClientData::setIpAddress(const std::string &newIpAddress){
	ipAddress = newIpAddress;
}

void ClientData::setEmailAddress(const std::string &newEmailAddress){
	emailAddress = newEmailAddress;
}

void ClientData::setPassword(const std::string &newPassword){
	password = newPassword;
}

std::string ClientData::buildCSVformat() const {
	std::string stringID = std::to_string(id);
	std::string csvDataFormat = stringID + "," + username + "," + ipAddress + "," + emailAddress + "," + password;

	return csvDataFormat;
}
