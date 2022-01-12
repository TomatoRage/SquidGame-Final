#include "SquidGame.h"

SquidGame::SquidGame(int K, int Scale) {
   NumOfGroups = K;
   scale = Scale;
   AllPlayers = new Player*[PlayersSize];
   WaitingRoom = new Player*[WaitingSize];
   deletedPlayersArray = new bool[PlayersSize];
   deletedWaitingArray = new bool[WaitingSize];
   Groups = new FlippedTreeNode[K];
   for(int i = 0; i < PlayersSize; i++){
       AllPlayers[i] = nullptr;
       WaitingRoom[i] = nullptr;
       deletedWaitingArray[i] = false;
       deletedPlayersArray[i] = false;
   }
   for(int i = 0; i < K;i++){
       Groups->father = nullptr;
       Groups->index = i;
       Groups->GP = new Group(i);
       Groups->TotalSons = 0;
       Groups->Sons = new FlippedTreeNode*[K];
       for(int j = 0; j < K; j++){
           Groups->Sons[j] = nullptr;
       }
   }

   Level.insert(0,new BST<int,Player>);
}

SquidGame::~SquidGame() {
    delete[] AllPlayers;
    delete[] WaitingRoom;
    delete[] deletedPlayersArray;
    delete[] deletedWaitingArray;
    Level.ResetIterator();
    int key, *key_ptr = &key;
    for(int i = 0; i < Level.GetSize(); i++){
        delete &Level.NextIteration(&key_ptr);
    }
    for(int i = 0; i < NumOfGroups; i++){
        delete Groups[i].GP;
    }
    delete[] Groups;
}

int SquidGame::GetK() const { return NumOfGroups; }

int SquidGame::GetScale() const { return scale; }

void SquidGame::AddPlayerToGroup(int GroupID, int PlayerID, int Score) {

    int index = FindPlayerHash(PlayerID);
    if(index != -1)
        throw FailureException();

    Player* p = new Player(Score, PlayerID, GroupID);
    Groups[GroupID].GP->AddPlayer(PlayerID,Score);

    InsertPlayer(PlayerID,p);

    if(double(CurrentTotalPlayers)/double(PlayersSize) > ResizeRatio){
        int size = FindNextPrime(PlayersSize*2);
        auto** NewArray = new Player*[size];
        auto* newDeleteArray = new bool[size];

        for(int i = 0; i < size; i++){
            NewArray[i] = nullptr;
            newDeleteArray[i] = false;
        }

        for(int i = 0; i < PlayersSize; i++){
            NewArray[i] = AllPlayers[i];
            newDeleteArray[i] = deletedPlayersArray[i];
        }


        delete[] AllPlayers;
        delete[] deletedPlayersArray;

        AllPlayers = NewArray;
        deletedPlayersArray = newDeleteArray;
        PlayersSize = size;
    }

    InsertWait(PlayerID,p);

    if(double(CurrentTotalWaiting)/double(WaitingSize) > ResizeRatio){
        int size = FindNextPrime(WaitingSize*2);
        auto** NewArray = new Player*[size];
        auto* newDeleteArray = new bool[size];

        for(int i = 0; i < size; i++){
            NewArray[i] = nullptr;
            newDeleteArray[i] = false;
        }

        for(int i = 0; i < WaitingSize; i++){
            NewArray[i] = WaitingRoom[i];
            newDeleteArray[i] = deletedWaitingArray[i];
        }


        delete[] WaitingRoom;
        delete[] deletedWaitingArray;

        WaitingRoom = NewArray;
        deletedWaitingArray = newDeleteArray;
        WaitingSize = size;
    }
}

