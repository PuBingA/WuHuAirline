#include"cocos2d.h"
#include<vector>
#include<string>
#include"public_define.h"


class Map_father :public cocos2d::Scene
{
public:
    static cocos2d::Scene* createScene();

    virtual bool init();//����������,���̳й��в���

    virtual void input_background() {};//���ñ���ͼ

    virtual void input_walk_way() {};//���ù����н�·��

    void menuCallback(cocos2d::Ref* pSender);//�˵���Ӧ����

    void input_return_pause();//���÷��أ��Լ���ͣ��   ��ͣ��δʵ��

    // implement the "static create()" method manually
    CREATE_FUNC(Map_father);


};


#define walk_way_begin_1 {250,550} //���￪ʼ�ƶ�������
#define way_size 82//ÿ���ذ�����ش�С
class Map_One :public Map_father
{
public:
    virtual void input_background();
    virtual void input_walk_way();

    CREATE_FUNC(Map_One);
private:
    std::vector<std::vector<double>>walk_way_store_1;//��Ź����н���x,y�������
};


#define walk_way_begin_2 {250-way_size,550-5*way_size} //���￪ʼ�ƶ�������
class Map_Two :public Map_father
{
public:
    virtual void input_background();
    virtual void input_walk_way();

    CREATE_FUNC(Map_Two);
private:
    std::vector<std::vector<double>>walk_way_store_2;//��Ź����н���x,y�������
};

#define walk_way_begin_3 {250,600} //���￪ʼ�ƶ�����
class Map_Three :public Map_father
{
public:
    virtual void input_background();
    virtual void input_walk_way();

    CREATE_FUNC(Map_Three);
private:
    std::vector<std::vector<double>>walk_way_store_3;//��Ź����н���x,y�������
};

