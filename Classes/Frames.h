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
const std::vector<FS> AllFrames_Lv3 =
{
	{0,{209,559},{291,477},{250,600 - way_size * 1}},
	{1,{209 + way_size * 1,559},{291 + way_size * 1,477},{250 + way_size * 1,600 - way_size * 1}},
	{2,{209 + way_size * 2,559},{291 + way_size * 2,477},{250 + way_size * 2,600 - way_size * 1}},
	{3,{209 + way_size * 3,559},{291 + way_size * 3,477},{250 + way_size * 3,600 - way_size * 1}},
	{4,{209 + way_size * 4,559},{291 + way_size * 4,477},{250 + way_size * 4,600 - way_size * 1}},
	{5,{209 + way_size * 5,559},{291 + way_size * 5,477},{250 + way_size * 5,600 - way_size * 1}},
	{6,{209 + way_size * 6,559},{291 + way_size * 6,477},{250 + way_size * 6,600 - way_size * 1}},
	{7,{209 + way_size * 7,559},{291 + way_size * 7,477},{250 + way_size * 7,600 - way_size * 1}},
	{8,{209 + way_size * 8,559},{291 + way_size * 8,477},{250 + way_size * 8,600 - way_size * 1}},
	{9,{209 + way_size * 8,559 - way_size * 1},{291 + way_size * 8,477 - way_size * 1},{250 + way_size * 8,518 - way_size * 1}},
	{10,{209 + way_size * 7,559 - way_size * 1},{291 + way_size * 7,477 - way_size * 1},{250 + way_size * 7,518 - way_size * 1}},
	{11,{209 + way_size * 6,559 - way_size * 1},{291 + way_size * 6,477 - way_size * 1},{250 + way_size * 6,518 - way_size * 1}},
	{12,{209 + way_size * 5,559 - way_size * 1},{291 + way_size * 5,477 - way_size * 1},{250 + way_size * 5,518 - way_size * 1}},
	{13,{209 + way_size * 4,559 - way_size * 1},{291 + way_size * 4,477 - way_size * 1},{250 + way_size * 4,518 - way_size * 1}},
	{14,{209 + way_size * 3,559 - way_size * 1},{291 + way_size * 3,477 - way_size * 1},{250 + way_size * 3,518 - way_size * 1}},
	{15,{209 + way_size * 2,559 - way_size * 1},{291 + way_size * 2,477 - way_size * 1},{250 + way_size * 2,518 - way_size * 1}},
	{16,{209 + way_size * 1,559 - way_size * 1},{291 + way_size * 1,477 - way_size * 1},{250 + way_size * 1,518 - way_size * 1}},
	{17,{209               ,559 - way_size * 1},{291               ,477 - way_size * 1},{250               ,518 - way_size * 1}},
	{18,{209 - way_size * 1,559 - way_size * 1},{291 - way_size * 1,477 - way_size * 1},{250 - way_size * 1,518 - way_size * 1}},
	{19,{209 - way_size * 1,559 - way_size * 2},{291 - way_size * 1,477 - way_size * 2},{250 - way_size * 1,518 - way_size * 2}},
	{20,{209 - way_size * 1,559 - way_size * 3},{291 - way_size * 1,477 - way_size * 3},{250 - way_size * 1,518 - way_size * 3}},
	{21,{209 - way_size * 1,559 - way_size * 4},{291 - way_size * 1,477 - way_size * 4},{250 - way_size * 1,518 - way_size * 4}},
	{22,{209 - way_size * 1,559 - way_size * 5},{291 - way_size * 1,477 - way_size * 5},{250 - way_size * 1,518 - way_size * 5}},
	{23,{209 + way_size * 10,559               },{291 + way_size * 10,477               },{250 + way_size * 10,518               }},
	{24,{209 + way_size * 10,559 - way_size * 1},{291 + way_size * 10,477 - way_size * 1},{250 + way_size * 10,518 - way_size * 1}},
	{25,{209 + way_size * 10,559 - way_size * 2},{291 + way_size * 10,477 - way_size * 2},{250 + way_size * 10,518 - way_size * 2}},
	{26,{209 + way_size * 10,559 - way_size * 3},{291 + way_size * 10,477 - way_size * 3},{250 + way_size * 10,518 - way_size * 3}},
	{27,{209 + way_size * 9,559 - way_size * 3},{291 + way_size * 9,477 - way_size * 3},{250 + way_size * 9,518 - way_size * 3}},
	{28,{209 + way_size * 8,559 - way_size * 3},{291 + way_size * 8,477 - way_size * 3},{250 + way_size * 8,518 - way_size * 3}},
	{29,{209 + way_size * 7,559 - way_size * 3},{291 + way_size * 7,477 - way_size * 3},{250 + way_size * 7,518 - way_size * 3}},
	{30,{209 + way_size * 6,559 - way_size * 3},{291 + way_size * 6,477 - way_size * 3},{250 + way_size * 6,518 - way_size * 3}},
	{31,{209 + way_size * 5,559 - way_size * 3},{291 + way_size * 5,477 - way_size * 3},{250 + way_size * 5,518 - way_size * 3}},
	{32,{209 + way_size * 4,559 - way_size * 3},{291 + way_size * 4,477 - way_size * 3},{250 + way_size * 4,518 - way_size * 3}},
	{33,{209 + way_size * 3,559 - way_size * 3},{291 + way_size * 3,477 - way_size * 3},{250 + way_size * 3,518 - way_size * 3}},
	{34,{209 + way_size * 2,559 - way_size * 3},{291 + way_size * 2,477 - way_size * 3},{250 + way_size * 2,518 - way_size * 3}},
	{35,{209 + way_size * 1,559 - way_size * 3},{291 + way_size * 1,477 - way_size * 3},{250 + way_size * 1,518 - way_size * 3}},
	{36,{209 + way_size * 1,559 - way_size * 4},{291 + way_size * 1,477 - way_size * 4},{250 + way_size * 1,518 - way_size * 4}},
	{37,{209 + way_size * 2,559 - way_size * 4},{291 + way_size * 2,477 - way_size * 4},{250 + way_size * 2,518 - way_size * 4}},
	{38,{209 + way_size * 3,559 - way_size * 4},{291 + way_size * 3,477 - way_size * 4},{250 + way_size * 3,518 - way_size * 4}},
	{39,{209 + way_size * 4,559 - way_size * 4},{291 + way_size * 4,477 - way_size * 4},{250 + way_size * 4,518 - way_size * 4}},
	{40,{209 + way_size * 5,559 - way_size * 4},{291 + way_size * 5,477 - way_size * 4},{250 + way_size * 5,518 - way_size * 4}},
	{41,{209 + way_size * 6,559 - way_size * 4},{291 + way_size * 6,477 - way_size * 4},{250 + way_size * 6,518 - way_size * 4}},
	{42,{209 + way_size * 7,559 - way_size * 4},{291 + way_size * 7,477 - way_size * 4},{250 + way_size * 7,518 - way_size * 4}},
	{43,{209 + way_size * 8,559 - way_size * 4},{291 + way_size * 8,477 - way_size * 4},{250 + way_size * 8,518 - way_size * 4}}
};

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
const std::vector<FS> AllPlants_Lv3 =
{
	{1,{25,585},{95,515},{60, 550}},
	{2,{25,485},{95,415},{60, 450}},
	{3,{25,385},{95,315},{60, 350}},
	{4,{25,285},{95,215},{60, 250}},
	{5,{25,185},{95,115},{60, 150}}
};

bool IsFrame(float&, float&, const std::vector<FS>&);
bool IsFramePlant(float&, float&, const std::vector<FS>&);

