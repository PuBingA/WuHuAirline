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

    // implement the "static create()" method manually
    CREATE_FUNC(Map_father);


};


#define walk_way_begin_x 250 
#define walk_way_begin_y 550//���￪ʼ�ƶ�������
#define way_size 82//ÿ���ذ�����ش�С
class Map_One :public Map_father
{
public:
    virtual void input_background();
    virtual void input_walk_way();

    CREATE_FUNC(Map_One);
private:
    std::vector<double>walk_way_store_x;
    std::vector<double>walk_way_store_y;//��Ź����н���x,y�������
};


#define two_walk_way_begin_x 250-way_size 
#define two_walk_way_begin_y 550-5*way_size//���￪ʼ�ƶ�������
class Map_Two :public Map_father
{
public:
    virtual void input_background();
    virtual void input_walk_way();

    CREATE_FUNC(Map_Two);
private:
    std::vector<double>walk_way_store_x;
    std::vector<double>walk_way_store_y;//��Ź����н���x,y�������

};

