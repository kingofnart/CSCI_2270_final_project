// Author: CS2270 Spring 2019
// Recitation: 104
// Homework 1 - Problem #1

/****************************************************************/
/*                    MovieTree Implementation                  */
/****************************************************************/
/* LEAVE THIS FILE AS IS! DO NOT MODIFY ANYTHING! =]            */
/****************************************************************/

#include "commonWords.hpp"
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
#include <time.h>
#include <chrono>

using namespace std;
using namespace std::chrono;

int split (string str, char c, string array[], int size) // Provided Function
     {
        if (str.length() == 0) {
             return 0;
         }
        string word = "";
        int count = 0;
        str = str + c;
        for (int i = 0; i < str.length(); i++)
        {
            if (str[i] == c)
            {
                if (word.length() == 0)
                    continue;
                array[count++] = word;
                word = "";
            } else {
                word = word + str[i];
            }
        }
        return count ;
     }

bool readCommonWords (string filename, HashTable * hashing) // Add the Common Words
{
    ifstream vocabulary;
    vocabulary.open (filename); // Open the File
    if (vocabulary.is_open ())
    {
        int i = 0;
        string word = "";
        while (getline (vocabulary, word)) // While Words can be Read
        {
          // Add the Word to the Common Words Hash Table
            // vocab [i] = word; // Set the Vocab in the Array
            hashing -> addWord (word);
            // cout << word << endl;
            // ++i;
        }
        vocabulary.close (); // Close the File
        return true;
    }
    return false;
}

int readMisspellings (string filename, BST * treeing, HashTable * hashing) // Add the Misspellings
{
  // cout << "started" << endl;
    ifstream misspelling;
    // cout << "testing" << endl;
    misspelling.open (filename); // Open the File
    if (misspelling.is_open())
    {
      // cout << "opened" << endl;
        int i = 0;
        string word = "";
        string words2 [2]; // Split Correct/Corrections
        string words3 [25]; // Split Corrections
        while (getline (misspelling, word))
        {
          // cout << "reading" << endl;
          // if (i == 0)
          // {
          //   cout << word << endl;
          // }
            split (word, ',', words2,  2); // Split Correct/Corrections
            // misspel [i] [0] = words2 [0]; // Set the Correct Word
            // cout << misspel [i] [0];
            // cout << " 1: " << words2 [0].length () << " 2: " << words2 [1].length() << endl;
            string correction = words2 [1];
            // cout << correction << endl;
            bool check = false;
            for (int z = 0; z < correction.length(); z++) // For the length of the corrections
            {
                if (correction [z] == '|') // If there is more than one
                {
                    check = true;
                }
            }
            // cout << " " << check;
            if (!check) // If there is one Correction
            {
              // cout << words2 [0] << endl;
                // misspel [i] [1] = words2 [1]; // Set the Correction
                treeing -> addNode (words2 [1], words2 [0]); // Set the Correction
                // cout << words2 [0] << endl;
                // cout << " " << misspel [i] [1] << endl;
                ++i;
            }
            else // If there is more than one Correction
            {
                for (int z = 0; z < 25; z++) // Empty the Corrections Split String
                {
                    words3 [z] = "";
                }
                split (words2 [1], '|', words3,  25); // Split the Corrections
                for (int z = 0; z < 25; z++)
                {
                    if (words3 [z].length() > 0) // While there are Corrections
                    {
                      // cout << "here";
                        // misspel [i] [z+1] = words3 [z]; // Set the Corrections
                        treeing -> addNode (words3 [z], words2 [0]); // Set the Correction
                        // cout << " " << misspel [i] [z+1] << " ";
                        ++i;
                    }
                    else // End Setting Corrections
                    {
                        z = 25;
                    }
                }
                // cout << endl;
            }
            bool verify = false;
            if (hashing -> isInTable (words2 [0])) // If the Misspelling Record is in the HashTable
            {
              verify = true; // The Word Exists
            }
            if (!verify) // If the word does not exist
            {
                // cout << misspel [z] [0] << endl;
                // vocab [3006 + count] = misspel [z] [0]; // Add the Word to Vocab
                hashing -> addWord (words2 [0]); // Add the Word to Vocab
                // ++count;
            }
             // ++i;
        }
        // cout << "ended";
        // int count = 0;
        // for (int z = 0; z < 3000; z++) // For the Number of Misspelling Words
        // {
        //     bool verify = false;
        //     // for (int i = 0; i < 4000; i++) // For the Number of Vocab Words
        //     // {
        //     //     if (misspel [z][0] == vocab [i])
        //     //     {
        //     //         verify = true; // The word exists in Vocab
        //     //     }
        //     // }
        //     if (hashing.isInTable ())
        //     if (!verify) // If the word does not exist
        //     {
        //         // cout << misspel [z] [0] << endl;
        //         vocab [3006 + count] = misspel [z] [0]; // Add the Word to Vocab
        //         ++count;
        //     }
        // }
        // cout << "count: " << count;
        // cout << "vocab 3007 " << vocab [3006] << endl;
        misspelling.close (); // Close the File
        // cout << "here";
        return i;
    }
    else
    {
        cout << "misspelling.txt does not exist" << endl; // The File does not Exist
        return false;
    }
  }

  string checkWord (string word, HashTable * hashing, BST * treeing)
  {
    // cout << "called";
      bool verify = false;
      bool incorrect = false;
      string newWord = "";
      if (hashing -> isInTable (word)) // If the Word is a Common Word
      {
        // cout << "In Table: " << word <<endl;
        return word; // Return the Word
      }
      else
      {
        string correction = treeing -> searchKey (word);
        if (correction != "") // If the Word is in the Misspellings
        {
          // cout << "In Tree: " << word <<endl;
          return correction; // Return the correction
        }
        else
        {
          // cout << "here";
          return "unknown";
        }
        // return newWord;
  }
}

