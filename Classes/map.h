#include "cocos2d.h"
#include "public_define.h"
#include "cocos-ext.h"
#include "Frames.h"
#include "monster.h"
#include <string>
#include <vector>
USING_NS_CC;

//VS包含每个种植位的所有信息：统一编排的序号+位置状态+防御塔种类+现有的精灵指针
typedef struct Vacancy_State
{
    int index;
    int level;
    int tower_type;
    Sprite* spr;
}VS;

//level=0 空 
//level=1 放置了一级炮台
//level=2 放置了二级炮台
//level=3 放置了三级炮台
//tower_type=1 加农炮
//tower_type=2 屎
//tower_type=3 电磁塔

class Map_father :public cocos2d::Scene
{
protected:
    FrameBox* yellow_frame = nullptr;
    FrameBox* plant_cannon = nullptr;
    FrameBox* plant_shit = nullptr;
    FrameBox* plant_etower = nullptr;
    FrameBox* cannon = nullptr;
    FrameBox* shit = nullptr;
    FrameBox* etower = nullptr;
    FrameBox* upgrade_frame = nullptr;
    FrameBox* delete_frame = nullptr;
    Carrot* carrot = nullptr;
    bool mouse_select_type = 0;
    int WhichPlant = 0;
    XY singleclick;                                 //存储点击的位置
    int vacancyIndex = -1;                          //点位索引
    std::vector<VS> vacancy;                        //vacancy存放每个可放置位置的信息
    int gold;                                       //当前金币数
    Label* gold_label;                              //金币标签
    std::vector<std::vector<float>>walk_way;        //存放怪物行进的x,y轴的向量
    std::vector<MonSprite*>monster_wave;
public:
    static cocos2d::Scene* createScene();
    virtual bool init();                              //创建场景类,被继承公有部分
    virtual void input_background() {};               //放置背景图
    virtual void input_walk_way() {};                 //放置怪物行进路线
    void menuCallback(cocos2d::Ref* pSender);         //返回响应函数
    void input_return_pause();                        //放置返回，以及暂停键 
    void buttonCallback(cocos2d::Ref* pSender);       //暂停响应函数
    void input_gold_item();                           //放置金币UI
    virtual void ShowPlantButton() {};
    virtual void input_listener() {};
    cocos2d::Label* input_gold();                     //生成金币标签
    std::string calculate_gold(const int gold);       //根据当前金币，得出字符串
    virtual void game_begin() {};                     //游戏开始函数
    void game_over_success(float dt);                 //游戏胜利
    void game_over_failure(float dt);                 //游戏失败
    template<typename T>
    void input_brick(T x,T y ,int choice);            //放置地板
    void spawnMonster1_1(float dt);       //生成Type=1的怪物
    void spawnMonster1_2(float dt);       //生成Type=1的怪物
    void spawnMonster1_3(float dt);       //生成Type=1的怪物
    void spawnMonster2_1(float dt);       //生成Type=2的怪物
    void spawnMonster2_2(float dt);       //生成Type=2的怪物
    void spawnMonster2_3(float dt);       //生成Type=2的怪物
    void spawnMonster3_1(float dt);       //生成Type=3的怪物
    void spawnMonster3_2(float dt);       //生成Type=3的怪物
    void spawnMonster3_3(float dt);       //生成Type=3的怪物
    void spawnMonster4_1(float dt);       //生成Type=4的怪物
    void spawnMonster4_2(float dt);       //生成Type=4的怪物
    void spawnMonster4_3(float dt);       //生成Type=4的怪物
    void waitForConditionAndExecute(const std::function<bool()>& condition, const std::function<void()>& callback);
    CREATE_FUNC(Map_father);
};

class Map_One :public Map_father
{
public:
    virtual void ShowPlantButton();
    virtual void input_listener();
    void onMouseDown_Do_Plant(Event* event);
    void StartAttack();
    virtual void input_background();
    virtual void input_walk_way();
    virtual void game_begin();      //游戏开始函数
    CREATE_FUNC(Map_One);
};

class Map_Two :public Map_father
{
public:
    virtual void ShowPlantButton();
    virtual void input_listener();
    void onMouseDown_Do_Plant(Event* event);

    virtual void input_background();
    virtual void input_walk_way();
    virtual void game_begin();      //游戏开始函数
    CREATE_FUNC(Map_Two);
};

class Map_Three :public Map_father
{
public:
    virtual void ShowPlantButton();
    virtual void input_listener();
    void onMouseDown_Do_Plant(Event* event);

    virtual void input_background();
    virtual void input_walk_way();
    virtual void game_begin();      //游戏开始函数
    CREATE_FUNC(Map_Three);
};

