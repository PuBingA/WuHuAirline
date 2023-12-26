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
    monster_wave->addChild(monster);
    monster->monster_attack_carrot(carrot);

}

void Map_father::spawnMonster1_2(float dt)
{
    MonSprite* monster = MonSprite::create(1);
    monster->monster_spawn(walk_way);
    monster_wave->addChild(monster);
    monster->monster_attack_carrot(carrot);
}

void Map_father::spawnMonster1_3(float dt)
{
    MonSprite* monster = MonSprite::create(1);
    monster->monster_spawn(walk_way);
    monster_wave->addChild(monster);
    monster->monster_attack_carrot(carrot);
}

void Map_father::spawnMonster2_1(float dt)
{
    MonSprite* monster = MonSprite::create(2);
    monster->monster_spawn(walk_way);
    monster_wave->addChild(monster);
    monster->monster_attack_carrot(carrot);

}

void Map_father::spawnMonster2_2(float dt)
{
    MonSprite* monster = MonSprite::create(2);
    monster->monster_spawn(walk_way);
    monster_wave->addChild(monster);
    monster->monster_attack_carrot(carrot);
}

void Map_father::spawnMonster2_3(float dt)
{
    MonSprite* monster = MonSprite::create(2);
    monster->monster_spawn(walk_way);
    monster_wave->addChild(monster);
    monster->monster_attack_carrot(carrot);
}

void Map_father::spawnMonster3_1(float dt)
{
    MonSprite* monster = MonSprite::create(3);
    monster->monster_spawn(walk_way);
    monster_wave->addChild(monster);
    monster->monster_attack_carrot(carrot);
}

void Map_father::spawnMonster3_2(float dt)
{
    MonSprite* monster = MonSprite::create(3);
    monster->monster_spawn(walk_way);
    monster_wave->addChild(monster);
    monster->monster_attack_carrot(carrot);
}

void Map_father::spawnMonster3_3(float dt)
{
    MonSprite* monster = MonSprite::create(3);
    monster->monster_spawn(walk_way);
    monster_wave->addChild(monster);
    monster->monster_attack_carrot(carrot);
}

void Map_father::spawnMonster4_1(float dt)
{
    MonSprite* monster = MonSprite::create(4);
    monster->monster_spawn(walk_way);
    monster_wave->addChild(monster);
    monster->monster_attack_carrot(carrot);
}

void Map_father::spawnMonster4_2(float dt)
{
    MonSprite* monster = MonSprite::create(4);
    monster->monster_spawn(walk_way);
    monster_wave->addChild(monster);
    monster->monster_attack_carrot(carrot);
}

void Map_father::spawnMonster4_3(float dt)
{
    MonSprite* monster = MonSprite::create(4);
    monster->monster_spawn(walk_way);
    monster_wave->addChild(monster);
    monster->monster_attack_carrot(carrot);
}

void Map_father::spawnBoss(float dt)
{
    AudioEngine::pauseAll();
    boss_music = AudioEngine::play2d("boss_background.mp3", false);
    boss_spawned = true;
    boss = MonSprite::create(5);
    boss->monster_spawn(walk_way);
    monster_wave->addChild(boss);
    boss->monster_attack_carrot(carrot);
}

bool Map_father::init()//父类创建场景总函数
{
    if (!Scene::init())
        return false;

    auto visibleSize = Director::getInstance()->getVisibleSize();//获取可见大小
    Vec2 origin = Director::getInstance()->getVisibleOrigin();//获取opengl起点
    
    vacancy.clear();
    for (int i = 0; i <= 50; i++)
        vacancy.push_back({ i,0,nullptr });
    input_background();//放置背景图
    input_walk_way();//放置地板
    input_return_pause();//放置返回，暂停键
    input_gold_item();//放置金币
    input_carrot_level_button();
    ShowPlantButton();
    input_listener();
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
    gold_label = Label::createWithTTF("", "fonts\\Marker Felt.ttf", 56);
    Color3B gold_color(255, 233, 0);
    gold_label->setColor(gold_color);//调成黄色
    this->addChild(gold_label);
    gold_label->setPosition(gold_x, gold_y);
    gold_label->setString(calculate_gold(gold));//更新字体，（注：增加、消耗金币时，记得用这个语句更新面板）
    //放好阳光图标
}



