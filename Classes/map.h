#include "cocos2d.h"
#include "public_define.h"
#include "cocos-ext.h"
#include "ui/CocosGUI.h"
#include "Frames.h"
#include "monster_towers.h"
#include <string>
#include <vector>
USING_NS_CC;

//VS����ÿ����ֲλ��������Ϣ��ͳһ���ŵ����+λ��״̬+����������+���еľ���ָ��
typedef struct Vacancy_State
{
    int index;
    int tower_type;
    Tower* spr;
}VS;

class Map_father :public cocos2d::Scene
{
protected:
    Sprite* yellow_frame = nullptr;
    Sprite* plant_cannon = nullptr;
    Sprite* plant_shit = nullptr;
    Sprite* plant_etower = nullptr;
    Sprite* upgrade_frame = nullptr;
    Sprite* delete_frame = nullptr;
    Cannon* cannon = nullptr;
    Shit* shit = nullptr;
    Etower* etower = nullptr;
    Carrot* carrot = nullptr;
    ui::Button* carrot_level_button = nullptr;      //����ܲ�������ť
    ui::Button* boom_button = nullptr;              //��ű�ը�����ף���ť
    std::vector<FS> AllPlants;
    std::vector<FS> AllFrames;
    bool mouse_select_type = 0;
    XY singleclick;                                 //�洢�����λ��
    int vacancyIndex = -1;                          //��λ����
    std::vector<VS> vacancy;                        //vacancy���ÿ���ɷ���λ�õ���Ϣ
    int gold_content[1];                           //��ǰ���������
    int* gold=gold_content;                                       //��ǰ�����ָ��
    Label* gold_label;                              //��ұ�ǩ
    int boss_music;  //���boss������
    std::vector<std::vector<float>>walk_way;        //��Ź����н���x,y�������
    Node* monster_wave = new Node;
    MonSprite* boss = nullptr;
    bool boss_spawned = false;
public:
    static cocos2d::Scene* createScene();
    virtual bool init();                              //����������,���̳й��в���
    virtual void input_background() {};               //���ñ���ͼ
    virtual void input_walk_way() {};                 //���ù����н�·��
    void menuCallback(cocos2d::Ref* pSender);         //������Ӧ����
    void input_return_pause();                        //���÷��أ��Լ���ͣ�� 
    void buttonCallback(cocos2d::Ref* pSender);       //��ͣ��Ӧ����
    void input_gold_item();                           //���ý��UI
    virtual void ShowPlantButton() {};
    virtual void input_listener() {};
    void onMouseDown_Do_Plant(Event* event);
    std::string calculate_gold(int *gold);       //���ݵ�ǰ��ң��ó��ַ���
    void change_gold_label(float dt);   //���½�Ҵ���

    virtual void game_begin() {};                     //��Ϸ��ʼ����
    void game_over_success(float dt);                 //��Ϸʤ��
    void game_over_failure(float dt);                 //��Ϸʧ��
    void input_carrot_level_button();;                //�����ܲ�������ť
    void carrot_level_button_call_back(cocos2d::Ref* pSender);     //�ܲ������ص�����
    void change_carrot_level_button(float dt);                //��⵱ǰ�Ƿ���Խ����ܲ�����,ʹ�ܲ���ťʧЧ/��Ч����ұ仯���ܲ��ȼ��ı�ʱ��Ҫ���ã���
    template<typename T>
    void input_brick(T x,T y ,int choice);            //���õذ�
    void spawnMonster1_1(float dt);       //����Type=1�Ĺ���
    void spawnMonster1_2(float dt);       //����Type=1�Ĺ���
    void spawnMonster1_3(float dt);       //����Type=1�Ĺ���
    void spawnMonster2_1(float dt);       //����Type=2�Ĺ���
    void spawnMonster2_2(float dt);       //����Type=2�Ĺ���
    void spawnMonster2_3(float dt);       //����Type=2�Ĺ���
    void spawnMonster3_1(float dt);       //����Type=3�Ĺ���
    void spawnMonster3_2(float dt);       //����Type=3�Ĺ���
    void spawnMonster3_3(float dt);       //����Type=3�Ĺ���
    void spawnMonster4_1(float dt);       //����Type=4�Ĺ���
    void spawnMonster4_2(float dt);       //����Type=4�Ĺ���
    void spawnMonster4_3(float dt);       //����Type=4�Ĺ���
    void spawnBoss(float dt);             //����Type=5�Ĺ���
    void waitForConditionAndExecute(const std::function<bool()>& condition, const std::function<void()>& callback);
    CREATE_FUNC(Map_father);
};

class Map_One :public Map_father
{
public:
    Map_One()
    {
        *gold = gold_1;
    }//���캯��
    virtual void ShowPlantButton();
    virtual void input_listener();
    virtual void input_background();
    virtual void input_walk_way();
    virtual void game_begin();      //��Ϸ��ʼ����
    CREATE_FUNC(Map_One);
};

class Map_Two :public Map_father
{
public:
    Map_Two()
    {
        *gold = gold_2;
    }//���캯��
    virtual void ShowPlantButton();
    virtual void input_listener();
    virtual void input_background();
    virtual void input_walk_way();
    virtual void game_begin();      //��Ϸ��ʼ����
    CREATE_FUNC(Map_Two);
};

class Map_Three :public Map_father
{
public:
    Map_Three()
    {
        *gold = gold_3;
    }//���캯��
    virtual void ShowPlantButton();
    virtual void input_listener();
    virtual void input_background();
    virtual void input_walk_way();
    virtual void game_begin();      //��Ϸ��ʼ����
    CREATE_FUNC(Map_Three);
};

