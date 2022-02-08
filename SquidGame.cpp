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
       Groups[i].father = nullptr;
       Groups[i].index = i;
       Groups[i].GP = new Group(i);
       Groups[i].TotalSons = 0;
   }

   Level.insert(0,new BST<int,Player>);
}

SquidGame::~SquidGame() {
    Level.ResetIterator();
    int key, *key_ptr = &key;
    for(int i = 0; i < Level.GetSize(); i++){
        delete Level.NextIteration(&key_ptr);
    }
    Level.clear();
    for(int i = 0; i < NumOfGroups; i++){
        delete Groups[i].GP;
    }
    for(int i = 0; i < PlayersSize; i++)
        delete AllPlayers[i];

    delete[] WaitingRoom;
    delete[] deletedPlayersArray;
    delete[] deletedWaitingArray;
    delete[] AllPlayers;
    delete[] Groups;
}

int SquidGame::GetK() const { return NumOfGroups; }

int SquidGame::GetScale() const { return scale; }

void SquidGame::AddPlayerToGroup(int GroupID, int PlayerID, int Score) {

    int index = FindPlayerHash(PlayerID);
    if(index != -1)
        throw FailureException();

    Player* p = new Player(Score, PlayerID, GroupID);
    Groups[FindGroupFather(GroupID)].GP->AddPlayer(PlayerID,Score);

    InsertPlayer(PlayerID,p);

    if(double(CurrentTotalPlayers)/double(PlayersSize) > ResizeRatio){
        int size = FindNextPrime(PlayersSize*2);
        auto** NewArray = new Player*[size];
        auto* newDeleteArray = new bool[size];
        DeletePlayersActionCounter = 0;
        HashFunctionMod = size;

        for(int i = 0; i < size; i++){
            NewArray[i] = nullptr;
            newDeleteArray[i] = false;
        }

        for(int i=0; i < PlayersSize; i++) {
            if (AllPlayers[i] != nullptr) {
                int ID = AllPlayers[i]->GetID();
                int HashFunction = ID % HashFunctionMod;
                int StepFunction = 1 + (ID % 5);
                int k = 0;
                int HashIndex = (HashFunction + k * StepFunction) % size;

                while (true) {
                    if (NewArray[HashIndex] == nullptr) {
                        NewArray[HashIndex] = AllPlayers[i];
                        break;
                    }
                    k++;
                    HashIndex = (HashFunction + k * StepFunction) % size;
                }

            }
        }


        delete[] AllPlayers;
        delete[] deletedPlayersArray;

        AllPlayers = NewArray;
        deletedPlayersArray = newDeleteArray;
        PlayersSize = size;
    }

    InsertWait(PlayerID,p);

    if(double(CurrentTotalWaiting)/double(WaitingSize) > ResizeRatio){
        EnterWaitingPlayers();
    }
}

void SquidGame::RemovePlayer(int PlayerID) {
    int index = FindPlayerHash(PlayerID);
    int WaitingIndex = FindWaitingHash(PlayerID);
    if(index == -1)
        throw FailureException();

    int GroupID = AllPlayers[index]->GetGroup();
    int PlayerLvl = AllPlayers[index]->GetLevel();
    Groups[FindGroupFather(GroupID)].GP->RemovePlayer(PlayerID);


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
                    HashIndex = (HashFunction+k*StepFunction) % PlayersSize;
                }

            }
            deletedPlayersArray[i] = false;
        }
        delete[] AllPlayers;
        AllPlayers = NewArray;
    }



    if(WaitingIndex == -1){
        Level.Find(PlayerLvl)->remove(PlayerID);
        if(Level.Find(PlayerLvl)->GetSize() == 0){
            delete Level.Find(PlayerLvl);
            Level.remove(PlayerLvl);
        }
        CurrentTotalPlayers --;
        return;
    }

    CurrentTotalPlayers --;
    CurrentTotalWaiting--;

    WaitingRoom[WaitingIndex] = nullptr;
    deletedWaitingArray[WaitingIndex] = true;
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
    int WaitingIndex = FindWaitingHash(PlayerID);

    if(index == -1)
        throw FailureException();

    int lvl = AllPlayers[index]->GetLevel();
    int GroupID = FindGroupFather(AllPlayers[index]->GetGroup());

    Level.Find(lvl)->remove(PlayerID);

    if(Level.Find(lvl)->GetSize() == 0) {
        delete Level.Find(lvl);
        Level.remove(lvl);
    }

    AllPlayers[index]->SetLevel(lvl+increment);
    Groups[GroupID].GP->EnterWaitingPlayers();
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

    Groups[FindGroupFather(AllPlayers[index]->GetGroup())].GP->EnterWaitingPlayers();
    Groups[FindGroupFather(AllPlayers[index]->GetGroup())].GP->UpdatePlayerScore(PlayerID,Score);

}

