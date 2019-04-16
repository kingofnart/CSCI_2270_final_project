#include <iostream>
#include <fstream>
#include "commonWords.hpp"
using namespace std;

int main(int argc, char* argv[]){
  if(argc == 2){
    ifstream myFile;
    myFile.open(argv[1]);
    if(myFile.is_open()){
      string line;
      getline(myFile, line);
      BST treeOfLife(line);
      while(getline(myFile, line)){
        treeOfLife.addNode(line);
      }
    }
  }
  return 0;
}
