/*************************************************

Copyright:于文凯 马丽千 王泳清

Author:于文凯 马丽千 王泳清

Date:2020-05-24

Description:本程序的界面管理

**************************************************/

#pragma once
#include <iostream>
#include <iomanip>
#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <string>
#include <windows.h>
#include "GHR_model.h"
#include "Wiedemann_modle.h"
#include "Data_management.h"
#include "File_management.h"
using namespace std;

// 图形界面类的定义
class Intrt
{
public:
	Intrt();                     // 构造函数的定义
	~Intrt();                    // 析构函数的定义

private:
	void startInter();                                        // 程序开始的界面选择
	void GHR_model_interface();                               // GHR模型界面
	void GF_model_interface();                                // GF 模型界面
	void Gipps_model_interface();                             // Gipps 模型界面
	void Wiedemann_model_interface();                         // Wiedemann 模型界面
	void Model_analysis_interface();                          // 三种模型的分析
	//void Display_algorithm(Type_model_calculation_results *); // 显示算法

};

// 全局变量
vector<Vehicle_information*>   Vehicle;   //车辆信息的向量
vector<Personnel_information*> Personnel; //人员信息的向量

/**
* 构造函数
* 函数功能：在程序开始前加载数据
*/
Intrt::Intrt()
{
	/*导入数据*/
	Input_vehicle_information(Vehicle);     // 录入车辆信息
	Input_personnel_information(Personnel); // 录入人员信息
	/*开始程序*/
	startInter();
}

/**
* 析构函数
* 函数功能：在程序结束后释放向量指针内存并删除数据
*/
Intrt::~Intrt()
{
	// 清除车辆信息指针内存
	for (vector<Vehicle_information*>::iterator it = Vehicle.begin(); it != Vehicle.end(); ++it)
		if (NULL != *it)
		{
			delete* it;
			*it = NULL;
		}
	Vehicle.clear();
	// 清除人员信息指针内容
	for (vector<Personnel_information*>::iterator it = Personnel.begin(); it != Personnel.end(); ++it)
		if (NULL != *it)
		{
			delete* it;
			*it = NULL;
		}
	Personnel.clear();
}

/**
* 函数功能：程序开始的界面展示及选择
*/
void Intrt::startInter()
{
	system("cls");
	puts("\n\n\n\n\n\n\n\n\t\t\t\t\t\t\t\t\t +------------------------------+");
	puts("\t\t\t\t\t\t\t\t\t |   道路交通跟驰行为仿真系统   | ");
	puts("\t\t\t\t\t\t\t\t\t +------------------------------+\n");
	puts("\t\t\t\t\t\t\t\t  +-------------------------------------------+");
	puts("\t\t\t\t\t\t\t\t  |\t  *1.GHR  模型（反应--刺激模型）      |");
	puts("\t\t\t\t\t\t\t\t  +-------------------------------------------+");
	puts("\t\t\t\t\t\t\t\t  |\t  *2.GF   模型（总合成力理想速度模型）|");
	puts("\t\t\t\t\t\t\t\t  +-------------------------------------------+");
	puts("\t\t\t\t\t\t\t\t  |\t  *3.Gipps模型（安全距离模型）        |");
	puts("\t\t\t\t\t\t\t\t  +-------------------------------------------+");
	puts("\t\t\t\t\t\t\t\t  |\t  *4.Wiedem模型（心理--生理模型模型） |");
	puts("\t\t\t\t\t\t\t\t  +-------------------------------------------+");
	puts("\t\t\t\t\t\t\t\t  |\t  *5.三种模型分析                     |");
	/*puts("\t\t\t\t  *\t\t  *2.学生端登录               *");
	puts("\t\t\t\t  *\t\t  *3.管理员登录               *");
	puts("\t\t\t\t  *\t\t  *4.退出该系统               *");*/
	puts("\t\t\t\t\t\t\t\t  +-------------------------------------------+");
	cout << endl << "\t\t\t\t\t\t\t\t  >>>请选择您需要的仿真：";
	char options; // 选择仿真的选项
	cin >> options;
	switch (options)
	{
	case '1':        // GHR模型的实现
		GHR_model_interface();
		system("pause");
		startInter();
		break;
	case '2':        // GF模型的实现
		GF_model_interface();
		system("pause");
		startInter();
		break;
	case '3':
		Gipps_model_interface();
		system("pause");
		startInter();
		break;
	case '4':
		Wiedemann_model_interface();
		system("pause");
		startInter();
		break;
	case '5':
		Model_analysis_interface();
		system("pause");
		startInter();
		break;
	default:
		break;
	}
}

