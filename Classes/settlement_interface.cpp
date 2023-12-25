#include"settlement_interface.h"
#include"choose_map.h"
#include"AudioEngine.h"
USING_NS_CC;




/*--------------------------ʤ������--------------------------------------*/
Scene* settlement_success::createScene()
{
    return settlement_success::create();
}

static void problemLoading(const char* filename)
{
    printf("Error while loading: %s\n", filename);
    printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in HelloWorldScene.cpp\n");
}

bool settlement_success::init()//�������ֺ���,��Ҫ����
{
    if (!Scene::init())
        return false;


    auto visibleSize = Director::getInstance()->getVisibleSize();//��ȡ�ɼ���С
    Vec2 origin = Director::getInstance()->getVisibleOrigin();//��ȡopengl���



    AudioEngine::pauseAll();
    music = AudioEngine::play2d("success.mp3", false);
  

    auto success_background = Sprite::create("success.png");
    this->addChild(success_background);
    success_background->setPosition(background_wide/2+60, background_high/2);

    Color3B color(0, 0, 255);
    auto success_label = Label::createWithTTF("You Win!", "fonts\\Marker Felt.ttf", 80);
    success_label->setColor(color);
    this->addChild(success_label);
    success_label->setPosition(background_wide / 2, background_high / 2 + 200);//�����ı�


    auto left = Sprite::create("success_1.png");
    left->setPosition(background_wide / 2-400, background_high / 2);
    this->addChild(left);

    auto right = Sprite::create("success_2.png");
    right->setPosition(background_wide / 2 + 400, background_high / 2);
    this->addChild(right);//���ü�����

    auto SuccessItem = MenuItemImage::create("win_continue.png", "win_continue_selected.png", CC_CALLBACK_1(settlement_success::menuCallback, this, music));//������л���ѡ���ͼ����
    auto menu = Menu::create(SuccessItem, NULL);
    this->addChild(menu);
    menu->setPosition(background_wide / 2, background_high / 2 - 200);//���ò˵�
    return true;
}

void settlement_success::menuCallback(cocos2d::Ref* pSender,int &music)
{
    AudioEngine::resumeAll();
    AudioEngine::stop(music);
    Director::getInstance()->replaceScene(choose_map::createScene());
}

/*--------------------------ʤ������--------------------------------------*/

/*--------------------------ʧ�ܳ���----------------------------------------*/
Scene* settlement_failure::createScene()
{
    return settlement_failure::create();
}

bool settlement_failure::init()//�������ֺ���,��Ҫ����
{
    if (!Scene::init())
        return false;


    AudioEngine::pauseAll();
    music = AudioEngine::play2d("failure.mp3", false);

    auto failure_background = Sprite::create("success.png");
    this->addChild(failure_background);
    failure_background->setPosition(background_wide / 2 + 60, background_high / 2);//���ñ���ͼƬ

    Color3B color(255, 0, 0);
    auto success_label = Label::createWithTTF("You Lose!", "fonts\\Marker Felt.ttf", 80);
    success_label->setColor(color);
    this->addChild(success_label);
    success_label->setPosition(background_wide / 2, background_high / 2 + 200);//�����ı�


    auto left = Sprite::create("failure_1.png");
    left->setPosition(background_wide / 2 - 400, background_high / 2);
    this->addChild(left);

    auto right = Sprite::create("failure_2.png");
    right->setPosition(background_wide / 2 + 400, background_high / 2);
    this->addChild(right);//���ü�����

    auto failureItem = MenuItemImage::create("win_continue.png", "win_continue_selected.png", CC_CALLBACK_1(settlement_failure::menuCallback, this,music));//������л���ѡ���ͼ����
    auto menu = Menu::create(failureItem, NULL);
    this->addChild(menu);
    menu->setPosition(background_wide / 2, background_high / 2 - 200);//���ò˵�
    return true;
}

void settlement_failure::menuCallback(cocos2d::Ref* pSender, int& music)
{
    AudioEngine::resumeAll();
    AudioEngine::stop(music);
    Director::getInstance()->replaceScene(choose_map::createScene());
}
/*--------------------------ʧ�ܳ���----------------------------------------*/