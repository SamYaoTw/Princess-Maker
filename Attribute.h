#ifndef ATTRIBUTE_H
    #define ATTRIBUTE_H

    #include <stdio.h>
    #include <stdlib.h>
    #include <string.h>

    struct Attribute
    {
        char Name[30] = {}; //  ���a�ݩʦW�r
        int Point = 0;      //  ���a�ݩ��I��
    };
    struct Player
    {
        char Name[30] = {};      //  ���a�W�r
        Attribute PA[12];        //  ���a�ݩʰ}�C
        int size = 0;
    };

    bool ReadAttribute(FILE * fp, Attribute * a);       //�q attribute.txt ���o�ݩʭȦW��
    bool InitializePlayer(FILE * fp, Player * p);
    int SearchAttribute(const Player *, const char *);
    void DisplayAttribute(const Attribute *);               //����ݩʸ�T
    void DisplayAttributeDB(const Player *);                //��ܥX���a�Ҧ��ݩ�

#endif
