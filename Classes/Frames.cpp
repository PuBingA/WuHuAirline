#include "Frames.h"
#include "public_define.h"
USING_NS_CC;

FrameBox* FrameBox::create(const std::string& filename)//Éú³ÉÂÜ²·Àà
{
	FrameBox* frame_box = new FrameBox();

	if (frame_box && frame_box->initWithFile(filename))
	{
		frame_box->autorelease();
		return frame_box;
	}
	CC_SAFE_DELETE(frame_box);
	return nullptr;
}


void FrameBox::Spawn(int x, int y, float scale)
{
	this->setScale(scale);
	this->setPosition(x, y);
}


void FrameBox::Shimmer()
{
	auto scaleTo = ScaleTo::create(0.3, 0.7);
	auto scaleBack = ScaleTo::create(0.3, 0.5);
	auto seq = Sequence::create(scaleTo, scaleBack, nullptr);
	this->runAction(RepeatForever::create(seq));
}

void FrameBox::Disappear()
{
	this->stopAllActions();
	this->runAction(FadeOut::create(fade_time));
}

void FrameBox::Rotate(float duration, float angle)
{
	auto rotateAction = RotateBy::create(duration, angle);
	this->runAction(rotateAction);
}

bool IsFrame_Lv1(int& x, int& y)	//if (level == 1)
{
	for (auto& adjust_coord : AllFrames_Lv1)
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

bool IsFramePlant_Lv1(int& x, int& y)
{
	for (auto& adjust_coord : AllPlants_Lv1)
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
