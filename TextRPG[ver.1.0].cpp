#include <iostream>
#include <time.h>
#include <stdlib.h>

using namespace std;

enum MAIN_MENU
{
	MM_NONE,
	MM_MAP,
	MM_STORE,
	MM_INVENTORY,
	MM_EXIT
};

enum MAP_TYPE
{
	MT_NONE,
	MT_EASY,
	MT_NORMAL,
	MT_HARD,
	MT_BACK
};

enum JOB
{
	JOB_NONE,
	JOB_KNIGHT,
	JOB_ARCHER,
	JOB_WIZARD,
	JOB_END
};

enum BATTLE
{
	BATTLE_NONE,
	BATTLE_ATTACK,
	BATTLE_BACK,
	BATTLE_END
};

enum ITEM_TYPE
{
	IT_NONE,
	IT_WEAPON,
	IT_ARMOR,
	IT_BACK
};

enum STORE_MENU
{
	SM_NONE,
	SM_WEAPON,
	SM_ARMOR,
	SM_BACK
};

enum EQUIP
{
	EQ_WEAPON,
	EQ_ARMOR,
	EQ_MAX
};

#define NAME_SIZE	32
#define ITEM_DESC_LENGTH 512
#define INVENTORY_MAX 20
#define STORE_WEAPON_MAX 3
#define STORE_ARMOR_MAX 3
#define LEVEL_MAX 10




struct _tagItem
{
	char strName[NAME_SIZE];
	char strTypeName[NAME_SIZE];
	ITEM_TYPE etype;
	int iMin, iMax, iPrice, iSell;
	char strDesc[ITEM_DESC_LENGTH];
};


struct _tagInventory
{
	_tagItem tItem[INVENTORY_MAX];
	int iITemCount;
	int iGold;
};

struct _tagPlayer
{
	char			strName[NAME_SIZE];
	char			strJobName[NAME_SIZE];
	JOB			eJob;
	int				iAttackMin, iAttackMax, iArmorMin, iArmorMax, iHp, iHpMax, iMp, iMpMax;
	int				iExp, iLevel;
	_tagItem  tEquip[EQ_MAX];
	bool			bEquip[EQ_MAX];
	_tagInventory tInventory;
};

struct _tagMonster
{
	char			strName[NAME_SIZE];
	int				iAttackMin, iAttackMax, iArmorMin, iArmorMax, iHp, iHpMax, iMp, iMpMax;
	int				iExp, iLevel, iGoldMin, iGoldMax;
};

struct _tagLevelUpStatus
{
	int				iAttackMin, iAttackMax, iArmorMin, iArmorMax, iHp, iHpMax, iMp, iMpMax;
};

