#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#define NUM_LETTERS 26
#define ALOCFAIL "Failed to allocate memory.\n"

struct node *head;
typedef enum {FALSE=0, TRUE=1} boolean;
typedef struct node {
    char letter;
    long unsigned int count;
    struct node* children[NUM_LETTERS];
    int dist;
} node;

struct node* newNode(){
    struct node *new_node = (struct node*)malloc(sizeof(node));
    for(int i = 0; i < NUM_LETTERS; i++){
        new_node->children[i] = NULL;
    }
    new_node->count = 0;
    new_node->dist = -1;
    return new_node;
}

void insert(struct node *head, char s[]){
    struct node *n = head;
    int i = 0;
    while (s[i] != '\0'){
        char c = s[i];
        if((int)c >= 'A' && (int)c <= 'Z') c = c + 32;
        if(c < 'a' || c > 'z'){
            i++;
            continue;
        }
        int currInd = (int)c - (int)'a';
        if(n->children[currInd] == NULL){
            n->children[currInd] = newNode();
            n->children[currInd]->dist = n->dist+1;
            n->children[currInd]->letter = c;
        }
        n = n->children[currInd];
        i++;
    }
    if(isalpha(n->letter)){
    n->count++;
    }
}

void printPreorder(node *n, char *s){
    if(n == NULL) return;
    s[n->dist] = n->letter;
    if(n->count != 0){
        s[n->dist+1] = '\0';
        printf("%s %ld\n",s , n->count);
    }
    for (int i = 0; i < NUM_LETTERS; i++){
        printPreorder(n->children[i], s);
    }
}

void printReversePreorder(node *n, char *s){
    if(n == NULL) return;
    s[n->dist] = n->letter;
    for (int i = NUM_LETTERS-1; i >= 0; i--){
        printReversePreorder(n->children[i], s);
    }
    if(n->count != 0){
        s[n->dist+1] = '\0';
        printf("%s %ld\n",s , n->count);
    }
}

void freeAll(node *head){
    if(head == NULL) return;
    for (int i = 0; i < NUM_LETTERS; i++){
        freeAll(head->children[i]);
    }
    free(head);
}

int main(int argc, char *argv[]){
    head = (struct node*)malloc(sizeof(node));
    head->dist = -1;
    // head->dist = -1;
    char *s = (char*)malloc(sizeof(char));
    int cnt = 0;
    boolean flag = TRUE;
    do{
        char c = getchar();
        if(c == ' ' || c == '\n' || c == '\t' || c == EOF){
            s = realloc(s, (cnt+1)*sizeof(char));
            s[cnt] = '\0';
            insert(head, s);
            cnt = 0;
            if(c == EOF){
                flag = FALSE;
                continue;
            }
        }
        else if(isalpha(c)){
            c = tolower(c);
            s = realloc(s, (cnt+1)*sizeof(char));
            s[cnt++] = c;
        }
    }while(flag);
    if(argc == 1){
        printPreorder(head, s);
    }
    else if(*argv[1] == 'r'){
        printReversePreorder(head, s);
    }
    freeAll(head);
    free(s);
    return 0;
}