#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <indexing.h>

// Create table
wlist_t **wl_create_table(void)
{
	int index;

	// Allocate memory
	wlist_t **w_array = malloc(52 * sizeof(wlist_t *));

	for (index = 0; index < 52; index++)

		w_array[index] = NULL;

	// Store the name
	return w_array;

}

// Get index value for the hash table
int wl_get_index(char ch)
{
	int index;

	if (ch >= 'A' && ch <= 'Z')
		index = ch - 'A';

	if (ch >= 'a' && ch <= 'z')
		index = ch - 'a' + 26;

	return index;

}

// Create file node
flist_t *create_f_node(char *fname)
{
	flist_t *f_new = malloc(sizeof(flist_t));
	int f_len =  strlen(fname);

	f_new->f_name = malloc(f_len + 1);

	strcpy(f_new->f_name, fname);

	f_new->w_count = 1;

	f_new->next = NULL;

	return f_new;
}

// Create word node
wlist_t *create_w_node(char *word, char *fname)
{
	wlist_t *w_new = malloc(sizeof(wlist_t));
	int w_len = strlen(word);

	w_new->w_name = malloc(w_len + 1);

	strcpy(w_new->w_name, word);

	w_new->f_count = 1;
	w_new->f_head = create_f_node(fname);
	w_new->next = NULL;

	return w_new;
}

// Insert word to the first of the word node
void wl_insert_first(wlist_t **head, char *word, char *fname)
{
	if (*head == NULL)
		*head = create_w_node(word, fname);

	else
	{
		wlist_t *new = create_w_node(word, fname);
		new->next = *head;
		*head = new;
	}
}

// Insert word to the last of the word node
void wl_insert_last(wlist_t **head, char *word, char *fname)
{
	if (*head == NULL)
		*head = create_w_node(word, fname);
	else
	{
		wlist_t *ptr;

		ptr = *head;

		while (ptr->next != NULL)
			ptr = ptr->next;
		ptr->next = create_w_node(word, fname);
	}
}

// Insert file to the last of the file node
void fl_insert_last(flist_t **head, char *fname)
{
	if (*head == NULL)
		*head = create_f_node(fname);
	else
	{
		flist_t *ptr;

		ptr = *head;

		while (ptr->next != NULL)
			ptr = ptr->next;
		ptr->next = create_f_node(fname);
	}
}

// Insert after fuction for word list
void wl_insert_after(wlist_t **head, char *word1, char *word2, char *fname)
{
	// If first node is null
	if (*head == NULL)
		printf("No list\n");

	else
	{
		wlist_t *ptr, *newnode;
		ptr = *head;

		// Move to the next node 
		while (ptr != NULL && strcmp(ptr->w_name, word1) != 0)
			ptr = ptr->next;

		// If ptr is null
		if (ptr == NULL)
			printf("No element found\n");

		// Else create a node and place is after the element
		else
		{
			newnode = create_w_node(word2, fname);
			newnode->next = ptr->next;
			ptr->next = newnode;
		}
	}
}

// Insert sorted function for word list
void wl_insert_sorted(wlist_t **head, char *word, char *fname)
{

	// If head is NULL
	if (*head == NULL)
		*head = create_w_node(word, fname);

	else
	{
		wlist_t *ptr1, *ptr2;

		ptr1 = *head;
		ptr2 = *head;

		// Check for value less than ptr1
		if (strcmp(word, ptr1->w_name) < 0)
			wl_insert_first(head, word, fname);

		else 
		{
			while (ptr2->next != NULL)
			{
				// move ptr2 till null
				ptr2 = ptr2->next;

				// Check if value lies between ptr1 and ptr2
				if (strcmp(ptr1->w_name, word) < 0 && strcmp(ptr2->w_name, word) > 0)
				{
					// Insert after ptr1
					wl_insert_after(head, ptr1->w_name, word, fname);
					break;
				}

				// Move ptr1
				ptr1 = ptr1->next;

			}

			// if value id greater than ptr2
			if  (ptr2->next == NULL && strcmp(word, ptr2->w_name) > 0)
				// Insert last
				wl_insert_last(head, word, fname);
		}
	}
}

// Create a hash database
void create_hash_database(wlist_t **h_array, char *wname, char *fname)
{
	int index = wl_get_index(wname[0]);

	wlist_t *ptr = h_array[index];

	while (ptr != NULL && strcmp(ptr->w_name, wname) != 0)
		ptr = ptr->next;

	// If word is found
	if (ptr != NULL)
	{

		flist_t *fptr = ptr->f_head;

		while (fptr != NULL && strcmp(fptr->f_name, fname) != 0)
			fptr = fptr->next;

		// If file is found
		if (fptr != NULL)
		{
			// Increment the word count in file list
			fptr->w_count = fptr->w_count + 1;
		}
		else 
		{
			// Insert file
			fl_insert_last(&ptr->f_head, fname);

			// Increment the file count in word list
			ptr->f_count = ptr->f_count + 1;
		}
	}

	else
		// Insert new word in the word list
		wl_insert_sorted(&h_array[index], wname, fname);

}

