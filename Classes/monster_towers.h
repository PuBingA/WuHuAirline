#include "cocos2d.h"
#include "ui/CocosGUI.h"
#include "public_define.h"
#include "carrot.h"
#include <vector>
#include <string>
#include <algorithm>
USING_NS_CC;

class MonSprite : public Sprite//怪物类
{
private:
    int monType = 1;
    int monVitality = 1;//生命
    int monAttack = 1;//攻击力
    int monSpeed = 1;//速度
    ui::LoadingBar* monLifeBar = NULL;

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
		case 5:
			monVitality = mon5_vit;
			monAttack = mon5_atk;
			monSpeed = mon5_spd;
			break;
		}
        monCurrentLife = monVitality;
    }
public:
    int monCurrentLife = 1;
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
            //monster_sprite->autorelease();
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

    //生成一个怪物并开始移动
    void monster_spawn(std::vector<std::vector<float>>walkPath)
    {
        this->setPosition(walkPath[0][0], walkPath[0][1]);
        this->setScale(0.8f);//设置贴图大小
        Vector<SpriteFrame*> animFrames;
        if (this->monType == 1)
        {
            animFrames.reserve(2);
            animFrames.pushBack(SpriteFrame::create("monster1_1.png", Rect(0, 0, monster_texture_size, monster_texture_size)));
            animFrames.pushBack(SpriteFrame::create("monster1_2.png", Rect(0, 0, monster_texture_size, monster_texture_size)));
        }
        else if (this->monType == 2)
        {
            animFrames.reserve(3);
            animFrames.pushBack(SpriteFrame::create("monster2_1.png", Rect(0, 0, monster_texture_size, monster_texture_size)));
            animFrames.pushBack(SpriteFrame::create("monster2_2.png", Rect(0, 0, monster_texture_size, monster_texture_size)));
            animFrames.pushBack(SpriteFrame::create("monster2_3.png", Rect(0, 0, monster_texture_size, monster_texture_size)));
        }
        else if (this->monType == 3)
        {
            animFrames.reserve(3);
            animFrames.pushBack(SpriteFrame::create("monster3_1.png", Rect(0, 0, monster_texture_size, monster_texture_size)));
            animFrames.pushBack(SpriteFrame::create("monster3_2.png", Rect(0, 0, monster_texture_size, monster_texture_size)));
            animFrames.pushBack(SpriteFrame::create("monster3_3.png", Rect(0, 0, monster_texture_size, monster_texture_size)));
        }
        else if (this->monType == 4)
        {
            animFrames.reserve(3);
            animFrames.pushBack(SpriteFrame::create("monster4_1.png", Rect(0, 0, monster_texture_size, monster_texture_size)));
            animFrames.pushBack(SpriteFrame::create("monster4_2.png", Rect(0, 0, monster_texture_size, monster_texture_size)));
            animFrames.pushBack(SpriteFrame::create("monster4_3.png", Rect(0, 0, monster_texture_size, monster_texture_size)));
        }
		else if (this->monType == 5)
		{
			animFrames.reserve(3);
			animFrames.pushBack(SpriteFrame::create("monster5_1.png", Rect(0, 0, boss_texture_size, boss_texture_size)));
			animFrames.pushBack(SpriteFrame::create("monster5_2.png", Rect(0, 0, boss_texture_size, boss_texture_size)));
			animFrames.pushBack(SpriteFrame::create("monster5_3.png", Rect(0, 0, boss_texture_size, boss_texture_size)));
		}
		Animation* animation = Animation::createWithSpriteFrames(animFrames, animate_duration);
        Animate* animate = Animate::create(animation);
        this->runAction(RepeatForever::create(animate));//不停扭动

        Vector<FiniteTimeAction*> monster_move_sequence;
        //怪物淡入，显示出来
        monster_move_sequence.pushBack(FadeIn::create(fade_time));
        for (auto& monster_walk_point : walkPath)
            monster_move_sequence.pushBack(MoveTo::create((base_move_time / this->monSpeed), Vec2(monster_walk_point[0], monster_walk_point[1])));
        monster_move_sequence.pushBack(FadeIn::create(fade_time));
        this->runAction(Sequence::create(monster_move_sequence));
    }

    //怪物去世
    void monster_die()
    {
		this->removeAllChildren();
		Node* wave = this->getParent();
		if (wave)
			wave->removeChild(this);//怪似了
    }

    //怪物受伤
    bool monster_hurt(int hit_point)
    {
        monCurrentLife -= hit_point;
        if (monCurrentLife < 0)
            monCurrentLife = 0;
        if (monCurrentLife <= 0)
        {
            monster_die();//死亡
            return 1;
        }
		monLifeBar->setPercent(static_cast<float>(monCurrentLife) / monVitality * 100);
        runAction(Blink::create(blink_duration, blink_time));
        return 0;
    }

    //攻击萝卜，返回伤害
    void monster_attack_carrot(Carrot* carrot)
    {
        wait_for_condition_and_execute([=](){return carrot->getBoundingBox().intersectsRect(this->getBoundingBox());},
			[=]()
			{
				carrot->hurt(this->monAttack);
				carrot->hurt(this->monAttack);
				this->monster_die();//怪物死
			});
    }
};


class Tower : public cocos2d::Sprite
{
public:
	int distance = 0;//攻击距离
	int level = 0;
	int bullet_atk = 0;
	MonSprite* lock_target = nullptr;
	Node* monster_wave = nullptr;
};

