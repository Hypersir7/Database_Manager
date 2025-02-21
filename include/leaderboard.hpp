#ifndef LEADERBOARD_HPP
#define LEADERBOARD_HPP

#include <string>
#include <vector>

class Leaderboard{
	private:
		const char *filename = "../database/leaderboard.csv"; // faut se decider ou stocker ce fichier!
		std::vector <std::pair<std::string, int>> scores; // vector de scores -> au format csv {{name,score}}

	public: 
		//Methode constantes : ne modifient pas les donner juste les chargent/affichent
		void displayLeaderboard() const;

		// cette methode devrait recevoir les donnees depuis 'game.cpp' pour les enrigistrer
		void addScore(const std::string &playerName, int score);// data: via 'Player::getScore()';
		void saveScores();
		void loadScores();
		void setFileName(const char *NewFilename);
		const char *getFileName() const;
		Leaderboard();
		~Leaderboard();
};

#endif