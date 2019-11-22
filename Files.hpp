/*------------------------------------------------------------------------------*/
/*              Developed By: Sri Sagar Abhishek Yeluri                         */
/*                          Version : 1.0                                       */
/*                    Super Simple File Indexer                                 */
/*                             Files.hpp                                        */
/*------------------------------------------------------------------------------*/
 
#include <list>
using namespace std;
#pragma once
class Files
{
    list<string> fileList;
    
    public:
    Files ();

    void insertFiles(string );

    void getFiles();

    string popFiles();

    int countFiles();

    bool files_available();
};
