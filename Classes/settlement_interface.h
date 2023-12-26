#include"cocos2d.h"
#include"public_define.h"
#include<string>
/*-------------------结算场景类---------------------------------------*/


class settlement:public cocos2d::Scene
{
protected:
    int music;//音乐
    std::string background="success.png";//背景图片名字
    std::string left;//左图片
    std::string right;//右图片
    std::string music_name;//音乐名字
    std::string label_content;//标签内容
public:
    static cocos2d::Scene* createScene() { return settlement::create(); }
    virtual bool init();//构建场景函数
    virtual void input_menu() {};//放置菜单按钮
    virtual void menuCallback(cocos2d::Ref* pSender, int& music) {};//菜单响应函数
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
    }//构造函数


    static cocos2d::Scene* createScene();
    virtual void input_menu();//放置菜单按钮
    virtual void menuCallback(cocos2d::Ref* pSender, int& music);//菜单响应函数
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
    }//构造函数


    static cocos2d::Scene* createScene();
    virtual void input_menu();//放置菜单按钮
    virtual void menuCallback(cocos2d::Ref* pSender, int& music);//菜单响应函数
    CREATE_FUNC(settlement_failure);


};

/*-------------------结算场景类---------------------------------------*/

/*-------------------暂停场景类---------------------------------------*/
class settlement_pause :public settlement
{
public:
    settlement_pause()
    {
        left = "pause.png";
        right = "pause.png";
        music_name = "pause.mp3";
        label_content = "Pause!";
    }//构造函数

    static cocos2d::Scene* createScene();
    virtual void input_menu();//放置菜单按钮
    virtual void menuCallback(cocos2d::Ref* pSender, int& music);//菜单响应函数
    CREATE_FUNC(settlement_pause);


};
/*-------------------暂停场景类---------------------------------------*/