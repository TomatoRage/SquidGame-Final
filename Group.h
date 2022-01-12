#ifndef SQUIDGAME_FINAL_GROUP_H
#define SQUIDGAME_FINAL_GROUP_H

#include "BinarySearchTree.h"
#include "Player.h"

class Group {

    int Size = 251;
    int CurrentTotalPlayers;
    int DeleteActionCounter;
    int HashFunctionMod = Size;
    bool* deletedArray;
    const int RehashMultiplier = 1;
    const double ResizeRatio = 0.5;

    BST<int,BST<int,Player>> Levels;
    BST<int,Player> Players;
    int ID;
    Player** Waiting;

    void InsertHash(int key,Player* image);
    static int FindNextPrime(int start);
    int FindHash(int ID);
    void EnterWaitingPlayers();

public:
    Group(int id);
    ~Group();
    void AddPlayer(int ID,int score);
    void RemovePlayer(int ID);
    void IncreasePlayerLevel(int ID,int increment);
    void UpdatePlayerScore(int ID,int Score);
    int GetPercentInBounds(int score,int LowerLevel,int HigherLevel);
    int AvargeHighestPlayer(int NumOfPlayers);

    class FailureException{};
};


#endif //SQUIDGAME_FINAL_GROUP_H
