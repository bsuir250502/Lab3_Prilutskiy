#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct stack
{
    char symbol;
    struct stack * next;
}stack;

void add(stack ** HEAD, char element)
{
    stack * tmp = (stack*)calloc(1,sizeof(stack));
    tmp->symbol = element;
    tmp->next = *HEAD;
    *HEAD = tmp;
}

void del (stack ** HEAD)
{
    stack * current;
    if (!*HEAD) return;
    current = *HEAD;
    *HEAD=current->next;
    free(current);
}

void show (stack * HEAD)
{
    stack * tmp = HEAD;
    while (tmp)
    {
        printf("%c ",tmp->symbol);
        tmp=tmp->next;
    }
    puts("");
}
void free_stack(stack * source)
{
    stack * tmp1 = source;
    while (tmp1)
    {
        stack * tmp2 = tmp1->next;
        free(tmp1);
        tmp1 = tmp2;
    }
    
}

int exp_check(char* source, stack * HEAD)
{
    int length = strlen(source);
    for (int i=0; i<length; i++)
    {
        if (source[i]=='.' || source[i]==':' || source[i]==';') break;
        if ((source[i]==')' || source[i]==']' || source[i]=='}') && HEAD==NULL)
            return 0;
        if (source[i]=='(' || source[i]=='[' || source[i]=='{')
            add(&HEAD, source[i]);
        if (source[i]==')' && HEAD->symbol=='(')
            del(&HEAD);
        if (source[i]==']' && HEAD->symbol=='[')
            del(&HEAD);
        if (source[i]=='}' && HEAD->symbol=='{')
            del(&HEAD);
    }
    if (!HEAD) return 1;
    else return 0;
}

void show_help()
{
    puts("Help Info:\n");
    puts("1. Enter expressions quantity\n2. Enter your expressions\n3.Wait for program output: your expressions will be checked, wether the brackets placed properly\n4. The End.");
}

int main(int argc, char * argv[])
{
    if (argc>1)
    {
        if (strcmp(argv[1],"-h")==0)
        {
             show_help();
             return 0;
        }
        else
        {
            puts("Error. Improper parameter");
            return 0;
        }
    }
    stack * head = NULL;
    puts("Enter number of expressions");
    char buf[10];
    fgets(buf,10,stdin);
    int exp_num = atoi(buf);

    char ** exp = (char**)calloc(exp_num, sizeof(char*));
    for (int i=0; i<exp_num; i++)
        exp[i] = (char*)calloc(200,sizeof(char));

    for (int i=0; i<exp_num; i++)
    {
        printf("Type %d Expression\n",i+1);
        fgets(exp[i],200,stdin);
    }
    puts("Expressions loaded");

    for (int i=0; i<exp_num; i++)
    {
        printf("%d Expression:\n%s - ",i+1,exp[i]);
        if(exp_check(exp[i], head)) puts("OK\n");
        else puts("NOT OK\n");
    }

    for (int i=0; i<exp_num; i++)
        free(exp[i]);
    free(exp);
    free(head);
    return 0;
}
