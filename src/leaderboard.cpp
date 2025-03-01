#include "../include/leaderboard.hpp"
#include "../myTools/loggerTools/logger.hpp" // un module Logger que j'ai CREE pour suivre les evenements de la BDD
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <utility>
#include <vector>


// constructeur qui va au demarrage charger les scores et noms des joeurs!
Leaderboard::Leaderboard(){
    loadScores(); 
}

Leaderboard::~Leaderboard(){
    saveScores();
}

void Leaderboard::loadScores(){
    std::ifstream leaderboardFile(filename);
    scores.clear(); // s'assurer qu'on vide les scores et noms avant d'en charger des nouveaux

    if(!leaderboardFile.is_open()){
        std::cerr << "[Error while loading data] : could not open file:" << filename << std::endl;
    }else{
        std::string line;

        while(std::getline(leaderboardFile, line)){ // tant qu'on atteint pas EOF (end of file)
            std::vector<std::string> name_score; // vector temporaire qui va stocker les donnees lues
            std::stringstream ss(line);

            while(ss.good()){
                std::string data;
                std::getline(ss, data, ',');
                name_score.push_back(data);
            }

            if(name_score.size() == 2){
                std::string playerName = name_score[0];
                int playerScore = std::stoi(name_score[1]);
                Leaderboard::scores.push_back({playerName, playerScore});
            }
        }

        leaderboardFile.close(); // on a atteint 'EOF'
    }
}


void Leaderboard::addScore(const std::string &playerName, int score){

    bool playerAlreadyExists = false;
    // savoir si un joeur existe deja dans la base de donner 
    // car ca cree des repetitions d'affichage de socre quand j'ai teste le code
    for(auto &items: scores){
        if(items.first == playerName){
            Logger::logMessage("Added score for player " + playerName + ": " + std::to_string(score), "INFO");
            items.second = score; // juste mettre a jour le score
            playerAlreadyExists = true;
            break;
        }
    }

    if(!playerAlreadyExists){
        Leaderboard::scores.push_back({playerName, score});
    }

    int vectoreSize = Leaderboard::scores.size();
    // on va trier selon un ordre decroissant (plus grand au plus petit) en utilisant le bubbleSort algo
    for(int i = 0; i < vectoreSize ; i++){
        for(int j = 0 ; j < vectoreSize - 1 - i ; j++){
            if(scores[j].second < scores[j + 1].second){
                std::swap(scores[j], scores[j + 1]);
            }
        }
    }
}


void Leaderboard::saveScores(){
    std::ofstream leaderboardFile(filename, std::ofstream::trunc); // vide le fichier avant d'y ecrire

    if(!leaderboardFile.is_open()){
        Logger::logMessage("Could not open leaderboard.csv", "ERROR");
        std::cerr << "[Error while loading data] : could not open file:" << filename << std::endl;
    }else{
        Logger::logMessage("Saving scores of leaderboard to CSV", "INFO");
        for(const auto &items: scores){
            leaderboardFile << items.first << "," << items.second << "\n";
        }
        Logger::logMessage("Saved scores of leaderboard to CSV", "INFO");
        leaderboardFile.close();
    }
}


void Leaderboard::displayLeaderboard() const {
    std::cout << "\033[1;34m-------------------------------------------\033[0m" << std::endl; 
    std::cout << "\033[1;32m=============== LEADERBOARD ==============\033[0m" << std::endl; 

    
    for(int i = 0 ; i < scores.size() ; i++){
        if(i == 0){
            std::cout << "\033[1;31m"; // coleur rouge pour le gaganat
            std::cout << scores[i].first << "\033[0m" << " : " << scores[i].second << " points   ";
            std::cout << "\033[1;36m 👑 [WINNER]\033[0m" << std::endl;
        }else if(i == 1){
            std::cout << scores[i].first << " : " << scores[i].second << " points  🥈 " << std::endl;
        }else if(i == 2){
            std::cout << scores[i].first << " : " << scores[i].second << " points  🥉 " << std::endl;
        }else{
            std::cout << scores[i].first << " : " << scores[i].second << " points " << std::endl;
        }
    }
    std::cout << "\033[1;34m-------------------------------------------\033[0m" << std::endl;
}

void Leaderboard::setFileName(const char *NewFilename){
    filename = NewFilename;
}

const char *Leaderboard::getFileName() const {
    return filename;
}
