#include "choose_map.h"
#include"OpeningScene.h"
#include<string>
#include<vector>
USING_NS_CC;
using namespace std;



Scene* choose_map::createScene()
{
    return choose_map::create();
}

static void problemLoading(const char* filename)
{
    printf("Error while loading: %s\n", filename);
    printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in HelloWorldScene.cpp\n");
}

bool choose_map::init()//场景布局函数,重要函数
{
    if (!Scene::init())
        return false;

    auto visibleSize = Director::getInstance()->getVisibleSize();//获取可见大小
    Vec2 origin = Director::getInstance()->getVisibleOrigin();//获取opengl起点


    auto choose_map_background = Sprite::create("choose_map_background.png");
    this->addChild(choose_map_background);
    choose_map_background->setPosition(background_wide / 2, background_high / 2);//生成背景图


    auto back_item = MenuItemImage::create("CloseNormal.png", "CloseSelected.png", CC_CALLBACK_1(choose_map::menuCallback, this, back));
    auto back_menu = Menu::create(back_item, NULL);
    back_menu->setPosition(1200, 70);
    this->addChild(back_menu);//生成关闭菜单图像

    auto choose_map_1 = MenuItemImage::create("choose_map_1.png", "choose_map_1_selected.png", CC_CALLBACK_1(choose_map::menuCallback, this, map1));
    auto map_1_menu = Menu::create(choose_map_1, NULL);
    map_1_menu->setPosition(background_wide / 2-300, background_high / 2);
    this->addChild(map_1_menu);//生成地图1选择菜单

    auto choose_map_2 = MenuItemImage::create("choose_map_2.png", "choose_map_2_selected.png", CC_CALLBACK_1(choose_map::menuCallback, this, map2));
    auto map_2_menu = Menu::create(choose_map_2, NULL);
    map_2_menu->setPosition(background_wide / 2 , background_high / 2);
    this->addChild(map_2_menu);//生成地图2选择菜单

    auto choose_map_3 = MenuItemImage::create("choose_map_3.png", "choose_map_3_selected.png", CC_CALLBACK_1(choose_map::menuCallback, this, map3));
    auto map_3_menu = Menu::create(choose_map_3, NULL);
    map_3_menu->setPosition(background_wide / 2+300, background_high / 2);
    this->addChild(map_3_menu);//生成地图3选择菜单
}


void choose_map::menuCallback(cocos2d::Ref* pSender, choose_scene_2 choose_map)
{
    if (choose_map == back)
        Director::getInstance()->replaceScene(Opening::create());//切换场景,返回开始界面
    if (choose_map == map1)
        Director::getInstance()->replaceScene(Map_One::create());//切换场景,进入地图1
    if (choose_map == map2)
        ;//进入地图2
    if (choose_map == map3)
        ;//进入地图3
}