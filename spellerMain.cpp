// Author: CS2270 Spring 2019
// Recitation: 104
// Homework 1 - Problem #1

/****************************************************************/
/*                    MovieTree Implementation                  */
/****************************************************************/
/* LEAVE THIS FILE AS IS! DO NOT MODIFY ANYTHING! =]            */
/****************************************************************/

#include "commonWords.hpp"
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

using namespace std;

// int split (string str, char c, string array[], int size) // Provided Function
//      {
//         if (str.length() == 0) {
//              return 0;
//          }
//         string word = "";
//         int count = 0;
//         str = str + c;
//         for (int i = 0; i < str.length(); i++)
//         {
//             if (str[i] == c)
//             {
//                 if (word.length() == 0)
//                     continue;
//                 array[count++] = word;
//                 word = "";
//             } else {
//                 word = word + str[i];
//             }
//         }
//         return count ;
//      }
//
// int readCommonWords (string filename) // Add the Common Words
// {
//     ifstream vocabulary;
//     vocabulary.open (filename); // Open the File
//     if (vocabulary.is_open ())
//     {
//         int i = 0;
//         string word = "";
//         while (getline (vocabulary, word)) // While Words can be Read
//         {
//           // Add the Word to the Common Words Hash Table
//             vocab [i] = word; // Set the Vocab in the Array
//             ++i;
//         }
//         vocabulary.close (); // Close the File
//         return true;
//     }
//     return false;
// }
//
// bool readMisspellings (string filename) // Add the Misspellings
// {
//     ifstream misspelling;
//     misspelling.open (filename); // Open the File
//     if (misspelling.is_open())
//     {
//         int i = 0;
//         string word = "";
//         string words2 [2]; // Split Correct/Corrections
//         string words3 [25]; // Split Corrections
//         while (getline (misspelling, word))
//         {
//             split (word, ',', words2,  2); // Split Correct/Corrections
//             misspel [i] [0] = words2 [0]; // Set the Correct Word
//             // cout << misspel [i] [0];
//             // cout << " 1: " << words2 [0].length () << " 2: " << words2 [1].length() << endl;
//             string correction = words2 [1];
//             bool check = false;
//             for (int z = 0; z < correction.length(); z++) // For the length of the corrections
//             {
//                 if (correction [z] == '|') // If there is more than one
//                 {
//                     check = true;
//                 }
//             }
//             // cout << " " << check;
//             if (!check) // If there is one Correction
//             {
//                 misspel [i] [1] = words2 [1]; // Set the Correction
//                 // cout << " " << misspel [i] [1] << endl;
//             }
//             else // If there is more than one Correction
//             {
//                 for (int z = 0; z < 25; z++) // Empty the Corrections Split String
//                 {
//                     words3 [z] = "";
//                 }
//                 split (words2 [1], '|', words3,  25); // Split the Corrections
//                 for (int z = 0; z < 25; z++)
//                 {
//                     if (words3 [z].length() > 0) // While there are Corrections
//                     {
//                         misspel [i] [z+1] = words3 [z]; // Set the Corrections
//                         // cout << " " << misspel [i] [z+1] << " ";
//                     }
//                     else // End Setting Corrections
//                     {
//                         z = 25;
//                     }
//                 }
//                 // cout << endl;
//             }
//             // bool verify = false;
//              ++i;
//         }
//         int count = 0;
//         for (int z = 0; z < 3000; z++) // For the Number of Misspelling Words
//         {
//             bool verify = false;
//             for (int i = 0; i < 4000; i++) // For the Number of Vocab Words
//             {
//                 if (misspel [z][0] == vocab [i])
//                 {
//                     verify = true; // The word exists in Vocab
//                 }
//             }
//             if (!verify) // If the word does not exist
//             {
//                 // cout << misspel [z] [0] << endl;
//                 vocab [3006 + count] = misspel [z] [0]; // Add the Word to Vocab
//                 ++count;
//             }
//         }
//         // cout << "count: " << count;
//         // cout << "vocab 3007 " << vocab [3006] << endl;
//         misspelling.close (); // Close the File
//         return i;
//     }
//     else
//     {
//         cout << "misspelling.txt does not exist" << endl; // The File does not Exist
//         return false;
//     }
//   }

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

int main (int argc, char *argv[])
{
  string phrase = ""; // The phrase that is entered
  string newPhrase = ""; // The corrected phrase
  string finalPhrase = ""; // The final phrase
  //Read in the Common Words File
  // readCommonWords (argv [1]);
  //
  // //Read in the Misspellings File
  // readMisspellings (argv [1]);

  cout << "Enter the phrase you would like to correct: "; // Get the phrase
  // getline (cin, phrase);

  // Test Cases
  phrase = "...,, $%!HELLO WORLD! My firends are qwer.";
  // phrase = "Do    you knwo youself?";
  // phrase = "I loev C++";
  // phrase = "!!! A lightyear is a distaNCe UiTN!!!";
  // phrase = ", xxx Thsi is 21 centruy NOW!!!";
  // phrase = "xxx @ yyy @ zzz";

  cout << endl << phrase << endl;
  // Set the phrase from the first word
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

  // Make the phrase lowercase
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
          if (newPhrase [i] == ' ' && space == false) // If there has not been a Space Before
          {
              space = true; // One Space has been Read
              changePhrase = changePhrase + ' '; // Add the Space
          }
      }
  }

  // Check each word in the phrase and add to the Final Phrase

  changePhrase = changePhrase + '.'; // Read the Last Word with the Punctuation
  int position = 0;
  string changeWord = "";
  for (int i = 0; i < changePhrase.length(); i++)
  {
      if (changePhrase [i] >= 'a' && changePhrase [i] <= 'z') // If there is a Letter
      {
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
          finalPhrase = finalPhrase + checkWord (changeWord, vocab, misspel); // Add the Looked Up Word
          changeWord = ""; // Clear the Word
          finalPhrase = finalPhrase + ' '; // Add the Space
      }
      else if (changePhrase [i] < 'a' || changePhrase [i] > 'z') // If Another Symbol
      {
          position = i + 1;
          // cout << checkWord (changeWord, vocab, misspel) << " ";
          // cout << changeWord << " ";
          // changeWord = "";
          finalPhrase = finalPhrase + checkWord (changeWord, vocab, misspel); // Add the Looked Up Word
          changeWord = ""; // Clear the Accumulated Word
          finalPhrase = finalPhrase + changePhrase [i]; // Add the Symbol
      }
      // else if (changePhrase [changePhrase.length ()] >= 'a' && changePhrase [changePhrase.length ()] <= 'z')
      // {
      //     finalPhrase = finalPhrase + checkWord (changeWord, vocab, misspel);
      //     // changeWord = "";
      //     // finalPhrase = finalPhrase + changePhrase [i];
      // }
  }
  finalPhrase [finalPhrase.length()-1] = ' '; // Remove the Punctutation
  cout << endl << finalPhrase << endl; // Display the Word

  cout << changePhrase << endl;
}
