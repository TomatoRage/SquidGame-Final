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
       delete Levels.NextIteration(&ket_ptr);
    }
    Levels.clear();
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
        Levels.Find(Players.Find(ID).GetLevel())->remove(ID);
        Players.remove(ID);
        CurrentTotalPlayers --;
        return;
    }

    delete Waiting[index];
    Waiting[index] = nullptr;
    deletedArray[index] = true;
    DeleteActionCounter++;
    CurrentTotalPlayers--;


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

    if(Levels.Find(p1.GetLevel())->GetSize() == 0) {
        delete Levels.Find(p1.GetLevel());
        Levels.remove(p1.GetLevel());
    }

    int newlvl = p1.GetLevel() + increment;
    Players.Find(ID).SetLevel(newlvl);
    p1.SetLevel(newlvl);
    try{
        Levels.Find(newlvl)->insert(ID,p1);
    }catch (BST<int,BST<int,Player>*>::KeyNotFound &e){
        Levels.insert(newlvl,new BST<int,Player>);
        Levels.Find(newlvl)->insert(ID,*new Player(p1));
    }
}

void Group::UpdatePlayerScore(int ID,int Score){
    EnterWaitingPlayers();
    Player p1 = this->Players.Find(ID);
    Levels.Find(p1.GetLevel())->Find(ID).SetScore(Score);
    Players.Find(ID).SetScore(Score);
}

double Group::GetPercentInBounds(int score,int LowerLevel,int HigherLevel){
    EnterWaitingPlayers();
    int NumOfPlayers=0,Total = 0,key,*key_ptr = &key;
    Levels.ResetIterator();
    for (int i = 0; i < Levels.GetSize(); i++) {
        BST<int, Player> *Tree = Levels.NextIteration(&key_ptr);
        if(key < LowerLevel) continue;
        else if( key > HigherLevel) break;
        else{
            Tree->ResetIterator();
            int KEY,*KEY_PTR = &KEY;
            for (int j = 0; j < Tree->GetSize();j++) {
                if(Tree->NextIteration((&KEY_PTR)).GetScore() == score)
                    NumOfPlayers++;
                Total++;
            }
        }
    }
    if(Total == 0)
        throw FailureException();
    return (double(NumOfPlayers)/double(Total))*100;
}
double Group::AvargeHighestPlayer(int NumOfPlayers) {
    EnterWaitingPlayers();

    if(NumOfPlayers > Players.GetSize())
        throw FailureException();

    int *Array = new int[NumOfPlayers];
    int Last = 0;
    int Total = 0;
    int key, *key_ptr = &key;

    Levels.SetLastIterator();
    for (int i = 0; i < Levels.GetSize(); i++) {
        BST<int, Player> *Tree = Levels.PreIteration(&key_ptr);
        if (Tree->GetSize() >= NumOfPlayers - Last) {
            for (int j = 0; j < Tree->GetSize()+1; j++) {
                if (Last + j == NumOfPlayers)
                    goto OUT1;
                Array[Last + j] = key;
            }
        } else {
            for (int j = 0; j < Tree->GetSize(); j++) {
                if (Last + j == NumOfPlayers)
                    goto OUT1;
                Array[Last + j] = key;
            }
            Last += Tree->GetSize();
        }
    }
    OUT1:
    for(int i = 0; i < NumOfPlayers;i++){
        Total += Array[i];
    }

    return double(Total)/double(NumOfPlayers);
}

void Group::EnterWaitingPlayers() {

    for(int i = 0; i < Size; i++){
        if(Waiting[i]){
            Players.insert(Waiting[i]->GetID(),*Waiting[i]);
            try {
                Levels.Find(0)->insert(Waiting[i]->GetID(), *Waiting[i]);
            }catch(BST<int,BST<int,Player>*>::KeyNotFound &e){
                Levels.insert(0,new BST<int,Player>);
                Levels.Find(0)->insert(Waiting[i]->GetID(), *Waiting[i]);
            }
            Waiting[i] = nullptr;
            deletedArray[i] = false;
        }
    }

}

void Group::MergeGroup(Group *GP) {

    EnterWaitingPlayers();

    GP->EnterWaitingPlayers();
    GP->Players.ResetIterator();

    int key,*key_ptr = &key;
    int KEY,*KEY_PTR = &KEY;

    for(int i = 0; i < GP->Players.GetSize(); i++){
        Player PPP = GP->Players.NextIteration(&key_ptr);
        Players.insert(key,PPP);
    }

    GP->Levels.ResetIterator();
    for(int i = 0; i < GP->Levels.GetSize(); i++){
        BST<int,Player>* Tree = GP->Levels.NextIteration(&key_ptr);
        try {
            Levels.Find(key);
        }
        catch(...){
            Levels.insert(key,new BST<int,Player>);
        }
        Tree->ResetIterator();
        for(int j = 0; j <  Tree->GetSize();j++){
            Player P = Tree->NextIteration(&KEY_PTR);
            Levels.Find(key)->insert(KEY,P);
        }
    }

}