#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<malloc.h>
typedef int ElemType;
typedef struct person {
	char num[10];//编号 
	char name[10];//姓名 
	char sex[10];//性别 
	char phone[10];//电话 
}personal;/*={};测试*/
typedef struct node
{
	person data;//数据域 
	struct node * next;//指针域 
}ListNode, *LinkList;
LinkList InitList();
LinkList Create(LinkList head);
void List(LinkList head);//显示所有记录 
void save(LinkList head);//保存到文件 
void Find(LinkList head);//按要求查找 
int GetLength(LinkList head);//总记录条数 
void Add(LinkList head);//增加新的记录 
void Alter(LinkList head);//修改 
void Delete(LinkList head); //删除 
void Statis_sex(LinkList head);//性别个数 
void Quit();//退出选单 
void Menu(LinkList head);//选单
//Creat模块已通过读取文件信息实现 
LinkList InitList()
{
	LinkList head = (LinkList)malloc(sizeof(ListNode));//创立头结点
	if (head == NULL)
	{
		printf("空间分配无效!");
		exit(-1);//退出程序
	}
	head->next = NULL;
	return head;
}
LinkList Create(LinkList head)
{
	person LM;//接受文件数据 
	LinkList rear;
	rear = head;
	FILE *fp = fopen("file.txt", "r");
	if (fp == NULL)
	{
		printf("打开文件失败!");
		return NULL;
	}

	while (fscanf(fp, "%s%s%s%s", LM.num, LM.name, LM.sex, LM.phone) != EOF)//处理到文件尾 
	{
		LinkList s = (LinkList)malloc(sizeof(ListNode));
		s->data = LM;
		s->next = NULL;
		rear->next = s;
		rear = s;
	}
	fclose(fp);
	return head;
}
void List(LinkList head) {
	LinkList p;
	p = head->next;
	if (!p) //如果head指针为空说明链表为空
	{
		printf("\n链表为空！\n\n");
	}
	else
	{
		printf("\n通信录：\n\n");
		printf("编号	姓名	性别	电话 \n");
		while (p)  //循环将各个节点值输出
		{
			printf("%s\t%s\t%s\t%s\n", p->data.num, p->data.name, p->data.sex, p->data.phone);//打印
			p = p->next;//此句放在打印后面，防止产生野指针 
		}
		Statis_sex(head);
		printf("\n返回主菜单\n");
		system("pause");//页面停留
		Menu(head);
	}
}
void save(LinkList head)
{
	LinkList rear;
	person LM;
	rear = head->next;//跳过头节点 
	FILE *fp;
	int i;
	if ((fp = fopen("file.txt", "wb")) == NULL)/*只打开或建立一个二进制文件，只允许写数据*/
	{
		printf("\n文件不存在!\n");
	}
	while (rear)//处理到文件尾 
	{
		LM = rear->data;
		fprintf(fp, "%s\t%s\t%s\t%s\n", LM.num, LM.name, LM.sex, LM.phone);
		rear = rear->next;
	}
	fclose(fp);
}
void Find(LinkList head)
{
	int Loop = 0;
	char name[10];
	printf("请输入要查询联系人的姓名[     ]\b\b\b\b\b\b");
	scanf("%s", name);
	LinkList rear = head->next;
	while (rear)
	{
		if (strcmp(rear->data.name, name) == 0)
		{
			printf("编号	姓名	性别	电话 \n");
			printf("%s\t%s\t%s\t%s\n", rear->data.num, rear->data.name, rear->data.sex, rear->data.phone);
			Loop = 1;
		}
		rear = rear->next;
	}
	if (Loop == 1)
	{
		printf("\n查询联系人成功!返回菜单\n");
		system("pause");
		Menu(head);
	}
	else
	{
		int n;
		printf("无此联系人!!!\n\n返回菜单(1) or 重新输入(2)[  ]\b\b\b");
		scanf("%d", &n);
		printf("\n");
		switch (n)
		{
		case 1:system("cls"); Menu(head); break;
		case 2:system("cls"); Find(head); break;
		}
	}
}
int GetLength(LinkList head)
{
	LinkList p = head->next;
	int i = 0;
	while (p)
	{
		i++;
		p = p->next;

	}
	return i;
}//获取链表长度 
void Add(LinkList head)
{
	char c;
	person LM;
	LinkList p = head;
	printf("请输入新建联系人的信息\n\n编号	/姓名	/性别	/电话号码：\n");
	do
	{
		scanf("%s", LM.num);
		scanf("%s", LM.name);
		scanf("%s", LM.sex);
		scanf("%s", LM.phone);
		LinkList s = (LinkList)malloc(sizeof(ListNode));
		s->data = LM;
		s->next = NULL;
		while (p->next)
		{
			p = p->next;
		}
		p->next = s;
		save(head);
		printf("是否继续添加 y/n\n");
		scanf(" %c", &c);
	} while (c == 'y' || c == 'Y');
	printf("\n返回主菜单\n");
	system("pause");
	Menu(head);
}
void Alter(LinkList head)
{
	int loop = 0;
	int n;
	char name[10];
	printf("请输入要查询联系人的姓名 [     ]\b\b\b\b\b\b");
	scanf("%s", name);
	printf("\n");
	LinkList rear = head->next;
	while (rear)
	{
		if (strcmp(rear->data.name, name) == 0)
		{
			printf("请输入要修改的内容:(1)编号 (2)姓名 (3)性别 (4)电话号码 (5)全部信息 [ ]\b\b");//printf("%s\t%s\t%s\t%s\n",rear->data.num,rear->data.name,rear->data.sex,rear->data.phone);
			scanf("%d", &n);
			printf("\n");
			switch (n)
			{
			case 1: printf("请输入修改后的编号："); scanf("%s", rear->data.num); break;
			case 2: printf("请输入修改后的姓名："); scanf("%s", rear->data.name); break;
			case 3: printf("请输入修改后的性别："); scanf("%s", rear->data.sex); break;
			case 4: printf("请输入修改后的电话号码"); scanf("%s", rear->data.phone); break;
			case 5: printf("请输入要修改联系人的信息: \n\n编号	姓名	性别	电话号码：\n");
				scanf("%s", rear->data.num);
				scanf("%s", rear->data.name);
				scanf("%s", rear->data.sex);
				scanf("%s", rear->data.phone); break;
			}
			system("cls");
			loop = 1;
		}
		rear = rear->next;
	}
	if (loop == 0)
	{
		printf("无此联系人!!!\n\n返回菜单(1) or 重新输入(2)[  ]\b\b\b");
		scanf("%d", &n);
		printf("\n");
		switch (n)
		{
		case 1:system("cls"); Menu(head); break;
		case 2:system("cls"); Alter(head); break;
		}
	}
	save(head);
	printf("\n修改成功!返回菜单\n");
	system("pause");
	Menu(head);
}
void Delete(LinkList head)
{
	LinkList rear = head;//用来找要删除节点的前一节点 
	LinkList p = rear->next;//用来找要删除节点
	char name[10];
	int Loop = 0, n;
	printf("请输入要删除联系人的姓名:[    ]\b\b\b\b\b");
	scanf("%s", name);
	printf("\n");
	while (p)
	{
		if (strcmp(p->data.name, name) == 0)
		{
			rear->next = p->next;
			free(p);
			save(head);
			Loop = 1;
		}
		rear = p;
		p = p->next;
	}
	if (Loop == 1)
	{
		printf("\n删除联系人成功!返回菜单\n");
		system("pause");
		Menu(head);
	}
	else
	{
		printf("无此联系人!!!\n\n返回菜单(1) or 重新输入(2)[  ]\b\b\b");
		scanf("%d", &n);
		printf("\n");
		switch (n)
		{
		case 1:system("cls"); Menu(head); break;
		case 2:system("cls"); Delete(head); break;
		}
	}
}
void Statis_sex(LinkList head)
{
	int i = 0;//记录男性数目 
	int j = GetLength(head);//获取总记录数 
	LinkList rear = head->next;
	char sex[10] = "man";
	while (rear)
	{
		if (strcmp(rear->data.sex, sex) == 0)
			i++;
		rear = rear->next;
	}
	printf("\n通信录中男性有 %d 人，有女性 %d 人。\n", i, j - i);
}
void Quit()
{
	printf("\n\t                         ★ ★ ★ ★ ★ ★ ★ ★ ★ ★ ★ ★ ★ ★ ★ ★ ★ ★\n\n");
	puts("\n");
	puts("\t                             ┃                                               ┃");
	puts("\t                             ┃                                               ┃");
	puts("\t                             ┃     感谢访问通信录管理系统!欢迎下次再来!      ┃");
	puts("\t                             ┃                                               ┃");
	puts("\t                             ┃                                               ┃");
	puts("\t                             ┃                  制作人：追足梦幻                ┃");
	puts("\t                             ┃                          2020.7.3             ┃ ");
	puts("\n ");

}
void Menu(LinkList head)
{
	int n;
	int choice = 0;
	do
	{
		system("cls");
		printf("\n");
		printf("                                              ---通讯录管理系统---\n");
		puts("\n");
		printf("                                             1/按姓名查询联系人信息\n");
		puts("\n");
		printf("                                             2/  新建联系人\n");
		puts("\n");
		printf("                                             3/修改联系人信息\n");
		puts("\n");
		printf("                                             4/ 删除联系人信息\n");
		puts("\n");
		printf("                                             5/显示所有联系人信息\n");
		puts("\n");
		printf("                                             6/     退出\n");
		puts("\n");
		printf("                                          请选择服务种类(1-6) : [ ]\b\b");
		scanf("%d", &n);
		if (n < 1 || n>6)
		{
			system("cls");
			printf("选择错误!  请重新选择!\n");
			system("pause");
			choice = 1;
		}
		else
		{
			break;
		}
	} while (choice == 1);

	switch (n)
	{
	case 1:system("cls"); Find(head); break;//Find函数查询 
	case 2:system("cls"); Add(head); break;//Add函数新建联系人 
	case 3:system("cls"); Alter(head); break;//Alter修改联系人信息 
	case 4:system("cls"); Delete(head); break;//Delete删除联系人信息 
	case 5:system("cls"); List(head); break;//List显示所有信息 
	case 6:system("cls"); Quit(); break;//退出 
	}
}
int main()
{
	LinkList head = InitList();
	head = Create(head);
	printf("\n信息录入成功！");
	system("pause");
	Menu(head);
}
