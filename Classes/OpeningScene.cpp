
#include "OpeningScene.h"
#include<string>
#include<vector>
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
bool Opening::init()//场景布局函数
{
    if ( !Scene::init() )
    {
        return false;
    }

    auto visibleSize = Director::getInstance()->getVisibleSize();//获取可见大小
    Vec2 origin = Director::getInstance()->getVisibleOrigin();//获取opengl起点

  

    /*----自己添加的---*/
    auto opening_background = Sprite::create("opening_background.png");
    this->addChild(opening_background);
    opening_background->setPosition(Vec2(1235 / 2, 694 / 2));//背景图

    /*-------------开发人员标签--------------------*/
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
    }//3个成员，输出4行
    /*-------------开发人员标签--------------------*/

   
        auto openItem = MenuItemImage::create("menu\\game_begin.png", "game_begin_select.png", CC_CALLBACK_1(Opening::menuCloseCallback, this));
        auto endingItem = MenuItemImage::create("menu\\game_ending.png", "game_ending_select.png", CC_CALLBACK_1(Opening::menuCloseCallback, this));
        auto menu = Menu::create(openItem,NULL);
        auto menu2 = Menu::create(endingItem, NULL);
        this->addChild(menu);
        this->addChild(menu2);
        menu->setPosition(1235 / 2-200, 100);
        menu2->setPosition(1235 / 2 + 200, 100);
    


     /*----自己添加的---*/
    return true;
}


void Opening::menuCloseCallback(Ref* pSender)
{
    //Close the cocos2d-x game scene and quit the application
    Director::getInstance()->end();
    /*To navigate back to native iOS screen(if present) without quitting the application  ,do not use Director::getInstance()->end() as given above,instead trigger a custom event created in RootViewController.mm as below*/

    //EventCustom customEndEvent("game_scene_close_event");
    //_eventDispatcher->dispatchEvent(&customEndEvent);


}

/*--------------输出标签函数-----------------*/
void Opening::label_output(cocos2d::Label* my_label, float wide, float high)
{
    my_label->enableShadow();
    my_label->enableGlow(Color4B::YELLOW);
    my_label->setPosition(wide,high);
    this->addChild(my_label);
}

/*--------------输出标签函数-----------------*/

