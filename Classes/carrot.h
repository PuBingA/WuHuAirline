#include"cocos2d.h"
USING_NS_CC;
class Carrot : public cocos2d::Sprite
{
public:
	cocos2d::Label* HP_Label;
	int HP = 10;//����ֵ
	int level = 1;//�ܲ��ȼ�
	static Carrot* create(const std::string& filename);
	std::string calculate_HP(const int HP);
	void hurt(const int damage);//�ܲ����ˣ�ս��
	void change();//�ı��ܲ���ò
	bool if_dead();//�ж��ܲ��Ƿ�����
};
