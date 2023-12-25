#include"cocos2d.h"
#include"public_define.h"
/*-------------------结算场景类---------------------------------------*/
class settlement_success :public cocos2d::Scene
{
protected:
    int music;


public:
    static cocos2d::Scene* createScene();

    virtual bool init();//构建场景函数
    void menuCallback(cocos2d::Ref* pSender, int& music);//菜单相应函数
    CREATE_FUNC(settlement_success);


};

class settlement_failure :public cocos2d::Scene
{
protected:
    int music;
public:
    static cocos2d::Scene* createScene();

    virtual bool init();//构建场景函数

    void menuCallback(cocos2d::Ref* pSender, int& music);//菜单响应函数
    CREATE_FUNC(settlement_failure);


};

/*-------------------结算场景类---------------------------------------*/