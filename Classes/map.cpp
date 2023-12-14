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

/*-------------------������������--------------------*/
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


/*-------------------������������--------------------*/

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
    for (int i = 0; i < 6; i++)
    {
        walk_way_store_x.push_back(walk_way_begin_x);
        walk_way_store_y.push_back(walk_way_begin_y - i * way_size);
    }//��ֱ����

    for (int i = 0; i < 10; i++)
    {
        walk_way_store_x.push_back(walk_way_begin_x + i * way_size);
        walk_way_store_y.push_back(walk_way_begin_y - 5 * way_size);
    }//ˮƽ����

    for (int i = 0; i < 6; i++)
    {
        walk_way_store_x.push_back(walk_way_begin_x + 9 * way_size);
        walk_way_store_y.push_back(walk_way_begin_y + (i - 5) * way_size);
    }//��ֱ����
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