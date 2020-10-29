/*

**** 程序名：PCB创建、阻塞、唤醒、终止模拟 
**** 时间：2020年10月23日
**** 作者：朱领

**** 程序思路
		1.用结构体模拟一个PCB
		typedef struct pcb
		{
			char P_name[10];//进程名
			char P_por;//优先级，1-3个级别 1.低 2.中 3.高
			char P_status;//运行状态，0.阻塞，1.运行，2.就绪 
			int P_runtime;//运行时间 
			//int P_wait;//等待时间
			struct pcb *next;//指针，指向下一个PCB 
		}PCB;
		
		2.利用数据结构线性链表存储 

**** 变量含义：
		
		
		
**** 函数功能：
**** 	1.Menu()：菜单
		2.CPCB(PCB *head)：创建PCB，创建一个结构体对象
		3.StopPCB(PCB *head)：阻塞PCB，将运行中的PCB添加到阻塞队列中
		4.WarePCB(PCB *head)：唤醒PCB，将阻塞队列中的PCB添加到运行队列中
		5.KillPCB(PCB *head)：终止PCB 
		6.insert(PCB *head,PCB *temp)： 将创建的PCB插入线性链表中
		7.Check(PCB *head,PCB *temp)：检查PCB是否存在 
		8.run(PCB *head)：保证有一个运行的PCB 
**** 其他声明：

*/

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
//用线性表实现PCB 
typedef struct pcb
{
	char P_name[10];//进程名
	char P_por;//优先级，1-3个级别 1.低 2.中 3.高
	char P_status;//运行状态，0.阻塞，1.运行，2.就绪 
	int P_runtime;//运行时间 
	int P_wait;//等待时间
	struct pcb *next;//指针，指向下一个PCB 
}PCB;
 
