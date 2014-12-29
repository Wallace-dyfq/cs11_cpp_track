#include <iostream>
#include <map>
#include <string>
#include<ctype.h>


// So we don't have to type "std::" everywhere...
using namespace std;


string processWord(string word);
void processText(map<string, int>& wordCounts);
void outputWordsByCount(map<string, int>& wordCounts);


int main()
{
  map<string, int> wordCounts;

  // Process the text on console-input, using the skip-list.
  processText(wordCounts);

  // Finally, output the word-list and the associated counts.
  outputWordsByCount(wordCounts);
}


/*
 * This helper-function converts a word to all lower-case, and then removes
 * any leading and/or trailing punctuation.
 *
 * Parameters:
 *   word    The word to process.  It is passed by-value so that it can be
 *           manipulated within the function without affecting the caller.
 *
 * Return value:
 *   The word after all leading and trailing punctuation have been removed.
 *   Of course, if the word is entirely punctuation (e.g. "--") then the result
 *   may be an empty string object (containing "").
 */
string processWord(string word)
{
  /*****************************************/
  /* TODO:  Your implementation goes here! */
  /*****************************************/
  string tmp;
  int i = 0;
  int j = word.size();
  int cx = 0;
  while(word[i])
  {
    if (!ispunct(word[i]))
      break;      
    i++;
  }
  j--;     // now j is the index for the last char in the string
  if (i < j) // the word is not all punctuation
  {
   
    while(word[j])
    {
    
      if (!ispunct(word[j]))
        break;
      j--;  
    }
  }
  int len = j -i+1;
  tmp = word.substr(i, len);
  
  while (tmp[cx])
  {
    if (!islower(tmp[cx]))
      tmp[cx] = tolower(tmp[cx]);
    cx++;
  }
  return tmp;  
}


void processText(map<string, int>& wordCounts)
{
  /*****************************************/
  /* TODO:  Your implementation goes here! */
  /*****************************************/
  string word;
  int totalWord = 0;
  while (cin >> word)
  {
    string tmp = processWord(word);
    if (tmp.size() != 0)
    {
      totalWord++;
      wordCounts[tmp]++;
    }
  }
  cout<< "Total words in document: "<<totalWord<<"\nUnique words: "<<wordCounts.size()<<endl;
  
}


/*
 * This helper-function outputs the generated word-list in descending order
 * of count.  The function uses an STL associative container to sort the words
 * by how many times they appear.  Because multiple words can have the same
 * counts, a multimap is used.
 */
void outputWordsByCount(map<string, int>& wordCounts)
{
  multimap<int, string, greater<int> > sortByCount;
  map<string, int>::const_iterator wIter;

  for (wIter = wordCounts.begin(); wIter != wordCounts.end(); wIter++)
    sortByCount.insert(pair<int, string>(wIter->second, wIter->first));

  multimap<int, string>::const_iterator cIter;
  for (cIter = sortByCount.begin(); cIter != sortByCount.end(); cIter++)
    cout << cIter->second << "\t" << cIter->first << endl;
}

