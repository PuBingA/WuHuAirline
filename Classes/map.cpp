#include"map.h"
#include"choose_map.h"
#include "monster.h"
#include"carrot.h"
#include "ui/CocosGUI.h"
#include"cocos-ext.h"
USING_NS_CC;

/*-------------------------------���ຯ��-----------------------------------*/

cocos2d::Scene* Map_father::createScene()
{
    return Map_father::create();
}

static void problemLoading(const char* filename)
{
    printf("Error while loading: %s\n", filename);
    printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in HelloWorldScene.cpp\n");
}

bool Map_father::init()//���ഴ�������ܺ���
{
    static int gold = 4321;//��ʼ���
    if (!Scene::init())
        return false;

    auto visibleSize = Director::getInstance()->getVisibleSize();//��ȡ�ɼ���С
    Vec2 origin = Director::getInstance()->getVisibleOrigin();//��ȡopengl���

    input_background();//���ñ���ͼ
    input_walk_way();//���õذ�
    input_return_pause();//���÷��أ���ͣ��
    input_gold(gold);//���ý��
    input_carrot();//�����ܲ�
    spawn_monster();//���ɹ���
    return true;
}

void Map_father::input_return_pause()//���������ͣ�Լ����ؼ�����
{
    bool pause = false;
    auto return_menu = MenuItemImage::create("return.png", "return_selected.png", CC_CALLBACK_1(Map_father::menuCallback, this));
    auto menu = Menu::create(return_menu, NULL);
    this->addChild(menu);
    menu->setPosition(return_x, return_y);
    //���ؼ��������
    auto button = ui::Button::create("pause_1.png","pause_2.png");
    this->addChild(button);
    button->setPosition(Point(pause_x,pause_y));
    button->addClickEventListener(CC_CALLBACK_1(Map_father::buttonCallback, this));
    //��ͣ���������
    
}

void Map_father::input_gold(const int gold)//���ý�Һ���,������ɣ�
{
    int digit = 1000;
    std::string figure;
    for (int i = 0; i < 4; i++)
    {
        int k = (gold / digit) % 10;
        digit /= 10;
        figure.push_back(k + '0');
    }//�����ÿһλ�����֣������ַ�����
    auto gold_label = Label::createWithTTF(figure, "fonts\\Marker Felt.ttf",56);
    Color3B gold_color(255, 233, 0);
    gold_label->setColor(gold_color);//���ɻ�ɫ
    this->addChild(gold_label);
    gold_label->setPosition(Point(gold_x, gold_y));
    //�������ǩ�ź�

    auto gold_item = Sprite::create("gold.png");//��������ͼ��
    this->addChild(gold_item);
    gold_item->setPosition(gold_x - 90, gold_y);
    //�ź�����ͼ��

}

void Map_father::buttonCallback(cocos2d::Ref* pSender)//��ͣ����������
{
    if (!Director::getInstance()->isPaused())
    {
        Director::getInstance()->pause();
        AudioEngine::pauseAll();
    }//��ͣ
    else
    {
        Director::getInstance()->resume();
        AudioEngine::resumeAll();
    }//����
}

void Map_father::menuCallback(cocos2d::Ref* pSender)//���ؼ���������
{
    Director::getInstance()->replaceScene(choose_map::createScene());//�л���ѡ���ͼ����
}

template<typename T>
void Map_father::input_brick(T x, T y ,int choice)//choice==1 ���ù�����ɫ�ذ�
{
    if (choice == 1)
    {
        auto walk_way = Sprite::create("way.png");
        this->addChild(walk_way);
        walk_way->setPosition(x, y);//����ͼ
    }
}

/*-------------------------------���ຯ��-----------------------------------*/



/*------------------------------��ͼһ����----------------------------------*/

void Map_One::input_background()//���ñ���ͼ
{
    auto background = Sprite::create("map\\map_one.png");
    this->addChild(background);
    background->setPosition(background_wide / 2, background_high / 2);//����ͼ
}

void Map_One::input_walk_way()//���ù����н�·��
{
    std::vector<float> current = walk_way_begin_1;
    walk_way_store_1.push_back(current);//�źó�ʼλ��
    input_brick(current[0], current[1], 1);
    for (int i = 0; i < 5; i++)
    {
        current[1] -= way_size;
        input_brick(current[0], current[1], 1);
        walk_way_store_1.push_back(current);
    }//��ֱ����5��

    for (int i = 0; i < 9; i++)
    {
        current[0] += way_size;
        input_brick(current[0], current[1], 1);
        walk_way_store_1.push_back(current);
    }//ˮƽ����9��

    for (int i = 0; i < 5; i++)
    {
        current[1] += way_size;
        input_brick(current[0], current[1], 1);
        walk_way_store_1.push_back(current);
    }//��ֱ����5��
    //��ŵذ������������
    return;
}

void Map_One::input_carrot()//�����ܲ�����
{
    auto carrot = Carrot::create("carrot_level1_1.png");//����һ�������ܲ�
    this->addChild(carrot);
    carrot->setPosition(walk_way_store_1[walk_way_store_1.size() - 1][0], walk_way_store_1[walk_way_store_1.size() - 1][1]);
}