// print hash table
void print_hash_table(wlist_t **h_array)
{
	int index = 0;

	while (index < 52)
	{
		if (h_array[index] != NULL)

			wl_print_list(h_array[index]);

		index++;
	}
}

// Print list
void wl_print_list(wlist_t *head)
{

	// If first node is null
	if (head == NULL)
		printf("No list\n");

	// Else print the list
	else
	{
		wlist_t *ptr;

		ptr = head;

		while (ptr != NULL)
		{
			printf("%-15s\t", ptr->w_name);
			printf("%-15d\t", ptr->f_count);

			if (ptr->f_head != NULL)
				fl_print_list(ptr->f_head);

			ptr = ptr->next;

		}

		printf("\n");
	}
}

// Print list
void fl_print_list(flist_t *head)
{

	// If first node is null
	if (head == NULL)
		printf("No list\n");

	// Else print the list
	else
	{
		flist_t *ptr;

		ptr = head;

		while (ptr != NULL)
		{
			printf("%-15s\t", ptr->f_name);
			printf("%-15d\t", ptr->w_count);
			ptr = ptr->next;
		}

		printf("\n");
	}
}

// Search word in hash table
void search_hash_table(wlist_t **h_array, char *wname)
{
	// Get the index value
	int index = wl_get_index(wname[0]);

	wlist_t *ptr = h_array[index];

	// Move till the word if found
	while (ptr != NULL && strcmp(ptr->w_name, wname) != 0)
		ptr = ptr->next;

	// If found
	if (ptr != NULL)
	{
		// Print the data
		printf("Word: %s\nFile count: %d\n", ptr->w_name, ptr->f_count);
		fl_print_list(ptr->f_head);

	}

	else
	{
		printf("Word not present in these files\n");

	}
}

// Get files
char **get_files(int *limit)
{
	char buffer[32];
	int index, length;

	// Read the number of files
	printf("Enter the no. of files : ");
	scanf("%d", limit);

	// Allocate memory 
	char **arr = malloc(*limit * sizeof(char *));
	
	// Read the file names and store it an array
	printf("Enter the file names: ");
	for (index = 0; index < *limit; index++)
	{
		scanf("%s", buffer);
		length = strlen(buffer);
		arr[index] = malloc(length + 1);
		strcpy(arr[index], buffer);
	}

	return arr;
}

// Get word function
FILE *get_word(FILE *fptr, char *word)
{
	char ch;
	int index = 0;

	if (feof(fptr) != 0)
	{
		word[0] = '\0';
		return fptr;
	}

	// Read till EOF is reached
	while (feof(fptr) == 0)
	{
		fread(&ch, 1, 1, fptr);

		// Reading till the delimeter is found
		if (ch < 31 || ch == ' ' || ch == '\n' || ch == '\t' || ch == ',' || ch == '.')
		{
			if (ch == ',' || ch == '.')
			{
				fread(&ch, 1, 1, fptr);

				// Check for spaces
				if (ch != ' ')
					fseek(fptr, -1, SEEK_CUR);
			}
			word[index] = '\0';
			break;
		}
		else
			word[index++] = ch;
	}

	return fptr;
}

// Read contents from files
void read_file(wlist_t **h_array)
{
	int  size, index;
	char word[32];
	FILE *fptr;

	// Get the file array
	char **file = get_files(&size);

	// Open all the files
	for (index = 0; index < size; index++)
	{
		fptr = fopen(file[index], "r");

		if (fptr == NULL)
		{
			printf("Error! File cannot be opened\n");
			return;
		}

		while (1)
		{
			// Get word from the file
			fptr = get_word(fptr, word);

			if (strlen(word) == 0)
				break;

			// Create the hash database
			if (word[0] >= 'A' && word[0] <= 'Z' ||word[0] >= 'a' && word[0] <= 'z')
			{

				create_hash_database(h_array, word, file[index]);

			}

		}

		// Close the file
		fclose(fptr);
	}
}

