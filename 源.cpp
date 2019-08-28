#include<iostream>
#include<windows.h>
#include<conio.h>
#include<time.h>
#include"tank.h"
#include<mmsystem.h>//播放音乐所需的头文件
#pragma comment (lib,"winmm.lib")//告诉编译器,加载winmm.lib库文件

int main(void)
{
	
	menu();//打印游戏菜单

	inimap(map);//初始化地图

	int result=play();
	
	gameover_Scene(result);
	return 0;
}

/*通过二维数组建立与画布坐标的对应关系,再根据二维数组元素的值以及相应的坐标贴相应的图*/
void menu()
{
	cout << "正在加载..." << endl;
	mciSendString(_T("play start.mp3"),0, 0, 0);
	initgraph(SCREEN_LENGTH,SCREEN_WIDTH+THICKNESS);//定义画布大小
	IMAGE logo_img;
	loadimage(&logo_img, _T("logo.bmp"), 433, 147);//加载图片,(433,137)为图片分辨率,_T用于处理编码问题
	putimage(110, 20, &logo_img);//输出图片
	setlinecolor(RED);//控制矩形边框颜色
	settextcolor(WHITE);//控制输出文本颜色
	settextstyle(25, 0, _T("宋体"));
	rectangle(230, 200, 310, 240);
	outtextxy(240, 210, _T("说明"));
	rectangle(350, 200, 430, 240);
	outtextxy(360, 210, _T("开始"));
	MOUSEMSG mouse;//定义一个保存鼠标信息的结构体
	IMAGE illustrate_img;//定义illustrate_img图片对象
	loadimage(&illustrate_img, _T("illustrate.jpg"), 300, 300);//加载图片illustrate.jpg到illustrate_img中
	int finish = 1;//用于控制while循环
	while (finish)
	{
		mouse = GetMouseMsg();//获取鼠标的消息;
		switch (mouse.uMsg)
		{
		case WM_MOUSEMOVE://WM_MOUSEMOVE为鼠标移动消息
			if ((mouse.x > 230 && mouse.x < 310) && (mouse.y > 200 && mouse.y < 240))//如果鼠表坐标在"开始"方框内
			{
				putimage(170, 250, &illustrate_img) ;//输出图片
			}
			else
			{
				setfillcolor(BLACK);
				solidrectangle(170, 250, 460, 560);//如果不在,则输出一张黑色矩形方框将其覆盖
			}
			break;
		case WM_LBUTTONDOWN:
			if ((mouse.x > 350 && mouse.x < 430) && (mouse.y > 200 && mouse.y < 240))
			{
				cleardevice();//清理图形屏幕
				finish = 0;//使循环条件为假
				break;//此break只是退出switch-case语句
			}
		}
	}
}
void inimap(int b[][width])
{
	int i, j;
	IMAGE img_home, img_wall_1, img_wall_2;//定义img_home, img_wall_1, img_wall_2图片对象
	loadimage(&img_home, _T("home.jpg"), 50, 50);//加载图片"home.jpg到illustrate_img中
	loadimage(&img_wall_1, _T("wall2.jpg"), 25, 25);//加载图片"wall2.jpg"到img_wall_1中
	loadimage(&img_wall_2, _T("wall1.jpg"), 25, 25);//加载图片"wall1.jpg"到img_wall_2中
	mciSendString(_T("pause start.mp3"), 0, 0, 0);
	for (i = 0; i<length; i++)//根据二维数组元素的值以及相应的坐标贴相应的图
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
				putimage(25 * j, 25 * i + THICKNESS, &img_home);//因为老鹰图片只需一张且分辨率为50*50,占4个小方格,所以在找到二维数组元素值为3的第一个元素后,再将图片输出,然后将这四个元素值为3的元素置为4;
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
/*通过我方坦克的位置来决定敌方坦克的方向*/
DIRECTION enemy_tank_direction(tank_s *tank, int x, int y)
{
	int r;//用于承接产生的随机数
	r = rand() % 100;
	if (tank->x > x)//我方坦克在敌方坦克左侧
	{
		if (tank->y > y)//如果我方坦克在敌方坦克左上方
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
		else//如果我方坦克在敌方坦克左下方
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
	else//我方坦克在敌方坦克右侧
	{
		if (tank->y > y)//如果我方坦克在敌方坦克左上方
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
		else//如果我方坦克在敌方坦克左下方
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
	//子弹在二维数组中的坐标
	x = bullet->bullet_x/25;
	y = (bullet->bullet_y-THICKNESS)/25;
	//擦除上一次绘制的子弹
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
	//碰撞检测
	if (map[y][x] == 4 || map[y1][x1] == 4) {//如果子弹击中我方老鹰
		if (bullet->origin == enemy_Tank) {
			return 1;
		}
		else {
			bullet->status = 0;
		}
	}
	if ((map[y][x] == 200 || map[y1][x1] == 200)) {//如果子弹击中我方坦克
		if (bullet->origin == enemy_Tank) {
			return 1;
		}
		else {
			bullet->status = 0;//若敌方坦克子弹击中敌方坦克,让子弹消失
		}
	}
	if ((map[y][x] >=100 && map[y][x] <100+enemy_num)|| (map[y1][x1] >= 100 && map[y1][x1] <100+enemy_num)) {//如果子弹击中敌方坦克
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
    if ((map[y][x] == 1)) {//如果子弹击中可消除墙
		map[y][x] = 0;
		bullet->status = 0;
		setfillcolor(BLACK);
		solidrectangle(x*25, y*25 + THICKNESS, x*25+25, y*25+25 + THICKNESS);
	}
	else if (map[y][x] == 2) {//如果子弹击中不可消除墙
		bullet->status = 0;
	}
	if ((map[y1][x1] == 1)) {//如果子弹击中可消除墙
		map[y1][x1] = 0;
		bullet->status = 0;
		setfillcolor(BLACK);
		solidrectangle(x1 * 25, y1 * 25 + THICKNESS, x1 * 25 + 25, y1 * 25 + 25 + THICKNESS);
	}
	else if (map[y1][x1] == 2) {//如果子弹击中不可消除墙
		bullet->status = 0;
	}
	//重新绘制子弹
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
		PlaySound(_T("paoji.wav"), NULL, SND_FILENAME | SND_ASYNC);//播放背景音乐
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
			return 0;//移动失败返回0
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
	return 1;//移动成功返回1
}
void tank_move(tank_s * tank, DIRECTION direction, IMAGE *img)
{
	switch (direction)
	{
	case left1://如果左边是空地
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
	case up://如果上边是空地
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
	case down://如果下边是空地
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
	case right1://如果右边是空地
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
	settextstyle(25, 0, _T("幼圆"));
	outtextxy(218,430,_T("按任意键退出游戏!"));
	system("pause");//将画面暂停
	closegraph();//关闭画布
}
void num_show(int Num,IMAGE * tank_img) {
	char num[10];
	TCHAR _Tnum[10];
	setbkmode(TRANSPARENT);
	settextcolor(WHITE);
	settextstyle(25, 0, _T("幼圆"));
	outtextxy(10, 10, _T("剩余"));
	putimage(65, 10, tank_img);
	outtextxy(100, 10, _T("数量:"));
	setfillcolor(BLACK);
	solidrectangle(152, 9, 200, 40);
	sprintf_s(num, sizeof(num),"%d辆",Num);//将整型变量写入char数组
	MultiByteToWideChar(CP_ACP, 0, num, -1, _Tnum, 100);//char类型转换成TCHAR类型
	outtextxy(152, 10,_Tnum);
}
int play(void)
{
	bullet_s my_bullet;//定义我方子弹
	bullet_s enemy_bullet[enemy_num];//定义敌方子弹
	tank_s my_tank;//定义我方tank;
	tank_s enemy_tank[enemy_num];//定义敌方坦克;
	int enemy_total = 3;
	int times = 1;
	//设定我方坦克的出场信息
	my_tank.x = 9;
	my_tank.y = 24;
	my_tank.live = 1;//我方坦克活着
	my_tank.direction = up;//初始方向向上
	my_tank.status = my_Tank;
	my_bullet.status = 0;//起初不存在子弹
	my_bullet.origin = my_Tank;
	set_prop_map(my_tank.x, my_tank.y, 200);
	//设定敌方坦克的出场信息
	for (int i = 0; i < enemy_num; i++)//通过i对3求余,来确定敌方坦克的出场位置;
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
		enemy_tank[i].direction = down;//敌方坦克的出场方向向下
		enemy_tank[i].live = 1;
		enemy_tank[i].status = enemy_Tank;
		enemy_bullet[i].status = 0;//起初敌方坦克并未开炮
		enemy_bullet[i].origin = enemy_Tank;
	}
	//初始化随机数种子
	srand((unsigned)time(NULL));
	//加载我方坦克的图片
	loadimage(&my_tank_img[up], _T("tank_up.jpg"), 50, 50);
	loadimage(&my_tank_img[down], _T("tank_down.jpg"), 50, 50);
	loadimage(&my_tank_img[left1], _T("tank_left.jpg"), 50, 50);
	loadimage(&my_tank_img[right1], _T("tank_right.jpg"), 50, 50);
	//加载敌方坦克的图片
	loadimage(&enemy_tank_img[up], _T("enemy_tank_up.jpg"), 50, 50);
	loadimage(&enemy_tank_img[down], _T("enemy_tank_down.jpg"), 50, 50);
	loadimage(&enemy_tank_img[left1], _T("enemy_tank_left.jpg"), 50, 50);
	loadimage(&enemy_tank_img[right1], _T("enemy_tank_right.jpg"), 50, 50);
	loadimage(&enemy_temp_img, _T("enemy_tank_right.jpg"), 30, 30);
	//音乐响起来
	PlaySound(_T("background.wav"), NULL, SND_FILENAME | SND_ASYNC);//播放背景音乐
	putimage(my_tank.x * 25, my_tank.y * 25+THICKNESS, &my_tank_img[up]);//我方坦克闪亮登场!
	//绘制敌方坦克,敌方前3辆坦克闪亮登场!
	for (int i = 0; i < enemy_total; i++) {
		do_tank_move(&enemy_tank[0], down, &enemy_tank_img[down], 0);
		set_prop_map(enemy_tank[i].x, enemy_tank[i].y, 100+i);
	}
	num_show(enemy_num, &enemy_temp_img);//说明坦克数量
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
		if (times % 200 == 0)//每隔2s改变一次方向
		{
			for (int i = 0; i < enemy_total; i++)
			{
				if (enemy_tank[i].live == 0)
					continue;
				if (i % 2 == 0)//偶数移向我方老巢
				{
					DIRECTION d = enemy_tank_direction(&enemy_tank[i], 12, 24);
					tank_move(&enemy_tank[i], d, &enemy_tank_img[d]);
				}
				else//单数移向我方坦克
				{
					DIRECTION d = enemy_tank_direction(&enemy_tank[i], my_tank.x, my_tank.y);
					tank_move(&enemy_tank[i], d, &enemy_tank_img[d]);
				}
				tank_fire(&enemy_tank[i], &enemy_bullet[i], 0);
			}
		}
		else if (times % 50 == 0)//每隔0.5s移动存活敌方坦克一次
		{
			for (int i = 0; i < enemy_total; i++)
			{
				if (enemy_tank[i].live)
					tank_move(&enemy_tank[i], enemy_tank[i].direction, &enemy_tank_img[enemy_tank[i].direction]);
			}
		}
		int ch;
		if (_kbhit())//如果有键按下,则返回值为true,没有则返回值为false
		{
			ch = _getch();
			switch (ch)
			{
			case 'a'://如果左边是空地
				tank_move(&my_tank, left1, &my_tank_img[left1]);
				break;
			case 'w'://如果上边是空地
				tank_move(&my_tank, up, &my_tank_img[up]);
				break;
			case 's'://如果下边是空地 
				tank_move(&my_tank, down, &my_tank_img[down]);
				break;
			case 'd'://如果右边是空地
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