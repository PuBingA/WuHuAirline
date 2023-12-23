﻿#include"map.h"
#include"choose_map.h"
#include"carrot.h"
#include "ui/CocosGUI.h"
#include"cocos-ext.h"
#include"settlement_interface.h"
USING_NS_CC;
using namespace std;

extern bool map_two_flag;
extern bool map_three_flag;

int CheckBox(XY obj, const std::vector<FS>& table);

/*-------------------------------父类函数-----------------------------------*/
cocos2d::Scene* Map_father::createScene()
{
    return Map_father::create();
}

static void problemLoading(const char* filename)
{
    printf("Error while loading: %s\n", filename);
    printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in HelloWorldScene.cpp\n");
}

bool Map_father::init()//父类创建场景总函数
{
    static int gold = 4321;//初始金币
    if (!Scene::init())
        return false;

    auto visibleSize = Director::getInstance()->getVisibleSize();//获取可见大小
    Vec2 origin = Director::getInstance()->getVisibleOrigin();//获取opengl起点

    input_background();//放置背景图
    input_walk_way();//放置地板
    input_return_pause();//放置返回，暂停键
    input_gold_item();//放置金币
    game_begin();//开始游戏
    return true;
}

void Map_father::input_return_pause()//父类放置暂停以及返回键函数
{
    bool pause = false;
    auto return_menu = MenuItemImage::create("return.png", "return_selected.png", CC_CALLBACK_1(Map_father::menuCallback, this));
    auto menu = Menu::create(return_menu, NULL);
    this->addChild(menu);
    menu->setPosition(return_x, return_y);
    //返回键放置完毕
    auto button = ui::Button::create("pause_1.png","pause_2.png");
    this->addChild(button);
    button->setPosition(Point(pause_x,pause_y));
    button->addClickEventListener(CC_CALLBACK_1(Map_father::buttonCallback, this));
    //暂停键创建完毕
    
}

void Map_father::input_gold_item()//放置阳光图标
{
   
    auto gold_item = Sprite::create("gold.png");//生成阳光图标
    this->addChild(gold_item);
    gold_item->setPosition(gold_x - 90, gold_y);
    //放好阳光图标
}

cocos2d::Label* Map_father::input_gold()//生成金币标签
{
    auto gold_label = Label::createWithTTF("", "fonts\\Marker Felt.ttf", 56);
    Color3B gold_color(255, 233, 0);
    gold_label->setColor(gold_color);//调成黄色
    this->addChild(gold_label);
    gold_label->setPosition(gold_x, gold_y);
    return gold_label;
}

string Map_father::calculate_gold(const int gold)
{
    int digit = 1000;//千位
    string figure;
    for (int i = 0; i < 4; i++)
    {
        int k = (gold / digit) % 10;
        digit /= 10;
        figure.push_back(k + '0');
    }//计算出每一位的数字，放入字符串中
    return figure;
}

template<typename T>
cocos2d::Label* Map_father::HP_display(const T x, const T y)//放置萝卜血条函数
{
    auto HP_label = Label::createWithTTF("", "fonts\\Marker Felt.ttf", 40);
    Color3B HP_color(255, 0, 0);
    HP_label->setColor(HP_color);//调成红色
    HP_label->setPosition(x, y);
    this->addChild(HP_label);//生成好血量标签
    auto Hp_item = Sprite::create("carrot_HP.png");
    Hp_item->setPosition(x - 50, y);
    this -> addChild(Hp_item);//生成血量图标

    return HP_label;
}

std::string Map_father::calculate_HP(const int HP)//根据萝卜血量生成字符串
{
    string figure;
    int digit = 10;//十位
    for (int i = 0; i < 2; i++)
    {
        int k = (HP / digit) % 10;
        digit /= 10;
        figure += k + '0';
    }//计算出每一位的数字，放入字符串中
    return figure;
}

void Map_father::buttonCallback(cocos2d::Ref* pSender)//暂停键触发函数
{
    if (!Director::getInstance()->isPaused())
    {
        Director::getInstance()->pause();
        AudioEngine::pauseAll();
    }//暂停
    else
    {
        Director::getInstance()->resume();
        AudioEngine::resumeAll();
    }//继续
}

