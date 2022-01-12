#ifndef SQUIDGAME_FINAL_SQUIDGAME_H
#define SQUIDGAME_FINAL_SQUIDGAME_H

#include "FlippedTree.h"
#include "Player.h"

class SquidGame {
    int NumOfGroups;
    int scale;
    int PlayersSize = 251;
    int WaitingSize = 251;
    int CurrentTotalPlayers = 0;
    int CurrentTotalWaiting = 0;
    int DeletePlayersActionCounter = 0;
    int DeleteWaitingActionCounter = 0;
    int HashFunctionMod = PlayersSize;
    bool* deletedPlayersArray;
    bool* deletedWaitingArray;
    const int RehashMultiplier = 1;
    const double ResizeRatio = 0.5;

    FlippedTreeNode* Groups;
    Player** AllPlayers;
    Player** WaitingRoom;
    BST<int,BST<int,Player>*> Level;

    void InsertPlayer(int key,Player* player);
    void InsertWait(int key,Player* player);
    static int FindNextPrime(int start);
    int FindPlayerHash(int ID);
    int FindWaitingHash(int ID);
    void EnterWaitingPlayers();
    int FindGroupFather(int GroupID);

public:

    SquidGame(int K,int Scale);
    ~SquidGame();
    int GetK() const;
    int GetScale() const;
    void AddPlayerToGroup(int GroupID,int PlayerID,int Score);
    void RemovePlayer(int PlayerID);
    void IncreasePlayerLevel(int PlayerID,int increment);
    void ChangePlayerIDScore(int PlayerID,int Score);
    void getPerecentOfPlayersWithScore(int GroupID,int Score,int LowerLevel,int HigherLevel,double *Player);
    void AvgHighestPlayerLevelByGroup(int GroupID,int m,double* AVG);
    void MergeGroups(int Group1,int Group2);

    class FailureException{};
};


#endif //SQUIDGAME_FINAL_SQUIDGAME_H
