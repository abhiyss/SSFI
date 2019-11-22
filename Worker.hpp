/*------------------------------------------------------------------------------*/
/*              Developed By: Sri Sagar Abhishek Yeluri                         */
/*                          Version : 1.0                                       */
/*                    Super Simple File Indexer                                 */
/*                            Worker.hpp                                        */
/*------------------------------------------------------------------------------*/

#include "Files.hpp"
#include "HashTable.hpp"
#pragma once
class Worker
{
    public:
    Worker();
    
    void getCount(Files*, HashTable*, bool*);
};
