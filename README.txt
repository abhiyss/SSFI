/*------------------------------------------------------------------------------*/
/*              Developed By: Sri Sagar Abhishek Yeluri                         */
/*                          Version : 1.0                                       */
/*                    Super Simple File Indexer                                 */
/*------------------------------------------------------------------------------*/
This is the solution i implemented for the Super Simple File Indexer (SSFI).

The following files should be found in the tar packages upon unpacking.

1. SSFI.cpp       - The coordinator C++ program that creates the File reader thread and the N worker threads and the prints the results once the searching and the parsing is complete
2. Files.cpp      - Program that provides acces to the list of the file paths found
3. Files.hpp      - Header file for Files.cpp
4. FileReader.cpp - Program that traverses through the directory to find ".txt" files
5. FileReader.hpp - Header file for FileReader.cpp
6. HashTable.cpp  - Program that provides access to the hash table in which the words and their number of occurences are to be stored.
7. HashTable.hpp  - Header file for HashTable.cpp
8. Worker.cpp     - Program that is repsonsible to pickup a file from the list and parse the words in it and update the hashtable
9. Worker.hpp     - Header file for Worker.cpp

To compile the files use the command:

	$ make

To remove the executable run the command:

	$ make clean

After compiling, to run the program use the ./ssfi executable using either of the follwing ways:

	1. ./ssfi "/path_name"
		
		or

	2. ./ssfi -t N "/path_name"

First option runs with 1 worker thread, Second option runs with N Worker threads. "/path_name" should be replaced by the actual path name.

Compilation is done using C++17 standard.

Tested on Fedora 30. Should work on Ubuntu 16.04 and Ubuntu 18.04. If there are problems running it due to compatability issues, please reach out to me and i will try to fix the issue.