// Delete word from file
void delete_word(char *word, char *fname)
{
	int flag = 0, length, bytes = 0, s_flag = 1, d_flag = 0, index;
	char ch, buff[100];

	length = strlen(word);

	// Open the temp file
	FILE *temp = fopen("temp.txt", "w");

	if (temp == NULL)
	{
		printf("Error! Temp File cannot be opened\n");
		return;
	}

	// Open the source file
	FILE *src_ptr = fopen(fname, "r");

	if (src_ptr == NULL)
	{
		printf("Error! Source File cannot be opened\n");
		return;
	}

	// Read till EOF is reached
	while (feof(src_ptr) == 0)
	{
		fread(&ch, 1, 1, src_ptr);

		// Check for delimeters
		if (flag || s_flag || d_flag || '!' <= ch && ch <= '/' || ':' <= ch && ch <= '@' || ch == ' ' || ch == '\n' || ch == '\t' )
		{
			s_flag = 0;
			d_flag = 0;
			flag = 1;
		}

		else 
			flag = 0;

		// If read character matches with word[0]
		if (flag && ch == word[0])
		{
			// Copy the word to the buffer
			index = 0;
			buff[index++] = ch;

			while (1)
			{
				fread(&ch, 1, 1, src_ptr);
				// If delimeter is found
				if ('!' <= ch && ch <= '/' || ':' <= ch && ch <= '@' || ch == ' ' || ch == '\n' || ch == '\t' )
				{
					d_flag = 1;

					buff[index] = '\0';

					break;
				}

				buff[index++] = ch;
			}

			// Compare buff matches with the word
			if (strcmp(buff, word) == 0)
			{
				// Ignore the word
				fwrite(&ch, 1, 1, temp);
				continue;
			}

			else
			{
				// Write the buff to temp file
				fwrite(buff, strlen(buff), 1, temp);
				fwrite(&ch, 1, 1, temp);
			}
		}	

		else
			fwrite(&ch, 1, 1, temp);
	}

	// Close all the files
	fclose(src_ptr);
	fclose(temp);

	// Open the files again
	src_ptr = fopen(fname, "w");

	if (src_ptr == NULL)
	{
		printf("Error! Source File cannot be opened\n");
		return;
	}

	temp = fopen("temp.txt", "r");

	if (temp == NULL)
	{
		printf("Error! File cannot be opened\n");
		return;
	}

	// Copy temp file contents back to source file
	while (feof(temp) == 0)
	{
		bytes = fread(buff, 1, 100, temp);
		buff[bytes] = '\0';
		fwrite(buff, 1, bytes,  src_ptr);
	}

	fclose(src_ptr);
	fclose(temp);
}

// Edit word from file
void edit_word(char *word, char *new_word, char *fname)
{
	int flag = 0, length, bytes = 0, s_flag = 1, d_flag = 0, index;
	char ch, buff[100];

	length = strlen(word);

	// Open the temp file
	FILE *temp = fopen("temp.txt", "w");

	if (temp == NULL)
	{
		printf("Error! Temp File cannot be opened\n");
		return;
	}

	// Open the source file
	FILE *src_ptr = fopen(fname, "r");

	if (src_ptr == NULL)
	{
		printf("Error! Source File cannot be opened\n");
		return;
	}

	// Read till EOF is reached
	while (feof(src_ptr) == 0)
	{
		fread(&ch, 1, 1, src_ptr);

		// If delimeter is found
		if (flag || s_flag || d_flag || '!' <= ch && ch <= '/' || ':' <= ch && ch <= '@' || ch == ' ' || ch == '\n' || ch == '\t' )
		{
			s_flag = 0;
			d_flag = 0;
			flag = 1;
		}

		else 
			flag = 0;

		// If character read matches woth word[0]
		if (flag && ch == word[0])
		{
			index = 0;
			buff[index++] = ch;

			while (1)
			{
				fread(&ch, 1, 1, src_ptr);

				// If delimeter is found stop copying
				if ('!' <= ch && ch <= '/' || ':' <= ch && ch <= '@' || ch == ' ' || ch == '\n' || ch == '\t' )
				{
					d_flag = 1;

					buff[index] = '\0';

					break;
				}
				// Copy the word to buff
				buff[index++] = ch;
			}

			// Compare buff with word
			if (strcmp(buff, word) == 0)
			{
				// If equal write the new word to the temp file
				fwrite(new_word, strlen(new_word), 1, temp);
				fwrite(&ch, 1, 1, temp);
				continue;
			}

			else
			{
				// Write remaining words to the temp file
				fwrite(buff, strlen(buff), 1, temp);
				fwrite(&ch, 1, 1, temp);
			}
		}	

		else
			
			fwrite(&ch, 1, 1, temp);
	}

	// Close all the files
	fclose(src_ptr);
	fclose(temp);

	// Open all the files again
	src_ptr = fopen(fname, "w");

	if (src_ptr == NULL)
	{
		printf("Error! Source File cannot be opened\n");
		return;
	}

	temp = fopen("temp.txt", "r");

	if (temp == NULL)
	{
		printf("Error! File cannot be opened\n");
		return;
	}

	// Copy temp file contents back to source file
	while (feof(temp) == 0)
	{
		bytes = fread(buff, 1, 100, temp);
		buff[bytes] = '\0';
		fwrite(buff, 1, bytes,  src_ptr);
	}

	// Close all the files
	fclose(src_ptr);
	fclose(temp);
}


