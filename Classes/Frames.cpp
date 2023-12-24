#include "Frames.h"
#include "public_define.h"
USING_NS_CC;

FrameBox* FrameBox::create(const std::string& filename)
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


void FrameBox::Spawn(float x, float y, float scale)
{
	this->setScale(scale);
	this->setPosition(x, y);
}


void FrameBox::Shimmer()
{
	auto scaleTo = ScaleTo::create(0.3f, 0.7f);
	auto scaleBack = ScaleTo::create(0.3f, 0.5f);
	auto seq = Sequence::create(scaleTo, scaleBack, nullptr);
	this->runAction(RepeatForever::create(seq));
}

void FrameBox::Disappear()
{
	this->stopAllActions();
	this->runAction(FadeOut::create(fade_time));
}

void FrameBox::RotateAndLock()
{
	float duration = 1.0f, angle = 45.0f;
	auto rotateAction = RotateBy::create(duration, angle);
	this->runAction(rotateAction);
}

bool IsFrame(float& x, float& y, const std::vector<FS>& allframes)
{
	for (auto& adjust_coord : allframes)
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

bool IsFramePlant(float& x, float& y, const std::vector<FS>& allplants)
{
	for (auto& adjust_coord : allplants)
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