string lowerCase (string phrase) // Make a word Lowercase
{
    string newWord = "";
    char lower;
    for (int i = 0; i < phrase.length(); i++) // For the Length of the Phrase
    {
        if (phrase [i] >= 'A' && phrase [i] <= 'Z') // If the character is Capital
        {
            lower = char(tolower (phrase [i])); // Set to a Lower Character
            newWord = newWord + lower; // Add to the New Word
        }
        else
        {
            // cout << "found unknown!";
            newWord = newWord + phrase [i]; // Otherwise add to the New Word
        }
    }
    return newWord; // Return the Word
}

// bool readMisspelling (string filename, HashTable hashing)
// {
//   cout << "hello";
//   return true;
// }

int main (int argc, char *argv[])
{
  double startTime, endTime;
  double execTime;
  string phrase = ""; // The phrase that is entered
  string newPhrase = ""; // The corrected phrase
  string finalPhrase = ""; // The final phrase

  //Read in the Common Words File
  // readCommonWords (argv [1]);
  HashTable hashing (700); // Create a HashTable
  // cout << argv [1] << endl;
  readCommonWords (argv [1], &hashing);
  // HashTable hashing2 (100);
  // //Read in the Misspellings File
  // readMisspellings (argv [1]);
  cout << "Read " << hashing.getNumItems () << " word from " << argv [1] << endl;

  BST treeing;
  cout << "Read " << readMisspellings (argv [2], &treeing, &hashing) << " lines from " << argv [2] << endl;
  // cout << treeing.searchKey ("athenean");
  // treeing.printTree ();

  // if (!readMisspelling (argv [2], hashing2))
  // {
  //   return 0;
  // }

  cout << "Enter the phrase you would like to correct: "; // Get the phrase
  // // getline (cin, phrase);
  //
  // // Test Cases
  phrase = "...,, $%!HELLO WORLD! My firends are qwer.";
  // phrase = "Do    you knwo youself?";
  // phrase = "I loev C++";
  // phrase = "!!! A lightyear is a distaNCe UiTN!!!";
  // phrase = ", xxx Thsi is 21 centruy NOW!!!";
  // phrase = "xxx @ yyy @ zzz";
  //
  cout << endl << phrase << endl;
  // // Set the phrase from the first word
  for (int i = 0; i < phrase.length(); i++) // For the Phrase
  {
      if (phrase [i] >= 'a' && phrase [i] <= 'z') // Once there is a letter
      {
          newPhrase = phrase.substr (i); // Set the New Phrase from the Letter
          i = phrase.length(); // End the Traversing
      }
      else if (phrase [i] >= 'A' && phrase [i] <= 'Z') // Once there is a Capital Letter
      {
          newPhrase = phrase.substr (i); // Set the New Phrase from the Letter
          i = phrase.length(); // End the Traversing
      }
  }
  //
  // // Make the phrase lowercase
  newPhrase = lowerCase (newPhrase); // Make the phrase lowercase

  // Remove the double spaces in the phrase
  string changePhrase = "";
  bool space = false;
  for (int i = 0; i < newPhrase.length(); i++) // For the Length of the Phrase
  {
      if (newPhrase [i] >= 'a' && newPhrase [i] <= 'z') // If there is a Letter
      {
          space = false;
          changePhrase = changePhrase + newPhrase [i]; // Add the Letter to the new Phrase
      }
      else if (newPhrase [i] != ' ') // If there is Punctuation
      {
          space = false;
          changePhrase = changePhrase + newPhrase [i]; // Add to the Phrase
      }
      else // If there is a Space
      {
        // cout << "spaced"
          if (newPhrase [i] == ' ' && space == false) // If there has not been a Space Before
          {
              space = true; // One Space has been Read
              changePhrase = changePhrase + ' '; // Add the Space
          }
      }
  }

  // Check each word in the phrase and add to the Final Phrase

  auto start = high_resolution_clock::now();
  changePhrase = changePhrase + '.'; // Read the Last Word with the Punctuation
  int position = 0;
  string changeWord = "";
  // cout << changePhrase << endl;
  // cout << changePhrase.length () << endl;
  for (int i = 0; i < changePhrase.length(); i++)
  {
    // cout << i << endl;
      if (changePhrase [i] >= 'a' && changePhrase [i] <= 'z') // If there is a Letter
      {
        // cout << "checking";
          changeWord = changeWord + changePhrase [i]; // Add the Letter
          // cout << changePhrase [i] << " ";
      }
      else if (changePhrase [i] == ' ') // If there is a space
      {
          // cout << changePhrase.substr (position, (i - position)) << endl;
          position = i + 1;
          // cout << checkWord (changeWord, vocab, misspel) << " ";
          // cout << changeWord << " ";
          // changeWord = "";
          // cout << "Space, Word: " << changeWord << endl;
          if (changeWord != "")
          {
            finalPhrase = finalPhrase + checkWord (changeWord, &hashing, &treeing); // Add the Looked Up Word
            // cout << checkWord (changeWord, hashing, treeing);
            changeWord = ""; // Clear the Word
            finalPhrase = finalPhrase + ' '; // Add the Space
          }
          // finalPhrase = finalPhrase + checkWord (changeWord, &hashing, &treeing); // Add the Looked Up Word
          // // cout << checkWord (changeWord, hashing, treeing);
          // changeWord = ""; // Clear the Word
          // finalPhrase = finalPhrase + ' '; // Add the Space
          // cout << finalPhrase << endl;
      }
      else if (changePhrase [i] < 'a' || changePhrase [i] > 'z') // If Another Symbol
      {
          position = i + 1;
          // cout << checkWord (changeWord, vocab, misspel) << " ";
          // cout << changeWord << " ";
          // changeWord = "";
            // cout << "Punctuation, Word: " << changeWord << endl;
            if (changeWord != "")
            {
              finalPhrase = finalPhrase + checkWord (changeWord, &hashing, &treeing); // Add the Looked Up Word
              changeWord = ""; // Clear the Accumulated Word
              finalPhrase = finalPhrase + changePhrase [i]; // Add the Symbol
            }
            else
            {
              finalPhrase = finalPhrase + changePhrase [i]; // Add the Symbol
            }
          // finalPhrase = finalPhrase + checkWord (changeWord, &hashing, &treeing); // Add the Looked Up Word
          // changeWord = ""; // Clear the Accumulated Word
          // finalPhrase = finalPhrase + changePhrase [i]; // Add the Symbol
          // cout << finalPhrase << endl;
      }
      // else if (changePhrase [changePhrase.length ()] >= 'a' && changePhrase [changePhrase.length ()] <= 'z')
      // {
      //     finalPhrase = finalPhrase + checkWord (changeWord, vocab, misspel);
      //     // changeWord = "";
      //     // finalPhrase = finalPhrase + changePhrase [i];
      // }
  }
  auto stop = high_resolution_clock::now();
  auto duration = duration_cast<microseconds>(stop - start);
  finalPhrase [finalPhrase.length()-1] = ' '; // Remove the Punctutation
  cout << endl << finalPhrase << endl; // Display the Word
  // cout << execTime << endl;
  cout << duration.count() << endl;
  // cout << changePhrase << endl;
}
