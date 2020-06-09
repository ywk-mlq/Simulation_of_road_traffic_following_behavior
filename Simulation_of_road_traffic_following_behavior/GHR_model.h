/*************************************************

Copyright:于文凯 马丽千 王泳清

Author:于文凯 马丽千 王泳清

Date:2020-05-24

Description:本程序的GHR和GF模型系统

**************************************************/
#pragma once
#include <map>
#include <cmath>
#include <string>
#include <iostream>
#include <windows.h>
#include "Data_management.h"
#include "File_management.h"
using namespace std;

// 全局变量
const int Aron                              = 0;     // Aron参数
const int Ozaki                             = 1;     // Ozaki参数
const int C                                 = 0;     // 车辆敏感系数
const int M                                 = 1;     // 速度敏感参数
const int L                                 = 2;     // 相对距离敏感参数
const int Parameters                        = 2;     // 参数的个数
const float Average_sensitivity_coefficient = 0.0786f;// 算术平均的敏感参数
const float m1 = -0.009f;                              //安全距离模型中的定量参数
const float m2 = 0.067f;                               //安全距离模型中的定量参数
const float n1 = 2.36f;                                //安全距离模型中的定量参数
const float n2 = 1.98f;                                //安全距离模型中的定量参数
const float response_time = 0.4f;                      //反应时间   T
const float addresponse_time = 0.2f;                   //附加反应时间  seita
const float maxdeceleration = -8.5f;                   //最大减速度

// GHR 类的定义
class GHR
{
public:
	GHR(vector<Vehicle_information*> Vehicle, string);				       // 构造函数的定义
	~GHR();																   // 析构函数的定义
	Type_model_calculation_results* GHR_model_algorithm(float, float, int);// GHR模型算法(核心算法)
	Type_model_calculation_results* Gip_model_algorithm(float, float, int);// Gipps模型算法(核心算法)
	Type_model_calculation_results* obtain_vehicle_map(int);			   // 获得每个时间的图，返回图

private:
	float Folttime = 3;                                        // 三秒定律
	int   TIMES    = 540;                                      // 跟驰多少秒
	const float Maximum_speed = 32;                            // 额定得最大车速
	void Gets_the_initial_state_data();                        // 获取初始状态数据
	float accelerate_algori();                                 // GHR加速加速度算法
	float deceleration_algori();                               // GHR减速加速度算法
	float GF_Acceleration_algorithm();                         // GF模型加速度算法                    
	vector<Vehicle_information*> vehicle;                      // 车辆信息的向量
	GHR_model_parameters GHR_Para[Parameters];                 // GHR模型参数的数据
	GHR_model_parameters Gipps_Para[Parameters];               // Gipps模型参数的数据
	string Model                                 = "GHR";      // 需要构建的模型种类
	Type_model_calculation_results* top          = NULL;       // 运算结果的头指针
	Type_model_calculation_results* front        = NULL;       // 前车的指针
	Type_model_calculation_results* rear         = NULL;       // 后车的指针
	Type_model_calculation_results* front_nxtime = NULL;       // 前车下一秒的指针
	Type_model_calculation_results* rear_nxtime  = NULL;       // 后车下一秒的指针
	map<int, Type_model_calculation_results*> Vehicle_time;    // 每个时间的图，存放指针

};

/*  Heaviside函数
	计算模型中的一个参数   */
float Heaviside(float v) {
	if (v > 0) return 1;
	if (v < 0) return 0;
	else return 0.5;
}


/**
* 构造函数
* 函数功能：GHR模型的参数数据导入
*/
GHR::GHR(vector<Vehicle_information*> Vehicle, string model = "GHR")
{
	// 导入车辆信息
	vehicle = Vehicle;
	// 导入GHR参数数据
	Input_GHR_model_parameter_information(GHR_Para, Parameters);
	// 导入模型种类
	Model = model;
}

/**
* 析构函数
* 函数功能：释放GHR算法的结果指针
*/
GHR::~GHR()
{
	/* 删除二叉链表 */
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
	/* 删除散列表 图 */
	if (!Vehicle_time.empty())
		Vehicle_time.clear();
}

