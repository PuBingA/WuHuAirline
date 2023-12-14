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

/*-------------------构建场景函数--------------------*/
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


/*-------------------构建场景函数--------------------*/

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
    for (int i = 0; i < 6; i++)
    {
        walk_way_store_x.push_back(walk_way_begin_x);
        walk_way_store_y.push_back(walk_way_begin_y - i * way_size);
    }//竖直向下

    for (int i = 0; i < 10; i++)
    {
        walk_way_store_x.push_back(walk_way_begin_x + i * way_size);
        walk_way_store_y.push_back(walk_way_begin_y - 5 * way_size);
    }//水平向右

    for (int i = 0; i < 6; i++)
    {
        walk_way_store_x.push_back(walk_way_begin_x + 9 * way_size);
        walk_way_store_y.push_back(walk_way_begin_y + (i - 5) * way_size);
    }//竖直向上
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