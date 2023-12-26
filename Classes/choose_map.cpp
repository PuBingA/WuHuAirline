#include "choose_map.h"
#include"OpeningScene.h"
#include"map.h"
#include<string>
#include<vector>
USING_NS_CC;

extern int clear_stage;

cocos2d::Scene* choose_map::createScene()
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
        return false;

    auto visibleSize = Director::getInstance()->getVisibleSize();//��ȡ�ɼ���С
    Vec2 origin = Director::getInstance()->getVisibleOrigin();//��ȡopengl���


    auto choose_map_background = Sprite::create("choose_map_background.png");
    this->addChild(choose_map_background);
    choose_map_background->setPosition(background_wide / 2, background_high / 2);//���ɱ���ͼ

    auto choose_label=Label::createWithTTF("Choose the map!", "fonts\\Marker Felt.ttf", 70);
    Color3B color(0, 255, 0);//���ɺ�ɫ����
    choose_label->setColor(color);
    choose_label->setPosition(background_wide / 2, background_high / 2-200);
    this->addChild(choose_label);//���ñ�ǩ


    auto back_item = MenuItemImage::create("CloseNormal.png", "CloseSelected.png", CC_CALLBACK_1(choose_map::menuCallback, this, back));
    auto back_menu = Menu::create(back_item, NULL);
    back_menu->setPosition(1200, 70);
    this->addChild(back_menu);//���ɹرղ˵�ͼ��

    auto choose_map_1 = MenuItemImage::create("choose_map_1.png", "choose_map_1_selected.png", CC_CALLBACK_1(choose_map::menuCallback, this, map1));
    auto map_1_menu = Menu::create(choose_map_1, NULL);
    map_1_menu->setPosition(background_wide / 2-300, background_high / 2);
    this->addChild(map_1_menu);//���ɵ�ͼ1ѡ��˵�

    if (clear_stage>=2)//ͨ�ص�1�ز����ɰ�ť
    {
        auto choose_map_2 = MenuItemImage::create("choose_map_2.png", "choose_map_2_selected.png", CC_CALLBACK_1(choose_map::menuCallback, this, map2));
        auto map_2_menu = Menu::create(choose_map_2, NULL);
        map_2_menu->setPosition(background_wide / 2, background_high / 2);
        this->addChild(map_2_menu);//���ɵ�ͼ2ѡ��˵�
    }

    else
    {
        auto disable_2 = Sprite::create("choose_map_2_disable.png");
        disable_2->setPosition(background_wide / 2, background_high / 2);
        this->addChild(disable_2);//������ͼ

        auto disable_label = Label::createWithTTF("LOCK", "fonts\\Marker Felt.ttf", 40);
        disable_label->setColor(color);//���ɺ�ɫ
        disable_label->setPosition(background_wide / 2, background_high / 2-80);
        this->addChild(disable_label);//���ñ�ǩ
    }

    if (clear_stage>=3)//ͨ�ص�2�ز����ɰ�ť
    {
        auto choose_map_3 = MenuItemImage::create("choose_map_3.png", "choose_map_3_selected.png", CC_CALLBACK_1(choose_map::menuCallback, this, map3));
        auto map_3_menu = Menu::create(choose_map_3, NULL);
        map_3_menu->setPosition(background_wide / 2 + 300, background_high / 2);
        this->addChild(map_3_menu);//���ɵ�ͼ3ѡ��˵�
    }

    else
    {
        auto disable_3 = Sprite::create("choose_map_3_disable.png");
        disable_3->setPosition(background_wide / 2 + 300, background_high / 2);
        this->addChild(disable_3);//������ͼ

        auto disable_label = Label::createWithTTF("LOCK", "fonts\\Marker Felt.ttf", 40);
        disable_label->setColor(color);//���ɺ�ɫ
        disable_label->setPosition(background_wide / 2 + 300, background_high / 2 - 80);
        this->addChild(disable_label);//���ñ�ǩ
    }
    return true;
}


void choose_map::menuCallback(cocos2d::Ref* pSender, choose_scene_2 choose_map)
{
    if (choose_map == back)
        Director::getInstance()->replaceScene(Opening::create());//�л�����,���ؿ�ʼ����
    if (choose_map == map1)
        Director::getInstance()->replaceScene(Map_One::create());//�л�����,�����ͼ1
    if (choose_map == map2)
        Director::getInstance()->replaceScene(Map_Two::create());//�����ͼ2
    if (choose_map == map3)
        Director::getInstance()->replaceScene(Map_Three::create());//�����ͼ3
        ;//�����ͼ3
}

void choose_map::map_error()//�ؿ�ѡ�񱨴���,δ���
{
    Vector<MenuItem*> MenuItems;
    auto error_report_label = Label::createWithTTF("�ùؿ�δ������","fonts\\arial.ttf", 40);
    auto error_report = MenuItemLabel::create(error_report_label);
    MenuItems.pushBack(error_report);//���ı�����˵�
}