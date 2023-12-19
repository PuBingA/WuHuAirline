#include"cocos2d.h"
#include<vector>
#include"public_define.h"
#include<string>

class Map_father :public cocos2d::Scene
{
public:
    static cocos2d::Scene* createScene();

    virtual bool init();//创建场景类,被继承公有部分
    virtual void input_background() {};//放置背景图
    virtual void input_walk_way() {};//放置怪物行进路线
    void menuCallback(cocos2d::Ref* pSender);//返回响应函数
    void input_return_pause();//放置返回，以及暂停键 
    void buttonCallback(cocos2d::Ref* pSender);//暂停响应函数
    void input_gold(const int gold);//放置金币UI
    virtual void input_carrot() {};//放置萝卜
    template<typename T>
    void input_brick(T x,T y ,int choice);//放置地板

    // implement the "static create()" method manually
    CREATE_FUNC(Map_father);
};

class Map_One :public Map_father
{
public:
    virtual void input_background();
    virtual void input_walk_way();
    virtual void input_carrot();
    CREATE_FUNC(Map_One);
private:
    std::vector<std::vector<float>>walk_way_store_1;//存放怪物行进的x,y轴的向量
};

class Map_Two :public Map_father
{
public:
    virtual void input_background();
    virtual void input_walk_way();
    virtual void input_carrot();
    CREATE_FUNC(Map_Two);
private:
    std::vector<std::vector<float>>walk_way_store_2;//存放怪物行进的x,y轴的向量
};

class Map_Three :public Map_father
{
public:
    virtual void input_background();
    virtual void input_walk_way();
    virtual void input_carrot();
    CREATE_FUNC(Map_Three);
private:
    std::vector<std::vector<float>>walk_way_store_3;//存放怪物行进的x,y轴的向量
};

