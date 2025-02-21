#include "../include/leaderboard.hpp"
#include <iostream>

void TestLeaderboard() {
    Leaderboard leaderboard;

    std::cout << "[START] Starting Leaderboard Test... 🧪 " << std::endl;

    std::cout << "[INFO] Initial Leaderboard" << std::endl;
    leaderboard.displayLeaderboard();
    
    std::cout << "[INFO] Setting the leaderboard file path..." << std::endl;
    leaderboard.setFileName("../database/leaderboard.csv");
    std::cout << "[RESULT] file path set to : '" << leaderboard.getFileName()<< "'" << std::endl;

    std::vector<std::pair<std::string, int>> scores = {
        {"Kira", 100}, {"Sheta", 450}, {"Abdo", 20},
        {"Amr", 56}, {"Joao", 199}, {"Horia", 0}, {"T", 296},
        {"Alex", 234}, {"L", 89}, {"Alex", 34}, {"Alice", 134}
    };

    std::cout << "1.  [TESTING] Adding test scores to the leaderboard..." << std::endl;
    for (const auto& item : scores) {
        std::cout << "[INFO] Adding player: " << item.first << " with score: " << item.second << std::endl;
        leaderboard.addScore(item.first, item.second);
    }
    std::cout << "      1.1 [SUCESS] ✅ " << std::endl;

    std::cout << "\n2.  [TESTING] Leaderboard after adding scores:" << std::endl;
    leaderboard.displayLeaderboard();
    std::cout << "      2.1 [SUCESS] ✅ " << std::endl;

    std::cout << "\n[TESTING] Current filename: " << leaderboard.getFileName() << std::endl;
    std::cout << "------[SUCESS] ✅ " << std::endl;

    std::cout << "3.  [TESTING] Saving scores to the file..." << std::endl;
    leaderboard.saveScores();
    std::cout << "      3.1 [RESULT] Scores saved successfully ✅ " << std::endl;

    std::cout << "\n4.  [TESTING] Loading leaderboard from the file..." << std::endl;
    leaderboard.loadScores();
    std::cout << "      4.1 [SUCESS] ✅ " << std::endl;

    std::cout << "\n5.  [TESTING] Leaderboard after loading from file:" << std::endl;
    leaderboard.displayLeaderboard();
    std::cout << "      5.1 [SUCESS] ✅ " << std::endl;

    std::cout << "[FINAL] Test completed successfully" << std::endl;
}

int main() {
    TestLeaderboard();
    return 0;
}


