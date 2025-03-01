#include <iostream>
#include "../include/friends.hpp"

void testFriendsModule() {
    std::cout << "[TESTING] Initializing Friends Module for TESTING..." << std::endl;

    Friends friendsManager;
    friendsManager.loadFriendsFromCSV("../database/friends.csv");
    std::cout << std::endl; std::cout << std::endl;
    int PLAYER1 = 9833; std::cout << "PLAYER1 ID : " << PLAYER1 << std::endl;
    int PLAYER2 = 1001; std::cout << "PLAYER2 ID : " << PLAYER2 << std::endl;
    int PLAYER3 = 2033; std::cout << "PLAYER3 ID : " << PLAYER3 << std::endl;
    int PLAYER4 = 4502; std::cout << "PLAYER4 ID : " << PLAYER4 << std::endl;

    std::cout << "\n[TEST] Adding friends..." << std::endl;
    friendsManager.addFriend(PLAYER1, PLAYER2); friendsManager.accepteFriend(PLAYER1, PLAYER2);
    friendsManager.addFriend(PLAYER1, PLAYER3); friendsManager.accepteFriend(PLAYER1, PLAYER3);
    friendsManager.addFriend(PLAYER1, PLAYER4); friendsManager.accepteFriend(PLAYER1, PLAYER4);
    friendsManager.addFriend(PLAYER3, PLAYER4); friendsManager.accepteFriend(PLAYER3, PLAYER2);

    std::cout << "[RESULT] Friends added successfully ✅\n" << std::endl;

    std::cout << "[TEST] Checking friendships..." << std::endl;
    friendsManager.isAFriend(PLAYER1, PLAYER2); 
    friendsManager.isAFriend(PLAYER1, PLAYER3); 
    friendsManager.isAFriend(PLAYER1, PLAYER4); 
    friendsManager.isAFriend(PLAYER3, PLAYER4);
    friendsManager.isAFriend(PLAYER2, PLAYER4); 

    std::cout << "\n[TEST] Displaying Player " << PLAYER1 << " friends:" << std::endl;
    friendsManager.displayFriends(PLAYER1);

    std::cout << "\n[TEST] Removing a friend..." << std::endl;
    friendsManager.removeFriend(PLAYER1, PLAYER3);
    std::cout << "[RESULT] Friendshhip removed successfully ✅\n" << std::endl;

    std::cout << "[TEST] Checking friendship again..." << std::endl;
    friendsManager.isAFriend(PLAYER1, PLAYER3);

    std::cout << "\n[TEST] Displaying Player " << PLAYER1 << " friends after removal of freind:" << std::endl;
    friendsManager.displayFriends(PLAYER1);

    std::cout << "\n[TEST] Saving friends data to '../database/friends.csv' .." << std::endl;
    friendsManager.saveFriendsToCSV("../database/friends.csv");
    std::cout << "[RESULT] Friends data saved successfully ✅\n" << std::endl;
}

int main() {
    testFriendsModule();
    return 0;
}
