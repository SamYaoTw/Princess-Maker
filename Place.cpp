#include "Place.h"
#include <ctype.h>
bool ReadPlaces(FILE * fp, Place * p) //�q places.txt ���o�a���T
{
    p->size = 0; //initialize
    char line[100]={}; //�C��Ū�@��

    if(fgets(line,90,fp)!=0) //BeautySalon +1000
    {
        sscanf(line, "%s%d", p->Name, &p->At[p->size].Point);
        strcpy(p->At[p->size].Name, "$");
        p->size += 1;
    }
    else return false;

    while(true)
    {
        if(fgets(line,90,fp)!=0)  //   Intelligence -5 ,   Charm +8 ....
        {
            if(line[0]=='#') break;
            sscanf(line, "%s%d", p->At[p->size].Name, &p->At[p->size].Point);
            p->size += 1;
        }
        else return false;
    }
    return true;
}

bool AddPlace(PlaceDB * PDB, const Place * p)
{
    if(PDB->size < 0 || PDB->size>=12) return false;
    PDB->P[PDB->size] = *p;
    PDB->size +=1;
    return true;
}

int CheckPlaceQualified(const Place *p, const Player *pl) //�ˬd�Ӧa��O�_�i�H�h
{
    //money
    int index = SearchAttribute(pl,p->At[0].Name);
    if(index == -1) return -1;
    if(pl->PA[index].Point + p->At[0].Point < 0) return 3;

    //attribute
    for(int i=1;i<p->size;i++)
    {
        int index = SearchAttribute(pl,p->At[i].Name);
        if(index ==-1) return -1;
        if(pl->PA[index].Point + p->At[i].Point < 0) return 2;
    }
    return 1;
}
/*
    �^��-1�N��L����O��
    �^��1�N��i�H�e��
    �^��2�N���O�����L�k�e��
    �^��3�N�������
*/


void AddPlayerAttributeByPlace(Place *p, Player *pl) //�ھڸӦa�誺��T�缾�a���ݩʭȰ��ާ@
{
    for(int i=0;i<p->size;i++)
    {
        for(int j=0;j<pl->size;j++)
        {
            if( strcmp(p->At[i].Name,pl->PA[j].Name)==0 )
            {
                pl->PA[j].Point += p->At[i].Point;
                break;
            }
        }
    }
}

void DisplayPlace(const Place * p, const Player *pl) //��ܦa���T �Q��CheckPlaceQualified�ˬd�Ӧa��O�_�i�H�h
{
    // NTNU  $ -1000  INT  +10 CHA  +10 ELE  +10 MAG  +10
    printf("%18s  ",p->Name);
    int qualified = CheckPlaceQualified(p,pl);
    if(qualified==2) printf("- Unqualified\n");
    else if (qualified == 3) printf("- Unaffordable\n");
    else
    {
        for(int i=0;i<p->size;i++)
        {
            char name[5] = {};
            char line[10];
            for (int k = 0; p->At[i].Name[k] && k < 3; k++)
                name[k] = toupper(p->At[i].Name[k]);
            name[3] = '\0';
            sprintf(line, "%c%d", p->At[i].Point < 0 ? '-' : '+', p->At[i].Point < 0 ? -p->At[i].Point : p->At[i].Point);
            printf("%3s%5s  ", name, line);
        }
        printf("\n");
    }
}


// AddPlayerAttributeByPlace�BDisplayPlace�����
