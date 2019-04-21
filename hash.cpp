#include "hash.hpp"
#include <iostream>


HashTable :: HashTable(int newHashTableSize){
    hashTableSize = newHashTableSize;
    hashTable = new HNode*[hashTableSize];
    numItems = 0;
    for(int i = 0; i < hashTableSize; i++){
        hashTable[i] = nullptr;
    }
}

HashTable :: ~HashTable(){
    for(int i = 0; i < hashTableSize; i++){
        HNode* entry = hashTable[i];
        while(entry != nullptr){
            HNode* previous = entry;
            entry = entry->next;
            delete previous;
        }
    }
    delete[] hashTable;
}

void HashTable :: addWord(string word, string correctSpelling){
    unsigned int hashValue = getHash(word);
    if(!searchTable(word)){
        HNode* newHNode = new HNode;
        newHNode->word = word;
        newHNode->correctSpelling = correctSpelling;
        newHNode->next = nullptr;

        if(hashTable[hashValue] == nullptr){
            hashTable[hashValue] = newHNode;
        }
        else{
            newHNode->next = hashTable[hashValue];
            hashTable[hashValue] = newHNode;
        }
    }
}

bool HashTable :: isInTable(string word){
    HNode* temp = searchTable(word);
    if(temp != nullptr){
        return true;
    }
    else{
        return false;
    }
}

unsigned int HashTable :: getHash(string word){ //if this the hash we want to use? It is supposed to be most efficient
    unsigned int hash = 5381;
    for(unsigned int i = 0; i < word.length(); i++){
        hash = hash*33 + word[i];
    }
    hash = hash % hashTableSize;
    return hash;
}

HNode* HashTable::searchItem(string key, HNode** table){ //helper function to search
  int hashValue = getHash(key);
  HNode* temp = table[hashValue]; //this pointer points at the head
  while(temp != nullptr){
    //cout << temp->word << " ";
    if(temp->word == key){ //once you find the pointer with the correct word then it's good
        return temp;
    }
    temp = temp-> next; //keep traversing till you find it
  }
  return nullptr;
}

HNode* HashTable :: searchTable(string word){
    return searchItem(word, hashTable);
}
