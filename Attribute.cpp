#include "Attribute.h"
bool ReadAttribute(FILE * fp, Attribute * a)
{
    if(fp == 0)
    {
        return false;
    }
    else
    {
        int checkEOF;
        checkEOF = fscanf(fp, "%s", a->Name);
        if (checkEOF != 1)
        {
            return false;
        }
        a->Point = 0;
        return true;
    }
}
bool InitializePlayer(FILE * fp, Player * p)
{
    Attribute temp;
    strcpy(p->PA[0].Name, "$");
    p->PA[0].Point = 1000;
    int i = 1;
    while(ReadAttribute(fp, &p->PA[i]))
    {
        i++;
    }
    p->size = i;
    return true;
}
void DisplayAttribute(const Attribute * a)
{
    printf("%17s %5d     ", a->Name, a->Point);
    for (int star = a->Point/10; star--; )
        printf("*");
    printf("\n");
}
void DisplayAttributeDB(const Player * p)
{
    for(int i = 1;i < p->size;i++)
    {
        DisplayAttribute(&p->PA[i]);
    }
}
int SearchAttribute(const Player *a, const char * AttributeName)
{
    for(int i = 0;i < a->size;i++)
    {
        if(strcmp(a->PA[i].Name, AttributeName) == 0)
        {
            return i;
        }
    }
    return -1;
}
