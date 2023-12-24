#include "cocos2d.h"
#include "public_define.h"
#include <vector>
USING_NS_CC;

struct XY
{
	float _x;
	float _y;
};

typedef struct FrameSpot
{
	int index;
	XY left_up;
	XY right_down;
	XY adjusted;
}FS;

/*********************************************************
* 防御塔的index对应不同的防御塔种类：
* index=1 一级炮台 index=2 二级炮台 index=3 三级炮台
* index=4 一级屎   index=5 二级屎   index=6 三级屎
* index=7 一级电塔 index=8 二级电塔 index=9 三级电塔
**********************************************************/
typedef struct TowerInfo
{
	int index;
	int upgrade_cost;
	int destroy_cost;
	int ATK_radius;
	int ATK_damage;
	int ATK_speed;
}TI;

//数值分别代表：炮台种类，升级花费，铲除返现，攻击范围，子弹伤害，攻速(单位ms)
//建立炮台花费100
const TI Cannon_1 = { 1, 180, 80, 100, 30, 500 };
const TI Cannon_2 = { 2, 260, 234, 150, 40, 500 };
const TI Cannon_3 = { 3, -1, 432, 200, 50, 500 };
//建立屎花费120
const TI Shit_1 = { 4, 220, 96, 75, 20, 400 };
const TI Shit_2 = { 5, 260, 272, 100, 35, 450 };
const TI Shit_3 = { 6, -1, 480, 125, 50, 500 };
//建立电塔花费160
const TI ETower_1 = { 7, 320, 128, 250, 50, 1000 };
const TI ETower_2 = { 8, 480, 384, 275, 60, 1000 };
const TI ETower_3 = { 9, -1, 768, 300, 70, 1000 };

/**************************  LEVEL ONE ******************************/
const std::vector<FS> AllFrames_Lv1 =
{
	{0,{291,591},{373,509},{332,550}} ,
	{1,{291,509},{373,427},{332,468}} ,
	{2,{291,427},{373,345},{332,386}} ,
	{3,{291,345},{373,263},{332,304}} ,
	//上横行
	{4,{291,263},{373,181},{332,222}} ,{5,{291 + way_size,263},{373 + way_size,181},{332 + way_size,222}} ,
	{6,{291 + way_size * 2,263},{373 + way_size * 2,181},{332 + way_size * 2,222}} ,
	{7,{291 + way_size * 3,263},{373 + way_size * 3,181},{332 + way_size * 3,222}} ,
	{8,{291 + way_size * 4,263},{373 + way_size * 4,181},{332 + way_size * 4,222}} ,
	{9,{291 + way_size * 5,263},{373 + way_size * 5,181},{332 + way_size * 5,222}} ,
	{10,{291 + way_size * 6,263},{373 + way_size * 6,181},{332 + way_size * 6,222}} ,
	{11,{291 + way_size * 7,263},{373 + way_size * 7,181},{332 + way_size * 7,222}} ,
	//
	{12,{291 + way_size * 7,263 + way_size},{373 + way_size * 7,181 + way_size},{332 + way_size * 7,222 + way_size}},
	{13,{291 + way_size * 7,263 + way_size * 2},{373 + way_size * 7,181 + way_size * 2},{332 + way_size * 7,222 + way_size * 2}},
	{14,{291 + way_size * 7,263 + way_size * 3},{373 + way_size * 7,181 + way_size * 3},{332 + way_size * 7,222 + way_size * 3}},
	//
	{15,{291 + way_size * 9,263 + way_size * 3},{373 + way_size * 9,181 + way_size * 3},{332 + way_size * 9,222 + way_size * 3}},
	{16,{291 + way_size * 9,263 + way_size * 2},{373 + way_size * 9,181 + way_size * 2},{332 + way_size * 9,222 + way_size * 2}},
	{17,{291 + way_size * 9,263 + way_size},{373 + way_size * 9,181 + way_size},{332 + way_size * 9,222 + way_size}},
	{18,{291 + way_size * 9,263},{373 + way_size * 9,181},{332 + way_size * 9,222}},
	{19,{291 + way_size * 9,263 - way_size},{373 + way_size * 9,181 - way_size},{332 + way_size * 9,222 - way_size}},
	//下横行
	{20,{291 + way_size * 9,263 - way_size * 2},{373 + way_size * 9,181 - way_size * 2},{332 + way_size * 9,222 - way_size * 2}},
	{21,{291 + way_size * 8,263 - way_size * 2},{373 + way_size * 8,181 - way_size * 2},{332 + way_size * 8,222 - way_size * 2}},
	{22,{291 + way_size * 7,263 - way_size * 2},{373 + way_size * 7,181 - way_size * 2},{332 + way_size * 7,222 - way_size * 2}},
	{23,{291 + way_size * 6,263 - way_size * 2},{373 + way_size * 6,181 - way_size * 2},{332 + way_size * 6,222 - way_size * 2}},
	{24,{291 + way_size * 5,263 - way_size * 2},{373 + way_size * 5,181 - way_size * 2},{332 + way_size * 5,222 - way_size * 2}},
	{25,{291 + way_size * 4,263 - way_size * 2},{373 + way_size * 4,181 - way_size * 2},{332 + way_size * 4,222 - way_size * 2}},
	{26,{291 + way_size * 3,263 - way_size * 2},{373 + way_size * 3,181 - way_size * 2},{332 + way_size * 3,222 - way_size * 2}},
	{27,{291 + way_size * 2,263 - way_size * 2},{373 + way_size * 2,181 - way_size * 2},{332 + way_size * 2,222 - way_size * 2}},
	{28,{291 + way_size,263 - way_size * 2},{373 + way_size,181 - way_size * 2},{332 + way_size,222 - way_size * 2}},
	{29,{291           ,263 - way_size * 2},{373,           181 - way_size * 2},{332           ,222 - way_size * 2}},
	{30,{291 - way_size,263 - way_size * 2},{373 - way_size,181 - way_size * 2},{332 - way_size,222 - way_size * 2}},
	//
	{31,{291 - way_size * 2,263 - way_size * 2},{373 - way_size * 2,181 - way_size * 2},{332 - way_size * 2,222 - way_size * 2}},
	{32,{291 - way_size * 2,263 - way_size},    {373 - way_size * 2,181 - way_size},    {332 - way_size * 2,222 - way_size}},
	{33,{291 - way_size * 2,263},               {373 - way_size * 2,181},               {332 - way_size * 2,222}},
	{34,{291 - way_size * 2,263 + way_size},    {373 - way_size * 2,181 + way_size},    {332 - way_size * 2,222 + way_size}},
	{35,{291 - way_size * 2,263 + way_size * 2},{373 - way_size * 2,181 + way_size * 2},{332 - way_size * 2,222 + way_size * 2}},
	{36,{291 - way_size * 2,263 + way_size * 3},{373 - way_size * 2,181 + way_size * 3},{332 - way_size * 2,222 + way_size * 3}},
	{37,{291 - way_size * 2,263 + way_size * 4},{373 - way_size * 2,181 + way_size * 4},{332 - way_size * 2,222 + way_size * 4}}
};

