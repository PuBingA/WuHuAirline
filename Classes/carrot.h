#include"cocos2d.h"
using namespace cocos2d;
class Carrot : public cocos2d::Sprite
{
<<<<<<< Updated upstream
private:
	int carrot_HP = 10;//生命值
=======
>>>>>>> Stashed changes
public:
	int HP = 10;//生命值
	static Carrot* create(const std::string& filename);
};