/**
*  函数功能：GHR模型界面的设计与运算
*/
void Intrt::GHR_model_interface()
{
	system("cls");
	puts("\n\t\t\t\t\t\t\t\t\t +--------------------------------+");
	puts("\t\t\t\t\t\t\t\t\t |   刺激-反应模型(GHR)仿真界面   |");
	puts("\t\t\t\t\t\t\t\t\t +--------------------------------+\n");
	// 1.显示车辆数据
	puts("\t\t\t\t\t\t     +----------------------------------------------------------------------+");
	puts("\t\t\t\t\t\t     |                         Vehicle  Information                         |");
	puts("\t\t\t\t\t\t     +---------+-----------+------------------+---------------+-------------+");
	cout << "\t\t\t\t\t\t     |" << setw(6) << "key" << setw(4) << "|" << setw(8) << "speed" <<
		setw(4) << "|" << setw(15) << "acceleration" << setw(4) << "|" << setw(12) <<
		"conductor" << setw(4) << "|" << setw(11) << "distance" << setw(4) << "|\n";
	puts("\t\t\t\t\t\t     +---------+-----------+------------------+---------------+-------------+");
	cout << setiosflags(ios::left | ios::showpoint);  // 设左对齐，以一般实数方式显示
	for (unsigned int i = 0; i < Vehicle.size(); ++i)
	{
		cout << "\t\t\t\t\t\t     |  " << setw(7) << Vehicle[i]->key << "|   " << setw(8) << fixed <<
			setprecision(2) << Vehicle[i]->speed << "|       " << setw(11) << Vehicle[i]->acceleration
			<< "|      " << setw(9) << Vehicle[i]->conductor << "|    " << setw(9) << Vehicle[i]->distance
			<< "|\n";
	}
	puts("\t\t\t\t\t\t     +---------+-----------+------------------+---------------+-------------+\n");
	// 2.显示GHR参数数据
	cout << setiosflags(ios::right | ios::showpoint);
	puts("\t\t\t\t\t\t       +------------------------------------------------------------------+");
	puts("\t\t\t\t\t\t       |                    GHR Parameter Information                     |");
	puts("\t\t\t\t\t\t       +----------+-----------------+------------+-----------+------------+");
	cout << "\t\t\t\t\t\t       |" << setw(6) << "The Author" << "| " << "Parameter Types |" << setw(7)
		<< "C" << setw(6) << "|" << setw(7) << "M" << setw(5) << "|" << setw(7) << "L" << setw(7) << "|\n";
	puts("\t\t\t\t\t\t       +----------+-----------------+------------+-----------+------------+");
	cout << resetiosflags(ios::right);  // 清除状态右对齐
	cout << setiosflags(ios::left | ios::showpoint);  // 设左对齐，以一般实数方式显示
	cout << fixed << setprecision(3);
	for (int i = 0; i < 6; ++i)
	{
		switch (i)
		{
		case 1:
			cout << "\t\t\t\t\t\t       |   " << setw(7) << "Aron   |";
			cout << "   " << setw(14) << "Stable" << "|    " << setw(8) << 2.67 << "|    "
				<< setw(7) << 0.26 << "|    " << setw(8) << 0.5 << "|\n";
			break;
		case 3:
			cout << "\t\t\t\t\t\t       +----------+-----------------+------------+-----------+------------+\n";
			break;
		case 4:
			cout << "\t\t\t\t\t\t       |   " << setw(7) << "Ozaki" << "|";
			cout << "   " << setw(14) << "Deceleration" << "|    " << setw(8) << 1.1 << "|    "
				<< setw(7) << 0.9 << "|    " << setw(8) << 1.0 << "|\n";
			break;
		default:
			cout << "\t\t\t\t\t\t       " << setw(11) << "|" << "|";
			if (i == 0)
				cout << "   " << setw(14) << "Deceleration" << "|    " << setw(8) << 2.45 << "|    "
				<< setw(7) << 0.655 << "|    " << setw(8) << 0.676 << "|\n";
			else
				if (i == 2)
					cout << "   " << setw(14) << "Scelerated" << "|    " << setw(8) << 2.46 << "|    "
					<< setw(7) << 0.14 << "|    " << setw(8) << 0.18 << "|\n";
				else
					cout << "   " << setw(14) << "Scelerated" << "|    " << setw(8) << 1.1 << "|    "
					<< setw(7) << -0.2 << "|    " << setw(8) << 0.2 << "|\n";
			break;
		}
	}
	puts("\t\t\t\t\t\t       +----------+-----------------+------------+-----------+------------+\n");
	// 3.需要用户自己输入改变头车的信息
	float changespeed = 0, accacc = 0;
	int times = 0;
	cout << "\t\t\t\t\t\t~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n";
	cout << "\t\t\t\t\t\t\t* Please enter the speed of the first car after the change(m/s)：";
	cin >> changespeed;
	cout << "\n\t\t\t\t\t\t\t* Please enter the acceleration of the first car changing speed：";
	cin >> accacc;
	cout << "\n\t\t\t\t\t\t\t* Please enter the time length of GHR model simulation operation:";
	cin >> times;
	puts("\n\t\t\t\t\t\t~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~");
	// 4.执行GHR算法
	GHR ghr(Vehicle);
	Type_model_calculation_results* top = ghr.GHR_model_algorithm(changespeed, accacc, times);
	// 5.GHR算法的展示 选择展示的方式
	puts("\t\t\t\t\t\t\t\t        +---------------------------------+");
	puts("\t\t\t\t\t\t\t\t        |        Display Data Mode        |");
	puts("\t\t\t\t\t\t\t\t        +----+----------------------------+");
	puts("\t\t\t\t\t\t\t\t        | 1. |  Total change information  |");
	puts("\t\t\t\t\t\t\t\t        | 2. |  Single vehicle information|");
	puts("\t\t\t\t\t\t\t\t        | 3. |  Single time information   |");
	puts("\t\t\t\t\t\t\t\t        +----+----------------------------+");
	int display = 1;
begin:
	cout << "\t\t\t\t\t\t\t\t* Please enter the data format you want to display：";
	cin >> display;
	Type_model_calculation_results* head = NULL;
	switch (display)
	{
	case 1:
	{
		// 5.1显示整体的数据
		// 5.1.1标题的定位
		system("cls");
		cout << resetiosflags(ios::left);  // 清除状态右对齐
		cout << setiosflags(ios::right);  // 设左对齐，以一般实数方式显示
		cout << "+--------";
		for (int i = 0; i < 9; ++i) cout << "------------------";
		cout << "-----------------+\n";
		cout << "+";
		cout << setw(99) << "GHR model simulation data" << setw(89) << "+";
		cout << "\n+-------+";
		for (int i = 0; i < 10; ++i) cout << "-----------------+";
		cout << "|       |";
		for (int i = 0; i < 10; ++i)
		{
			cout << setw(9) << "NO." << i + 1;
			if (i == 9)
				cout << setw(7) << "|";
			else
				cout << setw(8) << "|";
		}
		cout << "\n+ TIMES +";
		for (int i = 0; i < 10; ++i) cout << "-----|-----|-----+";
		cout << "\n|       |";
		for (int i = 0; i < 10; ++i) cout << "SPEED|ACCEL|DISTA|";
		cout << "\n+-------+";
		for (int i = 0; i < 10; ++i) cout << "-----|-----|-----+";
		cout << endl;
		// 5.1.2数据的展示
		cout << fixed << setprecision(1);
		head = top->next_car; top = head;
		while (head != NULL)
		{
			while (top != NULL)
			{
				if (top->key == 1) cout << "|" << setw(5) << top->time << "  |";
				cout << setw(5) << top->speed << "|" << setw(5) << top->acceleration << "|" << setw(5)
					<< top->distance << "|";
				top = top->next_car;
			}
			// 下一段时间的数据
			head = head->next_time;
			top = head;
		}
		cout << "\n+-------+";
		for (int i = 0; i < 10; ++i) cout << "-----------------+";
	}
	break;
	case 2:
	{
		int car_number;    // 定义车辆的编号
		/* 找到需要查看的车的信息 */
		cout << "\n\t\t\t\t\t\t\t\t* Please enter the vehicle number you wish to inquire:";
		cin >> car_number; // 输入车辆的编号（无判断程序的健壮性）
		/* 获得该车的全部信息 */
		head = top;
		system("cls"); // 清屏
		while (car_number--) head = head->next_car;
		// 5.2.1 标题的定位
		puts("\t\t\t\t\t\t\t    +-----------------------------------------------------------------+");
		cout << "\t\t\t\t\t\t\t    | GHR Model Simulation Information Of Car NO.";
		printf("%2d Changes With Time |\n", head->key);
		puts("\t\t\t\t\t\t\t    +-----+---------+---------+---------+---------+---------+---------+");
		puts("\t\t\t\t\t\t\t    |Times|  Speed  | C_speed |  Accel  | C_Accel |  Dista  | C_dista |");
		puts("\t\t\t\t\t\t\t    +-----+---------+---------+---------+---------+---------+---------+");
		// 5.2.2 数据的展示
		while (head != NULL)
		{
			printf("\t\t\t\t\t\t\t    | %3d | %6.3f  | %6.2f  | %6.2f  | %6.2f  | %7.3f | %7.2f |\n",
				head->time, head->speed, head->change_speed, head->acceleration, head->change_acceleration,
				head->distance, head->change_distance);
			head = head->next_time;
		}
		puts("\t\t\t\t\t\t\t    +-----+---------+---------+---------+---------+---------+---------+");
	}
	break;
	case 3:
	{
		// 找到需要的时间
		int startTime = 0, endTime = 0;
		cout << "\n\t\t\t\t\t\t\t\t* Please enter the vehicle information for the time period you need:";
		scanf_s("%d-%d", &startTime, &endTime);
		endTime = endTime == 0 ? startTime : endTime;
		head = ghr.obtain_vehicle_map(startTime);  /* 找到信息 */
		// 展示信息
		cout << resetiosflags(ios::left);  // 清除状态右对齐
		cout << setiosflags(ios::right);  // 设左对齐，以一般实数方式显示
		system("cls");
		cout << "+--------";
		for (int i = 0; i < 9; ++i) cout << "------------------";
		cout << "-----------------+\n";
		cout << "+";
		cout << setw(107) << "Time GHR Model Vehicle Information" << setw(81) << "+";
		cout << "+--------";
		for (int i = 0; i < 9; ++i) cout << "------------------";
		cout << "-----------------+\n";
		cout << "|       |";
		for (int i = 0; i < 10; ++i)
		{
			cout << setw(9) << "NO." << i + 1;
			if (i == 9)
				cout << setw(7) << "|";
			else
				cout << setw(8) << "|";
		}
		cout << "\n+ TIMES +";
		for (int i = 0; i < 10; ++i) cout << "-----|-----|-----+";
		cout << "\n|       |";
		for (int i = 0; i < 10; ++i) cout << "SPEED|ACCEL|DISTA|";
		cout << "\n+-------+";
		for (int i = 0; i < 10; ++i) cout << "-----|-----|-----+";
		// 数据显示
		cout << fixed << setprecision(1);
		Type_model_calculation_results* temp = head;
		while (1 + endTime - (startTime++) && temp != NULL)
		{
			head = temp;
			while (head != NULL)
			{
				if (head->key == 1) cout << "|" << setw(5) << head->time << "  |";
				cout << setw(5) << head->speed << "|" << setw(5) << head->acceleration << "|" << setw(5)
					<< head->distance << "|";
				head = head->next_car;
			}
			temp = temp->next_time;
			cout << endl;
		}
		cout << "+-------+";
		for (int i = 0; i < 10; ++i) cout << "-----------------+";
	}
	break;
	default:
		goto begin;
		break;
	}
}

