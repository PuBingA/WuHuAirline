#include"map.h"
#include"choose_map.h"
USING_NS_CC;
using namespace std;

/*----------------------------------
--------------------------------------------------------------------父类函数----------------------------------
--------------------------------*/
Scene* Map_father::createScene()
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
    if (!Scene::init())
    {
        return false;
    }

    auto visibleSize = Director::getInstance()->getVisibleSize();//获取可见大小
    Vec2 origin = Director::getInstance()->getVisibleOrigin();//获取opengl起点

    input_background();//放置背景图
    input_walk_way();//放置地板
    input_return_pause();//放置返回，暂停键
    return true;
}

void Map_father::input_return_pause()//父类放置暂停以及返回键函数  暂停键未实现
{
    auto return_menu = MenuItemImage::create("return.png", "return_selected.png", CC_CALLBACK_1(Map_father::menuCallback, this));
    auto menu = Menu::create(return_menu, NULL);
    this->addChild(menu);
    menu->setPosition(return_x,return_y);
    //返回键放置完毕
}

void Map_father::menuCallback(cocos2d::Ref* pSender)//返回键触发函数
{
    Director::getInstance()->replaceScene(choose_map::createScene());//切换到选择地图场景
}
/*----------------------------------
--------------------------------------------------------------------父类函数----------------------------------
--------------------------------*/






/*----------------------------------
--------------------------------------------------------------------地图一函数----------------------------------
--------------------------------*/

void Map_One::input_background()//放置背景图
{
    auto background = Sprite::create("map\\map_one.png");
    this->addChild(background);
    background->setPosition(background_wide / 2, background_high / 2);//背景图
}

void Map_One::input_walk_way()//放置怪物行进路径
{
    Vec2 current = walk_way_begin_1;
    walk_way_store_1.push_back(current);//放好初始位置
    for (int i = 0; i < 5; i++)
    {
        current.y -= way_size;
        walk_way_store_1.push_back(current);
    }//竖直向下5格

    for (int i = 0; i < 9; i++)
    {
        current.x += way_size;
        walk_way_store_1.push_back(current);
    }//水平向右9格

    for (int i = 0; i < 5; i++)
    {
        current.y += way_size;
        walk_way_store_1.push_back(current);
    }//竖直向上5格
    //存放地板向量生成完毕

    for (int i = 0; i < walk_way_store_1.size(); i++)
    {
        auto walk_way = Sprite::create("way.png");
        this->addChild(walk_way);
        walk_way->setPosition(walk_way_store_1[i].x, walk_way_store_1[i].y);//背景图
    }
    //放置地板
    return;
}

/*----------------------------------
--------------------------------------------------------------------地图一函数----------------------------------
--------------------------------*/


/*----------------------------------
--------------------------------------------------------------------地图二函数----------------------------------
--------------------------------*/
void Map_Two::input_background()//放置背景图
{
    auto background = Sprite::create("map\\map_two.png");
    this->addChild(background);
    background->setPosition(background_wide / 2, background_high / 2);//背景图
}

void Map_Two::input_walk_way()
{
    Vec2 current = walk_way_begin_2;
    walk_way_store_2.push_back(current);//放好初始位置
    for (int i = 0; i < 4; i++)
    {
        current.x += way_size;
        walk_way_store_2.push_back(current);
    }//水平向右4格

    for (int i = 0; i < 5; i++)
    {
        current.y += way_size;
        walk_way_store_2.push_back(current);
    }//竖直向上5格

    for (int i = 0; i < 3; i++)
    {
        current.x += way_size;
        walk_way_store_2.push_back(current);
    }//水平向右3格

    for (int i = 0; i < 5; i++)
    {
        current.y -= way_size;
        walk_way_store_2.push_back(current);
    }//竖直向下5格

    for (int i = 0; i < 4; i++)
    {
        current.x += way_size;
        walk_way_store_2.push_back(current);
    }//水平向右4格
     //存放地板向量生成完毕


    for (int i = 0; i < walk_way_store_2.size(); i++)
    {
        auto walk_way = Sprite::create("way.png");
        this->addChild(walk_way);
        walk_way->setPosition(walk_way_store_2[i].x, walk_way_store_2[i].y);//背景图
    }
    //放置地板
    return;
   
}

/*----------------------------------
--------------------------------------------------------------------地图二函数----------------------------------
--------------------------------*/


/*----------------------------------
--------------------------------------------------------------------地图三函数----------------------------------
--------------------------------*/
void Map_Three::input_background()
{
    auto background = Sprite::create("map\\map_three.png");
    this->addChild(background);
    background->setPosition(background_wide / 2, background_high / 2);//背景图
}

void Map_Three::input_walk_way()
{
    Vec2 current = walk_way_begin_3;
    walk_way_store_3.push_back(current);//放好初始位置

    for (int i = 0; i < 9; i++)
    {
        current.x += way_size;
        walk_way_store_3.push_back(current);//放好初始位置
    }//向右9格

    for (int i = 0; i < 3; i++)
    {
        current.y -= way_size;
        walk_way_store_3.push_back(current);//放好初始位置
    }//向下3格

    for (int i = 0; i < 9; i++)
    {
        current.x -= way_size;
        walk_way_store_3.push_back(current);//放好初始位置
    }//向左9格

    for (int i = 0; i < 3; i++)
    {
        current.y -= way_size;
        walk_way_store_3.push_back(current);//放好初始位置
    }//向下3格

    for (int i = 0; i < 9; i++)
    {
        current.x += way_size;
        walk_way_store_3.push_back(current);//放好初始位置
    }//向右9格
    //存放地板向量生成完毕

    for (int i = 0; i < walk_way_store_3.size(); i++)
    {
        auto walk_way = Sprite::create("way.png");
        this->addChild(walk_way);
        walk_way->setPosition(walk_way_store_3[i].x, walk_way_store_3[i].y);//背景图
    }
    //放置地板
    return;
}
/*----------------------------------
--------------------------------------------------------------------地图三函数----------------------------------
--------------------------------*/