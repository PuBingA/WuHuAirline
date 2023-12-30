#include "cocos2d.h"
#include "ui/CocosGUI.h"
#include "public_define.h"
#include "carrot.h"
#include <vector>
#include <string>
#include <algorithm>
#include"AudioEngine.h"
USING_NS_CC;

class MonSprite : public Sprite//������
{
	friend class Map_father;
	friend class Shit;
private:
    int monType = 1;
    int monVitality = 1;//����
    int monAttack = 1;//������
    int monSpeed = 1;//�ٶ�
    int if_broken = 0;//�Ƿ�����ֵȼ����ߵȼ����ǵ͵ȼ�buff
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
		case 5:
			monVitality = mon5_vit;
			monAttack = mon5_atk;
			monSpeed = mon5_spd;
			break;
		case 6:
			monVitality = mon6_vit;
			monAttack = mon6_atk;
			monSpeed = mon6_spd;
			break;
		case 7:
			monVitality = mon7_vit;
			monAttack = mon7_atk;
			monSpeed = mon7_spd;
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
        {//����������Ѫ��
            monster_sprite->setType(type);
            monster_sprite->setOpacity(0);//����ȫ͸��
            monster_sprite->monLifeBar = ui::LoadingBar::create("life_bar.png");
            monster_sprite->monLifeBar->setDirection(ui::LoadingBar::Direction::LEFT);
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

    //����һ�����ﲢ��ʼ�ƶ�
    void monster_spawn(std::vector<std::vector<float>>walkPath)
    {
        this->setPosition(walkPath[0][0], walkPath[0][1]);
        this->setScale(0.8f);//������ͼ��С
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
			animFrames.pushBack(SpriteFrame::create("monster5_1.png", Rect(0, 0, boss1_texture_size, boss1_texture_size)));
			animFrames.pushBack(SpriteFrame::create("monster5_2.png", Rect(0, 0, boss1_texture_size, boss1_texture_size)));
			animFrames.pushBack(SpriteFrame::create("monster5_3.png", Rect(0, 0, boss1_texture_size, boss1_texture_size)));
		}
		else if (this->monType == 6||this->monType==7)
		{
			animFrames.reserve(3);
			animFrames.pushBack(SpriteFrame::create("monster6_1.png", Rect(0, 0, boss2_texture_size, boss2_texture_size)));
			animFrames.pushBack(SpriteFrame::create("monster6_2.png", Rect(0, 0, boss2_texture_size, boss2_texture_size)));
			animFrames.pushBack(SpriteFrame::create("monster6_3.png", Rect(0, 0, boss2_texture_size, boss2_texture_size)));
		}
		Animation* animation = Animation::createWithSpriteFrames(animFrames, animate_duration);
        Animate* animate = Animate::create(animation);
        this->runAction(RepeatForever::create(animate));//��ͣŤ��

        Vector<FiniteTimeAction*> monster_move_sequence;
        //���ﵭ�룬��ʾ����
        monster_move_sequence.pushBack(FadeIn::create(fade_time));
        for (auto& monster_walk_point : walkPath)
            monster_move_sequence.pushBack(MoveTo::create((base_move_time / this->monSpeed), Vec2(monster_walk_point[0], monster_walk_point[1])));
        monster_move_sequence.pushBack(FadeIn::create(fade_time));
        this->runAction(Sequence::create(monster_move_sequence));
    }

    //����ȥ��
    int monster_die()
    {
		auto die_effect= AudioEngine::play2d("monster_die.mp3", false);
		int award = monster_basical_cost;
		for (int i = 1; i < monType; i++)
			award += 20;//��ͬ���࣬��ͬ������
		this->monCurrentLife = 0;//������������
		this->removeAllChildren();
		Node* wave = this->getParent();
		if (wave)
			wave->removeChild(this);//������
		return award;
    }

    //��������
    bool monster_hurt(int hit_point)
    {
        monCurrentLife -= (hit_point+if_broken);//��������buff�˺�
        if (monCurrentLife <= 0)
        {
            return 1;
        }
		monLifeBar->setPercent(static_cast<float>(monCurrentLife) / monVitality * 100);
        return 0;
    }

