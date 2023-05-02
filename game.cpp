#include "game_function.h"

int main(void)
{
	initgraph(WEIGHT, HEIGHT);// SHOWCONSOLE显示控制台窗口
	HWND graph = GetHWnd();
	SetWindowText(graph, "飞机大战(简易版)");
	planeOr();//初始化属性    &&加载图片
	BeginBatchDraw();//双缓冲绘图
	while (1)
	{
		Drawimg();//绘制图片
		FlushBatchDraw();
		PlayerMove(3);//玩家移动
		BulletMove(10);//子弹移动
		if (Timer(1000,0))
		{
		    createEnemy();//创建敌机 
		}
		if (Timer(10, 2))
		{
			enemyMove(1);//敌机运动

		}
		hitPlane();//打飞机
	}
	EndBatchDraw();
	getchar();
	return 0;
}