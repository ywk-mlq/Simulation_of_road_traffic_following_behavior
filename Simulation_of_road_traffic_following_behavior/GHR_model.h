/*************************************************

Copyright:于文凯 马丽千

Author:于文凯 马丽千

Date:2020-05-24

Description:本程序的GHR模型系统

**************************************************/
#pragma once
//#include "File_management.h"
#include <iostream>
#include "Data_management.h"
#include "File_management.h"
using namespace std;

// 全局变量
const int Parameters = 2;


// GHR 类的定义
class GHR
{
public:
	GHR(vector<Vehicle_information*> Vehicle);                 // 析构函数的定义
	void GHR_model_algorithm(float The_head_car_changes_speed);// GHR模型算法(核心算法)
private:
	void Gets_the_initial_state_data();                        // 获取初始状态数据
	vector<Vehicle_information*> vehicle;                      // 车辆信息的向量
	GHR_model_parameters GHR_Para[Parameters];                 // GHR模型参数的数据
	GHR_model_calculation_results* top = NULL;                 // 运算结果的头指针

};

/**
* 析构函数
* 函数功能：GHR模型的参数数据导入
*/
GHR::GHR(vector<Vehicle_information*> Vehicle)
{
	// 导入车辆信息
	vehicle = Vehicle;
	// 导入GHR参数数据
	Input_GHR_model_parameter_information(GHR_Para, Parameters);
}

/**
* GHR 核心算法
* 函数功能：GHR模型的算法 (三秒定律)
*/
void GHR::GHR_model_algorithm(float The_head_car_changes_speed)
{
	// 获取初始状态数据
	Gets_the_initial_state_data();
	// 判断算法循环(循环120秒)
	//int times = 0; bool the_crash = false;
	//while (++times <= 120)
	//{
	//	// 两辆车两辆车的判断
	//	for (int i = 0, j = 1; j < (int)vehicle.size(); ++i, ++j)
	//	{
	//		// 1.当相撞时，停止运算
	//		if ()
	//	}
	//	if (the_crash) break; // 如果撞车了，就停止运算
	//	
	//}

}

/**
* 函数功能：获取初始状态数据
*/
void GHR::Gets_the_initial_state_data()
{
	// 创建头指针
	top = new GHR_model_calculation_results;
	top->next_time = NULL; top->next_car = NULL;
	GHR_model_calculation_results* p = top, * q;
	// 每辆车进行录入信息
	for (unsigned int i = 0; i < vehicle.size(); ++i)
	{
		q = new GHR_model_calculation_results;
		q->time                = 0;
		q->change_speed        = 0;
		q->change_distance     = 0;
		q->change_acceleration = 0;
		q->key                 = vehicle[i]->key;
		q->speed               = vehicle[i]->speed;
		q->distance            = vehicle[i]->distance;
		q->acceleration        = vehicle[i]->acceleration;
		q->next_time = NULL;   q->next_car = NULL;
		p->next_car = q;       p = q;
	}
}
