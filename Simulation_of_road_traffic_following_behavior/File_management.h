/*************************************************

Copyright:于文凯 马丽千

Author:于文凯 马丽千

Date:2020-05-25

Description:本程序的文件管理

**************************************************/
#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
using namespace std;

const int MaxCharVeh = 60; // 车辆文件的第一行数据
const int MaxCharPer = 70; // 人员文件的第一行数据

/**
* 函数功能：录入车辆信息
*/
void Input_vehicle_information(vector<Vehicle_information*> &Veh)
{
	fstream fir;                    // 文件的创建
	char temp[MaxCharVeh];          // 定义获取第一行数据
	fir.open("The data center\\vehicle.txt", ios::in);
	if (fir.fail()) exit(-1);
	fir.getline(temp, MaxCharVeh);  // 将从第二行开始
	while (!fir.eof())
	{
		struct Vehicle_information* veh = new struct Vehicle_information;
		fir >> veh->key;
		fir >> veh->speed;
		fir >> veh->acceleration;
		fir >> veh->conductor;
		fir >> veh->distance;
		Veh.push_back(veh);
	}
	fir.close();
}

/**
* 函数功能：录入人员信息
*/
void Input_personnel_information(vector<Personnel_information*> &Per)
{
	fstream fir;                    // 文件的创建
	char temp[MaxCharPer];          // 定义获取第一行数据
	fir.open("The data center\\personnel.txt", ios::in);
	if (fir.fail()) exit(-1);
	fir.getline(temp, MaxCharPer);  // 将从第二行开始
	while (!fir.eof())
	{
		struct Personnel_information* per = new struct Personnel_information;
		fir >> per->key;
		fir >> per->age;
		fir >> per->auto_age;
		fir >> per->response_time;
		fir >> per->reaction_coefficient;
		Per.push_back(per);
	}
	fir.close();
}
/**
* 函数功能：录入GHR模型参数信息
*/
void Input_GHR_model_parameter_information(struct GHR_model_parameters GHR_Para[], int n)
{
	string lines;
	fstream fir;                    // 文件的创建
	fir.open("The data center\\GHR parameters.txt", ios::in);
	if (fir.fail()) exit(-1);
	/* 录入信息开始 */
	getline(fir, lines);
	getline(fir, lines);
	for (int i = 0; i < 6; ++i)
	{
		fir >> lines;
		fir >> lines;
		switch (i)
		{
		case 0:
			for (int i = 0; i < 3; ++i)
				fir >> GHR_Para[0].Dec_Pha[i];
			break;
		case 1:
			for (int i = 0; i < 3; ++i)
				fir >> GHR_Para[0].Sta_Pha[i];
			break;
		case 2:
			for (int i = 0; i < 3; ++i)
				fir >> GHR_Para[0].Sce_Pha[i];
			break;
		case 3:
			fir >> lines;
			fir >> lines;
			fir >> lines;
			break;
		case 4:
			for (int i = 0; i < 3; ++i)
				fir >> GHR_Para[1].Dec_Pha[i];
			break;
		case 5:
			for (int i = 0; i < 3; ++i)
				fir >> GHR_Para[1].Sce_Pha[i];
		default:
			break;
		}
	}
	/* 录入信息结束 */
	fir.close();
}
