struct Ability
{
    char Name[30] = {}; ///  玩家能力名字
    int Point = 0;      ///  玩家能力點數
};

// 公主的能力值

struct Player
{
    char Name[30] = {};      ///  玩家名字
    int Money = 0;           ///  玩家目前有的錢
    Ability * PA = 0;        ///  玩家能力陣列
};

struct AbilityCompare
{
    char Name[30] = {}; /// 比較能力名字
    char CS; /// Compare symbol 大於或小於
    bool Type; ///Type = 0 Compare Condition 比較數值, Type = 1 PlayerAbility 比較能力值
    int Condition = 0;
    char CAName[30] = {}; /// CompareAbility name
};
// 根據比較能力值 決定成為哪種職業
/*
Magician:
   Magic > 49
   Magic > Charm

Career->Name -> "Magician"
    Magician:

Career->AbilityCompare->Name -> "Magic"     Career->AbilityCompare->CS -> ">"     Career->AbilityCompare->Type -> "0"       Career->AbilityCompare->Condition = "49"
    Magic > 49

Career->AbilityCompare->Name -> "Magic"     Career->AbilityCompare->CS -> ">"     Career->AbilityCompare->Type -> "1"       Career->AbilityCompare->PlayerAbility = "Charm"
    Magic > Charm
*/
struct Career
{
    char Name[30] = {}; // 職業名稱
    AbilityCompare * Abi = 0;
};
// 職業名稱與職業限制

// 採取行動後獲得的能力值
/*
    NTNU -1000

    Intelligence +10


    Place->Name -> "NTNU"  Place->CostMoney -> "-1000"
    Place->AbilityReward->Name -> "Intelligence"   Place->AbilityReward->AddPoint -> "+10"
*/
struct Place
{
    char Name[30] = {}; // 地方名字
    int CostMoney = 0;  // 去那地方要花多少錢
    Ability * Abi = 0;  // 加的能力陣列
};
// 去某地的名字 花費 與獎勵

bool ReadAbility(FILE * fp, Ability * a);
bool ReadPlaces(FILE * fp, Place * p);
bool ReadCareer(FILE * fp, Career * c);

bool InitializePlayer(FILE * fp, Player * p);

void Display
