#pragma once
#include<iostream>
#include<fstream>
#include<iomanip>
#include<cmath>
#include <math.h>
using namespace std;
int input();
int change();
int out();
struct Vehicle_information_2
{
	float speed;                    // 车速（m/s）
	float acceleration;             // 车辆原本加速度（m/s^2）
	float newacceleration;          // 车辆改变的加速度 (m/s^2)
	float conductor;                // 车辆长度（m）
	float distance;                 // 距离前车的距离（m）(车头之间)
	float width;                    // 车辆宽度 （m）
	int TTC;                        // 实际车辆碰撞时间(s)
	int TTCest;                     // 驾驶人估计的车辆碰撞时间(s)
	float Dd;                       // 驾驶人察觉到跟驰距离变化所行驶过的距离(m)
	float Dp;                       // 驾驶人期望跟驰距离(m)
	float Tp;                       // 车头时距(s)（前后车车头间距除以后车车速）
	float T;                        // 驾驶人反应时间(s/ms)
	float max;                      // 最大心理安全距离(m)
	float min;                      // 最小心理安全距离(m)
}n[10];
//文件的数据采集
int input()
{
	cout << "                                                           修改前的数据" << endl;
	ifstream fcin("The data center\\car.txt");                     //打开文件
	char txt[20][20];
	if (fcin.fail())
	{
		cout << "error opening file\n";
		return 0;
	}
	for (int row1 = 0; row1 < 11; row1++)                                 //表示行
	{
		for (int column = 0; column < 8; column++)                      //表示列
		{
			cout.setf(ios::left);                                //设置左对齐
			cout.width(19);                                      //设置宽度为7，不足用空格补齐
			fcin >> txt[row1 + column];
			cout << txt[row1 + column] << "  ";
			cout.fill(' ');                                      //设置填充，缺省为空格
		}
		cout << endl;
	}
	for (int i = 0; i < 10; i++)                                      //表示车辆
	{
		float   data1 = atof(txt[10]);
		float   data2 = atof(txt[11]);                             //将char型数据转换成float型数据
		float	data3 = atof(txt[12]);
		float	data4 = atof(txt[13]);
		float	data5 = atof(txt[14]);
		float	data6 = atof(txt[15]);
		float  	data7 = atof(txt[16]);
		float	data8 = atof(txt[17]);
		n[i].speed = data1;
		n[i].acceleration = data2;
		n[i].conductor = data3;
		n[i].distance = data4;
		n[i].width = data5;
		n[i].T = data6;
		n[i].max = data7;
		n[i].min = data8;
	}
	return 0;
}
//文件的数据改变
int change()
{
	int choise, i = 1;
	cout << "是否修改数据？（1/0）  ";
	cin >> choise;
	while (choise != 1 && choise != 0)
	{
		cout << "输入错误，请重新输入（1/0）";
		cin >> choise;
	}
	if (choise == 0)
	{
		return 0;
	}
	else
	{
		do
		{
			cout << "请输入想要改变的车辆序号（1-10）" << endl;
			cout << "输入其他数字退出" << endl;
			cin >> i;
			if (i < 1 || i>10)
			{
				cout << "退出修改" << endl;
			}
			else
			{
				cout << "请输入第" << i << "辆车的数据" << endl;
				cout << "请输入车速";
				cin >> n[i - 1].speed;
				while (n[i - 1].speed < 0)
				{
					cout << "数据错误！请重新输入";
					cin >> n[i - 1].speed;
				}
				cout << "请输入加速度";
				cin >> n[i - 1].acceleration;
				while (n[i - 1].acceleration < 0)
				{
					cout << "数据错误！请重新输入";
					cin >> n[i - 1].acceleration;
				}
				cout << "请输入车辆长度";
				cin >> n[i - 1].conductor;
				while (n[i - 1].conductor < 0)
				{
					cout << "数据错误！请重新输入";
					cin >> n[i - 1].conductor;
				}
				cout << "请输入距离前车的距离";
				cin >> n[i - 1].distance;
				while (n[i - 1].distance < 0)
				{
					cout << "数据错误！请重新输入";
					cin >> n[i - 1].distance;
				}
				cout << "请输入车辆宽度";
				cin >> n[i - 1].width;
				while (n[i - 1].width < 0)
				{
					cout << "数据错误！请重新输入";
					cin >> n[i - 1].width;
				}
				cout << "请输入驾驶人反应时间";
				cin >> n[i - 1].T;
				while (n[i - 1].T < 0)
				{
					cout << "数据错误！请重新输入";
					cin >> n[i - 1].T;
				}
				cout << "请输入驾驶人认为的最大心理安全距离";
				cin >> n[i - 1].max;
				while (n[i - 1].max < 0)
				{
					cout << "数据错误！请重新输入";
					cin >> n[i - 1].max;
				}
				cout << "请输入驾驶人认为的最小心理安全距离";
				cin >> n[i - 1].min;
				while (n[i - 1].min < 0)
				{
					cout << "数据错误！请重新输入";
					cin >> n[i - 1].min;
				}
			}
		} while (i != 0);
	}
	return 0;
}
int out()
{
	cout << "                                                           修改后的数据" << endl;
	cout << "speed(m/s)" << "          " << "acceleration(m/s^2)" << "  " << "conductor(m)" << "          " << "distance(m)" << "          " << "width(m)" << "             " << "T(s)" << "                 " << "max(m)" << "               " << "min(m)" << endl;

	for (int i = 0; i < 10; i++)
	{
		cout.setf(ios::left);                                //设置左对齐
		cout.width(19);                                      //设置宽度为7，不足用空格补齐
		cout << std::left << setw(19) << n[i].speed << " " << std::left << setw(19) << n[i].acceleration << "  " << std::left << setw(21) << n[i].conductor << " " << std::left << setw(21) << n[i].distance << std::left << setw(21) << n[i].width << std::left << setw(21) << n[i].T << std::left << setw(21) << n[i].max << std::left << setw(19) << n[i].min << endl;
		cout.fill(' ');                                      //设置填充，缺省为空格
	}
	return 0;
}
void maining()
{
	int d = 6 * 10 ^ (-4);   // 可视角变化阈值（△v/△x^2）
	int e = 1.04;        // 模型待标定参数
	int f = 0.72;        // 模型待标定参数
	int c = 1;           // 模型待标定参数（未确定）
	int b = 0;           // 模型待标定参数（未确定）
	int l = 0;           // 加速度随机误差（未确定）
	int g = 0.1;         // 驾驶人对前导车视觉角变化的感知阈值	
	input();
	change();
	out();
	cout << "                                   从第二辆车到第十辆车的行驶情况：" << endl;
	for (int i = 1; i < 10; i++)
	{
		cout << "第 " << i + 1 << " 辆 车 的 运 行 情 况 为 ：";
		if (n[i].distance<n[i].min || n[i].distance>n[i].max)           //实际车距不符合心理安全距离
		{
			n[i].Tp = n[i].distance / n[i].speed;
			n[i].Dp = n[i].Tp * (n[i].speed + n[i].acceleration * n[i].Tp);
			n[i].Dd = n[i - 1].width / tan(180 * (1 + g) * atan(n[i - 1].width / n[i].Dp));
			n[i].TTC = n[i].Dd / (n[i].T * n[i - 1].acceleration);
			n[i].TTCest = e * n[i].TTC ^ f;
			n[i].newacceleration = c * n[i].TTCest + l + b;
			if (n[i].newacceleration < 0)
				n[i].newacceleration = -n[i].newacceleration;
			else
				n[i].newacceleration = n[i].newacceleration;
			if (n[i].distance < n[i].min)                                   //实际车距小于最小心理安全距离
			{
				n[i].newacceleration = -n[i].newacceleration;               //车辆做减速运动
				cout << "实 际 车 距 小 于 最 小 心 理 安 全 距 离 , 车 辆 做 加 速 度 为 " << setiosflags(ios::fixed) << setprecision(2) << n[i].newacceleration << "m/s^2 的 减 速 运 动 。" << endl;
			}
			else                                                              //实际车距大于最大心理安全距离
			{
				n[i].newacceleration = n[i].newacceleration;               //车辆做加速运动
				cout << "实 际 车 距 大 于 最 大 心 理 安 全 距 离 , 车 辆 做 加 速 度 为 " << setiosflags(ios::fixed) << setprecision(2) << n[i].newacceleration << "m/s^2 的 加 速 运 动 。" << endl;
			}
		}
		else                                                                  //实际车距符合心理安全距离
		{
			cout << "车 俩 保 持 原 有 速 度 行 驶 ， 加 速 度 为 零 。" << endl;
		}
	}
}
