#include"cocos2d.h"
USING_NS_CC;
class Carrot : public cocos2d::Sprite
{
public:
	cocos2d::Label* HP_Label;
	int HP = 10;//生命值
	int level = 1;//萝卜等级
	static Carrot* create(const std::string& filename);
	std::string calculate_HP(const int HP);
	void hurt(const int damage);//萝卜受伤，战损
	void change_tex();//改变萝卜外貌
};
