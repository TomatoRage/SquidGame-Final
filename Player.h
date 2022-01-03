#ifndef SQUIDGAME_FINAL_PLAYER_H
#define SQUIDGAME_FINAL_PLAYER_H

class Player {
int Score;
int Level;
int PlayerID;
int Group;

public:
    Player(int Score = -1,int ID = -1,int Group = -1,int Level = 0);
    void SetID(int ID);
    void SetGroup(int ID);
    void SetLevel(int lvl);
    void SetScore(int Score);
    int GetID();
    int GetScore();
    int GetGroup();
    int GetLevel();
};


#endif //SQUIDGAME_FINAL_PLAYER_H
