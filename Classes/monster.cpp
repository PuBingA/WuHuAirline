#include "monster.h"
USING_NS_CC;

//-------------------------------�����ຯ��------------------------------------

MonSprite* MonSprite::create(const std::string& filename)
{
    MonSprite* monster_sprite = new MonSprite();

    if (monster_sprite && monster_sprite->initWithFile(filename))
    {
        monster_sprite->autorelease();
        return monster_sprite;
    }
    CC_SAFE_DELETE(monster_sprite);
    return nullptr;
}

void MonSprite::setData()
{
    monsterVitality= 50;
    monsterAttack = 5;
    monsterDefense = 5;
    monsterSpeed = 1.0f;
}

//------------------------------������ƺ���-----------------------------------

//��������
void MonCtrl::hurt(float hit_point)const
{
    currentMon->monsterVitality -= hit_point;
    currentMon->runAction(Blink::create(blink_duration,blink_time));
    if (currentMon->monsterVitality < 0)
        die();
}

//��������
void MonCtrl::die()const
{
    currentMon->stopAllActions();
    //���ﵭ����������ʾ
    currentMon->runAction(FadeOut::create(fade_time));
}

void MonCtrl::spawn()
{
    currentMon->setOpacity(0);//����ȫ͸��
    currentMon->setPosition(monsterWalkPath[0][0], monsterWalkPath[0][1]);
    //����������Ѫ��
    life_bar = ui::LoadingBar::create("life_bar.png");
    life_bar->setDirection(ui::LoadingBar::Direction::LEFT);
    life_bar->setPositionNormalized(Vec2(0.5, 0));
    life_bar->setPercent(100);
    currentMon->addChild(life_bar);
    move();
}

//�����ƶ�
void MonCtrl::move() const
{
    if (monType == 1)
    {
        currentMon->setTexture("monster1_1.png");
        currentMon->setScale(0.7);
        Vector<SpriteFrame*> animFrames;
        animFrames.reserve(2);
        animFrames.pushBack(SpriteFrame::create("monster1_1.png", Rect(0, 0, 135, 135)));
        animFrames.pushBack(SpriteFrame::create("monster1_2.png", Rect(0, 0, 135, 135)));
        Animation* animation = Animation::createWithSpriteFrames(animFrames, animate_duration);
        Animate* animate = Animate::create(animation);
        currentMon->runAction(RepeatForever::create(animate));//��ͣŤ��
    }

    Vector<FiniteTimeAction*> monster_move_sequence;
    //���ﵭ�룬��ʾ����
    monster_move_sequence.pushBack(FadeIn::create(fade_time));
    for (auto& monster_walk_point : monsterWalkPath)
        monster_move_sequence.pushBack(MoveTo::create((base_move_time / currentMon->monsterSpeed), Vec2(monster_walk_point[0], monster_walk_point[1])));
    monster_move_sequence.pushBack(FadeIn::create(fade_time));
    auto seq = Sequence::create(monster_move_sequence);
    currentMon->runAction(seq);
}

