#include "cocos2d.h"
#include "public_define.h"
#include <vector>
using namespace cocos2d;

struct XY
{
	int _x;
	int _y;
};

typedef struct FrameSpot
{
	int level;
	XY left_up;
	XY right_down;
	XY adjusted;
}FS;

const std::vector<FS> AllFrames = 
{   
	/**************************  LEVEL ONE ******************************/
	{1,{291,591},{373,509},{332,550}} ,{1,{291,509},{373,427},{332,468}} ,{1,{291,427},{373,345},{332,386}} ,{1,{291,345},{373,263},{332,304}},
	//上横行
	{1,{291,263},{373,181},{332,222}} ,{1,{291 + way_size,263},{373 + way_size,181},{332 + way_size,222}} ,
    {1,{291 + way_size * 2,263},{373 + way_size * 2,181},{332 + way_size * 2,222}} ,
    {1,{291 + way_size * 3,263},{373 + way_size * 3,181},{332 + way_size * 3,222}} ,
    {1,{291 + way_size * 4,263},{373 + way_size * 4,181},{332 + way_size * 4,222}} ,
    {1,{291 + way_size * 5,263},{373 + way_size * 5,181},{332 + way_size * 5,222}} ,
    {1,{291 + way_size * 6,263},{373 + way_size * 6,181},{332 + way_size * 6,222}} ,
    {1,{291 + way_size * 7,263},{373 + way_size * 7,181},{332 + way_size * 7,222}} ,
	//
    {1,{291 + way_size * 7,263 + way_size},{373 + way_size * 7,181 + way_size},{332 + way_size * 7,222 + way_size}},
	{1,{291 + way_size * 7,263 + way_size * 2},{373 + way_size * 7,181 + way_size * 2},{332 + way_size * 7,222 + way_size * 2}},
	{1,{291 + way_size * 7,263 + way_size * 3},{373 + way_size * 7,181 + way_size * 3},{332 + way_size * 7,222 + way_size * 3}},
	//
	{1,{291 + way_size * 9,263},{373 + way_size * 9,181},{332 + way_size * 9,222}},
	{1,{291 + way_size * 9,263 + way_size},{373 + way_size * 9,181 + way_size},{332 + way_size * 9,222 + way_size}},
	{1,{291 + way_size * 9,263 + way_size * 2},{373 + way_size * 9,181 + way_size * 2},{332 + way_size * 9,222 + way_size * 2}},
	{1,{291 + way_size * 9,263 + way_size * 3},{373 + way_size * 9,181 + way_size * 3},{332 + way_size * 9,222 + way_size * 3}},
	{1,{291 + way_size * 9,263 - way_size},{373 + way_size * 9,181 - way_size},{332 + way_size * 9,222 - way_size}},
	//下横行
	{1,{291 + way_size * 9,263 - way_size * 2},{373 + way_size * 9,181 - way_size * 2},{332 + way_size * 9,222 - way_size * 2}},
	{1,{291 + way_size * 8,263 - way_size * 2},{373 + way_size * 8,181 - way_size * 2},{332 + way_size * 8,222 - way_size * 2}},
	{1,{291 + way_size * 7,263 - way_size * 2},{373 + way_size * 7,181 - way_size * 2},{332 + way_size * 7,222 - way_size * 2}},
	{1,{291 + way_size * 6,263 - way_size * 2},{373 + way_size * 6,181 - way_size * 2},{332 + way_size * 6,222 - way_size * 2}},
	{1,{291 + way_size * 5,263 - way_size * 2},{373 + way_size * 5,181 - way_size * 2},{332 + way_size * 5,222 - way_size * 2}},
	{1,{291 + way_size * 4,263 - way_size * 2},{373 + way_size * 4,181 - way_size * 2},{332 + way_size * 4,222 - way_size * 2}},
	{1,{291 + way_size * 3,263 - way_size * 2},{373 + way_size * 3,181 - way_size * 2},{332 + way_size * 3,222 - way_size * 2}},
	{1,{291 + way_size * 2,263 - way_size * 2},{373 + way_size * 2,181 - way_size * 2},{332 + way_size * 2,222 - way_size * 2}},
	{1,{291 + way_size,263 - way_size * 2},{373 + way_size,181 - way_size * 2},{332 + way_size,222 - way_size * 2}},
	{1,{291           ,263 - way_size * 2},{373,           181 - way_size * 2},{332           ,222 - way_size * 2}},
	{1,{291 - way_size,263 - way_size * 2},{373 - way_size,181 - way_size * 2},{332 - way_size,222 - way_size * 2}},
	//
	{1,{291 - way_size * 2,263 - way_size * 2},{373 - way_size * 2,181 - way_size * 2},{332 - way_size * 2,222 - way_size * 2}},
	{1,{291 - way_size * 2,263 - way_size},    {373 - way_size * 2,181 - way_size},    {332 - way_size * 2,222 - way_size}},
	{1,{291 - way_size * 2,263},               {373 - way_size * 2,181},               {332 - way_size * 2,222}},
	{1,{291 - way_size * 2,263 + way_size},    {373 - way_size * 2,181 + way_size},    {332 - way_size * 2,222 + way_size}},
	{1,{291 - way_size * 2,263 + way_size * 2},{373 - way_size * 2,181 + way_size * 2},{332 - way_size * 2,222 + way_size * 2}},
	{1,{291 - way_size * 2,263 + way_size * 3},{373 - way_size * 2,181 + way_size * 3},{332 - way_size * 2,222 + way_size * 3}},
	{1,{291 - way_size * 2,263 + way_size * 4},{373 - way_size * 2,181 + way_size * 4},{332 - way_size * 2,222 + way_size * 4}}
	/**************************  LEVEL TWO ******************************/
	/*************************  LEVEL THREE *****************************/
};

class FrameBox : public Sprite
{
	friend class Map_father;
private:
	Sprite* Current;
public:
	FrameBox(Sprite* crnt){Current = crnt;}
	void Spawn(int x, int y);   //鼠标点击，出现框
	void Shimmer();             //自动呈现闪烁效果，直到下一次点击
	void Disappear();           //下一次点击后，框消失
};
bool IsFrame(int& x, int& y);