#include"cocos2d.h"
using namespace cocos2d;

class Carrot : public cocos2d::Sprite
{
public:
	int HP = 10;//����ֵ
	int level = 1;//�ܲ��ȼ�
	static Carrot* create(const std::string& filename);
	template<typename T>
	void hurt(const T damage);//�ܲ����ˣ�ս��
	void change();//�ı��ܲ���ò
	bool if_dead();//�ж��ܲ��Ƿ�����
};
