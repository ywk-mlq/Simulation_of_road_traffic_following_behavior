/*************************************************

Copyright:于文凯 马丽千

Author:于文凯 马丽千

Date:2020-05-24

Description:本程序的GHR模型系统

**************************************************/
#pragma once
//#include "File_management.h"
#include <cmath>
#include <iostream>
#include "Data_management.h"
#include "File_management.h"
using namespace std;

// 全局变量
const int Aron       = 0;   // Aron参数
const int Ozaki      = 1;   // Ozaki参数
const int C          = 0;   // 车辆敏感系数
const int M          = 1;   // 速度敏感参数
const int L          = 2;   // 相对距离敏感参数
const int Parameters = 2;   // 参数的个数
const float Folttime = 3;   // 三秒定律
const int TIMES      = 540; // 跟驰多少秒


// GHR 类的定义
class GHR
{
public:
	GHR(vector<Vehicle_information*> Vehicle);                 // 构造函数的定义
	~GHR();                                                    // 析构函数的定义
	void GHR_model_algorithm(float The_head_car_changes_speed, float acceleration);
private:                                                       // GHR模型算法(核心算法)
	void Gets_the_initial_state_data();                        // 获取初始状态数据
	float accelerate_algori();                                 // GHR加速加速度算法
	float deceleration_algori();                               // GHR减速加速度算法
	vector<Vehicle_information*> vehicle;                      // 车辆信息的向量
	GHR_model_parameters GHR_Para[Parameters];                 // GHR模型参数的数据
	GHR_model_calculation_results* top          = NULL;        // 运算结果的头指针
	GHR_model_calculation_results* front        = NULL;        // 前车的指针
	GHR_model_calculation_results* rear         = NULL;        // 后车的指针
	GHR_model_calculation_results* front_nxtime = NULL;        // 前车下一秒的指针
	GHR_model_calculation_results* rear_nxtime  = NULL;        // 后车下一秒的指针
};

/**
* 构造函数
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
* 析构函数
* 函数功能：释放GHR算法的结果指针
*/
GHR::~GHR()
{
	if (top != NULL)
	{
		front = top->next_car;
		// 先释放top 指针
		delete top; top = NULL;
		// 再循环释放车辆信息指针
		while (front != NULL)
		{
			rear = front; front = front->next_car;
			while (rear != NULL)
			{
				rear_nxtime = rear; rear = rear->next_time;
				delete rear_nxtime; rear_nxtime = NULL;
			}
		}
	}
	
}