/**
* GHR 核心算法
* 函数功能：GHR模型的算法 (三秒定律)
*/
Type_model_calculation_results* GHR::GHR_model_algorithm
(float The_head_car_changes_speed, float acceleration, int timess)
{
	/**
	* 只要大于三秒定律就加速
	* 只要小于三秒定律就减速
	*/
	TIMES = timess;
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
				//rear->distance = 0.1;
				the_crash = true;
				break;
			}

			// 2.没有相撞时的比较
			else
			{
				if (Model == "GHR")
					rear_acc = rear->distance > rear->speed * Folttime ? accelerate_algori() : deceleration_algori();
				else
					rear_acc = GF_Acceleration_algorithm();
				// 2.1.2前车的变化后的速度
				front_sp = front->speed + front->acceleration;
				// 2.1.3后车的变化后的速度
				rear_sp = rear->speed + rear->acceleration > Maximum_speed ? Maximum_speed : rear->speed + rear->acceleration;
				rear_sp = rear->speed + rear->acceleration < 0  ? 1  : rear->speed + rear->acceleration;
				// 2.1.4后车与前车的间距
				rear_dis = rear->distance + ((front->speed + front_sp) / 2) - ((rear->speed + rear_sp) / 2);
			}

			// 3.接入下一秒的数据
			// 3.1如果front是头车
			if (front->key == 1 && front->next_time == NULL)
			{
				// 3.1.1赋予数据
				front_nxtime                  = new Type_model_calculation_results;
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
				// 3.1.2输入到图中
				Vehicle_time.insert(map<int, Type_model_calculation_results*> ::value_type
				(front_nxtime->time, front_nxtime));
				// 3.1.3接入结点
				front->next_time = front_nxtime;
			}
			// 3.2接入后车数据
			// 3.2.1赋予数据
			rear_nxtime                      = new Type_model_calculation_results;
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
			front->next_time->next_car       = rear_nxtime;

			// 4.下两辆车的比较
			front = rear; rear               = rear->next_car;
		}
		// 如果撞车了，就停止运算
		if (the_crash)
		{
			cout << "在第" << times << "秒";
			cout << "第" << front->key << "辆车与第" << rear->key
				 << "车相撞了！！！" << endl;
			break;
		}
	}
	return top;
}

/**
* 函数功能：获取初始状态数据
*/
void GHR::Gets_the_initial_state_data()
{
	// 创建头指针
	top = new Type_model_calculation_results;
	top->next_time = NULL; top->next_car = NULL;
	Type_model_calculation_results* p = top, * q;
	// 每辆车进行录入信息
	for (unsigned int i = 0; i < vehicle.size(); ++i)
	{
		q = new Type_model_calculation_results;
		q->time                = 0;
		q->change_speed        = 0;
		q->change_distance     = 0;
		q->change_acceleration = 0;
		q->key                 = vehicle[i]->key;
		q->speed               = vehicle[i]->speed;
		q->distance            = vehicle[i]->distance;
		q->acceleration        = q->key == 1 ? vehicle[i]->acceleration : 0;
		q->next_time = NULL;   q->next_car = NULL;
		p->next_car = q;       p = q;
	}
	Vehicle_time.insert(map<int, Type_model_calculation_results*> ::value_type
	(top->next_car->time, top->next_car));
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
	//return A > (float)1.6 ? (float)1.6 : A;
	/*if (rear->key == 6) cout << Ozaki_a << endl;*/
	return Ozaki_a;
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
	//return A < (float)-10 ? (float)-10 : A;
	/*if (rear->key == 6) cout << Ozaki_a << endl;*/
	return Ozaki_a;
}

/*
* 函数功能：获得每个时间的图，返回图
*/
Type_model_calculation_results* GHR::obtain_vehicle_map(int Temptimes)
{
	// 查找图的中指针
	rear_nxtime = Vehicle_time[Temptimes];
	return rear_nxtime;
}

/**
* 函数功能：GF模型加速的算法
*/
float GHR::GF_Acceleration_algorithm()
{
	// 当前后车是rear指针指向，前车是front指针指向
	float OV;  // 定义两个浮点的加速度
	// 1.先计算OV模型定义得参数
	// 1.1先计算f(x)的函数 反应时间为1s
	float Ds    = rear->speed * Folttime;                                      // 速度为0时的安全距离
	float f_x_t = (Maximum_speed / 2) * (tanh(rear->distance - Ds) + tanh(Ds));// 计算f(x)函数的算法
	OV          = Average_sensitivity_coefficient * (rear->speed - f_x_t);     // 计算OV模型加速度的算法
	// 2.在计算GF模型定义的参数
	OV = OV > 0 ? OV : (0 - OV);
	return rear->distance > rear->speed * Folttime ? OV : (0 - OV);
}

