#include <vector>
#include <string>
#include "cocos2d.h"
#include "public_define.h"
using namespace cocos2d;

/*********************************************************
* ��������index��Ӧ��ͬ�ķ��������ࣺ
* index=1 һ����̨ index=2 ������̨ index=3 ������̨
* index=4 һ��ʺ   index=5 ����ʺ   index=6 ����ʺ
* index=7 һ������ index=8 �������� index=9 ��������
**********************************************************/
typedef struct TowerInfo
{
	int index;
	int upgrade_cost;
	int destroy_cost;
	int ATK_radius;
	int ATK_damage;
	int speed;
}TI;

//������̨����100
const TI Cannon_1 = { 1, 180, 80, 100, 30, 500 };
const TI Cannon_2 = { 2, 260, 234, 150, 40, 500 };
const TI Cannon_3 = { 3, -1, 432, 200, 50, 500 };
//����ʺ����120
const TI Shit_1 = { 4, 220, 96, 75, 20, 400 };
const TI Shit_2 = { 5, 260, 272, 100, 35, 450 };
const TI Shit_3 = { 6, -1, 480, 125, 50, 500 };
//������������160
const TI ETower_1 = { 7, 320, 128, 250, 50, 1000 };
const TI ETower_2 = { 8, 480, 384, 275, 60, 1000 };
const TI ETower_3 = { 9, -1, 768, 300, 70, 1000 };


class FrameSprite;
class TowerSprite;
class BulletSprite;
class TowerControl;
class BulletControl;

class FrameSprite : public Sprite
{
private:
	Sprite* Current;
	int FrameType;
public:
	FrameSprite(Sprite* crnt, int fr_type)
	{
		Current = crnt;
		FrameType = fr_type;
	}
	void Spawn()const;   //����������ֿ�
	void Shimmer()const; //�Զ�������˸Ч����ֱ����һ�ε��
	void Disappear();    //��һ�ε���󣬿���ʧ
};

class TowerSprite : public Sprite
{
	friend class TowerControl;
public:
	static Sprite* Create(const std::string& filename)
	{
		Sprite* current = new Sprite;
		if (current && current->initWithFile(filename))
		{
			current->autorelease();
			return current;
		}
		CC_SAFE_DELETE(current);
		return nullptr;
	}
};

class TowerControl
{
private:
	Sprite* CurrentSprite;
	TI Info;
public:
	TowerControl(Sprite* curr, TI& info)
	{
		CurrentSprite = curr;
		Info = info;
	}
	void Spawn()const;
	void Rotate()const;
	void Upgrade();
	void Disappear();
};