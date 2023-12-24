#include"carrot.h"
USING_NS_CC;

/*----------------------¬‹≤∑¿‡-------------------------*/

Carrot* Carrot::create(const std::string& filename)//…˙≥…¬‹≤∑¿‡
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

template<typename T>
void Carrot::hurt(const T damage)//¬‹≤∑ ‹…À
{
    HP -= damage;
    if (HP < 0)
        HP == 0;//HP–ﬁ’˝
    return;
}

void Carrot::change()//∏ƒ±‰¬‹≤∑Õ‚√≤
{
    if (level == 1)
    {
        if(HP==10)
            this->setTexture("carrot_level1_1.png");

        if (HP < 10 && HP >= 8)
            this->setTexture("carrot_level1_2.png");
        if (HP < 8 && HP >= 6)
            this->setTexture("carrot_level1_3.png");
        if (HP < 6 && HP >= 4)
            this->setTexture("carrot_level1_4.png");
        if (HP < 4 && HP >= 0)
            this->setTexture("carrot_level1_5.png");
    }

    if (level == 2)
    {
        if (HP >= 10)
            this->setTexture("carrot_level2_1.png");
        if (HP < 10 && HP >= 5)
            this->setTexture("carrot_level2_2.png");
        if (HP < 5 && HP >= 0)
            this->setTexture("carrot_level2_3.png");
    }
 
    if (level == 3)
    {
        this->setTexture("carrot_level3.png");
    }
}

bool Carrot::if_dead()//≈–∂œ¬‹≤∑ «∑ÒÀ¿Õˆ
{
    if (HP > 0)
        return false;
    else
        return true;
}

/*----------------------¬‹≤∑¿‡-------------------------*/