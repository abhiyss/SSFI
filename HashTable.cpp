/*------------------------------------------------------------------------------*/
/*              Developed By: Sri Sagar Abhishek Yeluri                         */
/*                          Version : 1.0                                       */
/*                    Super Simple File Indexer                                 */
/*                          HashTable.cpp                                       */
/*------------------------------------------------------------------------------*/
/* Has the class that holds the hash map to keep track of the words seen so far */
/* and their counts. It provides the functions required to insert the words in  */
/* the has table, and also print functions to display all the entries and only  */
/* the top 10 enteries                                                          */
/*------------------------------------------------------------------------------*/

#include <iostream>
#include <unistd.h> 
#include <stdlib.h>
#include <vector> 
#include <list>
#include <mutex>
#include <algorithm>

#include "HashTable.hpp"

using namespace std;

mutex mutexForWords;

HashTable::HashTable()
{
    // To display only the top 10 occurences. Can be changed to N to display the top N occurences.
    numberOfElements = 10; 
}
void HashTable::insert_word(string word)
{
    // Th9is function is responsible to insert the input word in the hash table if it is not present in the hash table
    // or to increase the count of its occurence if already present
    
    //Acquire the lock to write so that two different workers don't write in the same place at the same time making data inconsistent
    unique_lock<mutex> lck (mutexForWords,defer_lock);
    lck.lock();
    auto it = countTable.find(word);
    
    
    // Word not present in the hash table, insert it with occurence being 1
    if (it == countTable.end())
    {
        countTable.insert(pair<string, int>(word,1)); 
    }
    
    // Word present in the hash table, increase the occurence count by 1
    else
    {
        it->second = (it->second)+1;
    }
    
    // Unlock the lock
    lck.unlock();
}
void HashTable::printer()
{
    // A function that can be used to print the occurence of all the words.
    // An auxiliary function that can be used for debugging purposes, but is not part of the primary requirements
    
    for(auto elem : countTable)
    {
        cout << elem.first << " " << elem.second << "\n";
    }
}

void HashTable::sorted_printer()
{
    // This function is used to print the top 10 occuring words in all the ".txt" files
    // We copy the hash map into this vector
    vector< pair < string, int > > vec;
	copy(countTable.begin(),countTable.end(),back_inserter< vector < pair < string, int > > >(vec));

	// We sort the vector by the values i.e. the second element in the pair. This is so that the most occuring words are at the top.
    sort(vec.begin(), vec.end(),[](const pair<string,int>& one, const pair<string,int>& two) {if (one.second != two.second)
            return one.second > two.second;

        return one.first < two.first;
    });
    
    // Print the top 10 words from the vector
    int counter = 0;
    for (auto const &pair: vec) 
    {
        cout << pair.first << " " << pair.second << '\n';
        if (++counter == numberOfElements)
            break;
	}
}
