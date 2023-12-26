#include "map.h"
#include "choose_map.h"
#include "settlement_interface.h"
USING_NS_CC;

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

void Map_father::waitForConditionAndExecute(const std::function<bool()>& condition, const std::function<void()>& callback)
{
    if (condition())
        callback();
    else
    {
        scheduleOnce([=](float dt)
            {
                waitForConditionAndExecute(condition, callback);
            }, 0.1f, "waitForConditionTag");
    }
}

void Map_father::spawnMonster1_1(float dt) 
{
    MonSprite* monster = MonSprite::create(1);
    monster->monster_spawn(walk_way);
    this->addChild(monster);
    monster_wave.push_back(monster);
    monster->monster_attack_carrot(carrot, monster_wave);

}

void Map_father::spawnMonster1_2(float dt)
{
    MonSprite* monster = MonSprite::create(1);
    monster->monster_spawn(walk_way);
    this->addChild(monster);
    monster_wave.push_back(monster);
    monster->monster_attack_carrot(carrot, monster_wave);
}

void Map_father::spawnMonster1_3(float dt)
{
    MonSprite* monster = MonSprite::create(1);
    monster->monster_spawn(walk_way);
    this->addChild(monster);
    monster_wave.push_back(monster);
    monster->monster_attack_carrot(carrot, monster_wave);
}

void Map_father::spawnMonster2_1(float dt)
{
    MonSprite* monster = MonSprite::create(2);
    monster->monster_spawn(walk_way);
    this->addChild(monster);
    monster_wave.push_back(monster);
    monster->monster_attack_carrot(carrot, monster_wave);

}

void Map_father::spawnMonster2_2(float dt)
{
    MonSprite* monster = MonSprite::create(2);
    monster->monster_spawn(walk_way);
    this->addChild(monster);
    monster_wave.push_back(monster);
    monster->monster_attack_carrot(carrot, monster_wave);
}

void Map_father::spawnMonster2_3(float dt)
{
    MonSprite* monster = MonSprite::create(2);
    monster->monster_spawn(walk_way);
    this->addChild(monster);
    monster_wave.push_back(monster);
    monster->monster_attack_carrot(carrot, monster_wave);
}

void Map_father::spawnMonster3_1(float dt)
{
    MonSprite* monster = MonSprite::create(3);
    monster->monster_spawn(walk_way);
    this->addChild(monster);
    monster_wave.push_back(monster);
    monster->monster_attack_carrot(carrot, monster_wave);

}

void Map_father::spawnMonster3_2(float dt)
{
    MonSprite* monster = MonSprite::create(3);
    monster->monster_spawn(walk_way);
    this->addChild(monster);
    monster_wave.push_back(monster);
    monster->monster_attack_carrot(carrot, monster_wave);
}

void Map_father::spawnMonster3_3(float dt)
{
    MonSprite* monster = MonSprite::create(3);
    monster->monster_spawn(walk_way);
    this->addChild(monster);
    monster_wave.push_back(monster);
    monster->monster_attack_carrot(carrot, monster_wave);
}

void Map_father::spawnMonster4_1(float dt)
{
    MonSprite* monster = MonSprite::create(4);
    monster->monster_spawn(walk_way);
    this->addChild(monster);
    monster_wave.push_back(monster);
    monster->monster_attack_carrot(carrot, monster_wave);

}

void Map_father::spawnMonster4_2(float dt)
{
    MonSprite* monster = MonSprite::create(4);
    monster->monster_spawn(walk_way);
    this->addChild(monster);
    monster_wave.push_back(monster);
    monster->monster_attack_carrot(carrot, monster_wave);
}

void Map_father::spawnMonster4_3(float dt)
{
    MonSprite* monster = MonSprite::create(4);
    monster->monster_spawn(walk_way);
    this->addChild(monster);
    monster_wave.push_back(monster);
    monster->monster_attack_carrot(carrot, monster_wave);
}

