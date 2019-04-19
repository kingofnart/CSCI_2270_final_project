#include <string>
#include <cstring>

using namespace std;

struct vocab // Vocab Record
{
    string word; // The Word
    string mispelling;
    vocab* next; // The Next Word
};

class HashTable {
  public:
    HashTable(int newHashTableSize);
    ~HashTable();
    void addMispelling(string mispelling);
    void addWord(string word); // Add a Vocab Word
    bool isInTable(string word); // Search for a Word in Vocabulary

  private:
    /* member functions */
    unsigned int getHash(string word); // The Hashing Function
    vocab* searchTable(string word); // Search for the location of a word
    
    //////Probably not Needed//////////////
    /* instance variables */
    // vocab** hashTable;
    vocab** hashTable; // Hashtable of vocab word (possibly a pointer) I think it needs to be a pointer but unsure 
    int hashTableSize; // The Table's Size
    int numItems;
};
