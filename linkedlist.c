#include <stdio.h>
#include <stdlib.h>

typedef struct node NODE;

struct node{
    int info;
    struct node *next;
};

NODE *list = NULL;

void printlist(NODE *list)
{
	while(list != NULL)
	{
		printf("%d\n",list->info);
		list = list->next;
	}
}

void push(NODE **list,int a)  //add at the bottom
{
	NODE *head = *list;
	NODE *tmp =(NODE*)calloc(1,sizeof(NODE));
    if(tmp == NULL)	return;
	if((*list) == NULL)
    {
		tmp->info = a;
    	tmp->next = NULL;
    	head = tmp;       //give the dynamic memory address to the first of list	  
	}
	else
	{
		while ((*list)->next != NULL) 
		{
        	(*list) = (*list)->next;
    	}
		tmp->info = a;
		tmp->next = NULL;
		(*list)->next = tmp;
	}
	*list = head;
}

void insert(NODE **list,int a)
{
	NODE *head = *list;
	NODE *tmp =(NODE*)calloc(1,sizeof(NODE));
    if(tmp == NULL)	return;
	if((*list) == NULL)
    {
		tmp->info = a;
    	tmp->next = NULL;
    	head = tmp;       //give the dynamic memory address to the first of list	  
	}
	else
	{
		tmp->info = a;
		tmp->next = *list;
		head = tmp;
	}
	*list = head;
}

int main(void){
	push(&list,3);
	push(&list,4);
	push(&list,5);
	push(&list,6);
	push(&list,7);
	insert(&list,2);
	insert(&list,8);
	printlist(list);

	return 0;

}