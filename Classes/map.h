#include"cocos2d.h"
#include<vector>
#include"public_define.h"


class Map_father :public cocos2d::Scene
{
public:
    static cocos2d::Scene* createScene();

    virtual bool init();//����������,���̳й��в���
    virtual void input_background() {};//���ñ���ͼ
    virtual void input_walk_way() {};//���ù����н�·��
<<<<<<< Updated upstream
    void menuCallback(cocos2d::Ref* pSender);//�˵���Ӧ����
    void input_return_pause();//���÷��أ��Լ���ͣ��   ��ͣ��δʵ��

=======
    void menuCallback(cocos2d::Ref* pSender);//������Ӧ����
    void input_return_pause();//���÷��أ��Լ���ͣ�� 
    void buttonCallback(cocos2d::Ref* pSender);//��ͣ��Ӧ����
    void input_gold(const int gold);//���ý��UI
    virtual void input_carrot() {};//�����ܲ�
    virtual void spawn_monster() {};//���ù���
>>>>>>> Stashed changes
    template<typename T>
    void input_brick(T x,T y ,int choice);//���õذ�

    // implement the "static create()" method manually
    CREATE_FUNC(Map_father);
};

class Map_One :public Map_father
{
public:
    virtual void input_background();
    virtual void input_walk_way();
<<<<<<< Updated upstream

=======
    virtual void input_carrot();
    virtual void spawn_monster();
>>>>>>> Stashed changes
    CREATE_FUNC(Map_One);
private:
    std::vector<std::vector<float>>walk_way_store_1;//��Ź����н���x,y�������
};

class Map_Two :public Map_father
{
public:
    virtual void input_background();
    virtual void input_walk_way();
<<<<<<< Updated upstream

=======
    virtual void input_carrot();
    virtual void spawn_monster();
>>>>>>> Stashed changes
    CREATE_FUNC(Map_Two);
private:
    std::vector<std::vector<float>>walk_way_store_2;//��Ź����н���x,y�������
};

class Map_Three :public Map_father
{
public:
    virtual void input_background();
    virtual void input_walk_way();
<<<<<<< Updated upstream

=======
    virtual void input_carrot();
    virtual void spawn_monster();
>>>>>>> Stashed changes
    CREATE_FUNC(Map_Three);
private:
    std::vector<std::vector<float>>walk_way_store_3;//��Ź����н���x,y�������
};

