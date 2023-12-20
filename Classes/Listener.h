#include <vector>
#include <string>
#include "cocos2d.h"
#include "public_define.h"
using namespace cocos2d;

class Listener : public Scene
{
public:
    Listener()
    {
        auto mouseListener = EventListenerMouse::create();
        mouseListener->onMouseDown = CC_CALLBACK_1(Listener::onMouseDown, this);
        _eventDispatcher->addEventListenerWithSceneGraphPriority(mouseListener, this);
    }
    //鼠标点击的回调函数
    void onMouseDown(EventMouse* event)
    {
        Vec2 clickPos = Vec2(event->getCursorX(), event->getCursorY());
        if (event->getMouseButton() == EventMouse::MouseButton::BUTTON_LEFT)        //检查是否是鼠标左键点击
        {
            if (IsMonsterClicked(clickPos))
            {
                // 在怪物上点击，执行相应逻辑
                ShowRedFrame();
            }
            else if (IsRoadSideClicked(clickPos))
            {
                // 在道路两旁点击，执行相应逻辑
                ShowYellowFrame(clickPos);
            }
        }
    }
    bool IsMonsterClicked(const Vec2& clickPos)
    {
        return false;
    }

    bool IsRoadSideClicked(const Vec2& clickPos)
    {
        return true;
    }

    // 弹出红框的函数
    void ShowRedFrame()
    {
        auto RedFrame = Sprite::create("red_frame.png");
        addChild(RedFrame);
    }

    // 弹出黄框的函数
    void ShowYellowFrame(const Vec2& position)
    {
        auto YellowFrame = Sprite::create("yellow_frame.png");
        addChild(YellowFrame);
        YellowFrame->setPosition(position);
    }
};
