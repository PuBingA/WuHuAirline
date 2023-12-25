#include "cocos2d.h"
#include "public_define.h"
#include "cocos-ext.h"
#include "Frames.h"
#include "monster.h"
#include <string>
#include <vector>
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
    FrameBox* yellow_frame = nullptr;
    FrameBox* tower_cannon = nullptr;
    FrameBox* tower_cannon_ready = nullptr;
    FrameBox* tower_shit = nullptr;
    FrameBox* tower_shit_ready = nullptr;
    FrameBox* tower_etower = nullptr;
    FrameBox* tower_etower_ready = nullptr;
    FrameBox* cannon_Lv1 = nullptr;
    FrameBox* cannon_Lv2 = nullptr;
    FrameBox* cannon_Lv3 = nullptr;
    FrameBox* shit_Lv1 = nullptr;
    FrameBox* shit_Lv2 = nullptr;
    FrameBox* shit_Lv3 = nullptr;
    FrameBox* etower_Lv1 = nullptr;
    FrameBox* etower_Lv2 = nullptr;
    FrameBox* etower_Lv3 = nullptr;
    FrameBox* upgrade_grey = nullptr;
    FrameBox* upgrade_ready = nullptr;
    FrameBox* delete_grey = nullptr;
    FrameBox* delete_ready = nullptr;
    Carrot* carrot = nullptr;
    int WhichPlant = 0;
    XY singleclick;                                 //�洢�����λ��
    int vacancyIndex = -1;                          //��λ����
    std::vector<VS> vacancy;                        //vacancy���ÿ���ɷ���λ�õ���Ϣ
    int gold;                                       //��ǰ�����
    Label* gold_label;                              //��ұ�ǩ
    std::vector<std::vector<float>>walk_way;        //��Ź����н���x,y�������
    std::vector<MonSprite*>monster_wave;
public:
    static cocos2d::Scene* createScene();
    virtual bool init();                              //����������,���̳й��в���
    virtual void input_background() {};               //���ñ���ͼ
    virtual void input_walk_way() {};                 //���ù����н�·��
    void menuCallback(cocos2d::Ref* pSender);         //������Ӧ����
    void input_return_pause();                        //���÷��أ��Լ���ͣ�� 
    void buttonCallback(cocos2d::Ref* pSender);       //��ͣ��Ӧ����
    void input_gold_item();                           //���ý��UI
    virtual void ShowTowerDark() {};
    virtual void input_listener() {};
    cocos2d::Label* input_gold();                     //���ɽ�ұ�ǩ
    std::string calculate_gold(const int gold);       //���ݵ�ǰ��ң��ó��ַ���
    virtual void game_begin() {};                     //��Ϸ��ʼ����
    void game_over_success(float dt);                 //��Ϸʤ��
    void game_over_failure(float dt);                 //��Ϸʧ��
    template<typename T>
    void input_brick(T x,T y ,int choice);            //���õذ�
    void spawnMonster1_1(float dt);       //����Type=1�Ĺ���
    void spawnMonster1_2(float dt);       //����Type=1�Ĺ���
    void spawnMonster1_3(float dt);       //����Type=1�Ĺ���
    void waitForConditionAndExecute(const std::function<bool()>& condition, const std::function<void()>& callback);
    CREATE_FUNC(Map_father);
};

class Map_One :public Map_father
{
public:
    Map_One();
    virtual void ShowTowerDark();
    virtual void input_listener();
    void onMouseDown_Do_Plant(Event* event);
    void onMouseDown_Show_Yellow(Event* event);
    void StartAttack();
    virtual void input_background();
    virtual void input_walk_way();
    virtual void game_begin();      //��Ϸ��ʼ����
    CREATE_FUNC(Map_One);
};

class Map_Two :public Map_father
{
public:
    Map_Two();
    virtual void ShowTowerDark();
    virtual void input_listener();
    void onMouseDown_Do_Plant(Event* event);
    void onMouseDown_Show_Yellow(Event* event);

    virtual void input_background();
    virtual void input_walk_way();
    virtual void game_begin();      //��Ϸ��ʼ����
    CREATE_FUNC(Map_Two);
};

class Map_Three :public Map_father
{
public:
    Map_Three();
    virtual void ShowTowerDark();
    virtual void input_listener();
    void onMouseDown_Do_Plant(Event* event);
    void onMouseDown_Show_Yellow(Event* event);

    virtual void input_background();
    virtual void input_walk_way();
    virtual void game_begin();      //��Ϸ��ʼ����
    CREATE_FUNC(Map_Three);
};

