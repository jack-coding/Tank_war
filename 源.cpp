#include<iostream>
#include<windows.h>
#include<conio.h>
#include<time.h>
#include"tank.h"
#include<mmsystem.h>//�������������ͷ�ļ�
#pragma comment (lib,"winmm.lib")//���߱�����,����winmm.lib���ļ�

int main(void)
{
	
	menu();//��ӡ��Ϸ�˵�

	inimap(map);//��ʼ����ͼ

	int result=play();
	
	gameover_Scene(result);
	return 0;
}

/*ͨ����ά���齨���뻭������Ķ�Ӧ��ϵ,�ٸ��ݶ�ά����Ԫ�ص�ֵ�Լ���Ӧ����������Ӧ��ͼ*/
void menu()
{
	cout << "���ڼ���..." << endl;
	mciSendString(_T("play start.mp3"),0, 0, 0);
	initgraph(SCREEN_LENGTH,SCREEN_WIDTH+THICKNESS);//���廭����С
	IMAGE logo_img;
	loadimage(&logo_img, _T("logo.bmp"), 433, 147);//����ͼƬ,(433,137)ΪͼƬ�ֱ���,_T���ڴ����������
	putimage(110, 20, &logo_img);//���ͼƬ
	setlinecolor(RED);//���ƾ��α߿���ɫ
	settextcolor(WHITE);//��������ı���ɫ
	settextstyle(25, 0, _T("����"));
	rectangle(230, 200, 310, 240);
	outtextxy(240, 210, _T("˵��"));
	rectangle(350, 200, 430, 240);
	outtextxy(360, 210, _T("��ʼ"));
	MOUSEMSG mouse;//����һ�����������Ϣ�Ľṹ��
	IMAGE illustrate_img;//����illustrate_imgͼƬ����
	loadimage(&illustrate_img, _T("illustrate.jpg"), 300, 300);//����ͼƬillustrate.jpg��illustrate_img��
	int finish = 1;//���ڿ���whileѭ��
	while (finish)
	{
		mouse = GetMouseMsg();//��ȡ������Ϣ;
		switch (mouse.uMsg)
		{
		case WM_MOUSEMOVE://WM_MOUSEMOVEΪ����ƶ���Ϣ
			if ((mouse.x > 230 && mouse.x < 310) && (mouse.y > 200 && mouse.y < 240))//������������"��ʼ"������
			{
				putimage(170, 250, &illustrate_img) ;//���ͼƬ
			}
			else
			{
				setfillcolor(BLACK);
				solidrectangle(170, 250, 460, 560);//�������,�����һ�ź�ɫ���η����串��
			}
			break;
		case WM_LBUTTONDOWN:
			if ((mouse.x > 350 && mouse.x < 430) && (mouse.y > 200 && mouse.y < 240))
			{
				cleardevice();//����ͼ����Ļ
				finish = 0;//ʹѭ������Ϊ��
				break;//��breakֻ���˳�switch-case���
			}
		}
	}
}
void inimap(int b[][width])
{
	int i, j;
	IMAGE img_home, img_wall_1, img_wall_2;//����img_home, img_wall_1, img_wall_2ͼƬ����
	loadimage(&img_home, _T("home.jpg"), 50, 50);//����ͼƬ"home.jpg��illustrate_img��
	loadimage(&img_wall_1, _T("wall2.jpg"), 25, 25);//����ͼƬ"wall2.jpg"��img_wall_1��
	loadimage(&img_wall_2, _T("wall1.jpg"), 25, 25);//����ͼƬ"wall1.jpg"��img_wall_2��
	mciSendString(_T("pause start.mp3"), 0, 0, 0);
	for (i = 0; i<length; i++)//���ݶ�ά����Ԫ�ص�ֵ�Լ���Ӧ����������Ӧ��ͼ
	{
		for (j = 0; j < width; j++)
		{
			if (b[i][j] == 1)
			{
				putimage(25 * j, 25 * i+THICKNESS, &img_wall_1);
			}
			if (b[i][j] == 2)
			{
				putimage(25 * j, 25 * i + THICKNESS, &img_wall_2);
			}
			if (b[i][j] == 3)
			{
				putimage(25 * j, 25 * i + THICKNESS, &img_home);//��Ϊ��ӥͼƬֻ��һ���ҷֱ���Ϊ50*50,ռ4��С����,�������ҵ���ά����Ԫ��ֵΪ3�ĵ�һ��Ԫ�غ�,�ٽ�ͼƬ���,Ȼ�����ĸ�Ԫ��ֵΪ3��Ԫ����Ϊ4;
				b[i][j] = 4;
				b[i + 1][j + 1] = 4;
				b[i + 1][j] = 4;
				b[i][j + 1] = 4;
			}
		}
	}
	setfillcolor(WHITE);
	solidrectangle(0,THICKNESS-1,SCREEN_LENGTH,THICKNESS-1);
}
/*ͨ���ҷ�̹�˵�λ���������з�̹�˵ķ���*/
DIRECTION enemy_tank_direction(tank_s *tank, int x, int y)
{
	int r;//���ڳнӲ����������
	r = rand() % 100;
	if (tank->x > x)//�ҷ�̹���ڵз�̹�����
	{
		if (tank->y > y)//����ҷ�̹���ڵз�̹�����Ϸ�
		{
			if (r <= 50)
			{
				return up;
			}
			else
			{
				return left1;
			}
		}
		else//����ҷ�̹���ڵз�̹�����·�
		{
			if (r <= 50)
			{
				return down;
			}
			else
			{
				return left1;
			}
		}
	}
	else//�ҷ�̹���ڵз�̹���Ҳ�
	{
		if (tank->y > y)//����ҷ�̹���ڵз�̹�����Ϸ�
		{
			if (r <= 50)
			{
				return up;
			}
			else
			{
				return right1;
			}
		}
		else//����ҷ�̹���ڵз�̹�����·�
		{
			if (r <= 50)
			{
				return down;
			}
			else
			{
				return right1;
			}
		}
	}
}
int bullet_action(bullet_s *bullet,tank_s *enemy_tank) {
	int x, y, x1, y1;
	//�ӵ��ڶ�ά�����е�����
	x = bullet->bullet_x/25;
	y = (bullet->bullet_y-THICKNESS)/25;
	//������һ�λ��Ƶ��ӵ�
	setfillcolor(BLACK);
	solidrectangle(bullet->bullet_x, bullet->bullet_y, bullet->bullet_x + 3, bullet->bullet_y + 3);
	if (bullet->direction == up) {
		bullet->bullet_y -=4;
		x1 = x + 1;
		y1 = y;
	}
	else if (bullet->direction == down) {
		bullet->bullet_y +=4;
		x1 = x + 1;
		y1 = y;
	}
	else if (bullet->direction == left1) {
		bullet->bullet_x -=4;
		x1 = x;
		y1 = y+1;
	} 
	else if (bullet->direction == right1){
		bullet->bullet_x += 4;
		x1 = x;
		y1 = y + 1;
	}
	else {
		return 0;
	}
	if (bullet->bullet_x < 0 || bullet->bullet_x>SCREEN_LENGTH || bullet->bullet_y < THICKNESS || bullet->bullet_y>SCREEN_WIDTH+THICKNESS) {
		bullet->status = 0;
		return 0;
	}
	//��ײ���
	if (map[y][x] == 4 || map[y1][x1] == 4) {//����ӵ������ҷ���ӥ
		if (bullet->origin == enemy_Tank) {
			return 1;
		}
		else {
			bullet->status = 0;
		}
	}
	if ((map[y][x] == 200 || map[y1][x1] == 200)) {//����ӵ������ҷ�̹��
		if (bullet->origin == enemy_Tank) {
			return 1;
		}
		else {
			bullet->status = 0;//���з�̹���ӵ����ез�̹��,���ӵ���ʧ
		}
	}
	if ((map[y][x] >=100 && map[y][x] <100+enemy_num)|| (map[y1][x1] >= 100 && map[y1][x1] <100+enemy_num)) {//����ӵ����ез�̹��
		if (bullet->origin == my_Tank) {
			tank_s *tank = NULL;
			bullet->status = 0;
			if (map[y][x] >= 100 && map[y][x] <100+enemy_num) {
				tank = enemy_tank + (map[y][x] - 100);
			}
			else {
				tank = enemy_tank + (map[y1][x1] - 100);
			}
			tank->live = 0;
			set_prop_map(tank->x, tank->y, 0);
			setfillcolor(BLACK);
			solidrectangle(tank->x * 25, tank->y * 25 + THICKNESS, tank->x * 25 + 50, tank->y * 25 + 50 + THICKNESS);
		}
		else {
			bullet->status = 0;
		}
	}
    if ((map[y][x] == 1)) {//����ӵ����п�����ǽ
		map[y][x] = 0;
		bullet->status = 0;
		setfillcolor(BLACK);
		solidrectangle(x*25, y*25 + THICKNESS, x*25+25, y*25+25 + THICKNESS);
	}
	else if (map[y][x] == 2) {//����ӵ����в�������ǽ
		bullet->status = 0;
	}
	if ((map[y1][x1] == 1)) {//����ӵ����п�����ǽ
		map[y1][x1] = 0;
		bullet->status = 0;
		setfillcolor(BLACK);
		solidrectangle(x1 * 25, y1 * 25 + THICKNESS, x1 * 25 + 25, y1 * 25 + 25 + THICKNESS);
	}
	else if (map[y1][x1] == 2) {//����ӵ����в�������ǽ
		bullet->status = 0;
	}
	//���»����ӵ�
	if (bullet->status == 1) {
		setfillcolor(YELLOW);
		solidrectangle(bullet->bullet_x, bullet->bullet_y, bullet->bullet_x + 3, bullet->bullet_y + 3);
	}
	return 0;
}
void tank_fire(tank_s *tank, bullet_s *bullet, int needsound)
{
	if (bullet->status == 0)
	{
		if(needsound)
		PlaySound(_T("paoji.wav"), NULL, SND_FILENAME | SND_ASYNC);//���ű�������
		if (tank->direction == up)
		{
			bullet->bullet_x = tank->x * 25 + 23;
			bullet->bullet_y = tank->y * 25 - 3 + THICKNESS;
		}
		else if (tank->direction == down)
		{
			bullet->bullet_x = tank->x * 25 + 23;
			bullet->bullet_y = tank->y * 25 + 53 + THICKNESS;
		}
		else if (tank->direction == left1)
		{
			bullet->bullet_x = tank->x * 25 - 3;
			bullet->bullet_y = tank->y * 25 + 23 + THICKNESS;
		}
		else if (tank->direction == right1)
		{
			bullet->bullet_x = tank->x * 25 + 53;
			bullet->bullet_y = tank->y * 25 + 23 + THICKNESS;
		}
		bullet->direction = tank->direction;
		bullet->status = 1;
	}
}
int do_tank_move(tank_s * tank, DIRECTION direction, IMAGE *img, int step)
{
	int new_x, new_y;
	new_x = tank->x;
	new_y = tank->y;
	int old_prop = map[tank->y][tank->x];
	if (step == 1)
	{
		if (direction == up)
		{
			new_y -= 1;
		}
		else if (direction == down)
		{
			new_y += 1;
		}
		else if (direction == left1)
		{
			new_x -= 1;
		}
		else if (direction == right1)
		{
			new_x += 1;
		}
		else
		{
			return 0;//�ƶ�ʧ�ܷ���0
		}
		set_prop_map(tank->x, tank->y, 0);
	}
	setfillcolor(BLACK);
	solidrectangle(tank->x * 25, tank->y * 25+ THICKNESS, tank->x * 25 + 50, tank->y * 25 +50+ THICKNESS);
	if (step)
	{
		set_prop_map(new_x, new_y, old_prop);
		tank->x = new_x;
		tank->y = new_y;
	}
	putimage(tank->x * 25, tank->y * 25 + THICKNESS, img);
	return 1;//�ƶ��ɹ�����1
}
void tank_move(tank_s * tank, DIRECTION direction, IMAGE *img)
{
	switch (direction)
	{
	case left1://�������ǿյ�
		if ((tank->direction == left1) && (tank->x - 1) >= 0 && map[tank->y][tank->x - 1] == 0 && map[tank->y + 1][tank->x - 1] == 0)
		{
			do_tank_move(tank, left1, img, 1);
		}
		else if (tank->direction != left1)
		{
			tank->direction = left1;
			do_tank_move(tank, left1, img, 0);
		}
		break;
	case up://����ϱ��ǿյ�
		if ((tank->direction == up) && (tank->y - 1) >= 0 && map[tank->y - 1][tank->x + 1] == 0 && map[tank->y - 1][tank->x] == 0)
		{
			do_tank_move(tank, up, img, 1);
		}
		else if (tank->direction != up)
		{
			tank->direction = up;
			do_tank_move(tank, up, img, 0);
		}
		break;
	case down://����±��ǿյ�
		if ((tank->direction == down) && (tank->y + 2) <= 25 && map[tank->y + 2][tank->x] == 0 && map[tank->y + 2][tank->x + 1] == 0)
		{
			do_tank_move(tank, down, img, 1);
		}
		else if (tank->direction != down)
		{
			tank->direction = down;
			do_tank_move(tank, down, img, 0);
		}
		break;
	case right1://����ұ��ǿյ�
		if ((tank->direction == right1) && (tank->x + 2) <= 25 && map[tank->y][tank->x + 2] == 0 && map[tank->y + 1][tank->x + 2] == 0)
		{
			do_tank_move(tank, right1, img, 1);
		}
		else if (tank->direction != right1)
		{
			tank->direction = right1;
			do_tank_move(tank, right1, img, 0);
		}
		break;
	}
}
void set_prop_map(int x, int y, int change)
{
	map[y][x] = change;
	map[y + 1][x + 1] = change;
	map[y + 1][x] = change;
	map[y][x + 1] = change;
}
void gameover_Scene(int result) {
	if (result) {
		IMAGE end_img;
		mciSendString(_T("play victory.mp3"), 0, 0, 0);
		loadimage(&end_img, _T("success.jpg"), 433, 248);
		Sleep(6000);
		putimage(125, 220, &end_img);
	}
	else {
		IMAGE end_img;
		loadimage(&end_img, _T("failure.jpg"), 433, 248);
		Sleep(2000);
		putimage(125, 220, &end_img);
	}
	setbkmode(TRANSPARENT);
	settextcolor(YELLOW);
	settextstyle(25, 0, _T("��Բ"));
	outtextxy(218,430,_T("��������˳���Ϸ!"));
	system("pause");//��������ͣ
	closegraph();//�رջ���
}
void num_show(int Num,IMAGE * tank_img) {
	char num[10];
	TCHAR _Tnum[10];
	setbkmode(TRANSPARENT);
	settextcolor(WHITE);
	settextstyle(25, 0, _T("��Բ"));
	outtextxy(10, 10, _T("ʣ��"));
	putimage(65, 10, tank_img);
	outtextxy(100, 10, _T("����:"));
	setfillcolor(BLACK);
	solidrectangle(152, 9, 200, 40);
	sprintf_s(num, sizeof(num),"%d��",Num);//�����ͱ���д��char����
	MultiByteToWideChar(CP_ACP, 0, num, -1, _Tnum, 100);//char����ת����TCHAR����
	outtextxy(152, 10,_Tnum);
}
int play(void)
{
	bullet_s my_bullet;//�����ҷ��ӵ�
	bullet_s enemy_bullet[enemy_num];//����з��ӵ�
	tank_s my_tank;//�����ҷ�tank;
	tank_s enemy_tank[enemy_num];//����з�̹��;
	int enemy_total = 3;
	int times = 1;
	//�趨�ҷ�̹�˵ĳ�����Ϣ
	my_tank.x = 9;
	my_tank.y = 24;
	my_tank.live = 1;//�ҷ�̹�˻���
	my_tank.direction = up;//��ʼ��������
	my_tank.status = my_Tank;
	my_bullet.status = 0;//����������ӵ�
	my_bullet.origin = my_Tank;
	set_prop_map(my_tank.x, my_tank.y, 200);
	//�趨�з�̹�˵ĳ�����Ϣ
	for (int i = 0; i < enemy_num; i++)//ͨ��i��3����,��ȷ���з�̹�˵ĳ���λ��;
	{
		if ((i % 3) == 0)
		{
			enemy_tank[i].x = 0;
		}
		else if ((i % 3) == 1)
		{
			enemy_tank[i].x = 12;
		}
		else
		{
			enemy_tank[i].x = 24;
		}
		enemy_tank[i].y = 0;
		enemy_tank[i].direction = down;//�з�̹�˵ĳ�����������
		enemy_tank[i].live = 1;
		enemy_tank[i].status = enemy_Tank;
		enemy_bullet[i].status = 0;//����з�̹�˲�δ����
		enemy_bullet[i].origin = enemy_Tank;
	}
	//��ʼ�����������
	srand((unsigned)time(NULL));
	//�����ҷ�̹�˵�ͼƬ
	loadimage(&my_tank_img[up], _T("tank_up.jpg"), 50, 50);
	loadimage(&my_tank_img[down], _T("tank_down.jpg"), 50, 50);
	loadimage(&my_tank_img[left1], _T("tank_left.jpg"), 50, 50);
	loadimage(&my_tank_img[right1], _T("tank_right.jpg"), 50, 50);
	//���صз�̹�˵�ͼƬ
	loadimage(&enemy_tank_img[up], _T("enemy_tank_up.jpg"), 50, 50);
	loadimage(&enemy_tank_img[down], _T("enemy_tank_down.jpg"), 50, 50);
	loadimage(&enemy_tank_img[left1], _T("enemy_tank_left.jpg"), 50, 50);
	loadimage(&enemy_tank_img[right1], _T("enemy_tank_right.jpg"), 50, 50);
	loadimage(&enemy_temp_img, _T("enemy_tank_right.jpg"), 30, 30);
	//����������
	PlaySound(_T("background.wav"), NULL, SND_FILENAME | SND_ASYNC);//���ű�������
	putimage(my_tank.x * 25, my_tank.y * 25+THICKNESS, &my_tank_img[up]);//�ҷ�̹�������ǳ�!
	//���Ƶз�̹��,�з�ǰ3��̹�������ǳ�!
	for (int i = 0; i < enemy_total; i++) {
		do_tank_move(&enemy_tank[0], down, &enemy_tank_img[down], 0);
		set_prop_map(enemy_tank[i].x, enemy_tank[i].y, 100+i);
	}
	num_show(enemy_num, &enemy_temp_img);//˵��̹������
	while (1)
	{
		if (times > 0 &&times %1000 == 0 && enemy_total < enemy_num) {
			if (map[enemy_tank[enemy_total].y][enemy_tank[enemy_total].x] != 0|| map[enemy_tank[enemy_total].y][enemy_tank[enemy_total].x+1] != 0|| map[enemy_tank[enemy_total].y+1][enemy_tank[enemy_total].x] != 0|| map[enemy_tank[enemy_total].y+1][enemy_tank[enemy_total].x+1] != 0) {
				for (int i = 0; i <= width - 2; i += 2) {
					if (map[enemy_tank[enemy_total].y][i] == 0) {
						enemy_tank[enemy_total].x = i;
						break;
					}
				}
			}
			set_prop_map(enemy_tank[enemy_total].x, enemy_tank[enemy_total].y, 100 + enemy_total);
			enemy_total++;
		}
		if (times % 200 == 0)//ÿ��2s�ı�һ�η���
		{
			for (int i = 0; i < enemy_total; i++)
			{
				if (enemy_tank[i].live == 0)
					continue;
				if (i % 2 == 0)//ż�������ҷ��ϳ�
				{
					DIRECTION d = enemy_tank_direction(&enemy_tank[i], 12, 24);
					tank_move(&enemy_tank[i], d, &enemy_tank_img[d]);
				}
				else//���������ҷ�̹��
				{
					DIRECTION d = enemy_tank_direction(&enemy_tank[i], my_tank.x, my_tank.y);
					tank_move(&enemy_tank[i], d, &enemy_tank_img[d]);
				}
				tank_fire(&enemy_tank[i], &enemy_bullet[i], 0);
			}
		}
		else if (times % 50 == 0)//ÿ��0.5s�ƶ����з�̹��һ��
		{
			for (int i = 0; i < enemy_total; i++)
			{
				if (enemy_tank[i].live)
					tank_move(&enemy_tank[i], enemy_tank[i].direction, &enemy_tank_img[enemy_tank[i].direction]);
			}
		}
		int ch;
		if (_kbhit())//����м�����,�򷵻�ֵΪtrue,û���򷵻�ֵΪfalse
		{
			ch = _getch();
			switch (ch)
			{
			case 'a'://�������ǿյ�
				tank_move(&my_tank, left1, &my_tank_img[left1]);
				break;
			case 'w'://����ϱ��ǿյ�
				tank_move(&my_tank, up, &my_tank_img[up]);
				break;
			case 's'://����±��ǿյ� 
				tank_move(&my_tank, down, &my_tank_img[down]);
				break;
			case 'd'://����ұ��ǿյ�
				tank_move(&my_tank, right1, &my_tank_img[right1]);
				break;
			case 'p':
				system("pause");
				break;
			case 'j':
				tank_fire(&my_tank, &my_bullet, 1);
				break;
			default:
				break;
			}
		}
		if (my_bullet.status == 1) {
			if (bullet_action(&my_bullet, enemy_tank)) {
				return FAILURE;
			}
		}
		for (int i = 0; i < enemy_total; i++) {
			if (enemy_bullet[i].status == 1) {
				if (bullet_action(&enemy_bullet[i], enemy_tank)) {
					return FAILURE;
				}
			}
		}
		int isWin = 0;
		for (int i = 0; i < enemy_num; i++) {
			if (enemy_tank[i].live == 0) {
				isWin++;
				num_show(enemy_num - isWin, &enemy_temp_img);
			}
		}
		if (isWin == enemy_num) {
			return SUCCESS;
		}
		Sleep(10);
		times++;
	}
}