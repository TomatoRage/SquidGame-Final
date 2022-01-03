#ifndef SQUIDGAME_FINAL_PLAYER_H
#define SQUIDGAME_FINAL_PLAYER_H

class Player {
int Score;
int Level;
int PlayerID;
int Group;

public:
    Player(int Score = -1,int ID = -1,int Group = -1,int Level = 0);
    void SetID(int ID){
        this->PlayerID = ID;
    }
    void SetGroup(int ID){
        this->Group = ID;
    }
    void SetLevel(int lvl){
        this->Level = lvl;
    }
    void SetScore(int score){
        this->Score = score;
    }
    int GetID(){
        return this->PlayerID;
    }
    int GetScore(){
        return this->Score;
    }
    int GetGroup(){
        return this->Group;
    }
    int GetLevel(){
        return this->Level;
    }
};


#endif //SQUIDGAME_FINAL_PLAYER_H
