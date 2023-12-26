#include"cocos2d.h"
#include"public_define.h"
#include<string>
/*-------------------���㳡����---------------------------------------*/


class settlement:public cocos2d::Scene
{
protected:
    int music;//����
    std::string background="success.png";//����ͼƬ����
    std::string left;//��ͼƬ
    std::string right;//��ͼƬ
    std::string music_name;//��������
    std::string label_content;//��ǩ����
public:
    static cocos2d::Scene* createScene() { return settlement::create(); }
    virtual bool init();//������������
    virtual void input_menu() {};//���ò˵���ť
    virtual void menuCallback(cocos2d::Ref* pSender, int& music) {};//�˵���Ӧ����
    CREATE_FUNC(settlement);
};


class settlement_success :public settlement
{
public:
    settlement_success()
    {
        left = "success_1.png";
        right = "success_2.png";
        music_name = "success.mp3";
        label_content = "You Win!";
    }//���캯��


    static cocos2d::Scene* createScene();
    virtual void input_menu();//���ò˵���ť
    virtual void menuCallback(cocos2d::Ref* pSender, int& music);//�˵���Ӧ����
    CREATE_FUNC(settlement_success);


};

class settlement_failure :public settlement
{
public:
    settlement_failure()
    {
        left = "failure_1.png";
        right = "failure_2.png";
        music_name = "failure.mp3";
        label_content = "You Lose!";
    }//���캯��


    static cocos2d::Scene* createScene();
    virtual void input_menu();//���ò˵���ť
    virtual void menuCallback(cocos2d::Ref* pSender, int& music);//�˵���Ӧ����
    CREATE_FUNC(settlement_failure);


};

/*-------------------���㳡����---------------------------------------*/

/*-------------------��ͣ������---------------------------------------*/
class settlement_pause :public settlement
{
public:
    settlement_pause()
    {
        left = "pause.png";
        right = "pause.png";
        music_name = "pause.mp3";
        label_content = "Pause!";
    }//���캯��

    static cocos2d::Scene* createScene();
    virtual void input_menu();//���ò˵���ť
    virtual void menuCallback(cocos2d::Ref* pSender, int& music);//�˵���Ӧ����
    CREATE_FUNC(settlement_pause);


};
/*-------------------��ͣ������---------------------------------------*/