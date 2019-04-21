#include <string>

using namespace std;

struct HNode
{
    string word; // The Word
    string correctSpelling; // misspelled word
    HNode* next; // The Next Word
};

class HashTable {
  public:
    HashTable(int newHashTableSize);
    ~HashTable();
    void addWord(string word, string correctSpelling); // Add a Vocab Word
    bool isInTable(string word); // Search for a Word in Vocabulary
    HNode* searchTable(string word); // Search for the location of a word

  private:
    /* member functions */
    unsigned int getHash(string word); // The Hashing Function
    HNode* searchItem(string key, HNode** table);

    /* instance variables */
    HNode** hashTable; // Hashtable of vocab word (possibly a pointer) I think it needs to be a pointer but unsure
    int hashTableSize; // The Table's Size
    int numItems;
};
