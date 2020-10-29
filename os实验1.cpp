/*

**** ��������PCB���������������ѡ���ֹģ�� 
**** ʱ�䣺2020��10��23��
**** ���ߣ�����

**** ����˼·
		1.�ýṹ��ģ��һ��PCB
		typedef struct pcb
		{
			char P_name[10];//������
			char P_por;//���ȼ���1-3������ 1.�� 2.�� 3.��
			char P_status;//����״̬��0.������1.���У�2.���� 
			int P_runtime;//����ʱ�� 
			//int P_wait;//�ȴ�ʱ��
			struct pcb *next;//ָ�룬ָ����һ��PCB 
		}PCB;
		
		2.�������ݽṹ��������洢 

**** �������壺
		
		
		
**** �������ܣ�
**** 	1.Menu()���˵�
		2.CPCB(PCB *head)������PCB������һ���ṹ�����
		3.StopPCB(PCB *head)������PCB���������е�PCB��ӵ�����������
		4.WarePCB(PCB *head)������PCB�������������е�PCB��ӵ����ж�����
		5.KillPCB(PCB *head)����ֹPCB 
		6.insert(PCB *head,PCB *temp)�� ��������PCB��������������
		7.Check(PCB *head,PCB *temp)�����PCB�Ƿ���� 
		8.run(PCB *head)����֤��һ�����е�PCB 
**** ����������

*/

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
//�����Ա�ʵ��PCB 
typedef struct pcb
{
	char P_name[10];//������
	char P_por;//���ȼ���1-3������ 1.�� 2.�� 3.��
	char P_status;//����״̬��0.������1.���У�2.���� 
	int P_runtime;//����ʱ�� 
	int P_wait;//�ȴ�ʱ��
	struct pcb *next;//ָ�룬ָ����һ��PCB 
}PCB;
 
