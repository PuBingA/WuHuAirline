#include"map.h"
#include"choose_map.h"
#include "monster.h"
#include"carrot.h"
#include "ui/CocosGUI.h"
#include"cocos-ext.h"
#include"settlement_interface.h"
USING_NS_CC;
using namespace std;
int CheckBox(XY obj, const std::vector<FS>& table);

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

void Map_father::game_over(cocos2d::Ref* pSender,int const choice)
{
    if(choice==1)
        Director::getInstance()->replaceScene(settlement_success::createScene());//�л���ʤ������
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
/*****************************change*************************************/
Map_One::Map_One()
{
    //��ʼ��vacancy_spots
    for (int i = 0; i <= 37; i++)
        vacancy.push_back({ i,0,0,nullptr });
    //Ϊָ�붯̬����ռ䣬����Ұָ��
    yellow_frame = new FrameBox(Sprite::create("yellow_frame.png"));
    tower_cannon = new FrameBox(Sprite::create("TI_1_unavailable.png"));
    tower_shit = new FrameBox(Sprite::create("TI_2_unavailable.png"));
    tower_cannon_ready = new FrameBox(Sprite::create("TI_1_available.png"));
    tower_shit_ready = new FrameBox(Sprite::create("TI_2_available.png"));
    cannon_Lv1 = new FrameBox(Sprite::create("cannon_Lv1.png"));
    cannon_Lv2 = new FrameBox(Sprite::create("cannon_Lv2.png"));
    cannon_Lv3 = new FrameBox(Sprite::create("cannon_Lv3.png"));
    shit_Lv1 = new FrameBox(Sprite::create("shit_Lv1.png"));
    shit_Lv2 = new FrameBox(Sprite::create("shit_Lv2.png"));
    shit_Lv3 = new FrameBox(Sprite::create("shit_Lv3.png"));
    upgrade_grey = new FrameBox(Sprite::create("upgrade_grey.png"));
    upgrade_ready = new FrameBox(Sprite::create("upgrade_ready.png"));
    delete_grey = new FrameBox(Sprite::create("delete_grey.png"));
    delete_ready = new FrameBox(Sprite::create("delete_ready.png"));
}

Map_One::~Map_One()
{
    delete yellow_frame;
    delete tower_cannon;
    delete tower_shit;
    delete tower_cannon_ready;
    delete tower_shit_ready;
    delete cannon_Lv1;
    delete cannon_Lv2;
    delete cannon_Lv3;
    delete shit_Lv1;
    delete shit_Lv2;
    delete shit_Lv3;
    delete upgrade_grey;
    delete upgrade_ready;
    delete delete_grey;
    delete delete_ready;
}

void Map_One::input_listener()
{
    auto mouseListener_show_yellow_frame = EventListenerMouse::create();
    mouseListener_show_yellow_frame->onMouseDown = CC_CALLBACK_1(Map_One::onMouseDown_Show_Yellow, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(mouseListener_show_yellow_frame, this);

    auto mouseListener_for_planting = EventListenerMouse::create();
    mouseListener_for_planting->onMouseDown = CC_CALLBACK_1(Map_One::onMouseDown_Do_Plant, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(mouseListener_for_planting, this);

    yellow_frame->Current = Sprite::create("yellow_frame.png");
    this->addChild(yellow_frame->Current); //z-value=0
    yellow_frame->Current->setVisible(false);
}

void Map_One::onMouseDown_Do_Plant(Event* event)
{
    EventMouse* e = dynamic_cast<EventMouse*>(event);
    if (e->getMouseButton() == EventMouse::MouseButton::BUTTON_LEFT)
    {
        int x = e->getCursorX(), y = e->getCursorY();
        if (IsFramePlant_Lv1(x, y))
        {
            if (x == 450)//plant a cannon
            {
                WhichPlant = 1;
            }
            if (x == 550)//plant a shit
            {
                WhichPlant = 2;
            }
            if (x == 650)//upgrade
            {
                WhichPlant = 3;
            }
            if (x == 750)//delete
            {
                WhichPlant = 4;
            }
        }
    }
}

void Map_One::onMouseDown_Show_Yellow(Event* event)
{
    EventMouse* e = dynamic_cast<EventMouse*>(event);
    if (e->getMouseButton() == EventMouse::MouseButton::BUTTON_LEFT)
    {
        int x = e->getCursorX(), y = e->getCursorY();
        if (IsFrame_Lv1(x, y))
        {
            yellow_frame->Current->setVisible(true);
            yellow_frame->Spawn(x, y, 0.5f);
            yellow_frame->Shimmer();
            singleclick._x = x, singleclick._y = y; //�����ɫ��λ�ã�׼����ֲ
            int vacancyIndex = CheckBox(singleclick, AllFrames_Lv1);

            //��ѯ��ֲ״̬�������0��δ��ֲ������к�������
            if (vacancy[vacancyIndex].state == 0)
            {

                //��ɫcannon��Ϊ���ɼ�
                tower_cannon->Current->setVisible(false);
                //��ɫshit��Ϊ���ɼ�
                tower_shit->Current->setVisible(false);
                //��ɫcannon��Ϊ�ɼ�
                tower_cannon_ready->Current->setVisible(true);
                //��ɫshit��Ϊ�ɼ�
                tower_shit_ready->Current->setVisible(true);


                //��ʼ��������λ�ã����ж���ֲ����������һֱ��
                //���⣺������ε�������ƿ���ֵ���˱��λ�ò����ƿ�����ֲ����̨��Ȼ���ֵ�֮ǰ��λ�ã�
                waitForConditionAndExecute(
                    [=]() {
                        return WhichPlant == 1 || WhichPlant == 2;
                    },
                    [=]() {
                        if (WhichPlant == 1) //plant a cannon
                        {
                            //��Ŀ�������һ��cannon
                            cannon_Lv1->Current = Sprite::create("cannon_Lv1.png");
                            this->addChild(cannon_Lv1->Current);
                            cannon_Lv1->Spawn(AllFrames_Lv1[vacancyIndex].adjusted._x, AllFrames_Lv1[vacancyIndex].adjusted._y, 1.0f);
                            vacancy[vacancyIndex].state = 1;      //state=1 ������һ����̨
                            vacancy[vacancyIndex].tower_type = 1; //cannon
                            vacancy[vacancyIndex].spr = cannon_Lv1->Current; //��ǰָ�����vacancy��
                            WhichPlant = 0;
                        }
                        if (WhichPlant == 2) //plant a shit
                        {
                            //��Ŀ�������һ��shit
                            shit_Lv1->Current = Sprite::create("shit_Lv1.png");
                            this->addChild(shit_Lv1->Current);
                            shit_Lv1->Spawn(AllFrames_Lv1[vacancyIndex].adjusted._x, AllFrames_Lv1[vacancyIndex].adjusted._y, 1.0f);
                            vacancy[vacancyIndex].state = 1;      //state=1 ������һ����̨
                            vacancy[vacancyIndex].tower_type = 2; //shit
                            vacancy[vacancyIndex].spr = shit_Lv1->Current; //��ǰָ�����vacancy��
                            WhichPlant = 0;
                        }
                    }
                );
            }
            else if (vacancy[vacancyIndex].state == 1) //state=1 ������һ����̨
            {
                //��ɫcannon��Ϊ�ɼ�
                tower_cannon->Current->setVisible(true);
                //��ɫshit��Ϊ�ɼ�
                tower_shit->Current->setVisible(true);
                //��ɫcannon��Ϊ���ɼ�
                tower_cannon_ready->Current->setVisible(false);
                //��ɫshit��Ϊ���ɼ�
                tower_shit_ready->Current->setVisible(false);
                //��ɫ������Ϊ�ɼ�
                upgrade_ready->Current->setVisible(true);
                //��ɫɾ����Ϊ�ɼ�
                delete_ready->Current->setVisible(true);
                //��ɫ������Ϊ���ɼ�
                upgrade_grey->Current->setVisible(false);
                //��ɫɾ����Ϊ���ɼ�
                delete_grey->Current->setVisible(false);
                waitForConditionAndExecute(
                    [=]() {
                        return WhichPlant == 3 || WhichPlant == 4;
                    },
                    [=]() {
                        if (WhichPlant == 3) //upgrade
                        {
                            if (vacancy[vacancyIndex].tower_type == 1)//upgrade cannon
                            {
                                this->removeChild(vacancy[vacancyIndex].spr);
                                cannon_Lv2->Current = Sprite::create("cannon_Lv2.png");
                                this->addChild(cannon_Lv2->Current);
                                cannon_Lv2->Spawn(AllFrames_Lv1[vacancyIndex].adjusted._x, AllFrames_Lv1[vacancyIndex].adjusted._y, 1.0f);
                                vacancy[vacancyIndex].state = 2;      //state=2 �����˶�����̨
                                vacancy[vacancyIndex].tower_type = 1; //cannon
                                vacancy[vacancyIndex].spr = cannon_Lv2->Current; //��ǰָ�����vacancy��*/
                                WhichPlant = 0;
                            }
                            else if (vacancy[vacancyIndex].tower_type == 2)//upgrade shit
                            {
                                this->removeChild(vacancy[vacancyIndex].spr);
                                shit_Lv2->Current = Sprite::create("shit_Lv2.png");
                                this->addChild(shit_Lv2->Current);
                                shit_Lv2->Spawn(AllFrames_Lv1[vacancyIndex].adjusted._x, AllFrames_Lv1[vacancyIndex].adjusted._y, 1.0f);
                                vacancy[vacancyIndex].state = 2;      //state=2 �����˶�����̨
                                vacancy[vacancyIndex].tower_type = 2; //shit
                                vacancy[vacancyIndex].spr = shit_Lv2->Current; //��ǰָ�����vacancy��*/
                                WhichPlant = 0;
                            }
                        }
                        if (WhichPlant == 4) //delete
                        {
                            if (vacancy[vacancyIndex].tower_type == 1)//delete cannon
                            {
                                this->removeChild(vacancy[vacancyIndex].spr);
                                vacancy[vacancyIndex].state = 0; //void
                                vacancy[vacancyIndex].tower_type = 0; //void
                                vacancy[vacancyIndex].spr = nullptr;
                                WhichPlant = 0;
                            }
                            else if (vacancy[vacancyIndex].tower_type == 2)//delete shit
                            {
                                this->removeChild(vacancy[vacancyIndex].spr);
                                vacancy[vacancyIndex].state = 0; //void
                                vacancy[vacancyIndex].tower_type = 0; //void
                                vacancy[vacancyIndex].spr = nullptr;
                                WhichPlant = 0;
                            }
                        }
                    }
                );
            }
            
            else if (vacancy[vacancyIndex].state == 2) //state=2 �����˶�����̨
            {
                //��ɫcannon��Ϊ�ɼ�
                tower_cannon->Current->setVisible(true);
                //��ɫshit��Ϊ�ɼ�
                tower_shit->Current->setVisible(true);
                //��ɫcannon��Ϊ���ɼ�
                tower_cannon_ready->Current->setVisible(false);
                //��ɫshit��Ϊ���ɼ�
                tower_shit_ready->Current->setVisible(false);
                //��ɫ������Ϊ�ɼ�
                upgrade_ready->Current->setVisible(true);
                //��ɫɾ����Ϊ�ɼ�
                delete_ready->Current->setVisible(true);
                //��ɫ������Ϊ���ɼ�
                upgrade_grey->Current->setVisible(false);
                //��ɫɾ����Ϊ���ɼ�
                delete_grey->Current->setVisible(false);
                waitForConditionAndExecute(
                    [=]() {
                        return WhichPlant == 3 || WhichPlant == 4;
                    },
                    [=]() {
                        if (WhichPlant == 3) //upgrade
                        {
                            if (vacancy[vacancyIndex].tower_type == 1)//upgrade cannon
                            {
                                this->removeChild(vacancy[vacancyIndex].spr);
                                cannon_Lv3->Current = Sprite::create("cannon_Lv3.png");
                                this->addChild(cannon_Lv3->Current);
                                cannon_Lv3->Spawn(AllFrames_Lv1[vacancyIndex].adjusted._x, AllFrames_Lv1[vacancyIndex].adjusted._y, 1.0f);
                                vacancy[vacancyIndex].state = 3;      //state=3 ������������̨
                                vacancy[vacancyIndex].tower_type = 1; //cannon
                                vacancy[vacancyIndex].spr = cannon_Lv3->Current; //��ǰָ�����vacancy��
                                WhichPlant = 0;
                            }
                            else if (vacancy[vacancyIndex].tower_type == 2)//upgrade shit
                            {
                                this->removeChild(vacancy[vacancyIndex].spr);
                                shit_Lv3->Current = Sprite::create("shit_Lv3.png");
                                this->addChild(shit_Lv3->Current);
                                shit_Lv3->Spawn(AllFrames_Lv1[vacancyIndex].adjusted._x, AllFrames_Lv1[vacancyIndex].adjusted._y, 1.0f);
                                vacancy[vacancyIndex].state = 3;      //state=3 ������������̨
                                vacancy[vacancyIndex].tower_type = 2; //shit
                                vacancy[vacancyIndex].spr = shit_Lv3->Current; //��ǰָ�����vacancy��
                                WhichPlant = 0;
                            }
                        }
                        if (WhichPlant == 4) //delete
                        {
                            if (vacancy[vacancyIndex].tower_type == 1)//delete cannon
                            {
                                this->removeChild(vacancy[vacancyIndex].spr);
                                vacancy[vacancyIndex].state = 0; //void
                                vacancy[vacancyIndex].tower_type = 0; //void
                                vacancy[vacancyIndex].spr = nullptr;
                                WhichPlant = 0;
                            }
                            else if (vacancy[vacancyIndex].tower_type == 2)//delete shit
                            {
                                this->removeChild(vacancy[vacancyIndex].spr);
                                vacancy[vacancyIndex].state = 0; //void
                                vacancy[vacancyIndex].tower_type = 0; //void
                                vacancy[vacancyIndex].spr = nullptr;
                                WhichPlant = 0;
                            }
                        }
                    }
                    );
            }
            else if (vacancy[vacancyIndex].state == 3)
            {
                //��ɫcannon��Ϊ�ɼ�
                tower_cannon->Current->setVisible(true);
                //��ɫshit��Ϊ�ɼ�
                tower_shit->Current->setVisible(true);
                //��ɫcannon��Ϊ���ɼ�
                tower_cannon_ready->Current->setVisible(false);
                //��ɫshit��Ϊ���ɼ�
                tower_shit_ready->Current->setVisible(false);
                //��ɫ������Ϊ���ɼ�����
                upgrade_ready->Current->setVisible(false);
                //��ɫɾ����Ϊ�ɼ�
                delete_ready->Current->setVisible(true);
                //��ɫ������Ϊ�ɼ�
                upgrade_grey->Current->setVisible(true);
                //��ɫɾ����Ϊ���ɼ�
                delete_grey->Current->setVisible(false);
                waitForConditionAndExecute(
                    [=]() {
                        return WhichPlant == 4;
                    },
                    [=]() {
                        if (vacancy[vacancyIndex].tower_type == 1)//delete cannon
                        {
                            this->removeChild(vacancy[vacancyIndex].spr);
                            vacancy[vacancyIndex].state = 0; //void
                            vacancy[vacancyIndex].tower_type = 0; //void
                            vacancy[vacancyIndex].spr = nullptr;
                            WhichPlant = 0;
                        }
                        else if (vacancy[vacancyIndex].tower_type == 2)//delete shit
                        {
                            this->removeChild(vacancy[vacancyIndex].spr);
                            vacancy[vacancyIndex].state = 0; //void
                            vacancy[vacancyIndex].tower_type = 0; //void
                            vacancy[vacancyIndex].spr = nullptr;
                            WhichPlant = 0;
                        }
                    }
                );
            }
        }
        else
        {
            yellow_frame->Current->setVisible(false);
            //grey cannon visible
            tower_cannon->Current->setVisible(true);
            //grey shit visible
            tower_shit->Current->setVisible(true);
            //colored cannon invisible
            tower_cannon_ready->Current->setVisible(false);
            //colored shit invisible
            tower_shit_ready->Current->setVisible(false);
            //colored upgrade invisible
            upgrade_ready->Current->setVisible(false);
            //colored delete invisible
            delete_ready->Current->setVisible(false);
            //grey update visible
            upgrade_grey->Current->setVisible(true);
            //grey delete visible
            delete_grey->Current->setVisible(true);
        }
    }
}

void Map_One::waitForConditionAndExecute(const std::function<bool()>& condition, const std::function<void()>& callback)
{
    if (condition())
    {
        callback();
    }
    else
    {
        scheduleOnce([=](float dt)
            {
                waitForConditionAndExecute(condition, callback);
            }, 0.1f, "waitForConditionTag");
    }
}

void Map_One::ShowTowerDark()
{
    //��ɫ��̨������״̬�ɼ�
    //��ɫcannon
    tower_cannon->Current = Sprite::create("TI_1_unavailable.png");
    this->addChild(tower_cannon->Current); //z-value=0
    tower_cannon->Spawn(450, 600, 1.0f);
    tower_cannon->Current->setVisible(true);
    //��ɫshit
    tower_shit->Current = Sprite::create("TI_2_unavailable.png");
    this->addChild(tower_shit->Current); //z-value=0
    tower_shit->Spawn(550, 600, 1.0f);
    tower_shit->Current->setVisible(true);
    //��ɫ��������ע������.png��Ҫ��������0.7
    upgrade_grey->Current = Sprite::create("upgrade_grey.png");
    this->addChild(upgrade_grey->Current); //z-value=0
    upgrade_grey->Spawn(650, 600, 0.7f);
    upgrade_grey->Current->setVisible(true);
    //��ɫ�Ƴ�����ע���Ƴ�.png��Ҫ��������0.7
    delete_grey->Current = Sprite::create("delete_grey.png");
    this->addChild(delete_grey->Current); //z-value=0
    delete_grey->Spawn(750, 600, 0.7f);
    delete_grey->Current->setVisible(true);


    //��ɫ��̨������״̬���ɼ�
    //��ɫcannon
    tower_cannon_ready->Current = Sprite::create("TI_1_available.png");
    this->addChild(tower_cannon_ready->Current); //z-value=0
    tower_cannon_ready->Spawn(450, 600, 1.0f);
    tower_cannon_ready->Current->setVisible(false);
    //��ɫshit
    tower_shit_ready->Current = Sprite::create("TI_2_available.png");
    this->addChild(tower_shit_ready->Current); //z-value=0
    tower_shit_ready->Spawn(550, 600, 1.0f);
    tower_shit_ready->Current->setVisible(false);
    //��ɫ����
    upgrade_ready->Current = Sprite::create("upgrade_ready.png");
    this->addChild(upgrade_ready->Current); //z-value=0
    upgrade_ready->Spawn(650, 600, 0.7f);
    upgrade_ready->Current->setVisible(false);
    //��ɫ�Ƴ�
    delete_ready->Current = Sprite::create("delete_ready.png");
    this->addChild(delete_ready->Current); //z-value=0
    delete_ready->Spawn(750, 600, 0.7f);
    delete_ready->Current->setVisible(false);
}


/*****************************change*************************************/

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

    /*****************************change*************************************/
    ShowTowerDark();
    input_listener();
    /*****************************change*************************************/

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

    //����Ϊ����
    carrot->HP = 0;
    carrot->level = 3;
    carrot->change();
    carrot_HP->setString(calculate_HP(carrot->HP));//���ݵ�ǰѪ���������壬��ע�����ӡ�����Ѫ��ʱ���ǵ��������������壩
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


/*************************************************************
    CheckBox��������֪��Ӧ��������ĵ����꣬��ѯ�����
*************************************************************/
int CheckBox(XY obj, const std::vector<FS>& table)
{
    for (auto& it : table)
    {
        if (it.adjusted._x == obj._x && it.adjusted._y == obj._y)
            return it.index;
    }
    return -1;
}
