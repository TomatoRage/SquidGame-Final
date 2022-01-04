#ifndef SQUIDGAME_FINAL_SQUIDGAME_H
#define SQUIDGAME_FINAL_SQUIDGAME_H

#include "FlippedTree.h"
#include "Player.h"

class SquidGame {
    int k;
    int scale;
    FlippedTreeNode* Groups;
    Player* AllPlayers;
    Player* WaitingRoom;
    BST<int,BST<int,Player>> Level;

public:

    SquidGame(int K,int Scale);
    ~SquidGame();
    int GetK(){
        return this->k;
    }
    int GetScale(){
        return this->scale;
    }
    void AddPlayerToGroup(int GroupID,int PlayerID,int Score);
    void RemovePlayer(int PlayerID);
    void IncreasePlayerLevel(int PlayerID,int increment);
    void ChangePlayerIDScore(int PlayerID,int Score);
    void getPerecentOfPlayersWithScore(int GroupID,int Score,int LowerLevel,int HigherLevel,double *Player);
    void AvgHighestPlayerLevelByGroup(int GroupID,int m,double* AVG);

};


#endif //SQUIDGAME_FINAL_SQUIDGAME_H
