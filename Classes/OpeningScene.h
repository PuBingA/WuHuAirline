#include "cocos2d.h"
#include"public_define.h"
#include "AudioEngine.h"

enum choose_scene
{
    close,//�ر�
    begining//��ʼѡ���ͼ
};//�������л������Ĳ��������ڼ��л���������

class Opening : public cocos2d::Scene
{
public:
    static cocos2d::Scene* createScene();

    virtual bool init();//������������
    
    void menuCallback(cocos2d::Ref* pSender, const choose_scene opening_menu);//�˵���Ӧ����
    
    CREATE_FUNC(Opening);

    /*һ����Ϊ�Ŷ��Զ���ĺ���*/
    template<class T,class K>
    void label_output(cocos2d::Label* my_label, T wide, K high);//�����ǩ
};
