#include"cocos2d.h"
using namespace cocos2d;

class Carrot : public cocos2d::Sprite
{
public:
	int HP = 10;//生命值
	int level = 1;//萝卜等级
	static Carrot* create(const std::string& filename);
	template<typename T>
	void hurt(const T damage);//萝卜受伤，战损
	void change();//改变萝卜外貌
	bool if_dead();//判断萝卜是否死亡
};
