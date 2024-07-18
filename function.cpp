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

struct Plane//属性
{
	int x;
	int y;
	bool live;//是否存活
	int width;
	int height;
	int hp;
	int type;//敌机的类型 big/small

}player,bull[BULLET_NUM],enemy[ENEMY_NUM],ebull[BULLET_NUM][BULLET_NUM];

//初识化敌机血量，宽，高
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


//初始化属性
void planeOr(void)
{
	//初始化玩家飞机
	Loadimg();
	player.x = WEIGHT-280;
	player.y = HEIGHT-100;
	player.live = true;
	//初始化子弹
	for (int i = 0; i < BULLET_NUM; i++)
	{
		bull[i].x = 0;
		bull[i].y = 0;
		bull[i].live= false;
		
	}
	//初始化敌机
	for (int  i = 0; i < ENEMY_NUM; i++)
	{
		enemy[i].live = false;
		enemyHp(i);//敌机血量 宽，高
	}
	

}

//加载图片
void Loadimg()//IMAGE Img_Bk, IMAGE Img_Pl
{


	//加载背景
	loadimage(&img_bk, "F:/vs/repos/game/Image/background.png");
	//加载玩家飞机
	loadimage(&img_pl, "F:/vs/repos/game/Image/me1.png");
	//加载子弹
	loadimage(&img_bull, "F:/vs/repos/game/Image/bullet1.png");
	//加载敌机图片 两种敌机 1 2
    loadimage(&img_enemy[0], "F:/vs/repos/game/Image/enemy1.png");//小
    loadimage(&img_enemy[1], "F:/vs/repos/game/Image/enemy2.png");//大

}


//png 透明贴图绘制函数
void drawAlpha(IMAGE* picture, int  picture_x, int picture_y) //x为载入图片的X坐标，y为Y坐标
{
	// 变量初始化
	DWORD* dst = GetImageBuffer();    // GetImageBuffer()函数，用于获取绘图设备的显存指针，EASYX自带
	DWORD* draw = GetImageBuffer();
	DWORD* src = GetImageBuffer(picture); //获取picture的显存指针
	int picture_width = picture->getwidth(); //获取picture的宽度，EASYX自带
	int picture_height = picture->getheight(); //获取picture的高度，EASYX自带
	int graphWidth = getwidth();       //获取绘图区的宽度，EASYX自带
	int graphHeight = getheight();     //获取绘图区的高度，EASYX自带
	int dstX = 0;    //在显存里像素的角标

	// 实现透明贴图 公式： Cp=αp*FP+(1-αp)*BP ， 贝叶斯定理来进行点颜色的概率计算
	for (int iy = 0; iy < picture_height; iy++)
	{
		for (int ix = 0; ix < picture_width; ix++)
		{
			int srcX = ix + iy * picture_width; //在显存里像素的角标
			int sa = ((src[srcX] & 0xff000000) >> 24); //0xAArrggbb;AA是透明度
			int sr = ((src[srcX] & 0xff0000) >> 16); //获取RGB里的R
			int sg = ((src[srcX] & 0xff00) >> 8);   //G
			int sb = src[srcX] & 0xff;              //B
			if (ix >= 0 && ix <= graphWidth && iy >= 0 && iy <= graphHeight && dstX <= graphWidth * graphHeight)
			{
				if ((ix + picture_x) >= 0 && (ix + picture_x) <= graphWidth)	//防止出边界后循环显示
				{
					dstX = (ix + picture_x) + (iy + picture_y) * graphWidth; //在显存里像素的角标
					int dr = ((dst[dstX] & 0xff0000) >> 16);
					int dg = ((dst[dstX] & 0xff00) >> 8);
					int db = dst[dstX] & 0xff;
					draw[dstX] = ((sr * sa / 255 + dr * (255 - sa) / 255) << 16)  //公式： Cp=αp*FP+(1-αp)*BP  ； αp=sa/255 , FP=sr , BP=dr
						| ((sg * sa / 255 + dg * (255 - sa) / 255) << 8)         //αp=sa/255 , FP=sg , BP=dg
						| (sb * sa / 255 + db * (255 - sa) / 255);              //αp=sa/255 , FP=sb , BP=db
				}
			}
		}
	}
}


//绘制图片  调用drawAlpha函数
void Drawimg()
{
	//绘制背景
	drawAlpha(&img_bk, 0, 0);

	//绘制玩家飞机
	drawAlpha(&img_pl, player.x, player.y);

	//绘制子弹
	for (int i = 0; i < BULLET_NUM; i++)
	{
		if (bull[i].live)
		{
			//绘制子弹
			drawAlpha(&img_bull, bull[i].x, bull[i].y);
		}
		
	}
	for (int i = 0; i < BULLET_NUM; i++) 
	{
		for (int j = 0; j < BULLET_NUM; j++) 
		{
			if(ebull[i][j].live)
			{
			   //绘制敌机子弹
				drawAlpha(&img_bull, ebull[i][j].x, ebull[i][j].y);
			}
		}
	}
	//绘制敌机
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


//计时器
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

//创建敌机子弹
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

//创建子弹属性 产生子弹
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

//敌机子弹移动
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
//子弹移动
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

//玩家移动
void PlayerMove(int speed)
{
#if 0
	if (_kbhit())//检测是否有键盘按下
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
	//2,使用windows函数获取键盘输入 GetAsyncKeyState
	if (GetAsyncKeyState(VK_UP) || GetAsyncKeyState('W'))//检测字母用大写，否则检测不到
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
	//创建子弹
	// Timer()--时间延迟 防止子弹一起发射  使每次发射一颗子弹
	if (GetAsyncKeyState(VK_SPACE) && Timer(100, 1))
	{
		//创建一个子弹
		createBullet();
	}
}

//产生敌机
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
			//if (enemy[i].type == BIG)//回复血量 使敌机无限产生
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

//敌机移动
void enemyMove(int speed)
{
	for (int  i = 0; i < ENEMY_NUM; i++)
	{
		if (enemy[i].live)
		{
			enemy[i].y += speed;
			if (enemy[i].y > HEIGHT)
			{
				enemy[i].live = false;//使敌机死亡
			}
		}
	}
	eBulletMove(1);
}


//子弹打飞机
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






