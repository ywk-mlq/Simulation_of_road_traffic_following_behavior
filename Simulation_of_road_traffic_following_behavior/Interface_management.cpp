/*************************************************

Copyright:于文凯 马丽千

Author:于文凯 马丽千

Date:2020-05-24

Description:本程序的界面管理

**************************************************/

#pragma once
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <string>
#include "GHR_model.h"
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
	void startInter();           // 程序开始的界面选择
	void GHR_model_interface();  // GHR模型界面

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
	puts("\t\t\t\t\t >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>");
	puts("\t\t\t\t\t >>>>道路交通跟驰行为仿真系统<<<< ");
	puts("\t\t\t\t\t <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<\n");
	puts("\t\t\t\t  *********************************************");
	puts("\t\t\t\t  *\t  *1.GHR模型（反应--刺激模型）        *");

	/*puts("\t\t\t\t  *\t\t  *2.学生端登录               *");
	puts("\t\t\t\t  *\t\t  *3.管理员登录               *");
	puts("\t\t\t\t  *\t\t  *4.退出该系统               *");*/
	puts("\t\t\t\t  *********************************************");
	cout << endl << "\t\t\t\t  >>>请选择您需要的仿真：";
	char options; // 选择仿真的选项
	cin >> options;
	switch (options)
	{
	case '1':        // GHR模型的实现
		GHR_model_interface();
		break;
	default:
		exit(-1);
		break;
	}
}

/**
*  函数功能：GHR模型界面的设计与运算
*/
void Intrt::GHR_model_interface()
{
	system("cls");
	puts("\t\t\t\t\t >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>");
	puts("\t\t\t\t\t >>>刺激-反应模型(GHR)仿真界面<<< ");
	puts("\t\t\t\t\t <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<\n");
	GHR ghr(Vehicle);
	// 先显示数据

	// GHR算法
	ghr.GHR_model_algorithm(30);
}
