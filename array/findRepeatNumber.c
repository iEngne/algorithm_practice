#include <stdio.h>
#include <stdlib.h>
#include <string.h>


// 自己实现一种hash表
#define DEFAULT_CAPACITY (256)

typedef struct Node Node;

struct Node {
    int val;
    struct Node* next;
};


typedef struct NstdHashMap {
    int capacity;
    Node** hashTable;
} NstdHashMap;


int hashFunc(int val, int capacity) {
    return (val ^ (val >> 16)) % capacity;
}

NstdHashMap* initHashMap(int capacity) {
    NstdHashMap* hashMap = (NstdHashMap*)malloc(sizeof(NstdHashMap));
    hashMap->hashTable = (Node**)malloc(capacity * sizeof(Node*));
    memset(&hashMap->hashTable[0], 0, capacity);
    hashMap->capacity = capacity;
    return hashMap;
}

Node* find(NstdHashMap* hashMap, int val) {
    int index = hashFunc(val, hashMap->capacity);
    Node* ret = NULL;
    Node* cur = hashMap->hashTable[index];
    while (cur) {
        if (hashMap->hashTable[index]->val == val) {
            ret = hashMap->hashTable[index];
            break;
        }
        cur = cur->next;
    }
    return ret;
}


void add(NstdHashMap* hashMap, int val) {
    int index = hashFunc(val, hashMap->capacity);
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->val = val;
    newNode->next = NULL;
    if (!(hashMap->hashTable[index])) {
        hashMap->hashTable[index] = newNode;
    } else {
        newNode->next = hashMap->hashTable[index];
        hashMap->hashTable[index] = newNode;
    }
    return;
}


void release(NstdHashMap* hashMap) {
    int i;
    Node* tmp = NULL;
    if (hashMap) {
        for (i = 0; i < hashMap->capacity; ++i) {
            Node* cur = hashMap->hashTable[i];
            while (cur) {
                tmp = cur;
                cur = cur->next;
                free(tmp);
            }
        }
        free(hashMap);
    }
}


int findRepeatNumber(int* nums, int numsSize){
    int i = 0;
    int ret = 0;
    NstdHashMap* hashMap = initHashMap(DEFAULT_CAPACITY);
    for (i = 0; i < numsSize; ++i) {
        Node* node = find(hashMap, nums[i]);
        if (!node) {
            add(hashMap, nums[i]);
        } else {
            ret = node->val;
            release(hashMap);
            break;
        }
    }
    return ret;
}

int main(int argc, char** argv)
{
    int arr[] = {2, 3, 1, 0, 2, 5, 3};
    printf("%d\n", findRepeatNumber(arr, sizeof(arr)/sizeof(int)));
    return 0;
}