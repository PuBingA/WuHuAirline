#include"map.h"
#include"choose_map.h"
#include "monster.h"
#include"carrot.h"
#include "ui/CocosGUI.h"
#include"cocos-ext.h"
#include"settlement_interface.h"
USING_NS_CC;
using namespace std;

extern bool map_two_flag;
extern bool map_three_flag;
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
    input_gold_item();//���ý��
    game_begin();//��ʼ��Ϸ
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

void Map_father::input_gold_item()//��������ͼ��
{
   
    auto gold_item = Sprite::create("gold.png");//��������ͼ��
    this->addChild(gold_item);
    gold_item->setPosition(gold_x - 90, gold_y);
    //�ź�����ͼ��
}

cocos2d::Label* Map_father::input_gold()//���ɽ�ұ�ǩ
{
    auto gold_label = Label::createWithTTF("", "fonts\\Marker Felt.ttf", 56);
    Color3B gold_color(255, 233, 0);
    gold_label->setColor(gold_color);//���ɻ�ɫ
    this->addChild(gold_label);
    gold_label->setPosition(gold_x, gold_y);
    return gold_label;
}

string Map_father::calculate_gold(const int gold)
{
    int digit = 1000;//ǧλ
    string figure;
    for (int i = 0; i < 4; i++)
    {
        int k = (gold / digit) % 10;
        digit /= 10;
        figure.push_back(k + '0');
    }//�����ÿһλ�����֣������ַ�����
    return figure;
}

template<typename T>
cocos2d::Label* Map_father::HP_display(const T x, const T y)//�����ܲ�Ѫ������
{
    auto HP_label = Label::createWithTTF("", "fonts\\Marker Felt.ttf", 40);
    Color3B HP_color(255, 0, 0);
    HP_label->setColor(HP_color);//���ɺ�ɫ
    HP_label->setPosition(x, y);
    this->addChild(HP_label);//���ɺ�Ѫ����ǩ
    auto Hp_item = Sprite::create("carrot_HP.png");
    Hp_item->setPosition(x - 50, y);
    this -> addChild(Hp_item);//����Ѫ��ͼ��

    return HP_label;
}

