#include "cocos2d.h"
#include"public_define.h"
#include"map.h"
#include "AudioEngine.h"

enum choose_scene_2
{
    back,//返回开始界面
    map1,//进入第一张地图
    map2,//进入第二张地图
    map3,//进入第三张地图
};


class choose_map :public cocos2d::Scene//继承场景类
{
private:
    int choose_map_bgm;//背景音乐植入
public:
    static cocos2d::Scene* createScene();

    virtual bool init();//创建场景类

    void menuCallback(cocos2d::Ref* pSender,choose_scene_2 choose_map);//菜单响应函数

    // implement the "static create()" method manually
    CREATE_FUNC(choose_map);

};
