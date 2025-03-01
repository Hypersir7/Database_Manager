#include <iostream>
#include "../include/invitation_system.hpp"


void testInvitationSystem() {
    std::cout << "[TESTING] Initializing Invitation System..." << std::endl;

    InvitationSystem invitationManager;
    invitationManager.loadInvitationsFromCSV("../database/invitations.csv");

    int PLAYER1 = 9833; std::cout << "PLAYER1 ID : " << PLAYER1 << std::endl;
    int PLAYER2 = 1001; std::cout << "PLAYER2 ID : " << PLAYER2 << std::endl;
    int PLAYER3 = 2033; std::cout << "PLAYER3 ID : " << PLAYER3 << std::endl;
    int PLAYER4 = 4502; std::cout << "PLAYER4 ID : " << PLAYER4 << std::endl;
    int PLAYER5 = 3802; std::cout << "PLAYER5 ID : " << PLAYER5 << std::endl;

    std::cout << "\n[TEST] Sending invitations..." << std::endl;
    invitationManager.sendInvitationToID(PLAYER1, PLAYER2);
    invitationManager.sendInvitationToID(PLAYER1, PLAYER3);
    invitationManager.sendInvitationToID(PLAYER2, PLAYER4);
    invitationManager.sendInvitationToID(PLAYER1, PLAYER4);

    std::cout << "[RESULT] Invitations sent successfully ✅\n" << std::endl;

    std::cout << "[TEST] Accepting invitations..." << std::endl;
    invitationManager.accepteInvitation(PLAYER2, PLAYER1);
    invitationManager.accepteInvitation(PLAYER3, PLAYER1);

    std::cout << "[RESULT] Invitations accepted successfully ✅\n" << std::endl;

    std::cout << "[TEST] Declining an invitation..." << std::endl;
    invitationManager.declineInvitation(PLAYER4, PLAYER2);

    std::cout << "[RESULT] Invitation declined successfully ✅\n" << std::endl;

    invitationManager.sendInvitationToID(PLAYER2, PLAYER1);
    invitationManager.sendInvitationToID(PLAYER3, PLAYER1);
    invitationManager.sendInvitationToID(PLAYER5, PLAYER1);
    invitationManager.sendInvitationToID(PLAYER4, PLAYER1);

    invitationManager.accepteInvitation(PLAYER1, PLAYER2);

    invitationManager.declineInvitation(PLAYER1,PLAYER3);

    invitationManager.sendInvitationToID(PLAYER4, PLAYER1);
    invitationManager.accepteInvitation(PLAYER1, PLAYER2);
    invitationManager.accepteInvitation(PLAYER1, PLAYER4);
    invitationManager.accepteInvitation(PLAYER1, PLAYER4);
    invitationManager.accepteInvitation(PLAYER1,PLAYER5);
    std::cout << "\n[TEST] Displaying Player " << PLAYER1 << " invitations:" << std::endl;
    invitationManager.displayPlayerInvitations(PLAYER1);

    std::cout << "\n[TEST] Saving invitations data to '../database/invitations.csv' ..." << std::endl;
    invitationManager.saveInvitationsToCSV("../database/invitations.csv");
    std::cout << "[RESULT] Invitations data saved successfully ✅\n" << std::endl;
}

int main() {
    testInvitationSystem();
    return 0;
}
