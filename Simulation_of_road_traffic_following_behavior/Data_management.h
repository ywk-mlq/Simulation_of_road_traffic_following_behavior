/*************************************************

Copyright:于文凯 马丽千

Author:于文凯 马丽千

Date:2020-05-24

Description:本程序的数据管理

**************************************************/
#pragma once
// 车辆信息结构体
struct Vehicle_information
{
	int   key;                 // 车标
	float speed;               // 车速（m/s）
	float acceleration;        // 车辆加速度（m/s^2）
	float conductor;           // 车辆长度（m）
	float distance;            // 距离前车的距离（m），头车为-1m
};

// 人员信息结构体
struct Personnel_information
{
	int   key;                 // 人标
	int   age;                 // 年龄
	int   auto_age;            // 车龄
	float response_time;       // 反应时间(s/ms)
	float reaction_coefficient;// 反应系数(s/ms)
};
