#include "Group.h"

Group::Group(int id){
    ID = id;
    Waiting = new Player*[Size];
    deletedArray = new bool[Size];
    CurrentTotalPlayers = 0;
    DeleteActionCounter = 0;
    for(int i = 0; i < Size;i++){
        Waiting[i] = nullptr;
        deletedArray[i] = false;
    }
    Levels.insert(0,new BST<int,Player>);
}

Group::~Group() {
    delete[] Waiting;
    delete[] deletedArray;
    Levels.ResetIterator();
    int Key,*ket_ptr = &Key;
    for(int i = 0; i < Levels.GetSize(); i++){
       delete &Levels.NextIteration(&ket_ptr);
    }
}

void Group::AddPlayer(int ID, int score) {
    InsertHash(ID,new Player(score,ID,this->ID));

    if(double(CurrentTotalPlayers)/double(Size) > ResizeRatio){
        int size = FindNextPrime(Size*2);
        auto** NewArray = new Player*[size];
        auto* newDeleteArray = new bool[size];

        for(int i = 0; i < size; i++){
            NewArray[i] = nullptr;
            newDeleteArray[i] = false;
        }

        for(int i = 0; i < Size; i++){
            NewArray[i] = Waiting[i];
            newDeleteArray[i] = deletedArray[i];
        }


        delete[] Waiting;
        delete[] deletedArray;

        Waiting = NewArray;
        deletedArray = newDeleteArray;
        Size = size;
    }
}

void Group::RemovePlayer(int ID) {

    int index = FindHash(ID);

    if(index == -1){
        Players.remove(ID);
        return;
    }


    delete Waiting[index];
    Waiting[index] = nullptr;
    deletedArray[index] = true;
    DeleteActionCounter++;

    if(DeleteActionCounter >= RehashMultiplier*Size){
        auto** NewArray = new Player*[Size];
        DeleteActionCounter = 0;
        HashFunctionMod = Size;
        for(int i=0; i < Size; i++){
            NewArray[i] = nullptr;
            deletedArray[i] = false;
        }
        for(int i=0; i < Size; i++){
            if(Waiting[i] != nullptr){
                int ID = Waiting[i]->GetID();
                int HashFunction = ID%HashFunctionMod;
                int StepFunction = 1+(ID%5);
                int k = 0;
                int HashIndex = (HashFunction+k*StepFunction) % Size;

                while(true){
                    if(NewArray[HashIndex] == nullptr){
                        NewArray[HashIndex] = Waiting[i];
                        break;
                    }
                    k++;
                }

            }
            deletedArray[i] = false;
        }
    }

}

void Group::InsertHash(int key,Player* player) {
    int HashFunction = key%HashFunctionMod;
    int StepFunction = 1+(key%5);
    int k = 0;
    while(true){
        int index = (HashFunction+k*StepFunction) % Size;
        if(Waiting[index] == nullptr){
            deletedArray[index] = false;
            Waiting[index] = player;
            player->SetID(key);
            CurrentTotalPlayers++;
            return;
        }
        else if(Waiting[index]->GetID() == key)
            throw FailureException();
        k++;
    }
}

int Group::FindNextPrime(int start) {
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

int Group::FindHash(int ID) {

    int HashFunction = ID%HashFunctionMod;
    int StepFunction = 1+(ID%5);
    int k = 0;

    while(true){
        int index = (HashFunction+k*StepFunction) % Size;
        if(Waiting[index] == nullptr && !deletedArray[index]){
            return -1;
        }
        else if(Waiting[index] != nullptr){
            if(Waiting[index]->GetID() == ID)
                return index;
        }
        k++;
    }
}

void Group::IncreasePlayerLevel(int ID, int increment) {
    EnterWaitingPlayers();
    Player p1 = this->Players.Find(ID);
    Levels.Find(p1.GetLevel())->remove(ID);
    int newlvl = p1.GetLevel() + increment;
    Players.Find(ID).SetLevel(newlvl);
    p1.SetLevel(newlvl);
    try{
        Levels.Find(newlvl)->insert(ID,p1);
    }catch (BST<int,BST<int,Player>*>::KeyNotFound &e){
        Levels.insert(newlvl,new BST<int,Player>);
        Levels.Find(newlvl)->insert(ID,p1);
    }
}

void Group::UpdatePlayerScore(int ID,int Score){
    EnterWaitingPlayers();
    Player p1 = this->Players.Find(ID);
    Levels.Find(p1.GetLevel())->Find(ID).SetScore(Score);
    Players.Find(ID).SetLevel(Score);
}

int Group::GetPercentInBounds(int score,int LowerLevel,int HigherLevel){
    EnterWaitingPlayers();
    int NumOfPlayers=0,key,*key_ptr = &key;
    Levels.ResetIterator();
    for (int i = 0; Levels.GetSize(); i++) {
        BST<int, Player> *Tree = Levels.NextIteration(&key_ptr);
        if(key < LowerLevel) continue;
        else if( key > HigherLevel) break;
        else{
            Tree->ResetIterator();
            int KEY,*KEY_PTR = &KEY;
            for (int j = 0; j < Tree->GetSize();j++) {
                if(Tree->NextIteration((&KEY_PTR)).GetScore() == score)
                    NumOfPlayers++;
            }
        }
    }
    return NumOfPlayers;
}
int* Group::AvargeHighestPlayer(int NumOfPlayers){
    int* lvls = new int[NumOfPlayers];

}
void Group::EnterWaitingPlayers() {

    for(int i = 0; i < Size; i++){
        if(Waiting[i]){
            Players.insert(Waiting[i]->GetID(),*Waiting[i]);
            Levels.Find(0)->insert(Waiting[i]->GetID(),*Waiting[i]);
            Waiting[i] = nullptr;
            deletedArray[i] = false;
        }
    }

}