#include <stdio.h>
#include <string.h>
#include <malloc.h>
#define N 100
#define M 2*N-1 

typedef struct {
	char name;
	int weight;
	int parent;
	int Lchild;
	int Rchild;
}HNode ,HuffmanTree[N+1];
typedef char * HuffmanCode [N+1];

void select (HuffmanTree ht,int n, int *s1,int *s2);
void CrtHuffmanTree(HuffmanTree ht , int *w, int n,int *s);
void CrtHuffmanCode(HuffmanTree ht,HuffmanCode hc,int n);
void print(HuffmanCode hc,HuffmanTree root,int n);
void HuffmanTranslateCoding(HuffmanTree root, int n,char* ch);
     
int main(){
	FILE *pf;
	char s[N];
	int logo = 0; 
	int n;
	int m[M],lan[M];
	HuffmanTree root;
	HuffmanCode hc;
	char tran[100];
	int qw = 1;
	int i,j,up[26]={0},down[26]={0};
	pf = fopen("D:\\huffman.txt","r");//以只读的方式打开文件 
	fread(s,100,1,pf);
	s[100] = '\0';
	printf("文本中的内容:");
	puts(s);//将文件中的数据输出 
	fclose(pf); 
    for(i=0;i<N && s[i]!=0;i++) { //记录文本中各个字符出现的次数 
       if(s[i]>='A' && s[i]<='Z') {
          up[ s[i]-'A' ]++;//大写字母 
      }
       else if(s[i]>='a' && s[i]<='z') {
          down[ s[i]-'a' ]++;//小写字母 
      }
    }
    printf("文本中各个字符出现的次数为：\n");
    for(i=0;i<26;i++) {
       if(up[i]!=0){
          printf("%c------%d\n",i+'A',up[i]);
          logo++;
      }
       if(down[i]!=0){
          printf("%c------%d\n",i+'a',down[i]);
          logo++;
      }
    }
	for(i=0;i<26;i++) {//将up[]和dowm[]中的值赋给m[] ，且m的下标从1开始 
       if(up[i]!=0){
       	   lan[qw] = i+'A';
           m[qw] = up[i];
           qw++; 
       } 
       if(down[i]!=0){
       	 lan[qw] = i+'a';
         m[qw] = down[i];
         qw++;
       }
    }
    n = qw-1; //将字符种类的个数用n存储 
    printf("叶子结点的个数为：%d\n",qw-1); 
	CrtHuffmanTree(root,m,n,lan);//建立哈夫曼树 
	for (i = 1;i<=(2*n-1);i++){//打印哈夫曼树的二叉链表 
	    printf("%c",root[i].name);
        printf("%5d",root[i].weight);
        printf("%5d",root[i].parent);
        printf("%5d",root[i].Lchild);
        printf("%5d\n",root[i].Rchild);
    }
    printf("各个结点对应的哈夫曼编码应该是：\n");
    CrtHuffmanCode(root,hc,n);//哈夫曼译码 
    print(hc,root,n);//将哈夫曼编码打印
	printf("\n输入要译码的二进制数字:"); //译码过程
    gets(tran);
    HuffmanTranslateCoding(root, n, tran);
	return 0;
} 

void select (HuffmanTree ht,int n, int *s1,int *s2){
	int i;
	int min1 = 900 ,min2 = 900 ;
	int logo1,logo2;
	for(i = 1;i<= n;i++){
		if((min1 > ht[i].weight)&&(ht[i].parent==0)){
		   min1 = ht[i].weight;
		   logo1 = i;
	    }
	}
	for (i = 1;i <= n; i++){
		if ((min2 > ht[i].weight)&&(i != logo1)&&(ht[i].parent==0)){
		   min2 = ht[i].weight;
		   logo2 = i;
	    }
	}
	*s1 = logo1;
	*s2 = logo2;
}

void CrtHuffmanTree(HuffmanTree ht , int *w, int n,int *s){
	int m;
	m = 2*n-1;
	int i,s1,s2;
	for(i =1;i<=n;i++)
	printf("%c",s[i]); 
	printf("哈夫曼表格为：\n");
	for ( i = 1 ; i <=n ; i++){
		ht[i].name = s[i];
    	ht[i].weight = w[i];
    	ht[i].parent = 0;
    	ht[i].Lchild = 0;
    	ht[i].Rchild = 0;
    }
    for (i = n+1 ; i<= m;i++){
    	ht[i].name = 1;
    	ht[i].weight = 0;
    	ht[i].parent = 0;
    	ht[i].Lchild = 0;
    	ht[i].Rchild = 0;
	}
	for(i = n+1;i<=m;i++){
	    select (ht,i-1,&s1,&s2);
	    ht[i].weight = ht[s1].weight+ht[s2].weight;
	    ht[i].Lchild = s1;
	    ht[i].Rchild = s2;
	    ht[s1].parent = i;
	    ht[s2].parent = i;
	}
}

void CrtHuffmanCode(HuffmanTree ht,HuffmanCode hc,int n){
	char *cd;
	int start;
	int i,c,p;
	cd = (char *)malloc (n*sizeof(char));
	cd[n-1] = '\0';
	for(i = 1;i <= n; i++){
		start = n-1;
		c = i;
		p = ht[i].parent;
		while(p!=0){
			--start;
			if(ht[p].Lchild == c)
			   cd[start] = '0';
			else 
			   cd[start] = '1';
			c = p;
			p = ht[p].parent; 
		}
		hc[i] = (char *)malloc((n-start)*sizeof(char));
		strcpy(hc[i],&cd[start]);
	}
	free(cd);
}

void print(HuffmanCode hc,HuffmanTree root,int n){
	int i;
	for(i=1;i<=n;i++){
        printf("%c------%s\n",root[i].name,hc[i]);
    }
	  
}

void HuffmanTranslateCoding(HuffmanTree root, int n,char* ch){
    int m=2*n-1;
    int i,j=0;

    printf("译码结果:");
    while(ch[j]!='\0')//ch[]:你输入的要译码的0101010串
    { 
        i=m;
        while(0 != root[i].Lchild && 0 != root[i].Rchild)//从顶部找到最下面
        {
            if('0' == ch[j])//0 往左子树走
            {
                i=root[i].Lchild;
            }
            else//1 往右子树走
            {
                i=root[i].Rchild;
            }
            ++j;//下一个路径
        }
        printf("%c",root[i].name);//打印出来
    }
    printf("\n");
}
