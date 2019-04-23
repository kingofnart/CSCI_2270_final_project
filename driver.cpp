#include "BST.hpp"
#include "hash.hpp"
#include <iostream>
#include <fstream>
#include <chrono>

using namespace std;
using namespace std::chrono;

string normalize(string input);
string removeSymbols(string input);
string removeSpaces(string input);
void displayMenu();
void printCorrectPhrase(string phrase, BST tree, HashTable table);

int main(int argc, char* argv[]){ //misspellings file; 10000 comomon words; misspelled document
  if(argc == 4){
    //instantiate hash tables & binary search tree
    BST BSTree;
    HashTable SmallTable(1000);
    HashTable BigTable(1000);
    //add mispellings to BST and correct spelling to hash table (all words to BigTable)
    ifstream misspelledFile;
    misspelledFile.open(argv[1]); // Open the File
    if(misspelledFile.is_open()){
      string line, s, correct;
      while(getline(misspelledFile, line)){
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
            cnt++; //increment count (if not 0, word is misspelled)
          }
          else{
            s += line[i];
          }
        }
        //add last word in line
        BSTree.addNode(s, correct);
        BigTable.addWord(s, correct);
        s = "";
      }
      //add common words file to hash tables
      ifstream commonWordsFile;
      commonWordsFile.open(argv[2]);
      while(getline(commonWordsFile, line)){
        //new word on each line
        SmallTable.addWord(line, "");
        BigTable.addWord(line, line);
        //s = "";
      }
      string phrase, newPhrase;
      //******************timing hashTable vs hashTable and BST*****************
      //************************hashTable and BST ******************************
      auto start = high_resolution_clock::now();
      ifstream inputFile1;
      inputFile1.open(argv[3]);
      while(getline(inputFile1, line)){
        string normalWord = normalize(line);
        if(!SmallTable.isInTable(normalWord)){
          string search = BSTree.searchKey(normalWord);
          if(search == ""){
            newPhrase += normalWord + " (unkown) ";
          }
          else{
            newPhrase += search + " ";
          }
        }
        else{
          newPhrase += normalWord + " ";
        }
        //s = "";
      }
      //s = "";
      cout << newPhrase.length() << endl;
      newPhrase = "";
      auto middle = high_resolution_clock::now();
      // only hashTable: *******************************************************
      ifstream inputFile2;
      inputFile2.open(argv[3]);
      while(getline(inputFile2, line)){
        string normalWord = normalize(line);
        if(!BigTable.isInTable(normalWord)){
          newPhrase += normalWord + " (unkown) ";
        }
        else{
          newPhrase += (BigTable.searchTable(normalWord))->correctSpelling + " ";
        }
      }
      cout << newPhrase.length() << endl;
      newPhrase = "";
      auto stop = high_resolution_clock::now();
      auto duration1 = duration_cast<microseconds>(middle - start);
      auto duration2 = duration_cast<microseconds>(stop - middle);
      cout << "BST & Hash Table count: " << duration1.count() << " (microseconds)" << endl;
      cout << "Hash Table only count: " << duration2.count() << " (microseconds)" << endl;
      // Test Cases
      phrase = "...,, $%!HELLO WORLD! My firends are qwer.";
      cout << "Original phrase: " << endl << phrase << endl;
      printCorrectPhrase(phrase, BSTree, SmallTable);
      phrase = "Do    you knwo youself?";
      cout << "Original phrase: " << endl << phrase << endl;
      printCorrectPhrase(phrase, BSTree, SmallTable);
      phrase = "I loev C++";
      cout << "Original phrase: " << endl << phrase << endl;
      printCorrectPhrase(phrase, BSTree, SmallTable);
      phrase = "!!! A lightyear is a distaNCe UiTN!!!";
      cout << "Original phrase: " << endl << phrase << endl;
      printCorrectPhrase(phrase, BSTree, SmallTable);
      phrase = ", xxx Thsi is 21 centruy NOW!!!";
      cout << "Original phrase: " << endl << phrase << endl;
      printCorrectPhrase(phrase, BSTree, SmallTable);
      phrase = "xxx @ yyy @ zzz";
      cout << "Original phrase: " << endl << phrase << endl;
      printCorrectPhrase(phrase, BSTree, SmallTable);
      string choice = "1";
      while(stoi(choice) != 2){
        displayMenu();
        getline(cin, choice);
        switch(stoi(choice)){
          case 1:
          cout << "Enter the phrase you would like to correct: " << endl;
          getline(cin, phrase);
          printCorrectPhrase(phrase, BSTree, SmallTable);
          newPhrase = "";
          break;

          case 2:
          cout << "Goodbye!" << endl;
          break;
        }
      }

    } //if(file.is_open) '}'
    else{ //file didnt open
      cout << argv[1] << " does not exist" << endl;
    }
  }
  return 0;
}

string removeSymbols(string input){
  string output;
  for(int i=0; i<input.length(); i++){
    if(input[i] >= 'a' && input[i] <= 'z'){
      output += input[i];
    }
    else if(input[i] >= 'A' && input[i] <= 'Z'){
      output += input[i];
    }
    else if(input[i] == 39 || input[i] == 32){
      output += input[i];
    }
  }
  return output;
}

string removeSpaces(string input){
  string output;
  for(int i=0; i<input.length(); i++){
    if(input[i] == ' '){
      output += ' ';
      while(input[i+1] == ' '){
        i++;
      }
    }
    else{
      output += input[i];
    }
  }
  return output;
}

string normalize(string input){
  string output;
  input = removeSymbols(input);
  input = removeSpaces(input);
  for(int i=0; i<input.length(); i++){
    if(input[i] >= 'A' && input[i] <= 'Z'){
      output += tolower(input[i]);
    }
    else{
      output += input[i];
    }
  }
  return output;
}

void printCorrectPhrase(string phrase, BST tree, HashTable table){
  string stdPhrase = normalize(phrase);
  string s, newPhrase;
  for(int u=0; u<stdPhrase.length(); u++){
    if(stdPhrase[u] == ' '){
      if(!table.isInTable(s)){
        string search = tree.searchKey(s);
        if(search == ""){
          newPhrase += s + " ";
          bool number = true;
          for(int i=0; i<s.length(); i++){
            if(s[i] < 48 || s[i] > 57){
              number = false;
            }
          }
          if(!number){
            newPhrase += "(unkown) ";
          }
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
      s += stdPhrase[u];
    }
  }
  if(!table.isInTable(s)){
    string search = tree.searchKey(s);
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
}

void displayMenu(){
  cout << "============Menu============" << endl;
  cout << "1. Input a phrase you would like corrected" << endl;
  cout << "2. Quit" << endl;
}