class Cannon : public Tower
{
public:
	static Cannon* create(const std::string& filename, Node* monwave)//初始化精灵
	{
		Cannon* cannon_sprite = new Cannon();
		if (cannon_sprite && cannon_sprite->initWithFile(filename))
		{
			cannon_sprite->monster_wave = monwave;
			cannon_sprite->level = 1;
			cannon_sprite->guard();
			return cannon_sprite;
		}
		CC_SAFE_DELETE(cannon_sprite);
		return nullptr;
	}

	void guard()
	{
		switch (level)
		{
			case 1:
				distance = bullet_range1;
				bullet_atk = cannon1_atk;
				break;
			case 2:
				distance = bullet_range2;
				bullet_atk = cannon2_atk;
				break;
			case 3:
				distance = bullet_range3;
				bullet_atk = cannon3_atk;
				break;
		}
		schedule([=](float dt)
			{
				for (auto& target : monster_wave->getChildren())
					if (this->getPosition().distance(target->getPosition()) <= distance)
					{
						lock_target = (MonSprite*)(target);
						auto relative_position = lock_target->getPosition() - this->getPosition();
						setRotation(relative_position.getAngle(Vec2(0, 1)) * 180 / 3.14);
						auto bullet = Sprite::create();
						bullet->setPosition(-relative_position);
						lock_target->addChild(bullet);
						auto bullet_fly = MoveTo::create(bullet_fly_time, Vec2(monster_texture_size / 2, monster_texture_size / 2));
						bullet->runAction(bullet_fly);
						switch (level)
						{
							case 1:
								bullet->setTexture("cannon_bullet_1.png");
								break;
							case 2:
								bullet->setTexture("cannon_bullet_2.png");
								break;
							case 3:
								bullet->setTexture("cannon_bullet_3.png");
								break;
						}
						scheduleOnce([=](float dt)
							{
								if (lock_target)
								{
									lock_target->removeChild(bullet, 1);
									lock_target->monster_hurt(bullet_atk);
								}
							}, bullet_fly_time, "CannonBulletTag");

						break;
					}
			}, bullet_shoot_interval, "CannonGuardTag");
	}
};

class Shit : public Tower
{
public:
	static Shit* create(const std::string& filename, Node* monwave)//初始化精灵
	{
		Shit* shit_sprite = new Shit();
		if (shit_sprite && shit_sprite->initWithFile(filename))
		{
			shit_sprite->monster_wave = monwave;
			shit_sprite->level = 1;
			shit_sprite->guard();
			return shit_sprite;
		}
		CC_SAFE_DELETE(shit_sprite);
		return nullptr;
	}

	void guard()
	{
		switch (level)
		{
			case 1:
				distance = bullet_range1;
				bullet_atk = shit1_atk;
				break;
			case 2:
				distance = bullet_range2;
				bullet_atk = shit2_atk;
				break;
			case 3:
				distance = bullet_range3;
				bullet_atk = shit3_atk;
				break;
		}
		schedule([=](float dt)
			{
				for (auto& target : monster_wave->getChildren())
					if (this->getPosition().distance(target->getPosition()) <= distance)
					{
						lock_target = (MonSprite*)(target);
						auto relative_position = lock_target->getPosition() - this->getPosition();
						setRotation(relative_position.getAngle(Vec2(0, 1)) * 180 / 3.14);
						auto bullet = Sprite::create("shit_bullet.png");
						bullet->setPosition(-relative_position);
						lock_target->addChild(bullet);
						auto bullet_fly = MoveTo::create(bullet_fly_time, Vec2(monster_texture_size / 2, monster_texture_size / 2));
						bullet->runAction(bullet_fly);
						scheduleOnce([=](float dt)
							{
								if (lock_target)
								{
									lock_target->removeChild(bullet, 1);
									lock_target->monster_hurt(bullet_atk);
								}
							}, bullet_fly_time, "ShitBulletTag");

						break;
					}
			}, bullet_shoot_interval, "ShitGuardTag");
	}
};

class Etower : public Tower
{
public:
	static Etower* create(const std::string& filename, Node* monwave)//初始化精灵
	{
		Etower* etower_sprite = new Etower();
		if (etower_sprite && etower_sprite->initWithFile(filename))
		{
			etower_sprite->monster_wave = monwave;
			etower_sprite->level = 1;
			etower_sprite->guard();
			etower_sprite->autorelease();
			return etower_sprite;
		}
		CC_SAFE_DELETE(etower_sprite);
		return nullptr;
	}
	void guard()
	{
		switch (level)
		{
			case 1:
				distance = bullet_range1;
				bullet_atk = etower1_atk;
				break;
			case 2:
				distance = bullet_range2;
				bullet_atk = etower2_atk;
				break;
			case 3:
				distance = bullet_range3;
				bullet_atk = etower3_atk;
				break;
		}
		schedule([=](float dt)
			{
				for (auto& target : monster_wave->getChildren())
					if (this->getPosition().distance(target->getPosition()) <= distance)
					{
						lock_target = (MonSprite*)(target);
						auto relative_position = lock_target->getPosition() - this->getPosition();
						auto bullet = Sprite::create("etower_bullet.png");
						bullet->setPosition(-relative_position);
						lock_target->addChild(bullet);
						auto bullet_fly = MoveTo::create(bullet_fly_time, Vec2(monster_texture_size / 2, monster_texture_size / 2));
						bullet->runAction(bullet_fly);
						scheduleOnce([=](float dt)
							{
								if (lock_target)
								{
									lock_target->removeChild(bullet, 1);
									lock_target->monster_hurt(bullet_atk);
								}
							}, bullet_fly_time, "EtowerBulletTag");

						break;
					}
			}, bullet_shoot_interval, "EtowerGuardTag");
	}
};
