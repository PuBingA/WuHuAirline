#include"cocos2d.h"
#include"public_define.h"
/*-------------------���㳡����---------------------------------------*/
class settlement_success :public cocos2d::Scene
{
public:
    static cocos2d::Scene* createScene();

    virtual bool init();//������������
    void menuCallback(cocos2d::Ref* pSender);//�˵���Ӧ����

    CREATE_FUNC(settlement_success);


};

class settlement_failure :public cocos2d::Scene
{
public:
    static cocos2d::Scene* createScene();

    virtual bool init();//������������

    void menuCallback(cocos2d::Ref* pSender);//�˵���Ӧ����

    CREATE_FUNC(settlement_failure);


};

/*-------------------���㳡����---------------------------------------*/