int main()
{
	srand((unsigned int)time(0));

	//레벨업에 필요한 경험치 목록을 만든다.
	const int iLevelUpExp[LEVEL_MAX] = {4000, 10000, 20000, 35000, 50000, 70000, 100000, 150000, 200000, 400000 };
	_tagLevelUpStatus tLvUpTable[JOB_END - 1];
	tLvUpTable[JOB_KNIGHT - 1].iAttackMin = 4;
	tLvUpTable[JOB_KNIGHT - 1].iAttackMax = 10;
	tLvUpTable[JOB_KNIGHT - 1].iArmorMin = 11;
	tLvUpTable[JOB_KNIGHT - 1].iArmorMax = 15;
	tLvUpTable[JOB_KNIGHT - 1].iHp = 60;
	tLvUpTable[JOB_KNIGHT - 1].iHpMax= 60;
	tLvUpTable[JOB_KNIGHT - 1].iMp = 20;
	tLvUpTable[JOB_KNIGHT - 1].iMpMax = 20;

	tLvUpTable[JOB_ARCHER - 1].iAttackMin = 10;
	tLvUpTable[JOB_ARCHER - 1].iAttackMax = 15;
	tLvUpTable[JOB_ARCHER - 1].iArmorMin = 5;
	tLvUpTable[JOB_ARCHER - 1].iArmorMax = 10;
	tLvUpTable[JOB_ARCHER - 1].iHp = 40;
	tLvUpTable[JOB_ARCHER - 1].iHpMax = 40;
	tLvUpTable[JOB_ARCHER - 1].iMp = 30;
	tLvUpTable[JOB_ARCHER - 1].iMpMax = 30;

	tLvUpTable[JOB_WIZARD - 1].iAttackMin = 13;
	tLvUpTable[JOB_WIZARD - 1].iAttackMax = 20;
	tLvUpTable[JOB_WIZARD - 1].iArmorMin = 2;
	tLvUpTable[JOB_WIZARD - 1].iArmorMax = 5;
	tLvUpTable[JOB_WIZARD - 1].iHp = 30;
	tLvUpTable[JOB_WIZARD - 1].iHpMax = 30;
	tLvUpTable[JOB_WIZARD - 1].iMp = 60;
	tLvUpTable[JOB_WIZARD - 1].iMpMax = 60;


	//게임시작할때의 플레이어 설정
	_tagPlayer tPlayer = {};

	cout << "이름 : ";
	cin.getline( tPlayer.strName, NAME_SIZE - 1);

	int iJob = JOB_NONE;
	while (iJob == JOB_NONE)
	{
		system("cls");
		cout << "1. 기사 " << endl;
		cout << "2. 궁수" << endl;
		cout << "3. 마법사" << endl;
		cout << "직업을 선택하세요 : ";
		cin >> iJob;

		if (cin.fail())
		{
			cin.clear();
			cin.ignore(1024, '\n');
			continue;
		}

		else if (iJob == JOB_NONE || iJob >= JOB_END)
			iJob = JOB_NONE;
	}


	tPlayer.iLevel = 1;
	tPlayer.iExp = 0;
	tPlayer.eJob = (JOB)iJob;
	tPlayer.tInventory.iGold = 10000;

	switch (tPlayer.eJob)
	{
	case JOB_KNIGHT:
		strcpy_s(tPlayer.strJobName, "기사");
		tPlayer.iAttackMin = 5;
		tPlayer.iAttackMax = 10;
		tPlayer.iArmorMin = 15;
		tPlayer.iArmorMax = 20;
		tPlayer.iHpMax = 500;
		tPlayer.iHp = 500;
		tPlayer.iMp = 100;
		tPlayer.iMpMax = 100;
		break;
	case JOB_ARCHER:
		strcpy_s(tPlayer.strJobName, "궁수");
		tPlayer.iAttackMin = 10;
		tPlayer.iAttackMax = 15;
		tPlayer.iArmorMin = 10;
		tPlayer.iArmorMax = 15;
		tPlayer.iHpMax = 400;
		tPlayer.iHp = 400;
		tPlayer.iMp = 200;
		tPlayer.iMpMax = 200;
		break;
	case JOB_WIZARD:
		strcpy_s(tPlayer.strJobName, "마법사");
		tPlayer.iAttackMin = 15;
		tPlayer.iAttackMax = 20;
		tPlayer.iArmorMin = 5;
		tPlayer.iArmorMax = 10;
		tPlayer.iHpMax = 300;
		tPlayer.iHp = 300;
		tPlayer.iMp = 300;
		tPlayer.iMpMax = 300;
	default:
		break;
	}

	// 몬스터 생성한다.
	_tagMonster tMonsterArr[MT_BACK - 1] = {};

	// 고블린 생성
	strcpy_s(tMonsterArr[0].strName, "고블린");
	tMonsterArr[0].iAttackMin = 20;
	tMonsterArr[0].iAttackMax = 30;
	tMonsterArr[0].iArmorMin = 2;
	tMonsterArr[0].iArmorMax = 5;
	tMonsterArr[0].iHp = 100;
	tMonsterArr[0].iHpMax = 100;
	tMonsterArr[0].iMp = 10;
	tMonsterArr[0].iMpMax = 10;
	tMonsterArr[0].iLevel = 1;
	tMonsterArr[0].iExp = 1000;
	tMonsterArr[0].iGoldMin = 500;
	tMonsterArr[0].iGoldMax = 1500;

	//트롤 생성 
	strcpy_s(tMonsterArr[1].strName, "트롤");
	tMonsterArr[1].iAttackMin = 80;
	tMonsterArr[1].iAttackMax = 130;
	tMonsterArr[1].iArmorMin = 60;
	tMonsterArr[1].iArmorMax = 90;
	tMonsterArr[1].iHp = 2000;
	tMonsterArr[1].iHpMax = 2000;
	tMonsterArr[1].iMp = 100;
	tMonsterArr[1].iMpMax = 100;
	tMonsterArr[1].iLevel = 5;
	tMonsterArr[1].iExp = 7000;
	tMonsterArr[1].iGoldMin = 6000;
	tMonsterArr[1].iGoldMax = 8000;

	//드래곤 생성
	strcpy_s(tMonsterArr[2].strName, "드래곤");
	tMonsterArr[2].iAttackMin = 250;
	tMonsterArr[2].iAttackMax = 500;
	tMonsterArr[2].iArmorMin = 200;
	tMonsterArr[2].iArmorMax = 400;
	tMonsterArr[2].iHp = 30000;
	tMonsterArr[2].iHpMax = 30000;
	tMonsterArr[2].iMp = 20000;
	tMonsterArr[2].iMpMax = 20000;
	tMonsterArr[2].iLevel = 10;
	tMonsterArr[2].iExp = 30000;
	tMonsterArr[2].iGoldMin = 20000;
	tMonsterArr[2].iGoldMax = 50000;

	//상점에서 판매할 아이템 목록을 생성한다.
	_tagItem tStoreWeapon[STORE_WEAPON_MAX] = {};
	_tagItem tStoreArmor[STORE_ARMOR_MAX] = {};

	strcpy_s(tStoreWeapon[0].strName, "명인의 검");
	strcpy_s(tStoreWeapon[0].strTypeName, "무기");
	strcpy_s(tStoreWeapon[0].strDesc, "명인이 만든 검입니다.");
	tStoreWeapon[0].iMin = 50;
	tStoreWeapon[0].iMax = 70;
	tStoreWeapon[0].iPrice = 10000;
	tStoreWeapon[0].iSell = 5000;
	tStoreWeapon[0].etype = IT_WEAPON;
	

	strcpy_s(tStoreWeapon[1].strName, "목검");
	strcpy_s(tStoreWeapon[1].strTypeName, "무기");
	strcpy_s(tStoreWeapon[1].strDesc, "나무를 깎아만든 검입니다.");
	tStoreWeapon[1].iMin = 10;
	tStoreWeapon[1].iMax = 20;
	tStoreWeapon[1].iPrice = 1000;
	tStoreWeapon[1].iSell = 500;
	tStoreWeapon[1].etype = IT_WEAPON;

	strcpy_s(tStoreWeapon[2].strName, "무한의 대검");
	strcpy_s(tStoreWeapon[2].strTypeName, "무기");
	strcpy_s(tStoreWeapon[2].strDesc, "무한의 힘을 지닌 대검입니다.");
	tStoreWeapon[2].iMin = 100;
	tStoreWeapon[2].iMax = 200;
	tStoreWeapon[2].iPrice = 18000;
	tStoreWeapon[2].iSell = 9000;
	tStoreWeapon[2].etype = IT_WEAPON;

	strcpy_s(tStoreArmor[0].strName, "천갑옷");
	strcpy_s(tStoreArmor[0].strTypeName, "방어구");
	strcpy_s(tStoreArmor[0].strDesc, "천을 엮어만든 튼튼한 갑옷입니다.");
	tStoreArmor[0].iMin = 5;
	tStoreArmor[0].iMax = 10;
	tStoreArmor[0].iPrice = 1200;
	tStoreArmor[0].iSell = 600;
	tStoreArmor[0].etype = IT_ARMOR;

	strcpy_s(tStoreArmor[1].strName, "워모그의 갑옷");
	strcpy_s(tStoreArmor[1].strTypeName, "방어구");
	strcpy_s(tStoreArmor[1].strDesc, "체력회복량이 높은 갑옷입니다.");
	tStoreArmor[1].iMin = 70;
	tStoreArmor[1].iMax = 100;
	tStoreArmor[1].iPrice = 11000;
	tStoreArmor[1].iSell = 5500;
	tStoreArmor[1].etype = IT_ARMOR;

	strcpy_s(tStoreArmor[2].strName, "가시갑옷");
	strcpy_s(tStoreArmor[2].strTypeName, "방어구");
	strcpy_s(tStoreArmor[2].strDesc, "맞기만해도 따가운 가시로 둘러진 갑옷입니다.");
	tStoreArmor[2].iMin = 50;
	tStoreArmor[2].iMax = 200;
	tStoreArmor[2].iPrice = 15000;
	tStoreArmor[2].iSell = 7500;
	tStoreArmor[2].etype = IT_ARMOR;

	while (true)
	{
		system("cls");
		cout << "************************** 로비 **************************" << endl;
		cout << "1. 맵" << endl;
		cout << "2. 상점" << endl;
		cout << "3. 가방" << endl;
		cout << "4. 종료" << endl;
		cout << "메뉴를 선택하세요 : ";
		int iMenu;
		cin >> iMenu;

		if (cin.fail())
		{
			cin.clear();
			cin.ignore(1024, '\n');
			continue;
		}

		if (iMenu == MM_EXIT)
			break;

		switch (iMenu)
		{
		case MM_MAP:
			while (true)
			{
				system("cls");
				cout << "************************** 맵 **************************" << endl;
				cout << "1. 쉬움" << endl;
				cout << "2. 보통" << endl;
				cout << "3. 어려움" << endl;
				cout << "4. 뒤로가기" << endl;
				cout << "맵을 선택하세요 : ";
				cin >> iMenu;
				if (cin.fail())
				{
					cin.clear();
					cin.ignore(1024, '\n');
					continue;
				}
				if (iMenu == MT_BACK)
					break;
				
				//선택한 메뉴에서 1을빼주면 몬스터 배열의 인덱스가된다.
				//그렇게 해서 해당맵의 몬스터를 생성해준다.
				_tagMonster tMonster = tMonsterArr[iMenu - 1];

				while (true)
				{
					system("cls");
					switch (iMenu)
					{
					case MT_EASY:
						cout << "************************** 쉬움 **************************" << endl;
						break;
					case MT_NORMAL:
						cout << "************************** 보통 **************************" << endl;
						break;
					case MT_HARD:
							cout << "************************** 어려움 **************************" << endl;
							break;

					}

					//플레이어 정보 출력
					cout << "************************** Player **************************" << endl;
					cout << "이름 : " << tPlayer.strName << "\t직업 : " <<
						tPlayer.strJobName << endl;
					cout << "레벨 : " << tPlayer.iLevel << "\t경험치 : " <<
						tPlayer.iExp <<  " / " << iLevelUpExp[tPlayer.iLevel-1] <<   endl;
					// 무기 장착하고 있을경우 능력치추가
					if (tPlayer.bEquip[EQ_WEAPON] == true)
					{
						cout << "공격력 : " << tPlayer.iAttackMin << " + " << tPlayer.tEquip[EQ_WEAPON].iMin << " ~ " <<
							tPlayer.iAttackMax << " + " << tPlayer.tEquip[EQ_WEAPON].iMax << endl;
					}

					else
					{
						cout << "공격력 : " << tPlayer.iAttackMin << " ~ " <<
							tPlayer.iAttackMax << endl;
					}

					//방어구 장착하고 있을경우 능력치 추가
					if (tPlayer.bEquip[EQ_ARMOR] == true)
					{
						cout << "\t방어력 : " << tPlayer.iArmorMin << " + " << tPlayer.tEquip[EQ_ARMOR].iMin << " ~ " <<
							tPlayer.iArmorMax << " + " << tPlayer.tEquip[EQ_ARMOR].iMax << endl;
					}

					else
					{
						cout << "\t방어력 : " << tPlayer.iArmorMin << " ~ " <<
							tPlayer.iArmorMax << endl;
					}

					cout << "체력 : " << tPlayer.iHp << " / " << tPlayer.iHpMax <<
						"\t마나 :  " << tPlayer.iMp << " / " << tPlayer.iMpMax << endl;
					cout << "보유골드 : " << tPlayer.tInventory.iGold << " Gold" << endl;

					//몬스터 정보 출력
					cout << "************************** Monster **************************" << endl;
					cout << "이름 : " << tMonster.strName << "\t레벨 : " <<
						tPlayer.iLevel << endl;
					cout << "공격력 : " << tMonster.iArmorMin << " ~ " <<
						tMonster.iAttackMax << "\t방어력 : " << tMonster.iArmorMin <<
						" ~ " << tMonster.iArmorMax << endl;
					cout << "체력 : " << tMonster.iHp << " / " << tMonster.iHpMax <<
						"\t마나 :  " << tMonster.iMp << " / " << tMonster.iMpMax << endl;
					cout << "획득경험치 :  " << tMonster.iExp << "\t획득골드 : " <<
						tMonster.iGoldMin << " ~ " << tMonster.iGoldMax << endl << endl;

					cout << "1. 공격" << endl;
					cout << "2. 도망가기" << endl;
					cout << "메뉴를 선택하세요 : ";
					cin >> iMenu;
					if (cin.fail())
					{
						cin.clear();
						cin.ignore(1024, '\n');
						continue;
					}

					else if (iMenu == BATTLE_BACK)
						break;
					switch (iMenu)
					{
					case BATTLE_ATTACK:
					{
						//예를들어 Min 5 Max 15라고 가정할 경우
						// 15 - 5 + 1 을 하면 11이된다. 11로 나눈 나머지는 0~10이
						//나오게되고 여기에 Min값인 5를 더하게되면
						//5~15사이로 값이 나오게 된다.

						int iAttackMin = tPlayer.iAttackMin;
						int iAttackMax = tPlayer.iArmorMax;

						//무기를 장착하고 있으면 무기와 Min,Max를 더해준다.
						if (tPlayer.bEquip[EQ_WEAPON])
						{
							iAttackMin += tPlayer.tEquip[EQ_WEAPON].iMin;
							iAttackMax += tPlayer.tEquip[EQ_WEAPON].iMax;
						}

						int iAttack = rand() % (iAttackMax -iAttackMin + 1) +
							iAttackMin;
						int iArmor = rand() % (tMonster.iArmorMax - tMonster.iArmorMin + 1) +
							tMonster.iArmorMin;

						int iDamage = iAttack - iArmor;
						iDamage = iDamage < 1 ? 1 : iDamage;

						tMonster.iHp -= iDamage;
						cout << tPlayer.strName << " 가 " << tMonster.strName <<
							"에게 " << iDamage << " 피해를 입혔습니다." << endl;

						if (tMonster.iHp <= 0)
						{
							cout << tMonster.strName << "몬스터가 사망하였습니다." << endl;
							tPlayer.iExp += tMonster.iExp;
							int iGold = tPlayer.tInventory.iGold += (rand() % (tMonster.iGoldMax - tMonster.iGoldMin + 1) +
								tMonster.iGoldMin);
							tPlayer.tInventory.iGold += iGold;

							cout << tMonster.iExp << "경험치를 획득하였습니다. " << endl;
							cout << iGold << "Gold를 획득하였습니다. " << endl;


							tMonster.iHp = tMonster.iHpMax;
							tMonster.iMp = tMonster.iMpMax;

							//레벨업 했는지 체크한다.
							if (tPlayer.iExp >= iLevelUpExp[tPlayer.iLevel - 1])
							{
								tPlayer.iExp -= iLevelUpExp[tPlayer.iLevel - 1];
								++tPlayer.iLevel;

								cout << "레벨업 하였습니다." << endl;

								//능력치 상승시킨다
								int iJobIndex = tPlayer.eJob - 1;
								int iAttackUp = rand() % (tLvUpTable[iJobIndex].iAttackMax - tLvUpTable[iJobIndex].iAttackMin + 1) +
									tLvUpTable[iJobIndex].iAttackMin;
								int iArmorUp = rand() % (tLvUpTable[iJobIndex].iArmorMax - tLvUpTable[iJobIndex].iArmorMin + 1) +
									tLvUpTable[iJobIndex].iArmorMin;
								int iHpUp = tLvUpTable[iJobIndex].iHpMax;
								int iMpUp = tLvUpTable[iJobIndex].iMpMax;

								tPlayer.iAttackMin += tLvUpTable[iJobIndex].iAttackMin;
								tPlayer.iAttackMax += tLvUpTable[iJobIndex].iAttackMax;
								tPlayer.iArmorMin += tLvUpTable[iJobIndex].iArmorMin;
								tPlayer.iArmorMax += tLvUpTable[iJobIndex].iArmorMax;
								tPlayer.iHpMax += iHpUp;
								tPlayer.iMpMax += iMpUp;

								//체력 마나 회복
								tPlayer.iHp = tPlayer.iHpMax;
								tPlayer.iMp = tPlayer.iMpMax;
							}

							system("pause");
							break;
						}

						//몬스터가 살아있다면 플레이어를 공격합니다.
						 iAttack = rand() % (tMonster.iAttackMax - tMonster.iAttackMin + 1) +
							tMonster.iAttackMin;

						 int iArmorMin = tPlayer.iArmorMin;
						 int iArmorMax = tPlayer.iArmorMax;

						 if (tPlayer.bEquip[EQ_ARMOR])
						 {
							 iArmorMin += tPlayer.tEquip[EQ_ARMOR].iMin;
							 iArmorMax += tPlayer.tEquip[EQ_ARMOR].iMax;
						 }

						 iArmor = rand() % (iArmorMax -iArmorMin + 1) +
							iArmorMin;

						 iDamage = iAttack - iArmor;
						iDamage = iDamage < 1 ? 1 : iDamage;

						tPlayer.iHp -= iDamage;
						cout << tMonster.strName << " 가 " << tPlayer.strName << "에게 " << iDamage << " 피해를 입혔습니다." << endl;

						//플레이어 사망시
						if (tPlayer.iHp <= 0)
						{
							cout << tPlayer.strName << " 플레이어가 사망하였습니다. " << endl;

							int iExp = tPlayer.iExp*0.1f;
							int iGold = tPlayer.tInventory.iGold *0.1f;

							tPlayer.iExp -= iExp;
							tPlayer.tInventory.iGold -= iGold;

							cout << iExp << " 경험치를 잃었습니다. " << endl;
							cout << iGold << " Gold를 잃었습니다. " << endl;

							tPlayer.iHp = tPlayer.iHpMax;
							tPlayer.iMp = tPlayer. iMpMax;

						}
						system("pause");
						
					}
						break;
					}
					
					
					
				}
				
			}
			
			break;
		case MM_STORE:
			while (true)
			{
				system("cls");
				cout << "************************** 상점 **************************" << endl;
				cout << "1. 무기상점 " << endl;
				cout << "2. 방어구상점" << endl;
				cout << "3. 뒤로가기" << endl;
				cout << "상점을 선택하세요 : ";
				cin >> iMenu;
				if (cin.fail())
				{
					cin.clear();
					cin.ignore(1024, '\n');
					continue;
				}
				else if (iMenu == SM_BACK)
					break;
				switch (iMenu)
				{
				case SM_WEAPON:
					while (true)
					{
						system("cls");
						cout << "************************** 무기상점 **************************" << endl;
						for (int i = 0; i < STORE_WEAPON_MAX; i++)
						{
							cout << i + 1 << ". 이름 : " << tStoreWeapon[i].strName <<
								"\t종류 : " << tStoreWeapon[i].strTypeName << endl;
							cout << "공격력 : " << tStoreWeapon[i].iMin << " ~ " <<
								tStoreWeapon[i].iMax << endl;
							cout << "판매가격 : " << tStoreWeapon[i].iPrice <<
								"\t구매가격 : " << tStoreWeapon[i] .iSell << endl;
							cout << "설명 : " << tStoreWeapon[i].strDesc << endl << endl;
						}

						cout << STORE_WEAPON_MAX + 1 << ". 뒤로가기" << endl;
						cout << "==================================" << endl;
						cout << "보유금액 : " << tPlayer.tInventory.iGold << " Gold " << endl;
						cout << "남은공간 : " << INVENTORY_MAX - tPlayer.tInventory.iITemCount << endl;
						cout << "==================================" << endl;
						cout << "구입할 아이템을 선택하세요 : ";
						cin >> iMenu;
						if (cin.fail())
						{
							cin.clear();
							cin.ignore(1024, '\n');
							continue;
						}

						else if (iMenu == STORE_WEAPON_MAX + 1)
							break;
						else if (iMenu <1 || iMenu > STORE_WEAPON_MAX + 1)
						{
							cout << "잘못 선택하였습니다. " << endl;
							system("pause");
							continue;
						}

						//상점판매목록 배열의 인덱스를 구해준다.
						int iWeaponIndex = iMenu - 1;


						//인벤토리가 꽉 찼는지 검사한다.
						if (tPlayer.tInventory.iITemCount == INVENTORY_MAX)
						{
							cout << "가방이 꽉 찼습니다." << endl;
							system("pause");
							continue;
						}

						//돈이 부족할경우
						else if (tPlayer.tInventory.iGold < tStoreWeapon[iWeaponIndex].iPrice)
						{
							cout << "보유금액이 부족합니다." << endl;
							system("pause");
							continue;
						}

						tPlayer.tInventory.tItem[tPlayer.tInventory.iITemCount] =
							tStoreWeapon[iWeaponIndex];
						++tPlayer.tInventory.iITemCount;

						//골드를 차감한다.
						tPlayer.tInventory.iGold -= tStoreWeapon[iWeaponIndex].iPrice;
						cout << tStoreWeapon[iWeaponIndex].strName << "아이템을 구매하였습니다. " << endl;
						system("pause");
					}
					break;
				case SM_ARMOR:
					while (true)
					{
						system("cls");
						cout << "************************** 방어구상점 **************************" << endl;
						for (int i = 0; i < STORE_ARMOR_MAX; i++)
						{
							cout << i + 1 << ". 이름 : " << tStoreArmor[i].strName <<
								"\t종류 : " << tStoreArmor[i].strTypeName << endl;
							cout << "방어력 : " << tStoreArmor[i].iMin << " ~ " <<
								tStoreArmor[i].iMax << endl;
							cout << "판매가격 : " << tStoreArmor[i].iPrice <<
								"\t구매가격 : " << tStoreArmor[i].iSell << endl;
							cout << "설명 : " << tStoreArmor[i].strDesc << endl << endl;
						}

						cout << STORE_ARMOR_MAX + 1 << ". 뒤로가기" << endl;
						cout << "==================================" << endl;
						cout << "보유금액 : " << tPlayer.tInventory.iGold << " Gold " << endl;
						cout << "남은공간 : " << INVENTORY_MAX - tPlayer.tInventory.iITemCount << endl;
						cout << "==================================" << endl;
						cout << "구입할 아이템을 선택하세요 : ";
						cin >> iMenu;
						if (cin.fail())
						{
							cin.clear();
							cin.ignore(1024, '\n');
							continue;
						}

						else if (iMenu == STORE_ARMOR_MAX + 1)
							break;
						else if (iMenu <1 || iMenu > STORE_ARMOR_MAX + 1)
						{
							cout << "잘못 선택하였습니다. " << endl;
							system("pause");
							continue;
						}

						//상점판매목록 배열의 인덱스를 구해준다.
						int iArmorIndex = iMenu - 1;


						//인벤토리가 꽉 찼는지 검사한다.
						if (tPlayer.tInventory.iITemCount == INVENTORY_MAX)
						{
							cout << "가방이 꽉 찼습니다." << endl;
							system("pause");
							continue;
						}

						//돈이 부족할경우
						else if (tPlayer.tInventory.iGold < tStoreArmor[iArmorIndex].iPrice)
						{
							cout << "보유금액이 부족합니다." << endl;
							system("pause");
							continue;
						}

						tPlayer.tInventory.tItem[tPlayer.tInventory.iITemCount] =
							tStoreArmor[iArmorIndex];
						++tPlayer.tInventory.iITemCount;

						//골드를 차감한다.
						tPlayer.tInventory.iGold -= tStoreArmor[iArmorIndex].iPrice;
						cout << tStoreArmor[iArmorIndex].strName << "아이템을 구매하였습니다. " << endl;
						system("pause");
					}
					break;
				}
			}
			break;
		case MM_INVENTORY:
			while (true)
			{
				system("cls");
				cout << "************************** 내 가방 **************************" << endl;
				cout << "************************** Player **************************" << endl;
				cout << "이름 : " << tPlayer.strName << "\t직업 : " <<
					tPlayer.strJobName << endl;
				cout << "레벨 : " << tPlayer.iLevel << "\t경험치 : " <<
					tPlayer.iExp << " / " << iLevelUpExp[tPlayer.iLevel - 1] << endl;


				// 무기 장착하고 있을경우 능력치추가
				if (tPlayer.bEquip[EQ_WEAPON] == true)
				{
					cout << "공격력 : " << tPlayer.iAttackMin << " + " << tPlayer.tEquip[EQ_WEAPON].iMin << " ~ " <<
						tPlayer.iAttackMax << " + " << tPlayer.tEquip[EQ_WEAPON].iMax << endl;
				}

				else
				{
					cout << "공격력 : " << tPlayer.iAttackMin << " ~ " <<
						tPlayer.iAttackMax << endl;
				}

				//방어구 장착하고 있을경우 능력치 추가
				if (tPlayer.bEquip[EQ_ARMOR] == true)
				{
					cout << "방어력 : " << tPlayer.iArmorMin << " + " << tPlayer.tEquip[EQ_ARMOR].iMin << " ~ " <<
						tPlayer.iArmorMax << " + " << tPlayer.tEquip[EQ_ARMOR].iMax << endl;
				}

				else
				{
					cout << "방어력 : " << tPlayer.iArmorMin << " ~ " <<
						tPlayer.iArmorMax << endl;
				}

			
				cout << "체력 : " << tPlayer.iHp << " / " << tPlayer.iHpMax <<
					"\t마나 :  " << tPlayer.iMp << " / " << tPlayer.iMpMax << endl;
				cout << "보유골드 : " << tPlayer.tInventory.iGold << " Gold" << endl;

				if (tPlayer.bEquip[EQ_WEAPON])
					cout << "장착무기 : " << tPlayer.tEquip[EQ_WEAPON].strName ;
				else
					cout << "장착무기 : 없음 " ;

				if (tPlayer.bEquip[EQ_ARMOR])
					cout << "\t장착방어구 : " << tPlayer.tEquip[EQ_ARMOR].strName << endl;
				else
					cout << "\t장착방어구 : 없음 " << endl;

				for (int i = 0; i < tPlayer.tInventory.iITemCount; ++i)
				{
					cout << "==================================" << endl;
					cout << i + 1 << ". 이름 : " << tPlayer.tInventory.tItem[i].strName <<
						"\t종류 : " << tPlayer.tInventory.tItem[i].strTypeName << endl;
					cout << "공격력 : " << tPlayer.tInventory.tItem[i].iMin << " ~ " <<
						tPlayer.tInventory.tItem[i].iMax << endl;
					cout << "판매가격 : " << tPlayer.tInventory.tItem[i].iPrice <<
						"\t구매가격 : " << tPlayer.tInventory.tItem[i].iSell << endl;
					cout << "설명 : " << tPlayer.tInventory.tItem[i].strDesc << endl << endl;
					cout << "==================================" << endl;
				}

				cout << tPlayer.tInventory.iITemCount + 1 << ". 뒤로가기" << endl;
				cout << "장착할 아이템을 선택하세요 : ";
				cin >> iMenu;
				if (cin.fail())
				{
					cin.clear();
					cin.ignore(1024, '\n');
					continue;
				}

				else if (iMenu == tPlayer.tInventory.iITemCount + 1)
					break;

				else if (iMenu < 1 || iMenu > tPlayer.tInventory.iITemCount + 1)
				{
					cout << "잘못 선택하였습니다. " << endl;
					system("pause");
					continue;
				}

				//아이템 인덱스 설정.
				int idx = iMenu - 1;

				//제대로 선택했을 경우 아이템의 종류에 따라 장착 부위를 결정.
				EQUIP eq;
				switch (tPlayer.tInventory.tItem[idx].etype)
				{
				case IT_WEAPON:
					eq = EQ_WEAPON;
					break;
				case IT_ARMOR:
					eq = EQ_ARMOR;
					break;
				}

				//아이템이 장착되어 있을 경우 장착되어 있는 아이템과 교체.
				if (tPlayer.bEquip[eq] == true)
				{
					_tagItem tSwap = tPlayer.tEquip[eq];
					tPlayer.tEquip[eq] = tPlayer.tInventory.tItem[eq];
					tPlayer.tInventory.tItem[idx] = tSwap;
				}

				//장착되어있지 않을경우 
				else
				{
					tPlayer.tEquip[eq] = tPlayer.tInventory.tItem[idx];
					for (int i = idx; i < tPlayer.tInventory.iITemCount - 1; i++)
					{
						tPlayer.tInventory.tItem[i] = tPlayer.tInventory.tItem[i + 1];
					}

					--tPlayer.tInventory.iITemCount;

					tPlayer.bEquip[eq] = true;
				}

				cout << tPlayer.tEquip[eq].strName << "아이템을 장착하였습니다." << endl;
			}
			break;
		default:
			cout << " 잘못 입력하셨습니다. " << endl;
			break;
		}
	}

}