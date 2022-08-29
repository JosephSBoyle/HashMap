#include <assert.h>
#include <stdio.h>
#include <string.h>

#include "hashmap.h"
#include <assert.h>
#include <stdio.h>
#include <string.h>

/** TESTS
 * These tests test the collision handling of the hashmap.
 * NOTE: To cause collisions, replace the return value of the hash function with a constant int, e.g `return 0;`
 */
void main(){

    // test adding and getting an item
    Node** hm0 = hm_create();
    hm_add(hm0, "bob", "x");
    
    char* a = hm_get(hm0, "bob");
    assert(strcmp(a, "x") == 0);
    
    // test deleting an item that doesn't exist
    Node** hm1 = hm_create();
    hm_del(hm1, "bob");
    
    char* b = hm_get(hm1, "bob");
    assert(strcmp(b, "\0") == 0);

    // test getting a deleted item
    Node** hm2 = hm_create();
    hm_add(hm0, "bob", "the dog");
    hm_del(hm2, "bob");
    
    char* c = hm_get(hm2, "bob");
    assert(strcmp(c, "\0") == 0);

    // test overwriting a value
    Node** hm3 = hm_create();
    hm_add(hm3, "bob", "foo");
    hm_add(hm3, "bob", "bar");
    
    char* d = hm_get(hm3, "bob");
    assert(strcmp(d, "bar") == 0);
    
    // test deleting the last item
    Node** hm4 = hm_create();
    hm_add(hm4, "bob", "foo");
    hm_add(hm4, "alice", "bar");
    hm_add(hm4, "jane", "baz");

    hm_del(hm4, "jane");
    char* e = hm_get(hm4, "jane");
    assert(strcmp(e, "\0") == 0);

    // test deleting an item in the middle of the linked list.
    Node** hm5 = hm_create();
    hm_add(hm5, "bob", "abc");
    hm_add(hm5, "alice", "123");
    hm_add(hm5, "jane", "xyz");

    hm_del(hm5, "alice");
    char* f = hm_get(hm5, "alice");
    assert(strcmp(f, "\0") == 0);

    printf(
        "############################\n"
        "----- ALL TESTS PASSED -----\n"
        "############################\n"
    );
}