std::string Map_father::calculate_gold(int *gold)
{
    int digit = 1000;//千位
    std::string figure;
    for (int i = 0; i < 4; i++)
    {
        int k = (*gold / digit) % 10;
        digit /= 10;
        figure.push_back(k + '0');
    }//计算出每一位的数字，放入字符串中
    return figure;
}

void Map_father::change_gold_label(float dt)
{
    gold_label->setString(calculate_gold(gold));//更新字体，（注：增加、消耗金币时，记得用这个语句更新面板）
}

void Map_father::buttonCallback(cocos2d::Ref* pSender)//暂停键触发函数
{
    Director::getInstance()->pushScene(settlement_pause::create());
}

void Map_father::menuCallback(cocos2d::Ref* pSender)//返回键触发函数
{
    Director::getInstance()->replaceScene(choose_map::createScene());//切换到选择地图场景
}

void Map_father::game_over_success(float dt)
{
    AudioEngine::stop(boss_music);
        auto scene = settlement_success::createScene();
        Director::getInstance()->replaceScene(TransitionCrossFade::create(2.0f, scene));
}

void Map_father::game_over_failure(float dt)
{
    if(boss_spawned)
        AudioEngine::stop(boss_music);
    auto scene = settlement_failure::createScene();
    Director::getInstance()->replaceScene(TransitionCrossFade::create(2.0f, scene));
}

