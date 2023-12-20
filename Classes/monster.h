#include "cocos2d.h"
#include "ui/CocosGUI.h"
#include "public_define.h"
#include <vector>

class MonSprite;

class MonCtrl//���������
{
private:
    MonSprite* currentMon;
    int monType;
    cocos2d::ui::LoadingBar* life_bar = NULL;
    std::vector<std::vector<float>>monsterWalkPath;//�����н�·��
    void move()const;//�ƶ�
public:
    MonCtrl(MonSprite* curnt_mon = NULL, int mon_type = 0)
    {
        currentMon = curnt_mon;
        monType = mon_type;
    }
    MonCtrl(MonSprite* curnt_mon, int mon_type, std::vector<std::vector<float>>mon_path)
    {
        currentMon = curnt_mon;
        monType = mon_type;
        monsterWalkPath = mon_path;
    }
    void setVal(MonSprite* curnt_mon, int mon_type, std::vector<std::vector<float>>mon_path)
    {
        currentMon = curnt_mon;
        monType = mon_type;
        monsterWalkPath = mon_path;
    }
    void spawn();//���þ��飬��ָ�����괦����
    void hurt(float hit_point)const;//����
    void die()const;//����
    void monAttackCarrot() {};//�����ܲ�
};


class MonSprite : public cocos2d::Sprite//������
{
private:
    float monsterVitality = 1;//����
    float monsterAttack = 1;//������
    float monsterDefense = 1;//������
    float monsterSpeed = 1;//�ٶ�
    float currentLife = monsterVitality;
public:
    friend class MonCtrl;
    static MonSprite* create(const std::string& filename);
    void setData();//������ֵ
};

