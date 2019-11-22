/*------------------------------------------------------------------------------*/
/*              Developed By: Sri Sagar Abhishek Yeluri                         */
/*                          Version : 1.0                                       */
/*                    Super Simple File Indexer                                 */
/*                         FileReader.cpp                                       */
/*------------------------------------------------------------------------------*/
/* This program has the function that goes through the directory in the given   */
/* path and all the sub directories in the given directory, and puts all the    */
/* files found into the list stored in the Files class                          */
/*------------------------------------------------------------------------------*/

#include <iostream>
#include <unistd.h> 
#include <filesystem>
#include <stdlib.h>
#include "Files.hpp"
#include "FileReader.hpp"

using namespace std;

FileReader::FileReader()
{
    // An empty constructor is used as there are no variables to be intiliazed when the object is created.
    ;
}
void FileReader::FilePathAccumulator(Files* object, string pathName)
{
    // The function is responsible to traverse through the directory given and any sub directories to find ".txt" files and inserts the path names in the list in Files object.
    // recursive_directory_iterator checks through all sub directories automatically
    
    namespace fs = filesystem;
    for (const auto & entry : fs::recursive_directory_iterator(pathName))
    {
        if (!(entry.is_directory()) && entry.path().extension() == ".txt")
        {
            // insert found ".txt files into the fileList list in Files class
            object->insertFiles(entry.path());
        }
    }
}
