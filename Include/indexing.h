#ifndef INDEXING_H
#define INDEXING_H

// File node structure
typedef struct file_node
{
	char *f_name;
	int w_count;
	struct file_node *next;
}flist_t;

// Word node structure
typedef struct word_node
{
	char *w_name;
	int f_count;
	flist_t *f_head;

	struct word_node *next;
}wlist_t;

// Function prototypes

wlist_t **wl_create_table(void);

int wl_get_index(char ch);

flist_t *create_f_node(char *fname);

wlist_t *create_w_node(char *word, char *fname);

void wl_insert_first(wlist_t **head, char *word, char *fname);

void wl_insert_last(wlist_t **head, char *word, char *fname);

void fl_insert_last(flist_t **head, char *fname);

void wl_insert_after(wlist_t **head, char *word1, char *word2, char *fname);

void wl_insert_sorted(wlist_t **head, char *word, char *fname);

void create_hash_database(wlist_t **h_array, char *wname, char *fname);

void print_hash_table(wlist_t **h_array);

void wl_print_list(wlist_t *head);

void fl_print_list(flist_t *head);

void search_hash_table(wlist_t **h_array, char *wname);

char **get_files(int *limit);

FILE *get_word(FILE *fptr, char *word);

void read_file(wlist_t **h_array);

void delete_word(char *word, char *fname);

void edit_word(char *word, char *new_word, char *fname);

void fl_delete_element(flist_t **head, char *fname);

void wl_delete_element(wlist_t **head, char *word);

void delete_word_hash(wlist_t **h_array, char *word, char *fname);

#endif
