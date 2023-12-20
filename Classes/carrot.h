#include"cocos2d.h"

class Carrot : public cocos2d::Sprite
{
private:
	int carrot_HP = 100;//ÉúÃüÖµ
public:
	static Carrot* create(const std::string& filename);

};
