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

	//�������� �ʿ��� ����ġ ����� �����.
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


	//���ӽ����Ҷ��� �÷��̾� ����
	_tagPlayer tPlayer = {};

	cout << "�̸� : ";
	cin.getline( tPlayer.strName, NAME_SIZE - 1);

	int iJob = JOB_NONE;
	while (iJob == JOB_NONE)
	{
		system("cls");
		cout << "1. ��� " << endl;
		cout << "2. �ü�" << endl;
		cout << "3. ������" << endl;
		cout << "������ �����ϼ��� : ";
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
		strcpy_s(tPlayer.strJobName, "���");
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
		strcpy_s(tPlayer.strJobName, "�ü�");
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
		strcpy_s(tPlayer.strJobName, "������");
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

	// ���� �����Ѵ�.
	_tagMonster tMonsterArr[MT_BACK - 1] = {};

	// ��� ����
	strcpy_s(tMonsterArr[0].strName, "���");
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

	//Ʈ�� ���� 
	strcpy_s(tMonsterArr[1].strName, "Ʈ��");
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

	//�巡�� ����
	strcpy_s(tMonsterArr[2].strName, "�巡��");
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

	//�������� �Ǹ��� ������ ����� �����Ѵ�.
	_tagItem tStoreWeapon[STORE_WEAPON_MAX] = {};
	_tagItem tStoreArmor[STORE_ARMOR_MAX] = {};

	strcpy_s(tStoreWeapon[0].strName, "������ ��");
	strcpy_s(tStoreWeapon[0].strTypeName, "����");
	strcpy_s(tStoreWeapon[0].strDesc, "������ ���� ���Դϴ�.");
	tStoreWeapon[0].iMin = 50;
	tStoreWeapon[0].iMax = 70;
	tStoreWeapon[0].iPrice = 10000;
	tStoreWeapon[0].iSell = 5000;
	tStoreWeapon[0].etype = IT_WEAPON;
	

	strcpy_s(tStoreWeapon[1].strName, "���");
	strcpy_s(tStoreWeapon[1].strTypeName, "����");
	strcpy_s(tStoreWeapon[1].strDesc, "������ ��Ƹ��� ���Դϴ�.");
	tStoreWeapon[1].iMin = 10;
	tStoreWeapon[1].iMax = 20;
	tStoreWeapon[1].iPrice = 1000;
	tStoreWeapon[1].iSell = 500;
	tStoreWeapon[1].etype = IT_WEAPON;

	strcpy_s(tStoreWeapon[2].strName, "������ ���");
	strcpy_s(tStoreWeapon[2].strTypeName, "����");
	strcpy_s(tStoreWeapon[2].strDesc, "������ ���� ���� ����Դϴ�.");
	tStoreWeapon[2].iMin = 100;
	tStoreWeapon[2].iMax = 200;
	tStoreWeapon[2].iPrice = 18000;
	tStoreWeapon[2].iSell = 9000;
	tStoreWeapon[2].etype = IT_WEAPON;

	strcpy_s(tStoreArmor[0].strName, "õ����");
	strcpy_s(tStoreArmor[0].strTypeName, "��");
	strcpy_s(tStoreArmor[0].strDesc, "õ�� ����� ưư�� �����Դϴ�.");
	tStoreArmor[0].iMin = 5;
	tStoreArmor[0].iMax = 10;
	tStoreArmor[0].iPrice = 1200;
	tStoreArmor[0].iSell = 600;
	tStoreArmor[0].etype = IT_ARMOR;

	strcpy_s(tStoreArmor[1].strName, "������� ����");
	strcpy_s(tStoreArmor[1].strTypeName, "��");
	strcpy_s(tStoreArmor[1].strDesc, "ü��ȸ������ ���� �����Դϴ�.");
	tStoreArmor[1].iMin = 70;
	tStoreArmor[1].iMax = 100;
	tStoreArmor[1].iPrice = 11000;
	tStoreArmor[1].iSell = 5500;
	tStoreArmor[1].etype = IT_ARMOR;

	strcpy_s(tStoreArmor[2].strName, "���ð���");
	strcpy_s(tStoreArmor[2].strTypeName, "��");
	strcpy_s(tStoreArmor[2].strDesc, "�±⸸�ص� ������ ���÷� �ѷ��� �����Դϴ�.");
	tStoreArmor[2].iMin = 50;
	tStoreArmor[2].iMax = 200;
	tStoreArmor[2].iPrice = 15000;
	tStoreArmor[2].iSell = 7500;
	tStoreArmor[2].etype = IT_ARMOR;

	while (true)
	{
		system("cls");
		cout << "************************** �κ� **************************" << endl;
		cout << "1. ��" << endl;
		cout << "2. ����" << endl;
		cout << "3. ����" << endl;
		cout << "4. ����" << endl;
		cout << "�޴��� �����ϼ��� : ";
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
				cout << "************************** �� **************************" << endl;
				cout << "1. ����" << endl;
				cout << "2. ����" << endl;
				cout << "3. �����" << endl;
				cout << "4. �ڷΰ���" << endl;
				cout << "���� �����ϼ��� : ";
				cin >> iMenu;
				if (cin.fail())
				{
					cin.clear();
					cin.ignore(1024, '\n');
					continue;
				}
				if (iMenu == MT_BACK)
					break;
				
				//������ �޴����� 1�����ָ� ���� �迭�� �ε������ȴ�.
				//�׷��� �ؼ� �ش���� ���͸� �������ش�.
				_tagMonster tMonster = tMonsterArr[iMenu - 1];

				while (true)
				{
					system("cls");
					switch (iMenu)
					{
					case MT_EASY:
						cout << "************************** ���� **************************" << endl;
						break;
					case MT_NORMAL:
						cout << "************************** ���� **************************" << endl;
						break;
					case MT_HARD:
							cout << "************************** ����� **************************" << endl;
							break;

					}

					//�÷��̾� ���� ���
					cout << "************************** Player **************************" << endl;
					cout << "�̸� : " << tPlayer.strName << "\t���� : " <<
						tPlayer.strJobName << endl;
					cout << "���� : " << tPlayer.iLevel << "\t����ġ : " <<
						tPlayer.iExp <<  " / " << iLevelUpExp[tPlayer.iLevel-1] <<   endl;
					// ���� �����ϰ� ������� �ɷ�ġ�߰�
					if (tPlayer.bEquip[EQ_WEAPON] == true)
					{
						cout << "���ݷ� : " << tPlayer.iAttackMin << " + " << tPlayer.tEquip[EQ_WEAPON].iMin << " ~ " <<
							tPlayer.iAttackMax << " + " << tPlayer.tEquip[EQ_WEAPON].iMax << endl;
					}

					else
					{
						cout << "���ݷ� : " << tPlayer.iAttackMin << " ~ " <<
							tPlayer.iAttackMax << endl;
					}

					//�� �����ϰ� ������� �ɷ�ġ �߰�
					if (tPlayer.bEquip[EQ_ARMOR] == true)
					{
						cout << "\t���� : " << tPlayer.iArmorMin << " + " << tPlayer.tEquip[EQ_ARMOR].iMin << " ~ " <<
							tPlayer.iArmorMax << " + " << tPlayer.tEquip[EQ_ARMOR].iMax << endl;
					}

					else
					{
						cout << "\t���� : " << tPlayer.iArmorMin << " ~ " <<
							tPlayer.iArmorMax << endl;
					}

					cout << "ü�� : " << tPlayer.iHp << " / " << tPlayer.iHpMax <<
						"\t���� :  " << tPlayer.iMp << " / " << tPlayer.iMpMax << endl;
					cout << "������� : " << tPlayer.tInventory.iGold << " Gold" << endl;

					//���� ���� ���
					cout << "************************** Monster **************************" << endl;
					cout << "�̸� : " << tMonster.strName << "\t���� : " <<
						tPlayer.iLevel << endl;
					cout << "���ݷ� : " << tMonster.iArmorMin << " ~ " <<
						tMonster.iAttackMax << "\t���� : " << tMonster.iArmorMin <<
						" ~ " << tMonster.iArmorMax << endl;
					cout << "ü�� : " << tMonster.iHp << " / " << tMonster.iHpMax <<
						"\t���� :  " << tMonster.iMp << " / " << tMonster.iMpMax << endl;
					cout << "ȹ�����ġ :  " << tMonster.iExp << "\tȹ���� : " <<
						tMonster.iGoldMin << " ~ " << tMonster.iGoldMax << endl << endl;

					cout << "1. ����" << endl;
					cout << "2. ��������" << endl;
					cout << "�޴��� �����ϼ��� : ";
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
						//������� Min 5 Max 15��� ������ ���
						// 15 - 5 + 1 �� �ϸ� 11�̵ȴ�. 11�� ���� �������� 0~10��
						//�����Եǰ� ���⿡ Min���� 5�� ���ϰԵǸ�
						//5~15���̷� ���� ������ �ȴ�.

						int iAttackMin = tPlayer.iAttackMin;
						int iAttackMax = tPlayer.iArmorMax;

						//���⸦ �����ϰ� ������ ����� Min,Max�� �����ش�.
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
						cout << tPlayer.strName << " �� " << tMonster.strName <<
							"���� " << iDamage << " ���ظ� �������ϴ�." << endl;

						if (tMonster.iHp <= 0)
						{
							cout << tMonster.strName << "���Ͱ� ����Ͽ����ϴ�." << endl;
							tPlayer.iExp += tMonster.iExp;
							int iGold = tPlayer.tInventory.iGold += (rand() % (tMonster.iGoldMax - tMonster.iGoldMin + 1) +
								tMonster.iGoldMin);
							tPlayer.tInventory.iGold += iGold;

							cout << tMonster.iExp << "����ġ�� ȹ���Ͽ����ϴ�. " << endl;
							cout << iGold << "Gold�� ȹ���Ͽ����ϴ�. " << endl;


							tMonster.iHp = tMonster.iHpMax;
							tMonster.iMp = tMonster.iMpMax;

							//������ �ߴ��� üũ�Ѵ�.
							if (tPlayer.iExp >= iLevelUpExp[tPlayer.iLevel - 1])
							{
								tPlayer.iExp -= iLevelUpExp[tPlayer.iLevel - 1];
								++tPlayer.iLevel;

								cout << "������ �Ͽ����ϴ�." << endl;

								//�ɷ�ġ ��½�Ų��
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

								//ü�� ���� ȸ��
								tPlayer.iHp = tPlayer.iHpMax;
								tPlayer.iMp = tPlayer.iMpMax;
							}

							system("pause");
							break;
						}

						//���Ͱ� ����ִٸ� �÷��̾ �����մϴ�.
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
						cout << tMonster.strName << " �� " << tPlayer.strName << "���� " << iDamage << " ���ظ� �������ϴ�." << endl;

						//�÷��̾� �����
						if (tPlayer.iHp <= 0)
						{
							cout << tPlayer.strName << " �÷��̾ ����Ͽ����ϴ�. " << endl;

							int iExp = tPlayer.iExp*0.1f;
							int iGold = tPlayer.tInventory.iGold *0.1f;

							tPlayer.iExp -= iExp;
							tPlayer.tInventory.iGold -= iGold;

							cout << iExp << " ����ġ�� �Ҿ����ϴ�. " << endl;
							cout << iGold << " Gold�� �Ҿ����ϴ�. " << endl;

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
				cout << "************************** ���� **************************" << endl;
				cout << "1. ������� " << endl;
				cout << "2. ������" << endl;
				cout << "3. �ڷΰ���" << endl;
				cout << "������ �����ϼ��� : ";
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
						cout << "************************** ������� **************************" << endl;
						for (int i = 0; i < STORE_WEAPON_MAX; i++)
						{
							cout << i + 1 << ". �̸� : " << tStoreWeapon[i].strName <<
								"\t���� : " << tStoreWeapon[i].strTypeName << endl;
							cout << "���ݷ� : " << tStoreWeapon[i].iMin << " ~ " <<
								tStoreWeapon[i].iMax << endl;
							cout << "�ǸŰ��� : " << tStoreWeapon[i].iPrice <<
								"\t���Ű��� : " << tStoreWeapon[i] .iSell << endl;
							cout << "���� : " << tStoreWeapon[i].strDesc << endl << endl;
						}

						cout << STORE_WEAPON_MAX + 1 << ". �ڷΰ���" << endl;
						cout << "==================================" << endl;
						cout << "�����ݾ� : " << tPlayer.tInventory.iGold << " Gold " << endl;
						cout << "�������� : " << INVENTORY_MAX - tPlayer.tInventory.iITemCount << endl;
						cout << "==================================" << endl;
						cout << "������ �������� �����ϼ��� : ";
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
							cout << "�߸� �����Ͽ����ϴ�. " << endl;
							system("pause");
							continue;
						}

						//�����ǸŸ�� �迭�� �ε����� �����ش�.
						int iWeaponIndex = iMenu - 1;


						//�κ��丮�� �� á���� �˻��Ѵ�.
						if (tPlayer.tInventory.iITemCount == INVENTORY_MAX)
						{
							cout << "������ �� á���ϴ�." << endl;
							system("pause");
							continue;
						}

						//���� �����Ұ��
						else if (tPlayer.tInventory.iGold < tStoreWeapon[iWeaponIndex].iPrice)
						{
							cout << "�����ݾ��� �����մϴ�." << endl;
							system("pause");
							continue;
						}

						tPlayer.tInventory.tItem[tPlayer.tInventory.iITemCount] =
							tStoreWeapon[iWeaponIndex];
						++tPlayer.tInventory.iITemCount;

						//��带 �����Ѵ�.
						tPlayer.tInventory.iGold -= tStoreWeapon[iWeaponIndex].iPrice;
						cout << tStoreWeapon[iWeaponIndex].strName << "�������� �����Ͽ����ϴ�. " << endl;
						system("pause");
					}
					break;
				case SM_ARMOR:
					while (true)
					{
						system("cls");
						cout << "************************** ������ **************************" << endl;
						for (int i = 0; i < STORE_ARMOR_MAX; i++)
						{
							cout << i + 1 << ". �̸� : " << tStoreArmor[i].strName <<
								"\t���� : " << tStoreArmor[i].strTypeName << endl;
							cout << "���� : " << tStoreArmor[i].iMin << " ~ " <<
								tStoreArmor[i].iMax << endl;
							cout << "�ǸŰ��� : " << tStoreArmor[i].iPrice <<
								"\t���Ű��� : " << tStoreArmor[i].iSell << endl;
							cout << "���� : " << tStoreArmor[i].strDesc << endl << endl;
						}

						cout << STORE_ARMOR_MAX + 1 << ". �ڷΰ���" << endl;
						cout << "==================================" << endl;
						cout << "�����ݾ� : " << tPlayer.tInventory.iGold << " Gold " << endl;
						cout << "�������� : " << INVENTORY_MAX - tPlayer.tInventory.iITemCount << endl;
						cout << "==================================" << endl;
						cout << "������ �������� �����ϼ��� : ";
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
							cout << "�߸� �����Ͽ����ϴ�. " << endl;
							system("pause");
							continue;
						}

						//�����ǸŸ�� �迭�� �ε����� �����ش�.
						int iArmorIndex = iMenu - 1;


						//�κ��丮�� �� á���� �˻��Ѵ�.
						if (tPlayer.tInventory.iITemCount == INVENTORY_MAX)
						{
							cout << "������ �� á���ϴ�." << endl;
							system("pause");
							continue;
						}

						//���� �����Ұ��
						else if (tPlayer.tInventory.iGold < tStoreArmor[iArmorIndex].iPrice)
						{
							cout << "�����ݾ��� �����մϴ�." << endl;
							system("pause");
							continue;
						}

						tPlayer.tInventory.tItem[tPlayer.tInventory.iITemCount] =
							tStoreArmor[iArmorIndex];
						++tPlayer.tInventory.iITemCount;

						//��带 �����Ѵ�.
						tPlayer.tInventory.iGold -= tStoreArmor[iArmorIndex].iPrice;
						cout << tStoreArmor[iArmorIndex].strName << "�������� �����Ͽ����ϴ�. " << endl;
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
				cout << "************************** �� ���� **************************" << endl;
				cout << "************************** Player **************************" << endl;
				cout << "�̸� : " << tPlayer.strName << "\t���� : " <<
					tPlayer.strJobName << endl;
				cout << "���� : " << tPlayer.iLevel << "\t����ġ : " <<
					tPlayer.iExp << " / " << iLevelUpExp[tPlayer.iLevel - 1] << endl;


				// ���� �����ϰ� ������� �ɷ�ġ�߰�
				if (tPlayer.bEquip[EQ_WEAPON] == true)
				{
					cout << "���ݷ� : " << tPlayer.iAttackMin << " + " << tPlayer.tEquip[EQ_WEAPON].iMin << " ~ " <<
						tPlayer.iAttackMax << " + " << tPlayer.tEquip[EQ_WEAPON].iMax << endl;
				}

				else
				{
					cout << "���ݷ� : " << tPlayer.iAttackMin << " ~ " <<
						tPlayer.iAttackMax << endl;
				}

				//�� �����ϰ� ������� �ɷ�ġ �߰�
				if (tPlayer.bEquip[EQ_ARMOR] == true)
				{
					cout << "���� : " << tPlayer.iArmorMin << " + " << tPlayer.tEquip[EQ_ARMOR].iMin << " ~ " <<
						tPlayer.iArmorMax << " + " << tPlayer.tEquip[EQ_ARMOR].iMax << endl;
				}

				else
				{
					cout << "���� : " << tPlayer.iArmorMin << " ~ " <<
						tPlayer.iArmorMax << endl;
				}

			
				cout << "ü�� : " << tPlayer.iHp << " / " << tPlayer.iHpMax <<
					"\t���� :  " << tPlayer.iMp << " / " << tPlayer.iMpMax << endl;
				cout << "������� : " << tPlayer.tInventory.iGold << " Gold" << endl;

				if (tPlayer.bEquip[EQ_WEAPON])
					cout << "�������� : " << tPlayer.tEquip[EQ_WEAPON].strName ;
				else
					cout << "�������� : ���� " ;

				if (tPlayer.bEquip[EQ_ARMOR])
					cout << "\t������ : " << tPlayer.tEquip[EQ_ARMOR].strName << endl;
				else
					cout << "\t������ : ���� " << endl;

				for (int i = 0; i < tPlayer.tInventory.iITemCount; ++i)
				{
					cout << "==================================" << endl;
					cout << i + 1 << ". �̸� : " << tPlayer.tInventory.tItem[i].strName <<
						"\t���� : " << tPlayer.tInventory.tItem[i].strTypeName << endl;
					cout << "���ݷ� : " << tPlayer.tInventory.tItem[i].iMin << " ~ " <<
						tPlayer.tInventory.tItem[i].iMax << endl;
					cout << "�ǸŰ��� : " << tPlayer.tInventory.tItem[i].iPrice <<
						"\t���Ű��� : " << tPlayer.tInventory.tItem[i].iSell << endl;
					cout << "���� : " << tPlayer.tInventory.tItem[i].strDesc << endl << endl;
					cout << "==================================" << endl;
				}

				cout << tPlayer.tInventory.iITemCount + 1 << ". �ڷΰ���" << endl;
				cout << "������ �������� �����ϼ��� : ";
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
					cout << "�߸� �����Ͽ����ϴ�. " << endl;
					system("pause");
					continue;
				}

				//������ �ε��� ����.
				int idx = iMenu - 1;

				//����� �������� ��� �������� ������ ���� ���� ������ ����.
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

				//�������� �����Ǿ� ���� ��� �����Ǿ� �ִ� �����۰� ��ü.
				if (tPlayer.bEquip[eq] == true)
				{
					_tagItem tSwap = tPlayer.tEquip[eq];
					tPlayer.tEquip[eq] = tPlayer.tInventory.tItem[eq];
					tPlayer.tInventory.tItem[idx] = tSwap;
				}

				//�����Ǿ����� ������� 
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

				cout << tPlayer.tEquip[eq].strName << "�������� �����Ͽ����ϴ�." << endl;
			}
			break;
		default:
			cout << " �߸� �Է��ϼ̽��ϴ�. " << endl;
			break;
		}
	}

}