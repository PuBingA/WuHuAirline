#include"cocos2d.h"
#include<vector>
#include"public_define.h"
#include<string>
#include"cocos-ext.h"
#include "Frames.h"
/**********************12.23 ����**************************/
#include "monster.h"
#include "Priority_Queue.h"


//ÿ�����ŵĹ��ﶼ��һ���Լ���MI����������ֻ�������Ϣ
typedef struct MonsterInfo
{
    XY current_location;
    MonSprite* current_monster;
}MI;
/**********************12.23 ����**************************/

//VS����ÿ����ֲλ��������Ϣ��ͳһ���ŵ����+λ��״̬+����������+���еľ���ָ��
typedef struct Vacancy_State
{
    int index;
    int state;
    int tower_type;
    Sprite* spr;
}VS;
//state=0 �� 
//state=1 ������һ����̨
//state=2 �����˶�����̨
//state=3 ������������̨
//tower_type=1 ��ũ��
//tower_type=2 ʺ
//tower_type=3 �����


class Map_father :public cocos2d::Scene
{
public:
    static cocos2d::Scene* createScene();
    virtual bool init();//����������,���̳й��в���
    virtual void input_background() {};//���ñ���ͼ
    virtual void input_walk_way() {};//���ù����н�·��
    void menuCallback(cocos2d::Ref* pSender);//������Ӧ����
    void input_return_pause();//���÷��أ��Լ���ͣ�� 
    void buttonCallback(cocos2d::Ref* pSender);//��ͣ��Ӧ����
    void input_gold_item();//���ý��UI
    cocos2d::Label* input_gold();//���ɽ�ұ�ǩ
    std::string  calculate_gold(const int gold);//���ݵ�ǰ��ң��ó��ַ���
    template<typename T>
    cocos2d::Label* HP_display(const T x, const T y);//����Ӧ���������ܲ�
    std::string calculate_HP(const int HP);//�����ܲ�Ѫ�����ȴ��ַ���
    virtual void game_begin() {};//��Ϸ��ʼ����(�ص�)
    void game_over_success(float dt);//��Ϸʤ��
    void game_over_failure(float dt);//��Ϸʧ��
    template<typename T>
    void input_brick(T x,T y ,int choice);//���õذ�
    virtual void spawn_monster() {};//���ù���
    // implement the "static create()" method manually
    CREATE_FUNC(Map_father);
};

class Map_One :public Map_father
{
private:
    FrameBox* yellow_frame;
    FrameBox* tower_cannon;
    FrameBox* tower_shit;
    FrameBox* tower_cannon_ready;
    FrameBox* tower_shit_ready;
    FrameBox* cannon_Lv1;
    FrameBox* cannon_Lv2;
    FrameBox* cannon_Lv3;
    FrameBox* shit_Lv1;
    FrameBox* shit_Lv2;
    FrameBox* shit_Lv3;
    FrameBox* upgrade_grey;
    FrameBox* upgrade_ready;
    FrameBox* delete_grey;
    FrameBox* delete_ready;
    int WhichPlant = 0; 
    /* ����ָʾֲ���ָʾ������ֻ�������λ�ã�
               WhichPlant = 1 cannon
               WhichPlant = 2 shit
               WhichPlant = 3 upgrade
               WhichPlant = 1 delete           */
    XY singleclick;
    //vacancy���ÿ���ɷ���λ�õ���Ϣ
    std::vector<VS> vacancy;

    /**********************12.23 ����**************************/
    PQueue<MI> currentMonstersOnScreen;
    /**********************12.23 ����**************************/

public:
    Map_One();
    ~Map_One();
    void ShowTowerDark();
    void input_listener();
    void onMouseDown_Do_Plant(Event* event);
    void onMouseDown_Show_Yellow(Event* event);
    void waitForConditionAndExecute(const std::function<bool()>& condition, const std::function<void()>& callback);

    virtual void input_background();
    virtual void input_walk_way();
    virtual void spawn_monster();
    virtual void game_begin();//��Ϸ��ʼ����(�ص�)
    CREATE_FUNC(Map_One);
private:
    std::vector<std::vector<float>>walk_way_store_1;//��Ź����н���x,y�������
};

class Map_Two :public Map_father
{
public:
    virtual void input_background();
    virtual void input_walk_way();
    virtual void spawn_monster();
    virtual void game_begin();//��Ϸ��ʼ����(�ص�)
    CREATE_FUNC(Map_Two);
private:
    std::vector<std::vector<float>>walk_way_store_2;//��Ź����н���x,y�������
};

class Map_Three :public Map_father
{
public:
    virtual void input_background();
    virtual void input_walk_way();
    virtual void spawn_monster();
    virtual void game_begin() ;//��Ϸ��ʼ����(�ص�)
    CREATE_FUNC(Map_Three);
private:
    std::vector<std::vector<float>>walk_way_store_3;//��Ź����н���x,y�������
};