void SquidGame::getPerecentOfPlayersWithScore(int GroupID, int Score, int LowerLevel, int HigherLevel, double *player) {

    EnterWaitingPlayers();

    int NumOfPlayers=0,Total = 0,key,*key_ptr = &key;

    if(GroupID == -1) {
        Level.ResetIterator();

        for (int i = 0; i < Level.GetSize(); i++) {
            BST<int, Player> *Tree = Level.NextIteration(&key_ptr);

            if (key < LowerLevel)
                continue;
            else if(key > HigherLevel)
                break;
            else{
                Tree->ResetIterator();
                int KEY,*KEY_PTR = &KEY;
                for(int j = 0; j < Tree->GetSize();j++){
                    if(Tree->NextIteration(&KEY_PTR).GetScore() == Score)
                        NumOfPlayers++;
                    Total++;
                }
            }
        }
        if(Total == 0)
            throw FailureException();
        *player = (double(NumOfPlayers)/double(Total))*100;
        return;
    }

    int Index = FindGroupFather(GroupID);

    Groups[Index].GP->EnterWaitingPlayers();
    *player = Groups[Index].GP->GetPercentInBounds(Score,LowerLevel,HigherLevel);

}

void SquidGame::AvgHighestPlayerLevelByGroup(int GroupID, int m, double *AVG) {

    EnterWaitingPlayers();
    if(GroupID == -1){

        if(CurrentTotalPlayers < m)
            throw FailureException();
        Level.SetLastIterator();
        int * Array = new int[m];
        int Last = 0;
        int key,*key_ptr = &key;
        int Total = 0;

        for(int i = 0; i < Level.GetSize(); i++){
            BST<int,Player>* Tree = Level.PreIteration(&key_ptr);
             if(Tree->GetSize() >= m-Last){
                 for(int j = 0; j < Tree->GetSize()+1; j++){
                     if(Last + j == m)
                         goto OUT;
                     Array[Last + j] = key;
                 }
             }
             else{
                 for(int j = 0; j < Tree->GetSize(); j++){
                     if(Last + j == m)
                         goto OUT;
                     Array[Last + j] = key;
                 }
                 Last += Tree->GetSize();
             }
        }
        OUT:
        for(int i = 0; i < m; i++)
            Total += Array[i];

        *AVG = double(Total)/double(m);
        delete[] Array;
        return;
    }

    Groups[FindGroupFather(GroupID)].GP->EnterWaitingPlayers();
    *AVG = Groups[FindGroupFather(GroupID)].GP->AvargeHighestPlayer(m);
}

void SquidGame:: SortArray(int* arr,int size){
    int temp;
    for(int i=0;i<size;i++)
    {
        for(int j=i+1;j<size;j++)
        {
            if(arr[i]>arr[j])
            {
                temp =arr[i];
                arr[i]=arr[j];
                arr[j]=temp;
            }
        }
    }
}

void SquidGame::MergeGroups(int Group1, int Group2) {

    FlippedTreeNode* HostRoot,*OtherRoot;

    int Hostindex = FindGroupFather(Group1);
    int ToBeUnitedIndex = FindGroupFather(Group2);

    HostRoot = &Groups[Hostindex];
    OtherRoot = &Groups[ToBeUnitedIndex];

    if(HostRoot == OtherRoot)
        return;

    HostRoot->GP->MergeGroup(OtherRoot->GP);
    OtherRoot->father = HostRoot;
    HostRoot->TotalSons += OtherRoot->TotalSons+1;
}

