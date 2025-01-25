#pragma once
//��ֹͷ�ļ��ظ�����

/*
ѧ���ṹ
*/
//�洢һ��
typedef struct Student
{
	unsigned long long number;
	char name[32];
	float score;
}Student;


//�洢��������ݽṹ��֯��������
/*
�ڵ�Node
*/
typedef struct Node 
{
	Student stu;	  //ѧ��
	struct Node* next;//ָ����һ������ָ�루ע�⣺��ʱ����ֱ���ñ���Node������Ҫд����struct Node����Ϊ��ʱ���������}��д�������Ŷ����꣩
}Node;


/*
����
*/
typedef struct List
{
	Node* front;//ͷָ�룺ָ���һ�����
	int size;	//��ǰ�������
}List;



/*
�˵�����
*/
typedef enum MenuOptions
{
	Quit,//�˳�ϵͳ
	Entry,
	Search,
	Remove,
	Print,
	Read,
	Save
}MenuOptions;


/*��ӡ�˵�������ʾ�û�ѡ����*/
int menu();


/*
ѧ��¼��
*/
void entryStudent(List* list);//����main�ļ��ж���Ĳ���

/*
��ӡѧ��
*/
void printStudent(List* list);

/*
����ѧ��(�Զ����Ƶķ�ʽ���棺���ļ����������������)
*/
void saveStudent(List* list);

/*
����ѧ�����������ܿ����ķ�ʽ���棩
*/
void saveStudentHuman(List* list);

/*
����ѧ�������ؽ�㣩
*/
Node* searchStudent(List* list);

/*
ɾ��ѧ��
*/
void removeStudent(List* list);

/*
��ȡѧ��(�������ļ�)
*/
void readStudent(List* list);

/*
��ȡѧ��(�ܶ�����)
*/
void readStudentHuman(List* list);

