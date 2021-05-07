#include<stdio.h>
#include<stdlib.h>

typedef struct huffmanNode {
    char data;
    int freq;
    struct huffmanNode *left, *right;
} NODE;

void heapInsert(NODE** newNode, NODE* heap[]);
NODE* heapRemove(NODE* heap[]);
NODE* constructTree(NODE* heap[]);
void preorder(NODE** root);
void inorder(NODE** root);

int main() {
    NODE* heapArray[100];
    NODE* root;
    char controlChar;
    int quit = 0;
    int i;
    int j;
    int count = 0;
    
    for(i = 0; i < 100; ++i) {
        heapArray[i] = NULL;
    }
    
    while(!quit) {
        NODE* newNode = malloc(sizeof(NODE));
        printf("enter a char or $ to quit: ");
        scanf(" %c", &controlChar);
        if(controlChar == '$') {
            quit = 1;
        } else {
            (newNode->data) = controlChar;
            printf("enter the freq: ");
            scanf(" %d", &(newNode->freq));
            heapInsert(&newNode, heapArray);
            ++count;
        }
    }
    if(heapArray[1] != NULL){
        printf("HEAP ARRAY: ");
        for(j = 1; j < (count + 1); ++j) {
            printf("%d ", heapArray[j]->freq);
        }
        printf("\n\n");
        root = constructTree(heapArray);
        printf("PREORDER: ");
        preorder(&root);
        printf("\n");
        printf("INORDER: ");
        inorder(&root);
        printf("\n");
    }
    return 0;
}

void heapInsert(NODE** newNode, NODE* heap[]) {
    NODE* temp;
    int i;
    int done = 0;
    if(heap[1] == NULL) {
        heap[1] = *newNode;
    } else {
        for(i = 2; i < 100; ++i) {
            if(heap[i] == NULL) {
                heap[i] = *newNode;
                break;
            }
        }
        while(!done) {
            if ((i/2 != 0) && (heap[i]->freq < heap[i/2]->freq)) {
                temp = heap[i/2];
                heap[i/2] = heap[i];
                heap[i] = temp;
                i = i / 2;
            } else {
                done = 1;
            }
        }
    }
}

NODE* heapRemove(NODE* heap[]) {
    NODE* value = heap[1];
    NODE* temp;
    int i;
    int done = 0;
    heap[1] = NULL;
    for(i = 2; i < 100; ++i) {
        if(heap[i] == NULL) {
            break;
        }
    }
    if(!((i - 1) < 1)) {
        heap[1] = heap[i-1];
        heap[i-1] = NULL;
    }
    while(!done) {
        if ((i/2 != 0) && (heap[i]->freq < heap[i/2]->freq)) {
            temp = heap[i/2];
                heap[i/2] = heap[i];
                heap[i] = temp;
                i = i / 2;
            } else {
                done = 1;
            }
    }
    return value;  
}

NODE* constructTree(NODE* heap[]) {
    NODE* root;
    NODE* leftChild;
    NODE* rightChild;
    while(heap[2] != NULL) {
        root = malloc(sizeof(NODE*));
        leftChild = heapRemove(heap);
        rightChild = heapRemove(heap);
        
        root->left = leftChild;
        root->right = rightChild;
        root->data = '-';
        root->freq = (leftChild->freq) + (rightChild->freq);
        
        heapInsert(&root, heap);
    }
    
    return root;
}

void preorder(NODE** root) {
    printf("(%c, %d) ", (*root)->data, (*root)->freq);
    
    if((*root)->left != NULL)
        preorder(&((*root)->left));
    if((*root)->right != NULL)
        preorder(&((*root)->right));
}

void inorder(NODE** root) {
    if((*root)->left != NULL)
        inorder(&((*root)->left));
        
    printf("(%c, %d)", (*root)->data, (*root)->freq);
    
    if((*root)->right != NULL)
        inorder(&((*root)->right));
}