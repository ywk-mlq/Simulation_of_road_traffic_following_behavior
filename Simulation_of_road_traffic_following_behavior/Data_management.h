/*************************************************

Copyright:于文凯 马丽千 王泳清

Author:于文凯 马丽千 王泳清

Date:2020-05-24

Description:本程序的数据管理

**************************************************/
#pragma once

/* 车辆信息 结构体 */
struct Vehicle_information
{
	int   key;                 // 车标
	float speed;               // 车速（m/s）
	float acceleration;        // 车辆加速度（m/s^2）
	float conductor;           // 车辆长度（m）
	float distance;            // 距离前车的距离（m），头车为-1m
};

/* 人员信息 结构体 */
struct Personnel_information
{
	int   key;                 // 人标
	int   age;                 // 年龄
	int   auto_age;            // 车龄
	float response_time;       // 反应时间(s/ms)
	float reaction_coefficient;// 反应系数(s/ms)
};

/* GHR模型参数 结构体 */
struct GHR_model_parameters
{
	float Dec_Pha[3];          //减速时三个参数【C,M,L】
	float Sta_Pha[3];          //稳定时三个参数【C,M,L】
	float Sce_Pha[3];          //加速时三个参数【C,M,L】
};

/* GHR和GF模型计算结果 结构体 */
struct Type_model_calculation_results
{
	int   key;	              // 车标
	int   time;               // 进行的时间（s）
	float speed;              // 车速（m/s）
	float change_speed;       // 距上一秒变化的速度
	float acceleration;       // 车辆加速度（m/s^2）
	float change_acceleration;// 距上一秒变化的加速度
	float distance;           // 距离前车的距离（m），头车为-1m
	float change_distance;    // 距上一秒变化的车头距离
	Type_model_calculation_results* next_car; // 指向下一辆车的数据
	Type_model_calculation_results* next_time;// 指向下一秒的数据
};


