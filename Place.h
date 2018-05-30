#ifndef PLACE_H
    #define PLACE_H

    #include <stdio.h>
    #include <stdlib.h>
    #include <string.h>
    #include "Attribute.h"

    struct Place
    {
        char Name[30] = {}; /// 地方名字
        Attribute At[12];  /// 加的能力陣列
        int size = 0;
    };
    /// 去某地的名字 與獎勵
    struct PlaceDB
    {
        Place P[12];
        int size = 0;
    };
    /// 地方資料庫

    bool ReadPlaces(FILE * fp, Place * p);              ///從 places.txt 取得地方資訊
    bool AddPlace(PlaceDB * PDB, const Place * p);            ///將地方加入地方資料庫
    ///記得回傳成不成功

    bool CheckPlaceQualified(const Place * p, const Player * p);    ///檢查該地方是否可以去
    void DisplayPlace(const Place * p);                       ///顯示地方資訊 利用CheckPlaceQualified檢查該地方是否可以去

#endif
