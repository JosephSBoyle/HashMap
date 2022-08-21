#include <stddef.h>
#include "hashmap.c"

/* Create a hashmap.*/
Node** hm_create(void);

/* Add an item to the hashmap */
void hm_add(Node** hmap, char key[], char value[]);

/* Remove an item from the hashmap */
void hm_del(Node** hmap, char key[]);

/** Get an item from the hashmap 
 * @returns the value corresponding to 'key' or the terminating character '\0'
 * if no such item exists. */
char* hm_get(Node** hmap, char key[]);
