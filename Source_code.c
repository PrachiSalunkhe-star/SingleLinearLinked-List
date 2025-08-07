#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef struct node{
	int rollno;
	char name[50];
	float marks;
	struct node *next;
}node_t;

typedef struct list{
	node_t *head;
	node_t *tail;
}list_t;

void initList(list_t *list)
{
	list->head = list->tail = NULL;
}

void freeList(list_t *list)
{
	node_t *trav = list->head;
	while(trav != NULL)
	{
		node_t *temp = trav;
		trav = trav->next;
		free(temp);
	}
	list->head = list->tail = NULL;
}

int isEmpty(list_t *list)
{
	return list->head == NULL && list->tail == NULL;
}
void deleteLast(list_t *list)
{
	//1. if list is empty, do nothing
	if(list->head == NULL)
		return;
	//2. if list has single node
	if((list->head)->next == NULL){
		//a. release space of single node
		free(list);
		//b. add NULL into head
		list->head = NULL;
	}
	//3. if list has multiple nodes
	else{
		//a. traverse till second last node
		struct node *trav = list->head;
		while(trav->next->next != NULL)
			trav = trav->next;
		//b. release space of last node
		free(trav->next);
		//c. add NULL into next of second last node
		trav->next = NULL;
	}
}

node_t *createNode(int no, char *name, float marks)
{
	node_t *newnode = (node_t *)malloc(sizeof(node_t));
	newnode->rollno =no;
	strcpy(newnode->name, name);
	newnode->marks= marks;
	newnode->next = NULL;
	return newnode;
}

void add(list_t *list, int no, char *name,  float marks)
{
	node_t *newnode = createNode(no, name,marks);
	if(isEmpty(list))
		list->head = list->tail = newnode;
	else{
		newnode->next = list->head;
		list->head = newnode;
	}
}


void display(list_t *list)
{
	node_t *trav = list->head;
	printf("Student List : \n");
	while(trav != NULL)
	{
		printf("%d %s %.2f\n", trav->rollno, trav->name, trav->marks);
		trav = trav->next;
	}
}


int count(list_t *list)
{
	node_t *trav = list->head;
	printf("Student : \n");
	int count=0;
	while(trav != NULL)
	{
		count++;
		trav = trav->next;
	}
	return count;
}



void delete(list_t *list,int rollno)
{
	
	node_t *trav = list->head;
	if(trav == NULL)
	   return;

	int count=1;
	while( trav->next != NULL)
	{
	  	
		
		if(trav->rollno==rollno)
		{
			break;
		}
		count++;
		trav = trav->next;
	}
	deletePosition(list,count);
	
	
}

void deletePosition(list_t *list, int pos)
{

	if(pos <= 0)
		return;
	//1. if list is empty
	if(list->head == NULL)
		return;
	// special case 2 : pos = 1
	else if(pos == 1){
		struct node *temp = list->head;
		list->head = list->head->next;
		free(temp);
	}
	else if(pos==count)
		{ deleteLast(list);}
	//2. if list is not empty
	else{
		//a. traverse till pos - 1 node
		struct node *trav = list->head;
					// special case 3 : pos > nodeCount
		for(int i = 1 ; i < pos - 1 && trav->next != NULL ; i++)
			trav = trav->next;
		if(trav->next == NULL)
			return;
		//b. take backup of pos node
		struct node *temp = trav->next;
		//c. add pos + 1 node into next of pos - 1 node
		trav->next = temp->next;
		//d. release space of pos node
		free(temp);
	}
}
void search(list_t *list, int rollno)
{
	node_t *trav = list->head;
	while(trav!=NULL)
	{
		if(rollno==trav->rollno)
		{
			printf("%d %s %.2f\n", trav->rollno, trav->name, trav->marks);
			return;
		}
		trav = trav->next;
	}
	printf("Student  is not found\n");
}

void edit(list_t *list,int rollno,float marks)
{
	
	node_t *trav = list->head;
	while(trav != NULL)
	{
		if(rollno==trav->rollno)
		{
			trav->marks=marks;
		
		}
		trav = trav->next;
	}


}

int main(void)
{
	list_t List;
	int num;
	char name[50];
	float marks;	
	int ch;

	initList(&List);
	do{
	printf("\n0.exit\n1.add student\n 2.display all students\n 3.search student by rollno\n 4.Delete student by rollno\n 5.edit marks of student\n");
	printf("Enter Choice:");
	scanf("%d",&ch);

	
	
	switch(ch)
	{
		case 0:
			break;
		case 1:
			printf("\n Enter rollno name marks:");
			scanf("%d%s%f",&num,&name,&marks);
			add(&List,num,name,marks);
			break;
		case 2:
			display(&List);
			break;
		case 3:
			printf("Enter Rollno:");
			scanf("%d",&num);
			search(&List,num);
			break;
		case 4:
			printf("Enter rollno:");
			scanf("%d",&num);
			delete(&List,num);
			break;
		case 5:
			printf("Enter Rollno:");
			scanf("%d",&num);
			printf("Enter marks:");
			scanf("%f",&marks);
			edit(&List,num,marks);
			break;
	}
	}while(ch!=0);

			 
	

	freeList(&List);

	return 0;
}



	
