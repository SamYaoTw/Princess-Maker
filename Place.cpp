#include "Place.h"
#include <ctype.h>
bool ReadPlaces(FILE * fp, Place * p) //從 places.txt 取得地方資訊
{
    p->size = 0; //initialize
    char line[100]={}; //每次讀一行

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

int CheckPlaceQualified(const Place *p, const Player *pl) //檢查該地方是否可以去
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
    回傳-1代表無此能力值
    回傳1代表可以前往
    回傳2代表能力不足無法前往
    回傳3代表錢不夠
*/


void AddPlayerAttributeByPlace(Place *p, Player *pl) //根據該地方的資訊對玩家的屬性值做操作
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

void DisplayPlace(const Place * p, const Player *pl) //顯示地方資訊 利用CheckPlaceQualified檢查該地方是否可以去
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


// AddPlayerAttributeByPlace、DisplayPlace有更動
