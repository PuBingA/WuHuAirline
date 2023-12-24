#include"settlement_interface.h"
#include"choose_map.h"
#include"AudioEngine.h"
USING_NS_CC;

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
    success_background->setPosition(background_wide/2+60, background_high/2);

    Color3B color(0, 0, 255);
    auto success_label = Label::createWithTTF("You Win!", "fonts\\Marker Felt.ttf", 80);
    success_label->setColor(color);
    this->addChild(success_label);
    success_label->setPosition(background_wide / 2, background_high / 2 + 200);//放置文本


    auto left = Sprite::create("success_1.png");
    left->setPosition(background_wide / 2-400, background_high / 2);
    this->addChild(left);

    auto right = Sprite::create("success_2.png");
    right->setPosition(background_wide / 2 + 400, background_high / 2);
    this->addChild(right);//放置吉祥物

    auto SuccessItem = MenuItemImage::create("win_continue.png", "win_continue_selected.png", CC_CALLBACK_1(settlement_success::menuCallback, this));//点击则切换到选择地图场景
    auto menu = Menu::create(SuccessItem, NULL);
    this->addChild(menu);
    menu->setPosition(background_wide / 2, background_high / 2 - 200);//放置菜单
    return true;
}

void settlement_success::menuCallback(cocos2d::Ref* pSender)
{
    Director::getInstance()->replaceScene(choose_map::createScene());
}

/*--------------------------胜利场景--------------------------------------*/

/*--------------------------失败场景----------------------------------------*/
Scene* settlement_failure::createScene()
{
    return settlement_failure::create();
}

bool settlement_failure::init()//场景布局函数,重要函数
{
    if (!Scene::init())
        return false;

    auto failure_background = Sprite::create("success.png");
    this->addChild(failure_background);
    failure_background->setPosition(background_wide / 2 + 60, background_high / 2);//放置背景图片

    Color3B color(255, 0, 0);
    auto success_label = Label::createWithTTF("You Lose!", "fonts\\Marker Felt.ttf", 80);
    success_label->setColor(color);
    this->addChild(success_label);
    success_label->setPosition(background_wide / 2, background_high / 2 + 200);//放置文本


    auto left = Sprite::create("failure_1.png");
    left->setPosition(background_wide / 2 - 400, background_high / 2);
    this->addChild(left);

    auto right = Sprite::create("failure_2.png");
    right->setPosition(background_wide / 2 + 400, background_high / 2);
    this->addChild(right);//放置吉祥物

    auto failureItem = MenuItemImage::create("win_continue.png", "win_continue_selected.png", CC_CALLBACK_1(settlement_failure::menuCallback, this));//点击则切换到选择地图场景
    auto menu = Menu::create(failureItem, NULL);
    this->addChild(menu);
    menu->setPosition(background_wide / 2, background_high / 2 - 200);//放置菜单
    return true;
}

void settlement_failure::menuCallback(cocos2d::Ref* pSender)
{
    Director::getInstance()->replaceScene(choose_map::createScene());
}
/*--------------------------失败场景----------------------------------------*/