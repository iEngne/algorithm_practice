#include <stdio.h>
#include <stdlib.h>


#define DEFAULT_CAPACITY (128)
#define RATIO (0.75f)

typedef struct Node {
    int val;
    int index;
    struct Node* next;
} Node;

typedef struct NStdHashMap {
    int capacity;
    Node** heads;
} NStdHashMap;


int hashFunc(int val, int capacity) {
    return ((val ^ (val >> 16)) % capacity);
}

NStdHashMap* add(NStdHashMap* hashMap, int val, int index) {
    if (!hashMap) {
        hashMap = (NStdHashMap*)malloc(sizeof(NStdHashMap));
        if (!hashMap) {
            goto _exit0;
        }
        hashMap->heads = (Node**)calloc(DEFAULT_CAPACITY , sizeof(Node*));
        if (!hashMap->heads) {
            printf("out of mem:%d\n", __LINE__);
            goto _exit1;
        }
        hashMap->capacity = DEFAULT_CAPACITY;
    }
    int key = hashFunc(val, hashMap->capacity);
    if (!hashMap->heads[key]) {
        Node* node = (Node*)malloc(sizeof(Node));
        if (!node) {
            printf("out of mem:%d\n", __LINE__);
            goto _exit2;
        }
        node->next = NULL;
        node->val = val;
        node->index = index;
        hashMap->heads[key] = node;
    } else {
        Node* current = hashMap->heads[key];
        // 已经存在相同元素，覆盖下标
        while (current) {
            if (current->val == val) {
                current->index = index;
                return hashMap;
            }
            current = current->next;
        }
        Node* node = (Node*)malloc(sizeof(Node));
        if (!node) {
            printf("out of mem:%d\n", __LINE__);
            goto _exit2;
        }
        node->next = NULL;
        node->val = val;
        node->index = index;
        node->next = hashMap->heads[key];
        hashMap->heads[key] = node;
    }

_exit0:
    return hashMap;
_exit1:
    free(hashMap);
    return hashMap;
_exit2:
    free(hashMap->heads);
    free(hashMap);
    return hashMap;
}


Node* find(NStdHashMap* hashMap, int val) {
    int key = hashFunc(val, hashMap->capacity);

    // 可能存在hash碰撞
    if (hashMap->heads[key]) {
        Node* current = hashMap->heads[key];
        while (current) {
            if (current->val == val) {
                return current;
            }
            current = current->next;
        }
    } 
    return NULL;
}


void del(NStdHashMap* hashMap, int val, int index) {
    int key = hashFunc(val, hashMap->capacity);
    
    if (hashMap->heads[key]) {
        Node* current = hashMap->heads[key];
        Node* pre = current;
        while (current) {
            if (current->val == val && current->index == index) {
                pre->next = current->next;
                free(current);
                return;
            }
            pre = current;
            current = current->next;
        }
    } else {
        return;
    }
}


void releaseHashMap(NStdHashMap* hashMap) {
    int i = 0;
    for (i = 0; i < hashMap->capacity; ++i) {
        Node* current = hashMap->heads[i];
        Node* tmp = NULL;
        while (current) {
            tmp = current->next;
            free(current);
            current = tmp;
        }
        hashMap->heads[i] = NULL;
    }
    free(hashMap->heads);
    free(hashMap);
    return;
}


int* twoSum(int* nums, int numsSize, int target, int* returnSize) {
    int i = 0;
    NStdHashMap* hashMap = NULL;
    for (i = 0; i < numsSize; ++i) {
        hashMap = add(hashMap, nums[i], i);
        if (!hashMap) {
            printf("add error\n");
        }
    }
    Node* node;
    for (i = 0; i < numsSize; ++i) {
        int ano = target - nums[i];
        node = find(hashMap, ano);
        if (node && node->index != i) {
            printf("i = %d, ano = %d\n", nums[i], ano);
            break;
        }
    }

    int* res = (int*)malloc(2 * sizeof(int));
    res[0] = i;
    res[1] = node->index;
    *returnSize = 2;
    releaseHashMap(hashMap);
    return res;
}

int main(void){
    int array[] = {1,2,3,4,5,6,7,7,15,18};
    int returnSize = 0;
    int* p = twoSum(array, sizeof(array), 14, &returnSize);
    if (p) {
        printf("[%d, %d]\n", p[0], p[1]);
        free(p);
    }
    return 0;
}