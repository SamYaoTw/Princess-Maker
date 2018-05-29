#ifndef ATTRIBUTE_H
    #define ATTRIBUTE_H

    #include <stdio.h>
    #include <stdlib.h>
    #include <string.h>

    struct Attribute
    {
        char Name[30] = {}; ///  玩家能力名字
        int Point = 0;      ///  玩家能力點數
    };
    struct Player
    {
        char Name[30] = {};      ///  玩家名字
        Attribute PA[12];        ///  玩家能力陣列
    };

    bool ReadAttribute(FILE * fp, Attribute * a);       ///從 attribute.txt 取得能力值名稱
    bool InitializePlayer(FILE * fp, Player * p);       ///根據 attribute.txt 利用 ReadAttribute 讀入能力資訊 初始化玩家的各項能力資訊
    ///記得回傳成不成功

    void DisplayAttribute(Attribute * a);               ///顯示能力資訊

#endif
