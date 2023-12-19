#include"carrot.h"
using namespace std;

/*----------------------ÂÜ²·Àà-------------------------*/
Carrot* Carrot::create(const std::string& filename)
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

/*----------------------ÂÜ²·Àà-------------------------*/