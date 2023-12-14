#include "cocos2d.h"
#include"public_define.h"
#include "AudioEngine.h"

enum choose_scene
{
    close,//关闭
    begining//开始选择地图
};//这里存放切换场景的参数，用于简化切换场景函数

class Opening : public cocos2d::Scene
{
public:
    static cocos2d::Scene* createScene();

    virtual bool init();//构建场景函数
    
    void menuCallback(cocos2d::Ref* pSender, const choose_scene opening_menu);//菜单响应函数
    
    CREATE_FUNC(Opening);

    /*一以下为团队自定义的函数*/
    template<class T,class K>
    void label_output(cocos2d::Label* my_label, T wide, K high);//输出标签
};
