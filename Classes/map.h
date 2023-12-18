#include"cocos2d.h"
#include<vector>
#include<string>
#include"public_define.h"


class Map_father :public cocos2d::Scene
{
public:
    static cocos2d::Scene* createScene();

    virtual bool init();//创建场景类,被继承公有部分
    virtual void input_background() {};//放置背景图
    virtual void input_walk_way() {};//放置怪物行进路线
    void menuCallback(cocos2d::Ref* pSender);//菜单响应函数
    void input_return_pause();//放置返回，以及暂停键   暂停键未实现

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

    CREATE_FUNC(Map_One);
private:
    std::vector<Vec2>walk_way_store_1;//存放怪物行进的x,y轴的向量
};

class Map_Two :public Map_father
{
public:
    virtual void input_background();
    virtual void input_walk_way();

    CREATE_FUNC(Map_Two);
private:
    std::vector<Vec2>walk_way_store_2;//存放怪物行进的x,y轴的向量
};

class Map_Three :public Map_father
{
public:
    virtual void input_background();
    virtual void input_walk_way();

    CREATE_FUNC(Map_Three);
private:
    std::vector<Vec2>walk_way_store_3;//存放怪物行进的x,y轴的向量
};

