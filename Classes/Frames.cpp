#include "Frames.h"
#include "public_define.h"
USING_NS_CC;

void FrameBox::Spawn(int x, int y)
{
	Current->setScale(0.5);
	Current->setPosition(x, y);
}


void FrameBox::Shimmer()
{
	auto scaleTo = ScaleTo::create(0.3, 0.7);
	auto scaleBack = ScaleTo::create(0.3, 0.5);
	auto seq = Sequence::create(scaleTo, scaleBack, nullptr);
	Current->runAction(RepeatForever::create(seq));
}

void FrameBox::Disappear()
{
	Current->stopAllActions();
	Current->runAction(FadeOut::create(fade_time));
}

bool IsFrame(int& x, int& y)	//if (level == 1)
{
	for (auto& adjust_coord : AllFrames)
	{
		if (x > adjust_coord.left_up._x && x < adjust_coord.right_down._x && y > adjust_coord.right_down._y && y < adjust_coord.left_up._y)
		{
			x = adjust_coord.adjusted._x;
			y = adjust_coord.adjusted._y;
			return true;
		}
	}
	return false;
}
