#include "game_function.h"

int main(void)
{
	initgraph(WEIGHT, HEIGHT);// SHOWCONSOLE��ʾ����̨����
	HWND graph = GetHWnd();
	SetWindowText(graph, "�ɻ���ս(���װ�)");
	planeOr();//��ʼ������    &&����ͼƬ
	BeginBatchDraw();//˫�����ͼ
	while (1)
	{
		Drawimg();//����ͼƬ
		FlushBatchDraw();
		PlayerMove(3);//����ƶ�
		BulletMove(10);//�ӵ��ƶ�
		if (Timer(1000,0))
		{
		    createEnemy();//�����л� 
		}
		if (Timer(10, 2))
		{
			enemyMove(1);//�л��˶�

		}
		hitPlane();//��ɻ�
	}
	EndBatchDraw();
	getchar();
	return 0;
}