void Menu()
{
	printf("*********************系统主菜单*************************\n");
	printf("--------------------------------------------------------\n");
	putchar(10); 
	printf("*********************1.创建进程*************************\n");
	printf("*********************2.阻塞进程*************************\n");
	printf("*********************3.唤醒进程*************************\n");
	printf("*********************4.终止进程*************************\n");
	printf("*********************5.显示进程*************************\n");
	printf("*********************0.退    出*************************\n");
	putchar(10);
	printf("--------------------------------------------------------\n");	
} 
void insert(PCB *head,PCB *temp)
{
	//保存头节点
	//尾插法
	PCB *p;
	p = head;
	while(p->next != NULL)
	{
		p = p->next;
	}
	p->next = temp;
	temp->next = NULL;
}
//检查进程是否已经创建
int Check(PCB *head,PCB *temp)
{
	PCB *p = head;
	while(p->next)
	{
		p = p->next;
		if(strcmp(p->P_name,temp->P_name) == 0)
		{
			return 0;
		}
	}
	return 1;
}
//保证有一个程序在运行
void run(PCB *head)
{
	//指向第一个节点
	PCB *p = head->next;
	//遍历链表给前面的就绪队列等待时间+1
	//防止前面进程因为唤醒又进入运行状态
	while(p != NULL)
	{
		if(p->P_status == '2')
		{
			p->P_wait++;
		}
		p = p->next;
	}
	//回到第一个节点
	p = head->next;
	while(p->P_status != '1' && p != NULL)
	{
		//防止被唤醒的又进入阻塞状态
		if(p->P_status == '2')  
		{
			p->P_status = '1';
			p->P_wait = 2;
		}
		if(p->P_status == '1')
		{
			return;
		}
		p = p->next;     
	}
	return;

}
void CPCB(PCB *head)
{
	//设置检查进程名称，相同则返回主界面
	int chk = 0;
	PCB *temp = (PCB *)malloc(sizeof(PCB));
	system("cls");
	printf("----------Create PCB--------------\n");
	printf("input PCB name:");
	scanf("%s",temp->P_name);
	getchar();
	chk = Check(head,temp);
	if(chk == 0)
	{
		printf("创建失败：该进程已经存在\n");
		system("pause");
		return;
	}
	//优先级
	printf("Enter PCB por(1:低 2:中 3: 高):");
	scanf("%c",&temp->P_por);
	getchar();
	//运行时间
	printf("Enter PCB runtime:");
	scanf("%d",&temp->P_runtime);
	getchar();
	//直接设置为就绪
	temp->P_status = '2';
	temp->P_wait = 2;
	/*
	printf("Enter PCB status(0：阻塞，1：就绪，2：运行):");
	scanf("%c",&temp->P_status);
	getchar();

	*/

	//插入队列
	insert(head,temp);
	system("pause");
	run(head);
}
void StopPCB(PCB *head)
{
	
	char name[10];
	//记录头节点
	PCB *p = head;
	system("cls");
	printf("输入要放入阻塞队列的进程名称:");
	scanf("%s",name);
	getchar();
	p = p->next;
	//遍历查看队列中是否有叫做name的进程
	while(p)
	{
		if(strcmp(p->P_name,name) == 0)
		{
			break;
		}
		p = p->next;
	}
	if(!p)
	{
		printf("此进程不存在\n");
		return;
	}
	if(p->P_status == '1')
	{
		printf("该进程正在运行\n");
		printf("正在将该进程放入阻塞队列……\n\n");
		p->P_status = '0';
		printf("该进程已成功放入阻塞队列\n\n");
	}
	else
	{
		if(p->P_status == '0')
		{
			printf("该进程已经在就绪队列中\n");
		}
		if(p->P_status == '2')
		{
			printf("该进程正处于就绪队列中不可阻塞\n");
		}
	}
	run(head);
}
void WarePCB(PCB *head)
{
	char name[10];
	//记录头节点
	PCB *p = head;
	system("cls");
	printf("输入要唤醒的进程名称:");
	scanf("%s",name);
	getchar();
	p = p->next;
	//遍历查看队列中是否有叫做name的进程
	while(p)
	{
		if(strcmp(p->P_name,name) == 0)
		{
			break;
		}
		p = p->next;
	}
	if(!p)
	{
		printf("此进程不存在\n");
		return;
	}
	if(p->P_status == '0')
	{
		printf("该进程正在阻塞队列中\n");
		printf("正在将该进程放入就绪队列……\n\n");
		p->P_status = '2';
		p->P_wait = 2;
		printf("该进程已成功放入就绪队列\n\n");
	}
	else
	{
		if(p->P_status == '1')
		{
			printf("该进程已经在运行，不可唤醒\n");
		}
		if(p->P_status == '2')
		{
			printf("该进程正处于就绪队列中不可唤醒\n");
		}
	}
}
void Delete(PCB *head,PCB *temp)
{
	PCB *p = head,*q = temp->next;
	while(p->next != temp)
	{
		p = p->next;
	}
	p->next = q;
	free(temp);
}
void KillPCB(PCB *head)
{
	char name[10];
	//记录头节点
	PCB *p = head;
	system("cls");
	printf("输入要杀死的进程名称:");
	scanf("%s",name);
	getchar();
	p = p->next;
	//遍历查看队列中是否有叫做name的进程
	while(p)
	{
		if(strcmp(p->P_name,name) == 0)
		{
			break;
		}
		p = p->next;
	}
	if(!p)
	{
		printf("此进程不存在\n");
		return;
	}
	Delete(head,p);
	printf("进程终止成功");
	run(head);
}
void ShowPCB(PCB *head)
{
	//给就绪进程标号
	int ready = 1;
	//给运行进程标号
	int run = 1;
	//给阻塞进程标号
	int block = 1;

	PCB *p = head,*q;
	system("cls");
	printf("---------------------显示进程--------------------------\n"); 
	printf("======================================================\n");
	if(p->next == NULL)
	{
		printf("当前系统中没有进程，请先创建");
		//system("PAUSE")? 是暂停的意思，
		//等待用户信号；不然控制台程序会一闪即过，
		//你来不及看到执行结果。
		system("pause");
		return;
	}
	//列出就绪列表
	q = p->next;
	printf("-----------就绪进程-----------\n");
	while(q)
	{
		if(q->P_status == '2')
		{
			//进程名
			printf("%d 	进程名：%s",ready++,q->P_name);
			//优先级
			printf("	优先级：%c",q->P_por);
			printf("	运行时间：%d",q->P_runtime);
			printf("	等待时间：%d",q->P_wait);
			putchar(10);
		}
		q = q->next;
	}
	putchar(10);

	// 列出运行队列列表
	q = p->next;
	printf("-----------运行进程-----------\n");
	while(q)
	{
		if(q->P_status == '1')
		{
			//进程名
			printf("%d 	进程名：%s",run++,q->P_name);
			//优先级
			printf("	优先级：%c",q->P_por);
			printf("	运行时间：%d",q->P_runtime);
			printf("已运行时间");
			putchar(10);
		}
		q = q->next;
	}
	putchar(10);

	q = p->next;
	printf("-----------阻塞进程-----------\n");
	while(q)
	{
		if(q->P_status == '0')
		{
			//进程名
			printf("%d 	进程名：%s",block++,q->P_name);
			//优先级
			printf("	优先级：%c",q->P_por);
			printf("	运行时间：%d",q->P_runtime);
			printf("	等待时间：%d",q->P_wait);
			putchar(10);
		}
		q = q->next;
	}
	putchar(10);

	
	printf("===============================\n");
	printf("----------进程显示完毕--------------\n"); 
	system("pause");
	
}
int main()
{
	
	PCB * head;
	//头节点为空
	head = (PCB *)malloc(sizeof(PCB));
	head->next = NULL;
	
	if(!head)
	{
		printf("error");
		system("pause");
		exit(0);
	}

	while(1)
	{
		//输入选择 
		int choice;
		Menu();
		printf("请输入你的选择（0-5):");
		scanf("%d",&choice); 
		switch(choice)
		{
			case 1:CPCB(head);break;
			case 2:StopPCB(head);break;
			case 3:WarePCB(head);break;
			case 4:KillPCB(head);break;
			case 5:ShowPCB(head);break;
			case 0:exit(0);
			default:;
			
		}
		
	}
	
	return 0;
} 