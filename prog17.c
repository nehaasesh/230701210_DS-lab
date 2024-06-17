#include <stdio.h>
#include <stdlib.h>

// Structure for a hash node
struct Node {
    int key;
    int data;
    struct Node* next;
};

// Structure for a hash table
struct HashTable {
    int size;        
     int count;     
    struct Node** array; 
};


struct HashTable* createHashTable(int size) {
    struct HashTable* ht = (struct HashTable*) malloc(sizeof(struct HashTable));
    ht->size = size;
    ht->count = 0;
    ht->array = (struct Node**) malloc(ht->size * sizeof(struct Node*));
    for (int i = 0; i < ht->size; ++i)
        ht->array[i] = NULL;
    return ht;
}
int hashFunction(int key, int size) {
    return key % size;
}
void rehash(struct HashTable** ht) {
    int oldSize = (*ht)->size;
    struct Node** oldArray = (*ht)->array;


    struct HashTable* newHashTable = createHashTable(2 * oldSize);
    (*ht) = newHashTable;


    for (int i = 0; i < oldSize; ++i) {
        struct Node* current = oldArray[i];
        while (current != NULL) {
            insert((*ht), current->key, current->data);
            current = current->next;
        }
    }
    free(oldArray);
}

void insert(struct HashTable* ht, int key, int data) {
    
    if (ht->count >= ht->size) {
        rehash(&ht);
    }

   
    struct Node* newNode = (struct Node*) malloc(sizeof(struct Node));
    newNode->key = key;
    newNode->data = data;
    newNode->next = NULL;

    
    int index = hashFunction(key, ht->size);

   
    newNode->next = ht->array[index];
    ht->array[index] = newNode;
    
    
    ht->count++;
}

void printHashTable(struct HashTable* ht) {
    for (int i = 0; i < ht->size; ++i) {
        printf("Bucket %d: ", i);
        struct Node* current = ht->array[i];
        while (current != NULL) {
            printf("(%d, %d) ", current->key, current->data);
            current = current->next;
        }
        printf("\n");
    }
}

int main() {
    struct HashTable* ht = createHashTable(5);
    

    insert(ht, 1, 10);
    insert(ht, 2, 20);
    insert(ht, 6, 30);
    insert(ht, 11, 40);
    insert(ht, 12, 50);

    // Print the hash table
    printf("Hash Table:\n");
    printHashTable(ht);

    return 0;
}