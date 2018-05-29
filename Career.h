#ifndef CAREER_H
    #define CAREER_H

    #include <stdio.h>
    #include <stdlib.h>
    #include <string.h>
    #include "Attribute.h"

    struct AttributeCompare
    {
        char Name[30] = {}; /// 比較能力名字
        char CS; /// Compare symbol 大於或小於
        bool Type; ///Type = 0 Compare Condition 比較數值, Type = 1 CAName 比較能力值
        int Condition = 0; /// 比較數值
        char CAName[30] = {}; /// CompareAttribute name 比較能力值的名字
    };
    /// 根據比較能力值 決定成為哪種職業
    /*
    Magician:
       Magic > 49
       Magic > Charm

    Career->Name -> "Magician"
        Magician:

    Career->At->Type -> "0"
    Career->At->Name -> "Magic"
    Career->At->CS -> ">"
    Career->At->Condition = "49"
        Magic > 49

    Career->At->Type -> "1"
    Career->At->Name -> "Magic"
    Career->At->CS -> ">"
    Career->At->CAName = "Charm"
        Magic > Charm
    */
    struct Career
    {
        char Name[30] = {};         /// 職業名稱
        AttributeCompare At[12];    /// 職業需求
    };
    /// 職業名稱與職業限制

    struct CareerDB
    {
        Career C[12];
        int size = 0;
    };
    /// 職業資料庫
    /// 採取行動後扣的錢 與 獲得的能力值

    bool ReadCareer(FILE * fp, Career * c);             ///從 titlerules.txt 取得職業資訊
    bool AddCareer(CareerDB * PDB, Career * p);         ///將職業加入職業資料庫
    ///記得回傳成不成功

    int SearchCareerMatch(CareerDB * PDB, Player * p);  /// 查詢資料庫中是否有符合要求的職業 若有則回傳該職業在該資料庫中的索引Index
    /// 輸出-1表示甚麼都不符合

#endif
