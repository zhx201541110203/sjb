#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include <time.h>
struct phb                       /*ʹ�ýṹ�����ڴ洢��ҵ���Ϣ */
{
	char nm[20];                 /*���ڴ洢��ҵ�����*/
	int df;                      /*��ҵ÷���Ϣ*/ 
	float num;                   /*�������ܴ��� */
	float mal;                   /*��ҵ�ʤ���� */
	float sl;                    /*���ʤ�� */
};
float zs,ys;                     /*����ͳ�����Ӯ�Ĵ���*/
                                 /*��������Ϊ��ʹ�õĺ��������� */
  int init();
  void baocunxingming(char a[],struct phb c[]);
  int panduan(struct phb a[]);
  void baocunshenglv(struct phb a[]);
  void xierucuowu(struct phb a[]); 
  int show(struct phb a[]); 

int main() 
{
	int a;
	struct phb tz[6]={{"a",0,0},{"b",0,0},{"c",0,0},{"d",0,0},{"e",0,0},{"f",0,0}};/*�ṹ��ĳ�ʼ��*/ 
	    a=init();
	if(a==1)
		exit(0);                     /*���ѡ��1���˳����� */
	if(a==3)
	    a=show(tz);                  /*���ѡ���� ��ʾ���а� */
	while(a==2)                      /*����һ����ѭ�� */
	{
		baocunxingming(tz[0].nm,tz); /*����������� */
		a=panduan(tz);               /*�ж�һ����Ӯ */
    	baocunshenglv(tz);               /*�������ҵ�ʤ�� */
		xierucuowu(tz);              /*����д�����ʱ��ʾ ����ر����������� */
		if(a==3)
		a=show(tz);
	}
	return 0;
}

