/* HASHMAP OF ARBITRARY LENGTH STRINGS TO CHARACTERS */
#define BUCKETS 1000000
#define PRIME_SEED_1 17
#define PRIME_SEED_2 97
#define KEY_CHARS 128

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <assert.h>

typedef struct Node Node;

struct Node {
    Node* next; // pointer to the next node
    char value;
    char key[KEY_CHARS];
};

#define NODE_SIZE sizeof(Node)


Node* create_sentinel_node(){
    void* ptr = malloc(NODE_SIZE);
    if (ptr == NULL){
        exit(EXIT_FAILURE);
    } else {
        Node* node = (Node*)ptr; // safely typecast the pointer
        node->next = NULL;
        strcpy(node->key, "\0");
        node->value = '\0';
        return node;
    }
}


size_t modular_hash(char* string) {
    size_t hash = 0;
    for (char* character=string; *character != '\0'; character++) {
        hash += ((int)*character + PRIME_SEED_1) * PRIME_SEED_2; 
    }
    return 0; // TODO
    // return hash;
}


Node** hm_create(){
    static Node* keys[BUCKETS] = {};
    for (size_t i=0; i<BUCKETS; i++){
        keys[i] = create_sentinel_node();
    }
    return keys;
}


void hm_add(Node** hmap, char key[], char value){
    size_t hkey = modular_hash(key);
    Node* node = hmap[hkey];

    if (node->value == '\0'){
        node->value = value;
        strcpy(node->key, key);
        return;
    }
    // go to the last node
    while(true){
        // check for a key collision
        if (strcmp(node->key, key) == 0){
            node->value = value;
            return;
        }
        if (node->next == NULL){
            // create a new node
            void* ptr = malloc(NODE_SIZE);
            if (ptr == NULL){
                exit(EXIT_FAILURE);
            } else {
                Node* new_node = (Node*)ptr; // safely typecast the pointer
                new_node->next = NULL;
                new_node->value = value;
                strcpy(new_node->key, key);
                node->next = new_node;
                return;
            }
        }
        node = node->next;
    }
}
    

char hm_get(Node** hmap, char* key){
    size_t hkey = modular_hash(key);
    Node* node = hmap[hkey];

    // skip list elements in the bucket that don't match our key.
    while (strcmp(node->key, key) != 0){
        node = node->next;
    }
    return node->value;
}

void main(){
    Node** hashmap = hm_create();
    
    hm_add(hashmap, "syuuu", 'x');
    char a = hm_get(hashmap, "syuuu");
    assert(a=='x');

    hm_add(hashmap, "syuuu", 'y');
    a = hm_get(hashmap, "syuuu");
    assert(a=='y');
    
    hm_add(hashmap, "big_bob", 'z');
    a = hm_get(hashmap, "big_bob");
    assert(a=='z');

    a = hm_get(hashmap, "syuuu");
    assert(a=='y');
}