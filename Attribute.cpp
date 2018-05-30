#include "Attribute.h"
bool ReadAttribute(FILE * fp, Attribute * a)
{
    if(fp == 0)
    {
        return false;
    }
    else
    {
        fscanf(fp, "%s", a->Name);
        a->Point = 0;
        return true;
    }
}
bool InitializePlayer(FILE * fp, Player * p)
{
    Attribute temp;
    if(!(ReadAttribute(fp, &temp)))
    {
        return false;
    }
    strcpy(p->PA[0].Name, "Money");
    p->PA[0].Point = 1000;
    int i = 1;
    while(ReadAttribute(fp, &temp))
    {
        p->PA[i] = temp;
        i++;
    }
    return true;
}
void DisplayAttribute(const Attribute * a)
{
    printf("%17s %5d\n", a->Name, a->Point);
}
void DisplayAttributeDB(const Player * p)
{
    for(int i = 0;i < p->size;i++)
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