/**
* GHR 核心算法
* 函数功能：GHR模型的算法 (三秒定律)
*/
void GHR::GHR_model_algorithm(float The_head_car_changes_speed, float acceleration)
{
	/**
	* 只要大于三秒定律就加速
	* 只要小于三秒定律就减速
	*/
	// 获取初始状态数据
	Gets_the_initial_state_data();
	// 加速度输入
	top->next_car->acceleration = acceleration;
	// 判断算法循环(循环timess秒)
	int times = 0; bool the_crash = false;
	while (++times <= TIMES)
	{
		// 车辆指针的第一次准备
		front = top->next_car;
		// 车辆指针的第二次准备
		for (int i = 1; i < times; ++i)
			front = front->next_time;
		rear = front->next_car;
		// 两辆车两辆车的判断
		while (rear != NULL)
		{
			// 后车需要变化的加速度,前车变化的车速，后车变化的车速，距离的变化
			float rear_acc = 0, front_sp = 0, rear_sp = 0, rear_dis = 0;
			// 1.当两辆车相撞时
			if (rear->distance <= 0)
			{
				the_crash = true;
				break;
			}

			// 2.没有相撞时的比较
			else
			{
				rear_acc = rear->distance > rear->speed * Folttime ? accelerate_algori() : deceleration_algori();
				// 2.1.2前车的变化后的速度
				front_sp = front->speed + front->acceleration;
				// 2.1.3后车的变化后的速度
				rear_sp = rear->speed + rear->acceleration > 32 ? 32 : rear->speed + rear->acceleration;
				// 2.1.4后车与前车的间距
				rear_dis = rear->distance + ((front->speed + front_sp) / 2) - ((rear->speed + rear_sp) / 2);
			}

			// 3.接入下一秒的数据
			// 3.1如果front是头车
			if (front->key == 1 && front->next_time == NULL)
			{
				// 3.1.1赋予数据
				front_nxtime                  = new GHR_model_calculation_results;
				front_nxtime->key             = 1;                      // 车标
				front_nxtime->distance        = -1;                     // 前车距离
				front_nxtime->change_distance = 0;                      // 变化的前车距离
				front_nxtime->time            = times;                  // 第几秒的数据
				front_nxtime->change_speed    = front_sp - front->speed;// 改变的速度
				front_nxtime->speed           = front_sp;               // 改变后的速度
				front_nxtime->next_time       = NULL;
				front_nxtime->next_car        = NULL;
				                                                        // 变化的加速度
				if (top->next_car->speed < The_head_car_changes_speed)
					front_nxtime->acceleration = front_sp >= The_head_car_changes_speed ? 0 : acceleration;
				else
					front_nxtime->acceleration = front_sp <= The_head_car_changes_speed ? 0 : acceleration;
				front_nxtime->change_acceleration = front_nxtime->acceleration - front->acceleration;
				// 3.1.2接入结点
				front->next_time = front_nxtime;
			}
			// 3.2接入后车数据
			// 3.2.1赋予数据
			rear_nxtime                      = new GHR_model_calculation_results;
			rear_nxtime->key                 = rear->key;                    // 车标
			rear_nxtime->time                = times;                        // 第几秒的数据
			rear_nxtime->speed               = rear_sp;                      // 变化后的速度
			rear_nxtime->change_speed        = rear_sp - rear->speed;        // 变化的速度
			rear_nxtime->acceleration        = rear_acc;                     // 变化后的加速度
			rear_nxtime->change_acceleration = rear_acc - rear->acceleration;// 变化的加速度
			rear_nxtime->distance            = rear_dis;                     // 变化后的车距
			rear_nxtime->change_distance     = rear_dis - rear->distance;    // 变化的车距
			rear_nxtime->next_car            = NULL;
			rear_nxtime->next_time           = NULL;
			// 3.2.2接入结点
			rear->next_time                  = rear_nxtime;
			// 3.3前车的下一结点连接后车
			front->next_time->next_car = rear_nxtime;

			// 4.下两辆车的比较
			front = rear; rear = rear->next_car;
		}
		// 如果撞车了，就停止运算
		if (the_crash)
		{
			cout << "第" << front->key << "辆车与第" << rear->key
				 << "车相撞了！！！" << endl;
			break;
		}
	}
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
		q->acceleration = q->key == 1 ? vehicle[i]->acceleration : 0;
		q->next_time = NULL;   q->next_car = NULL;
		p->next_car = q;       p = q;
	}
}

/**
* 函数功能：GHR加速加速度算法
*/
float GHR::accelerate_algori()
{
	// Aron 和 Ozaki参数的算数平均
	float Aron_a = (front->speed - rear->speed) * GHR_Para[Aron].Sce_Pha[C] * 
		pow(rear->speed, GHR_Para[Aron].Sce_Pha[M]) / pow(rear->distance, GHR_Para[Aron].Sce_Pha[L]);
	float Ozaki_a = (front->speed - rear->speed) * GHR_Para[Ozaki].Sce_Pha[C] *
		pow(rear->speed, GHR_Para[Ozaki].Sce_Pha[M]) / pow(rear->distance, GHR_Para[Ozaki].Sce_Pha[L]);
	Aron_a  = Aron_a  < 0 ? (0 - Aron_a)  : Aron_a;
	Ozaki_a = Ozaki_a < 0 ? (0 - Ozaki_a) : Ozaki_a;
	float A = (Aron_a + Ozaki_a) / 2;
	return A > (float)6.2 ? (float)6.2 : A;
}

/**
* 函数功能：GHR减速加速度算法
*/
float GHR::deceleration_algori()
{
	// Aron 和 Ozaki参数的算数平均
	float Aron_a = (front->speed - rear->speed) * GHR_Para[Aron].Dec_Pha[C] *
		pow(rear->speed, GHR_Para[Aron].Dec_Pha[M]) / pow(rear->distance, GHR_Para[Aron].Dec_Pha[L]);
	float Ozaki_a = (front->speed - rear->speed) * GHR_Para[Ozaki].Dec_Pha[C] *
		pow(rear->speed, GHR_Para[Ozaki].Dec_Pha[M]) / pow(rear->distance, GHR_Para[Ozaki].Dec_Pha[L]);
	Aron_a  = Aron_a  > 0 ? (0 - Aron_a)  : Aron_a;
	Ozaki_a = Ozaki_a > 0 ? (0 - Ozaki_a) : Ozaki_a;
	float A = (Aron_a + Ozaki_a) / 2;
	return A < (float)-6.2 ? (float)-6.2 : A;
}
