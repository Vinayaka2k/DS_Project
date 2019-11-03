#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<time.h>

typedef struct node
{
int key;
struct node* prev;
struct node* next;
}NODE;


typedef struct record
{
NODE* pnode;
}RECORD;


typedef struct hash_table
{
RECORD htb[1000];
}HT;


void queue_init(NODE** h)								// initialise the queue
{
*h=NULL;
}


void ht_init(HT* pht)									// initialise the Hash-Table
{
for(int i=0;i<1000;++i)
	{
	pht->htb[i].pnode=NULL;
	}
}


NODE* prepend(NODE** h,int ele)							// Enqueue an element ele into the queue
{
NODE* temp=(NODE*)malloc(sizeof(NODE));
temp->key=ele;
if(*h == NULL)
	{
	*h=temp;
	temp->next=NULL;
	temp->prev=NULL;
	return temp;
	}
temp->prev=NULL;
temp->next=*h;
(*h)->prev=temp;
*h=temp;
return temp;
}


int del_last(NODE** h,int* pe)							// Dequeue an element from the queue
{
NODE* p;
p=*h;
if(*h == NULL)
	return 0;
if((*h)->next==NULL)
	{
	*pe=(*h)->key;
	free(p);	
	*h=NULL;
	return 1;
	}
while(p->next != NULL)
	{
	p=p->next;	
	}
*pe=p->key;
p->prev->next=NULL;
free(p);
return 1; 
}


void disp(NODE** h)								// Display all elements of the queue
{
NODE* p;
p=*h;
printf("The contents of the Cache:\n");
while(p!=NULL)
	{
	printf("%d ",p->key);
	p=p->next;
	}
printf("\n \n");
}


int search(NODE** h,int ele)							// Search for a given element ele in the queue
{
if(*h == NULL)
	return 0;
NODE* p;
p=*h;
while(p!=NULL)
	{
	if(p->key==ele)
		return 1;
	p=p->next;
	}
return 0;
}


int del(NODE** h,int ele)							// Delete an element ele from the queue					
{
if(*h==NULL)	
	return 0;
NODE *p;
p=*h;
if(p->prev==NULL && p->next==NULL && p->key==ele)
	{
	free(p);
	*h=NULL;	
	return 1;	
	}
if(p->prev==NULL && p->key==ele)
	{
	(*h)=(*h)->next;
	(*h)->prev=NULL;
	free(p);
	return 1;
	}
while(p!=NULL && p->key!=ele)
	{
	p=p->next;
	}
if(p==NULL)
	return 0;	
if(p->key==ele)
	{
	if(p->next==NULL)
		{
		p->prev->next=NULL;
		free(p);
		return 1;
		}
	else
		{
		p->prev->next=p->next;
		p->next->prev=p->prev;
		free(p);
		return 1;
		}
	}
}


int length(NODE** h)								// Get the Number of elements in the (cache size)
{
int cnt=0;
NODE* p;
p=*h;
if(*h==NULL)
	return 0;
while(p!=NULL)
	{
	p=p->next;
	++cnt;
	}
return cnt;
}


void lru_cache(NODE** h,int ele,int capacity,HT* pht,int* phit,int* pmiss)					

// function to compute Cache Hit/ Cache Miss and Hash the address of the nodes present in the Cache into a Hash Table.
													
{															 								
static int k=1,hit=0,miss=0;
printf("%d. CURRENT ELEMENT: %d\n",k++,ele);
NODE* ptr;
int del_ele;
if(search(h,ele))							//cache hit
	{
	del(h,ele);
	ptr=prepend(h,ele);
	pht->htb[ele].pnode=ptr;	
	printf("CACHE HIT\n");
	++hit;
	}

else									//cache miss
	{
	if(length(h)<capacity)					//cache miss when cache is not full	
		{
		ptr=prepend(h,ele);
		pht->htb[ele].pnode=ptr;
		}
	else								//cache miss when cache is full
		{
		del_last(h,&del_ele);
		pht->htb[del_ele].pnode=NULL;
		ptr=prepend(h,ele);
		pht->htb[ele].pnode=ptr;
		}
	printf("CACHE MISS\n");	
	++miss;
	}
*phit=hit;
*pmiss=miss;
}

void print_ht(HT* pht)										// Print the contents of Hash Table
{
printf("HASH TABLE FOR CACHE:\n\nindex: \t\t\t address of the ele in Cache:\n");
for(int i=0;i<1000;++i)
	{
	if(pht->htb[i].pnode)
		printf(" %d \t\t\t %p\n",i,pht->htb[i].pnode);
	}
}

void main()
{
clock_t begin=clock();
int hit,miss;
int capacity,j,i=0,val;
HT ht;
RECORD r;
NODE* head;
ht_init(&ht);
queue_init(&head);

printf("Enter the capacity for the Cache:\n");
scanf("%d",&capacity);
printf("\n");

FILE* fp;						// Reading from the file a.txt and splitting the page numbers 
char* tok;						// using the function 'strtok' based on the delimiter 'space'
char str[50];
fp=fopen("a.txt","r");
while(fgets(str,100,fp)!=NULL)
	{
	tok=strtok(str," ");
	val=atoi(tok);
	lru_cache(&head,val,capacity,&ht,&hit,&miss);
	disp(&head);
	}
fclose(fp);
print_ht(&ht);
printf("\nHIT RATE: %f percent \nMISS RATE: %f percent \n",(float)hit/10,(float)miss/10);		// Hit Rate and Miss Rate

clock_t end=clock();
printf("Time taken for the whole program: %f sec\n",(double)(end-begin)/CLOCKS_PER_SEC);    	// Time taken for execution
}



























