#pragma once
#include<stdio.h>
#include<string.h>
#include<time.h>
#include<graphics.h>//easyX ͼ�ο�
#include<conio.h>//����_getch ��������
#define WEIGHT 480  //������Ⱥ͸߶�
#define HEIGHT 700
#define BULLET_NUM 15   //�ӵ�����
#define ENEMY_NUM 10    //�л�����
//��������

bool Timer(int ms, int id);//��ʱ��

void Loadimg(void);//����ͼƬ

void Drawimg(void);//����ͼƬ

void planeOr(void);//��ʼ���ɻ�����

void PlayerMove(int speed);//��ɫ�ƶ�

void createBullet();//�����ӵ�����

void BulletMove(int speed);//�ӵ��ƶ�

void enemyHp(int i);//��ʶ���л�Ѫ��������

void createEnemy();//�����л�

void enemyMove(int speed);//�л��ƶ�

void hitPlane();//��ɻ�

