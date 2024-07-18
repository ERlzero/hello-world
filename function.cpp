#include"game_function.h"
IMAGE img_bk;
IMAGE img_pl;
IMAGE img_bull;
IMAGE img_enemy[2];
//enum My
//{
//	WEIGHT=480,//x
//	HEIGHT=700,//y
//	BULLET_NUM=15
//};
enum My
{
	BIG,
	SMALL
};

struct Plane//����
{
	int x;
	int y;
	bool live;//�Ƿ���
	int width;
	int height;
	int hp;
	int type;//�л������� big/small

}player,bull[BULLET_NUM],enemy[ENEMY_NUM],ebull[BULLET_NUM][BULLET_NUM];

//��ʶ���л�Ѫ��������
void enemyHp(int i)
{
	int flag = rand() % 10;
	if (flag >= 0 && flag <= 2)
	{
		enemy[i].type = BIG;
		enemy[i].hp = 3;
		enemy[i].width = 69;
		enemy[i].height = 99;
	}
	else
	{
		enemy[i].type = SMALL;
		enemy[i].hp = 1;
		enemy[i].width = 57;
		enemy[i].height = 43;

	}

}


//��ʼ������
void planeOr(void)
{
	//��ʼ����ҷɻ�
	Loadimg();
	player.x = WEIGHT-280;
	player.y = HEIGHT-100;
	player.live = true;
	//��ʼ���ӵ�
	for (int i = 0; i < BULLET_NUM; i++)
	{
		bull[i].x = 0;
		bull[i].y = 0;
		bull[i].live= false;
		
	}
	//��ʼ���л�
	for (int  i = 0; i < ENEMY_NUM; i++)
	{
		enemy[i].live = false;
		enemyHp(i);//�л�Ѫ�� ����
	}
	

}

//����ͼƬ
void Loadimg()//IMAGE Img_Bk, IMAGE Img_Pl
{


	//���ر���
	loadimage(&img_bk, "F:/vs/repos/game/Image/background.png");
	//������ҷɻ�
	loadimage(&img_pl, "F:/vs/repos/game/Image/me1.png");
	//�����ӵ�
	loadimage(&img_bull, "F:/vs/repos/game/Image/bullet1.png");
	//���صл�ͼƬ ���ֵл� 1 2
    loadimage(&img_enemy[0], "F:/vs/repos/game/Image/enemy1.png");//С
    loadimage(&img_enemy[1], "F:/vs/repos/game/Image/enemy2.png");//��

}


//png ͸����ͼ���ƺ���
void drawAlpha(IMAGE* picture, int  picture_x, int picture_y) //xΪ����ͼƬ��X���꣬yΪY����
{
	// ������ʼ��
	DWORD* dst = GetImageBuffer();    // GetImageBuffer()���������ڻ�ȡ��ͼ�豸���Դ�ָ�룬EASYX�Դ�
	DWORD* draw = GetImageBuffer();
	DWORD* src = GetImageBuffer(picture); //��ȡpicture���Դ�ָ��
	int picture_width = picture->getwidth(); //��ȡpicture�Ŀ�ȣ�EASYX�Դ�
	int picture_height = picture->getheight(); //��ȡpicture�ĸ߶ȣ�EASYX�Դ�
	int graphWidth = getwidth();       //��ȡ��ͼ���Ŀ�ȣ�EASYX�Դ�
	int graphHeight = getheight();     //��ȡ��ͼ���ĸ߶ȣ�EASYX�Դ�
	int dstX = 0;    //���Դ������صĽǱ�

	// ʵ��͸����ͼ ��ʽ�� Cp=��p*FP+(1-��p)*BP �� ��Ҷ˹���������е���ɫ�ĸ��ʼ���
	for (int iy = 0; iy < picture_height; iy++)
	{
		for (int ix = 0; ix < picture_width; ix++)
		{
			int srcX = ix + iy * picture_width; //���Դ������صĽǱ�
			int sa = ((src[srcX] & 0xff000000) >> 24); //0xAArrggbb;AA��͸����
			int sr = ((src[srcX] & 0xff0000) >> 16); //��ȡRGB���R
			int sg = ((src[srcX] & 0xff00) >> 8);   //G
			int sb = src[srcX] & 0xff;              //B
			if (ix >= 0 && ix <= graphWidth && iy >= 0 && iy <= graphHeight && dstX <= graphWidth * graphHeight)
			{
				if ((ix + picture_x) >= 0 && (ix + picture_x) <= graphWidth)	//��ֹ���߽��ѭ����ʾ
				{
					dstX = (ix + picture_x) + (iy + picture_y) * graphWidth; //���Դ������صĽǱ�
					int dr = ((dst[dstX] & 0xff0000) >> 16);
					int dg = ((dst[dstX] & 0xff00) >> 8);
					int db = dst[dstX] & 0xff;
					draw[dstX] = ((sr * sa / 255 + dr * (255 - sa) / 255) << 16)  //��ʽ�� Cp=��p*FP+(1-��p)*BP  �� ��p=sa/255 , FP=sr , BP=dr
						| ((sg * sa / 255 + dg * (255 - sa) / 255) << 8)         //��p=sa/255 , FP=sg , BP=dg
						| (sb * sa / 255 + db * (255 - sa) / 255);              //��p=sa/255 , FP=sb , BP=db
				}
			}
		}
	}
}


//����ͼƬ  ����drawAlpha����
void Drawimg()
{
	//���Ʊ���
	drawAlpha(&img_bk, 0, 0);

	//������ҷɻ�
	drawAlpha(&img_pl, player.x, player.y);

	//�����ӵ�
	for (int i = 0; i < BULLET_NUM; i++)
	{
		if (bull[i].live)
		{
			//�����ӵ�
			drawAlpha(&img_bull, bull[i].x, bull[i].y);
		}
		
	}
	for (int i = 0; i < BULLET_NUM; i++) 
	{
		for (int j = 0; j < BULLET_NUM; j++) 
		{
			if(ebull[i][j].live)
			{
			   //���Ƶл��ӵ�
				drawAlpha(&img_bull, ebull[i][j].x, ebull[i][j].y);
			}
		}
	}
	//���Ƶл�
	for (int i = 0; i < ENEMY_NUM; i++)
	{
		if (enemy[i].live)
		{
			if (enemy[i].type == BIG)
			{
				drawAlpha(&img_enemy[1], enemy[i].x, enemy[i].y);
			}
			else
			{
				drawAlpha(&img_enemy[0], enemy[i].x, enemy[i].y);
			}
		}
	}
}


//��ʱ��
bool Timer(int ms, int id)
{
	static DWORD t[10];
	if (clock() - t[id] > ms)
	{
		t[id] = clock();
		return true;
	}
	return false;
}

//�����л��ӵ�
void ceBullet() {
	for (int i = 0; i < BULLET_NUM; i++) {
		for (int j = 0; j < BULLET_NUM; j++)
        {
		  if (!ebull[i][j].live) 
		  {
			ebull[i][j].x = enemy[i].x + enemy[i].width / 2;
			ebull[i][j].y = enemy[i].y + enemy[i].height / 2;
			ebull[i][j].live = true;
			
		  }
        }
	}
} 

//�����ӵ����� �����ӵ�
void createBullet()
{
	for (int i = 0; i < BULLET_NUM; i++)
	{
		if (!bull[i].live)
		{
			bull[i].x = player.x+50;
			bull[i].y = player.y-7;
			bull[i].live = true;
			break;
		}
	}
}

//�л��ӵ��ƶ�
void eBulletMove(int speed) {
	for (int i = 0; i < BULLET_NUM; i++) 
	{
		for (int j = 0; j < BULLET_NUM; j++) 
		{
			if (ebull[i][j].live) 
			{
				ebull[i][j].y += speed;
				if (ebull[i][j].y > HEIGHT) 
				{
					ebull[i][j].live = false;
				}
			}
		}
	}
}
//�ӵ��ƶ�
void BulletMove(int speed)
{
	for (int i = 0; i < BULLET_NUM; i++)
	{
		if (bull[i].live)
		{
			bull[i].y -= speed;
			if (bull[i].y < 0)
			{
				bull[i].live = false;
			}
		}
	}
}

//����ƶ�
void PlayerMove(int speed)
{
#if 0
	if (_kbhit())//����Ƿ��м��̰���
	{
		char move = _getch();
		switch (move)
		{
		case'w':
		case'W':
			player.y -= speed;
			break;

		case 's':
		case 'S':
			player.y += speed;
			break;

		case'a':
		case'A':
			player.x -= speed;
			break;

		case'd':
		case'D':
			player.x += speed;
			break;

		default:
			break;
		}
	}
#elif 1
	//2,ʹ��windows������ȡ�������� GetAsyncKeyState
	if (GetAsyncKeyState(VK_UP) || GetAsyncKeyState('W'))//�����ĸ�ô�д�������ⲻ��
	{
		if (player.y > 0)
		{
			player.y -= speed;
		}
	}
	if (GetAsyncKeyState(VK_DOWN) || GetAsyncKeyState('S'))
	{
		if (player.y + 100 < 700)
		{
			player.y += speed;
		}
	}
	if (GetAsyncKeyState(VK_LEFT) || GetAsyncKeyState('A'))
	{
		if (player.x + 51 > 0)
		{
			player.x -= speed;
		}
	}
	if (GetAsyncKeyState(VK_RIGHT) || GetAsyncKeyState('D'))
	{
		if (player.x + 51 < 480)
		{
			player.x += speed;
		}
	}
#endif
	//�����ӵ�
	// Timer()--ʱ���ӳ� ��ֹ�ӵ�һ����  ʹÿ�η���һ���ӵ�
	if (GetAsyncKeyState(VK_SPACE) && Timer(100, 1))
	{
		//����һ���ӵ�
		createBullet();
	}
}

//�����л�
void createEnemy()
{
	for (int i = 0; i < ENEMY_NUM; i++)
	{
		if (!enemy[i].live)
		{
			enemy[i].live = true;
			enemy[i].x = rand() % (WEIGHT - 60);
			enemy[i].y = 0;
			enemyHp(i);
			//if (enemy[i].type == BIG)//�ظ�Ѫ�� ʹ�л����޲���
			//{
			//	enemy[i].hp = 3;
			//	enemy[i].live = true;
			//}
			//else
			//{
			//	enemy[i].hp = 1;
			//	enemy[i].hp = true;
			//}
			break;
		}
		if (Timer(10, 1)) {
			ceBullet();
		}
		
	}
}

//�л��ƶ�
void enemyMove(int speed)
{
	for (int  i = 0; i < ENEMY_NUM; i++)
	{
		if (enemy[i].live)
		{
			enemy[i].y += speed;
			if (enemy[i].y > HEIGHT)
			{
				enemy[i].live = false;//ʹ�л�����
			}
		}
	}
	eBulletMove(1);
}


//�ӵ���ɻ�
void hitPlane()
{
	for (int i = 0; i < ENEMY_NUM; i++)
	{
		if (!enemy[i].live)
			continue;
		for (int j = 0; j < BULLET_NUM; j++)
		{
			if (!bull[j].live)
				continue;
			if (bull[j].x > enemy[i].x && bull[j].x<enemy[i].x + enemy[i].width
				&& bull[j].y>enemy[i].y && bull[j].y < enemy[i].y + enemy[i].height)
			{
				bull[j].live = false;
				enemy[i].hp--;
			}
		}
		if (enemy[i].hp <= 0)
		{
			enemy[i].live = false;
		}
	}
}






