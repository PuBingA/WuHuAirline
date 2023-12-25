#include"cocos2d.h"
#include"public_define.h"
#include<string>
#include<math.h>
USING_NS_CC;

/*--------------����-----------------*/
class Tower :public cocos2d::Sprite
{
protected:
	int cost_1;//���컨��
	int cost_2;//��2������
	int cost_3;//��3������
	int distance ;//��������
	int level;
	std::string Tower_name;//������ͼƬ����
public:
	static Tower* create() {}//��ʼ������


	bool if_build(const int gold)//�ж��Ƿ���Խ���
	{
		if (gold >= cost_1)
			return true;
		else
			return false;
	}
	
	template<typename T>
	void input_towel(const T& x ,const T & y)
	{
		this->setTexture(Tower_name);//���ɶ�Ӧ���ֵ�����ͼ
		this->setPosition(x, y);//��������
	}
	

	bool if_evolution(const int gold)//�ж��Ƿ��������
	{
		if (level == 3)//������������
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
	virtual int level_up() {};//����

	template<typename T>
	bool if_shoot(const T& x, const T& y)//�ж��Ƿ�������
	{
		if (sqrt(pow((this->getPositionX() - x), 2) + pow((this->getPositionY() - y), 2)) <= distance)//�������빫ʽ
		{
			return true;
		}
		else
		{
			return false;
		}
	}
	
	
};
/*--------------����-----------------*/



/*---------------������1------------------*/
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
	}//���캯��,����������������

	int level_up()//����������������������
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

		this->setTexture(Tower_name);//�ı���ò
		return level_cost;
	}

};
/*---------------������1------------------*/


/*---------------������2--------------------*/
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
	}//���캯��,����������������

	int level_up()//����������������������
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

		this->setTexture(Tower_name);//�ı���ò
		return level_cost;
	}

};
/*---------------������2------------------*/


/*---------------������3--------------------*/
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
	}//���캯��,����������������

	int level_up()//����������������������
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

		this->setTexture(Tower_name);//�ı���ò
		return level_cost;
	}

};
/*---------------������3------------------*/
