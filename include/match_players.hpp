#ifndef MATCH_PLAYERS_HPP
#define MATCH_PLAYERS_HPP

struct MatchPlayers{
	int playerID;
	int gameID;
	int score;
	int rank;

	MatchPlayers(int newPlayerID, int newGameID, int newScore, int newRank);
};



#endif




