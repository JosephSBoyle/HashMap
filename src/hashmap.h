#include <stddef.h>
#include "hashmap.c"

/* Create a hashmap.*/
Node** hm_create(void);


/* Add an item to the hashmap */
void hm_add(char* key, char value);

/** Get an item from the hashmap 
 * @returns the value corresponding to 'key' or the terminating character '\0'
 * if no such item exists. */
char hm_get(char* key);
