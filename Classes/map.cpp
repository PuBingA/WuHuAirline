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
    input_brick(x, y, 1);
    walk_way_store_x.push_back(x);
    walk_way_store_y.push_back(y);//放好初始位置
    for (int i = 0; i < 5; i++)
    {
        y -= way_size;
        input_brick(x,y,1);
    }//竖直向下5格
    walk_way_store_x.push_back(x);
    walk_way_store_y.push_back(y);//存放路径转折点

    for (int i = 0; i < 9; i++)
    {
        x += way_size;
        input_brick(x, y, 1);
    }//水平向右9格
    walk_way_store_x.push_back(x);
    walk_way_store_y.push_back(y);//存放路径转折点
    for (int i = 0; i < 5; i++)
    {
        y += way_size;
        input_brick(x, y, 1);
    }//竖直向上5格
    walk_way_store_x.push_back(x);
    walk_way_store_y.push_back(y);//存放路径转折点
    //存放地板向量生成完毕

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
    input_brick(x, y, 1);
    walk_way_store_x.push_back(x);
    walk_way_store_y.push_back(y);//放好初始位置
    for (int i = 0; i < 4; i++)
    {
        x += way_size;
        input_brick(x, y, 1);
    }//水平向右4格
    walk_way_store_x.push_back(x);
    walk_way_store_y.push_back(y);
    for (int i = 0; i < 5; i++)
    {
        y += way_size;
        input_brick(x, y, 1);
    }//竖直向上5格
    walk_way_store_x.push_back(x);
    walk_way_store_y.push_back(y);

    for (int i = 0; i < 3; i++)
    {
        x += way_size;
        input_brick(x, y, 1);
    }//水平向右3格
    walk_way_store_x.push_back(x);
    walk_way_store_y.push_back(y);
    for (int i = 0; i < 5; i++)
    {
        y -= way_size;
        input_brick(x, y, 1);

    }//竖直向下5格
    walk_way_store_x.push_back(x);
    walk_way_store_y.push_back(y);
    for (int i = 0; i < 4; i++)
    {
        x += way_size;
        input_brick(x, y, 1);
   
    }//水平向右4格
    walk_way_store_x.push_back(x);
    walk_way_store_y.push_back(y);
     //存放地板向量生成完毕

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
    auto bakcground = Sprite::create("map\\map_three.png");
    this->addChild(bakcground);
    bakcground->setPosition(background_wide / 2, background_high / 2);//背景图
}

void Map_Three::input_walk_way()
{
    int x = three_walk_way_begin_x;
    int y = three_walk_way_begin_y;
    input_brick(x, y, 1);
    walk_way_store_x.push_back(x);
    walk_way_store_y.push_back(y);//放好初始位置

    for (int i = 0; i <9; i++)
    {
        x += way_size;
        input_brick(x, y, 1);
 
    }//向右9格
    walk_way_store_x.push_back(x);
    walk_way_store_y.push_back(y);
    for (int i = 0; i < 3; i++)
    {
        y -= way_size;
        input_brick(x, y, 1);

    }//向下3格
    walk_way_store_x.push_back(x);
    walk_way_store_y.push_back(y);
    for (int i = 0; i < 9; i++)
    {
        x -= way_size;
        input_brick(x, y, 1);
  
    }//向左9格
    walk_way_store_x.push_back(x);
    walk_way_store_y.push_back(y);
    for (int i = 0; i < 3; i++)
    {
        y -= way_size;
        input_brick(x, y, 1);
  
    }//向下3格
    walk_way_store_x.push_back(x);
    walk_way_store_y.push_back(y);
    for (int i = 0; i < 9; i++)
    {
        x += way_size;
        input_brick(x, y, 1);

    }//向右9格
    walk_way_store_x.push_back(x);
    walk_way_store_y.push_back(y);
    //存放地板向量生成完毕

    return;
}
/*----------------------------------
--------------------------------------------------------------------地图三函数----------------------------------
--------------------------------*/