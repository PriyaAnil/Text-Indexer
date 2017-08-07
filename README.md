# Text-Indexer
Text Indexer is an application that helps to locate a particular text faster in given set of large data by keeping track of words and their locations in files. This console based application uses standard I/O for searching the words in the files. The purpose of storing an index is to optimize speed and performance in finding relevant documents for a search query. Without an index, the search engine would scan every document in the corpus, which would require considerable time and computing power. The goal of the project is to achieve optimal searching by using Hashing.

ALGORITHM

Step1 : START
Step2 : Create a structure for file and word information to be stored
Step3: Create a hash table by allocating memory dynamically
Step4: Function to create index values, called as hash function 
Step5: Write a function for file node and word node creation
Step6: Develop a function to insert a word into an hash array, insert after, insert first,  insert last and insert sorted
Step7: Write a function for file insertion (Insert last)
Step8: Create the database of word name and file names in hash array
Read file name
Open the files
Read the word from files
Store the word in sorted manner in the hash table
Store the file name, word, file count and word count
Step9 : Print the contents of hash table
Step10: Develop a function to search a word in table
Read a word from user
Search word in the hash table
Print the word, file name, file count and word count
Step13:Delete a word from file
Read the word from user
Read the file name from user
Open the source file and a temporary file
Read word by word from the source file and write to the temporary file 
If word found skip the word
Copy the contents from temporary file back to the source file
tep14:Edit a word from file
Read the word from user
Read the file name from user
Read the new word from user
Open the source file and a temporary file
Read word by word from the source file and write to the temporary file 
If word found write the new word to the temporary file
Copy the contents from temporary file back to the source file
Step15: STOP

Future implementation: Database backup using .csv file can be implemented
