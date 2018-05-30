#include "Career.h"
bool ReadCareer(FILE * fp, Career * c)
{
    if(fp == 0)   return false;
    else
    {
        fgets(c->Name,50,fp);
        if(c->Name[0] == '\0')  return false;
        for(int i=0 ; (c->Name[strlen(c->Name)-1] <= 'a' || c->Name[strlen(c->Name)-1] >= 'z') && (c->Name[strlen(c->Name)-1] <= 'A' || c->Name[strlen(c->Name)-1] >= 'Z') ; i++)    c->Name[strlen(c->Name)-1] = '\0';
        char str[50]= {};
        while(fgets(str,50,fp))
        {
            if(c->size >= 12)   return false;
            if(str[0] == '#')   break;
            sscanf(str,"%s %c %s",c->At[c->size].Name,&c->At[c->size].CS,c->At[c->size].CAName);
            if(c->At[c->size].CAName[0] >= '0' && c->At[c->size].CAName[0] <= '9')
            {
                int count = 0;
                for(int i=0 ; c->At[c->size].CAName[i] != '\0' ; i++)
                {
                    count *= 10;
                    count += c->At[c->size].CAName[i]-'0';
                }
                for(int i=0 ; i<strlen(c->At[c->size].CAName) ; i++)
                {
                    c->At[c->size].CAName[i] = '\0';
                }
                c->At[c->size].Condition = count;
                c->At[c->size].Type = 0;
            }
            else    c->At[c->size].Type = 1;
            c->size += 1;
        }
        return true;
    }
}

bool AddCareer(CareerDB *PDB,Career *c)
{
	if(PDB->size >= 12)     return false;
	else
    {
        PDB->C[PDB->size] = *c;
        PDB->size += 1;
        return true;
    }
}

int SearchCareerMatch(CareerDB * PDB, Player * p)
{
    bool check = true;
    for(int i=0 ; i<PDB->size ; i++)
    {
        check = true;
        for(int j=0 ; j<PDB->C[i].size ; j++)
        {
            for(int k=0 ; k<p->size ; k++)
            {
                if(strcmp(PDB->C[i].At[j].Name,p->PA[k].Name) == 0)
                {
                    if(!PDB->C[i].At[j].Type)
                    {
                        if(PDB->C[i].At[j].CS == '>')
                        {
                            if(p->PA[k].Point <= PDB->C[i].At[j].Condition)
                            {
                                check = false;
                                break;
                            }
                        }
                        else if(PDB->C[i].At[j].CS == '<')
                        {
                            if(p->PA[k].Point >= PDB->C[i].At[j].Condition)
                            {
                                check = false;
                                break;
                            }
                        }
                    }
                    else
                    {
                        for(int l=0 ; l<p->size ; l++)
                        {
                            if(strcmp(PDB->C[i].At[j].CAName,p->PA[l].Name) == 0)
                            {
                                if(PDB->C[i].At[j].CS == '>')
                                {
                                    if(p->PA[k].Point <= p->PA[l].Point)
                                    {
                                        check = false;
                                        break;
                                    }
                                }
                                else if(PDB->C[i].At[j].CS == '<')
                                {
                                    if(p->PA[k].Point >= p->PA[l].Point)
                                    {
                                        check = false;
                                        break;
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
        if(check)   return i;
    }
    return -1;
}
