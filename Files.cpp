/*------------------------------------------------------------------------------*/
/*              Developed By: Sri Sagar Abhishek Yeluri                         */
/*                          Version : 1.0                                       */
/*                    Super Simple File Indexer                                 */
/*                             Files.cpp                                        */
/*------------------------------------------------------------------------------*/
/* Has the class Files that has the list that can store the paths of all the    */
/* ".txt" files found. It has the function that is responsible to insert a file */
/* path into the list, a function to remove the file path which is at the front */
/* of the list, a function to print all the files in the list, a function to    */
/* return the number of entries in the list, and a function to check is the     */
/* list is empty                                                                */
/*------------------------------------------------------------------------------*/

#include <unistd.h> 
#include <stdlib.h> 
#include <mutex>
#include <thread>
#include <list>
#include <iostream>
#include "Files.hpp"

using namespace std;
mutex mutexForFiles;

Files::Files()
{
    // An empty constructor is used as there are no variables to be intiliazed when the object is created.
    ;
}

int Files::countFiles()
{
    // Returns the number of file paths in the list
    return fileList.size();
}

bool Files::files_available()
{
    // Returns if the file path list is empty or not
    if(fileList.size() != 0)
        return true;
    else
        return false;
}

void Files::insertFiles(string filePath)
{
    // Function is responsible to inser the file paths found into the list 
    
    //Acquire the lock first to insert the file path into the list
    unique_lock<mutex> lck (mutexForFiles,defer_lock);
    lck.lock();
    
    // Insert the file path into the list
    fileList.push_back(filePath);
    
    //Unlock lock
    lck.unlock();
}
void Files::getFiles()
{
    // An auxiliary fucnton that can be used to print the files found. Could be used for debugging.
    for (string looper: fileList)
        cout<<"Files"<<" "<<looper<<endl;
}
string Files::popFiles()
{
    // Function that is used to get the file path at the front of the list and remove that entry from the list
    
    // Acquire lock
    unique_lock<mutex> lck (mutexForFiles);
    // If list size is not zero after acquiring lock, we can pop a file and return the path as a string
    if (fileList.size() != 0)
    {
        string firstPath = fileList.front();
        fileList.pop_front();
        
        // Unlock lock
        lck.unlock();
        return firstPath;
    }
    // If list size is zero after acquiring lock, we cannot pop a file so we return an empty string
    else
    {
        // Unlock lock
        lck.unlock();
        return "";
    }
}
