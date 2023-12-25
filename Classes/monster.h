#include "cocos2d.h"
#include "ui/CocosGUI.h"
#include "public_define.h"
#include "carrot.h"
#include <vector>
#include <algorithm>
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
        case 2:
            monVitality = mon2_vit;
            monAttack = mon2_atk;
            monSpeed = mon2_spd;
            break;
        case 3:
            monVitality = mon3_vit;
            monAttack = mon3_atk;
            monSpeed = mon3_spd;
            break;
        case 4:
            monVitality = mon4_vit;
            monAttack = mon4_atk;
            monSpeed = mon4_spd;
            break;
        }
        monCurrentLife = monVitality;
    }

public:
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
    
    void wait_for_condition_and_execute(const std::function<bool()>& condition, const std::function<void()>& callback)
    {
        if (condition())
            callback();
        else
        {
            scheduleOnce([=](float dt)
                {
                    wait_for_condition_and_execute(condition, callback);
                }, 0.05f, "waitForConditionTag");
        }
    }

    //����һ�����ﲢ��ʼ�ƶ�
    void monster_spawn(std::vector<std::vector<float>>walkPath)
    {
        this->setPosition(walkPath[0][0], walkPath[0][1]);
        if (this->monType == 1)
        {
            this->setTexture("monster1_1.png");//������ͼ
            this->setScale(0.9f);//������ͼ��С
            Vector<SpriteFrame*> animFrames;
            animFrames.reserve(2);
            animFrames.pushBack(SpriteFrame::create("monster1_1.png", Rect(0, 0, monster_texture_size, monster_texture_size)));
            animFrames.pushBack(SpriteFrame::create("monster1_2.png", Rect(0, 0, monster_texture_size, monster_texture_size)));
            Animation* animation = Animation::createWithSpriteFrames(animFrames, animate_duration);
            Animate* animate = Animate::create(animation);
            this->runAction(RepeatForever::create(animate));//��ͣŤ��
        }
        else if (this->monType == 2)
        {
            this->setTexture("monster2_1.png");//������ͼ
            this->setScale(0.9f);//������ͼ��С
            Vector<SpriteFrame*> animFrames;
            animFrames.reserve(3);
            animFrames.pushBack(SpriteFrame::create("monster2_1.png", Rect(0, 0, monster_texture_size, monster_texture_size)));
            animFrames.pushBack(SpriteFrame::create("monster2_2.png", Rect(0, 0, monster_texture_size, monster_texture_size)));
            animFrames.pushBack(SpriteFrame::create("monster2_3.png", Rect(0, 0, monster_texture_size, monster_texture_size)));
            Animation* animation = Animation::createWithSpriteFrames(animFrames, animate_duration);
            Animate* animate = Animate::create(animation);
            this->runAction(RepeatForever::create(animate));//��ͣŤ��
        }
        else if (this->monType == 3)
        {
            this->setTexture("monster3_1.png");//������ͼ
            this->setScale(0.9f);//������ͼ��С
            Vector<SpriteFrame*> animFrames;
            animFrames.reserve(3);
            animFrames.pushBack(SpriteFrame::create("monster3_1.png", Rect(0, 0, monster_texture_size, monster_texture_size)));
            animFrames.pushBack(SpriteFrame::create("monster3_2.png", Rect(0, 0, monster_texture_size, monster_texture_size)));
            animFrames.pushBack(SpriteFrame::create("monster3_3.png", Rect(0, 0, monster_texture_size, monster_texture_size)));
            Animation* animation = Animation::createWithSpriteFrames(animFrames, animate_duration);
            Animate* animate = Animate::create(animation);
            this->runAction(RepeatForever::create(animate));//��ͣŤ��
        }
        else if (this->monType == 4)
        {
            this->setTexture("monster4_1.png");//������ͼ
            this->setScale(0.9f);//������ͼ��С
            Vector<SpriteFrame*> animFrames;
            animFrames.reserve(3);
            animFrames.pushBack(SpriteFrame::create("monster4_1.png", Rect(0, 0, monster_texture_size, monster_texture_size)));
            animFrames.pushBack(SpriteFrame::create("monster4_2.png", Rect(0, 0, monster_texture_size, monster_texture_size)));
            animFrames.pushBack(SpriteFrame::create("monster4_3.png", Rect(0, 0, monster_texture_size, monster_texture_size)));
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
    void monster_die(std::vector<MonSprite*>currentWave)
    {
        this->stopAllActions();
        this->runAction(FadeOut::create(fade_time));//���ﵭ��
        currentWave.erase(find(currentWave.begin(), currentWave.end(), this));//������
        this->removeAllChildren();
    }

    //��������
    void monster_hurt(std::vector<MonSprite*>currentWave, int hit_point)
    {
        this->monVitality -= hit_point;
        this->runAction(Blink::create(blink_duration, blink_time));
        monster_die(currentWave);//�жϹ�������
    }

    //�����ܲ��������˺�
    void monster_attack_carrot(Carrot* carrot, std::vector<MonSprite*>currentWave)
    {
        wait_for_condition_and_execute(
            [=]()
            {
                return carrot->getBoundingBox().intersectsRect(this->getBoundingBox());
            },
            [=]()
            {
                this->monster_die(currentWave);//������
                carrot->hurt(this->monAttack);
            }
            );
    }
};