void Map_father::menuCallback(cocos2d::Ref* pSender)//返回键触发函数
{
    Director::getInstance()->replaceScene(choose_map::createScene());//切换到选择地图场景
}

void Map_father::game_over_success(float dt)
{
    auto scene = settlement_success::createScene();
    Director::getInstance()->replaceScene(TransitionCrossFade::create(2.0f, scene));
}

void Map_father::game_over_failure(float dt)
{
    auto scene = settlement_failure::createScene();
    Director::getInstance()->replaceScene(TransitionCrossFade::create(2.0f, scene));
}

template<typename T>
void Map_father::input_brick(T x, T y ,int choice)//choice==1 放置怪物绿色地板
{
    if (choice == 1)
    {
        auto walk_way = Sprite::create("way.png");
        this->addChild(walk_way);
        walk_way->setPosition(x, y);//背景图
    }
}

/*-------------------------------父类函数-----------------------------------*/



/*------------------------------地图一函数----------------------------------*/
/*****************************change*************************************/
Map_One::Map_One()
{
    //初始化vacancy_spots
    for (int i = 0; i <= 37; i++)
        vacancy.push_back({ i,0,0,nullptr });
    //为指针动态分配空间，避免野指针
    yellow_frame = new FrameBox(Sprite::create("yellow_frame.png"));
    tower_cannon = new FrameBox(Sprite::create("TI_1_unavailable.png"));
    tower_shit = new FrameBox(Sprite::create("TI_2_unavailable.png"));
    tower_cannon_ready = new FrameBox(Sprite::create("TI_1_available.png"));
    tower_shit_ready = new FrameBox(Sprite::create("TI_2_available.png"));
    cannon_Lv1 = new FrameBox(Sprite::create("cannon_Lv1.png"));
    cannon_Lv2 = new FrameBox(Sprite::create("cannon_Lv2.png"));
    cannon_Lv3 = new FrameBox(Sprite::create("cannon_Lv3.png"));
    shit_Lv1 = new FrameBox(Sprite::create("shit_Lv1.png"));
    shit_Lv2 = new FrameBox(Sprite::create("shit_Lv2.png"));
    shit_Lv3 = new FrameBox(Sprite::create("shit_Lv3.png"));
    upgrade_grey = new FrameBox(Sprite::create("upgrade_grey.png"));
    upgrade_ready = new FrameBox(Sprite::create("upgrade_ready.png"));
    delete_grey = new FrameBox(Sprite::create("delete_grey.png"));
    delete_ready = new FrameBox(Sprite::create("delete_ready.png"));
}

Map_One::~Map_One()
{
    CC_SAFE_DELETE(yellow_frame);
    CC_SAFE_DELETE(tower_cannon);
    CC_SAFE_DELETE(tower_shit);
    CC_SAFE_DELETE(tower_cannon_ready);
    CC_SAFE_DELETE(tower_shit_ready);
    CC_SAFE_DELETE(cannon_Lv1);
    CC_SAFE_DELETE(cannon_Lv2);
    CC_SAFE_DELETE(cannon_Lv3);
    CC_SAFE_DELETE(shit_Lv1);
    CC_SAFE_DELETE(shit_Lv2);
    CC_SAFE_DELETE(shit_Lv3);
    CC_SAFE_DELETE(upgrade_grey);
    CC_SAFE_DELETE(upgrade_ready);
    CC_SAFE_DELETE(delete_grey);
    CC_SAFE_DELETE(delete_ready);
}

