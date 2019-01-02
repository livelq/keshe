#include<stdio.h>
#include<stdlib.h>
#define M 10000
#define MAXVEX 20
#define INF 32767
typedef struct node
{
	int num;
	char name[20];
	struct node *next;
}Node;
int visited[30];
int way[30];
int n=30;


void show()
{
	printf("                                   长思公寓-----旭日苑-----长智公寓               \n"); 
	printf("                                            |          |  \\    |         \n"); 
	printf("                                            |          |   \\   |         \n"); 
	printf("                  -------西邮桥-----------大操场       |    \\  |         \n"); 
	printf("                  |                         |          |    小操场      \n"); 
	printf("                  |                         |          |      /\n"); 
	printf("                东升苑                    体育馆       |     / \n"); 
	printf("                  |                               \     |    /  \n"); 
	printf("                  |                                \    |   /   \n"); 
	printf("                  |                                  图书馆      \n"); 
	printf("                  |                                  / |   \\  \n"); 
	printf("                  |                                 /  |    \\ \n"); 
	printf("                  |                            情人湖  |     \\ \n"); 
	printf("                  |                              |     |      \\ \n"); 
	printf("             东区宿舍楼                          |     |       实验楼群\n"); 
	printf("                  |                            大活    |          | \n"); 
	printf("                  |                               \\    |          | \n"); 
	printf("                  |                                \\   |          | \n"); 
	printf("                  |                        行政楼----水煮鸽子------西区教学楼\n"); 
	printf("                  |                           \        |              /     \n"); 
	printf("                  |                            \       |             /      \n"); 
	printf("                  |                             \      |            /       \n"); 
	printf("              东区教学楼--------------------------西邮正门----------         \n"); 
	printf("                  |                                                \n"); 
	printf("                  |                                                \n"); 
	printf("              东区操场                                                  \n"); 
} 

void Dijkstra(int a[][30],int start,int n,int dist[],int path[][MAXVEX])
{
int mindist,i,j,k,t=1;
	
	for(i=0;i<=MAXVEX;i++)
	{
		for(j=0;j<=MAXVEX;j++)
		{
			path[i][j]=0;
		}
	}
	
	for(i=0;i<=MAXVEX;i++)
	{
		dist[i]=INF;
	}
	
	for(i=1;i<=n;i++)
	{
		dist[i]=a[start][i];
		if(a[start][i]!=INF)
		{
			path[i][1]=start;
		}
	}
	
	path[start][0]=1;
	
	for(i=2;i<=n;i++)
	{
		mindist=INF;
		for(j=1;j<=n;j++)
			if(!path[j][0]&&dist[j]<mindist)
			{
				k=j;
				mindist=dist[j];
			}
			
			
			if(mindist==INF)
			return;
			
			path[k][0]=1;
			for(j=1;j<=n;j++)
			{
				if(!path[j][0]&&a[k][j]<INF&&dist[k]+a[k][j]<dist[j])
				{
					dist[j]=dist[k]+a[k][j];
					t=1;
					while(path[k][t]!=0)
					{
						path[j][t]=path[k][t];
						t++;
					}
					path[j][t]=k;
					path[j][t+1]=0;
				}
				
			}
	}
} 


void map(int a[][30])
{
	FILE *fp=fopen("a.txt","r");  
	int i,j;
    for(i=0;i<30;i++)  
    {  
    	for(j=0;j<30;j++)  
    	{  
            fscanf(fp,"%d\t",&a[i][j]);/*每次读取一个数，fscanf函数遇到空格或者换行结束*/  
        }  
        fscanf(fp,"\n");  
    }  
    fclose(fp);  
}

void read(Node *head)
{
	FILE* fp=fopen("地点.txt","r"); //打开文件  
    if(fp==NULL)  
    {  
        printf("无文件"); 
		return; 
    }
	Node *p1,*p2;
	head->next=NULL;
	while(!feof(fp))
	{
		p1=(Node*)malloc(sizeof(Node));
		fscanf(fp," %d %s",&p1->num,p1->name);
		if(head->next==NULL)
		{
			head->next=p1;
			p2=p1;
		}
		else
		{
			p2->next=p1;
			p2=p1;
		}
	}
	fclose(fp);

}

void showways(int a[][30],int vi,int vj,int path[],int i,Node *head)//利用邻接矩阵求  
{  
	Node *p1;
    visited[vi]=1;//标记该点  
    int j;  
    path[i] = vi;//存入路径  
    for(j=1;j<=19;j++)//遍历邻接点  
    { 
	
        if(a[vi][j]!=INF)  
        {  
            if(j==vj)//满足到顶点v  
            {  
                path[i+1]=j;  
                int k;  
                for(k=1;k<=i+1;k++)
				{
					p1=head; 
					while(p1->num!=path[k])
						p1=p1->next;
					printf("%s ",p1->name); //输出一组路径 
					if(i+1<n)
					{
						n=i+1;
						for(int m=0;m<20;m++)
						{
							way[m]=path[m];
						}
					}    
				}
                printf("\n");  
            }  
            else if(j!=vj&&visited[j]==0){  
               showways(a,j,vj,path,i+1,head);  
            }  
        }  
    }  
    visited[vi]=0;//取消标记  
} 

int search(Node *head,int n)
{
	Node *p1=head;
	while(p1->num!=n)
	{
		p1=p1->next;
	}
	return p1->num;
}

void FindSimpleWay(int a[][30],Node *head)
{
	Node *p1;
	printf("查询简单路径：\n");
	int path[20]={0};
	int x,y;
	printf("请输入起点序号：");
	scanf("%d",&x); 
	printf("请输入终点序号：");
	scanf("%d",&y);
	x=search(head,x);
	y=search(head,y);
	
	printf("所有简单路径为：\n");	
	showways(a,x,y,path,0,head);
	printf("\n");
	
	p1=head;
	while(p1->num!=x)
		p1=p1->next;
	printf("最短简单路径为：%s ",p1->name);
	for(int m=1;m<=n;m++)
	{
		p1=head;
		while(p1->num!=way[m])
			p1=p1->next;
		printf("%s ",p1->name);
	}
	printf("\n");
}


int main(void)
{
	int a[30][30]={0};
	int i,j;
	char v;
	
	int dist[MAXVEX],v0;
	int path2[MAXVEX][MAXVEX]={0};
	int x,y,m;
	
	Node *head=(Node*)malloc(sizeof(Node));
	Node *p1,*p2;
	head->next=NULL;
	read(head);
	map(a);
	show();	
	FindSimpleWay(a,head);
	printf("\n");
	
	printf("查询最短路径：\n");
	printf("请输入起点序号：");
	scanf("%d",&x); 
	printf("请输入终点序号：");
	scanf("%d",&y);
	x=search(head,x);
	y=search(head,y);
	Dijkstra(a,x,19,dist,path2);
	
	for(int m=1;m<18;m++)
	{
		p1=head;
		while(p1->num!=path2[y][m]&&p1!=NULL&&path2[y][m]!=0)
		{
			p1=p1->next;
		}
		if(p1&&path2[y][m])
		{
			printf("%s ",p1->name);
		}
	} 
	p1=head;
	while(p1->num!=y&&p1)
	{
		p1=p1->next;
	}
	printf("%s ",p1->name);
	
	return 0;
}



