#include"map.h"
#include"choose_map.h"
#include "monster.h"
#include"carrot.h"
#include "ui/CocosGUI.h"
#include"cocos-ext.h"
USING_NS_CC;
using namespace std;

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
<<<<<<< Updated upstream
    input_gold(gold);//放置金币
    input_carrot();//放置萝卜
=======
    input_gold_item();//放置金币
    game_begin();//开始游戏
>>>>>>> Stashed changes
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
        figure.push_back(k+'0');
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

    //放置一个怪兽
        auto monster1 = MonSprite::create("monster1_1.png");
        this->addChild(monster1);
        MonCtrl Moncon1(monster1, 1, walk_way_store_1);
        Moncon1.spawn();
<<<<<<< Updated upstream
    return;
}

void Map_One::input_carrot()//放置萝卜函数
{
    auto carrot = Carrot::create("carrot_level1_1.png");//放置一个完整萝卜
    this->addChild(carrot);
    carrot->setPosition(walk_way_store_1[walk_way_store_1.size() - 1][0], walk_way_store_1[walk_way_store_1.size() - 1][1]);
}
=======

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
}

void Map_One::spawn_monster()//刷新怪物
{
    MonSprite* monster1 = MonSprite::create("monster1_1.png");
    this->addChild(monster1);
    MonCtrl Moncon1(monster1, 1, walk_way_store_1);
    Moncon1.spawn();
>>>>>>> Stashed changes

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

<<<<<<< Updated upstream
void Map_Two::input_carrot()//放置萝卜函数
=======
void Map_Two::game_begin()//游戏开始函数
>>>>>>> Stashed changes
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
}

<<<<<<< Updated upstream
=======
void Map_Two::spawn_monster()
{
    MonSprite* monster1 = MonSprite::create("monster1_1.png");
    this->addChild(monster1);
    MonCtrl Moncon1(monster1, 1, walk_way_store_2);
    Moncon1.spawn();

}

>>>>>>> Stashed changes
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
<<<<<<< Updated upstream

=======
>>>>>>> Stashed changes

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
<<<<<<< Updated upstream
=======

void Map_Three::spawn_monster()
{
    MonSprite* monster1 = MonSprite::create("monster1_1.png");
    this->addChild(monster1);
    MonCtrl Moncon1(monster1, 1, walk_way_store_3);
    Moncon1.spawn();

}
>>>>>>> Stashed changes
/*------------------------------地图三函数----------------------------------*/