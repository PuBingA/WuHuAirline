#include"map.h"
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

bool Map_father::init()
{
    if (!Scene::init())
    {
        return false;
    }

    auto visibleSize = Director::getInstance()->getVisibleSize();//获取可见大小
    Vec2 origin = Director::getInstance()->getVisibleOrigin();//获取opengl起点

    input_background();//放置背景图
    input_walk_way();//放置地板
    return true;
}


/*----------------------------------
--------------------------------------------------------------------父类函数----------------------------------
--------------------------------*/






/*----------------------------------
--------------------------------------------------------------------地图一函数----------------------------------
--------------------------------*/

void Map_One::input_background()//放置背景图
{
    auto bakcground = Sprite::create("map\\map_one.png");
    this->addChild(bakcground);
    bakcground->setPosition(background_wide / 2, background_high / 2);//背景图
}

void Map_One::input_walk_way()//放置怪物行进路径
{

    int x = walk_way_begin_x;
    int y = walk_way_begin_y;
    walk_way_store_x.push_back(x);
    walk_way_store_y.push_back(y);//放好初始位置
    for (int i = 0; i < 5; i++)
    {
        y -= way_size;
        walk_way_store_x.push_back(x);
        walk_way_store_y.push_back(y);
    }//竖直向下5格

    for (int i = 0; i < 9; i++)
    {
        x += way_size;
        walk_way_store_x.push_back(x);
        walk_way_store_y.push_back(y);
    }//水平向右9格

    for (int i = 0; i < 5; i++)
    {
        y += way_size;
        walk_way_store_x.push_back(x);
        walk_way_store_y.push_back(y);
    }//竖直向上5格
    //存放地板向量生成完毕

    for (int i = 0; i < walk_way_store_x.size(); i++)
    {
        auto walk_way = Sprite::create("way.png");
        this->addChild(walk_way);
        walk_way->setPosition(walk_way_store_x[i], walk_way_store_y[i]);//背景图
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

    auto bakcground = Sprite::create("map\\map_two.png");
    this->addChild(bakcground);
    bakcground->setPosition(background_wide / 2, background_high / 2);//背景图
}

void Map_Two::input_walk_way()
{
    int x = two_walk_way_begin_x;
    int y = two_walk_way_begin_y;
    walk_way_store_x.push_back(x);
    walk_way_store_y.push_back(y);//放好初始位置
    for (int i = 0; i < 4; i++)
    {
        x += way_size;
        walk_way_store_x.push_back(x);
        walk_way_store_y.push_back(y);
    }//水平向右4格

    for (int i = 0; i < 5; i++)
    {
        y += way_size;
        walk_way_store_x.push_back(x);
        walk_way_store_y.push_back(y);
    }//竖直向上5格

    for (int i = 0; i < 3; i++)
    {
        x += way_size;
        walk_way_store_x.push_back(x);
        walk_way_store_y.push_back(y);
    }//水平向右3格

    for (int i = 0; i < 5; i++)
    {
        y -= way_size;
        walk_way_store_x.push_back(x);
        walk_way_store_y.push_back(y);
    }//竖直向下5格

    for (int i = 0; i < 4; i++)
    {
        x += way_size;
        walk_way_store_x.push_back(x);
        walk_way_store_y.push_back(y);
    }//水平向右4格
     //存放地板向量生成完毕


    for (int i = 0; i < walk_way_store_x.size(); i++)
    {
        auto walk_way = Sprite::create("way.png");
        this->addChild(walk_way);
        walk_way->setPosition(walk_way_store_x[i], walk_way_store_y[i]);//背景图
    }
    //放置地板
    return;
   
}

/*----------------------------------
--------------------------------------------------------------------地图二函数----------------------------------
--------------------------------*/