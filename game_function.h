#pragma once
#include<stdio.h>
#include<string.h>
#include<time.h>
#include<graphics.h>//easyX 图形库
#include<conio.h>//函数_getch 键盘输入
#define WEIGHT 480  //创建宽度和高度
#define HEIGHT 700
#define BULLET_NUM 15   //子弹数量
#define ENEMY_NUM 10    //敌机数量
//函数声明

bool Timer(int ms, int id);//计时器

void Loadimg(void);//加载图片

void Drawimg(void);//绘制图片

void planeOr(void);//初始化飞机属性

void PlayerMove(int speed);//角色移动

void createBullet();//创建子弹属性

void BulletMove(int speed);//子弹移动

void enemyHp(int i);//初识化敌机血量，宽，高

void createEnemy();//产生敌机

void enemyMove(int speed);//敌机移动

void hitPlane();//打飞机

