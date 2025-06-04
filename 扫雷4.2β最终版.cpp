#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<string.h>
#include <windows.h>
#define ROW 10
#define COL 10
//自定义函根据参数改变颜色
void color(short x)	
{
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), x);
}
//开始菜单，利用a来决定选项
void start(int a){
	printf("*******###########################*********\n");
	printf("*******|       [ 输入0退出 ]      |********\n");
	printf("*******|    [输入1进入新手教程]   |********\n");
	printf("*******|      [输入2开始游戏 ]    |********\n");
	printf("*******###########################*********\n");
	if(a==3){
		scanf("%d",&a);
		getchar();
	}
	switch (a) {
		case 0:
			exit(0);
		case 1:
			int c;
			system("cls");
			color(6);
			printf("【新手教程】：扫雷是一款经典小游戏。它的规则是输入一个坐标，根据显示的数字（周围8块方块中的雷数），当棋盘中剩余的所有格子都为雷，并不踩到雷，即为获胜。下面是具体操作方法：\n");
			printf("1.开局：首先选择一个起始点，通常是随机输入一个坐标（例如:1,2），这个方格的数字将显示其周围的8个方格中隐藏了几颗雷。\n");
			printf("2.标记雷：使用，1可以标记一个方格是否含有地雷，（例如：标记1,2格式为1,2,1），被标记的方格将用@作为标识。\n");
			printf("3.判断雷的位置：通过观察标记的数字，结合数字周围的方格状态，来判断哪些方格中含有地雷。如果某个数字周围有两个或更多的标记，说明该数字下方可能存在地雷；如果只有单个标记，则可能是雷或者标记错误。\n");
			printf("4.胜利条件：当棋盘中剩下的格子全为雷时游戏胜利，如果输入的坐标对应格子为雷时，游戏结束！\n");
			printf("5.技巧与策略：扫雷游戏中，可以通过尝试不同的路径和方法来提高胜率。例如，可以从边缘开始逐步向中心推进，或者优先标记那些与其他数字相邻且看起来最有可能藏有地雷的区域。\n");
			color(7);
			printf("*******###########################*********\n");
			printf("*******|      [ 输入0退出 ]       |********\n");
			printf("*******|  [输入其他数字开始游戏]  |********\n");
			printf("*******###########################*********\n");
			scanf("%d",&c);
			if(c==0)
				exit(0);
			break;
		case 2:
			break;
		default:
			printf("error!");
			start(3);
	}
}
void BOOMS(int map[][COL]){
	//设置随机数种子 
	srand(time(NULL));
	//设置10个雷,用9表示
	for(int i=0;i<10;){
		int r=rand()%ROW;  //随机开始布置雷
		int c=rand()%ROW;
		 if(map[r][c]==0){ //若该坐标不为雷时，我们将其布置雷（赋值为9)
		 	map[r][c]=9; 
		 	i++;  // i 表示雷的个数
		 }
	}
	//标记雷周围格子的数字
	for(int i=0;i<ROW;i++){  //开始循环棋盘
		for(int k=0;k<COL;k++){
			if(map[i][k]==9){   //如果该坐标为雷，则需要周围8个格子各加1
				for(int r=i-1;r <=i+1;r++){
					for(int c=k-1;c<=k+1;c++){
						if(r>=0&&r<ROW&&c>=0&&c<COL&&map[r][c]!=9){ //将r，c局限于棋盘内
						map[r][c]++;
						}
					}
				}				
			}
		}
	}
}
//初始化里地图
void uncover(char unmap[11][11]){
	for(int i=1;i<11;i++){
		for(int j=1;j<11;j++){
			unmap[i][j]='*';
		}
		for(int i=1;i<11;i++){
			unmap[i][0]=i-1+'0';
			unmap[0][i]=i-1+'0';
		}
	}
	unmap[0][0]=' ';
}
void show(char unmap[11][11]){
	for(int i=0;i<11;i++){ 
		for(int k=0;k<11;k++){
			if(i==0||k==0){ 
			color(2);
			printf("%c ",unmap[i][k]);
			color(7);
			}
			else if(unmap[i][k]=='@'){//如果是标记符号@则用红色输出
				color(4);
				printf("%c ",unmap[i][k]);
				color(7);
			}
			else if(unmap[i][k]=='0')//如果是0则输出空格
				printf("  ");
			else
			printf("%c ",unmap[i][k]);
		}
		printf("\n");
	}
}
//炸开0格子
void fun(int map[][10],int a,int b,char unmap[][11]){ //a,b为里棋盘数字
	int x=a+1;
	int y=b+1;
	if(unmap[x][y]=='0'){  //判断点开坐标是否为0
		for(int r=x-1;r<=x+1;r++){  //开始炸开周围格子
			for(int c=y-1;c<=y+1;c++){
				if(r>=1&&r<=11&&c>=1&&c<=11&&unmap[r][c]=='*'){  //将r,c局限在棋盘并且判断是为“*”
					unmap[r][c]=map[r-1][c-1]+'0';  //将里棋盘显示出来
					fun(map,(r-1),(c-1),unmap);  //若周围出现0，则递归回fun函数继续jie'duan进行，直到周围数字都不为0
				}
			}
		}
		
	}	
}
int ingame(int a,int b,char unmap[][11],int map[][10]){
	int k=0;
	if(map[a][b]!=9)  //输入坐标不是雷时，显示内棋盘
	{
		unmap[a+1][b+1]=map[a][b]+'0';
		fun(map,a,b,unmap);
	//判断胜利
	for(int i=0;i<=10&&k<12;i++){ //k表示“*”数目，循环棋盘，计算k值
		for(int j=0;j<=10;j++)
			{
				if(unmap[i][j]=='*'||unmap[i][j]=='@')
				{
					k++;
				}
				if(k>10) // k大于10时，游戏继续
					break;
			}
	}
	if(k==10) //k等于10，游戏结束
		return 0;
	else
		return 2;
	}
	else 
	return 1;
}
int game(int map[][COL],char unmap[][11]){
	//排除第一个就是雷的情况
	int x,y;
	scanf("%d,%d",&x,&y);
	getchar();
	system("cls");  //清屏
		for(;1;){
			if(x<0||x>9||y<0||y>9){
				printf("请输入正确的坐标\n");
				scanf("%d,%d",&x,&y);
				getchar();
			}
			else if(map[x][y]==9){  //若第一次点到雷，则需重新布置雷，重新开始游戏
				BOOMS(map);
			}
			else{  //若第一次不是雷，正常继续游戏
				unmap[x+1][y+1]=map[x][y]+'0';
				fun(map,x,y,unmap);
				break;
			}
		}
	//正式开始扫雷
	do{
		int a,b,p=0,q=2;
		show(unmap);  //展示外棋盘
		scanf("%d,%d,%d",&a,&b,&p);   //开始输入坐标
		getchar();
		system("cls");
		if(a<0||a>9||b<0||b>9){  //输入比棋盘大的坐标需重新输入
			printf("请输入正确的坐标\n");
			scanf("%d,%d,%d",&a,&b,&p);
			getchar();
		}
		else if(p==0)
		q=ingame(a,b,unmap,map);
		else{
		unmap[a+1][b+1]='@';
		q=2;
		}
		if(q!=2)
			return q;
	}while(1);
	}
void lose(){
	printf("*******###########################*********\n");
	printf("*******|           loser!        |*********\n");
	printf("*******###########################*********\n");
}
void win(){
	printf("*******###########################*********\n");
	printf("*******|          winner!         |********\n");
	printf("*******###########################*********\n");
}
int end(){
	printf("*******###########################*********\n");
	printf("*******      ！[结束页面] ！      *********\n");
	printf("*******|      [ 输入0退出 ]       |********\n");
	printf("*******|     [ 输入1重新开始 ]    |********\n");
	printf("*******###########################*********\n");
	int a;
	scanf("%d",&a);
	getchar();
	return a;
}
//最终输出答案
void showout(char unmap[][11],int map[][10]){
	for(int i=1;i<11;i++){
		for(int j=1;j<11;j++){
			unmap[i][j]=map[i-1][j-1]+'0';
			if(unmap[i][j]=='9'){
				unmap[i][j]='@';
			}
		}
	}
	show(unmap);
}
int main(){
	start(3);
	loop://设置一个记录点方便再次开始游戏
	system("cls");
	int s,b;
	int map[10][10]={0}; 
	char unmap[11][11]; 
	BOOMS(map); 
	uncover(unmap);
	show(unmap);
	s=game(map,unmap);
	system("cls");
	if(s==1){
		lose();
		showout(unmap,map);
		b=end();
		if(b==1)
			goto loop;
	}
	else{
		win();
		showout(unmap,map);
		b=end();
		if(b==1)
			goto loop;
		else
		exit(0);
	}
}
