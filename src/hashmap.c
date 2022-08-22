#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stddef.h>

#include "hashmap.h"

#define BUCKETS 1000000
#define PRIME_SEED_1 17
#define PRIME_SEED_2 97
#define NODE_SIZE sizeof(Node)


Node* create_sentinel_node(){
    void* ptr = malloc(NODE_SIZE);
    if (ptr == NULL){
        exit(EXIT_FAILURE);
    } else {
        Node* node = (Node*)ptr; // safely typecast the pointer
        node->next = NULL;
        strcpy(node->key, "\0");
        strcpy(node->value, "\0");
        return node;
    }
}


size_t modular_hash(char* string) {
    size_t hash = 0;
    for (char* character=string; *character != '\0'; character++) {
        hash += ((int)*character + PRIME_SEED_1) * PRIME_SEED_2; 
    }
    return hash;
}

Node** hm_create(void){
    void* ptr = malloc(sizeof(Node*) * BUCKETS);
    if (ptr == NULL){
        exit(EXIT_FAILURE);
    } else {
        Node** keys = (Node**)ptr;
        for (size_t i=0; i<BUCKETS; i++){
            keys[i] = create_sentinel_node();
        }
        return keys;
    }

}

void hm_add(Node** hmap, char key[], char value[]){
    Node* node = hmap[modular_hash(key)];

    if (node->value[0] == '\0'){
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
        if (node->next == NULL){
            // no more nodes, append a new node to the linked list.
            void* ptr = malloc(NODE_SIZE);
            if (ptr == NULL){
                exit(EXIT_FAILURE);
            } 
            Node* new_node = (Node*)ptr; // safely typecast the pointer
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
    
    void* prev_node = NULL;
    Node* head = node;
    
    // find the node
    while (strcmp(head->key, key) != 0){
        if (head->next == NULL){
            // the key doesn't exist in this hashmap.
            return;
        }
        head = head->next;
        prev_node = head;
    }

    // are we deleting the first node?
    if (prev_node == NULL){
        // are we deleting the only node?
        if (head->next == NULL){
            // reset the node to the sentinel node.
            node->value[0] = '\0';
            node->key[0] = '\0';
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

char* hm_get(Node** hmap, char key[]){
    Node* node = hmap[modular_hash(key)];

    // skip list elements in the bucket (linked list) that don't match our key.
    while (strcmp(node->key, key) != 0){
        if (node->next==NULL){
            return "\0";
        }
        node = node->next;
    }
    return node->value;
}
