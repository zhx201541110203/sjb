#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include <time.h>
struct phb                       /*使用结构体用于存储玩家的信息 */
{
	char nm[20];                 /*用于存储玩家的姓名*/
	int df;                      /*玩家得分信息*/ 
	float num;                   /*玩家玩的总次数 */
	float mal;                   /*玩家得胜次数 */
	float sl;                    /*玩家胜率 */
};
float zs,ys;                     /*用于统计玩家赢的次数*/
                                 /*以下六行为所使用的函数的声明 */
  int init();
  void baocunxingming(char a[],struct phb c[]);
  int panduan(struct phb a[]);
  void baocunshenglv(struct phb a[]);
  void xierucuowu(struct phb a[]); 
  int show(struct phb a[]); 

int main() 
{
	int a;
	struct phb tz[6]={{"a",0,0},{"b",0,0},{"c",0,0},{"d",0,0},{"e",0,0},{"f",0,0}};/*结构体的初始化*/ 
	    a=init();
	if(a==1)
		exit(0);                     /*玩家选择1，退出程序 */
	if(a==3)
	    a=show(tz);                  /*玩家选择三 显示排行榜 */
	while(a==2)                      /*进入一个死循环 */
	{
		baocunxingming(tz[0].nm,tz); /*保存玩家名字 */
		a=panduan(tz);               /*判断一次输赢 */
    	baocunshenglv(tz);               /*计算该玩家的胜率 */
		xierucuowu(tz);              /*数据写入错误时提示 否则关闭所有数据流 */
		if(a==3)
		a=show(tz);
	}
	return 0;
}

