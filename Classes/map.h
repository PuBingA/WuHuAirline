#include "cocos2d.h"
#include "public_define.h"
#include "cocos-ext.h"
#include "ui/CocosGUI.h"
#include "Frames.h"
#include "monster_towers.h"
#include <string>
#include <vector>
USING_NS_CC;

//VS包含每个种植位的所有信息：统一编排的序号+位置状态+防御塔种类+现有的精灵指针
typedef struct Vacancy_State
{
    int index;
    int tower_type;
    Tower* spr;
}VS;

class Map_father :public cocos2d::Scene
{
protected:
    Sprite* yellow_frame = nullptr;
    Sprite* plant_cannon = nullptr;
    Sprite* plant_shit = nullptr;
    Sprite* plant_etower = nullptr;
    Sprite* upgrade_frame = nullptr;
    Sprite* delete_frame = nullptr;
    Cannon* cannon = nullptr;
    Shit* shit = nullptr;
    Etower* etower = nullptr;
    Carrot* carrot = nullptr;
    ui::Button* carrot_level_button = nullptr;      //存放萝卜升级按钮
    std::vector<FS> AllPlants;
    std::vector<FS> AllFrames;
    bool mouse_select_type = 0;
    XY singleclick;                                 //存储点击的位置
    int vacancyIndex = -1;                          //点位索引
    std::vector<VS> vacancy;                        //vacancy存放每个可放置位置的信息
    int gold_content[1];                           //当前金币数数组
    int* gold=gold_content;                                       //当前金币数指针
    Label* gold_label;                              //金币标签
    std::vector<std::vector<float>>walk_way;        //存放怪物行进的x,y轴的向量
    Node* monster_wave = new Node;
    MonSprite* boss = nullptr;
    bool boss_spawned = false;
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
    void onMouseDown_Do_Plant(Event* event);
    std::string calculate_gold(int *gold);       //根据当前金币，得出字符串
    void change_gold_label(float dt);   //更新金币储存

    virtual void game_begin() {};                     //游戏开始函数
    void game_over_success(float dt);                 //游戏胜利
    void game_over_failure(float dt);                 //游戏失败
    void input_carrot_level_button();;                //放置萝卜升级按钮
    void carrot_level_button_call_back(cocos2d::Ref* pSender);     //萝卜升级回调函数
    void change_carrot_level_button(float dt);                //检测当前是否可以进行萝卜升级,使萝卜按钮失效/有效（金币变化，萝卜等级改变时需要调用！）
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
    void spawnBoss(float dt);             //生成Type=5的怪物
    void waitForConditionAndExecute(const std::function<bool()>& condition, const std::function<void()>& callback);
    CREATE_FUNC(Map_father);
};

class Map_One :public Map_father
{
public:
    Map_One()
    {
        *gold = gold_1;
    }//构造函数
    virtual void ShowPlantButton();
    virtual void input_listener();
    virtual void input_background();
    virtual void input_walk_way();
    virtual void game_begin();      //游戏开始函数
    CREATE_FUNC(Map_One);
};

class Map_Two :public Map_father
{
public:
    Map_Two()
    {
        *gold = gold_2;
    }//构造函数
    virtual void ShowPlantButton();
    virtual void input_listener();
    virtual void input_background();
    virtual void input_walk_way();
    virtual void game_begin();      //游戏开始函数
    CREATE_FUNC(Map_Two);
};

class Map_Three :public Map_father
{
public:
    Map_Three()
    {
        *gold = gold_3;
    }//构造函数
    virtual void ShowPlantButton();
    virtual void input_listener();
    virtual void input_background();
    virtual void input_walk_way();
    virtual void game_begin();      //游戏开始函数
    CREATE_FUNC(Map_Three);
};

