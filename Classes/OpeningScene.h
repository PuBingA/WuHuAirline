#include "cocos2d.h"

class Opening : public cocos2d::Scene
{
public:
    static cocos2d::Scene* createScene();

    virtual bool init();
    
    // a selector callback
    void menuCloseCallback(cocos2d::Ref* pSender);
    
    // implement the "static create()" method manually
    CREATE_FUNC(Opening);

    /*һ����Ϊ�Ŷ��Զ���ĺ���*/

    void label_output(cocos2d::Label* my_label, float wide, float high);//�����ǩ
};
