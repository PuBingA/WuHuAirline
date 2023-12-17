#include"map.h"
USING_NS_CC;
using namespace std;

/*----------------------------------
--------------------------------------------------------------------���ຯ��----------------------------------
--------------------------------*/
Scene* Map_father::createScene()
{
    return Map_father::create();
}

static void problemLoading(const char* filename)
{
    printf("Error while loading: %s\n", filename);
    printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in HelloWorldScene.cpp\n");
}

bool Map_father::init()
{
    if (!Scene::init())
    {
        return false;
    }

    auto visibleSize = Director::getInstance()->getVisibleSize();//��ȡ�ɼ���С
    Vec2 origin = Director::getInstance()->getVisibleOrigin();//��ȡopengl���

    input_background();//���ñ���ͼ
    input_walk_way();//���õذ�
    return true;
}


/*----------------------------------
--------------------------------------------------------------------���ຯ��----------------------------------
--------------------------------*/






/*----------------------------------
--------------------------------------------------------------------��ͼһ����----------------------------------
--------------------------------*/

void Map_One::input_background()//���ñ���ͼ
{
    auto bakcground = Sprite::create("map\\map_one.png");
    this->addChild(bakcground);
    bakcground->setPosition(background_wide / 2, background_high / 2);//����ͼ
}

void Map_One::input_walk_way()//���ù����н�·��
{

    int x = walk_way_begin_x;
    int y = walk_way_begin_y;
    walk_way_store_x.push_back(x);
    walk_way_store_y.push_back(y);//�źó�ʼλ��
    for (int i = 0; i < 5; i++)
    {
        y -= way_size;
        walk_way_store_x.push_back(x);
        walk_way_store_y.push_back(y);
    }//��ֱ����5��

    for (int i = 0; i < 9; i++)
    {
        x += way_size;
        walk_way_store_x.push_back(x);
        walk_way_store_y.push_back(y);
    }//ˮƽ����9��

    for (int i = 0; i < 5; i++)
    {
        y += way_size;
        walk_way_store_x.push_back(x);
        walk_way_store_y.push_back(y);
    }//��ֱ����5��
    //��ŵذ������������

    for (int i = 0; i < walk_way_store_x.size(); i++)
    {
        auto walk_way = Sprite::create("way.png");
        this->addChild(walk_way);
        walk_way->setPosition(walk_way_store_x[i], walk_way_store_y[i]);//����ͼ
    }
    //���õذ�
    return;
}

/*----------------------------------
--------------------------------------------------------------------��ͼһ����----------------------------------
--------------------------------*/


/*----------------------------------
--------------------------------------------------------------------��ͼ������----------------------------------
--------------------------------*/
void Map_Two::input_background()//���ñ���ͼ
{

    auto bakcground = Sprite::create("map\\map_two.png");
    this->addChild(bakcground);
    bakcground->setPosition(background_wide / 2, background_high / 2);//����ͼ
}

void Map_Two::input_walk_way()
{
    int x = two_walk_way_begin_x;
    int y = two_walk_way_begin_y;
    walk_way_store_x.push_back(x);
    walk_way_store_y.push_back(y);//�źó�ʼλ��
    for (int i = 0; i < 4; i++)
    {
        x += way_size;
        walk_way_store_x.push_back(x);
        walk_way_store_y.push_back(y);
    }//ˮƽ����4��

    for (int i = 0; i < 5; i++)
    {
        y += way_size;
        walk_way_store_x.push_back(x);
        walk_way_store_y.push_back(y);
    }//��ֱ����5��

    for (int i = 0; i < 3; i++)
    {
        x += way_size;
        walk_way_store_x.push_back(x);
        walk_way_store_y.push_back(y);
    }//ˮƽ����3��

    for (int i = 0; i < 5; i++)
    {
        y -= way_size;
        walk_way_store_x.push_back(x);
        walk_way_store_y.push_back(y);
    }//��ֱ����5��

    for (int i = 0; i < 4; i++)
    {
        x += way_size;
        walk_way_store_x.push_back(x);
        walk_way_store_y.push_back(y);
    }//ˮƽ����4��
     //��ŵذ������������


    for (int i = 0; i < walk_way_store_x.size(); i++)
    {
        auto walk_way = Sprite::create("way.png");
        this->addChild(walk_way);
        walk_way->setPosition(walk_way_store_x[i], walk_way_store_y[i]);//����ͼ
    }
    //���õذ�
    return;
   
}

/*----------------------------------
--------------------------------------------------------------------��ͼ������----------------------------------
--------------------------------*/