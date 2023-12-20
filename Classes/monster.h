#include "cocos2d.h"
#include "public_define.h"
#include <vector>

class MonSprite;

class MonCtrl//���������
{
private:
    MonSprite* currentMon;
    int monType;
    std::vector<std::vector<float>>monsterWalkPath;//�����н�·��
public:
    MonCtrl(MonSprite* curnt_mon, int mon_type, std::vector<std::vector<float>>mon_path)
    {
        currentMon = curnt_mon;
        monType = mon_type;
        monsterWalkPath = mon_path;
    }
    void spawn()const;//���þ��飬��ָ�����괦����
    void move()const;//�ƶ�
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
public:
    friend class MonCtrl;
    static MonSprite* create(const std::string& filename);
    void setData();//������ֵ
};

