#include"cocos2d.h"
#include"public_define.h"
#include<string>
#include<math.h>
USING_NS_CC;

/*--------------父类-----------------*/
class Tower :public cocos2d::Sprite
{
protected:
	int cost_1;//建造花费
	int cost_2;//升2级花费
	int cost_3;//升3级花费
	int distance ;//攻击距离
	int level;
	std::string Tower_name;//防御塔图片名字
public:
	static Tower* create() {}//初始化精灵


	bool if_build(const int gold)//判断是否可以建造
	{
		if (gold >= cost_1)
			return true;
		else
			return false;
	}
	
	template<typename T>
	void input_towel(const T& x ,const T & y)
	{
		this->setTexture(Tower_name);//生成对应名字的塔贴图
		this->setPosition(x, y);//设置坐标
	}
	

	bool if_evolution(const int gold)//判断是否可以升级
	{
		if (level == 3)//满级不可升级
			return false;
		else
		{
			if(level ==1&&gold>=cost_2)
				return true;
			if(level==2&&gold>=cost_3)
			return true;

			return false;
		}
	};
	virtual int level_up() {};//升级

	template<typename T>
	bool if_shoot(const T& x, const T& y)//判断是否可以射击
	{
		if (sqrt(pow((this->getPositionX() - x), 2) + pow((this->getPositionY() - y), 2)) <= distance)//两点间距离公式
		{
			return true;
		}
		else
		{
			return false;
		}
	}
	
	
};
/*--------------父类-----------------*/



/*---------------防御塔1------------------*/
class Tower_1 : public ::Tower
{
public:
	Tower_1()
	{
		cost_1 = 200;
		cost_2 = 280;
		cost_3 = 400;
		distance = 100;
		level = 1;
		Tower_name = "cannon_Lv1.png";
	}//构造函数,区别与其他防御塔

	int level_up()//升级函数，返回升级费用
	{
		int level_cost = 0;
		level++;
		if (level == 2)
		{
			Tower_name = "cannon_Lv2.png";
			level_cost = cost_2;
		}
		if (level == 3)
		{
			Tower_name = "cannon_Lv3.png";
			level_cost = cost_3;
		}

		this->setTexture(Tower_name);//改变外貌
		return level_cost;
	}

};
/*---------------防御塔1------------------*/


/*---------------防御塔2--------------------*/
class Tower_2 : public ::Tower
{
public:
	Tower_2()
	{
		cost_1 = 180;
		cost_2 = 240;
		cost_3 = 360;
		distance = 100;
		level = 1;
		Tower_name = "shit_Lv1.png";
	}//构造函数,区别与其他防御塔

	int level_up()//升级函数，返回升级费用
	{
		int level_cost = 0;
		level++;
		if (level == 2)
		{
			Tower_name = "shit_Lv2.png";
			level_cost = cost_2;
		}
		if (level == 3)
		{
			Tower_name = "shit_Lv3.png";
			level_cost = cost_3;
		}

		this->setTexture(Tower_name);//改变外貌
		return level_cost;
	}

};
/*---------------防御塔2------------------*/


/*---------------防御塔3--------------------*/
class Tower_3 : public ::Tower
{
public:
	Tower_3()
	{
		cost_1 = 300;
		cost_2 = 400;
		cost_3 = 560;
		distance = 180;
		level = 1;
		Tower_name = "etower_Lv1.png";
	}//构造函数,区别与其他防御塔

	int level_up()//升级函数，返回升级费用
	{
		int level_cost = 0;
		level++;
		if (level == 2)
		{
			Tower_name = "etower_Lv2.png";
			level_cost = cost_2;
		}
		if (level == 3)
		{
			Tower_name = "etower_Lv2.png";
			level_cost = cost_3;
		}

		this->setTexture(Tower_name);//改变外貌
		return level_cost;
	}

};
/*---------------防御塔3------------------*/
