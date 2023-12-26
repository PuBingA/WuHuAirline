#include"settlement_interface.h"
#include"choose_map.h"
#include"AudioEngine.h"
USING_NS_CC;

/*-------------------------���ೡ��-------------------------*/
bool settlement::init()
{
    if (!Scene::init())
        return false;


    auto visibleSize = Director::getInstance()->getVisibleSize();//��ȡ�ɼ���С
    Vec2 origin = Director::getInstance()->getVisibleOrigin();//��ȡopengl���

    AudioEngine::pauseAll();
    music = AudioEngine::play2d(music_name, false);//��������

    auto background_picture = Sprite::create(background);
    this->addChild(background_picture);
    background_picture->setPosition(background_wide / 2 + 60, background_high / 2);//���ñ���ͼ

    Color3B color(255, 0, 0);
    auto label = Label::createWithTTF(label_content, "fonts\\Marker Felt.ttf", 80);
    label->setColor(color);
    this->addChild(label);
    label->setPosition(background_wide / 2, background_high / 2 + 200);//�����ı�


    auto left_picture = Sprite::create(left);
    left_picture->setPosition(background_wide / 2 - 400, background_high / 2);
    this->addChild(left_picture);

    auto right_picture = Sprite::create(right);
    right_picture->setPosition(background_wide / 2 + 400, background_high / 2);
    this->addChild(right_picture);//���ü�����

    input_menu();//���ò˵���ť
    return true;
}

/*-------------------------���ೡ��-------------------------*/

/*--------------------------ʤ������--------------------------------------*/
Scene* settlement_success::createScene()
{
    return settlement_success::create();
}

void settlement_success::input_menu()
{
    auto SuccessItem = MenuItemImage::create("win_continue.png", "win_continue_selected.png", CC_CALLBACK_1(settlement_success::menuCallback, this, music));//������л���ѡ���ͼ����
    auto menu = Menu::create(SuccessItem, NULL);
    this->addChild(menu);
    menu->setPosition(background_wide / 2, background_high / 2 - 200);//���ò˵�
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

void settlement_failure::input_menu()
{
    auto failureItem = MenuItemImage::create("win_continue.png", "win_continue_selected.png", CC_CALLBACK_1(settlement_failure::menuCallback, this, music));//������л���ѡ���ͼ����
    auto menu = Menu::create(failureItem, NULL);
    this->addChild(menu);
    menu->setPosition(background_wide / 2, background_high / 2 - 200);//���ò˵�
}

void settlement_failure::menuCallback(cocos2d::Ref* pSender, int& music)
{
    AudioEngine::resumeAll();
    AudioEngine::stop(music);
    Director::getInstance()->replaceScene(choose_map::createScene());
}
/*--------------------------ʧ�ܳ���----------------------------------------*/



/*--------------------------��ͣ����----------------------------------------*/
Scene* settlement_pause::createScene()
{
    return settlement_pause::create();
}

void settlement_pause::input_menu()
{
    auto pauseItem = MenuItemImage::create("win_continue.png", "win_continue_selected.png", CC_CALLBACK_1(settlement_pause::menuCallback, this, music));//������л���ѡ���ͼ����
    auto menu = Menu::create(pauseItem, NULL);
    this->addChild(menu);
    menu->setPosition(background_wide / 2, background_high / 2 - 200);//���ò˵�
}

void settlement_pause::menuCallback(cocos2d::Ref* pSender, int& music)
{
    AudioEngine::resumeAll();
    AudioEngine::stop(music);
    Director::getInstance()->popScene();
}
/*--------------------------��ͣ����----------------------------------------*/