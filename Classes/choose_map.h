#include "cocos2d.h"
#include"public_define.h"
#include"map.h"
#include "AudioEngine.h"

enum choose_scene_2
{
    back,//���ؿ�ʼ����
    map1,//�����һ�ŵ�ͼ
    map2,//����ڶ��ŵ�ͼ
    map3,//��������ŵ�ͼ
};


class choose_map :public cocos2d::Scene//�̳г�����
{
private:
    int choose_map_bgm;//��������ֲ��
public:
    static cocos2d::Scene* createScene();

    virtual bool init();//����������

    void menuCallback(cocos2d::Ref* pSender,choose_scene_2 choose_map);//�˵���Ӧ����

    // implement the "static create()" method manually
    CREATE_FUNC(choose_map);

};
