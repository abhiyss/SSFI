/*------------------------------------------------------------------------------*/
/*              Developed By: Sri Sagar Abhishek Yeluri                         */
/*                          Version : 1.0                                       */
/*                    Super Simple File Indexer                                 */
/*                          HashTable.hpp                                       */
/*------------------------------------------------------------------------------*/

#include <map>
#pragma once
using namespace std;
class HashTable
{
    int numberOfElements;
    public:
    map<string,int> countTable;
    
    HashTable();
    
    void insert_word(string);
    
    void printer();
    
    void sorted_printer();
};
