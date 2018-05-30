#ifndef ATTRIBUTE_H
    #define ATTRIBUTE_H

    #include <stdio.h>
    #include <stdlib.h>
    #include <string.h>

    struct Attribute
    {
        char Name[30] = {}; //  玩家屬性名字
        int Point = 0;      //  玩家屬性點數
    };
    struct Player
    {
        char Name[30] = {};      //  玩家名字
        Attribute PA[12];        //  玩家屬性陣列
        int size = 0;
    };

    bool ReadAttribute(FILE * fp, Attribute * a);       //從 attribute.txt 取得屬性值名稱
    bool InitializePlayer(FILE * fp, Player * p);
    int SearchAttribute(const Player *, const char *);
    void DisplayAttribute(const Attribute *);               //顯示屬性資訊
    void DisplayAttributeDB(const Player *);                //顯示出玩家所有屬性

#endif