/**
* 函数功能：GF模型的界面设计与运算
*/
void Intrt::GF_model_interface()
{
	system("cls");
	puts("\n\t\t\t\t\t\t\t\t\t +--------------------------------+");
	puts("\t\t\t\t\t\t\t\t\t |  总合成力理想速度(GF)仿真界面  |");
	puts("\t\t\t\t\t\t\t\t\t +--------------------------------+\n");
	// 1.显示车辆数据
	puts("\t\t\t\t\t\t     +----------------------------------------------------------------------+");
	puts("\t\t\t\t\t\t     |                         Vehicle  Information                         |");
	puts("\t\t\t\t\t\t     +---------+-----------+------------------+---------------+-------------+");
	cout << "\t\t\t\t\t\t     |" << setw(6) << "key" << setw(4) << "|" << setw(8) << "speed" <<
		setw(4) << "|" << setw(15) << "acceleration" << setw(4) << "|" << setw(12) <<
		"conductor" << setw(4) << "|" << setw(11) << "distance" << setw(4) << "|\n";
	puts("\t\t\t\t\t\t     +---------+-----------+------------------+---------------+-------------+");
	cout << setiosflags(ios::left | ios::showpoint);  // 设左对齐，以一般实数方式显示
	for (unsigned int i = 0; i < Vehicle.size(); ++i)
	{
		cout << "\t\t\t\t\t\t     |  " << setw(7) << Vehicle[i]->key << "|   " << setw(8) << fixed <<
			setprecision(2) << Vehicle[i]->speed << "|       " << setw(11) << Vehicle[i]->acceleration
			<< "|      " << setw(9) << Vehicle[i]->conductor << "|    " << setw(9) << Vehicle[i]->distance
			<< "|\n";
	}
	puts("\t\t\t\t\t\t     +---------+-----------+------------------+---------------+-------------+\n");
	// 2.需要用户自己输入改变头车的信息
	float changespeed = 0, accacc = 0;
	int times = 0;
	cout << "\t\t\t\t\t\t~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n";
	cout << "\t\t\t\t\t\t\t* Please enter the speed of the first car after the change(m/s)：";
	cin >> changespeed;
	cout << "\n\t\t\t\t\t\t\t* Please enter the acceleration of the first car changing speed：";
	cin >> accacc;
	cout << "\n\t\t\t\t\t\t\t* Please enter the time length of GHR model simulation operation:";
	cin >> times;
	puts("\n\t\t\t\t\t\t~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~");
	// 4.执行GHR算法
	GHR ghr(Vehicle, "GF");
	Type_model_calculation_results* top = ghr.GHR_model_algorithm(changespeed, accacc, times);
	// 5.GHR算法的展示 选择展示的方式
	puts("\t\t\t\t\t\t\t\t        +---------------------------------+");
	puts("\t\t\t\t\t\t\t\t        |        Display Data Mode        |");
	puts("\t\t\t\t\t\t\t\t        +----+----------------------------+");
	puts("\t\t\t\t\t\t\t\t        | 1. |  Total change information  |");
	puts("\t\t\t\t\t\t\t\t        | 2. |  Single vehicle information|");
	puts("\t\t\t\t\t\t\t\t        | 3. |  Single time information   |");
	puts("\t\t\t\t\t\t\t\t        +----+----------------------------+");
	int display = 1;
begin:
	cout << "\t\t\t\t\t\t\t\t* Please enter the data format you want to display：";
	cin >> display;
	Type_model_calculation_results* head = NULL;
	switch (display)
	{
	case 1:
	{
		// 5.1显示整体的数据
		// 5.1.1标题的定位
		system("cls");
		cout << resetiosflags(ios::left);  // 清除状态右对齐
		cout << setiosflags(ios::right);  // 设左对齐，以一般实数方式显示
		cout << "+--------";
		for (int i = 0; i < 9; ++i) cout << "------------------";
		cout << "-----------------+\n";
		cout << "+";
		cout << setw(99) << "G F model simulation data" << setw(89) << "+";
		cout << "\n+-------+";
		for (int i = 0; i < 10; ++i) cout << "-----------------+";
		cout << "|       |";
		for (int i = 0; i < 10; ++i)
		{
			cout << setw(9) << "NO." << i + 1;
			if (i == 9)
				cout << setw(7) << "|";
			else
				cout << setw(8) << "|";
		}
		cout << "\n+ TIMES +";
		for (int i = 0; i < 10; ++i) cout << "-----|-----|-----+";
		cout << "\n|       |";
		for (int i = 0; i < 10; ++i) cout << "SPEED|ACCEL|DISTA|";
		cout << "\n+-------+";
		for (int i = 0; i < 10; ++i) cout << "-----|-----|-----+";
		cout << endl;
		// 5.1.2数据的展示
		cout << fixed << setprecision(1);
		head = top->next_car; top = head;
		while (head != NULL)
		{
			while (top != NULL)
			{
				if (top->key == 1) cout << "|" << setw(5) << top->time << "  |";
				cout << setw(5) << top->speed << "|" << setw(5) << top->acceleration << "|" << setw(5)
					<< top->distance << "|";
				top = top->next_car;
			}
			// 下一段时间的数据
			head = head->next_time;
			top = head;
		}
		cout << "\n+-------+";
		for (int i = 0; i < 10; ++i) cout << "-----------------+";
	}
	break;
	case 2:
	{
		int car_number;    // 定义车辆的编号
		/* 找到需要查看的车的信息 */
		cout << "\n\t\t\t\t\t\t\t\t* Please enter the vehicle number you wish to inquire:";
		cin >> car_number; // 输入车辆的编号（无判断程序的健壮性）
		/* 获得该车的全部信息 */
		head = top;
		system("cls"); // 清屏
		while (car_number--) head = head->next_car;
		// 5.2.1 标题的定位
		puts("\t\t\t\t\t\t\t    +-----------------------------------------------------------------+");
		cout << "\t\t\t\t\t\t\t    | G F Model Simulation Information Of Car NO.";
		printf("%2d Changes With Time |\n", head->key);
		puts("\t\t\t\t\t\t\t    +-----+---------+---------+---------+---------+---------+---------+");
		puts("\t\t\t\t\t\t\t    |Times|  Speed  | C_speed |  Accel  | C_Accel |  Dista  | C_dista |");
		puts("\t\t\t\t\t\t\t    +-----+---------+---------+---------+---------+---------+---------+");
		// 5.2.2 数据的展示
		while (head != NULL)
		{
			printf("\t\t\t\t\t\t\t    | %3d | %6.3f  | %6.2f  | %6.2f  | %6.2f  | %7.3f | %7.2f |\n",
				head->time, head->speed, head->change_speed, head->acceleration, head->change_acceleration,
				head->distance, head->change_distance);
			head = head->next_time;
		}
		puts("\t\t\t\t\t\t\t    +-----+---------+---------+---------+---------+---------+---------+");
	}
	break;
	case 3:
	{
		// 找到需要的时间
		int startTime = 0, endTime = 0;
		cout << "\n\t\t\t\t\t\t\t\t* Please enter the vehicle information for the time period you need:";
		scanf_s("%d-%d", &startTime, &endTime);
		endTime = endTime == 0 ? startTime : endTime;
		head = ghr.obtain_vehicle_map(startTime);  /* 找到信息 */
		// 展示信息
		cout << resetiosflags(ios::left);  // 清除状态右对齐
		cout << setiosflags(ios::right);  // 设左对齐，以一般实数方式显示
		system("cls");
		cout << "+--------";
		for (int i = 0; i < 9; ++i) cout << "------------------";
		cout << "-----------------+\n";
		cout << "+";
		cout << setw(107) << "Time G F Model Vehicle Information" << setw(81) << "+";
		cout << "+--------";
		for (int i = 0; i < 9; ++i) cout << "------------------";
		cout << "-----------------+\n";
		cout << "|       |";
		for (int i = 0; i < 10; ++i)
		{
			cout << setw(9) << "NO." << i + 1;
			if (i == 9)
				cout << setw(7) << "|";
			else
				cout << setw(8) << "|";
		}
		cout << "\n+ TIMES +";
		for (int i = 0; i < 10; ++i) cout << "-----|-----|-----+";
		cout << "\n|       |";
		for (int i = 0; i < 10; ++i) cout << "SPEED|ACCEL|DISTA|";
		cout << "\n+-------+";
		for (int i = 0; i < 10; ++i) cout << "-----|-----|-----+";
		// 数据显示
		cout << fixed << setprecision(1);
		Type_model_calculation_results* temp = head;
		while (1 + endTime - (startTime++) && temp != NULL)
		{
			head = temp;
			while (head != NULL)
			{
				if (head->key == 1) cout << "|" << setw(5) << head->time << "  |";
				cout << setw(5) << head->speed << "|" << setw(5) << head->acceleration << "|" << setw(5)
					<< head->distance << "|";
				head = head->next_car;
			}
			temp = temp->next_time;
			cout << endl;
		}
		cout << "+-------+";
		for (int i = 0; i < 10; ++i) cout << "-----------------+";
	}
	break;
	default:
		goto begin;
		break;
	}
}

