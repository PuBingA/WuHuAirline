#include "cocos2d.h"
#include "ui/CocosGUI.h"
#include "public_define.h"
#include <vector>
USING_NS_CC;

class MonSprite : public Sprite//������
{
private:
    int monType = 1;
    int monVitality = 1;//����
    int monAttack = 1;//������
    int monSpeed = 1;//�ٶ�
    int monCurrentLife = 1;
    ui::LoadingBar* monLifeBar = NULL;

    void setType(int type)//������ֵ
    {
        monType = type;
        switch (monType)
        {
        case 1:
            monVitality = mon1_vit;
            monAttack = mon1_atk;
            monSpeed = mon1_spd;
            break;
        }
        monCurrentLife = monVitality;
    }

public:
    /**********************12.23 ����**************************/
    friend class FrameBox;
    /**********************12.23 ����**************************/

    friend class MonsterController;

    static MonSprite* create(int type = 0)
    {
        MonSprite* monster_sprite = new MonSprite();
        if (monster_sprite && monster_sprite->init())
        {//����������Ѫ��
            monster_sprite->setType(type);
            monster_sprite->setOpacity(0);//����ȫ͸��
            monster_sprite->monLifeBar = cocos2d::ui::LoadingBar::create("life_bar.png");
            monster_sprite->monLifeBar->setDirection(cocos2d::ui::LoadingBar::Direction::LEFT);
            monster_sprite->monLifeBar->setPositionNormalized(Vec2(0.5, 0));
            monster_sprite->monLifeBar->setPercent(100);
            monster_sprite->addChild(monster_sprite->monLifeBar);
            //�Զ��ͷ�
            monster_sprite->autorelease();
            return monster_sprite;
        }
        CC_SAFE_DELETE(monster_sprite);
        return nullptr;
    }

    //����һ�����ﲢ��ʼ�ƶ�
    void monster_spawn(std::vector<std::vector<float>>walkPath)
    {
        this->setPosition(walkPath[0][0], walkPath[0][1]);
        if (this->monType == 1)
        {
            this->setTexture("monster1_1.png");//������ͼ
            this->setScale(0.7f);//������ͼ��С
            Vector<SpriteFrame*> animFrames;
            animFrames.reserve(2);
            animFrames.pushBack(SpriteFrame::create("monster1_1.png", Rect(0, 0, 135, 135)));
            animFrames.pushBack(SpriteFrame::create("monster1_2.png", Rect(0, 0, 135, 135)));
            Animation* animation = Animation::createWithSpriteFrames(animFrames, animate_duration);
            Animate* animate = Animate::create(animation);
            this->runAction(RepeatForever::create(animate));//��ͣŤ��
        }

        Vector<FiniteTimeAction*> monster_move_sequence;
        //���ﵭ�룬��ʾ����
        monster_move_sequence.pushBack(FadeIn::create(fade_time));
        for (auto& monster_walk_point : walkPath)
            monster_move_sequence.pushBack(MoveTo::create((base_move_time / this->monSpeed), Vec2(monster_walk_point[0], monster_walk_point[1])));
        monster_move_sequence.pushBack(FadeIn::create(fade_time));
        this->runAction(Sequence::create(monster_move_sequence));
    }

    //����ȥ��
    int monster_if_die(Node* currentWave)
    {
        if (this->monVitality <= 0)
        {
            this->stopAllActions();
            this->runAction(FadeOut::create(fade_time));//���ﵭ��
            currentWave->removeChild(this);//������
            delete this;
            return 1;
        }
        return 0;
    }

    //��������
    void monster_hurt(Node* currentWave, int hit_point)
    {
        this->monVitality -= hit_point;
        this->runAction(Blink::create(blink_duration, blink_time));
        monster_if_die(currentWave);//�жϹ�������
    }

    //�����ܲ��������˺�
    int monster_attack_carrot(Rect carrot_rect, Node* currentWave)
    {
        if (carrot_rect.intersectsRect(this->getBoundingBox()))
        {
            this->monVitality = 0;
            this->monster_if_die(currentWave);//������
            return this->monAttack;
        }
        return 0;
    }

};


class MonsterSpawner
{
public:
    Node* wave;
    std::vector<std::vector<float>>walk_way;
    int monster_type;
    MonSprite* monster1;
    MonSprite* monster2;
    MonSprite* monster3;
    MonSprite* monster4;
    MonSprite* monster5;

    MonsterSpawner(Node* wv, std::vector<std::vector<float>>w_w, int mon_type = 0) : wave(wv), walk_way(w_w), monster_type(mon_type)
    {
        monster1 = MonSprite::create(monster_type);
        wave->addChild(monster1);
        monster2 = MonSprite::create(monster_type);
        wave->addChild(monster2);
        monster3 = MonSprite::create(monster_type);
        wave->addChild(monster3);
        monster4 = MonSprite::create(monster_type);
        wave->addChild(monster4);
        monster5 = MonSprite::create(monster_type);
        wave->addChild(monster5);
    }

    void spawn1(float dt)
    {
        monster1->monster_spawn(walk_way);
    }

    void spawn2(float dt)
    {
        monster2->monster_spawn(walk_way);
    }

    void spawn3(float dt)
    {
        monster3->monster_spawn(walk_way);
    }

    void spawn4(float dt)
    {
        monster4->monster_spawn(walk_way);
    }

    void spawn5(float dt)
    {
        monster5->monster_spawn(walk_way);
    }

};