void SquidGame::RemovePlayer(int PlayerID) {
    int index = FindPlayerHash(PlayerID);

    if(index == -1)
        throw FailureException();

    int GroupID = AllPlayers[index]->GetGroup();
    int PlayerLvl = AllPlayers[index]->GetLevel();
    Groups[GroupID].GP->RemovePlayer(PlayerID);

    delete AllPlayers[index];
    AllPlayers[index] = nullptr;
    deletedPlayersArray[index] = true;
    DeletePlayersActionCounter++;

    if(DeletePlayersActionCounter >= RehashMultiplier*PlayersSize){
        auto** NewArray = new Player*[PlayersSize];
        DeletePlayersActionCounter = 0;
        HashFunctionMod = PlayersSize;
        for(int i=0; i < PlayersSize; i++){
            NewArray[i] = nullptr;
            deletedPlayersArray[i] = false;
        }
        for(int i=0; i < PlayersSize; i++){
            if(AllPlayers[i] != nullptr){
                int ID = AllPlayers[i]->GetID();
                int HashFunction = ID%HashFunctionMod;
                int StepFunction = 1+(ID%5);
                int k = 0;
                int HashIndex = (HashFunction+k*StepFunction) % PlayersSize;

                while(true){
                    if(NewArray[HashIndex] == nullptr){
                        NewArray[HashIndex] = AllPlayers[i];
                        break;
                    }
                    k++;
                }

            }
            deletedPlayersArray[i] = false;
        }
    }

    int WaitingIndex = FindWaitingHash(PlayerID);

    if(WaitingIndex == -1){
        Level.Find(PlayerLvl)->remove(PlayerID);
        if(Level.Find(PlayerLvl)->GetSize() == 0){
            delete Level.Find(PlayerLvl);
            Level.remove(PlayerLvl);
        }
        return;
    }

    delete WaitingRoom[index];
    WaitingRoom[index] = nullptr;
    deletedWaitingArray[index] = true;
    DeleteWaitingActionCounter++;

    if(DeleteWaitingActionCounter >= RehashMultiplier*WaitingSize){
        auto** NewArray = new Player*[WaitingSize];
        DeleteWaitingActionCounter = 0;
        HashFunctionMod = WaitingSize;
        for(int i=0; i < WaitingSize; i++){
            NewArray[i] = nullptr;
            deletedWaitingArray[i] = false;
        }
        for(int i=0; i < WaitingSize; i++){
            if(WaitingRoom[i] != nullptr){
                int ID = WaitingRoom[i]->GetID();
                int HashFunction = ID%HashFunctionMod;
                int StepFunction = 1+(ID%5);
                int k = 0;
                int HashIndex = (HashFunction+k*StepFunction) % WaitingSize;

                while(true){
                    if(NewArray[HashIndex] == nullptr){
                        NewArray[HashIndex] = WaitingRoom[i];
                        break;
                    }
                    k++;
                }

            }
            deletedWaitingArray[i] = false;
        }
    }
}

void SquidGame::IncreasePlayerLevel(int PlayerID, int increment) {

    EnterWaitingPlayers();

    int index = FindPlayerHash(PlayerID);

    if(index == -1)
        throw FailureException();

    int lvl = AllPlayers[index]->GetLevel();
    int GroupID = AllPlayers[index]->GetGroup();

    Level.Find(lvl)->remove(PlayerID);

    if(Level.Find(lvl)->GetSize() == 0) {
        delete Level.Find(lvl);
        Level.remove(lvl);
    }

    AllPlayers[index]->SetLevel(lvl+increment);
    Groups[GroupID].GP->IncreasePlayerLevel(PlayerID,increment);

    try{
        Level.Find(lvl+increment)->insert(PlayerID,*AllPlayers[index]);
    }catch(BST<int,BST<int,Player>*>::KeyNotFound &e){
        Level.insert(lvl+increment,new BST<int,Player>);
        Level.Find(lvl+increment)->insert(PlayerID,*AllPlayers[index]);
    }
}

void SquidGame::ChangePlayerIDScore(int PlayerID, int Score) {

    EnterWaitingPlayers();

    int index = FindPlayerHash(PlayerID);
    if(index == -1)
        throw FailureException();

    int lvl = AllPlayers[index]->GetLevel();

    AllPlayers[index]->SetScore(Score);

    Level.Find(lvl)->Find(PlayerID).SetScore(Score);

    Groups[AllPlayers[index]->GetGroup()].GP->UpdatePlayerScore(PlayerID,Score);

}

void SquidGame::getPerecentOfPlayersWithScore(int GroupID, int Score, int LowerLevel, int HigherLevel, double *player) {

    EnterWaitingPlayers();

    int NumOfPlayers=0,key,*key_ptr = &key;

    if(GroupID == 0) {
        Level.ResetIterator();

        for (int i = 0; Level.GetSize(); i++) {
            BST<int, Player> *Tree = Level.NextIteration(&key_ptr);

            if (key < LowerLevel)
                continue;
            else if(key > HigherLevel)
                break;
            else{
                Tree->ResetIterator();
                int KEY,*KEY_PTR = &KEY;
                for(int j = 0; j < Tree->GetSize();j++){
                    if(Tree->NextIteration(&KEY_PTR).GetScore() == Score){
                        NumOfPlayers++;
                    }
                }
            }
        }
        *player = double(NumOfPlayers)/double(CurrentTotalPlayers);
        return;
    }

    int TotalPlayers = 0;
    int Index = FindGroupFather(GroupID);

    for(int i = 0; i < NumOfGroups; i++){
        if(Groups[Index].Sons[i] == nullptr)
            continue;
        TotalPlayers += Groups[Index].Sons[i]->GP->GetPercentInBounds(Score,LowerLevel,HigherLevel);
    }

    *player = double(TotalPlayers)/double(CurrentTotalPlayers);

}

void SquidGame::AvgHighestPlayerLevelByGroup(int GroupID, int m, double *AVG) {

    EnterWaitingPlayers();

    if(GroupID == 0){

        if(CurrentTotalPlayers < m)
            throw FailureException();

        Level.ResetIterator();
        for(int i = 0; < )

    }
    //*AVG = Groups[GroupID].GP->AvargeHighestPlayer(m);
}