/**
* 函数功能：Gipps模型的界面设计与运算
*/
void Intrt::Gipps_model_interface()
{
	system("cls");
	puts("\n\t\t\t\t\t\t\t\t\t +--------------------------------+");
	puts("\t\t\t\t\t\t\t\t\t |  安全距离模型(Gipps)仿真界面   |");
	puts("\t\t\t\t\t\t\t\t\t +--------------------------------+\n");
	// 1.显示车辆数据
	puts("\t\t\t\t\t\t     +----------------------------------------------------------------------+");
	puts("\t\t\t\t\t\t     |                         Vehicle  Information                         |");
	puts("\t\t\t\t\t\t     +---------+-----------+------------------+---------------+-------------+");
	cout << "\t\t\t\t\t\t     |" << setw(6) << "key" << setw(4) << "|" << setw(8) << "speed" <<
		setw(4) << "|" << setw(15) << "acceleration" << setw(4) << "|" << setw(12) <<
		"conductor" << setw(4) << "|" << setw(11) << "distance" << setw(4) << "|\n";
	puts("\t\t\t\t\t\t     +---------+-----------+------------------+---------------+-------------+");
	cout << setiosflags(ios::left | ios::showpoint);  // 设左对齐，以一般实数方式显示
	for (unsigned int i = 0; i < Vehicle.size(); ++i)
	{
		cout << "\t\t\t\t\t\t     |  " << setw(7) << Vehicle[i]->key << "|   " << setw(8) << fixed <<
			setprecision(2) << Vehicle[i]->speed << "|       " << setw(11) << Vehicle[i]->acceleration
			<< "|      " << setw(9) << Vehicle[i]->conductor << "|    " << setw(9) << Vehicle[i]->distance
			<< "|\n";
	}
	puts("\t\t\t\t\t\t     +---------+-----------+------------------+---------------+-------------+\n");
	// 2.需要用户自己输入改变头车的信息
	float changespeed = 0, accacc = 0;
	int times = 0;
	cout << "\t\t\t\t\t\t~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n";
	cout << "\t\t\t\t\t\t\t* Please enter the speed of the first car after the change(m/s)：";
	cin >> changespeed;
	cout << "\n\t\t\t\t\t\t\t* Please enter the acceleration of the first car changing speed：";
	cin >> accacc;
	cout << "\n\t\t\t\t\t\t\t* Please enter the time length of GHR model simulation operation:";
	cin >> times;
	puts("\n\t\t\t\t\t\t~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~");
	// 执行安全距离模型算法
	GHR Gipps(Vehicle);
	Type_model_calculation_results* top = Gipps.Gip_model_algorithm(changespeed, accacc, times);
	// 显示数据
	puts("\t\t\t\t\t\t\t\t        +---------------------------------+");
	puts("\t\t\t\t\t\t\t\t        |        Display Data Mode        |");
	puts("\t\t\t\t\t\t\t\t        +----+----------------------------+");
	puts("\t\t\t\t\t\t\t\t        | 1. |  Total change information  |");
	puts("\t\t\t\t\t\t\t\t        | 2. |  Single vehicle information|");
	puts("\t\t\t\t\t\t\t\t        | 3. |  Single time information   |");
	puts("\t\t\t\t\t\t\t\t        +----+----------------------------+");
	int display = 1;
begin:
	cout << "\t\t\t\t\t\t\t\t* Please enter the data format you want to display：";
	cin >> display;
	Type_model_calculation_results* head = NULL;
	switch (display)
	{
	case 1:
	{
		// 5.1显示整体的数据
		// 5.1.1标题的定位
		system("cls");
		cout << resetiosflags(ios::left);  // 清除状态右对齐
		cout << setiosflags(ios::right);  // 设左对齐，以一般实数方式显示
		cout << "+--------";
		for (int i = 0; i < 9; ++i) cout << "------------------";
		cout << "-----------------+\n";
		cout << "+";
		cout << setw(99) << "Gip model simulation data" << setw(89) << "+";
		cout << "\n+-------+";
		for (int i = 0; i < 10; ++i) cout << "-----------------+";
		cout << "|       |";
		for (int i = 0; i < 10; ++i)
		{
			cout << setw(9) << "NO." << i + 1;
			if (i == 9)
				cout << setw(7) << "|";
			else
				cout << setw(8) << "|";
		}
		cout << "\n+ TIMES +";
		for (int i = 0; i < 10; ++i) cout << "-----|-----|-----+";
		cout << "\n|       |";
		for (int i = 0; i < 10; ++i) cout << "SPEED|ACCEL|DISTA|";
		cout << "\n+-------+";
		for (int i = 0; i < 10; ++i) cout << "-----|-----|-----+";
		cout << endl;
		// 5.1.2数据的展示
		cout << fixed << setprecision(1);
		head = top->next_car; top = head;
		while (head != NULL)
		{
			while (top != NULL)
			{
				if (top->key == 1) cout << "|" << setw(5) << top->time << "  |";
				cout << setw(5) << top->speed << "|" << setw(5) << top->acceleration << "|" << setw(5)
					<< top->distance << "|";
				top = top->next_car;
			}
			// 下一段时间的数据
			head = head->next_time;
			top = head;
		}
		cout << "\n+-------+";
		for (int i = 0; i < 10; ++i) cout << "-----------------+";
	}
	break;
	case 2:
	{
		int car_number;    // 定义车辆的编号
		/* 找到需要查看的车的信息 */
		cout << "\n\t\t\t\t\t\t\t\t* Please enter the vehicle number you wish to inquire:";
		cin >> car_number; // 输入车辆的编号（无判断程序的健壮性）
		/* 获得该车的全部信息 */
		head = top;
		system("cls"); // 清屏
		while (car_number--) head = head->next_car;
		// 5.2.1 标题的定位
		puts("\t\t\t\t\t\t\t    +-----------------------------------------------------------------+");
		cout << "\t\t\t\t\t\t\t    | GIP Model Simulation Information Of Car NO.";
		printf("%2d Changes With Time |\n", head->key);
		puts("\t\t\t\t\t\t\t    +-----+---------+---------+---------+---------+---------+---------+");
		puts("\t\t\t\t\t\t\t    |Times|  Speed  | C_speed |  Accel  | C_Accel |  Dista  | C_dista |");
		puts("\t\t\t\t\t\t\t    +-----+---------+---------+---------+---------+---------+---------+");
		// 5.2.2 数据的展示
		while (head != NULL)
		{
			printf("\t\t\t\t\t\t\t    | %3d | %6.3f  | %6.2f  | %6.2f  | %6.2f  | %7.3f | %7.2f |\n",
				head->time, head->speed, head->change_speed, head->acceleration, head->change_acceleration,
				head->distance, head->change_distance);
			head = head->next_time;
		}
		puts("\t\t\t\t\t\t\t    +-----+---------+---------+---------+---------+---------+---------+");
	}
	break;
	case 3:
	{
		// 找到需要的时间
		int startTime = 0, endTime = 0;
		cout << "\n\t\t\t\t\t\t\t\t* Please enter the vehicle information for the time period you need:";
		scanf_s("%d-%d", &startTime, &endTime);
		endTime = endTime == 0 ? startTime : endTime;
		head = Gipps.obtain_vehicle_map(startTime);  /* 找到信息 */
		// 展示信息
		cout << resetiosflags(ios::left);  // 清除状态右对齐
		cout << setiosflags(ios::right);  // 设左对齐，以一般实数方式显示
		system("cls");
		cout << "+--------";
		for (int i = 0; i < 9; ++i) cout << "------------------";
		cout << "-----------------+\n";
		cout << "+";
		cout << setw(107) << "Time G F Model Vehicle Information" << setw(81) << "+";
		cout << "+--------";
		for (int i = 0; i < 9; ++i) cout << "------------------";
		cout << "-----------------+\n";
		cout << "|       |";
		for (int i = 0; i < 10; ++i)
		{
			cout << setw(9) << "NO." << i + 1;
			if (i == 9)
				cout << setw(7) << "|";
			else
				cout << setw(8) << "|";
		}
		cout << "\n+ TIMES +";
		for (int i = 0; i < 10; ++i) cout << "-----|-----|-----+";
		cout << "\n|       |";
		for (int i = 0; i < 10; ++i) cout << "SPEED|ACCEL|DISTA|";
		cout << "\n+-------+";
		for (int i = 0; i < 10; ++i) cout << "-----|-----|-----+";
		// 数据显示
		cout << fixed << setprecision(1);
		Type_model_calculation_results* temp = head;
		while (1 + endTime - (startTime++) && temp != NULL)
		{
			head = temp;
			while (head != NULL)
			{
				if (head->key == 1) cout << "|" << setw(5) << head->time << "  |";
				cout << setw(5) << head->speed << "|" << setw(5) << head->acceleration << "|" << setw(5)
					<< head->distance << "|";
				head = head->next_car;
			}
			temp = temp->next_time;
			cout << endl;
		}
		cout << "+-------+";
		for (int i = 0; i < 10; ++i) cout << "-----------------+";
	}
	break;
	default:
		goto begin;
		break;
	}
}

