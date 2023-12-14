#include"choose_map.h"
#include "OpeningScene.h"
#include<string>
#include<vector>
#include "AudioEngine.h"
USING_NS_CC;
using namespace std;

Scene* Opening::createScene()
{
    return Opening::create();
}

// Print useful error message instead of segfaulting when files are not there.
static void problemLoading(const char* filename)
{
    printf("Error while loading: %s\n", filename);
    printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in HelloWorldScene.cpp\n");
}

// on "init" you need to initialize your instance

bool Opening::init()//�������ֺ���,��Ҫ����
{
    if ( !Scene::init() )
    {
        return false;
    }

    auto visibleSize = Director::getInstance()->getVisibleSize();//��ȡ�ɼ���С
    Vec2 origin = Director::getInstance()->getVisibleOrigin();//��ȡopengl���

  

    /*----�Լ���ӵ�---*/
    auto opening_background = Sprite::create("opening_background.png");
    this->addChild(opening_background);
    opening_background->setPosition(Vec2(1235 / 2, 694 / 2));//����ͼ

    /*-------------������Ա��ǩ--------------------*/
    vector<Label*>group_member;
    string input_name[4] =
    { "Group Member:",
        "Chen Fu Bing",
    "Zhou Zhi Yuan",
        "Wang Zhi"
    };
    for (int i = 0; i < 4; i++)
    {
        Label* current_label=Label::createWithTTF(input_name[i], "fonts\\Marker Felt.ttf", 40);
        group_member.push_back(current_label);
        label_output(group_member[i], 1100, 200 - 50 * i);
    }//3����Ա�����4��
    /*-------------������Ա��ǩ--------------------*/

   /*----------------�˵�----------------------------*/
        auto openItem = MenuItemImage::create("menu\\game_begin.png", "menu\\game_begin_select.png", CC_CALLBACK_1(Opening::menuCallback, this,begining));//������л���ѡ���ͼ����
        auto endingItem = MenuItemImage::create("menu\\game_ending.png", "menu\\game_ending_select.png", CC_CALLBACK_1(Opening::menuCallback, this,close));//��������óɽ�������
        auto menu = Menu::create(openItem,NULL);
        auto menu2 = Menu::create(endingItem, NULL);
        this->addChild(menu);
        this->addChild(menu2);
        menu->setPosition(1235 / 2-200, 100);
        menu2->setPosition(1235 / 2 + 200, 100);//�˵��������
       /*----------------�˵�----------------------------*/


        /*------------����----------------*/
        auto background_music = AudioEngine::play2d("", true);
        /*------------����----------------*/

     /*----�Լ���ӵ�---*/
    return true;
}


void Opening::menuCallback(Ref* pSender, const choose_scene opening_menu)
{
    if(opening_menu==close)
    Director::getInstance()->end();//��������
    if (opening_menu == begining)
    {
        Director::getInstance()->replaceScene(choose_map::createScene());//�л�����
    }
}

/*--------------�����ǩ����-----------------*/
template<class T, class K>
void Opening::label_output(cocos2d::Label* my_label, T wide, K high)
{
    my_label->enableShadow();
    my_label->enableGlow(Color4B::YELLOW);//�����ֻ�ɫ��Ӱ
    my_label->setPosition(wide,high);//�ƶ���ǩλ��
    this->addChild(my_label);
}
/*--------------�����ǩ����-----------------*/