void Menu()
{
	printf("*********************ϵͳ���˵�*************************\n");
	printf("--------------------------------------------------------\n");
	putchar(10); 
	printf("*********************1.��������*************************\n");
	printf("*********************2.��������*************************\n");
	printf("*********************3.���ѽ���*************************\n");
	printf("*********************4.��ֹ����*************************\n");
	printf("*********************5.��ʾ����*************************\n");
	printf("*********************0.��    ��*************************\n");
	putchar(10);
	printf("--------------------------------------------------------\n");	
} 
void insert(PCB *head,PCB *temp)
{
	//����ͷ�ڵ�
	//β�巨
	PCB *p;
	p = head;
	while(p->next != NULL)
	{
		p = p->next;
	}
	p->next = temp;
	temp->next = NULL;
}
//�������Ƿ��Ѿ�����
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
//��֤��һ������������
void run(PCB *head)
{
	//ָ���һ���ڵ�
	PCB *p = head->next;
	//���������ǰ��ľ������еȴ�ʱ��+1
	//��ֹǰ�������Ϊ�����ֽ�������״̬
	while(p != NULL)
	{
		if(p->P_status == '2')
		{
			p->P_wait++;
		}
		p = p->next;
	}
	//�ص���һ���ڵ�
	p = head->next;
	while(p->P_status != '1' && p != NULL)
	{
		//��ֹ�����ѵ��ֽ�������״̬
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
	//���ü��������ƣ���ͬ�򷵻�������
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
		printf("����ʧ�ܣ��ý����Ѿ�����\n");
		system("pause");
		return;
	}
	//���ȼ�
	printf("Enter PCB por(1:�� 2:�� 3: ��):");
	scanf("%c",&temp->P_por);
	getchar();
	//����ʱ��
	printf("Enter PCB runtime:");
	scanf("%d",&temp->P_runtime);
	getchar();
	//ֱ������Ϊ����
	temp->P_status = '2';
	temp->P_wait = 2;
	/*
	printf("Enter PCB status(0��������1��������2������):");
	scanf("%c",&temp->P_status);
	getchar();

	*/

	//�������
	insert(head,temp);
	system("pause");
	run(head);
}
void StopPCB(PCB *head)
{
	
	char name[10];
	//��¼ͷ�ڵ�
	PCB *p = head;
	system("cls");
	printf("����Ҫ�����������еĽ�������:");
	scanf("%s",name);
	getchar();
	p = p->next;
	//�����鿴�������Ƿ��н���name�Ľ���
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
		printf("�˽��̲�����\n");
		return;
	}
	if(p->P_status == '1')
	{
		printf("�ý�����������\n");
		printf("���ڽ��ý��̷����������С���\n\n");
		p->P_status = '0';
		printf("�ý����ѳɹ�������������\n\n");
	}
	else
	{
		if(p->P_status == '0')
		{
			printf("�ý����Ѿ��ھ���������\n");
		}
		if(p->P_status == '2')
		{
			printf("�ý��������ھ��������в�������\n");
		}
	}
	run(head);
}
void WarePCB(PCB *head)
{
	char name[10];
	//��¼ͷ�ڵ�
	PCB *p = head;
	system("cls");
	printf("����Ҫ���ѵĽ�������:");
	scanf("%s",name);
	getchar();
	p = p->next;
	//�����鿴�������Ƿ��н���name�Ľ���
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
		printf("�˽��̲�����\n");
		return;
	}
	if(p->P_status == '0')
	{
		printf("�ý�����������������\n");
		printf("���ڽ��ý��̷���������С���\n\n");
		p->P_status = '2';
		p->P_wait = 2;
		printf("�ý����ѳɹ������������\n\n");
	}
	else
	{
		if(p->P_status == '1')
		{
			printf("�ý����Ѿ������У����ɻ���\n");
		}
		if(p->P_status == '2')
		{
			printf("�ý��������ھ��������в��ɻ���\n");
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
	//��¼ͷ�ڵ�
	PCB *p = head;
	system("cls");
	printf("����Ҫɱ���Ľ�������:");
	scanf("%s",name);
	getchar();
	p = p->next;
	//�����鿴�������Ƿ��н���name�Ľ���
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
		printf("�˽��̲�����\n");
		return;
	}
	Delete(head,p);
	printf("������ֹ�ɹ�");
	run(head);
}
void ShowPCB(PCB *head)
{
	//���������̱��
	int ready = 1;
	//�����н��̱��
	int run = 1;
	//���������̱��
	int block = 1;

	PCB *p = head,*q;
	system("cls");
	printf("---------------------��ʾ����--------------------------\n"); 
	printf("======================================================\n");
	if(p->next == NULL)
	{
		printf("��ǰϵͳ��û�н��̣����ȴ���");
		//system("PAUSE")? ����ͣ����˼��
		//�ȴ��û��źţ���Ȼ����̨�����һ��������
		//������������ִ�н����
		system("pause");
		return;
	}
	//�г������б�
	q = p->next;
	printf("-----------��������-----------\n");
	while(q)
	{
		if(q->P_status == '2')
		{
			//������
			printf("%d 	��������%s",ready++,q->P_name);
			//���ȼ�
			printf("	���ȼ���%c",q->P_por);
			printf("	����ʱ�䣺%d",q->P_runtime);
			printf("	�ȴ�ʱ�䣺%d",q->P_wait);
			putchar(10);
		}
		q = q->next;
	}
	putchar(10);

	// �г����ж����б�
	q = p->next;
	printf("-----------���н���-----------\n");
	while(q)
	{
		if(q->P_status == '1')
		{
			//������
			printf("%d 	��������%s",run++,q->P_name);
			//���ȼ�
			printf("	���ȼ���%c",q->P_por);
			printf("	����ʱ�䣺%d",q->P_runtime);
			printf("������ʱ��");
			putchar(10);
		}
		q = q->next;
	}
	putchar(10);

	q = p->next;
	printf("-----------��������-----------\n");
	while(q)
	{
		if(q->P_status == '0')
		{
			//������
			printf("%d 	��������%s",block++,q->P_name);
			//���ȼ�
			printf("	���ȼ���%c",q->P_por);
			printf("	����ʱ�䣺%d",q->P_runtime);
			printf("	�ȴ�ʱ�䣺%d",q->P_wait);
			putchar(10);
		}
		q = q->next;
	}
	putchar(10);

	
	printf("===============================\n");
	printf("----------������ʾ���--------------\n"); 
	system("pause");
	
}
int main()
{
	
	PCB * head;
	//ͷ�ڵ�Ϊ��
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
		//����ѡ�� 
		int choice;
		Menu();
		printf("���������ѡ��0-5):");
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