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
}

Group::~Group() {
    delete[] Waiting;
    delete[] deletedArray;
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

}

void Group::EnterWaitingPlayers() {

    for(int i = 0; i < Size; i++){
        if(Waiting[i]){
            Players.insert(Waiting[i]->GetID(),*Waiting[i]);
            Waiting[i] = nullptr;
            deletedArray[i] = false;
        }
    }

}