bool Map_father::init()//父类创建场景总函数
{
    if (!Scene::init())
        return false;

    auto visibleSize = Director::getInstance()->getVisibleSize();//获取可见大小
    Vec2 origin = Director::getInstance()->getVisibleOrigin();//获取opengl起点
    
    vacancy.clear();
    for (int i = 0; i <= 37; i++)
        vacancy.push_back({ i,0,0,nullptr });

    input_background();//放置背景图
    input_walk_way();//放置地板
    input_return_pause();//放置返回，暂停键
    input_gold_item();//放置金币
    input_carrot_level_button();//放置萝卜升级按钮
    ShowPlantButton();
    input_listener();
    //StartAttack();
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

void Map_father::input_carrot_level_button()//放置萝卜升级按钮
{
    carrot_level_button = ui::Button::create("carrot_level_up.png", "carrot_level_up_selected.png", "carrot_level_up_disabled.png");
    carrot_level_button->setPosition(Point(carrot_level_x, carrot_level_y));
    this->addChild(carrot_level_button);
    carrot_level_button->addClickEventListener(CC_CALLBACK_1(Map_father::carrot_level_button_call_back, this));
}

void Map_father::carrot_level_button_call_back(cocos2d::Ref* pSender)//萝卜升级按钮触发
{
    if (carrot->level == 1)
        gold -= carrot_level2_cost;
    if (carrot->level == 2)
        gold -= carrot_level3_cost;
    gold_label->setString(calculate_gold(gold));//更新字体，（注：增加、消耗金币时，记得用这个语句更新面板）
    carrot->level++;
    carrot->HP += 10;//萝卜属性更新
    carrot->change_tex();//萝卜外貌更新
    carrot->HP_Label->setString(carrot->calculate_HP(carrot->HP));//萝卜血条更新
}

void Map_father::change_carrot_level_button(float dt)//检测萝卜是否可以升级
{
    carrot_level_button->setTouchEnabled(true);
    carrot_level_button->setBright(true);//先设置可点击
    if (carrot->level == 3)
    {
        carrot_level_button->setTouchEnabled(false);
        carrot_level_button->setBright(false);
    }
    else
    {
        if (carrot->level == 1 && gold < carrot_level2_cost)
        {
            carrot_level_button->setTouchEnabled(false);
            carrot_level_button->setBright(false);
        }
        if (carrot->level == 2 && gold < carrot_level3_cost)
        {
            carrot_level_button->setTouchEnabled(false);
            carrot_level_button->setBright(false);
        }
    }//对不可点击情况进行分析
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

std::string Map_father::calculate_gold(const int gold)
{
    int digit = 1000;//千位
    std::string figure;
    for (int i = 0; i < 4; i++)
    {
        int k = (gold / digit) % 10;
        digit /= 10;
        figure.push_back(k + '0');
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
void Map_One::input_listener()
{
    auto mouseListener = EventListenerMouse::create();
    mouseListener->onMouseDown = CC_CALLBACK_1(Map_One::onMouseDown_Do_Plant, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(mouseListener, this);
    mouse_select_type = 0;
    yellow_frame = FrameBox::create("yellow_frame.png");
    this->addChild(yellow_frame); //z-value=0
    yellow_frame->setVisible(false);
}

void Map_One::onMouseDown_Do_Plant(Event* event)
{
    EventMouse* e = dynamic_cast<EventMouse*>(event);
    if (e->getMouseButton() == EventMouse::MouseButton::BUTTON_LEFT)
    {
        float x = e->getCursorX(), y = e->getCursorY();
        if (IsFramePlant(x, y, AllPlants_Lv1) && mouse_select_type)//选中种植功能
        {
            //plant a cannon
            if (x <= 450.1 && x >= 449.9 && vacancy[vacancyIndex].level == 0 && gold >= cannon_build_cost)
            {
                //于目标点生成一级cannon
                cannon = FrameBox::create("cannon_Lv1.png");
                this->addChild(cannon);
                cannon->Spawn(AllFrames_Lv1[vacancyIndex].adjusted._x, AllFrames_Lv1[vacancyIndex].adjusted._y, 1.0f);
                vacancy[vacancyIndex].level++;
                vacancy[vacancyIndex].tower_type = type_cannon;
                vacancy[vacancyIndex].spr = cannon; //当前指针存入vacancy中
                gold -= cannon_build_cost;
                upgrade_frame->setTexture("upgrade_ready.png");//升级按钮有效
                delete_frame->setTexture("delete_ready.png");//删除按钮有效
            }
            //plant a shit
            else if (x <= 550.1 && x >= 549.9 && vacancy[vacancyIndex].level == 0 && gold >= shit_build_cost)
            {
                //于目标点生成一级shit
                shit = FrameBox::create("shit_Lv1.png");
                this->addChild(shit);
                shit->Spawn(AllFrames_Lv1[vacancyIndex].adjusted._x, AllFrames_Lv1[vacancyIndex].adjusted._y, 1.0f);
                vacancy[vacancyIndex].level++;
                vacancy[vacancyIndex].tower_type = type_shit;
                vacancy[vacancyIndex].spr = shit; //当前指针存入vacancy中
                gold -= shit_build_cost;
                upgrade_frame->setTexture("upgrade_ready.png");//升级按钮有效
                delete_frame->setTexture("delete_ready.png");//删除按钮有效
            }
            //upgrade
            else if (x <= 650.1 && x >= 649.9)
            {
                //1级升2级
                if (vacancy[vacancyIndex].level == 1)
                {
                    if (vacancy[vacancyIndex].tower_type == type_cannon && gold >= cannon_upgrade_1to2)//upgrade cannon
                    {
                        cannon->setTexture("cannon_Lv2.png");
                        vacancy[vacancyIndex].level++;
                        gold -= cannon_upgrade_1to2;
                    }
                    else if (vacancy[vacancyIndex].tower_type == type_shit && gold >= shit_upgrade_1to2)//upgrade shit
                    {
                        shit->setTexture("shit_Lv2.png");
                        vacancy[vacancyIndex].level++;
                        gold -= shit_upgrade_1to2;
                    }
                }
                //2级升3级
                else if (vacancy[vacancyIndex].level == 2)
                {
                    if (vacancy[vacancyIndex].tower_type == type_cannon && gold >= cannon_upgrade_2to3)//upgrade cannon
                    {
                        cannon->setTexture("cannon_Lv3.png");
                        vacancy[vacancyIndex].level++;
                        gold -= cannon_upgrade_2to3;
                    }
                    else if (vacancy[vacancyIndex].tower_type == type_shit && gold >= shit_upgrade_2to3)//upgrade shit
                    {
                        shit->setTexture("shit_Lv3.png");
                        vacancy[vacancyIndex].level++;
                        gold -= shit_upgrade_2to3;
                    }
                }
            }
            //delete
            else if (x <= 750.1 && x >= 749.9 && vacancy[vacancyIndex].level)
            {
                this->removeChild(vacancy[vacancyIndex].spr);
                vacancy[vacancyIndex].level = 0;
                vacancy[vacancyIndex].tower_type = 0;
                vacancy[vacancyIndex].spr = nullptr;
                gold += delete_recover;
            }
            
            gold_label->setString(calculate_gold(gold));//更新金币
        }
        else if (IsFrame(x, y, AllFrames_Lv1))//选中空地
        {
            mouse_select_type = 1;
            yellow_frame->setVisible(true);
            yellow_frame->Spawn(x, y, 0.5f);
            yellow_frame->Shimmer();
            singleclick._x = x, singleclick._y = y; //保存黄色框位置，准备种植
            vacancyIndex = CheckBox(singleclick, AllFrames_Lv1);
            //查询选中位置种植状态
            switch (vacancy[vacancyIndex].level)
            {
                case 0://未种植
                    upgrade_frame->setTexture("upgrade_grey.png");//升级按钮无效
                    delete_frame->setTexture("delete_grey.png");//删除按钮无效
                    if (gold >= cannon_build_cost)
                        plant_cannon->setTexture("plant_cannon_available.png");//种植cannon按钮有效
                    if (gold >= shit_build_cost)
                        plant_shit->setTexture("plant_shit_available.png");//种植shit按钮有效
                    break;
                case 1://种植了1级炮台
                    plant_cannon->setTexture("plant_cannon_unavailable.png");//种植cannon按钮失效
                    plant_shit->setTexture("plant_shit_unavailable.png");//种植shit按钮失效
                    delete_frame->setTexture("delete_ready.png");//删除按钮有效
                    if (vacancy[vacancyIndex].tower_type == type_cannon && gold >= cannon_upgrade_1to2)
                        upgrade_frame->setTexture("upgrade_ready.png");//升级按钮有效
                    if (vacancy[vacancyIndex].tower_type == type_shit && gold >= shit_upgrade_1to2)
                        upgrade_frame->setTexture("upgrade_ready.png");//升级按钮有效
                    break;
                case 2:
                    plant_cannon->setTexture("plant_cannon_unavailable.png");//种植cannon按钮失效
                    plant_shit->setTexture("plant_shit_unavailable.png");//种植shit按钮失效
                    delete_frame->setTexture("delete_ready.png");//删除按钮有效
                    if ((vacancy[vacancyIndex].tower_type == type_cannon && gold >= cannon_upgrade_2to3) || (vacancy[vacancyIndex].tower_type == type_shit && gold >= shit_upgrade_2to3))
                        upgrade_frame->setTexture("upgrade_ready.png");//升级按钮有效
                    break;
                case 3:
                    plant_cannon->setTexture("plant_cannon_unavailable.png");//种植cannon按钮失效
                    plant_shit->setTexture("plant_shit_unavailable.png");//种植shit按钮失效
                    delete_frame->setTexture("delete_ready.png");//删除按钮有效
                    break;
            }
        }
        else
        {
            mouse_select_type = 0;
            yellow_frame->setVisible(false);
            plant_cannon->setTexture("plant_cannon_unavailable.png");
            plant_shit->setTexture("plant_shit_unavailable.png");
            upgrade_frame->setTexture("upgrade_grey.png");
            delete_frame->setTexture("delete_grey.png");
        }
    }
}

void Map_One::ShowPlantButton()
{
    //暗色cannon
    plant_cannon = FrameBox::create("plant_cannon_unavailable.png");
    this->addChild(plant_cannon); //z-value=0
    plant_cannon->Spawn(450, 600, 1.0f);
    //暗色shit
    plant_shit = FrameBox::create("plant_shit_unavailable.png");
    this->addChild(plant_shit); //z-value=0
    plant_shit->Spawn(550, 600, 1.0f);
    //暗色升级——注意升级.png需要缩放至×0.7
    upgrade_frame = FrameBox::create("upgrade_grey.png");
    this->addChild(upgrade_frame); //z-value=0
    upgrade_frame->Spawn(650, 600, 0.7f);
    //暗色移除——注意移除.png需要缩放至×0.7
    delete_frame = FrameBox::create("delete_grey.png");
    this->addChild(delete_frame); //z-value=0
    delete_frame->Spawn(750, 600, 0.7f);
}

void Map_One::input_background()//放置背景图
{
    auto background = Sprite::create("map\\map_one.png");
    this->addChild(background);
    background->setPosition(background_wide / 2, background_high / 2);//背景图
}

void Map_One::input_walk_way()//放置怪物行进路径
{
    std::vector<float> current = walk_way_begin_1;
    walk_way.push_back(current);//放好初始位置
    input_brick(current[0], current[1], 1);
    for (int i = 0; i < 5; i++)
    {
        current[1] -= way_size;
        input_brick(current[0], current[1], 1);
        walk_way.push_back(current);
    }//竖直向下5格

    for (int i = 0; i < 9; i++)
    {
        current[0] += way_size;
        input_brick(current[0], current[1], 1);
        walk_way.push_back(current);
    }//水平向右9格

    for (int i = 0; i < 5; i++)
    {
        current[1] += way_size;
        input_brick(current[0], current[1], 1);
        walk_way.push_back(current);
    }//竖直向上5格
    //存放地板向量生成完毕
    return;
}

void Map_One::game_begin()//游戏开始函数
{
    float carrot_x = walk_way[walk_way.size() - 1][0];
    float carrot_y = walk_way[walk_way.size() - 1][1];//萝卜坐标
    carrot = Carrot::create("carrot_level1_1.png");//萝卜精灵变量
    carrot->setPosition(carrot_x, carrot_y);
    //放置萝卜
    carrot->HP = 10;
    carrot->level = 1;
    carrot->change_tex();
    carrot->HP_Label->setString(carrot->calculate_HP(carrot->HP));//根据当前血量更新字体，（注：增加、消耗血量时，记得用这个语句更新面板）
    this->addChild(carrot);

    gold = gold_1;
    gold_label = input_gold();//初始化金币标签
    gold_label->setString(calculate_gold(gold));//更新字体，（注：增加、消耗金币时，记得用这个语句更新面板）


    schedule(CC_SCHEDULE_SELECTOR(Map_father::spawnMonster1_1), 1.0f, 2, 3.0f); //第1波：生成3个怪物1
    schedule(CC_SCHEDULE_SELECTOR(Map_father::spawnMonster1_2), 1.0f, 4, 13.0f);//第2波：生成5个怪物1
    schedule(CC_SCHEDULE_SELECTOR(Map_father::spawnMonster1_3), 1.0f, 5, 23.0f);//第3波：生成6个怪物1

    waitForConditionAndExecute(
        [=](){return (carrot->HP <= 0);},
        [=](){this->scheduleOnce(CC_SCHEDULE_SELECTOR(Map_father::game_over_failure), 1.0f);}
        );


    schedule(CC_SCHEDULE_SELECTOR(Map_father::change_carrot_level_button), 0.1f);//测试，检测萝卜能否升级



    map_two_flag = true;

}


/*------------------------------地图一函数----------------------------------*/


/*------------------------------地图二函数----------------------------------*/

void Map_Two::input_listener()
{
    auto mouseListener = EventListenerMouse::create();
    mouseListener->onMouseDown = CC_CALLBACK_1(Map_Two::onMouseDown_Do_Plant, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(mouseListener, this);

    yellow_frame = FrameBox::create("yellow_frame.png");
    this->addChild(yellow_frame); //z-value=0
    yellow_frame->setVisible(false);
}

void Map_Two::ShowPlantButton()
{
    //暗色cannon
    plant_cannon = FrameBox::create("plant_cannon_unavailable.png");
    this->addChild(plant_cannon); //z-value=0
    plant_cannon->Spawn(60.0f, 550.0f, 1.0f);
    plant_cannon->setTexture("plant_cannon_unavailable.png");
    //暗色etower
    plant_etower = FrameBox::create("plant_etower_unavailable.png");
    this->addChild(plant_etower); //z-value=0
    plant_etower->Spawn(60.0f, 450.0f, 1.0f);
    plant_etower->setTexture("plant_etower_unavailable.png");
    //暗色升级——注意升级.png需要缩放至×0.7
    upgrade_frame = FrameBox::create("upgrade_grey.png");
    this->addChild(upgrade_frame); //z-value=0
    upgrade_frame->Spawn(60.0f, 350.0f, 0.7f);
    upgrade_frame->setTexture("upgrade_grey.png");
    //暗色移除——注意移除.png需要缩放至×0.7
    delete_frame = FrameBox::create("delete_grey.png");
    this->addChild(delete_frame); //z-value=0
    delete_frame->Spawn(60.0f, 250.0f, 0.7f);
    delete_frame->setTexture("delete_grey.png");
}

void Map_Two::onMouseDown_Do_Plant(Event* event)
{
    EventMouse* e = dynamic_cast<EventMouse*>(event);
    if (e->getMouseButton() == EventMouse::MouseButton::BUTTON_LEFT)
    {
        float x = e->getCursorX(), y = e->getCursorY();
        if (IsFramePlant(x, y, AllPlants_Lv2) && mouse_select_type)//选中种植功能
        {
            //plant a cannon
            if (y <= 550.1 && y >= 549.9 && vacancy[vacancyIndex].level == 0 && gold >= cannon_build_cost)
            {
                //于目标点生成一级cannon
                cannon = FrameBox::create("cannon_Lv1.png");
                this->addChild(cannon);
                cannon->Spawn(AllFrames_Lv2[vacancyIndex].adjusted._x, AllFrames_Lv2[vacancyIndex].adjusted._y, 1.0f);
                vacancy[vacancyIndex].level++;
                vacancy[vacancyIndex].tower_type = type_cannon;
                vacancy[vacancyIndex].spr = cannon; //当前指针存入vacancy中
                gold -= cannon_build_cost;
            }
            //plant a etower
            else if (y <= 450.1 && y >= 449.9 && vacancy[vacancyIndex].level == 0 && gold >= etower_build_cost)
            {
                //于目标点生成一级etower
                etower = FrameBox::create("etower_Lv1.png");
                this->addChild(etower);
                etower->Spawn(AllFrames_Lv2[vacancyIndex].adjusted._x, AllFrames_Lv2[vacancyIndex].adjusted._y, 1.0f);
                vacancy[vacancyIndex].level++;
                vacancy[vacancyIndex].tower_type = type_etower;
                vacancy[vacancyIndex].spr = etower; //当前指针存入vacancy中
                gold -= etower_build_cost;
            }
            //upgrade
            else if (y <= 350.1 && y >= 349.9)
            {
                //1级升2级
                if (vacancy[vacancyIndex].level == 1)
                {
                    if (vacancy[vacancyIndex].tower_type == type_cannon && gold >= cannon_upgrade_1to2)//upgrade cannon
                    {
                        cannon->setTexture("cannon_Lv2.png");
                        vacancy[vacancyIndex].level++;
                        gold -= cannon_upgrade_1to2;
                    }
                    else if (vacancy[vacancyIndex].tower_type == type_etower && gold >= etower_upgrade_1to2)//upgrade etower
                    {
                        etower->setTexture("etower_Lv2.png");
                        vacancy[vacancyIndex].level++;
                        gold -= etower_upgrade_1to2;
                    }
                }
                //2级升3级
                else if (vacancy[vacancyIndex].level == 2)
                {
                    if (vacancy[vacancyIndex].tower_type == type_cannon && gold >= cannon_upgrade_2to3)//upgrade cannon
                    {
                        cannon->setTexture("cannon_Lv3.png");
                        vacancy[vacancyIndex].level++;
                        gold -= cannon_upgrade_2to3;
                    }
                    else if (vacancy[vacancyIndex].tower_type == type_etower && gold >= etower_upgrade_2to3)//upgrade etower
                    {
                        etower->setTexture("etower_Lv3.png");
                        vacancy[vacancyIndex].level++;
                        gold -= etower_upgrade_2to3;
                    }
                }
            }
            //delete
            else if (y <= 250.1 && y >= 249.9 && vacancy[vacancyIndex].level)
            {
                this->removeChild(vacancy[vacancyIndex].spr);
                vacancy[vacancyIndex].level = 0;
                vacancy[vacancyIndex].tower_type = 0;
                vacancy[vacancyIndex].spr = nullptr;
                gold += delete_recover;
            }

            gold_label->setString(calculate_gold(gold));//更新金币
        }
        else if (IsFrame(x, y, AllFrames_Lv2))//选中空地
        {
            mouse_select_type = 1;
            yellow_frame->setVisible(true);
            yellow_frame->Spawn(x, y, 0.5f);
            yellow_frame->Shimmer();
            singleclick._x = x, singleclick._y = y; //保存黄色框位置，准备种植
            vacancyIndex = CheckBox(singleclick, AllFrames_Lv2);

            //查询选中位置种植状态
            switch (vacancy[vacancyIndex].level)
            {
                case 0://未种植
                    upgrade_frame->setTexture("upgrade_grey.png");//升级按钮无效
                    delete_frame->setTexture("delete_grey.png");//删除按钮无效
                    if (gold >= cannon_build_cost)
                        plant_cannon->setTexture("plant_cannon_available.png");//种植cannon按钮有效
                    if (gold >= etower_build_cost)
                        plant_etower->setTexture("plant_etower_available.png");//种植etower按钮有效
                    break;
                case 1://种植了1级炮台
                    plant_cannon->setTexture("plant_cannon_unavailable.png");//种植cannon按钮失效
                    plant_etower->setTexture("plant_etower_unavailable.png");//种植etower按钮失效
                    delete_frame->setTexture("delete_ready.png");//删除按钮有效
                    if (vacancy[vacancyIndex].tower_type == type_cannon && gold >= cannon_upgrade_1to2)
                        upgrade_frame->setTexture("upgrade_ready.png");//升级按钮有效
                    if (vacancy[vacancyIndex].tower_type == type_etower && gold >= etower_upgrade_1to2)
                        upgrade_frame->setTexture("upgrade_ready.png");//升级按钮有效
                    break;
                case 2:
                    plant_cannon->setTexture("plant_cannon_unavailable.png");//种植cannon按钮失效
                    plant_etower->setTexture("plant_etower_unavailable.png");//种植etower按钮失效
                    delete_frame->setTexture("delete_ready.png");//删除按钮有效
                    if ((vacancy[vacancyIndex].tower_type == type_cannon && gold >= cannon_upgrade_2to3) || (vacancy[vacancyIndex].tower_type == type_etower && gold >= etower_upgrade_2to3))
                        upgrade_frame->setTexture("upgrade_ready.png");//升级按钮有效
                    break;
                case 3:
                    plant_cannon->setTexture("plant_cannon_unavailable.png");//种植cannon按钮失效
                    plant_etower->setTexture("plant_etower_unavailable.png");//种植etower按钮失效
                    delete_frame->setTexture("delete_ready.png");//删除按钮有效
                    break;
            }
        }
        else
        {
            mouse_select_type = 0;
            yellow_frame->setVisible(false);
            plant_cannon->setTexture("plant_cannon_unavailable.png");
            plant_etower->setTexture("plant_etower_unavailable.png");
            upgrade_frame->setTexture("upgrade_grey.png");
            delete_frame->setTexture("delete_grey.png");
        }
    }

}

void Map_Two::input_background()//放置背景图
{
    auto background = Sprite::create("map\\map_two.png");
    this->addChild(background);
    background->setPosition(background_wide / 2, background_high / 2);//背景图
}

void Map_Two::input_walk_way()//放置怪物路径
{
    std::vector<float> current = walk_way_begin_2;
    walk_way.push_back(current);//放好初始位置
    input_brick(current[0], current[1], 1);
    for (int i = 0; i < 4; i++)
    {
        current[0] += way_size;
        input_brick(current[0], current[1], 1);
        walk_way.push_back(current);
    }//水平向右4格

    for (int i = 0; i < 5; i++)
    {
        current[1] += way_size;
        input_brick(current[0], current[1], 1);
        walk_way.push_back(current);
    }//竖直向上5格

    for (int i = 0; i < 3; i++)
    {
        current[0] += way_size;
        input_brick(current[0], current[1], 1);
        walk_way.push_back(current);
    }//水平向右3格

    for (int i = 0; i < 5; i++)
    {
        current[1] -= way_size;
        input_brick(current[0], current[1], 1);
        walk_way.push_back(current);
    }//竖直向下5格

    for (int i = 0; i < 4; i++)
    {
        current[0] += way_size;
        input_brick(current[0], current[1], 1);
        walk_way.push_back(current);
    }//水平向右4格
     //存放地板向量生成完毕
    return;
}

void Map_Two::game_begin()//游戏开始函数
{
    float carrot_x = walk_way[walk_way.size() - 1][0];
    float carrot_y = walk_way[walk_way.size() - 1][1];//萝卜坐标
    carrot = Carrot::create("carrot_level1_1.png");//萝卜精灵变量
    carrot->setPosition(carrot_x, carrot_y);
    //放置萝卜
    carrot->HP = 10;
    carrot->level = 1;
    carrot->change_tex();
    carrot->HP_Label->setString(carrot->calculate_HP(carrot->HP));//根据当前血量更新字体，（注：增加、消耗血量时，记得用这个语句更新面板）
    this->addChild(carrot);


    gold = gold_2;//金币变量
    gold_label = input_gold();//生成标签
    gold_label->setString(calculate_gold(gold));//更新字体，（注：增加、消耗金币时，记得用这个语句更新面板）

    schedule(CC_SCHEDULE_SELECTOR(Map_father::spawnMonster1_1), 1.0f, 3, 3.0f); //第1波：生成4个怪物1
    schedule(CC_SCHEDULE_SELECTOR(Map_father::spawnMonster1_2), 1.0f, 4, 13.0f);//第2波：生成5个怪物1
    schedule(CC_SCHEDULE_SELECTOR(Map_father::spawnMonster2_1), 1.0f, 3, 23.0f);//第3波：生成4个怪物2
    schedule(CC_SCHEDULE_SELECTOR(Map_father::spawnMonster2_2), 1.0f, 4, 33.0f);//第2波：生成5个怪物2
    schedule(CC_SCHEDULE_SELECTOR(Map_father::spawnMonster3_1), 1.0f, 5, 43.0f);//第3波：生成6个怪物3

    waitForConditionAndExecute(
        [=]() {return (carrot->HP <= 0); },
        [=]() {this->scheduleOnce(CC_SCHEDULE_SELECTOR(Map_father::game_over_failure), 1.0f); }
    );

    map_three_flag = true;
}


/*------------------------------地图二函数----------------------------------*/


/*------------------------------地图三函数----------------------------------*/
void Map_Three::input_listener()
{
    auto mouseListener = EventListenerMouse::create();
    mouseListener->onMouseDown = CC_CALLBACK_1(Map_Three::onMouseDown_Do_Plant, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(mouseListener, this);

    yellow_frame = FrameBox::create("yellow_frame.png");
    this->addChild(yellow_frame); //z-value=0
    yellow_frame->setVisible(false);
}

void Map_Three::ShowPlantButton()
{
    //暗色cannon
    plant_cannon = FrameBox::create("plant_cannon_unavailable.png");
    this->addChild(plant_cannon); //z-value=0
    plant_cannon->Spawn(60.0f, 550.0f, 1.0f);
    plant_cannon->setTexture("plant_cannon_unavailable.png");
    //暗色shit
    plant_shit = FrameBox::create("plant_shit_unavailable.png");
    this->addChild(plant_shit); //z-value=0
    plant_shit->Spawn(60.0f, 450.0f, 1.0f);
    plant_shit->setTexture("plant_shit_unavailable.png");
    //暗色etower
    plant_etower = FrameBox::create("plant_etower_unavailable.png");
    this->addChild(plant_etower); //z-value=0
    plant_etower->Spawn(60.0f, 350.0f, 1.0f);
    plant_etower->setTexture("plant_etower_unavailable.png");
    //暗色升级——注意升级.png需要缩放至×0.7
    upgrade_frame = FrameBox::create("upgrade_grey.png");
    this->addChild(upgrade_frame); //z-value=0
    upgrade_frame->Spawn(60.0f, 250.0f, 0.7f);
    upgrade_frame->setTexture("upgrade_grey.png");
    //暗色移除——注意移除.png需要缩放至×0.7
    delete_frame = FrameBox::create("delete_grey.png");
    this->addChild(delete_frame); //z-value=0
    delete_frame->Spawn(60.0f, 150.0f, 0.7f);
    delete_frame->setTexture("delete_grey.png");
}

void Map_Three::onMouseDown_Do_Plant(Event* event)
{
    EventMouse* e = dynamic_cast<EventMouse*>(event);
    if (e->getMouseButton() == EventMouse::MouseButton::BUTTON_LEFT)
    {
        float x = e->getCursorX(), y = e->getCursorY();
        if (IsFramePlant(x, y, AllPlants_Lv3) && mouse_select_type)//选中种植功能
        {
            //plant a cannon
            if (y <= 550.1 && y >= 549.9 && vacancy[vacancyIndex].level == 0 && gold >= cannon_build_cost)
            {
                //于目标点生成一级cannon
                cannon = FrameBox::create("cannon_Lv1.png");
                this->addChild(cannon);
                cannon->Spawn(AllFrames_Lv3[vacancyIndex].adjusted._x, AllFrames_Lv3[vacancyIndex].adjusted._y, 1.0f);
                vacancy[vacancyIndex].level++;
                vacancy[vacancyIndex].tower_type = type_cannon;
                vacancy[vacancyIndex].spr = cannon; //当前指针存入vacancy中
                gold -= cannon_build_cost;
            }
            //plant a shit
            else if (y <= 450.1 && y >= 449.9 && vacancy[vacancyIndex].level == 0 && gold >= shit_build_cost)
            {
                //于目标点生成一级shit
                shit = FrameBox::create("shit_Lv1.png");
                this->addChild(shit);
                shit->Spawn(AllFrames_Lv3[vacancyIndex].adjusted._x, AllFrames_Lv3[vacancyIndex].adjusted._y, 1.0f);
                vacancy[vacancyIndex].level++;
                vacancy[vacancyIndex].tower_type = type_shit;
                vacancy[vacancyIndex].spr = shit; //当前指针存入vacancy中
                gold -= shit_build_cost;
            }
            //plant a etower
            else if (y <= 350.1 && y >= 349.9 && vacancy[vacancyIndex].level == 0 && gold >= etower_build_cost)
            {
                //于目标点生成一级etower
                etower = FrameBox::create("etower_Lv1.png");
                this->addChild(etower);
                etower->Spawn(AllFrames_Lv3[vacancyIndex].adjusted._x, AllFrames_Lv3[vacancyIndex].adjusted._y, 1.0f);
                vacancy[vacancyIndex].level++;
                vacancy[vacancyIndex].tower_type = type_etower;
                vacancy[vacancyIndex].spr = etower; //当前指针存入vacancy中
                gold -= etower_build_cost;
            }
            //upgrade
            else if (y <= 250.1 && y >= 249.9)
            {
                //1级升2级
                if (vacancy[vacancyIndex].level == 1)
                {
                    if (vacancy[vacancyIndex].tower_type == type_cannon && gold >= cannon_upgrade_1to2)//upgrade cannon
                    {
                        cannon->setTexture("cannon_Lv2.png");
                        vacancy[vacancyIndex].level++;
                        gold -= cannon_upgrade_1to2;
                    }
                    else if (vacancy[vacancyIndex].tower_type == type_shit && gold >= shit_upgrade_1to2)//upgrade shit
                    {
                        shit->setTexture("shit_Lv2.png");
                        vacancy[vacancyIndex].level++;
                        gold -= shit_upgrade_1to2;
                    }
                    else if (vacancy[vacancyIndex].tower_type == type_etower && gold >= etower_upgrade_1to2)//upgrade etower
                    {
                        etower->setTexture("etower_Lv2.png");
                        vacancy[vacancyIndex].level++;
                        gold -= etower_upgrade_1to2;
                    }
                }
                //2级升3级
                else if (vacancy[vacancyIndex].level == 2)
                {
                    if (vacancy[vacancyIndex].tower_type == type_cannon && gold >= cannon_upgrade_2to3)//upgrade cannon
                    {
                        cannon->setTexture("cannon_Lv3.png");
                        vacancy[vacancyIndex].level++;
                        gold -= cannon_upgrade_2to3;
                    }
                    else if (vacancy[vacancyIndex].tower_type == type_shit && gold >= shit_upgrade_2to3)//upgrade shit
                    {
                        shit->setTexture("shit_Lv3.png");
                        vacancy[vacancyIndex].level++;
                        gold -= shit_upgrade_2to3;
                    }
                    else if (vacancy[vacancyIndex].tower_type == type_etower && gold >= etower_upgrade_2to3)//upgrade etower
                    {
                        etower->setTexture("etower_Lv3.png");
                        vacancy[vacancyIndex].level++;
                        gold -= etower_upgrade_2to3;
                    }
                }
            }
            //delete
            else if (y <= 150.1 && y >= 149.9 && vacancy[vacancyIndex].level)
            {
                this->removeChild(vacancy[vacancyIndex].spr);
                vacancy[vacancyIndex].level = 0;
                vacancy[vacancyIndex].tower_type = 0;
                vacancy[vacancyIndex].spr = nullptr;
                gold += delete_recover;
            }

            gold_label->setString(calculate_gold(gold));//更新金币
        }
        else if (IsFrame(x, y, AllFrames_Lv3))//选中空地
        {
            mouse_select_type = 1;
            yellow_frame->setVisible(true);
            yellow_frame->Spawn(x, y, 0.5f);
            yellow_frame->Shimmer();
            singleclick._x = x, singleclick._y = y; //保存黄色框位置，准备种植
            vacancyIndex = CheckBox(singleclick, AllFrames_Lv3);

            //查询选中位置种植状态
            switch (vacancy[vacancyIndex].level)
            {
                case 0://未种植
                    upgrade_frame->setTexture("upgrade_grey.png");//升级按钮无效
                    delete_frame->setTexture("delete_grey.png");//删除按钮无效
                    if (gold >= cannon_build_cost)
                        plant_cannon->setTexture("plant_cannon_available.png");//种植cannon按钮有效
                    if (gold >= shit_build_cost)
                        plant_shit->setTexture("plant_shit_available.png");//种植shit按钮有效
                    if (gold >= etower_build_cost)
                        plant_etower->setTexture("plant_etower_available.png");//种植etower按钮有效
                    break;
                case 1://种植了1级炮台
                    plant_cannon->setTexture("plant_cannon_unavailable.png");//种植cannon按钮失效
                    plant_shit->setTexture("plant_shit_unavailable.png");//种植shit按钮失效
                    plant_etower->setTexture("plant_etower_unavailable.png");//种植etower按钮失效
                    delete_frame->setTexture("delete_ready.png");//删除按钮有效
                    if (vacancy[vacancyIndex].tower_type == type_cannon && gold >= cannon_upgrade_1to2)
                        upgrade_frame->setTexture("upgrade_ready.png");//升级按钮有效
                    if (vacancy[vacancyIndex].tower_type == type_etower && gold >= etower_upgrade_1to2)
                        upgrade_frame->setTexture("upgrade_ready.png");//升级按钮有效
                    break;
                case 2:
                    plant_cannon->setTexture("plant_cannon_unavailable.png");//种植cannon按钮失效
                    plant_shit->setTexture("plant_shit_unavailable.png");//种植shit按钮失效
                    plant_etower->setTexture("plant_etower_unavailable.png");//种植etower按钮失效
                    delete_frame->setTexture("delete_ready.png");//删除按钮有效
                    if ((vacancy[vacancyIndex].tower_type == type_cannon && gold >= cannon_upgrade_2to3)
                        || (vacancy[vacancyIndex].tower_type == type_shit && gold >= shit_upgrade_2to3)
                        || (vacancy[vacancyIndex].tower_type == type_etower && gold >= etower_upgrade_2to3))
                        upgrade_frame->setTexture("upgrade_ready.png");//升级按钮有效
                    break;
                case 3:
                    plant_cannon->setTexture("plant_cannon_unavailable.png");//种植cannon按钮失效
                    plant_shit->setTexture("plant_shit_unavailable.png");//种植shit按钮失效
                    plant_etower->setTexture("plant_etower_unavailable.png");//种植etower按钮失效
                    delete_frame->setTexture("delete_ready.png");//删除按钮有效
                    break;
            }
        }
        else
        {
            mouse_select_type = 0;
            yellow_frame->setVisible(false);
            plant_cannon->setTexture("plant_cannon_unavailable.png");
            plant_shit->setTexture("plant_shit_unavailable.png");
            plant_etower->setTexture("plant_etower_unavailable.png");
            upgrade_frame->setTexture("upgrade_grey.png");
            delete_frame->setTexture("delete_grey.png");
        }
    }

}

void Map_Three::input_background()//生成背景图
{
    auto background = Sprite::create("map\\map_three.png");
    this->addChild(background);
    background->setPosition(background_wide / 2, background_high / 2);//背景图
}

void Map_Three::input_walk_way()//放置怪物路径
{
    std::vector<float> current = walk_way_begin_3;
    walk_way.push_back(current);//放好初始位置
    input_brick(current[0], current[1], 1);
    for (int i = 0; i < 9; i++)
    {
        current[0] += way_size;
        input_brick(current[0], current[1], 1);
        walk_way.push_back(current);//放好初始位置
    }//向右9格
    for (int i = 0; i < 3; i++)
    {
        current[1] -= way_size;
        input_brick(current[0], current[1], 1);
        walk_way.push_back(current);//放好初始位置
    }//向下3格
    for (int i = 0; i < 9; i++)
    {
        current[0] -= way_size;
        input_brick(current[0], current[1], 1);
        walk_way.push_back(current);//放好初始位置
    }//向左9格
    for (int i = 0; i < 3; i++)
    {
        current[1] -= way_size;
        input_brick(current[0], current[1], 1);
        walk_way.push_back(current);//放好初始位置
    }//向下3格
    for (int i = 0; i < 9; i++)
    {
        current[0] += way_size;
        input_brick(current[0], current[1], 1);
        walk_way.push_back(current);//放好初始位置
    }//向右9格
    //存放地板向量生成完毕
    return;
}

void Map_Three::game_begin()//游戏开始函数
{
    float carrot_x = walk_way[walk_way.size() - 1][0];
    float carrot_y = walk_way[walk_way.size() - 1][1];//萝卜坐标
    carrot = Carrot::create("carrot_level1_1.png");//萝卜精灵变量
    carrot->setPosition(carrot_x, carrot_y);
    //放置萝卜
    carrot->HP = 1000;
    carrot->level = 1;
    carrot->change_tex();
    carrot->HP_Label->setString(carrot->calculate_HP(carrot->HP));//根据当前血量更新字体，（注：增加、消耗血量时，记得用这个语句更新面板）
    this->addChild(carrot);

    gold = gold_3;//金币变量
    gold_label = input_gold();//生成标签
    gold_label->setString(calculate_gold(gold));//更新字体，（注：增加、消耗金币时，记得用这个语句更新面板）

    schedule(CC_SCHEDULE_SELECTOR(Map_father::spawnMonster2_1), 1.0f, 3, 3.0f); //第1波：生成4个怪物2
    schedule(CC_SCHEDULE_SELECTOR(Map_father::spawnMonster2_2), 1.0f, 4, 13.0f);//第2波：生成5个怪物2
    schedule(CC_SCHEDULE_SELECTOR(Map_father::spawnMonster3_1), 1.0f, 3, 23.0f);//第3波：生成4个怪物3
    schedule(CC_SCHEDULE_SELECTOR(Map_father::spawnMonster3_2), 1.0f, 4, 33.0f);//第2波：生成5个怪物3
    schedule(CC_SCHEDULE_SELECTOR(Map_father::spawnMonster4_1), 1.0f, 4, 43.0f);//第3波：生成5个怪物4
    schedule(CC_SCHEDULE_SELECTOR(Map_father::spawnMonster4_2), 1.0f, 5, 53.0f);//第3波：生成6个怪物4

    waitForConditionAndExecute(
        [=]() {return (carrot->HP <= 0); },
        [=]() {this->scheduleOnce(CC_SCHEDULE_SELECTOR(Map_father::game_over_failure), 1.0f); }
    );

}

/*------------------------------地图三函数----------------------------------*/


/*************************************************************
    CheckBox函数：已知对应方块的中心点坐标，查询其代号
*************************************************************/
int CheckBox(XY obj, const std::vector<FS>& table)
{
    for (auto& it : table)
        if (it.adjusted._x == obj._x && it.adjusted._y == obj._y)
            return it.index;
    return -1;
}
