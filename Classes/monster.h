#include "cocos2d.h"
#include "ui/CocosGUI.h"
#include "public_define.h"
#include <vector>
USING_NS_CC;

class MonsterController;

class MonSprite : public cocos2d::Sprite//怪物类
{
private:
    int monType = 1;
    float monVitality = 1;//生命
    float monAttack = 1;//攻击力
    float monSpeed = 1;//速度
    float monCurrentLife = 1;
    cocos2d::ui::LoadingBar* monLifeBar = NULL;

    void setType(int type)//设置数值
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
    /**********************12.23 新增**************************/
    friend class FrameBox;
    /**********************12.23 新增**************************/
    friend class MonsterController;

    static MonSprite* create(int type = 0)
    {
        MonSprite* monster_sprite = new MonSprite();
        if (monster_sprite && monster_sprite->init())
        {//给精灵增加血条
            monster_sprite->setType(type);
            monster_sprite->setOpacity(0);//先完全透明
            monster_sprite->monLifeBar = cocos2d::ui::LoadingBar::create("life_bar.png");
            monster_sprite->monLifeBar->setDirection(cocos2d::ui::LoadingBar::Direction::LEFT);
            monster_sprite->monLifeBar->setPositionNormalized(Vec2(0.5, 0));
            monster_sprite->monLifeBar->setPercent(100);
            monster_sprite->addChild(monster_sprite->monLifeBar);
            //自动释放
            monster_sprite->autorelease();
            return monster_sprite;
        }
        CC_SAFE_DELETE(monster_sprite);
        return nullptr;
    }

};


class MonsterController
{
public:
    //生成一个怪物并开始移动
    void monster_spawn(MonSprite* currentMon, std::vector<std::vector<float>>walkPath)
    {
        currentMon->setPosition(walkPath[0][0], walkPath[0][1]);
        if (currentMon->monType == 1)
        {
            currentMon->setTexture("monster1_1.png");
            currentMon->setScale(0.7f);
            Vector<SpriteFrame*> animFrames;
            animFrames.reserve(2);
            animFrames.pushBack(SpriteFrame::create("monster1_1.png", Rect(0, 0, 135, 135)));
            animFrames.pushBack(SpriteFrame::create("monster1_2.png", Rect(0, 0, 135, 135)));
            Animation* animation = Animation::createWithSpriteFrames(animFrames, animate_duration);
            Animate* animate = Animate::create(animation);
            currentMon->runAction(RepeatForever::create(animate));//不停扭动
        }

        Vector<FiniteTimeAction*> monster_move_sequence;
        //怪物淡入，显示出来
        monster_move_sequence.pushBack(FadeIn::create(fade_time));
        for (auto& monster_walk_point : walkPath)
            monster_move_sequence.pushBack(MoveTo::create((base_move_time / currentMon->monSpeed), Vec2(monster_walk_point[0], monster_walk_point[1])));
        monster_move_sequence.pushBack(FadeIn::create(fade_time));
        auto seq = Sequence::create(monster_move_sequence);
        currentMon->runAction(seq);
    }

    //怪物受伤，返回值代表目前的健康状态
    int monster_hurt(MonSprite* currentMon, float hit_point)
    {
        currentMon->monVitality -= hit_point;
        currentMon->runAction(Blink::create(blink_duration, blink_time));
        if (currentMon->monVitality < 0)
            return -1;//怪物死亡

        return 0;
    }

    //怪物死亡
    void monster_die(Node* currentWave, MonSprite* currentMon)
    {
        currentMon->stopAllActions();
        //怪物淡出
        currentMon->runAction(FadeOut::create(fade_time));
        currentWave->removeChild(currentMon);
    }
    
    //攻击萝卜
    void monAttackCarrot()
    {

    }


};

class MonsterSpawner
{
public:
    MonsterController monctrler;
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
        monctrler.monster_spawn(monster1, walk_way);
    }

    void spawn2(float dt)
    {
        monctrler.monster_spawn(monster2, walk_way);
    }

    void spawn3(float dt)
    {
        monctrler.monster_spawn(monster3, walk_way);
    }

    void spawn4(float dt)
    {
        monctrler.monster_spawn(monster4, walk_way);
    }

    void spawn5(float dt)
    {
        monctrler.monster_spawn(monster5, walk_way);
    }

};