	//��������buff
	void monster_broken_down(const int buff_level)
	{
		if (buff_level>if_broken)
		{
			Color3B slow_down_buff(255, 0, 0);
			this->setColor(slow_down_buff);
			if_broken = buff_level;
		}
	}

    //�����ܲ��������˺�
    void monster_attack_carrot(Carrot* carrot)
    {
        wait_for_condition_and_execute([=](){return carrot->getBoundingBox().intersectsRect(this->getBoundingBox());},
			[=]()
			{
				carrot->hurt(this->monAttack);
				carrot->hurt(1);
				this->monster_die();//������
			});
    }
};


class Tower : public Sprite
{
public:
	int distance = 0;//��������
	int level = 0;
	int bullet_atk = 0;
	MonSprite* lock_target = nullptr;
	Node* monster_wave = nullptr;
};

class Cannon : public Tower
{
public:
	static Cannon* create(const std::string& filename, Node* monwave, int * gold)//��ʼ������
	{
		Cannon* cannon_sprite = new Cannon();
		auto plant_effect = AudioEngine::play2d("plant_effect.mp3", false);
		if (cannon_sprite && cannon_sprite->initWithFile(filename))
		{
			cannon_sprite->monster_wave = monwave;
			cannon_sprite->level = 1;
			cannon_sprite->guard(gold);
			return cannon_sprite;
		}
		CC_SAFE_DELETE(cannon_sprite);
		return nullptr;
	}

	void guard(int*gold)
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
					if (this->getPosition().distance(target->getPosition()) <= distance)//�ڹ�����Χ��
					{
						lock_target = (MonSprite*)(target);
						auto relative_position = lock_target->getPosition() - this->getPosition();
						setRotation(relative_position.getAngle(Vec2(0, 1)) * 180 / 3.14);
						auto bullet = Sprite::create();
						bullet->setPosition(-relative_position);
						lock_target->addChild(bullet);
						auto bullet_fly = MoveTo::create(bullet_fly_time, Vec2(monster_texture_size / 2, monster_texture_size / 2));
						bullet->runAction(bullet_fly);
						auto bullet_effect = AudioEngine::play2d("shoot.mp3", false);//�ӵ��ɳ�
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
									if (lock_target->monster_hurt(bullet_atk))
										*gold += lock_target->monster_die();//�����
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
	static Shit* create(const std::string& filename, Node* monwave,int*gold)//��ʼ������
	{
		Shit* shit_sprite = new Shit();
		auto plant_effect = AudioEngine::play2d("plant_effect.mp3", false);
		if (shit_sprite && shit_sprite->initWithFile(filename))
		{
			shit_sprite->monster_wave = monwave;
			shit_sprite->level = 1;
			shit_sprite->guard(gold);
			return shit_sprite;
		}
		CC_SAFE_DELETE(shit_sprite);
		return nullptr;
	}

	void guard(int* gold)
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
						auto bullet_effect = AudioEngine::play2d("shoot.mp3", false);//�ӵ��ɳ�
						scheduleOnce([=](float dt)
							{
								if (lock_target)
								{
									lock_target->removeChild(bullet, 1);
									lock_target->monster_broken_down(this->level);//���⼼�ܣ���������buff
									if (lock_target->monster_hurt(bullet_atk))
										*gold += lock_target->monster_die();//�����
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
	static Etower* create(const std::string& filename, Node* monwave, int*gold)//��ʼ������
	{
		Etower* etower_sprite = new Etower();
		auto plant_effect = AudioEngine::play2d("plant_effect.mp3", false);
		if (etower_sprite && etower_sprite->initWithFile(filename))
		{
			etower_sprite->monster_wave = monwave;
			etower_sprite->level = 1;
			etower_sprite->guard(gold);
			etower_sprite->autorelease();
			return etower_sprite;
		}
		CC_SAFE_DELETE(etower_sprite);
		return nullptr;
	}
	void guard(int* gold)
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
					auto bullet_effect = AudioEngine::play2d("shoot.mp3", false);
					scheduleOnce([=](float dt)
						{
							if (lock_target)
							{
								lock_target->removeChild(bullet, 1);
								if (lock_target->monster_hurt(bullet_atk))
									*gold += lock_target->monster_die();//�����
							}
						}, bullet_fly_time, "EtowerBulletTag");

					break;
				}
			}, bullet_shoot_interval, "EtowerGuardTag");
	}
};
