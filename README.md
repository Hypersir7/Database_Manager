





En supposant qu'on se trouve dans le dossier tests\ voici la commande de compilation pour tester Leaderboard

'''
g++ ../include/leaderboard.hpp ../src/leaderboard.cpp testLeaderboard.cpp -o testLeaderboard

'''

-----------------------------------------
Leaderboard contient 6 methodes:

		void displayLeaderboard() const;
		void addScore(const std::string &playerName, int score);// data: via 'Player::getScore()';
		void saveScores();
		void loadScores();
		void setFileName(const char *NewFilename);
		const char *getFileName() const;
		Leaderboard();
		~Leaderboard();

-----------------------------------------




===  ===  ===  ===  ===  ===  ===  ===  ===  ===  ===  ===  ===  