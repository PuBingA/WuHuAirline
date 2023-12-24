#include "choose_map.h"
#include"OpeningScene.h"
#include"map.h"
#include<string>
#include<vector>
USING_NS_CC;

extern bool map_two_flag ;//关卡二flag
extern bool map_three_flag ;//关卡三flag


cocos2d::Scene* choose_map::createScene()
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

    auto choose_label=Label::createWithTTF("Choose the map!", "fonts\\Marker Felt.ttf", 70);
    Color3B color(0, 255, 0);//生成红色字体
    choose_label->setColor(color);
    choose_label->setPosition(background_wide / 2, background_high / 2-200);
    this->addChild(choose_label);//放置标签


    auto back_item = MenuItemImage::create("CloseNormal.png", "CloseSelected.png", CC_CALLBACK_1(choose_map::menuCallback, this, back));
    auto back_menu = Menu::create(back_item, NULL);
    back_menu->setPosition(1200, 70);
    this->addChild(back_menu);//生成关闭菜单图像

    auto choose_map_1 = MenuItemImage::create("choose_map_1.png", "choose_map_1_selected.png", CC_CALLBACK_1(choose_map::menuCallback, this, map1));
    auto map_1_menu = Menu::create(choose_map_1, NULL);
    map_1_menu->setPosition(background_wide / 2-300, background_high / 2);
    this->addChild(map_1_menu);//生成地图1选择菜单

    if (map_two_flag)//通关第1关才生成按钮
    {
        auto choose_map_2 = MenuItemImage::create("choose_map_2.png", "choose_map_2_selected.png", CC_CALLBACK_1(choose_map::menuCallback, this, map2));
        auto map_2_menu = Menu::create(choose_map_2, NULL);
        map_2_menu->setPosition(background_wide / 2, background_high / 2);
        this->addChild(map_2_menu);//生成地图2选择菜单
    }

    else
    {
        auto disable_2 = Sprite::create("choose_map_2_disable.png");
        disable_2->setPosition(background_wide / 2, background_high / 2);
        this->addChild(disable_2);//放置贴图

        auto disable_label = Label::createWithTTF("LOCK", "fonts\\Marker Felt.ttf", 40);
        disable_label->setColor(color);//调成红色
        disable_label->setPosition(background_wide / 2, background_high / 2-80);
        this->addChild(disable_label);//放置标签
    }

    if (map_three_flag)//通关第2关才生成按钮
    {
        auto choose_map_3 = MenuItemImage::create("choose_map_3.png", "choose_map_3_selected.png", CC_CALLBACK_1(choose_map::menuCallback, this, map3));
        auto map_3_menu = Menu::create(choose_map_3, NULL);
        map_3_menu->setPosition(background_wide / 2 + 300, background_high / 2);
        this->addChild(map_3_menu);//生成地图3选择菜单
    }

    else
    {
        auto disable_3 = Sprite::create("choose_map_3_disable.png");
        disable_3->setPosition(background_wide / 2 + 300, background_high / 2);
        this->addChild(disable_3);//放置贴图

        auto disable_label = Label::createWithTTF("LOCK", "fonts\\Marker Felt.ttf", 40);
        disable_label->setColor(color);//调成红色
        disable_label->setPosition(background_wide / 2 + 300, background_high / 2 - 80);
        this->addChild(disable_label);//放置标签
    }
    return true;
}


void choose_map::menuCallback(cocos2d::Ref* pSender, choose_scene_2 choose_map)
{
    if (choose_map == back)
        Director::getInstance()->replaceScene(Opening::create());//切换场景,返回开始界面
    if (choose_map == map1)
        Director::getInstance()->replaceScene(Map_One::create());//切换场景,进入地图1
    if (choose_map == map2)
        Director::getInstance()->replaceScene(Map_Two::create());//进入地图2
    if (choose_map == map3)
        Director::getInstance()->replaceScene(Map_Three::create());//进入地图3
        ;//进入地图3
}

void choose_map::map_error()//关卡选择报错函数,未完成
{
    Vector<MenuItem*> MenuItems;
    auto error_report_label = Label::createWithTTF("该关卡未解锁！","fonts\\arial.ttf", 40);
    auto error_report = MenuItemLabel::create(error_report_label);
    MenuItems.pushBack(error_report);//将文本加入菜单
}