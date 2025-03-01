#include <iostream>
#include <vector>
#include "../include/database_manager.hpp"
#include "../include/client_data.hpp"


void testDB_ClientsData(){
    DatabaseManager db;
    db.setClientDataFilename("../database/clientData.csv");
    std::cout << "[TESTING] Loading data from ' " << db.getClientDataFilename() << "' ..." << std::endl;

    std::vector<ClientData> clients = db.loadClientsData();

    std::cout << "[RESULT] Loaded Clients Data:" << std::endl;
    for (const auto& client : clients) {
        std::cout << "ID: " << client.getId() << ", Username: " << client.getUsername()
                  << ", IP Address: " << client.getIpAddress() << ", Email: " << client.getEmailAddress() <<
                  "Password: " << client.getPassword() << std::endl;
    }
    std::string testedIPAddress  = "192.162.1.108";
    if (!clients.empty()) {
        std::cout << "[TESTING] Modifying first client data username and email address..." << std::endl;
        clients[0].setUsername("someName");
        clients[0].setEmailAddress("newemail@gmail.com");
        clients[0].setIpAddress(testedIPAddress);
    }
    std::cout << "[TESTING] Saving modified data to '../database/clientData.csv'..." << std::endl;
    db.saveClientsData(clients);

    std::cout << "[TESTING] Checking if the IP address " << testedIPAddress << " exists in the database..." << std::endl;
    if(db.doesIpAddressExists(testedIPAddress)){
        std::cout << "[RESULT] : the IP Address " << testedIPAddress << " exists in the database ✅" << std::endl;
    }else{
        std::cout << "[RESULT] : the IP Address " << testedIPAddress << " does not exist in the database ❌" << std::endl;
    }


    std::cout << "[TEST] Loading modified data from '../database/clientData.csv'..." << std::endl;
    std::vector<ClientData> savedClients = db.loadClientsData();

    std::cout << "[TEST] Loaded Modified Clients Data:" << std::endl;
    for (const auto& client : savedClients) {
        std::cout << "ID: " << client.getId() << ", Username: " << client.getUsername()
                  << ", IP Address: " << client.getIpAddress() << ", Email: " << client.getEmailAddress() << std::endl;
    }
}


int main() {
    testDB_ClientsData(); // on va tester le fonctionnement de
    std::cout << "DONE!" << std::endl;
    return 0;
}