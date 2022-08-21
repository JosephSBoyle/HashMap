#define BUCKETS 1000000
#define PRIME_SEED_1 17
#define PRIME_SEED_2 97
#define KEY_CHARS 128

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <assert.h>

/* A key-value node in a single-linked list. */
typedef struct Node Node;

struct Node {
    Node* next;
    char key[KEY_CHARS];
    char value; 
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
    Node* node = hmap[modular_hash(key)];

    if (node->value == '\0'){
        node->value = value;
        strcpy(node->key, key);
        return;
    }

    // TODO refactor
    while(true){
        // check for a key collision
        if (strcmp(node->key, key) == 0){
            node->value = value;
            return;
        }
        if (node->next == NULL){
            // no more nodes, append a new node to the linked list.
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

void hm_del(Node** hmap, char key[]){
    size_t khash = modular_hash(key);
    Node* node = hmap[khash];
    
    // find the correct node in the linked list.
    // if it's the first and only node, reset it to the sentinel node.

    // if the prev node is defined and the target node has a non-null 'next', replace the prev node's next with that.
    // delete the node if it's the last node, and update the 'next' of the prev. node to NULL.
    void* prev_node = NULL;
    Node* head = node;
    
    // find the node
    while (strcmp(head->key, key) != 0){
        head = head->next;
        prev_node = head;
    }

    // are we deleting the first node?
    if (prev_node == NULL){
        // are we deleting the only node?
        if (head->next == NULL){
            // reset the node to the sentinel node.
            node->value = '\0';
            strcpy(node->key, "\0");
        } else {
            // we are deleting the first of n>1 nodes.
            hmap[khash] = head->next;
        }
    } else {
        // there must be a previous node.
        Node* prev_node = (Node*)prev_node;

        // is this the last node?
        if (head->next == NULL){
            prev_node->next = NULL;
        } else {
            // we are deleting neither the first nor the last node.
            prev_node->next = head->next;
        }
        free(head);            
    }

}

char hm_get(Node** hmap, char* key){
    Node* node = hmap[modular_hash(key)];

    // skip list elements in the bucket that don't match our key.
    while (strcmp(node->key, key) != 0){
        if (node->next==NULL){
            return '\0';
        }
        node = node->next;
    }
    return node->value;
}

void main(){
    // test adding, getting and deleting two items.
    Node** hashmap = hm_create();
    
    hm_add(hashmap, "bob", 'x');
    char a = hm_get(hashmap, "bob");
    assert(a=='x');

    hm_del(hashmap, "bob");
    a = hm_get(hashmap, "bob");
    assert(a=='\0');

    hm_add(hashmap, "bob", 'x');
    hm_add(hashmap, "bob", 'y');
    a = hm_get(hashmap, "bob");
    assert(a=='y');
    
    hm_add(hashmap, "alice", 'z');
    a = hm_get(hashmap, "alice");
    assert(a=='z');

    a = hm_get(hashmap, "bob");
    assert(a=='y');

    hm_del(hashmap, "bob");
    a = hm_get(hashmap, "bob");
    assert(a=='\0');

    // test deleting the last item
    Node** hashmap2 = hm_create();
    hm_add(hashmap2, "bob", 'x');
    hm_add(hashmap2, "alice", 'x');
    hm_add(hashmap2, "jane", 'x');

    hm_del(hashmap2, "jane");
    char b = hm_get(hashmap2, "jane");
    assert(b=='\0');

    // test deleting an item in the middle.
    Node** hashmap3 = hm_create();
    hm_add(hashmap3, "bob", 'x');
    hm_add(hashmap3, "alice", 'x');
    hm_add(hashmap3, "jane", 'x');

    hm_del(hashmap3, "alice");
    char c = hm_get(hashmap3, "alice");
    assert(c=='\0');
}