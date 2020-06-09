/*************************************************

Copyright:于文凯 马丽千 王泳清

Author:于文凯 马丽千 王泳清

Date:2020-05-24

Description:主函数

**************************************************/

#include <windows.h>
#include "Interface_management.h"

/**
*  开始程序
*/
int main()
{
    // 调整界面
    HWND hwnd = GetForegroundWindow();
    int cx = GetSystemMetrics(SM_CXSCREEN); /* 屏幕宽度 像素 */
    int cy = GetSystemMetrics(SM_CYSCREEN); /* 屏幕高度 像素 */
    LONG l_WinStyle = GetWindowLong(hwnd, GWL_STYLE); /* 获取窗口信息 */
    /* 设置窗口信息 最大化 取消标题栏及边框 */
    SetWindowLong(hwnd, GWL_STYLE, (l_WinStyle | WS_POPUP | WS_MAXIMIZE)
        & ~WS_CAPTION & ~WS_THICKFRAME & ~WS_BORDER);
    SetWindowPos(hwnd, HWND_TOP, 0, 0, cx, cy, 0);

	// 开始程序
	Intrt start;
	return 0;
}
