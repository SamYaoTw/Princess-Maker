#ifndef ATTRIBUTE_H
    #define ATTRIBUTE_H

    #include <stdio.h>
    #include <stdlib.h>
    #include <string.h>

    struct Attribute
    {
        char Name[30] = {}; ///  玩家屬性名字
        int Point = 0;      ///  玩家屬性點數
    };
    struct Player
    {
        char Name[30] = {};      ///  玩家名字
        Attribute PA[12];        ///  玩家屬性陣列
        int size = 0;
    };

    bool ReadAttribute(FILE * fp, Attribute * a);       ///從 attribute.txt 取得屬性值名稱
    bool InitializePlayer(FILE * fp, Player * p);       ///根據 attribute.txt 利用 ReadAttribute 讀入屬性資訊 初始化玩家的各項屬性資訊
    ///記得回傳成不成功
    int SearchAttribute(const Player *, const char * AttributeName); ///從玩家資料庫中根據屬性名稱搜尋 回傳該屬性的索引值
    /// 輸出-1表示甚麼都不符合
    void DisplayAttribute(const Attribute * a);               ///顯示屬性資訊
    void DisplayAttributeDB(const Player * p);                ///顯示出玩家所有屬性

#endif
