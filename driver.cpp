#include "BST.hpp"
#include "hash.hpp"
#include <iostream>
#include <fstream>
#include <chrono>

using namespace std;
using namespace std::chrono;

string normalize(string input);

int main(int argc, char* argv[]){
  if(argc == 2){
    BST BSTree;
    HashTable SmallTable(1000);
    HashTable BigTable(1000);
    ifstream inputFile;
    inputFile.open(argv[1]); // Open the File
    if(inputFile.is_open()){
      string line, s, correct;
      while(getline(inputFile, line)){
        int cnt = 0;
        for(int i=0; i<line.length(); i++){
          if(line[i] == ',' || line[i] == '|'){ // end of word add to main hash table
            if(cnt == 0){ // correctly spelled word add to small hash table
              SmallTable.addWord(s, "");
              correct = s;
            }
            else{ // misspelled word add to BST
              BSTree.addNode(s, correct);
            }
            BigTable.addWord(s, correct);
            s = "";
          }
          else{
            s += line[i];
          }
        }
        BSTree.addNode(s, correct);
        BigTable.addWord(s, correct);
        s = "";
      }
      string phrase, newPhrase;
      cout << "Enter the phrase you would like to correct: " << endl;
      getline(cin, phrase);
      phrase = normalize(phrase);
      for(int u=0; u<phrase.length(); u++){
        if(phrase[u] == ' '){
          //cout << "s: <" << s << "> ";
          if(!SmallTable.isInTable(s)){
            string search = BSTree.searchKey(s);
            if(search == ""){
              newPhrase += s + " (unkown) ";
            }
            else{
              newPhrase += search + " ";
            }
          }
          else{
            newPhrase += s + " ";
          }
          s = "";
        }
        else{
          s += phrase[u];
        }
      }
      if(!SmallTable.isInTable(s)){
        string search = BSTree.searchKey(s);
        if(search == ""){
          newPhrase += s + " (unkown)";
        }
        else{
          newPhrase += search;
        }
      }
      else{
        newPhrase += s;
      }
      s = "";
      cout << "Your corrected phrase:" << endl;
      cout << newPhrase << endl;
      newPhrase = "";
      //timing hashTable vs hashTable and BST **********************************
      //hashTable and BST:
      auto start = high_resolution_clock::now();
      ifstream inputFile1;
      inputFile1.open(argv[1]);
      while(getline(inputFile1, line)){
        //cout << newPhrase.length() << " -- ";
        for(int p=0; p<line.length(); p++){
          if(line[p] == ',' || line[p] == '|'){
            if(!SmallTable.isInTable(s)){
              string search = BSTree.searchKey(s);
              if(search == ""){
                newPhrase += s + " (unkown) ";
              }
              else{
                newPhrase += search + " ";
              }
            }
            else{
              newPhrase += s + " ";
            }
            s = "";
          }
          else{
            s += line[p];
          }
        }
        if(!SmallTable.isInTable(s)){
          string search = BSTree.searchKey(s);
          if(search == ""){
            newPhrase += s + " (unkown)";
          }
          else{
            newPhrase += search;
          }
        }
        else{
          newPhrase += s;
        }
        s = "";
      }
      s = "";
      cout << newPhrase.length() << endl;
      newPhrase = "";
      auto middle = high_resolution_clock::now();
      // only hashTable:
      ifstream inputFile2;
      inputFile2.open(argv[1]);
      while(getline(inputFile2, line)){
        //cout << newPhrase.length() << " -- ";
        for(int y=0; y<line.length(); y++){
          if(line[y] == ',' || line[y] == '|'){
            if(!BigTable.isInTable(s)){
              newPhrase += s + " (unkown) ";
            }
            else{
              newPhrase += (BigTable.searchTable(s))->correctSpelling + " ";
            }
            s = "";
          }
          else{
            s += line[y];
          }
        }
        if(!BigTable.isInTable(s)){
          newPhrase += s + " (unkown) ";
        }
        else{
          newPhrase += (BigTable.searchTable(s))->correctSpelling + " ";
        }
      }
      s = "";
      cout << newPhrase.length() << endl;
      newPhrase = "";
      auto stop = high_resolution_clock::now();
      auto duration1 = duration_cast<microseconds>(middle - start);
      auto duration2 = duration_cast<microseconds>(stop - middle);
      cout << "BST & Hash Table count: " << duration1.count() << endl;
      cout << "Hash Table only count: " << duration2.count() << endl;
    } //if(file.is_open) '}'
    else{ //file didnt open
      cout << argv[1] << " does not exist" << endl;
    }
    // else{
    //   cout << "not enough command line arguments" << endl;
    // }
  }
  return 0;
}

string normalize(string input){
  string output;
  for(int i=0; i<input.length(); i++){
    if(input[i] >= 'A' || input[i] <= 'Z'){
      output += tolower(input[i]);
    }
    else if(input[i] = ' '){
      output += ' ';
      while(input[i+1] == ' '){
        i++;
      }
    }
    //only keep letters and apostrophes
    else if((input[i] >= 'a' && input[i] <= 'z') || input[i] == 39){
      output += input[i];
    }
  }
  return output;
}