int init()                          /*����ʼǰ��һЩ��ʼ������ */
{
	int n;
	printf("*****************************************************************\n\n");
	printf("             ��ӭ����ʯͷ�������˻����ս��Ϸ                      \n");
	printf("\n***************************************************************\n\n");
	printf("\t\t��ѡ���Ƿ�������Ϸ����Enterȷ��\n");
	printf("\t\t1:�˳���Ϸ\n\t\t2:������Ϸ\n\t\t3:�鿴��Ϸ���а�\n��ѡ��");
	scanf("%d",&n);                         /*�˴�������ҵ�ѡ��*/
	return n;                               /*���ڼ�ס���һ��ʼ��ѡ��*/ 
	printf("\f");
}
void baocunxingming(char a[],struct phb c[])/*�˺������ڼ��벢������ҵ����� */
{
	FILE *fp;                               /*����һ���ļ���ָ��*/ 
	int b=1,i;
	zs=0;ys=0;
	printf("�����������������");
	scanf("%s",a);                          /*�˴�������ҵ���Ϣ */
	if((fp=fopen("ph.dat","r"))==NULL)      /*fopen�������ڴ��ļ��������ļ���ָ�� */
	{
		for(i=1;i<6;i++)
			if(strcmp(a,c[i].nm)==0)        /*{strcmp�������ڱȽ������ַ����Ĵ�С���ж���������������Ƿ�һ��*/
				b=0;
	}
	else
	{
		for(i=1;i<6;i++)
		{ 
		                                    /*fread�������ļ����ж������� */
			fread(&c[i],sizeof(struct phb),1,fp);/*sizeofΪC�������ж��������ͻ��߱��ʽ���ȷ��Ĳ����� */
			if(strcmp(a,c[i].nm)==0)
				b=0;
		}
		fclose(fp);                              /*�ر�һ���ļ��� */
	}
	if(b==0)                                     /*�������һ�¡���ʾ���� */
	{
		printf("������������Ѵ��ڣ�����������\n");
		baocunxingming(a,c);
	}
	if(b==1)
		printf("\f");
}
int panduan(struct phb a[]  )                         /*�ж�һ����Ӯ�ĺ��� */
{
	int b,c,d;
	zs++;                                             /*�������ܴ������� */
	printf("��ѡ���������Ĳ���Enterȷ��\n");
	printf("1:ʯͷ\n2:����\n3:��\n");
	printf("��ѡ��");
	scanf("%d",&b);
	srand((unsigned int)time(NULL));                 /*���������������ʼ��*/ 
	c=rand()%3+1;                                    /*��������1��3֮����������ģ���ȭ������� */
	switch(b)                                        /*switch������ڶ�ѡ��ĵ�������  */     
		{
			case 1:printf(" ʯͷ--");break;
			case 2:printf(" ����--");break;
			case 3:printf(" ��--");break;
		}
	switch(c)          
		{
			case 1:printf(" ʯͷ\n");break;
			case 2:printf(" ����\n");break;
			case 3:printf(" ��\n");break;
		}
	if((b==1&&c==2)||(b==2&&c==3)||(b==3&&c==1))      /*���Ӯ��������� */
	{
		a[0].df++;                                    /*���Ӯ�Ĵ�����һ*/ 
		ys++;                                         /*Ҳ���ڼ�¼���Ӯ�Ĵ��� �������ڼ���ʤ�� */
		printf("\n\t\t��ϲ�㣡Ӯ��Ŷ��\n\n");
	}
	else if(b==c)
		printf("\n\t\tƽ���ˣ�����Ŷ��\n\n");
	else
	{
		a[0].df--;                                   /*��ҵ�Ӯ�Ĵ�����һ */
		printf("\n\t\t�ǳ���Ǹ�������ˣ�������սѽ��\n\n");
	}
	a[0].sl=ys/zs;                                   /*����ʤ�� */
	a[0].mal=ys;                                     /*��¼�����Ӯ�Ĵ��� ��׼��¼���ļ��� */
	a[0].num=zs;                                     /*��¼��Ĵ�����׼��¼���ļ��� */
	printf("�Ƿ񻹽�����Ϸ\n\n1:�˳���Ϸ\n2:���Ž�����Ϸ\n3:�˳���Ϸ���鿴���а�\n");
	printf("��ѡ��");
	scanf("%d",&d);                                  /*��һ�κ󣬿��ڴ�ѡ���Ƿ���� */
	if(d==2)
		d=panduan(a);
	return d;
}
void baocunshenglv(struct phb a[])                   /*�˺������ڱ�����ҵĵ÷֣�ʤ�ʵ���Ϣ */
{
	FILE *fp;
	int i;
	struct phb b;
	if((fp=fopen("ph.dat","r"))==NULL);              /*�ж��ļ��Ƿ�ǿ� ��fopen�������ڴ��ļ�ph�������ش��ļ���ָ�� */
	else
	{                                                /*ѭ�����ļ����ݶ����ֽ����� */
		for(i=1;i<6;i++)
			fread(&a[i],sizeof(struct phb),1,fp);
		fclose(fp);                                  /*����� �ر��ֽ���*/ 
	}
	for(i=1;i<6;i++)                                 /*����ʤ�� �����ҵ����а�˳�� */
		if(a[0].sl>=a[i].sl)
		{
			b=a[0];
			a[0]=a[i];
			a[i]=b;
		}
}
void xierucuowu(struct phb a[])                       /*�������д�����ʱ�Ĵ���*/ 
{
	int i;
	FILE *fp;
	fp=fopen("ph.dat","w");
	for(i=1;i<6;i++)
		if(fwrite(&a[i],sizeof(struct phb),1,fp)!=1)   /*�ж�д���Ƿ����*/ 
			printf("file write error\n");
	fclose(fp);                                        /*�ر��ļ��� */
}
int show(struct phb a[])                               /*չʾ���а�ĺ���*/ 
{
	int i,b;
	FILE *fp;
	if((fp=fopen("ph.dat","r"))==NULL)                 /*�ļ�����Ϊ�� ���ļ�ʧ�� */
	{
		printf("�޷������а�\n");
	}
	else
	{
		printf("--------------------------------------------------------------------");
		printf("\n����\t\t����\t\t�ܴ���\t\tʤ�ô���\tʤ��");
		for(i=1;i<6;i++)
		{
			fread(&a[i],sizeof(struct phb),1,fp);         /*���ļ����ж�ȡ���а����� ������� */
			printf("\n%s\t\t%d\t\t%4.0f\t\t%4.0f\t\t%5.2f%%\n",a[i].nm,i,a[i].num,a[i].mal,a[i].sl*100);/*����һ����ʽ������а�*/ 
		}
		printf("-----------------------------------------------------------------------");
	}
	printf("\n�Ƿ������Ϸ\n1:�˳���Ϸ\n2:��������Ϸ\n��ѡ��");/*���ٴ�ѡ���Ƿ��ٴν������*/ 
	scanf("%d",&b);                                              /*��¼��ҵ��ٴ�ѡ�� */
	return b;                                                    /*���ظ����� �����Ƿ�������� */
}
