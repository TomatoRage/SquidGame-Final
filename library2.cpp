#include "library2.h"
#include "SquidGame.h"
#include "stdexcept"
#include "iostream"

void *Init(int k, int scale){
    try{
        auto* DS = new SquidGame(k,scale);
        return (void*)DS;
    }catch(std::bad_alloc& e){
        return nullptr;
    }
}

StatusType MergeGroups(void *DS, int GroupID1, int GroupID2){
    if(GroupID1 <= 0 || GroupID2 <= 0 || GroupID1 > ((SquidGame*)DS)->GetK()|| GroupID2>((SquidGame*)DS)->GetK()){
        return INVALID_INPUT;
    }
    try{
        ((SquidGame*)DS)->MergeGroups(GroupID1-1,GroupID2-1);
    }catch(std::bad_alloc& e){
        return ALLOCATION_ERROR;
    }catch (...){
        return FAILURE;
    }
    return SUCCESS;
}

StatusType AddPlayer(void *DS, int PlayerID, int GroupID, int score){
    if(!DS || PlayerID <= 0||GroupID <= 0 || GroupID > ((SquidGame*)DS)->GetK() || score <= 0 || score > ((SquidGame*)DS)->GetScale()){
        return INVALID_INPUT;
    }
    try{
        ((SquidGame*)DS)->AddPlayerToGroup(GroupID-1,PlayerID,score);
    }catch(std::bad_alloc& e){
        return ALLOCATION_ERROR;
    }catch (...){
        return FAILURE;
    }
    return SUCCESS;
}

StatusType RemovePlayer(void *DS, int PlayerID){
    if(!DS || PlayerID <= 0)
        return INVALID_INPUT;
    try{
        ((SquidGame*)DS)->RemovePlayer(PlayerID);
    }catch(std::bad_alloc& e){
        return ALLOCATION_ERROR;
    }catch(...){
        return FAILURE;
    }
    return SUCCESS;
}

StatusType IncreasePlayerIDLevel(void *DS, int PlayerID, int LevelIncrease){
    if(!DS || PlayerID <= 0 || LevelIncrease <= 0)
        return INVALID_INPUT;
    try{
        ((SquidGame*)DS)->IncreasePlayerLevel(PlayerID,LevelIncrease);
    }catch (std::bad_alloc& e){
        return ALLOCATION_ERROR;
    }catch (...){
        return FAILURE;
    }
    return SUCCESS;
}

StatusType ChangePlayerIDScore(void *DS, int PlayerID, int NewScore){
    if(!DS || PlayerID <= 0 || NewScore <= 0 || NewScore > ((SquidGame*)DS)->GetScale()){
        return INVALID_INPUT;
    }
    try{
        ((SquidGame*)DS)->ChangePlayerIDScore(PlayerID,NewScore);
    }catch (std::bad_alloc& e){
        return ALLOCATION_ERROR;
    }catch (...){
        return FAILURE;
    }
    return SUCCESS;
}

StatusType GetPercentOfPlayersWithScoreInBounds(void *DS, int GroupID, int score, int lowerLevel, int higherLevel,
                                                double * players){
    if(!DS || GroupID < 0 || GroupID > ((SquidGame*)DS)->GetK() || !players){
        return INVALID_INPUT;
    }
    try{
        ((SquidGame*)DS)->getPerecentOfPlayersWithScore(GroupID-1,score,lowerLevel,higherLevel,players);
    }catch (std::bad_alloc& e){
        return ALLOCATION_ERROR;
    }catch (...){
        return FAILURE;
    }
    return SUCCESS;
}

StatusType AverageHighestPlayerLevelByGroup(void *DS, int GroupID, int m, double * level){
    if(!DS || GroupID < 0 || GroupID > ((SquidGame*)DS)->GetK() || !level || m <= 0){
        return INVALID_INPUT;
    }
    try{
        ((SquidGame*)DS)->AvgHighestPlayerLevelByGroup(GroupID-1,m,level);
    }catch (std::bad_alloc& e){
        return ALLOCATION_ERROR;
    }catch (...){
        return FAILURE;
    }
    return SUCCESS;
}

StatusType GetPlayersBound(void *DS, int GroupID, int score, int m,
                           int * LowerBoundPlayers, int * HigherBoundPlayers){
    return SUCCESS;
}

void Quit(void** DS){

    if(!DS)
        return;
    delete *(SquidGame**)DS;
    *DS = nullptr;

}