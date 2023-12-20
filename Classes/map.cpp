#include"map.h"
#include"choose_map.h"
#include "monster.h"
#include"carrot.h"
#include "ui/CocosGUI.h"
#include"cocos-ext.h"
USING_NS_CC;

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
    input_gold(gold);//放置金币
    input_carrot();//放置萝卜
    spawn_monster();//生成怪物
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

void Map_father::input_gold(const int gold)//放置金币函数,（已完成）
{
    int digit = 1000;
    std::string figure;
    for (int i = 0; i < 4; i++)
    {
        int k = (gold / digit) % 10;
        digit /= 10;
        figure.push_back(k + '0');
    }//计算出每一位的数字，放入字符串中
    auto gold_label = Label::createWithTTF(figure, "fonts\\Marker Felt.ttf",56);
    Color3B gold_color(255, 233, 0);
    gold_label->setColor(gold_color);//调成黄色
    this->addChild(gold_label);
    gold_label->setPosition(Point(gold_x, gold_y));
    //将字体标签放好

    auto gold_item = Sprite::create("gold.png");//生成阳光图标
    this->addChild(gold_item);
    gold_item->setPosition(gold_x - 90, gold_y);
    //放好阳光图标

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
    return;
}

void Map_One::input_carrot()//放置萝卜函数
{
    auto carrot = Carrot::create("carrot_level1_1.png");//放置一个完整萝卜
    this->addChild(carrot);
    carrot->setPosition(walk_way_store_1[walk_way_store_1.size() - 1][0], walk_way_store_1[walk_way_store_1.size() - 1][1]);
}

void Map_One::spawn_monster()
{
    auto wave1 = Node::create();
    MonsterSpawner wave1Spawn(wave1, walk_way_store_1, 1);
    this->addChild(wave1);
    wave1Spawn.spawn1(1.0f);
    /*
    wave1->scheduleUpdate();
    wave1->scheduleOnce(SEL_SCHEDULE(MonsterSpawner::spawn1), 10.0f);
    wave1->scheduleOnce(SEL_SCHEDULE(MonsterSpawner::spawn2), 11.0f);
    wave1->scheduleOnce(SEL_SCHEDULE(MonsterSpawner::spawn3), 12.0f);
    wave1->scheduleOnce(SEL_SCHEDULE(MonsterSpawner::spawn4), 13.0f);
    wave1->scheduleOnce(SEL_SCHEDULE(MonsterSpawner::spawn5), 13.0f);*/
}

/*------------------------------地图一函数----------------------------------*/


/*------------------------------地图二函数----------------------------------*/

void Map_Two::input_background()//放置背景图
{
    auto background = Sprite::create("map\\map_two.png");
    this->addChild(background);
    background->setPosition(background_wide / 2, background_high / 2);//背景图
}

void Map_Two::input_walk_way()
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

void Map_Two::input_carrot()//放置萝卜函数
{
    auto carrot = Carrot::create("carrot_level1_1.png");//放置一个完整萝卜
    this->addChild(carrot);
    carrot->setPosition(walk_way_store_2[walk_way_store_2.size() - 1][0], walk_way_store_2[walk_way_store_2.size() - 1][1]);
}

void Map_Two::spawn_monster()
{
}

/*------------------------------地图二函数----------------------------------*/


/*------------------------------地图三函数----------------------------------*/
void Map_Three::input_background()
{
    auto background = Sprite::create("map\\map_three.png");
    this->addChild(background);
    background->setPosition(background_wide / 2, background_high / 2);//背景图
}

void Map_Three::input_walk_way()
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

void Map_Three::input_carrot()//放置萝卜函数
{
    auto carrot = Carrot::create("carrot_level1_1.png");//放置一个完整萝卜
    this->addChild(carrot);
    carrot->setPosition(walk_way_store_3[walk_way_store_3.size() - 1][0], walk_way_store_3[walk_way_store_3.size() - 1][1]);
}

void Map_Three::spawn_monster()
{
}

/*------------------------------地图三函数----------------------------------*/