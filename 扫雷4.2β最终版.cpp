#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<string.h>
#include <windows.h>
#define ROW 10
#define COL 10
//�Զ��庯���ݲ����ı���ɫ
void color(short x)	
{
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), x);
}
//��ʼ�˵�������a������ѡ��
void start(int a){
	printf("*******###########################*********\n");
	printf("*******|       [ ����0�˳� ]      |********\n");
	printf("*******|    [����1�������ֽ̳�]   |********\n");
	printf("*******|      [����2��ʼ��Ϸ ]    |********\n");
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
			printf("�����ֽ̡̳���ɨ����һ���С��Ϸ�����Ĺ���������һ�����꣬������ʾ�����֣���Χ8�鷽���е�����������������ʣ������и��Ӷ�Ϊ�ף������ȵ��ף���Ϊ��ʤ�������Ǿ������������\n");
			printf("1.���֣�����ѡ��һ����ʼ�㣬ͨ�����������һ�����꣨����:1,2���������������ֽ���ʾ����Χ��8�������������˼����ס�\n");
			printf("2.����ף�ʹ�ã�1���Ա��һ�������Ƿ��е��ף������磺���1,2��ʽΪ1,2,1��������ǵķ�����@��Ϊ��ʶ��\n");
			printf("3.�ж��׵�λ�ã�ͨ���۲��ǵ����֣����������Χ�ķ���״̬�����ж���Щ�����к��е��ס����ĳ��������Χ�����������ı�ǣ�˵���������·����ܴ��ڵ��ף����ֻ�е�����ǣ���������׻��߱�Ǵ���\n");
			printf("4.ʤ����������������ʣ�µĸ���ȫΪ��ʱ��Ϸʤ�����������������Ӧ����Ϊ��ʱ����Ϸ������\n");
			printf("5.��������ԣ�ɨ����Ϸ�У�����ͨ�����Բ�ͬ��·���ͷ��������ʤ�ʡ����磬���Դӱ�Ե��ʼ���������ƽ����������ȱ����Щ���������������ҿ��������п��ܲ��е��׵�����\n");
			color(7);
			printf("*******###########################*********\n");
			printf("*******|      [ ����0�˳� ]       |********\n");
			printf("*******|  [�����������ֿ�ʼ��Ϸ]  |********\n");
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
	//������������� 
	srand(time(NULL));
	//����10����,��9��ʾ
	for(int i=0;i<10;){
		int r=rand()%ROW;  //�����ʼ������
		int c=rand()%ROW;
		 if(map[r][c]==0){ //�������겻Ϊ��ʱ�����ǽ��䲼���ף���ֵΪ9)
		 	map[r][c]=9; 
		 	i++;  // i ��ʾ�׵ĸ���
		 }
	}
	//�������Χ���ӵ�����
	for(int i=0;i<ROW;i++){  //��ʼѭ������
		for(int k=0;k<COL;k++){
			if(map[i][k]==9){   //���������Ϊ�ף�����Ҫ��Χ8�����Ӹ���1
				for(int r=i-1;r <=i+1;r++){
					for(int c=k-1;c<=k+1;c++){
						if(r>=0&&r<ROW&&c>=0&&c<COL&&map[r][c]!=9){ //��r��c������������
						map[r][c]++;
						}
					}
				}				
			}
		}
	}
}
//��ʼ�����ͼ
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
			else if(unmap[i][k]=='@'){//����Ǳ�Ƿ���@���ú�ɫ���
				color(4);
				printf("%c ",unmap[i][k]);
				color(7);
			}
			else if(unmap[i][k]=='0')//�����0������ո�
				printf("  ");
			else
			printf("%c ",unmap[i][k]);
		}
		printf("\n");
	}
}
//ը��0����
void fun(int map[][10],int a,int b,char unmap[][11]){ //a,bΪ����������
	int x=a+1;
	int y=b+1;
	if(unmap[x][y]=='0'){  //�жϵ㿪�����Ƿ�Ϊ0
		for(int r=x-1;r<=x+1;r++){  //��ʼը����Χ����
			for(int c=y-1;c<=y+1;c++){
				if(r>=1&&r<=11&&c>=1&&c<=11&&unmap[r][c]=='*'){  //��r,c���������̲����ж���Ϊ��*��
					unmap[r][c]=map[r-1][c-1]+'0';  //����������ʾ����
					fun(map,(r-1),(c-1),unmap);  //����Χ����0����ݹ��fun��������jie'duan���У�ֱ����Χ���ֶ���Ϊ0
				}
			}
		}
		
	}	
}
int ingame(int a,int b,char unmap[][11],int map[][10]){
	int k=0;
	if(map[a][b]!=9)  //�������겻����ʱ����ʾ������
	{
		unmap[a+1][b+1]=map[a][b]+'0';
		fun(map,a,b,unmap);
	//�ж�ʤ��
	for(int i=0;i<=10&&k<12;i++){ //k��ʾ��*����Ŀ��ѭ�����̣�����kֵ
		for(int j=0;j<=10;j++)
			{
				if(unmap[i][j]=='*'||unmap[i][j]=='@')
				{
					k++;
				}
				if(k>10) // k����10ʱ����Ϸ����
					break;
			}
	}
	if(k==10) //k����10����Ϸ����
		return 0;
	else
		return 2;
	}
	else 
	return 1;
}
int game(int map[][COL],char unmap[][11]){
	//�ų���һ�������׵����
	int x,y;
	scanf("%d,%d",&x,&y);
	getchar();
	system("cls");  //����
		for(;1;){
			if(x<0||x>9||y<0||y>9){
				printf("��������ȷ������\n");
				scanf("%d,%d",&x,&y);
				getchar();
			}
			else if(map[x][y]==9){  //����һ�ε㵽�ף��������²����ף����¿�ʼ��Ϸ
				BOOMS(map);
			}
			else{  //����һ�β����ף�����������Ϸ
				unmap[x+1][y+1]=map[x][y]+'0';
				fun(map,x,y,unmap);
				break;
			}
		}
	//��ʽ��ʼɨ��
	do{
		int a,b,p=0,q=2;
		show(unmap);  //չʾ������
		scanf("%d,%d,%d",&a,&b,&p);   //��ʼ��������
		getchar();
		system("cls");
		if(a<0||a>9||b<0||b>9){  //��������̴����������������
			printf("��������ȷ������\n");
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
	printf("*******      ��[����ҳ��] ��      *********\n");
	printf("*******|      [ ����0�˳� ]       |********\n");
	printf("*******|     [ ����1���¿�ʼ ]    |********\n");
	printf("*******###########################*********\n");
	int a;
	scanf("%d",&a);
	getchar();
	return a;
}
//���������
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
	loop://����һ����¼�㷽���ٴο�ʼ��Ϸ
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