/**
*函数功能：Wiedemann 模型界面
*/
void Intrt::Wiedemann_model_interface()
{
	system("cls");
	maining();
}

/**
* 函数功能：分析三种模型的算法界面
*/
void Intrt::Model_analysis_interface()
{
	system("cls");
	puts("\n\t\t\t\t\t\t\t\t\t +--------------------------------+");
	puts("\t\t\t\t\t\t\t\t\t |    三种模型的分析比较界面      |");
	puts("\t\t\t\t\t\t\t\t\t +--------------------------------+\n");
	puts("\t\t\t\t\t\t     +----------------------------------------------------------------------+");
	puts("\t\t\t\t\t\t     |                         Vehicle  Information                         |");
	puts("\t\t\t\t\t\t     +---------+-----------+------------------+---------------+-------------+");
	cout << "\t\t\t\t\t\t     |" << setw(6) << "key" << setw(4) << "|" << setw(8) << "speed" <<
		setw(4) << "|" << setw(15) << "acceleration" << setw(4) << "|" << setw(12) <<
		"conductor" << setw(4) << "|" << setw(11) << "distance" << setw(4) << "|\n";
	puts("\t\t\t\t\t\t     +---------+-----------+------------------+---------------+-------------+");
	cout << setiosflags(ios::left | ios::showpoint);  // 设左对齐，以一般实数方式显示
	for (unsigned int i = 0; i < Vehicle.size(); ++i)
	{
		cout << "\t\t\t\t\t\t     |  " << setw(7) << Vehicle[i]->key << "|   " << setw(8) << fixed <<
			setprecision(2) << Vehicle[i]->speed << "|       " << setw(11) << Vehicle[i]->acceleration
			<< "|      " << setw(9) << Vehicle[i]->conductor << "|    " << setw(9) << Vehicle[i]->distance
			<< "|\n";
	}
	puts("\t\t\t\t\t\t     +---------+-----------+------------------+---------------+-------------+\n");
	float changespeed = 0, accacc = 0;
	int times = 0;
	cout << "\t\t\t\t\t\t~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n";
	cout << "\t\t\t\t\t\t\t* Please enter the speed of the first car after the change(m/s)：";
	cin >> changespeed;
	cout << "\n\t\t\t\t\t\t\t* Please enter the acceleration of the first car changing speed：";
	cin >> accacc;
	cout << "\n\t\t\t\t\t\t\t* Please enter the time length of GHR model simulation operation:";
	cin >> times;
	puts("\n\t\t\t\t\t\t~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~");
	int No_N = 0, time = 0;
	cout << "\n\t\t\t\t\t\t\t\t* Please enter the model of vehicle to be analyzed: ";
	cin >> No_N;
	cout << "\n\t\t\t\t\t\t\t\t* Please enter the timestamp to be analyzed: ";
	cin >> time;
	puts("\n\t\t\t\t\t\t~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~");
	// 进行第一个模型演算
	cout << "\t\t\t\t\t\t\t  *** GHR模型正在计算中......\n";
	GHR ghr(Vehicle);
	ghr.GHR_model_algorithm(changespeed, accacc, times);
	Type_model_calculation_results* head_1 = ghr.obtain_vehicle_map(time);
	Sleep(1000);
	cout << "\t\t\t\t\t\t\t  *** G F模型正在计算中......\n";
	GHR gf(Vehicle, "GF");
	gf.GHR_model_algorithm(changespeed, accacc, times);
	Type_model_calculation_results* head_2 = gf.obtain_vehicle_map(time);
	Sleep(1000);
	cout << "\t\t\t\t\t\t\t  *** Gipps模型正在计算中......\n";
	GHR gipps(Vehicle);
	gipps.Gip_model_algorithm(changespeed, accacc, times);
	Type_model_calculation_results* head_3 = gipps.obtain_vehicle_map(time);
	Sleep(1000);
	// 展示数据
	system("cls");
	puts("\n\n\n\n\n\t\t\t\t\t\t\t+---------------------------------------------------------------------+");
	cout << "\t\t\t\t\t\t\t|  Three Model Simulation Information Of Car NO.";
	printf("%2d Changes With Time  |\n", No_N);
	while (--No_N)
	{
		head_1 = head_1->next_car;
		head_3 = head_3->next_car;
		head_2 = head_2->next_car;
	}
	puts("\t\t\t\t\t\t\t+---+-----+---------+---------+---------+---------+---------+---------+");
	puts("\t\t\t\t\t\t\t|Mod|Times|  Speed  | C_speed |  Accel  | C_Accel |  Dista  | C_dista |");
	puts("\t\t\t\t\t\t\t+---+-----+---------+---------+---------+---------+---------+---------+");
	// 5.2.2 数据的展示
	printf("\t\t\t\t\t\t\t|GHR| %3d | %6.3f  | %6.2f  | %6.2f  | %6.2f  | %7.3f | %7.2f |\n",
	head_1->time, head_1->speed, head_1->change_speed, head_1->acceleration, head_1->change_acceleration,
		head_1->distance, head_1->change_distance);
	puts("\t\t\t\t\t\t\t+---+-----+---------+---------+---------+---------+---------+---------+");
	printf("\t\t\t\t\t\t\t|G F| %3d | %6.3f  | %6.2f  | %6.2f  | %6.2f  | %7.3f | %7.2f |\n",
		head_2->time, head_2->speed, head_2->change_speed, head_2->acceleration, head_2->change_acceleration,
		head_2->distance, head_2->change_distance);
	puts("\t\t\t\t\t\t\t+---+-----+---------+---------+---------+---------+---------+---------+");
	printf("\t\t\t\t\t\t\t|GIP| %3d | %6.3f  | %6.2f  | %6.2f  | %6.2f  | %7.3f | %7.2f |\n",
		head_3->time, head_3->speed, head_3->change_speed, head_3->acceleration, head_3->change_acceleration,
		head_3->distance, head_3->change_distance);
	puts("\t\t\t\t\t\t\t+---+-----+---------+---------+---------+---------+---------+---------+");
	// 5.2.2 数据的展示

}
