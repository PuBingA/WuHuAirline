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

bool choose_map::init()//�������ֺ���,��Ҫ����
{
    if (!Scene::init())
    {
        return false;
    }

    auto visibleSize = Director::getInstance()->getVisibleSize();//��ȡ�ɼ���С
    Vec2 origin = Director::getInstance()->getVisibleOrigin();//��ȡopengl���


    auto choose_map_background = Sprite::create("choose_map_background.png");
    this->addChild(choose_map_background);
    choose_map_background->setPosition(background_wide / 2, background_high / 2);//���ɱ���ͼ






    auto back_item = MenuItemImage::create("CloseNormal.png", "CloseSelected.png", CC_CALLBACK_1(choose_map::menuCallback, this, back));
    auto back_menu = Menu::create(back_item, NULL);
    back_menu->setPosition(1200, 70);
    this->addChild(back_menu);//���ɹرղ˵�ͼ��

    auto choose_map_1 = MenuItemImage::create("choose_map_1.png", "choose_map_1_selected.png", CC_CALLBACK_1(choose_map::menuCallback, this, map1));
    auto map_1_menu = Menu::create(choose_map_1, NULL);
    map_1_menu->setPosition(background_wide / 2-300, background_high / 2);
    this->addChild(map_1_menu);//���ɵ�ͼ1ѡ��˵�

    auto choose_map_2 = MenuItemImage::create("choose_map_2.png", "choose_map_2_selected.png", CC_CALLBACK_1(choose_map::menuCallback, this, map2));
    auto map_2_menu = Menu::create(choose_map_2, NULL);
    map_2_menu->setPosition(background_wide / 2 , background_high / 2);
    this->addChild(map_2_menu);//���ɵ�ͼ2ѡ��˵�

    auto choose_map_3 = MenuItemImage::create("choose_map_3.png", "choose_map_3_selected.png", CC_CALLBACK_1(choose_map::menuCallback, this, map3));
    auto map_3_menu = Menu::create(choose_map_3, NULL);
    map_3_menu->setPosition(background_wide / 2+300, background_high / 2);
    this->addChild(map_3_menu);//���ɵ�ͼ2ѡ��˵�
 

}


void choose_map::menuCallback(cocos2d::Ref* pSender, choose_scene_2 choose_map)
{
    if (choose_map == back)
    {
        auto scene = Opening::create();//���ɳ�ʼ����
        Director::getInstance()->replaceScene(scene);//�л�����
    }//���ؿ�ʼ����

    if (choose_map == map1)
    {
  
    }//�����ͼ1
}