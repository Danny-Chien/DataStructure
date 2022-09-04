#include <stdio.h>
#include <stdlib.h>


#define true 1
#define false 0

typedef struct queuelist qlist;
struct queuelist{
    char info[8];
    struct queuelist *next;
};


int emptyq(const qlist *q)
{
    if(q == NULL)
        return true;
    else
        return false;
}

void insert(qlist **q, char x[8])
{
    qlist* tmp = NULL;
    tmp = (qlist*)calloc(1,sizeof(qlist));
    if(tmp == NULL) return;
    for(int i = 0; i < 8; i++){
        tmp->info[i] = x[i];
    }
    if(emptyq(*q))
        tmp->next = NULL;
    else
        tmp->next = *q;
    *q = tmp;
}

char* removeq(qlist **q)
{
    char* out = calloc(8,sizeof(char));\
    if(*q == NULL)   return 0; 
    qlist* tmp = *q;
    qlist* prev = NULL;
    while(tmp->next != NULL){
        prev = tmp;
        tmp = tmp->next;
    }
    printf("success\n");
    for(int i = 0; i < 8; i++){
        *(out + i) = tmp->info[i];
    }
    if(tmp != *q)
        prev->next = NULL;
    else
        *q = NULL;
    return(out);
    free(tmp);
    free(prev);
}

int main(){

    /*initialize*/
    qlist *ql = NULL; 
    /*variable*/
    char keyin[8] = "\0"; 
    /*main*/
    scanf("%s",keyin);
    insert(&ql,keyin);
    scanf("%s",keyin);
    insert(&ql,keyin);
    while(!emptyq(ql)){
        char* out = removeq(&ql);
        for(int i = 0; i < 8; i++){
            printf("%c",*(out + i));
        }
        printf("\n");
    }
    return 0;
}