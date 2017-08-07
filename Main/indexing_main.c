#include <stdio.h>
#include <indexing.h>

int main()
{
	int option;
	char ch , word[32], file[50], new_word[32];

	wlist_t **h_array = wl_create_table();

	do
	{
		// Read the option
		printf("1. Create table\n2. Search word\n3. Print hash table\n4. Delete word\n5. Edit word\nEnter the option: ");
		scanf("%d", &option);

		switch (option)
		{
			case 1: 
				// Read file and create table
				read_file(h_array);
				break;

			case 2:	
				// Read the word
				printf("Enter the word to be searched: ");
				scanf("%s", word);

				// Search table
				search_hash_table(h_array, word);
				break;

			case 3:
				
				printf("***************************DATABASE**************************\n");
				print_hash_table(h_array);
				break;

			case 4: 

				// Read the word to delete
				printf("Enter the word to be deleted: ");
				scanf("%s", word);

				// Read the file name
				printf("Enter the file from which word is to be deleted: ");
				scanf("%s", file);

				// Delete the word
				delete_word(word, file);
				break;

			case 5: 

				// Read the word to edit
				printf("Enter the word to be edited: ");
				scanf("%s", word);

				// Read the new word
				printf("Enter the new word: ");
				scanf("%s", new_word);

				// Read the file name
				printf("Enter the file from which word is to be edited: ");
				scanf("%s", file);

				// Edit word from file
				edit_word(word, new_word, file);
				break;
		}
		printf("Do you want to continue: ");
		scanf("\n%c", &ch);
	}while (ch == 'y');
	return 0;

}
