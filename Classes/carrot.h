#include"cocos2d.h"
USING_NS_CC;
class Carrot : public cocos2d::Sprite
{
public:
	cocos2d::Label* HP_Label = nullptr;
	int HP = 10;//����ֵ
	int level = 1;//�ܲ��ȼ�
	static Carrot* create(const std::string& filename)//�����ܲ���
    {
        Carrot* carrot_sprite = new Carrot();

        if (carrot_sprite && carrot_sprite->initWithFile(filename))
        {
            carrot_sprite->HP_Label = Label::createWithTTF("", "fonts\\Marker Felt.ttf", 40);
            carrot_sprite->HP_Label->setColor({ 255,0,0 });//���ɺ�ɫ
            carrot_sprite->HP_Label->setPosition(100, 0);
            carrot_sprite->addChild(carrot_sprite->HP_Label);//���ɺ�Ѫ����ǩ
            auto Hp_item = Sprite::create("carrot_HP.png");
            Hp_item->setPosition(30, 0);
            carrot_sprite->addChild(Hp_item);//����Ѫ��ͼ��
            carrot_sprite->change_tex();
            carrot_sprite->autorelease();
            return carrot_sprite;
        }
        CC_SAFE_DELETE(carrot_sprite);
        return nullptr;
    }

	std::string calculate_HP(const int HP)//�����ܲ�Ѫ�������ַ���
    {
        std::string figure;
        int digit = 10;//ʮλ
        for (int i = 0; i < 2; i++)
        {
            int k = (HP / digit) % 10;
            digit /= 10;
            figure += k + '0';
        }//�����ÿһλ�����֣������ַ�����
        return figure;
    }

	void hurt(const int damage)//�ܲ�����
    {
        HP -= damage;
        if (HP <= 0)
            HP = 0;//HP����
        HP_Label->setString(calculate_HP(HP));
        change_tex();
    }

	void change_tex()//�ı��ܲ���ò
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
