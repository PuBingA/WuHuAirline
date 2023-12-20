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
    //������Ļص�����
    void onMouseDown(EventMouse* event)
    {
        Vec2 clickPos = Vec2(event->getCursorX(), event->getCursorY());
        if (event->getMouseButton() == EventMouse::MouseButton::BUTTON_LEFT)        //����Ƿ������������
        {
            if (IsMonsterClicked(clickPos))//�ڹ����ϵ����ִ����Ӧ�߼�
            {
                ShowRedFrame();
            }
            else if (IsRoadSideClicked(clickPos))//�ڵ�·���Ե����ִ����Ӧ�߼�
            {
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

    //�������ĺ���
    void ShowRedFrame()
    {
        auto RedFrame = Sprite::create("red_frame.png");
        addChild(RedFrame);
    }

    //�����ƿ�ĺ���
    void ShowYellowFrame(const Vec2& position)
    {
        auto YellowFrame = Sprite::create("yellow_frame.png");
        addChild(YellowFrame);
        YellowFrame->setPosition(position);
    }
};
