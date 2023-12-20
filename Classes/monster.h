#include "cocos2d.h"
#include "public_define.h"
#include <vector>

class MonSprite;

class MonCtrl//怪物控制类
{
private:
    MonSprite* currentMon;
    int monType;
    std::vector<std::vector<float>>monsterWalkPath;//怪物行进路径
public:
    MonCtrl(MonSprite* curnt_mon, int mon_type, std::vector<std::vector<float>>mon_path)
    {
        currentMon = curnt_mon;
        monType = mon_type;
        monsterWalkPath = mon_path;
    }
    void spawn()const;//放置精灵，在指定坐标处生成
    void move()const;//移动
    void hurt(float hit_point)const;//受伤
    void die()const;//死亡
    void monAttackCarrot() {};//攻击萝卜
};


class MonSprite : public cocos2d::Sprite//怪物类
{
private:
    float monsterVitality = 1;//生命
    float monsterAttack = 1;//攻击力
    float monsterDefense = 1;//防御力
    float monsterSpeed = 1;//速度
public:
    friend class MonCtrl;
    static MonSprite* create(const std::string& filename);
    void setData();//设置数值
};

