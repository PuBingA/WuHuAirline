#define background_wide 1235							//整个游戏页面的宽度
#define background_high 694								//整个游戏页面的高度

#define gold_x 1170
#define gold_y 630										//金币坐标

#define return_x 1170     
#define return_y 630-70									//返回选择关卡界面坐标

#define pause_x 1170
#define pause_y 630-70-70								//暂停键坐标

#define gold_max 9990  //金币上限
#define gold_1   4000  //第一关初始金币
#define gold_2   7000  //第二关初始金币
#define gold_3   9000  //第三关初始金币


#define way_size 82										//每个地板的像素大小
#define walk_way_begin_1 {250,550}						//怪物开始移动的坐标
#define walk_way_begin_2 {250-way_size,550-5*way_size}	//怪物开始移动的坐标
#define walk_way_begin_3 {250,600}						//怪物开始移动坐标
#define walk_way_begin_1_x 250
#define walk_way_begin_1_y 550
#define walk_way_begin_2_x 250-way_size
#define walk_way_begin_2_y 550-5*way_size
#define walk_way_begin_3_x 250
#define walk_way_begin_3_y 600

#define monster_texture_size 100						//规定怪物贴图大小均为100*100像素
#define base_move_time 1.5f								//speed设为1时走一格花费的时间
#define blink_duration 0.5f
#define blink_time 3
#define fade_time 0.7f
#define animate_duration 0.3f

//升级费用
#define carrot_level_2 1000
#define carrot_level_3 1500

//第一关共有38个种植点位
#define Level_One_Spots 38 

//怪兽属性
#define mon1_vit 5
#define mon1_atk 10
#define mon1_spd 10
#define mon2_vit 8
#define mon2_atk 2
#define mon2_spd 2
#define mon3_vit 10
#define mon3_atk 2
#define mon3_spd 2
#define mon4_vit 12
#define mon4_atk 2
#define mon4_spd 3

#define type_cannon 1
#define type_shit 2
#define type_etower 3

#define cannon_build_cost 100
#define cannon_upgrade_1to2 180
#define cannon_upgrade_2to3 220

#define shit_build_cost 120
#define shit_upgrade_1to2 220
#define shit_upgrade_2to3 260

#define etower_build_cost 160
#define etower_upgrade_1to2 260
#define etower_upgrade_2to3 300

#define delete_recover 100