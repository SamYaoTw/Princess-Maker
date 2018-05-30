#include"Attribute.h"
bool ReadAttribute(FILE * fp, Attribute * a)
{
    if(fp==0)
    {
        return false;
    }
    else
    {
        fscanf(fp,"%s",a->Name);
        a->Point=0;
        return true;
    }
}
bool InitializePlayer(FILE * fp, Player * p)
{
    Attribute temp;
    if(!(ReadAttribute(fp,&temp)))
    {
        return false;
    }
    int i=0;
    while(ReadAttribute(fp,&temp))
    {
        p->PA[i] = temp;
        i++;
    }
    return true;
}
void DisplayAttribute(Attribute * a)
{
    printf("%17s %5d\n",a->Name,a->Point);
}
