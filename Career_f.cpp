#include "Career.h"

int SearchCareerMatch(CareerDB * PDB, Player * p)
{
    for(int i = 0;i < PDB->size;i++)
    {
        bool check = 1;
        for(int j = 0;j < PDB->C[i].size;j++)
        {
            int index = SearchAttribute(p, PDB->C[i].At[j].Name);
            if(index == -1)
            {
                check = 0;
                break;
            }
            if(PDB->C[i].At[j].Type == 0)
            {
                if(PDB->C[i].At[j].CS == '<')
                {
                    if(p->PA[index].Point >= PDB->C[i].At[j].Condition)
                    {
                        check = 0;
                        break;
                    }
                }
                else
                {
                    if(p->PA[index].Point <= PDB->C[i].At[j].Condition)
                    {
                        check = 0;
                        break;
                    }
                }
            }
            else
            {
                int index_b = Search(p, PDB->C[i].At[j].CAName);
                if(PDB->C[i].At[j].CS == '<')
                {
                    if(p->PA[index].Point >= p->PA[index_b].Point)
                    {
                        check = 0;
                        break;
                    }
                }
                else
                {
                    if(p->PA[index].Point <= p->PA[index_b].Point)
                    {
                        check = 0;
                        break;
                    }
                }
            }
        }
        if(check)
            return i;
    }
    return -1;
}