/**************************  LEVEL TWO ******************************/
const std::vector<FS> AllFrames_Lv2 =
{
	{0,{127,263},{209,181},{168,222}},
	{1,{127 + way_size * 1,263},{209 + way_size * 1,181},{168 + way_size * 1,222}},
	{2,{127 + way_size * 2,263},{209 + way_size * 2,181},{168 + way_size * 2,222}},
	{3,{127 + way_size * 3,263},{209 + way_size * 3,181},{168 + way_size * 3,222}},
	{4,{127 + way_size * 3,263 + way_size * 1},{209 + way_size * 3,181 + way_size * 1},{168 + way_size * 3,222 + way_size * 1}},
	{5,{127 + way_size * 3,263 + way_size * 2},{209 + way_size * 3,181 + way_size * 2},{168 + way_size * 3,222 + way_size * 2}},
	{6,{127 + way_size * 3,263 + way_size * 3},{209 + way_size * 3,181 + way_size * 3},{168 + way_size * 3,222 + way_size * 3}},
	{7,{127 + way_size * 3,263 + way_size * 4},{209 + way_size * 3,181 + way_size * 4},{168 + way_size * 3,222 + way_size * 4}},
	{8,{127 + way_size * 3,263 + way_size * 5},{209 + way_size * 3,181 + way_size * 5},{168 + way_size * 3,222 + way_size * 5}},
	{9,{127 + way_size * 4,263 + way_size * 5},{209 + way_size * 4,181 + way_size * 5},{168 + way_size * 4,222 + way_size * 5}},
	{10,{127 + way_size * 5,263 + way_size * 5},{209 + way_size * 5,181 + way_size * 5},{168 + way_size * 5,222 + way_size * 5}},
	{11,{127 + way_size * 6,263 + way_size * 5},{209 + way_size * 6,181 + way_size * 5},{168 + way_size * 6,222 + way_size * 5}},
	{12,{127 + way_size * 7,263 + way_size * 5},{209 + way_size * 7,181 + way_size * 5},{168 + way_size * 7,222 + way_size * 5}},
	{13,{127 + way_size * 8,263 + way_size * 5},{209 + way_size * 8,181 + way_size * 5},{168 + way_size * 8,222 + way_size * 5}},
	{14,{127 + way_size * 8,263 + way_size * 4},{209 + way_size * 8,181 + way_size * 4},{168 + way_size * 8,222 + way_size * 4}},
	{15,{127 + way_size * 8,263 + way_size * 3},{209 + way_size * 8,181 + way_size * 3},{168 + way_size * 8,222 + way_size * 3}},
	{16,{127 + way_size * 8,263 + way_size * 2},{209 + way_size * 8,181 + way_size * 2},{168 + way_size * 8,222 + way_size * 2}},
	{17,{127 + way_size * 8,263 + way_size * 1},{209 + way_size * 8,181 + way_size * 1},{168 + way_size * 8,222 + way_size * 1}},
	{18,{127 + way_size * 8,263               },{209 + way_size * 8,181               },{168 + way_size * 8,222               }},
	{19,{127 + way_size * 9,263               },{209 + way_size * 9,181               },{168 + way_size * 9,222               }},
	{20,{127 + way_size * 10,263              },{209 + way_size * 10,181              },{168 + way_size * 10,222              }},
	{21,{127               ,263 - way_size * 2},{209               ,181 - way_size * 2},{168               ,222 - way_size * 2}},
	{22,{127 + way_size * 1,263 - way_size * 2},{209 + way_size * 1,181 - way_size * 2},{168 + way_size * 1,222 - way_size * 2}},
	{23,{127 + way_size * 2,263 - way_size * 2},{209 + way_size * 2,181 - way_size * 2},{168 + way_size * 2,222 - way_size * 2}},
	{24,{127 + way_size * 3,263 - way_size * 2},{209 + way_size * 3,181 - way_size * 2},{168 + way_size * 3,222 - way_size * 2}},
	{25,{127 + way_size * 4,263 - way_size * 2},{209 + way_size * 4,181 - way_size * 2},{168 + way_size * 4,222 - way_size * 2}},
	{26,{127 + way_size * 5,263 - way_size * 2},{209 + way_size * 5,181 - way_size * 2},{168 + way_size * 5,222 - way_size * 2}},
	{27,{127 + way_size * 5,263 - way_size * 1},{209 + way_size * 5,181 - way_size * 1},{168 + way_size * 5,222 - way_size * 1}},
	{28,{127 + way_size * 5,263               },{209 + way_size * 5,181               },{168 + way_size * 5,222               }},
	{29,{127 + way_size * 5,263 + way_size * 1},{209 + way_size * 5,181 + way_size * 1},{168 + way_size * 5,222 + way_size * 1}},
	{30,{127 + way_size * 5,263 + way_size * 2},{209 + way_size * 5,181 + way_size * 2},{168 + way_size * 5,222 + way_size * 2}},
	{31,{127 + way_size * 5,263 + way_size * 3},{209 + way_size * 5,181 + way_size * 3},{168 + way_size * 5,222 + way_size * 3}},
	{32,{127 + way_size * 6,263 + way_size * 3},{209 + way_size * 6,181 + way_size * 3},{168 + way_size * 6,222 + way_size * 3}},
	{33,{127 + way_size * 6,263 + way_size * 2},{209 + way_size * 6,181 + way_size * 2},{168 + way_size * 6,222 + way_size * 2}},
	{34,{127 + way_size * 6,263 + way_size * 1},{209 + way_size * 6,181 + way_size * 1},{168 + way_size * 6,222 + way_size * 1}},
	{35,{127 + way_size * 6,263               },{209 + way_size * 6,181               },{168 + way_size * 6,222               }},
	{36,{127 + way_size * 6,263 - way_size * 1},{209 + way_size * 6,181 - way_size * 1},{168 + way_size * 6,222 - way_size * 1}},
	{37,{127 + way_size * 6,263 - way_size * 2},{209 + way_size * 6,181 - way_size * 2},{168 + way_size * 6,222 - way_size * 2}},
	{38,{127 + way_size * 7,263 - way_size * 2},{209 + way_size * 7,181 - way_size * 2},{168 + way_size * 7,222 - way_size * 2}},
	{39,{127 + way_size * 8,263 - way_size * 2},{209 + way_size * 8,181 - way_size * 2},{168 + way_size * 8,222 - way_size * 2}},
	{40,{127 + way_size * 9,263 - way_size * 2},{209 + way_size * 9,181 - way_size * 2},{168 + way_size * 9,222 - way_size * 2}},
	{41,{127 + way_size * 10,263 - way_size * 2},{209 + way_size * 10,181 - way_size * 2},{168 + way_size * 10,222 - way_size * 2}}
};

/*************************  LEVEL THREE *****************************/

const std::vector<FS> AllPlants_Lv1 =
{
	{1,{415,635},{485,565},{450, 600}},
	{2,{515,635},{585,565},{550, 600}},
	{3,{615,635},{685,565},{650, 600}},
	{4,{715,635},{785,565},{750, 600}}
};
const std::vector<FS> AllPlants_Lv2 =
{
	{1,{25,585},{95,515},{60, 550}},
	{2,{25,485},{95,415},{60, 450}},
	{3,{25,385},{95,315},{60, 350}},
	{4,{25,285},{95,215},{60, 250}}
};

bool IsFrame(float&, float&, const std::vector<FS>&);
bool IsFramePlant(float&, float&, const std::vector<FS>&);

class FrameBox : public Sprite
{
	friend class Map_father;
public:
	static FrameBox* create(const std::string& filename);
	void Spawn(float x, float y, float scale); //在某个特定位置以特定大小显示某只精灵
	void Shimmer();                            //自动呈现闪烁效果，直到下一次点击
	void Disappear();                          //下一次点击后，框消失
	void Rotate(float duration, float angle);  //以angle角度顺时针旋转
};