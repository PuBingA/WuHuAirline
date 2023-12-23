#include"cocos2d.h"
#include<vector>
#include"public_define.h"
#include<string>
#include"cocos-ext.h"
#include "Frames.h"
#include "monster.h"
#include "Priority_Queue.h"
USING_NS_CC;


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
protected:
    FrameBox* yellow_frame = NULL;
    FrameBox* tower_cannon = NULL;
    FrameBox* tower_shit = NULL;
    FrameBox* tower_cannon_ready = NULL;
    FrameBox* tower_shit_ready = NULL;
    FrameBox* cannon_Lv1 = NULL;
    FrameBox* cannon_Lv2 = NULL;
    FrameBox* cannon_Lv3 = NULL;
    FrameBox* shit_Lv1 = NULL;
    FrameBox* shit_Lv2 = NULL;
    FrameBox* shit_Lv3 = NULL;
    FrameBox* upgrade_grey = NULL;
    FrameBox* upgrade_ready = NULL;
    FrameBox* delete_grey = NULL;
    FrameBox* delete_ready = NULL;
    int WhichPlant = 0;
    /* ����ָʾֲ���ָʾ������ֻ�������λ�ã�
               WhichPlant = 1 cannon
               WhichPlant = 2 shit
               WhichPlant = 3 upgrade
               WhichPlant = 1 delete           */
    XY singleclick;
    //vacancy���ÿ���ɷ���λ�õ���Ϣ
    std::vector<VS> vacancy;
    int vacancyIndex = 0;

    /**********************12.23 ����**************************/
    PQueue<MonSprite*> currentMonstersOnScreen;
    /**********************12.23 ����**************************/

public:
    static cocos2d::Scene* createScene();
    virtual bool init();//����������,���̳й��в���
    virtual void input_background() {};//���ñ���ͼ
    virtual void input_walk_way() {};//���ù����н�·��

    void waitForConditionAndExecute(const std::function<bool()>& condition, const std::function<void()>& callback);

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
    // implement the "static create()" method manually
    CREATE_FUNC(Map_father);
};

class Map_One :public Map_father
{
public:
    Map_One();
    void ShowTowerDark();
    void input_listener();
    void onMouseDown_Do_Plant(Event* event);
    void onMouseDown_Show_Yellow(Event* event);

    virtual void input_background();
    virtual void input_walk_way();
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
    virtual void game_begin() ;//��Ϸ��ʼ����(�ص�)
    CREATE_FUNC(Map_Three);
private:
    std::vector<std::vector<float>>walk_way_store_3;//��Ź����н���x,y�������
};

