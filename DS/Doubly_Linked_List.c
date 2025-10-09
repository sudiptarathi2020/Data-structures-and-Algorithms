#include<stdio.h>
#include <stdio.h>
#include <stdlib.h>
typedef struct Node{
    int val;
    struct Node *prev;
    struct Node *next;
}node;
typedef struct List{
    int sz;
    node *head;
    node *tail;
}list;
void push_front(list **l,int n){
    if(*l == NULL){
        *l = (list*)malloc(sizeof(list));
        (*l)->sz = 0;
        (*l)->head = (*l)->tail = NULL;
    }
    node *temp = (node*)malloc(sizeof(node));
    temp->val = n;
    temp->prev = NULL;
    temp->next = (*l)->head;
    if((*l)->head){
        (*l)->head->prev = temp;
    }else{
        (*l)->tail = temp;
    }
    (*l)->head = temp;
    (*l)->sz++;
}
void push_back(list **l,int n){
    if(*l == NULL){
        *l = (list*)malloc(sizeof(list));
        (*l)->sz = 0;
        (*l)->head = (*l)->tail = NULL;
    }
    node *temp = (node*)malloc(sizeof(node));
    temp->val = n;
    temp->next = NULL;
    temp->prev = (*l)->tail;
    if((*l)->tail){
        (*l)->tail->next = temp;
    }else{
        (*l)->head = temp;
    }
    (*l)->tail = temp;
    (*l)->sz ++;
}
void pop_front(list **l){
    if(*l == NULL||(*l)->head == NULL){
        return;
    }
    node *temp = (*l)->head;
    (*l)->head = temp->next;
    if((*l)->head){
        (*l)->head->prev = NULL;
    }else{
        (*l)->tail = NULL;
    }
    free(temp);
    (*l)->sz--;
    if((*l)->sz == 0){
        free(*l);
        *l = NULL;
    }
}
void pop_back(list **l){
    if(*l == NULL||(*l)->tail == NULL){
        return;
    }
    node *temp = (*l)->tail;
    (*l)->tail = temp->prev;
    if((*l)->tail){
        (*l)->tail->next = NULL;
    }else{
        (*l)->head = NULL;
    }
    free(temp);
    (*l)->sz--;
    if((*l)->sz == 0){
        free(*l);
        *l = NULL;
    }
}
int front(list *l){
    if(!l||!l->head)return -1000;
    return l->head->val;
}
int back(list *l){
    if(!l||!l->tail)return -1000;
    return l->tail->val;
}
int size(list *l){
    return l?l->sz:0;
}
int main(){
    list *l = NULL;
    for(int i=0;i<5;i++){
        push_front(&l,i);
        push_back(&l,i);
    }
    while(size(l)){
        printf("%d\n",front(l));
        pop_front(&l);
    }
    for(int i=0;i<10;i++){
        push_front(&l,i);
        push_back(&l,i);
    }
    while(size(l)){
        printf("%d\n",back(l));
        pop_back(&l);
    }
}


