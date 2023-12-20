#include"carrot.h"
<<<<<<< Updated upstream
using namespace std;

/*----------------------萝卜类-------------------------*/
Carrot* Carrot::create(const std::string& filename)
=======
using namespace cocos2d;

/*----------------------萝卜类-------------------------*/

Carrot* Carrot::create(const std::string& filename)//生成萝卜类
>>>>>>> Stashed changes
{
    Carrot* carrot_sprite = new Carrot();

    if (carrot_sprite && carrot_sprite->initWithFile(filename))
    {
        carrot_sprite->autorelease();
        return carrot_sprite;
    }
    CC_SAFE_DELETE(carrot_sprite);
    return nullptr;
}

/*----------------------萝卜类-------------------------*/