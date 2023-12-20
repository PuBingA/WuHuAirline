#include <vector>
#include <string>
#include "cocos2d.h"
#include "public_define.h"
using namespace cocos2d;

/*********************************************************
* 防御塔的index对应不同的防御塔种类：
* index=1 一级炮台 index=2 二级炮台 index=3 三级炮台
* index=4 一级屎   index=5 二级屎   index=6 三级屎
* index=7 一级电塔 index=8 二级电塔 index=9 三级电塔
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

//建立炮台花费100
const TI Cannon_1 = { 1, 180, 80, 100, 30, 500 };
const TI Cannon_2 = { 2, 260, 234, 150, 40, 500 };
const TI Cannon_3 = { 3, -1, 432, 200, 50, 500 };
//建立屎花费120
const TI Shit_1 = { 4, 220, 96, 75, 20, 400 };
const TI Shit_2 = { 5, 260, 272, 100, 35, 450 };
const TI Shit_3 = { 6, -1, 480, 125, 50, 500 };
//建立电塔花费160
const TI ETower_1 = { 7, 320, 128, 250, 50, 1000 };
const TI ETower_2 = { 8, 480, 384, 275, 60, 1000 };
const TI ETower_3 = { 9, -1, 768, 300, 70, 1000 };


class FrameSprite;
class TowerSprite;
class TowerControl;

class BulletSprite;
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
	void Spawn()const;   //鼠标点击，出现框
	void Shimmer()const; //自动呈现闪烁效果，直到下一次点击
	void Disappear();    //下一次点击后，框消失
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