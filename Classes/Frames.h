#include "cocos2d.h"
#include "public_define.h"
#include <vector>
USING_NS_CC;

struct XY
{
	int _x;
	int _y;
};

typedef struct FrameSpot
{
	int index;
	XY left_up;
	XY right_down;
	XY adjusted;
}FS;

const std::vector<FS> AllFrames_Lv1 = 
{   
	/**************************  LEVEL ONE ******************************/
	{0,{291,591},{373,509},{332,550}} ,
	{1,{291,509},{373,427},{332,468}} ,
	{2,{291,427},{373,345},{332,386}} ,
	{3,{291,345},{373,263},{332,304}},
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
	/*************************  LEVEL THREE *****************************/
const std::vector<FS> AllPlants_Lv1 = { {1,{415,635},{485,565},{450, 600}},{2,{515,635},{585,565},{550, 600}}, {3,{615,635},{685,565},{650, 600}},{4,{715,635},{785,565},{750, 600}} };

class FrameBox : public Sprite
{
	friend class Map_One;
private:
	Sprite* Current;
public:
	FrameBox(Sprite* crnt){Current = crnt;}
	void Spawn(int x, int y, float scale); //在某个特定位置以特定大小显示某只精灵
	void Shimmer();             //自动呈现闪烁效果，直到下一次点击
	void Disappear();           //下一次点击后，框消失
};
bool IsFrame_Lv1(int& x, int& y);
bool IsFramePlant_Lv1(int& x, int& y);