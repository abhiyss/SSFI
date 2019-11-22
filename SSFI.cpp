/*------------------------------------------------------------------------------*/
/*              Developed By: Sri Sagar Abhishek Yeluri                         */
/*                          Version : 1.0                                       */
/*                    Super Simple File Indexer                                 */
/*                             SSFI.cpp                                         */
/*------------------------------------------------------------------------------*/
/* This is the main coordinator file. This file is responsible to take the      */
/* input from the terminal about the number of worker threads and source path   */
/* to look into for ".txt" files and sub-directories. It spawns a FileReader    */
/* thread that searches through directories and it also spawns N number of      */
/* worker threads that it is responsible to pick up the found files and count   */
/* and insert he count in the HashTable. Once all wokrer threads finish it then */
/* prints out the top 10 occurring words.                                       */
/*------------------------------------------------------------------------------*/

#include <iostream>
#include <unistd.h> 
#include <stdlib.h>
#include <thread>

#include "Files.hpp"
#include "Worker.hpp"
#include "HashTable.hpp"
#include "FileReader.hpp"

using namespace std;

int main(int argc, char *argv[])  
{ 
    int numOfThreads,opt;
    string pathName;
    
    // If number of worker threads are passed as argument
    if((opt = getopt(argc, argv, "t:")) != -1)                                          
    {
        switch(opt)  
        {  
            case 't':
                numOfThreads = atoi(optarg);
        }
    }
    // Else If number of worker threads are not passed as argument, we set max number of worker threads to 1
    else
    {
        numOfThreads = 1;
    }
    
    // To get the pathname of the directory from the command prompt
    for(; optind < argc; optind++)
    {      
        pathName = argv[optind];  
    }
    
    // Create a Files object in which we will store the path names of all the ".txt" files found
    Files object;
    
    // Create a FileReader object that has the function FilePathAccumulator that will be invoked using a thread. 
    FileReader objectF;
    
    // This boolean value is used to see if the File Reader thread is still running.
    // This is used by the worker threads, if the File reader thread is not running and if list is empty it means they can end too.
    bool fileReaderThreadAlive = true;
    
    // Create a file reader thread by calling FilePathAccumulator function using the thread
    thread fileReaderThread (&FileReader::FilePathAccumulator, objectF, &object, pathName);

    // Create a HashTable object which contains the map that stores teh word and the number of occurences of them.
    HashTable objectH;
    
    // An array of threads. Used to store spawned threads to see if they all joined later on.
    thread threads[numOfThreads];
    
    // Create the required number of Wokrer threads. Function getCount is called using the Worker Threads.
    for (int looper = 0; looper < numOfThreads; looper++)
    {
        Worker* objectW = new Worker();
        threads[looper] = thread(&Worker::getCount,objectW,&object,&objectH,&fileReaderThreadAlive);
    }
    
    // File Reader finished running. Set boolean to false so that the Worker threads are aware that no more new files will be added to the list
    fileReaderThread.join();
    fileReaderThreadAlive = false;
    
    // Wait for all worker threads to finish running and join back
    for (int looper = 0; looper < numOfThreads; looper++)
    {
        threads[looper].join();
    }
    
    //Print the top 10 occuring words in the ".txt" files
    objectH.sorted_printer();
}
