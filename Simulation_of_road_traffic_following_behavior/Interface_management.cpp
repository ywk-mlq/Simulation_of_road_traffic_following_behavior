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
#include "Data_management.h"
#include "GHR_model.h"
#include "File_management.h"
using namespace std;

// 图形界面类的定义
class Intrt
{
public:
	Intrt();  // 构造函数的定义
	~Intrt(); // 析构函数的定义
	void startInter();  //程序开始的界面选择

private:
	

};

// 全局变量
vector<Vehicle_information*>   Vehicle;  //车辆信息的向量
vector<Personnel_information*> Personnel; //人员信息的向量

/**
* 函数功能：在程序开始前加载数据
*/
Intrt::Intrt()
{
	Input_vehicle_information(Vehicle);     // 录入车辆信息
	Input_personnel_information(Personnel); // 录入人员信息
	// 检查信息是否完整
	for (unsigned int i = 0; i < Vehicle.size(); ++i)
	{
		cout << "key:\t" << Vehicle[i]->key << endl;
		cout << "speed:\t" << Vehicle[i]->speed << endl;
		cout << "acceleration:\t" << Vehicle[i]->acceleration << endl;
		cout << "conductor:\t" << Vehicle[i]->conductor << endl;
		cout << "distance:\t" << Vehicle[i]->distance << endl;
	}
	for (unsigned int j = 0; j < Personnel.size(); ++j)
	{
		cout << "age:\t" << Personnel[j]->age << endl;
		cout << "auto_age:\t" << Personnel[j]->auto_age << endl;
		cout << " response_time:\t" << Personnel[j]->response_time << endl;
		cout << "reaction_coefficient:\t" << Personnel[j]->reaction_coefficient << endl;
	}
}

/**
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
	case '1':
		// GHR模型的实现
		break;
	default:
		exit(-1);
		break;
	}
	
}
