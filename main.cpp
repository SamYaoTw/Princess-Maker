#include "Attribute.h"
#include "Career.h"
#include "Place.h"
#include <string.h>
#include <stdio.h>

int main() {
	//變數 
	const int MAXday = 14;	//天數上限 
	int day = 1;
	Player   player;
	PlaceDB  placedb;
	CareerDB careerdb;
	
	//初始化資料
	{	//強制區域變數 
		FILE *fattributes = fopen("attributes.txt", "r"),
			 *fplaces     = fopen("places.txt", "r"),
			 *ftitlerules = fopen("titlerules.txt", "r");
		Attribute attribute;
		Place     place;
		Career    career;
		
		//找不到檔案退出程式 
		if (fattributes == nullptr || fplaces == nullptr || ftitlerules == nullptr)
		{
			return 0;
		}
		
		//讀取資料 
			//能力
			//strcpy(attribute.Name, "$"), attribute.Point = 1000;	//設定"$"的能力 
			#這邊我不太清楚是要如何把"$"加入到能力中, 還是說在InitializePlayer()中會順便加入?? 
			#這裡應該跟Place和Career一樣使用Read()和Add()比較妥當 
			if (InitializePlayer(fattributes, &player) == false)	//初始化資料失敗則退出程式 
			{
				return 0;
			}
			//地點 	
			while (ReadPlaces(&fplaces, &place))
			{
				#這裡的AddPlace()中的Place*要加const較為妥當 
				if (AddPlace(placedb, place) == false)		//無法加入則退出程式
				{
					return 0;
				}
			}
			//職業(結局)
			while (ReadCareer(&ftitlerules, &career))
			{
				#這裡的AddCareer()中的Career*要加const較為妥當 
				if (AddCareer(careerdb, career) == false)	//無法加入則退出程式
				{
					return 0;
				}
			}
	}
	
	//開始遊戲 
		printf(	"=========================================\n"
				"|   Princess Maker Extremely Simplied   |\n"
				"=========================================\n\n"	);
		printf(	"ello Princess, what's your name?...(no more than 17 chars)>");
		scanf("%17[^\n]%*[^\n]", player.Name), scanf("%*c");	//輸入名字
		printf(	"\n"
				"Princess %s, let's start the %d-day journey!\n\n", player.Name, MAXday);
		system("pause");
		system("cls");		//清空顯示 
	
	//遊戲主迴圈 
	for (day = 1; day <= MAXday; day++)
	{
		//顯示 
			#我不知道如何取得"$"的數值, 所以先假設"$"的能力會在PA[0] 
			printf("Day %3d (%3d days left)        Princess %s: ($%5d)\n\n", day, MAXday-day, player.Name, player.PA[0].Point);
			//顯示能力
			#這裡一樣先假設"$"的能力在PA[0], 所以i從1開始 
			DisplayAttributeDB(&player);
			printf("==================================================================\n"  );		//分隔線
			printf("All %d places to go:\n", placedb.size);
			//顯示地點 
			for (int i = 0; i < placedb.size; i++)
			{
				printf("[%02d]", i+1);		//地點編號 
				#這裡的DisplayPlace()中的Place*要加const較為妥當 
				DisplayPlace(placedb.P+i);	//地點 
			}
			printf("==================================================================\n\n");		//分隔線
			printf("Which place would you like to go?...(1 ~ 5)>");
		
		//輸入&判斷
			int choice, check;
			char line[1024];
			#這邊其實有點小bug, 假如玩家輸入超過line[]上限有可能會導致遊戲crash, 但老師給的範例程式也有這bug, 經測試上限差不多在1000左右, 這裡就取1024了~~~  OwO 
			scanf("%s%*[^\n]", line), scanf("%*c");		//讀入一行 
			#這邊其實有點小bug, 假如玩家輸入4294967297會導致choice溢位變成1而執行了操作1的動作, 但老師給的範例程式也有這bug, 所以就不改了~~~  OwO 
			check = sscanf(line, "%d%*[\n]", &choice);		//輸入
			//檢查輸入是否正確 
			if (check == 1 && 1 <= choice && choice <= placedb.size)
			{
				//判斷地點是否可以前往
				#這裡的CheckPlaceQualified()中的Place*和Player*要加const較為妥當 
				#另外CheckPlaceQualified()在"Place.h"中也有點問題, bool CheckPlaceQualified(Place * p, Player * p); 兩者變數皆為p會無法編譯, 題外話, 其實在.h中可以不用寫出變數的, 所以可以寫成 bool CheckPlaceQualified(Place*, Player*); 這樣就好 
				#還有CheckPlaceQualified()回傳值不應該為bool, 因為在遊戲中會有3種情況: 1.可以前往 2.因能力不足而無法前往("we are not good enough") 3.因"$"不足而無法前往("we don't have enough money") 
				int Qualified = CheckPlaceQualified(placedb.P+choice-1);
				if (Qualified)
				{
					//前往地點
					printf("After going to BeautySalon, Princess %s makes her ability better:\n\n", player.Name); 
					//計算玩家的能力值 
					#由於沒有對應的函數給我使用, 所以我就直接在main()中直接做玩家能力值的計算 
					for (int i = 0; i < placedb.P[choice-1].size; i++)
					{
						//搜尋能力 
						int attributeIndex = SearchAttribute(&player, placedb.P[choice-1].At[i].Name);
						//計算
						#由於沒有對應的函數給我使用(與DisplayAttribute()不同), 所以我就直接在main()中直接實作顯示能的操作了
						printf("%18s %c%d\n", placedb.P[choice-1].At[i].Name, placedb.P[choice-1].At[i].Point < 0 ? '-' : '+', placedb.P[choice-1].At[i].Point < 0 ? -placedb.P[choice-1].At[i].Point : placedb.P[choice-1].At[i].Point);
						player.PA[attributeIndex].Point += placedb.P[choice-1].At[i].Point;
					}
				}
				else
				{
					//能力不足(不包含"$") 
					#這邊我暫時都以第2種狀況作處理
					printf(	"\n"
							"Sorry, Princess %s, we are not good enough to go to BeautySalon.\n", player.Name);
				}
			}
			else
			{
				//輸入錯誤則當天不做事
				printf(	"\n"
						"Princess %s keeps idle today. Nothing happens.\n", player.Name);
			}
			system("pause");
			system("cls");		//清空顯示 
	}
	
	//遊戲結局
		#這裡一樣先假設"$"的能力在PA[0]
		printf(	"Princess %s: ($%5d)\n\n", player.Name, player.PA[0].Point);
		//顯示能力
		#這裡一樣先假設"$"的能力在PA[0], 所以i從1開始 
		DisplayAttributeDB(&player);
		//搜尋職業 
		#這裡的SearchCareerMatch()中的CareerDB*和Player*要加const較為妥當 
		int careerIndex = SearchCareerMatch(&careerdb, &player);
		//輸出
		printf("After %d days, Princess %s becomes a %s.", MAXday, player.Name, careerIndex < 0 ? "Nobody" : careerdb.C[CareerIndex].name);
		system("pause");
	
	//遊戲結束 
	return 0;
}
