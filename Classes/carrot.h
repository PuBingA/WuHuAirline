#include"cocos2d.h"
USING_NS_CC;
class Carrot : public cocos2d::Sprite
{
public:
	cocos2d::Label* HP_Label = nullptr;
	int HP = 10;//生命值
	int level = 1;//萝卜等级
	static Carrot* create(const std::string& filename)//生成萝卜类
    {
        Carrot* carrot_sprite = new Carrot();

        if (carrot_sprite && carrot_sprite->initWithFile(filename))
        {
            carrot_sprite->HP_Label = Label::createWithTTF("", "fonts\\Marker Felt.ttf", 40);
            carrot_sprite->HP_Label->setColor({ 255,0,0 });//调成红色
            carrot_sprite->HP_Label->setPosition(100, 0);
            carrot_sprite->addChild(carrot_sprite->HP_Label);//生成好血量标签
            auto Hp_item = Sprite::create("carrot_HP.png");
            Hp_item->setPosition(30, 0);
            carrot_sprite->addChild(Hp_item);//生成血量图标
            carrot_sprite->change_tex();
            carrot_sprite->autorelease();
            return carrot_sprite;
        }
        CC_SAFE_DELETE(carrot_sprite);
        return nullptr;
    }

	std::string calculate_HP(const int HP)//根据萝卜血量生成字符串
    {
        std::string figure;
        int digit = 10;//十位
        for (int i = 0; i < 2; i++)
        {
            int k = (HP / digit) % 10;
            digit /= 10;
            figure += k + '0';
        }//计算出每一位的数字，放入字符串中
        return figure;
    }

	void hurt(const int damage)//萝卜受伤
    {
        HP -= damage;
        if (HP <= 0)
            HP = 0;//HP修正
        HP_Label->setString(calculate_HP(HP));
        change_tex();
    }

	void change_tex()//改变萝卜外貌
    {
        switch (level)
        {
            case 1:
                if (HP == 10)
                    this->setTexture("carrot_level1_1.png");
                if (HP < 10 && HP >= 8)
                    this->setTexture("carrot_level1_2.png");
                if (HP < 8 && HP >= 6)
                    this->setTexture("carrot_level1_3.png");
                if (HP < 6 && HP >= 4)
                    this->setTexture("carrot_level1_4.png");
                if (HP < 4 && HP >= 0)
                    this->setTexture("carrot_level1_5.png");
                break;
            case 2:
                if (HP >= 10)
                    this->setTexture("carrot_level2_1.png");
                if (HP < 10 && HP >= 5)
                    this->setTexture("carrot_level2_2.png");
                if (HP < 5 && HP >= 0)
                    this->setTexture("carrot_level2_3.png");
                break;
            case 3:
                this->setTexture("carrot_level3.png");
                break;
        }
    }

};
