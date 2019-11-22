/*------------------------------------------------------------------------------*/
/*              Developed By: Sri Sagar Abhishek Yeluri                         */
/*                          Version : 1.0                                       */
/*                    Super Simple File Indexer                                 */
/*                            Worker.cpp                                        */
/*------------------------------------------------------------------------------*/
/* This program has the function which will be used for a thread that will pop  */
/* the file at the fron of the list and then parses words in it and updates the */
/* count or inserts the word into the hash table.                               */
/*------------------------------------------------------------------------------*/

#include <unistd.h> 
#include <filesystem>
#include <stdlib.h>
#include <fstream>
#include <thread>
#include <string.h>
#include <boost/tokenizer.hpp>

#include "Files.hpp"
#include "HashTable.hpp"
#include "Worker.hpp"

using namespace std;
using namespace boost;

Worker::Worker()
{
    // An empty constructor is used as there are no variables to be intiliazed when the object is created.
    ;
}

void Worker::getCount(Files* object, HashTable* objectH,bool *fileReaderThreadAlive)
{
    // This function is responsible to pop a file path name from the received File object
    // counting the words in the file and updating the number of occurences in the hashtable object received
    while (true)
    {
        // If the number of enteries in the list of file paths is zero do either of the follwing
        // 1. If the File reader thread is not running it means no more new files will come in so return from the function
        // 2. If the File reader thread is running then yield the thread so that the File reader can insert files in to the list
        while (object->countFiles()==0)
        {
            if(*fileReaderThreadAlive == false)
                return;
            this_thread::yield();
        }
        
        ifstream myfile;
        string line;
        
        //Pop the files whose path is at the front of the list
        string fileName = object->popFiles();
        if (fileName != "")
        {
            myfile.open(fileName);
            while ( getline (myfile,line) )
            {
                // Convert any non A-Z, non a-z or non 0-9 character to a space
                for (int looper = 0; looper < line.length(); looper++)
                {
                    if (!(isalnum(line[looper])))
                        line[looper] = ' ';
                }
                
                // Tokenize the string by spaces.
                tokenizer<> tok(line);
                for(tokenizer<>::iterator beg=tok.begin(); beg!=tok.end();++beg)
                {
                    string word = *beg;
                    transform(word.begin(), word.end(), word.begin(), ::tolower);
                    
                    // Insert or update the count of the word in the hash table
                    objectH->insert_word(word);
                }
            }
            myfile.close();
        }
    }
}