void Map_father::onMouseDown_Do_Plant(Event* event)
{
    EventMouse* e = dynamic_cast<EventMouse*>(event);
    if (e->getMouseButton() == EventMouse::MouseButton::BUTTON_LEFT)
    {
        float x = e->getCursorX(), y = e->getCursorY();
        if (IsFramePlant(x, y, AllPlants) && mouse_select_type)//选中种植功能
        {
            //plant a cannon
            if (IsFramePlant(x, y, AllPlants) == 1 && vacancy[vacancyIndex].spr == nullptr && *gold >= cannon_build_cost)
            {
                //于目标点生成一级cannon
                cannon = Cannon::create("cannon_Lv1.png",monster_wave,gold);
                this->addChild(cannon);
                cannon->setPosition(AllFrames[vacancyIndex].adjusted._x, AllFrames[vacancyIndex].adjusted._y);
                cannon->level = 1;
                vacancy[vacancyIndex].tower_type = type_cannon;
                vacancy[vacancyIndex].spr = cannon; //当前指针存入vacancy中
                *gold -= cannon_build_cost;
                upgrade_frame->setTexture("upgrade_ready.png");//升级按钮有效
                delete_frame->setTexture("delete_ready.png");//删除按钮有效
            }
            //plant a shit
            else if (IsFramePlant(x, y, AllPlants) == 2 && vacancy[vacancyIndex].spr == nullptr && *gold >= shit_build_cost)
            {
                //于目标点生成一级shit
                shit = Shit::create("shit_Lv1.png", monster_wave, gold);
                this->addChild(shit);
                shit->setPosition(AllFrames[vacancyIndex].adjusted._x, AllFrames[vacancyIndex].adjusted._y);
                shit->level = 1;
                vacancy[vacancyIndex].tower_type = type_shit;
                vacancy[vacancyIndex].spr = shit; //当前指针存入vacancy中
               * gold -= shit_build_cost;
                upgrade_frame->setTexture("upgrade_ready.png");//升级按钮有效
                delete_frame->setTexture("delete_ready.png");//删除按钮有效
            }
            //plant a etower
            else if (IsFramePlant(x, y, AllPlants) == 3 && vacancy[vacancyIndex].spr == nullptr && *gold >= etower_build_cost)
            {
                //于目标点生成一级etower
                etower = Etower::create("etower_Lv1.png", monster_wave, gold);
                this->addChild(etower);
                etower->setPosition(AllFrames[vacancyIndex].adjusted._x, AllFrames[vacancyIndex].adjusted._y);
                etower->level = 1;
                vacancy[vacancyIndex].tower_type = type_etower;
                vacancy[vacancyIndex].spr = etower; //当前指针存入vacancy中
               * gold -= etower_build_cost;
                upgrade_frame->setTexture("upgrade_ready.png");//升级按钮有效
                delete_frame->setTexture("delete_ready.png");//删除按钮有效
            }
            //upgrade
            else if (IsFramePlant(x, y, AllPlants) == 4 && vacancy[vacancyIndex].spr)
            {
                //1级升2级
                if (vacancy[vacancyIndex].spr->level == 1)
                {
                    if (vacancy[vacancyIndex].tower_type == type_cannon && *gold >= cannon_upgrade_1to2)//upgrade cannon
                    {
                        cannon->setTexture("cannon_Lv2.png");
                        cannon->level++;
                       * gold -= cannon_upgrade_1to2;
                       auto evolution_effect = AudioEngine::play2d("evolution_effect.mp3",false);
                    }
                    else if (vacancy[vacancyIndex].tower_type == type_shit && *gold >= shit_upgrade_1to2)//upgrade shit
                    {
                        shit->setTexture("shit_Lv2.png");
                        shit->level++;
                       * gold -= shit_upgrade_1to2;
                       auto evolution_effect = AudioEngine::play2d("evolution_effect.mp3", false);
                    }
                    else if (vacancy[vacancyIndex].tower_type == type_etower && *gold >= etower_upgrade_1to2)//upgrade etower
                    {
                        etower->setTexture("etower_Lv2.png");
                        etower->level++;
                        *gold -= etower_upgrade_1to2;
                        auto evolution_effect = AudioEngine::play2d("evolution_effect.mp3", false);
                    }
                }
                //2级升3级
                else if (vacancy[vacancyIndex].spr->level == 2)
                {
                    if (vacancy[vacancyIndex].tower_type == type_cannon && *gold >= cannon_upgrade_2to3)//upgrade cannon
                    {
                        cannon->setTexture("cannon_Lv3.png");
                        cannon->level++;
                        *gold -= cannon_upgrade_2to3;
                        auto evolution_effect = AudioEngine::play2d("evolution_effect.mp3", false);
                    }
                    else if (vacancy[vacancyIndex].tower_type == type_shit && * gold >= shit_upgrade_2to3)//upgrade shit
                    {
                        shit->setTexture("shit_Lv3.png");
                        shit->level++;
                        *gold -= shit_upgrade_2to3;
                        auto evolution_effect = AudioEngine::play2d("evolution_effect.mp3", false);
                    }
                    else if (vacancy[vacancyIndex].tower_type == type_etower && *gold >= etower_upgrade_2to3)//upgrade etower
                    {
                        etower->setTexture("etower_Lv3.png");
                        etower->level++;
                        *gold -= etower_upgrade_2to3;
                        auto evolution_effect = AudioEngine::play2d("evolution_effect.mp3", false);
                    }
                }
            }
            //delete
            else if (IsFramePlant(x, y, AllPlants) == 5 && vacancy[vacancyIndex].spr)
            {
                this->removeChild(vacancy[vacancyIndex].spr);
                vacancy[vacancyIndex].tower_type = 0;
                vacancy[vacancyIndex].spr = nullptr;
                *gold += delete_recover;
                auto delete_effect = AudioEngine::play2d("delete_effect.mp3", false);
            }
            
        }
        else if (IsFrame(x, y, AllFrames))//选中空地
        {
            mouse_select_type = 1;
            yellow_frame->setVisible(true);
            yellow_frame->setPosition(x, y);
            singleclick._x = x, singleclick._y = y; //保存黄色框位置，准备种植
            vacancyIndex = CheckBox(singleclick, AllFrames);
            //查询选中位置种植状态
            if (vacancy[vacancyIndex].spr == nullptr)
            {
                upgrade_frame->setTexture("upgrade_grey.png");//升级按钮无效
                delete_frame->setTexture("delete_grey.png");//删除按钮无效
                if (*gold >= cannon_build_cost && plant_cannon)
                    plant_cannon->setTexture("plant_cannon_available.png");//种植cannon按钮有效
                if (*gold >= shit_build_cost && plant_shit)
                    plant_shit->setTexture("plant_shit_available.png");//种植shit按钮有效
                if (*gold >= etower_build_cost && plant_etower)
                    plant_etower->setTexture("plant_etower_available.png");//种植etower按钮有效
            }
            else
            {
                if (plant_cannon)
                    plant_cannon->setTexture("plant_cannon_unavailable.png");//种植cannon按钮失效
                if (plant_shit)
                    plant_shit->setTexture("plant_shit_unavailable.png");//种植shit按钮失效
                if (plant_etower)
                    plant_etower->setTexture("plant_etower_unavailable.png");//种植etower按钮失效
                delete_frame->setTexture("delete_ready.png");//删除按钮有效
                if ((vacancy[vacancyIndex].spr->level == 1
                    && ((vacancy[vacancyIndex].tower_type == type_cannon && *gold >= cannon_upgrade_1to2) || (vacancy[vacancyIndex].tower_type == type_shit && *gold >= shit_upgrade_1to2) || (vacancy[vacancyIndex].tower_type == type_etower && *gold >= etower_upgrade_1to2)))
                    || (vacancy[vacancyIndex].spr->level == 2
                    && ((vacancy[vacancyIndex].tower_type == type_cannon && *gold >= cannon_upgrade_2to3) || (vacancy[vacancyIndex].tower_type == type_shit && *gold >= shit_upgrade_2to3) || (vacancy[vacancyIndex].tower_type == type_etower && *gold >= etower_upgrade_2to3))))
                    upgrade_frame->setTexture("upgrade_ready.png");//升级按钮有效
            }
        }
        else
        {
            mouse_select_type = 0;
            yellow_frame->setVisible(false);
            if (plant_cannon)
                plant_cannon->setTexture("plant_cannon_unavailable.png");//种植cannon按钮失效
            if (plant_shit)
                plant_shit->setTexture("plant_shit_unavailable.png");//种植shit按钮失效
            if (plant_etower)
                plant_etower->setTexture("plant_etower_unavailable.png");//种植etower按钮失效
            upgrade_frame->setTexture("upgrade_grey.png");
            delete_frame->setTexture("delete_grey.png");
        }
    }
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
        *gold -= carrot_level2_cost;
    if (carrot->level == 2)
        *gold -= carrot_level3_cost;
    auto evolution_effect = AudioEngine::play2d("success_scream.mp3", false);
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
        if (carrot->level == 1 && *gold < carrot_level2_cost)
        {
            carrot_level_button->setTouchEnabled(false);
            carrot_level_button->setBright(false);
        }
        if (carrot->level == 2 && *gold < carrot_level3_cost)
        {
            carrot_level_button->setTouchEnabled(false);
            carrot_level_button->setBright(false);
        }
    }//对不可点击情况进行分析
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
    AllFrames = AllFrames_Lv1;
    AllPlants = AllPlants_Lv1;
    auto mouseListener = EventListenerMouse::create();
    mouseListener->onMouseDown = CC_CALLBACK_1(Map_One::onMouseDown_Do_Plant, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(mouseListener, this);
    mouse_select_type = 0;
    yellow_frame = Sprite::create("yellow_frame.png");
    yellow_frame->runAction(RepeatForever::create(Sequence::create(ScaleTo::create(0.3f, 0.7f), ScaleTo::create(0.3f, 0.5f), nullptr)));
    this->addChild(yellow_frame); //z-value=0
    yellow_frame->setVisible(false);
}