/**
* 函数功能：安全距离模型的算法
*/
Type_model_calculation_results* GHR::Gip_model_algorithm
(float The_head_car_changes_speed, float acceleration, int timess)
{
	/**
	* 只要大于三秒定律就加速
	* 只要小于三秒定律就减速
	*/
	TIMES = timess;
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
			// 后车需要变化的加速度,前车变化的车速，后车变化的车速，距离的变化,后车车长
			float rear_acc = 0, front_sp = 0, rear_sp = 0, rear_dis = 0, rear_co = 17;
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
				float t = 1 - response_time - addresponse_time;//减速/加速的时间
				// 2.1.2前车的变化后的速度
				front_sp = front->speed + front->acceleration;

				rear_dis = rear->distance + (front->speed * t - front->acceleration * 0.5 * pow(t, 2)) - (rear->speed * t - rear_acc * 0.5 * pow(t, 2));
				// 2.1.4后车与前车的间距
				float safe_distance;
				safe_distance = rear_dis - rear_co;
				//依靠安全距离模型得出的式子
				float  middle_result;
				middle_result = pow(maxdeceleration, 2) * pow((response_time / 2 + addresponse_time), 2) + 2 * maxdeceleration * safe_distance / (Heaviside(acceleration * (response_time + addresponse_time)) * (m1 * acceleration * (response_time + addresponse_time) + n1) + Heaviside(-acceleration * (response_time + addresponse_time)) * (m2 * rear_sp + n2));
				//  只是一个中间结果，因为模型公式太长了分开写的

				rear_sp = -maxdeceleration * (response_time / 2 + addresponse_time) + pow(middle_result, 0.5);
				// 2.1.3后车的变化后的速度
				//优化的Gipps模型下的拥挤状态（不考虑自由行驶状态）
				rear_sp = rear->speed + rear->acceleration > 32 ? 32 : rear->speed + rear->acceleration;
				rear_sp = rear->speed + rear->acceleration < 0 ? 1 : rear->speed + rear->acceleration;

			}

			// 3.接入下一秒的数据
			// 3.1如果front是头车
			if (front->key == 1 && front->next_time == NULL)
			{
				// 3.1.1赋予数据
				front_nxtime = new Type_model_calculation_results;
				front_nxtime->key = 1;                      // 车标
				front_nxtime->distance = -1;                     // 前车距离
				front_nxtime->change_distance = 0;                      // 变化的前车距离
				front_nxtime->time = times;                  // 第几秒的数据
				front_nxtime->change_speed = front_sp - front->speed;// 改变的速度
				front_nxtime->speed = front_sp;               // 改变后的速度
				front_nxtime->next_time = NULL;
				front_nxtime->next_car = NULL;
				// 变化的加速度
				if (top->next_car->speed < The_head_car_changes_speed)
					front_nxtime->acceleration = front_sp >= The_head_car_changes_speed ? 0 : acceleration;
				else
					front_nxtime->acceleration = front_sp <= The_head_car_changes_speed ? 0 : acceleration;
				front_nxtime->change_acceleration = front_nxtime->acceleration - front->acceleration;
				Vehicle_time.insert(map<int, Type_model_calculation_results*> ::value_type
				(front_nxtime->time, front_nxtime));
				// 3.1.2接入结点
				front->next_time = front_nxtime;
			}
			// 3.2接入后车数据
			// 3.2.1赋予数据
			rear_nxtime = new Type_model_calculation_results;
			rear_nxtime->key = rear->key;                    // 车标
			rear_nxtime->time = times;                        // 第几秒的数据
			rear_nxtime->speed = rear_sp;                      // 变化后的速度
			rear_nxtime->change_speed = rear_sp - rear->speed;        // 变化的速度
			rear_nxtime->acceleration = rear_acc;                     // 变化后的加速度
			rear_nxtime->change_acceleration = rear_acc - rear->acceleration;// 变化的加速度
			rear_nxtime->distance = rear_dis;                     // 变化后的车距
			rear_nxtime->change_distance = rear_dis - rear->distance;    // 变化的车距
			rear_nxtime->next_car = NULL;
			rear_nxtime->next_time = NULL;
			// 3.2.2接入结点
			rear->next_time = rear_nxtime;
			// 3.3前车的下一结点连接后车
			front->next_time->next_car = rear_nxtime;

			// 4.下两辆车的比较
			front = rear; rear = rear->next_car;
		}
		// 如果撞车了，就停止运算
		if (the_crash)
		{
			cout << "在第" << times << "秒";
			cout << "第" << front->key << "辆车与第" << rear->key
				<< "车相撞了！！！" << endl;
			break;
		}
	}
	return top;
}