std::string Map_father::calculate_HP(const int HP)//�����ܲ�Ѫ�������ַ���
{
    string figure;
    int digit = 10;//ʮλ
    for (int i = 0; i < 2; i++)
    {
        int k = (HP / digit) % 10;
        digit /= 10;
        figure += k + '0';
    }//�����ÿһλ�����֣������ַ�����
    return figure;
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

void Map_father::game_over_success(float dt)//��Ϸʤ��
{
     auto scene = settlement_success::createScene();
     Director::getInstance()->replaceScene(TransitionCrossFade::create(2.0f, scene));
    
}

void Map_father::game_over_failure(float dt)//��Ϸʧ��
{
    auto scene = settlement_failure::createScene();
    Director::getInstance()->replaceScene(TransitionCrossFade::create(2.0f, scene));

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

    //����һ������
        auto monster1 = MonSprite::create("monster1_1.png");
        this->addChild(monster1);
        MonCtrl Moncon1(monster1, 1, walk_way_store_1);
        Moncon1.spawn();

    return;
}



void Map_One::game_begin()//��Ϸ��ʼ����
{
    float carrot_x = walk_way_store_1[walk_way_store_1.size() - 1][0];
    float carrot_y = walk_way_store_1[walk_way_store_1.size() - 1][1];//�ܲ�����
    auto carrot = Carrot::create("carrot_level1_1.png");//�ܲ��������
    this->addChild(carrot);
    carrot->setPosition(carrot_x, carrot_y);
    //�����ܲ�
    auto carrot_HP = HP_display(carrot_x+120, carrot_y );//�����ܲ�Ѫ��
    carrot_HP->setString(calculate_HP(carrot->HP));//���ݵ�ǰѪ���������壬��ע�����ӡ�����Ѫ��ʱ���ǵ��������������壩


    static int gold = gold_1;//��ұ���
    auto gold_label = input_gold();;//���ɱ�ǩ
    gold_label->setString(calculate_gold(gold));//�������壬��ע�����ӡ����Ľ��ʱ���ǵ��������������壩

    carrot->HP = 0;
    carrot->change();
    carrot_HP->setString(calculate_HP(carrot->HP));//���ݵ�ǰѪ���������壬��ע�����ӡ�����Ѫ��ʱ���ǵ��������������壩

    if (carrot->if_dead())//�ܲ���������
        this->scheduleOnce(CC_SCHEDULE_SELECTOR(Map_father::game_over_failure), 1.0f);

    map_two_flag = true;
  

}

void Map_One::spawn_monster()//ˢ�¹���
{
    MonSprite* monster1 = MonSprite::create("monster1_1.png");
    this->addChild(monster1);
    MonCtrl Moncon1(monster1, 1, walk_way_store_1);
    Moncon1.spawn();

}
/*------------------------------��ͼһ����----------------------------------*/


/*------------------------------��ͼ������----------------------------------*/

void Map_Two::input_background()//���ñ���ͼ
{
    auto background = Sprite::create("map\\map_two.png");
    this->addChild(background);
    background->setPosition(background_wide / 2, background_high / 2);//����ͼ
}

void Map_Two::input_walk_way()//���ù���·��
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

void Map_Two::game_begin()//��Ϸ��ʼ����
{
    float carrot_x = walk_way_store_2[walk_way_store_2.size() - 1][0];
    float carrot_y = walk_way_store_2[walk_way_store_2.size() - 1][1];//�ܲ�����
    auto carrot = Carrot::create("carrot_level1_1.png");//�ܲ��������
    this->addChild(carrot);
    carrot->setPosition(carrot_x, carrot_y);
    //�����ܲ�
    auto carrot_HP = HP_display(carrot_x + 120, carrot_y);//�����ܲ�Ѫ��
    carrot_HP->setString(calculate_HP(carrot->HP));//���ݵ�ǰѪ���������壬��ע�����ӡ�����Ѫ��ʱ���ǵ��������������壩


    static int gold = gold_2;//��ұ���
    auto gold_label = input_gold();;//���ɱ�ǩ
    gold_label->setString(calculate_gold(gold));//�������壬��ע�����ӡ����Ľ��ʱ���ǵ��������������壩

    map_three_flag = true;

}

void Map_Two::spawn_monster()
{
    MonSprite* monster1 = MonSprite::create("monster1_1.png");
    this->addChild(monster1);
    MonCtrl Moncon1(monster1, 1, walk_way_store_2);
    Moncon1.spawn();

}

/*------------------------------��ͼ������----------------------------------*/


/*------------------------------��ͼ������----------------------------------*/
void Map_Three::input_background()//���ɱ���ͼ
{
    auto background = Sprite::create("map\\map_three.png");
    this->addChild(background);
    background->setPosition(background_wide / 2, background_high / 2);//����ͼ
}

void Map_Three::input_walk_way()//���ù���·��
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

void Map_Three::game_begin()//��Ϸ��ʼ����
{
    float carrot_x = walk_way_store_3[walk_way_store_3.size() - 1][0];
    float carrot_y = walk_way_store_3[walk_way_store_3.size() - 1][1];//�ܲ�����
    auto carrot = Carrot::create("carrot_level1_1.png");//�ܲ��������
    this->addChild(carrot);
    carrot->setPosition(carrot_x, carrot_y);
    //�����ܲ�
    auto carrot_HP = HP_display(carrot_x + 120, carrot_y);//�����ܲ�Ѫ��
    carrot_HP->setString(calculate_HP(carrot->HP));//���ݵ�ǰѪ���������壬��ע�����ӡ�����Ѫ��ʱ���ǵ��������������壩


    static int gold = gold_3;//��ұ���
    auto gold_label = input_gold();;//���ɱ�ǩ
    gold_label->setString(calculate_gold(gold));//�������壬��ע�����ӡ����Ľ��ʱ���ǵ��������������壩
}

void Map_Three::spawn_monster()
{
    MonSprite* monster1 = MonSprite::create("monster1_1.png");
    this->addChild(monster1);
    MonCtrl Moncon1(monster1, 1, walk_way_store_3);
    Moncon1.spawn();

}
/*------------------------------��ͼ������----------------------------------*/