int init()                          /*程序开始前的一些初始化函数 */
{
	int n;
	printf("*****************************************************************\n\n");
	printf("             欢迎来到石头剪刀布人机大对战游戏                      \n");
	printf("\n***************************************************************\n\n");
	printf("\t\t请选择是否运行游戏并按Enter确定\n");
	printf("\t\t1:退出游戏\n\t\t2:运行游戏\n\t\t3:查看游戏排行榜\n请选择：");
	scanf("%d",&n);                         /*此处键入玩家的选择*/
	return n;                               /*用于记住玩家一开始的选择*/ 
	printf("\f");
}
void baocunxingming(char a[],struct phb c[])/*此函数用于键入并保存玩家的姓名 */
{
	FILE *fp;                               /*定义一个文件的指针*/ 
	int b=1,i;
	zs=0;ys=0;
	printf("请输入你的人物名：");
	scanf("%s",a);                          /*此处键入玩家的信息 */
	if((fp=fopen("ph.dat","r"))==NULL)      /*fopen函数用于打开文件，返回文件的指针 */
	{
		for(i=1;i<6;i++)
			if(strcmp(a,c[i].nm)==0)        /*{strcmp函数用于比较两个字符串的大小，判断两次输入的姓名是否一致*/
				b=0;
	}
	else
	{
		for(i=1;i<6;i++)
		{ 
		                                    /*fread函数从文件流中读入数据 */
			fread(&c[i],sizeof(struct phb),1,fp);/*sizeof为C语言中判断数据类型或者表达式长度符的操作符 */
			if(strcmp(a,c[i].nm)==0)
				b=0;
		}
		fclose(fp);                              /*关闭一个文件流 */
	}
	if(b==0)                                     /*玩家姓名一致。提示错误 */
	{
		printf("你输入的名字已存在，请重新输入\n");
		baocunxingming(a,c);
	}
	if(b==1)
		printf("\f");
}
int panduan(struct phb a[]  )                         /*判断一次输赢的函数 */
{
	int b,c,d;
	zs++;                                             /*玩家玩的总次数计数 */
	printf("请选择你所出的并按Enter确定\n");
	printf("1:石头\n2:剪刀\n3:布\n");
	printf("请选择：");
	scanf("%d",&b);
	srand((unsigned int)time(NULL));                 /*随机数产生函数初始化*/ 
	c=rand()%3+1;                                    /*产生介于1到3之间的随机数，模拟出拳的随机性 */
	switch(b)                                        /*switch语句用于多选择的的流程中  */     
		{
			case 1:printf(" 石头--");break;
			case 2:printf(" 剪刀--");break;
			case 3:printf(" 布--");break;
		}
	switch(c)          
		{
			case 1:printf(" 石头\n");break;
			case 2:printf(" 剪刀\n");break;
			case 3:printf(" 布\n");break;
		}
	if((b==1&&c==2)||(b==2&&c==3)||(b==3&&c==1))      /*玩家赢的三种情况 */
	{
		a[0].df++;                                    /*玩家赢的次数加一*/ 
		ys++;                                         /*也用于记录玩家赢的次数 不过用于计算胜率 */
		printf("\n\t\t恭喜你！赢了哦！\n\n");
	}
	else if(b==c)
		printf("\n\t\t平局了！加油哦！\n\n");
	else
	{
		a[0].df--;                                   /*玩家的赢的次数减一 */
		printf("\n\t\t非常抱歉！你输了，继续来战呀！\n\n");
	}
	a[0].sl=ys/zs;                                   /*计算胜率 */
	a[0].mal=ys;                                     /*记录下玩家赢的次数 ，准备录入文件中 */
	a[0].num=zs;                                     /*记录玩的次数，准备录入文件中 */
	printf("是否还进行游戏\n\n1:退出游戏\n2:接着进行游戏\n3:退出游戏并查看排行榜\n");
	printf("请选择：");
	scanf("%d",&d);                                  /*玩一次后，可在此选择是否继续 */
	if(d==2)
		d=panduan(a);
	return d;
}
void baocunshenglv(struct phb a[])                   /*此函数用于保存玩家的得分，胜率等信息 */
{
	FILE *fp;
	int i;
	struct phb b;
	if((fp=fopen("ph.dat","r"))==NULL);              /*判断文件是否非空 ，fopen函数用于打开文件ph，并返回此文件的指针 */
	else
	{                                                /*循环把文件内容读到字节流中 */
		for(i=1;i<6;i++)
			fread(&a[i],sizeof(struct phb),1,fp);
		fclose(fp);                                  /*读完后 关闭字节流*/ 
	}
	for(i=1;i<6;i++)                                 /*按照胜率 完成玩家的排行榜顺序 */
		if(a[0].sl>=a[i].sl)
		{
			b=a[0];
			a[0]=a[i];
			a[i]=b;
		}
}
void xierucuowu(struct phb a[])                       /*玩家数据写入错误时的处理*/ 
{
	int i;
	FILE *fp;
	fp=fopen("ph.dat","w");
	for(i=1;i<6;i++)
		if(fwrite(&a[i],sizeof(struct phb),1,fp)!=1)   /*判断写入是否错误*/ 
			printf("file write error\n");
	fclose(fp);                                        /*关闭文件流 */
}
int show(struct phb a[])                               /*展示排行榜的函数*/ 
{
	int i,b;
	FILE *fp;
	if((fp=fopen("ph.dat","r"))==NULL)                 /*文件内容为空 打开文件失败 */
	{
		printf("无法打开排行榜\n");
	}
	else
	{
		printf("--------------------------------------------------------------------");
		printf("\n姓名\t\t名次\t\t总次数\t\t胜得次数\t胜率");
		for(i=1;i<6;i++)
		{
			fread(&a[i],sizeof(struct phb),1,fp);         /*从文件流中读取排行榜数据 遍历输出 */
			printf("\n%s\t\t%d\t\t%4.0f\t\t%4.0f\t\t%5.2f%%\n",a[i].nm,i,a[i].num,a[i].mal,a[i].sl*100);/*按照一定格式输出排行榜*/ 
		}
		printf("-----------------------------------------------------------------------");
	}
	printf("\n是否接着游戏\n1:退出游戏\n2:还接着游戏\n请选择：");/*可再次选择是否再次进入程序*/ 
	scanf("%d",&b);                                              /*记录玩家的再次选择 */
	return b;                                                    /*返回给电脑 决定是否继续程序 */
}