void Map_One::input_listener()
{
    auto mouseListener_show_yellow_frame = EventListenerMouse::create();
    mouseListener_show_yellow_frame->onMouseDown = CC_CALLBACK_1(Map_One::onMouseDown_Show_Yellow, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(mouseListener_show_yellow_frame, this);

    auto mouseListener_for_planting = EventListenerMouse::create();
    mouseListener_for_planting->onMouseDown = CC_CALLBACK_1(Map_One::onMouseDown_Do_Plant, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(mouseListener_for_planting, this);

    yellow_frame->Current = Sprite::create("yellow_frame.png");
    this->addChild(yellow_frame->Current); //z-value=0
    yellow_frame->Current->setVisible(false);
}

void Map_One::onMouseDown_Do_Plant(Event* event)
{
    EventMouse* e = dynamic_cast<EventMouse*>(event);
    if (e->getMouseButton() == EventMouse::MouseButton::BUTTON_LEFT)
    {
        int x = e->getCursorX(), y = e->getCursorY();
        if (IsFramePlant_Lv1(x, y))
        {
            if (x == 450)//plant a cannon
            {
                WhichPlant = 1;
            }
            else if (x == 550)//plant a shit
            {
                WhichPlant = 2;
            }
            else if (x == 650)//upgrade
            {
                WhichPlant = 3;
            }
            else if (x == 750)//delete
            {
                WhichPlant = 4;
            }
        }
    }
}

void Map_One::onMouseDown_Show_Yellow(Event* event)
{
    EventMouse* e = dynamic_cast<EventMouse*>(event);
    if (e->getMouseButton() == EventMouse::MouseButton::BUTTON_LEFT)
    {
        int x = e->getCursorX(), y = e->getCursorY();
        if (IsFrame_Lv1(x, y))
        {
            yellow_frame->Current->setVisible(true);
            yellow_frame->Spawn(x, y, 0.5f);
            yellow_frame->Shimmer();
            singleclick._x = x, singleclick._y = y; //保存黄色框位置，准备种植
            int vacancyIndex = CheckBox(singleclick, AllFrames_Lv1);

            //查询种植状态，如果是0（未种植）则进行后续操作
            if (vacancy[vacancyIndex].state == 0)
            {
                tower_cannon->Current->setVisible(false);//暗色cannon设为不可见
                tower_shit->Current->setVisible(false);//暗色shit设为不可见
                tower_cannon_ready->Current->setVisible(true);//亮色cannon设为可见
                tower_shit_ready->Current->setVisible(true);//亮色shit设为可见

                //开始检测鼠标点击位置，以判断种植哪种炮塔，一直等
                //问题：如果单次点击产生黄框后又点击了别的位置产生黄框，新种植的炮台仍然会种到之前的位置！
                waitForConditionAndExecute(
                    [=]() {
                        return WhichPlant == 1 || WhichPlant == 2;
                    },
                    [=]() {
                        if (WhichPlant == 1) //plant a cannon
                        {
                            //于目标点生成一级cannon
                            cannon_Lv1->Current = Sprite::create("cannon_Lv1.png");
                            this->addChild(cannon_Lv1->Current);
                            cannon_Lv1->Spawn(AllFrames_Lv1[vacancyIndex].adjusted._x, AllFrames_Lv1[vacancyIndex].adjusted._y, 1.0f);
                            vacancy[vacancyIndex].state = 1;      //state=1 放置了一级炮台
                            vacancy[vacancyIndex].tower_type = 1; //cannon
                            vacancy[vacancyIndex].spr = cannon_Lv1->Current; //当前指针存入vacancy中
                            WhichPlant = 0;
                        }
                        else if (WhichPlant == 2) //plant a shit
                        {
                            //于目标点生成一级shit
                            shit_Lv1->Current = Sprite::create("shit_Lv1.png");
                            this->addChild(shit_Lv1->Current);
                            shit_Lv1->Spawn(AllFrames_Lv1[vacancyIndex].adjusted._x, AllFrames_Lv1[vacancyIndex].adjusted._y, 1.0f);
                            vacancy[vacancyIndex].state = 1;      //state=1 放置了一级炮台
                            vacancy[vacancyIndex].tower_type = 2; //shit
                            vacancy[vacancyIndex].spr = shit_Lv1->Current; //当前指针存入vacancy中
                            WhichPlant = 0;
                        }
                    }
                );
            }
            else if (vacancy[vacancyIndex].state == 1) //state=1 放置了一级炮台
            {
                tower_cannon->Current->setVisible(true);//暗色cannon设为可见
                tower_shit->Current->setVisible(true);//暗色shit设为可见
                tower_cannon_ready->Current->setVisible(false);//亮色cannon设为不可见
                tower_shit_ready->Current->setVisible(false);//亮色shit设为不可见
                upgrade_ready->Current->setVisible(true);//亮色升级设为可见
                delete_ready->Current->setVisible(true);//亮色删除设为可见
                upgrade_grey->Current->setVisible(false);//暗色升级设为不可见
                delete_grey->Current->setVisible(false);//暗色删除设为不可见
                waitForConditionAndExecute(
                    [=]() {
                        return WhichPlant == 3 || WhichPlant == 4;
                    },
                    [=]() {
                        if (WhichPlant == 3) //upgrade
                        {
                            if (vacancy[vacancyIndex].tower_type == 1)//upgrade cannon
                            {
                                this->removeChild(vacancy[vacancyIndex].spr);
                                cannon_Lv2->Current = Sprite::create("cannon_Lv2.png");
                                this->addChild(cannon_Lv2->Current);
                                cannon_Lv2->Spawn(AllFrames_Lv1[vacancyIndex].adjusted._x, AllFrames_Lv1[vacancyIndex].adjusted._y, 1.0f);
                                vacancy[vacancyIndex].state = 2;      //state=2 放置了二级炮台
                                vacancy[vacancyIndex].tower_type = 1; //cannon
                                vacancy[vacancyIndex].spr = cannon_Lv2->Current; //当前指针存入vacancy中*/
                                WhichPlant = 0;
                            }
                            else if (vacancy[vacancyIndex].tower_type == 2)//upgrade shit
                            {
                                this->removeChild(vacancy[vacancyIndex].spr);
                                shit_Lv2->Current = Sprite::create("shit_Lv2.png");
                                this->addChild(shit_Lv2->Current);
                                shit_Lv2->Spawn(AllFrames_Lv1[vacancyIndex].adjusted._x, AllFrames_Lv1[vacancyIndex].adjusted._y, 1.0f);
                                vacancy[vacancyIndex].state = 2;      //state=2 放置了二级炮台
                                vacancy[vacancyIndex].tower_type = 2; //shit
                                vacancy[vacancyIndex].spr = shit_Lv2->Current; //当前指针存入vacancy中*/
                                WhichPlant = 0;
                            }
                        }
                        else if (WhichPlant == 4) //delete
                        {
                            if (vacancy[vacancyIndex].tower_type == 1)//delete cannon
                            {
                                this->removeChild(vacancy[vacancyIndex].spr);
                                vacancy[vacancyIndex].state = 0; //void
                                vacancy[vacancyIndex].tower_type = 0; //void
                                vacancy[vacancyIndex].spr = nullptr;
                                WhichPlant = 0;
                            }
                            else if (vacancy[vacancyIndex].tower_type == 2)//delete shit
                            {
                                this->removeChild(vacancy[vacancyIndex].spr);
                                vacancy[vacancyIndex].state = 0; //void
                                vacancy[vacancyIndex].tower_type = 0; //void
                                vacancy[vacancyIndex].spr = nullptr;
                                WhichPlant = 0;
                            }
                        }
                    }
                );
            }
            
            else if (vacancy[vacancyIndex].state == 2) //state=2 放置了二级炮台
            {
                tower_cannon->Current->setVisible(true);//暗色cannon设为可见
                tower_shit->Current->setVisible(true);//暗色shit设为可见
                tower_cannon_ready->Current->setVisible(false);//亮色cannon设为不可见
                tower_shit_ready->Current->setVisible(false);//亮色shit设为不可见
                upgrade_ready->Current->setVisible(true);//亮色升级设为可见
                delete_ready->Current->setVisible(true);//亮色删除设为可见
                upgrade_grey->Current->setVisible(false);//暗色升级设为不可见
                delete_grey->Current->setVisible(false);//暗色删除设为不可见
                waitForConditionAndExecute(
                    [=]() {
                        return WhichPlant == 3 || WhichPlant == 4;
                    },
                    [=]() {
                        if (WhichPlant == 3) //upgrade
                        {
                            if (vacancy[vacancyIndex].tower_type == 1)//upgrade cannon
                            {
                                this->removeChild(vacancy[vacancyIndex].spr);
                                cannon_Lv3->Current = Sprite::create("cannon_Lv3.png");
                                this->addChild(cannon_Lv3->Current);
                                cannon_Lv3->Spawn(AllFrames_Lv1[vacancyIndex].adjusted._x, AllFrames_Lv1[vacancyIndex].adjusted._y, 1.0f);
                                vacancy[vacancyIndex].state = 3;      //state=3 放置了三级炮台
                                vacancy[vacancyIndex].tower_type = 1; //cannon
                                vacancy[vacancyIndex].spr = cannon_Lv3->Current; //当前指针存入vacancy中
                                WhichPlant = 0;
                            }
                            else if (vacancy[vacancyIndex].tower_type == 2)//upgrade shit
                            {
                                this->removeChild(vacancy[vacancyIndex].spr);
                                shit_Lv3->Current = Sprite::create("shit_Lv3.png");
                                this->addChild(shit_Lv3->Current);
                                shit_Lv3->Spawn(AllFrames_Lv1[vacancyIndex].adjusted._x, AllFrames_Lv1[vacancyIndex].adjusted._y, 1.0f);
                                vacancy[vacancyIndex].state = 3;      //state=3 放置了三级炮台
                                vacancy[vacancyIndex].tower_type = 2; //shit
                                vacancy[vacancyIndex].spr = shit_Lv3->Current; //当前指针存入vacancy中
                                WhichPlant = 0;
                            }
                        }
                        else if (WhichPlant == 4) //delete
                        {
                            if (vacancy[vacancyIndex].tower_type == 1)//delete cannon
                            {
                                this->removeChild(vacancy[vacancyIndex].spr);
                                vacancy[vacancyIndex].state = 0; //void
                                vacancy[vacancyIndex].tower_type = 0; //void
                                vacancy[vacancyIndex].spr = nullptr;
                                WhichPlant = 0;
                            }
                            else if (vacancy[vacancyIndex].tower_type == 2)//delete shit
                            {
                                this->removeChild(vacancy[vacancyIndex].spr);
                                vacancy[vacancyIndex].state = 0; //void
                                vacancy[vacancyIndex].tower_type = 0; //void
                                vacancy[vacancyIndex].spr = nullptr;
                                WhichPlant = 0;
                            }
                        }
                    }
                    );
            }
            else if (vacancy[vacancyIndex].state == 3)  //state=3 放置了三级炮台
            {
                tower_cannon->Current->setVisible(true);//暗色cannon设为可见
                tower_shit->Current->setVisible(true);//暗色shit设为可见
                tower_cannon_ready->Current->setVisible(false);//亮色cannon设为不可见
                tower_shit_ready->Current->setVisible(false);//亮色shit设为不可见
                upgrade_ready->Current->setVisible(false);//亮色升级设为不可见！！
                delete_ready->Current->setVisible(true);//亮色删除设为可见
                upgrade_grey->Current->setVisible(true);//暗色升级设为可见
                delete_grey->Current->setVisible(false);//暗色删除设为不可见
                waitForConditionAndExecute(
                    [=]() {
                        return WhichPlant == 4;
                    },
                    [=]() {
                        if (WhichPlant == 4) {
                            if (vacancy[vacancyIndex].tower_type == 1)//delete cannon
                            {
                                this->removeChild(vacancy[vacancyIndex].spr);
                                vacancy[vacancyIndex].state = 0; //void
                                vacancy[vacancyIndex].tower_type = 0; //void
                                vacancy[vacancyIndex].spr = nullptr;
                                WhichPlant = 0;
                            }
                            else if (vacancy[vacancyIndex].tower_type == 2)//delete shit
                            {
                                this->removeChild(vacancy[vacancyIndex].spr);
                                vacancy[vacancyIndex].state = 0; //void
                                vacancy[vacancyIndex].tower_type = 0; //void
                                vacancy[vacancyIndex].spr = nullptr;
                                WhichPlant = 0;
                            }
                        }
                    }
                );
            }
        }
        else
        {
            yellow_frame->Current->setVisible(false);//grey cannon visible
            tower_cannon->Current->setVisible(true);//grey shit visible
            tower_shit->Current->setVisible(true);//colored cannon invisible
            tower_cannon_ready->Current->setVisible(false);//colored shit invisible
            tower_shit_ready->Current->setVisible(false);//colored upgrade invisible
            upgrade_ready->Current->setVisible(false);//colored delete invisible
            delete_ready->Current->setVisible(false);//grey update visible
            upgrade_grey->Current->setVisible(true);//grey delete visible
            delete_grey->Current->setVisible(true);
        }
    }
}

void Map_One::waitForConditionAndExecute(const std::function<bool()>& condition, const std::function<void()>& callback)
{
    if (condition())
    {
        callback();
    }
    else
    {
        scheduleOnce([=](float dt)
            {
                waitForConditionAndExecute(condition, callback);
            }, 0.1f, "waitForConditionTag");
    }
}

void Map_One::ShowTowerDark()
{
    //暗色炮台——初状态可见
    //暗色cannon
    tower_cannon->Current = Sprite::create("TI_1_unavailable.png");
    this->addChild(tower_cannon->Current); //z-value=0
    tower_cannon->Spawn(450, 600, 1.0f);
    tower_cannon->Current->setVisible(true);
    //暗色shit
    tower_shit->Current = Sprite::create("TI_2_unavailable.png");
    this->addChild(tower_shit->Current); //z-value=0
    tower_shit->Spawn(550, 600, 1.0f);
    tower_shit->Current->setVisible(true);
    //暗色升级——注意升级.png需要缩放至×0.7
    upgrade_grey->Current = Sprite::create("upgrade_grey.png");
    this->addChild(upgrade_grey->Current); //z-value=0
    upgrade_grey->Spawn(650, 600, 0.7f);
    upgrade_grey->Current->setVisible(true);
    //暗色移除——注意移除.png需要缩放至×0.7
    delete_grey->Current = Sprite::create("delete_grey.png");
    this->addChild(delete_grey->Current); //z-value=0
    delete_grey->Spawn(750, 600, 0.7f);
    delete_grey->Current->setVisible(true);


    //亮色炮台——初状态不可见
    //亮色cannon
    tower_cannon_ready->Current = Sprite::create("TI_1_available.png");
    this->addChild(tower_cannon_ready->Current); //z-value=0
    tower_cannon_ready->Spawn(450, 600, 1.0f);
    tower_cannon_ready->Current->setVisible(false);
    //亮色shit
    tower_shit_ready->Current = Sprite::create("TI_2_available.png");
    this->addChild(tower_shit_ready->Current); //z-value=0
    tower_shit_ready->Spawn(550, 600, 1.0f);
    tower_shit_ready->Current->setVisible(false);
    //亮色升级
    upgrade_ready->Current = Sprite::create("upgrade_ready.png");
    this->addChild(upgrade_ready->Current); //z-value=0
    upgrade_ready->Spawn(650, 600, 0.7f);
    upgrade_ready->Current->setVisible(false);
    //亮色移除
    delete_ready->Current = Sprite::create("delete_ready.png");
    this->addChild(delete_ready->Current); //z-value=0
    delete_ready->Spawn(750, 600, 0.7f);
    delete_ready->Current->setVisible(false);
}


/*****************************change*************************************/

void Map_One::input_background()//放置背景图
{
    auto background = Sprite::create("map\\map_one.png");
    this->addChild(background);
    background->setPosition(background_wide / 2, background_high / 2);//背景图
}

void Map_One::input_walk_way()//放置怪物行进路径
{
    std::vector<float> current = walk_way_begin_1;
    walk_way_store_1.push_back(current);//放好初始位置
    input_brick(current[0], current[1], 1);
    for (int i = 0; i < 5; i++)
    {
        current[1] -= way_size;
        input_brick(current[0], current[1], 1);
        walk_way_store_1.push_back(current);
    }//竖直向下5格

    for (int i = 0; i < 9; i++)
    {
        current[0] += way_size;
        input_brick(current[0], current[1], 1);
        walk_way_store_1.push_back(current);
    }//水平向右9格

    for (int i = 0; i < 5; i++)
    {
        current[1] += way_size;
        input_brick(current[0], current[1], 1);
        walk_way_store_1.push_back(current);
    }//竖直向上5格
    //存放地板向量生成完毕
    /*****************************change*************************************/
    ShowTowerDark();
    input_listener();
    /*****************************change*************************************/

    return;
}




void Map_One::game_begin()//游戏开始函数
{
    float carrot_x = walk_way_store_1[walk_way_store_1.size() - 1][0];
    float carrot_y = walk_way_store_1[walk_way_store_1.size() - 1][1];//萝卜坐标
    auto carrot = Carrot::create("carrot_level1_1.png");//萝卜精灵变量
    this->addChild(carrot);
    carrot->setPosition(carrot_x, carrot_y);
    //放置萝卜
    auto carrot_HP = HP_display(carrot_x+120, carrot_y );//生成萝卜血量
    carrot_HP->setString(calculate_HP(carrot->HP));//根据当前血量更新字体，（注：增加、消耗血量时，记得用这个语句更新面板）


    static int gold = gold_1;//金币变量
    auto gold_label = input_gold();;//生成标签
    gold_label->setString(calculate_gold(gold));//更新字体，（注：增加、消耗金币时，记得用这个语句更新面板）

    //以下为调试
    /**********************12.23 新增**************************/
    carrot->HP = 10;
    carrot->level = 1;
    /**********************12.23 新增**************************/
    carrot->change();
    carrot_HP->setString(calculate_HP(carrot->HP));//根据当前血量更新字体，（注：增加、消耗血量时，记得用这个语句更新面板）
    
    
    /**********************12.23 新增**************************/
    Node* wave1 = cocos2d::Node::create();
    this->addChild(wave1);
    MonSprite* monster1 = MonSprite::create(1);
    wave1->addChild(monster1);
    monster1->monster_spawn(walk_way_store_1);
    carrot->HP -= monster1->monster_attack_carrot(carrot->getBoundingBox(), wave1);

    if (carrot->if_dead())  //萝卜死亡结束
        this->scheduleOnce(CC_SCHEDULE_SELECTOR(Map_father::game_over_failure), 1.0f);

    map_two_flag = true;
    /**********************12.23 新增**************************/

}

/*------------------------------地图一函数----------------------------------*/


/*------------------------------地图二函数----------------------------------*/

void Map_Two::input_background()//放置背景图
{
    auto background = Sprite::create("map\\map_two.png");
    this->addChild(background);
    background->setPosition(background_wide / 2, background_high / 2);//背景图
}

void Map_Two::input_walk_way()//放置怪物路径
{
    std::vector<float> current = walk_way_begin_2;
    walk_way_store_2.push_back(current);//放好初始位置
    input_brick(current[0], current[1], 1);
    for (int i = 0; i < 4; i++)
    {
        current[0] += way_size;
        input_brick(current[0], current[1], 1);
        walk_way_store_2.push_back(current);
    }//水平向右4格

    for (int i = 0; i < 5; i++)
    {
        current[1] += way_size;
        input_brick(current[0], current[1], 1);
        walk_way_store_2.push_back(current);
    }//竖直向上5格

    for (int i = 0; i < 3; i++)
    {
        current[0] += way_size;
        input_brick(current[0], current[1], 1);
        walk_way_store_2.push_back(current);
    }//水平向右3格

    for (int i = 0; i < 5; i++)
    {
        current[1] -= way_size;
        input_brick(current[0], current[1], 1);
        walk_way_store_2.push_back(current);
    }//竖直向下5格

    for (int i = 0; i < 4; i++)
    {
        current[0] += way_size;
        input_brick(current[0], current[1], 1);
        walk_way_store_2.push_back(current);
    }//水平向右4格
     //存放地板向量生成完毕
    return;

}

void Map_Two::game_begin()//游戏开始函数
{
    float carrot_x = walk_way_store_2[walk_way_store_2.size() - 1][0];
    float carrot_y = walk_way_store_2[walk_way_store_2.size() - 1][1];//萝卜坐标
    auto carrot = Carrot::create("carrot_level1_1.png");//萝卜精灵变量
    this->addChild(carrot);
    carrot->setPosition(carrot_x, carrot_y);
    //放置萝卜
    auto carrot_HP = HP_display(carrot_x + 120, carrot_y);//生成萝卜血量
    carrot_HP->setString(calculate_HP(carrot->HP));//根据当前血量更新字体，（注：增加、消耗血量时，记得用这个语句更新面板）


    static int gold = gold_2;//金币变量
    auto gold_label = input_gold();;//生成标签
    gold_label->setString(calculate_gold(gold));//更新字体，（注：增加、消耗金币时，记得用这个语句更新面板）

    map_three_flag = true;
}


/*------------------------------地图二函数----------------------------------*/


/*------------------------------地图三函数----------------------------------*/
void Map_Three::input_background()//生成背景图
{
    auto background = Sprite::create("map\\map_three.png");
    this->addChild(background);
    background->setPosition(background_wide / 2, background_high / 2);//背景图
}

void Map_Three::input_walk_way()//放置怪物路径
{
    std::vector<float> current = walk_way_begin_3;
    walk_way_store_3.push_back(current);//放好初始位置
    input_brick(current[0], current[1], 1);
    for (int i = 0; i < 9; i++)
    {
        current[0] += way_size;
        input_brick(current[0], current[1], 1);
        walk_way_store_3.push_back(current);//放好初始位置
    }//向右9格
    for (int i = 0; i < 3; i++)
    {
        current[1] -= way_size;
        input_brick(current[0], current[1], 1);
        walk_way_store_3.push_back(current);//放好初始位置
    }//向下3格
    for (int i = 0; i < 9; i++)
    {
        current[0] -= way_size;
        input_brick(current[0], current[1], 1);
        walk_way_store_3.push_back(current);//放好初始位置
    }//向左9格
    for (int i = 0; i < 3; i++)
    {
        current[1] -= way_size;
        input_brick(current[0], current[1], 1);
        walk_way_store_3.push_back(current);//放好初始位置
    }//向下3格
    for (int i = 0; i < 9; i++)
    {
        current[0] += way_size;
        input_brick(current[0], current[1], 1);
        walk_way_store_3.push_back(current);//放好初始位置
    }//向右9格
    //存放地板向量生成完毕
    return;
}

void Map_Three::game_begin()//游戏开始函数
{
    float carrot_x = walk_way_store_3[walk_way_store_3.size() - 1][0];
    float carrot_y = walk_way_store_3[walk_way_store_3.size() - 1][1];//萝卜坐标
    auto carrot = Carrot::create("carrot_level1_1.png");//萝卜精灵变量
    this->addChild(carrot);
    carrot->setPosition(carrot_x, carrot_y);
    //放置萝卜
    auto carrot_HP = HP_display(carrot_x + 120, carrot_y);//生成萝卜血量
    carrot_HP->setString(calculate_HP(carrot->HP));//根据当前血量更新字体，（注：增加、消耗血量时，记得用这个语句更新面板）


    static int gold = gold_3;//金币变量
    auto gold_label = input_gold();;//生成标签
    gold_label->setString(calculate_gold(gold));//更新字体，（注：增加、消耗金币时，记得用这个语句更新面板）
}

/*------------------------------地图三函数----------------------------------*/


/*************************************************************
    CheckBox函数：已知对应方块的中心点坐标，查询其代号
*************************************************************/
int CheckBox(XY obj, const std::vector<FS>& table)
{
    for (auto& it : table)
    {
        if (it.adjusted._x == obj._x && it.adjusted._y == obj._y)
            return it.index;
    }
    return -1;
}
