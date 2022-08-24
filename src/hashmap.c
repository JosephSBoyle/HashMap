#include "hashmap.h"
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#define BUCKETS 1000000
#define PRIME_SEED_1 17
#define PRIME_SEED_2 97

/* A key-value node in a single-linked list. */
Node* create_sentinel_node(){
    Node* node = malloc(sizeof(Node));
    if (!node){
        exit(EXIT_FAILURE);
    }
    node->next = NULL;
    strcpy(node->key, "\0");
    strcpy(node->value, "\0");
    return node;
}


size_t modular_hash(char* string) {
    size_t hash = 0;
    for (char* character=string; *character != '\0'; character++) {
        hash += (*character + PRIME_SEED_1) * PRIME_SEED_2; 
    }
    return hash;
}


Node** hm_create(void){
    static Node* keys[BUCKETS] = {}; // this makes the hashmap a singleton. Use malloc instead
    for (size_t i=0; i<BUCKETS; i++){
        keys[i] = create_sentinel_node();
    }
    return keys;
}

void hm_add(Node** hmap, char key[], char value[]){
    Node* node = hmap[modular_hash(key)];

    if (strcmp(node->value, "\0") == 0){
        // there's no item in this bucket.
        strcpy(node->key, key);
        strcpy(node->value, value);
        return;
    }

    while(true){
        if (strcmp(node->key, key) == 0){
            // the key already exists as a node in the linked list
            // so we can simply replace the value.
            strcpy(node->value, value);
            return;
        }
        if (!node->next){
            // no more nodes, append a new node to the linked list.
            Node* new_node = malloc(sizeof(Node));
            if (!new_node){
                exit(EXIT_FAILURE);
            } 
            new_node->next = NULL;
            strcpy(node->value, value);
            strcpy(new_node->key, key);
            node->next = new_node;
            return;
        }
        node = node->next;
    }
}

void hm_del(Node** hmap, char key[]){
    size_t khash = modular_hash(key);
    Node* node = hmap[khash];
    
    Node* prev_node = NULL;
    Node* head = node;
    
    // find the node
    while (strcmp(head->key, key) != 0){
        if (!head->next){
            // the key doesn't exist in this hashmap.
            return;
        }
        head = head->next;
        prev_node = head;
    }

    // are we deleting the first node?
    if (!prev_node){
        // are we deleting the only node?
        if (!head->next){
            // reset the node to the sentinel node.
            strcpy(node->value, "\0");
            strcpy(node->key, "\0");
        } else {
            // we are deleting the first of n>1 nodes.
            hmap[khash] = head->next;
        }
    } else {
        // there must be a previous node.
        // is this the last node?
        if (!head->next){
            prev_node->next = NULL;
        } else {
            // we are deleting neither the first nor the last node.
            prev_node->next = head->next;
        }
        free(head);
    }

}

char* hm_get(Node** hmap, char key[]){
    Node* node = hmap[modular_hash(key)];

    // skip list elements in the bucket (linked list) that don't match our key.
    while (strcmp(node->key, key) != 0){
        if (!node->next){
            return "\0";
        }
        node = node->next;
    }
    return node->value;
}
