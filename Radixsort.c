#include <stdio.h>
#include <stdlib.h>


struct node{
    int info;
    struct node *next;
};

typedef struct node Node;
typedef struct node *NODE;


void Radixsort(int num, NODE *list)
{
    NODE head = (*list);
    NODE tmp = (NODE)calloc(1,sizeof(Node));
    if(tmp == NULL) return;
    tmp->info = num;
    tmp->next = NULL;
    if( (*list) != NULL ){
        while ((*list)->next != NULL) 
        	(*list) = (*list)->next;
        (*list)->next = tmp;
        (*list) = head;
    }
    else
        (*list) = tmp;
    free(tmp);
    return;

}

int main(void)
{
    NODE num0 = NULL, num1 = NULL, num2 = NULL, num3 = NULL, num4 = NULL, num5 = NULL, num6 = NULL, num7 = NULL, num8 = NULL, num9 = NULL;
    // NODE *num0 = NULL, *num1 = NULL, *num2 = NULL, *num3 = NULL, *num4 = NULL, *num5 = NULL, *num6 = NULL, *num7 = NULL, *num8 = NULL, *num9 = NULL;
    int array[8] = {25,57,48,37,12,2,86,33};
    int num = 0;
    for(int i = 0; i < 8; i++){
        num = array[i] % 10;
        printf("%d\n",num);
        switch(num){
            case 0:
                Radixsort(array[i],&num0);
                break;
            case 1:
                Radixsort(array[i],&num1);
                break;
            case 2:
                Radixsort(array[i],&num2);
                printf("a\n");
                break;
            case 3:
                Radixsort(array[i],&num3);
                break;
            case 4:
                Radixsort(array[i],&num4);
                break;
            case 5:
                Radixsort(array[i],&num5);
                break;
            case 6:
                Radixsort(array[i],&num6);
                break;
            case 7:
                Radixsort(array[i],&num7);
                break;
            case 8:
                Radixsort(array[i],&num8);
                break;
            case 9:
                Radixsort(array[i],&num9);
                break;
            default:
                break;
        }
    }
    if(num0 != NULL)
        printf("%d\n",num0->info);
    if(num1 != NULL)
        printf("%d\n",num1->info);
    if(num2 != NULL)
        printf("%d\n",num2->info);
    if(num3 != NULL)
        printf("%d\n",num3->info);
    if(num4 != NULL)
        printf("%d\n",num4->info);
    if(num5 != NULL)
        printf("%d\n",num5->info);
    if(num6 != NULL)
        printf("%d\n",num6->info);
    if(num7 != NULL)
        printf("%d\n",num7->info);
    if(num8 != NULL)
        printf("%d\n",num8->info);
    if(num9 != NULL)
        printf("%d\n",num9->info);
    return 0;
}