void Map_One::spawn_monster()
{
    auto wave1 = Node::create();
    MonsterSpawner wave1Spawn(wave1, walk_way_store_1, 1);
    this->addChild(wave1);
    wave1Spawn.spawn1(1.0f);
    /*
    wave1->scheduleUpdate();
    wave1->scheduleOnce(SEL_SCHEDULE(MonsterSpawner::spawn1), 10.0f);
    wave1->scheduleOnce(SEL_SCHEDULE(MonsterSpawner::spawn2), 11.0f);
    wave1->scheduleOnce(SEL_SCHEDULE(MonsterSpawner::spawn3), 12.0f);
    wave1->scheduleOnce(SEL_SCHEDULE(MonsterSpawner::spawn4), 13.0f);
    wave1->scheduleOnce(SEL_SCHEDULE(MonsterSpawner::spawn5), 13.0f);*/
}

/*------------------------------��ͼһ����----------------------------------*/


/*------------------------------��ͼ������----------------------------------*/

void Map_Two::input_background()//���ñ���ͼ
{
    auto background = Sprite::create("map\\map_two.png");
    this->addChild(background);
    background->setPosition(background_wide / 2, background_high / 2);//����ͼ
}

void Map_Two::input_walk_way()
{
    std::vector<float> current = walk_way_begin_2;
    walk_way_store_2.push_back(current);//�źó�ʼλ��
    input_brick(current[0], current[1], 1);
    for (int i = 0; i < 4; i++)
    {
        current[0] += way_size;
        input_brick(current[0], current[1], 1);
        walk_way_store_2.push_back(current);
    }//ˮƽ����4��

    for (int i = 0; i < 5; i++)
    {
        current[1] += way_size;
        input_brick(current[0], current[1], 1);
        walk_way_store_2.push_back(current);
    }//��ֱ����5��

    for (int i = 0; i < 3; i++)
    {
        current[0] += way_size;
        input_brick(current[0], current[1], 1);
        walk_way_store_2.push_back(current);
    }//ˮƽ����3��

    for (int i = 0; i < 5; i++)
    {
        current[1] -= way_size;
        input_brick(current[0], current[1], 1);
        walk_way_store_2.push_back(current);
    }//��ֱ����5��

    for (int i = 0; i < 4; i++)
    {
        current[0] += way_size;
        input_brick(current[0], current[1], 1);
        walk_way_store_2.push_back(current);
    }//ˮƽ����4��
     //��ŵذ������������
    return;

}

void Map_Two::input_carrot()//�����ܲ�����
{
    auto carrot = Carrot::create("carrot_level1_1.png");//����һ�������ܲ�
    this->addChild(carrot);
    carrot->setPosition(walk_way_store_2[walk_way_store_2.size() - 1][0], walk_way_store_2[walk_way_store_2.size() - 1][1]);
}

void Map_Two::spawn_monster()
{
}

/*------------------------------��ͼ������----------------------------------*/


/*------------------------------��ͼ������----------------------------------*/
void Map_Three::input_background()
{
    auto background = Sprite::create("map\\map_three.png");
    this->addChild(background);
    background->setPosition(background_wide / 2, background_high / 2);//����ͼ
}

void Map_Three::input_walk_way()
{
    std::vector<float> current = walk_way_begin_3;
    walk_way_store_3.push_back(current);//�źó�ʼλ��
    input_brick(current[0], current[1], 1);
    for (int i = 0; i < 9; i++)
    {
        current[0] += way_size;
        input_brick(current[0], current[1], 1);
        walk_way_store_3.push_back(current);//�źó�ʼλ��
    }//����9��
    for (int i = 0; i < 3; i++)
    {
        current[1] -= way_size;
        input_brick(current[0], current[1], 1);
        walk_way_store_3.push_back(current);//�źó�ʼλ��
    }//����3��
    for (int i = 0; i < 9; i++)
    {
        current[0] -= way_size;
        input_brick(current[0], current[1], 1);
        walk_way_store_3.push_back(current);//�źó�ʼλ��
    }//����9��
    for (int i = 0; i < 3; i++)
    {
        current[1] -= way_size;
        input_brick(current[0], current[1], 1);
        walk_way_store_3.push_back(current);//�źó�ʼλ��
    }//����3��
    for (int i = 0; i < 9; i++)
    {
        current[0] += way_size;
        input_brick(current[0], current[1], 1);
        walk_way_store_3.push_back(current);//�źó�ʼλ��
    }//����9��
    //��ŵذ������������
    return;
}

void Map_Three::input_carrot()//�����ܲ�����
{
    auto carrot = Carrot::create("carrot_level1_1.png");//����һ�������ܲ�
    this->addChild(carrot);
    carrot->setPosition(walk_way_store_3[walk_way_store_3.size() - 1][0], walk_way_store_3[walk_way_store_3.size() - 1][1]);
}

void Map_Three::spawn_monster()
{
}

/*------------------------------��ͼ������----------------------------------*/