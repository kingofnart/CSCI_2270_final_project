#include "hash.hpp"
#include <iostream>
#include <cmath>
#include <cstdlib>
#include <unistd.h>
#include <stdio.h>
#include <string>
#include <fstream>
#include <vector>
#include <string>
#include <iomanip>
#include <sstream>
#include <iostream>


HashTable :: HashTable(int newHashTableSize){
    hashTableSize = newHashTableSize;
    hashTable = new vocab*[hashTableSize];
    numItems = 0;
    for(int i = 0; i < hashTableSize; i++){
        hashTable[i] = nullptr;
    }
}

HashTable :: ~HashTable(){
    for(int i = 0; i < hashTableSize; i++){
        vocab* entry = hashTable[i];
        while(entry != nullptr){
            vocab* previous = entry;
            entry = entry -> next;
            delete previous;
        }
    }
    delete[] hashTable;
}

void HashTable :: addWord(string word, string mispelling){
    unsigned int hashValue = getHash(word);
    if(!searchTable(word)){
        vocab* newVocab = new vocab;
        newVocab->word = word;
        newVocab->mispelling = mispelling;
        newVocab->next = nullptr;
        
        if(hashTable[hashValue] == nullptr){
            hashTable[hashValue] = newVocab;
        }
        else{
            newVocab->next = hashTable[hashValue];
            hashTable[hashValue] = newVocab;
        }
        numItems++;
    }
}

bool HashTable :: isInTable(string word){
    vocab* temp = searchTable(word);
    
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

vocab* searchItem(string key, vocab** table, int hashTableSize){ //helper function to search
    unsigned int hashValue = 5381;
    
    for(unsigned int i = 0; i < key.length(); i++){
        hashValue = hashValue*33 + key[i];
    }
    hashValue = hashValue % hashTableSize;
    
    vocab* temp = table[hashValue]; //this pointer points at the head 
    while(temp != nullptr){
        if(temp->word == key){ //once you find the pointer with the correct word then it's good
            return temp;
        }
        temp = temp -> next; //keep traversing till you find it
    }
    return nullptr;
}

vocab* HashTable :: searchTable(string word){
    return searchItem(word, hashTable, hashTableSize);
}
