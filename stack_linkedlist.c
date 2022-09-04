#include <stdio.h>
#include <stdlib.h>

#define true 1
#define false 0

typedef struct stacklist slist;
struct stacklist{
    // char* info;
    char info[8];
    struct stacklist *next;
};


int empty(const slist *s)
{
    if(s == NULL)
        return true;
    else
        return false;
}

void push(slist **s, char x[8])
{
    slist* tmp = NULL;
    tmp = (slist*)calloc(1,sizeof(slist));
    if(tmp == NULL) return;
    for(int i = 0; i < 8; i++){
        tmp->info[i] = x[i];
    }
    if(empty(*s))
        tmp->next = NULL;
    else
        tmp->next = *s;
    *s = tmp;
}

char* pop(slist **s)
{
    char* out = calloc(8,sizeof(char));
    slist* tmp = NULL;
    if(empty(*s))   return 0; 
    tmp = *s;
    for(int i = 0; i < 8; i++){
        *(out + i) = tmp->info[i];
    }
    *s = (*s)->next;
    return(out);
    free(tmp);
}

// int main(){

//     /*initialize*/
//     slist *sl = NULL; 
//     /*variable*/
//     char keyin[9]; 
//     /*main*/
//     while(1){
//         scanf("%s",keyin);
//         push(&sl,keyin);
//         char* out = pop(&sl);
//         for(int i = 0; i < 8; i++){
//             printf("%c",*(out + i));
//         }
//         printf("\n");
//     }
    
//     return 0;
// }