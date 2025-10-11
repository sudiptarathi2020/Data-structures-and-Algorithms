#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>
#define TABLE_SIZE 200050
typedef struct Number{
    int val;
    struct Number *next;
}number;
int Hash(int x){
    uint32_t y= (uint32_t)x * 2654435761U;
    return y%TABLE_SIZE;
}
number* Hash_table[TABLE_SIZE];
bool Hash_table_insert(number *n){
    if(n==NULL)return false;
    int index = Hash(n->val);
    n->next = Hash_table[index];
    Hash_table[index]=n;
    return true;
}
number* Hash_table_lookup(number *n){
    int index = Hash(n->val);
    number *tmp = Hash_table[index];
    while(tmp != NULL && tmp->val!=n->val){
        tmp=tmp->next;
    }
    return tmp;
}
number *Hash_table_delete(number *n){
    int index = Hash(n->val);
    number *tmp = Hash_table[index];
    number *prev = NULL;
    while(tmp != NULL && tmp->val!=n->val){
        prev = tmp;
        tmp=tmp->next;
    }
    if(tmp == NULL)return NULL;
    if(prev == NULL){
        Hash_table[index]=tmp->next;
    }else{
        prev->next = tmp->next;
    }
    return tmp;
}
void Hash_table_init(){
    for(int i=0;i<TABLE_SIZE;i++){
        Hash_table[i]=NULL;
    }
}
int main(){
    number one   = {.val = 1};printf("one   insertion: %d\n",Hash_table_insert(&one));
    number two   = {.val = 1};printf("two   insertion: %d\n",Hash_table_insert(&two));
    number three = {.val = 1};printf("three insertion: %d\n",Hash_table_insert(&three));
    number four  = {.val = 1};printf("four  insertion: %d\n",Hash_table_insert(&four));
    number five  = {.val = 1};printf("five  insertion: %d\n",Hash_table_insert(&five));

}