void Map_One::ShowPlantButton()
{
    //暗色cannon
    plant_cannon = Sprite::create("plant_cannon_unavailable.png");
    this->addChild(plant_cannon); //z-value=0
    plant_cannon->setPosition(450, 600);
    //暗色shit
    plant_shit = Sprite::create("plant_shit_unavailable.png");
    this->addChild(plant_shit); //z-value=0
    plant_shit->setPosition(550, 600);
    //暗色升级——注意升级.png需要缩放至×0.7
    upgrade_frame = Sprite::create("upgrade_grey.png");
    this->addChild(upgrade_frame); //z-value=0
    upgrade_frame->setPosition(650, 600);
    upgrade_frame->setScale(0.7f);
    //暗色移除——注意移除.png需要缩放至×0.7
    delete_frame = Sprite::create("delete_grey.png");
    this->addChild(delete_frame); //z-value=0
    delete_frame->setPosition(750, 600);
    delete_frame->setScale(0.7f);
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
    carrot->change_tex();
    carrot->HP_Label->setString(carrot->calculate_HP(carrot->HP));//根据当前血量更新字体，（注：增加、消耗血量时，记得用这个语句更新面板）
    this->addChild(carrot);
   
    this->addChild(monster_wave);
    monster_wave->setVisible(1);
    schedule(CC_SCHEDULE_SELECTOR(Map_father::spawnMonster1_1), 1.0f, 2, 3.0f); //第1波：生成3个怪物1
    schedule(CC_SCHEDULE_SELECTOR(Map_father::spawnMonster1_2), 1.0f, 4, 13.0f);//第2波：生成5个怪物1
    schedule(CC_SCHEDULE_SELECTOR(Map_father::spawnMonster1_3), 1.0f, 5, 23.0f);//第3波：生成6个怪物1
    scheduleOnce(CC_SCHEDULE_SELECTOR(Map_father::spawnBoss), 33.0f);//boss

    waitForConditionAndExecute
    (
        [=](){return (carrot->HP <= 0||(boss_spawned == true && boss->monCurrentLife == 0));},
        [=]()
        {if(carrot->HP<=0)
            this->scheduleOnce(CC_SCHEDULE_SELECTOR(Map_father::game_over_failure), 0.1f);
        else
    {
        map_two_flag = true; 
        this->scheduleOnce(CC_SCHEDULE_SELECTOR(Map_father::game_over_success), 0.1f);
    }
        }
   );//游戏结束判断



    schedule(CC_SCHEDULE_SELECTOR(Map_father::change_gold_label), 0.1f);//检测金币变化
    schedule(CC_SCHEDULE_SELECTOR(Map_father::change_carrot_level_button), 0.1f);//检测萝卜能否升级

}


