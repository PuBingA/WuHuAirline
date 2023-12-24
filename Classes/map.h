#include"cocos2d.h"
#include<vector>
#include"public_define.h"
#include<string>
#include"cocos-ext.h"
#include "Frames.h"
#include "monster.h"
#include "Priority_Queue.h"
USING_NS_CC;

//VS包含每个种植位的所有信息：统一编排的序号+位置状态+防御塔种类+现有的精灵指针
typedef struct Vacancy_State
{
    int index;
    int state;
    int tower_type;
    Sprite* spr;
}VS;

//state=0 空 
//state=1 放置了一级炮台
//state=2 放置了二级炮台
//state=3 放置了三级炮台
//tower_type=1 加农炮
//tower_type=2 屎
//tower_type=3 电磁塔


class Map_father :public cocos2d::Scene
{
protected:
    FrameBox* yellow_frame = nullptr;
    FrameBox* tower_cannon = nullptr;
    FrameBox* tower_cannon_ready = nullptr;
    FrameBox* tower_shit = nullptr;
    FrameBox* tower_shit_ready = nullptr;
    FrameBox* tower_etower = nullptr;
    FrameBox* tower_etower_ready = nullptr;
    FrameBox* cannon_Lv1 = nullptr;
    FrameBox* cannon_Lv2 = nullptr;
    FrameBox* cannon_Lv3 = nullptr;
    FrameBox* shit_Lv1 = nullptr;
    FrameBox* shit_Lv2 = nullptr;
    FrameBox* shit_Lv3 = nullptr;
    FrameBox* etower_Lv1 = nullptr;
    FrameBox* etower_Lv2 = nullptr;
    FrameBox* etower_Lv3 = nullptr;
    FrameBox* upgrade_grey = nullptr;
    FrameBox* upgrade_ready = nullptr;
    FrameBox* delete_grey = nullptr;
    FrameBox* delete_ready = nullptr;
    int WhichPlant = 0;
    /* 不仅指示植物，还指示操作！只代表相对位置！
               WhichPlant = 1 cannon
               WhichPlant = 2 shit
               WhichPlant = 3 upgrade
               WhichPlant = 4 delete           */
    XY singleclick;                                 //存储点击的位置
    int vacancyIndex = -1;                          //点位索引
    std::vector<VS> vacancy;                        //vacancy存放每个可放置位置的信息
    int gold;                                       //当前金币数
    Label* gold_label;                              //金币标签
    PQueue<MonSprite*> currentMonstersOnScreen;     //存放场上所有怪物的指针的vector
    std::vector<std::vector<float>>walk_way;        //存放怪物行进的x,y轴的向量
public:
    static cocos2d::Scene* createScene();
    virtual bool init();                              //创建场景类,被继承公有部分
    virtual void input_background() {};               //放置背景图
    virtual void input_walk_way() {};                 //放置怪物行进路线
    void menuCallback(cocos2d::Ref* pSender);         //返回响应函数
    void input_return_pause();                        //放置返回，以及暂停键 
    void buttonCallback(cocos2d::Ref* pSender);       //暂停响应函数
    void input_gold_item();                           //放置金币UI
    cocos2d::Label* input_gold();                     //生成金币标签
    std::string calculate_gold(const int gold);       //根据当前金币，得出字符串
    template<typename T>
    cocos2d::Label* HP_display(const T x, const T y); //在相应坐标生成萝卜
    std::string calculate_HP(const int HP);           //根据萝卜血量，等处字符串
    virtual void game_begin() {};                     //游戏开始函数
    void game_over_success(float dt);                 //游戏胜利
    void game_over_failure(float dt);                 //游戏失败
    template<typename T>
    void input_brick(T x,T y ,int choice);            //放置地板
    void Map_father::spawn_single_monster_1(float dt);//生成单个怪物
    void waitForConditionAndExecute(const std::function<bool()>& condition, const std::function<void()>& callback);
    CREATE_FUNC(Map_father);
};

class Map_One :public Map_father
{
private:

public:
    Map_One();
    void ShowTowerDark();
    void input_listener();
    void onMouseDown_Do_Plant(Event* event);
    void onMouseDown_Show_Yellow(Event* event);

    virtual void input_background();
    virtual void input_walk_way();
    virtual void game_begin();      //游戏开始函数
    CREATE_FUNC(Map_One);
};

class Map_Two :public Map_father
{
public:
public:
    Map_Two();
    void ShowTowerDark();
    void input_listener();
    void onMouseDown_Do_Plant(Event* event);
    void onMouseDown_Show_Yellow(Event* event);

    virtual void input_background();
    virtual void input_walk_way();
    virtual void game_begin();      //游戏开始函数
    CREATE_FUNC(Map_Two);
};

class Map_Three :public Map_father
{
public:
    virtual void input_background();
    virtual void input_walk_way();
    virtual void game_begin();      //游戏开始函数
    CREATE_FUNC(Map_Three);
};

