#include"settlement_interface.h"
USING_NS_CC;
using namespace cocos2d;
/*--------------------------胜利场景--------------------------------------*/
Scene* settlement_success::createScene()
{
    return settlement_success::create();
}

static void problemLoading(const char* filename)
{
    printf("Error while loading: %s\n", filename);
    printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in HelloWorldScene.cpp\n");
}

bool settlement_success::init()//场景布局函数,重要函数
{
    if (!Scene::init())
        return false;

    auto visibleSize = Director::getInstance()->getVisibleSize();//获取可见大小
    Vec2 origin = Director::getInstance()->getVisibleOrigin();//获取opengl起点

    auto success_background = Sprite::create("success.png");
    this->addChild(success_background);
    success_background->setPosition(background_wide/2, background_high/2);

    auto success_label = Label::createWithTTF("You Win!", "fonts\\Marker Felt.ttf", 80);
    this->addChild(success_label);
    success_label->setPosition(background_wide / 2, background_high / 2 + 100);
    return true;
}

/*--------------------------胜利场景--------------------------------------*/