/*------------------------------地图一函数----------------------------------*/


/*------------------------------地图二函数----------------------------------*/

void Map_Two::input_listener()
{
    AllFrames = AllFrames_Lv2;
    AllPlants = AllPlants_Lv2;
    auto mouseListener = EventListenerMouse::create();
    mouseListener->onMouseDown = CC_CALLBACK_1(Map_Two::onMouseDown_Do_Plant, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(mouseListener, this);

    yellow_frame = Sprite::create("yellow_frame.png");
    yellow_frame->runAction(RepeatForever::create(Sequence::create(ScaleTo::create(0.3f, 0.7f), ScaleTo::create(0.3f, 0.5f), nullptr)));
    this->addChild(yellow_frame); //z-value=0
    yellow_frame->setVisible(false);
}

void Map_Two::ShowPlantButton()
{
    //暗色cannon
    plant_cannon = Sprite::create("plant_cannon_unavailable.png");
    this->addChild(plant_cannon); //z-value=0
    plant_cannon->setPosition(60, 550);
    plant_cannon->setTexture("plant_cannon_unavailable.png");
    //暗色etower
    plant_etower = Sprite::create("plant_etower_unavailable.png");
    this->addChild(plant_etower); //z-value=0
    plant_etower->setPosition(60, 450);
    plant_etower->setTexture("plant_etower_unavailable.png");
    //暗色升级——注意升级.png需要缩放至×0.7
    upgrade_frame = Sprite::create("upgrade_grey.png");
    this->addChild(upgrade_frame); //z-value=0
    upgrade_frame->setScale(0.7f);
    upgrade_frame->setPosition(60, 350);
    upgrade_frame->setTexture("upgrade_grey.png");
    //暗色移除——注意移除.png需要缩放至×0.7
    delete_frame = Sprite::create("delete_grey.png");
    this->addChild(delete_frame); //z-value=0
    delete_frame->setScale(0.7f);
    delete_frame->setPosition(60, 250);
    delete_frame->setTexture("delete_grey.png");
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
    carrot->change_tex();
    carrot->HP_Label->setString(carrot->calculate_HP(carrot->HP));//根据当前血量更新字体，（注：增加、消耗血量时，记得用这个语句更新面板）
    this->addChild(carrot);

    this->addChild(monster_wave);
    monster_wave->setVisible(1);

 

    schedule(CC_SCHEDULE_SELECTOR(Map_father::spawnMonster1_1), 1.0f, 3, 3.0f); //第1波：生成4个怪物1
    schedule(CC_SCHEDULE_SELECTOR(Map_father::spawnMonster1_2), 1.0f, 4, 13.0f);//第2波：生成5个怪物1
    schedule(CC_SCHEDULE_SELECTOR(Map_father::spawnMonster2_1), 1.0f, 3, 23.0f);//第3波：生成4个怪物2
    schedule(CC_SCHEDULE_SELECTOR(Map_father::spawnMonster2_2), 1.0f, 4, 33.0f);//第2波：生成5个怪物2
    schedule(CC_SCHEDULE_SELECTOR(Map_father::spawnMonster3_1), 1.0f, 5, 43.0f);//第3波：生成6个怪物3
    scheduleOnce(CC_SCHEDULE_SELECTOR(Map_father::spawnBoss), 53.0f);//boss


    waitForConditionAndExecute
    (
        [=]() {return (carrot->HP <= 0 || (boss_spawned == true && boss->monCurrentLife == 0)); },
        [=]()
        {if (carrot->HP <= 0)
        this->scheduleOnce(CC_SCHEDULE_SELECTOR(Map_father::game_over_failure), 0.1f);
        else
    {
        map_three_flag = true;
        this->scheduleOnce(CC_SCHEDULE_SELECTOR(Map_father::game_over_success), 0.1f);
    }
        }
    );//游戏结束判断

    schedule(CC_SCHEDULE_SELECTOR(Map_father::change_gold_label), 0.1f);//检测金币变化
    schedule(CC_SCHEDULE_SELECTOR(Map_father::change_carrot_level_button), 0.1f);//检测萝卜能否升级
}


/*------------------------------地图二函数----------------------------------*/


/*------------------------------地图三函数----------------------------------*/
void Map_Three::input_listener()
{
    AllFrames = AllFrames_Lv3;
    AllPlants = AllPlants_Lv3;
    auto mouseListener = EventListenerMouse::create();
    mouseListener->onMouseDown = CC_CALLBACK_1(Map_Three::onMouseDown_Do_Plant, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(mouseListener, this);

    yellow_frame = Sprite::create("yellow_frame.png");
    yellow_frame->runAction(RepeatForever::create(Sequence::create(ScaleTo::create(0.3f, 0.7f), ScaleTo::create(0.3f, 0.5f), nullptr)));
    this->addChild(yellow_frame); //z-value=0
    yellow_frame->setVisible(false);
}

void Map_Three::ShowPlantButton()
{
    //暗色cannon
    plant_cannon = Sprite::create("plant_cannon_unavailable.png");
    this->addChild(plant_cannon); //z-value=0
    plant_cannon->setPosition(60.0f, 550.0f);
    plant_cannon->setTexture("plant_cannon_unavailable.png");
    //暗色shit
    plant_shit = Sprite::create("plant_shit_unavailable.png");
    this->addChild(plant_shit); //z-value=0
    plant_shit->setPosition(60.0f, 450.0f);
    plant_shit->setTexture("plant_shit_unavailable.png");
    //暗色etower
    plant_etower = Sprite::create("plant_etower_unavailable.png");
    this->addChild(plant_etower); //z-value=0
    plant_etower->setPosition(60.0f, 350.0f);
    plant_etower->setTexture("plant_etower_unavailable.png");
    //暗色升级——注意升级.png需要缩放至×0.7
    upgrade_frame = Sprite::create("upgrade_grey.png");
    this->addChild(upgrade_frame); //z-value=0
    upgrade_frame->setPosition(60.0f, 250.0f);
    upgrade_frame->setScale(0.7f);
    upgrade_frame->setTexture("upgrade_grey.png");
    //暗色移除——注意移除.png需要缩放至×0.7
    delete_frame = Sprite::create("delete_grey.png");
    this->addChild(delete_frame); //z-value=0
    delete_frame->setPosition(60.0f, 150.0f);
    delete_frame->setScale(0.7f);
    delete_frame->setTexture("delete_grey.png");
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
    carrot->change_tex();
    carrot->HP_Label->setString(carrot->calculate_HP(carrot->HP));//根据当前血量更新字体，（注：增加、消耗血量时，记得用这个语句更新面板）
    this->addChild(carrot);

    this->addChild(monster_wave);
    monster_wave->setVisible(1);



    schedule(CC_SCHEDULE_SELECTOR(Map_father::spawnMonster2_1), 1.0f, 3, 3.0f); //第1波：生成4个怪物2
    schedule(CC_SCHEDULE_SELECTOR(Map_father::spawnMonster2_2), 1.0f, 4, 13.0f);//第2波：生成5个怪物2
    schedule(CC_SCHEDULE_SELECTOR(Map_father::spawnMonster3_1), 1.0f, 3, 23.0f);//第3波：生成4个怪物3
    schedule(CC_SCHEDULE_SELECTOR(Map_father::spawnMonster3_2), 1.0f, 4, 33.0f);//第2波：生成5个怪物3
    schedule(CC_SCHEDULE_SELECTOR(Map_father::spawnMonster4_1), 1.0f, 4, 43.0f);//第3波：生成5个怪物4
    schedule(CC_SCHEDULE_SELECTOR(Map_father::spawnMonster4_2), 1.0f, 5, 53.0f);//第3波：生成6个怪物4
    scheduleOnce(CC_SCHEDULE_SELECTOR(Map_father::spawnBoss), 63.0f);//boss


    waitForConditionAndExecute
    (
        [=]() {return (carrot->HP <= 0 || (boss_spawned == true && boss->monCurrentLife == 0)); },
        [=]()
        {if (carrot->HP <= 0)
        this->scheduleOnce(CC_SCHEDULE_SELECTOR(Map_father::game_over_failure), 0.1f);
        else
    {
        map_two_flag = true;
        this->scheduleOnce(CC_SCHEDULE_SELECTOR(Map_father::game_over_success), 0.1f);
    }
        }
    );//游戏结束判断


    schedule(CC_SCHEDULE_SELECTOR(Map_father::change_gold_label), 0.1f);//检测金币变化
    schedule(CC_SCHEDULE_SELECTOR(Map_father::change_carrot_level_button), 0.1f);//检测萝卜能否升级

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

bool IsFrame(float& x, float& y, const std::vector<FS>& allframes)
{
    for (auto& adjust_coord : allframes)
        if (x > adjust_coord.left_up._x && x < adjust_coord.right_down._x && y > adjust_coord.right_down._y && y < adjust_coord.left_up._y)
        {
            x = adjust_coord.adjusted._x;
            y = adjust_coord.adjusted._y;
            return 1;
        }
    return 0;
}

int IsFramePlant(float& x, float& y, const std::vector<FS>& allplants)
{
    for (auto& adjust_coord : allplants)
        if (x > adjust_coord.left_up._x && x < adjust_coord.right_down._x && y > adjust_coord.right_down._y && y < adjust_coord.left_up._y)
        {
            x = adjust_coord.adjusted._x;
            y = adjust_coord.adjusted._y;
            return adjust_coord.index;
        }
    return 0;
}