#ifndef INVITATION_SYSTEM_HPP
#define INVITATION_SYSTEM_HPP

#include <string>
#include <vector>

class InvitationSystem{
	private:	
		std::string filename = "../database/invitations.csv";
		std::vector<std::vector<std::string>> invitationsList;
	public:
		void loadInvitationsFromCSV(const std::string &dbFile); // done
		void saveInvitationsToCSV(const std::string &dbFile); // done

		void sendInvitationToID(int senderID, int receiverID); // de sender vers receiver via le ID du friend/client
		void accepteInvitation(int receiverID, int senderID);
		void declineInvitation(int receiverID, int senderID);
		std::vector<std::vector<std::string>> &getPendingInvitations(int playerID);
		void displayPlayerInvitations(int playerID);

};



#endif