void SquidGame::InsertPlayer(int key, Player *player) {
    int HashFunction = key%HashFunctionMod;
    int StepFunction = 1+(key%5);
    int k = 0;
    while(true){
        int index = (HashFunction+k*StepFunction) % PlayersSize;
        if(AllPlayers[index] == nullptr){
            deletedPlayersArray[index] = false;
            AllPlayers[index] = player;
            player->SetID(key);
            CurrentTotalPlayers++;
            return;
        }
        else if(AllPlayers[index]->GetID() == key)
            throw FailureException();
        k++;
    }
}

void SquidGame::InsertWait(int key, Player *player) {
    int HashFunction = key%HashFunctionMod;
    int StepFunction = 1+(key%5);
    int k = 0;
    while(true){
        int index = (HashFunction+k*StepFunction) % WaitingSize;
        if(WaitingRoom[index] == nullptr){
            deletedWaitingArray[index] = false;
            WaitingRoom[index] = player;
            player->SetID(key);
            CurrentTotalWaiting++;
            return;
        }
        else if(WaitingRoom[index]->GetID() == key)
            throw FailureException();
        k++;
    }
}

int SquidGame::FindNextPrime(int start) {
    int PrimeContainer[start];
    int size = 1;
    int i = 3;
    PrimeContainer[0] = 2;
    while(true){
        int isPrime = true;
        for(int j = 0; j < size; j++){
            if(i % PrimeContainer[j] == 0){
                isPrime = false;
                break;
            }
        }
        if(isPrime) {
            PrimeContainer[size] = i;
            size++;
            if(i > start)
                return i;
        }
        i += 2 ;
    }
}

int SquidGame::FindPlayerHash(int ID) {

    int HashFunction = ID%HashFunctionMod;
    int StepFunction = 1+(ID%5);
    int k = 0;

    while(true){
        int index = (HashFunction+k*StepFunction) % PlayersSize;
        if(AllPlayers[index] == nullptr && !deletedPlayersArray[index]){
            return -1;
        }
        else if(AllPlayers[index] != nullptr){
            if(AllPlayers[index]->GetID() == ID)
                return index;
        }
        k++;
    }

}

int SquidGame::FindWaitingHash(int ID) {

    int HashFunction = ID%HashFunctionMod;
    int StepFunction = 1+(ID%5);
    int k = 0;

    while(true){
        int index = (HashFunction+k*StepFunction) % WaitingSize;
        if(WaitingRoom[index] == nullptr && !deletedWaitingArray[index]){
            return -1;
        }
        else if(WaitingRoom[index] != nullptr){
            if(WaitingRoom[index]->GetID() == ID)
                return index;
        }
        k++;
    }

}

void SquidGame::EnterWaitingPlayers() {

    for(int i = 0; i < WaitingSize; i++){
        if(WaitingRoom[i]){
            try {
                Level.Find(0)->insert(WaitingRoom[i]->GetID(), *WaitingRoom[i]);
            }catch(BST<int,BST<int,Player>*>::KeyNotFound &e){
                Level.insert(0,new BST<int,Player>);
                Level.Find(0)->insert(WaitingRoom[i]->GetID(), *WaitingRoom[i]);
            }
            WaitingRoom[i] = nullptr;
            deletedWaitingArray[i] = false;
        }
    }

}

int SquidGame::FindGroupFather(int GroupID) {

    if(Groups[GroupID].father == nullptr){
        return GroupID;
    }
    else if(Groups[GroupID].father->father == nullptr){
        return Groups[GroupID].father->index;
    }else{
        FlippedTreeNode* Node,*Temp,* Root = nullptr;

        Node = &Groups[GroupID];
        for(int i = 0; i < NumOfGroups; i++){
            if(Root)
                break;
            if(Node->father == nullptr)
                Root = Node;
            Node = Node->father;
        }
        Node = &Groups[GroupID];
        for(int i = 0; i < NumOfGroups; i++){
            if(Node->father == nullptr)
                break;
            Temp = Node;
            Node->TotalSons -= i;
            Node = Node->father;
            Temp->father = Root;
        }
        return Root->index;
    }

}