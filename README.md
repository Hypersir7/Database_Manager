
---

# Database Management Module

## Description
This **library** manages player data, game data and scores in the Tetris project, with interactions via CSV files in the database of the project.

---

## 1) Update 1: Leaderboard

The **Leaderboard** module contains 6 methods:

- **void displayLeaderboard() const;**
- **void addScore(const std::string &playerName, int score);**
- **void saveScores();**
- **void loadScores();**
- **void setFileName(const char *NewFilename);**
- **const char *getFileName() const;**

These methods handle the display [and the updating of the leaderboard is done by DatabaseManager class].

---

## 2)  Update 2: Player Data

The files **client_data.cpp** and **client_data.hpp** manage player information. The data is stored in clientData.csv with the following format:

clientDate.csv
		id, username, ipAddress, emailAddress, password


---

## 3) Update 3:  DatabaseManager

The DatabaseManager module acts as the intermediary between our game and the storage, handling I/O operations for player data, leaderboard, and match records. 
It's like the Operating System of the app, managing interactions between the core logic and the data storage in CSV files.

---

## Compilation and Testing

Creer le repertoire bin/

```bash
mkdir -p ../bin
```

In the tests/ folder, you can test the Leaderboard module with the following command:

```bash
g++ ../include/leaderboard.hpp ../src/leaderboard.cpp ../myTools/loggerTools/logger.cpp testLeaderboard.cpp -o testLeaderboard

```

In the tests/ folder, you can test the Database Manager for clientsData module with the following command:

```bash
g++ ../include/database_manager.hpp ../include/match.hpp ../include/client_data.hpp ../src/client_data.cpp ../src/match.cpp ../src/database_manager.cpp ../myTools/loggerTools/logger.cpp testDatabaseManager.cpp -o testDBClient

```

In the tests/ folder, you can test the Friends module with the following command:

```bash

g++ ../include/friends.hpp ../src/friends.cpp ../myTools/loggerTools/logger.cpp testFriendsModule.cpp -o testFriendsModule

```

In the tests/ folder, you can test the InvitationSystem module with the following command: MODULE NEARLY DONE

```bash
g++ ../include/invitation_system.hpp ../src/invitation_system.cpp ../myTools/loggerTools/logger.cpp testInvitationsSystem.cpp -o testInvitationsSystem

```



---

## Remarks

- **Important**: Always check the README.md for updates.
- The **DatabaseManager** library is still under development.

---
