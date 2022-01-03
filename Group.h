#ifndef SQUIDGAME_FINAL_GROUP_H
#define SQUIDGAME_FINAL_GROUP_H

#include "BinarySearchTree.h"
#include "Player.h"

class Group {

BST<int,BST<int,Player>> Levels;
BST<int,Player> Players;
int ID;
Player* Waiting;

public:
    Group(int id);
    ~Group();
    void AddPlayer(int ID,int score);
    void RemovePlayer(int ID);
    void IncreasePlayerLevel(int ID,int increment);
    void UpdatePlayerScore(int ID,int Score);
    double GetPercentInBounds(int score,int LowerLevel,int HigherLevel);
    double AvargeHighestPlayer(int NumOfPlayers);
};


#endif //SQUIDGAME_FINAL_GROUP_H
