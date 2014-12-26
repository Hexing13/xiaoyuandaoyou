//西邮校园导航系统
#include "stdio.h"
#include "stdlib.h"
#include "byebye.h"
#include "xiyou.h"
#include "denglu.h"
#include "welcom.h"
#include "menu1.h"
#include "menu2.h"
#include "map.h"
#include "password.h"
#define Max_num 50
#define INFINITY 32768

//顶点结构体
typedef struct
{
    int NO;  //地点序号
    char name[50]; //地点名
}Vextype;

//邻接矩阵结构体
typedef struct
{
    int arcs[Max_num+1][Max_num+1];  //边集
    Vextype vex[Max_num+1];   //顶点集
    int vexnum;    //顶点数目
    int arcnum;    //边数目
}AdjMatrix;


//根据地点名确定地点序号
int Locate(AdjMatrix *G, char name[]);
//采用邻接矩阵创建无向网
void Create_AdjMatrix(AdjMatrix *G);
//输出无向网矩阵
void Print_AdjMatrix(AdjMatrix *G);
//深度优先遍历所有景点
void DFSTrave(AdjMatrix G );
void DFS(AdjMatrix G, int i);
//添加新地点
void Add_Place();
//添加新路线
void Add_Route();
//撤销旧路线
void Del_Route();
//撤销旧地点
void Del_Place();
//采用prim算法求最短连通图
void Prim(AdjMatrix *G, int start);
//查询从某个景点出发的最短连通图
void Prim_MiniSpanTree(AdjMatrix *G);
//采用Dijkstra算法求单元点的最短路径
void Dijkstra(AdjMatrix *G, int start, int end, int dist[], int path[][Max_num+1]);
//查询任意两景点间的最短路径
void Dij_Short_Path();
//查询任意两景点间的所有路径
void All_Path(AdjMatrix *G);
//查询地点信息
void plcae();
//主菜单
void menu(AdjMatrix G);
//menu1菜单的对应功能
void switch1(AdjMatrix G);
//menu2菜单的对应功能
void switch2();
//存储信息
void Store(AdjMatrix *G);
//读取信息
AdjMatrix Read();

void menu(AdjMatrix G)
 { 
     int choice;

     choice = denglu();
    //管理员登陆
    if(choice == 1){
        password();
        sleep(1);
        menu1();
        switch1(G);
    }

    //客户登陆
    else if(choice == 2){
        menu2();
        switch2();
    }
    else if(choice == 0){
         byebye();
    }
    else{
        printf("\033[31m\t\t\t\t\t抱歉，不存在该登陆模式!\n\033[0m");
        exit(-1);
    }
}

int main()
{
    AdjMatrix G;
    G = Read();
    welcom();
    xiyou();
    menu(G);  

    return 0;
}


//根据地点名确定地点序号
int Locate(AdjMatrix *G, char name[])
{
    int i;
    for(i = 1; i <= G->vexnum; i++){
        //图中含有该景点，找到其序号
        if(!strcmp(G->vex[i].name, name))
            return i;
    }
    return -1;
}

//采用邻接矩阵创建无向网
void Create_AdjMatrix(AdjMatrix *G)
{
    int i, j, k, weight;
    char name1[50], name2[50];
    printf("\033[2J\033[3;0H\033[33m");
    printf("\t\t\t********************************   西  安  邮  电  大  学   ********************************\n\n\n\n");
    printf("\t\t\t\033[31m+\033[0m   创建新地图...\n\033[0m\n\n\n");
    printf("\t\t\t请输入学校中的景点数目和路径数目：");
    scanf("%d %d", &G->vexnum, &G->arcnum);

    //初始化边信息
    for(i = 1; i <= G->vexnum; i++){
        for(j = 1; j <= G->vexnum; j++){
            G->arcs[i][j] = INFINITY;
        }
    }

    //初始化顶点集合
    for(i = 1; i <= G->vexnum; i++){
        printf("\t\t\t请分别输入第NO.%d个景点序号和名字：", i);
        scanf("%d %s", &G->vex[i].NO, G->vex[i].name);
    }
    printf("\n\n");
    //建立边关系
    for(k = 1; k <= G->arcnum; k++){
        printf("\t\t\t请输入第NO.%d个相关联的两个景点名字和路径长度：", k);
        scanf("%s %s %d", name1, name2, &weight);
        i = Locate(G, name1);
        j = Locate(G, name2);
        G->arcs[i][j] = weight;
        G->arcs[j][i] = weight;
    }
    printf("\n\n\n\t\t\t\t\t创建新地图成功！\n\n");
    Store(G);
}

//输出无向网矩阵
void Print_AdjMatrix(AdjMatrix *G)
{

    int i, j;
    for(i = 1; i <= G->vexnum; i++)
        printf("%8s", G->vex[i].name);
    printf("\n\n");
    for(i = 1; i <= G->vexnum; i++){
        for(j = 1; j <= G->vexnum; j++){
            if(G->arcs[i][j] == INFINITY)
                printf("       #");
           else 
                printf("%8d", G->arcs[i][j]);
        }
        printf("\n");
    }
}

int visited[Max_num+1];
//深度优先遍历所有景点
void DFS(AdjMatrix G, int i)
{
    printf("%s ",G.vex[i].name);
    int j;
    visited[i] = 1;
    for(j = 1; j <= G.vexnum;j++){
        if(G.arcs[i][j] != INFINITY && visited[j] == 0)
            DFS(G, j);
    }
}

void DFSTrave(AdjMatrix G)
{
    int j;
    for(j = 1; j <= G.vexnum; j++)

        visited[j] = 0;
    for(j = 1; j <= G.vexnum; j++){
        if(visited[j] == 0){
            DFS(G, j);
        }
    }
}

//添加新地点
void Add_Place(AdjMatrix *G)
{
    char name[50];
    int i, j, m, num;

    printf("\033[2J\033[15;0H\t\t\t\t\t\033[31m+\033[0m   添加新地点...\n\n\n\n");
    printf("\t\t\t\t\t请输入要添加的景点的数目：");
    scanf("%d", &num);
    m = G->vexnum;
    G->vexnum += num;
    
    //初始化新加入的边信息集合
    for(j = 1; j <= num; j++){
        for(i = 1; i <= G->vexnum; i++){

            G->arcs[i][m+j] = INFINITY;
            G->arcs[m+j][i] = INFINITY;

        }
    }

    //新加入的顶点信息
    for(i = m+1; i <= G->vexnum; i++){
        printf("\t\t\t\t\t请输入第NO.%d个景点序号和名字：", i);
        scanf("%d %s", &G->vex[i].NO, G->vex[i].name);
    }
    Store(G);
    Print_AdjMatrix(G);
}

//添加新路线
void Add_Route(AdjMatrix *G)
{ 

    char name1[50], name2[50];
    char choice = 'y';
    int arcnum = G->arcnum, weight, i, j;

    while(choice == 'y' || choice == 'Y'){
        printf("\t\t\t\t\t请输入相关联的两个景点名字和路径长度相关联：");
        scanf("%s %s %d", name1, name2, &weight);
        i = Locate(G, name1);
        j = Locate(G, name2);
        G->arcs[i][j] = weight;
        G->arcs[j][i] = weight;
        printf("\t\t\t\t\t是否继续添加路线(y || n)：");
        getchar();
        choice = getchar();
    }
    Store(G);
    Print_AdjMatrix(G);
}

//撤销旧路线
void Del_Route(AdjMatrix *G)
{
    
    char name1[50], name2[50];
    char choice = 'y';
    int  i, j;

    while(choice == 'y' || choice == 'Y'){
        printf("\t\t\t\t\t请输入要撤销的两个景点名字:");
        scanf("%s %s", name1, name2);
        i = Locate(G, name1);
        j = Locate(G, name2);
        G->arcs[i][j] = INFINITY;
        G->arcs[j][i] = INFINITY;
        printf("\t\t\t\t\t是否继续撤销路线(y || n)：");
        getchar();
        choice = getchar();
    }
    Store(G);
    Print_AdjMatrix(G);
}

//撤销旧地点
void Del_Place(AdjMatrix *G)
{
    
    char name[50];
    char choice = 'y';
    int  i, j, k;

    while(choice == 'y' || choice == 'Y'){
        printf("\t\t\t\t\t请输入要撤销的景点的名字:");
        scanf("%s", name);
        k = Locate(G, name);
        for(j = k; j < G->vexnum; j++){
            G->vex[j] = G->vex[j+1];
        }
        for(i = k; i < G->vexnum; i++){
            for(j = 1; j <= G->vexnum; j++)
                G->arcs[i][j] = G->arcs[i+1][j];
        }
        for(j = k; j < G->vexnum; j++){
            for(i = 1; i < G->vexnum; i++)
                G->arcs[i][j] = G->arcs[i][j+1];
        }
        G->vexnum -= 1;
        Print_AdjMatrix(G);
        printf("\t\t\t\t\t是否继续撤销景点：(y || n)：");
        getchar();
        choice = getchar();
    }
    Store(G);
    Print_AdjMatrix(G);
}

//采用prim算法求最短连通图
void Prim(AdjMatrix *G, int start)
{
    struct{
        int adjvex;
        int lowcost;
        int pass;
    }closedge[Max_num+1];
    int i, e, k, m, min;
    
    //初始化
    closedge[start].lowcost = 0;
    for(i = 1; i <= G->vexnum; i++){
        if(i != start){
        closedge[i].adjvex = start;
        closedge[i].lowcost = G->arcs[start][i];

        }
    }
    
    //找最小值的边
    for(e = 1; e <= G->vexnum-1; e++){
                 
        min = INFINITY;
        for(k = 1; k <= G->vexnum; k++){
            if(closedge[k].lowcost != 0 && closedge[k].lowcost < min){
                m = k;
                min = closedge[k].lowcost;
            }
        }
        printf("\t%s----->%s: 距离为%d\n", G->vex[closedge[m].adjvex].name, G->vex[m].name, closedge[m].lowcost);
        closedge[m].lowcost = 0;
        
        //加入后，更新closedge数组
        for(i = 1; i <= G->vexnum; i++){
            if(i != m && G->arcs[m][i] < closedge[i].lowcost){
                closedge[i].lowcost = G->arcs[m][i];
                closedge[i].adjvex = m;
            }
        }
    }

}

//查询从某个景点出发的最短连通图
void Prim_MiniSpanTree(AdjMatrix *G)
{
    char name[50], choice = 'y';
    int start;

    printf("\033[2J\033[033m\033[10;0H");
    printf("\t\t\t\t\t\033[31m+\033[0m   最佳布网方案...\n\n\n\n\033[0m");
    while(choice == 'y' || choice == 'Y'){
        printf("\t\t\t\t\t请输入起点：");
        scanf("%s", name);
        start = Locate(G, name);
        Prim(G, start);
        printf("\t\t\t\t\t是否继续查询(y || n): ");
        getchar();
        choice = getchar();
    }
}

//采用Dijkstra算法求单元点的最短路径
void Dijkstra(AdjMatrix *G, int start, int end, int dist[], int path[][Max_num+1])
{
    int mindist, i, j, k, t = 1;

    //初始化
    for(i = 1; i <= G->vexnum; i++){
        dist[i] = G->arcs[start][i];
        if(G->arcs[start][i] != INFINITY)
            path[i][1] = start;
    }
    path[start][0] = 1;

    //寻求最短路径
    for(i = 2; i <= G->vexnum; i++){
        mindist = INFINITY;
        for(j = 1; j <= G->vexnum; j++){
            if(!path[j][0] && dist[j] < mindist){
                mindist = dist[j];
                k = j;
            }
        }
        if(mindist == INFINITY)  break;
        path[k][0] = 1;

        //修改加入后的最短路径
        for(j = 1; j <= G->vexnum; j++){
            if(!path[j][0] && G->arcs[k][j] < INFINITY && G->arcs[k][j] + dist[k] < dist[j]){
                dist[j] = dist[k] + G->arcs[k][j];
                 
               //记录最短路径
                t = 1;
                while(path[k][t]){
                    path[j][t] = path[k][t];
                    t++;
                }
                path[j][t] = k;
                path[j][t+1] = 0;
            }
        }
    }
    if(dist[end] == INFINITY){
        printf("\n\n\t%s----->%s  不存在通路!!!\n", G->vex[start].name, G->vex[end].name);
        return;
    }
    //输出最短路径
    printf("\n\n\t%s----->%s的最短路线：%s ", G->vex[start].name, G->vex[end].name, G->vex[start].name);
    for(j = 2; path[end][j]; j++)
        printf("——>%s ", G->vex[path[end][j]].name);
    printf("——>%s", G->vex[end].name);
    printf("\n\t距离为：%d\n", dist[end]);

}

//查询任意两景点间的最短路径
void Dij_Short_Path(AdjMatrix *G)
{
    char name[50], choice = 'y';
    int start, end;
    int dist[Max_num+1];
    printf("\033[2J\033[33m\033[10;0H");
    printf("\t\t\t\t\t\033[31m+\033[0m   最短路径...\n\n\n\n\033[0m");
    while(choice == 'y' || choice == 'Y'){
        int path[Max_num+1][Max_num+1] = {0};
        printf("\n\t\t\t\t\t请输入起点：");
        scanf("%s", name);
        start = Locate(G, name);
        printf("\t\t\t\t\t请输入终点：");
        scanf("%s", name);
        end = Locate(G, name);
        Dijkstra(G, start, end, dist, path);
        printf("\t\t\t\t\t是否继续查询(y || n)：");
        getchar();
        choice = getchar();
    }
}

//查询任意两景点间的所有路径
int pre[Max_num+1];  //存放一条路中的各顶点在数组中的下标
void Path(AdjMatrix *G, int start, int end, int length, int dist)
{
    int i;

    if(pre[length] == end && length < G->vexnum){
        printf("%s ", G->vex[pre[1]].name);
        for(i = 2; i <= length; i++){
            printf("——> %s", G->vex[pre[i]].name);
            if(G->arcs[pre[i-1]][pre[i]] != INFINITY){
                dist += G->arcs[pre[i-1]][pre[i]];
            }
        }
       
        printf("距离为: %d\n", dist);
        dist = 0;
    }else{  	// 没有输出完则进入
        i = 1;
        while(i <= G->vexnum){
            if(!visited[i] && G->arcs[pre[length]][i] != INFINITY){
                visited[i] = 1;
                pre[length+1] = i;
                Path(G, i, end, length+1, dist);
                visited[i] = 0;
            }
            i++;
        }
    }
}

void All_Path(AdjMatrix *G)
{
    int i, start, end;
    char name1[50], name2[50];
    int dist = 0;
    
    printf("\t\t\t\t\t请输入起点：");
    scanf("%s", name1);
    start = Locate(G, name1);
    printf("\t\t\t\t\t请输入终点：");
    scanf("%s", name2);
    end = Locate(G, name2);
    for(i = 1; i <= Max_num; i++)
        visited[i] = 0;
    visited[start] = 1;  // 访问过则标记为1
    pre[1] = start;      
    printf("%s---->%s的所有路径为：\n", G->vex[start].name, G->vex[end].name);
    Path(G, start, end, 1, dist);
}

//存储景点及路径信息
void Store(AdjMatrix *G) 
{
    FILE *fp;
    
    if((fp = fopen("message", "wt")) == NULL){
        printf("\033[31m\033[15;0H\t\t\t\t\t抱歉，无法正常存储!\n\033[0m");
        return ; 

    }
    printf("\033[33m\033[15;0H\t\t\t\033[31m+\033[0m   存储信息中...\n");
    fwrite(G, sizeof(AdjMatrix), 1, fp);
    fclose(fp);
    printf("\033[2J\033[15;0H\t\t\t\t\t恭喜，存储成功!\n\n\n\033[0m");
}

//读取景点及路线信息
AdjMatrix Read()
{
    FILE *fp;
    AdjMatrix G;
    if((fp = fopen("message", "rt")) == NULL){
        printf("\033[31m\033[15;0H\t\t\t\t\t抱歉，无法正常读取!\n\033[0m");
        return ;
    }
    printf("\033[33m\033[15;0H\t\t\t\033[31m+\033[0m   读取信息中...\n");
    fread(&G, sizeof(AdjMatrix), 1, fp);
    fclose(fp);
    printf("\033[2J\033[15;0H\t\t\t\t\t恭喜,  读取成功!\n");

    return G;
}

//查询地点信息
void plcae(AdjMatrix *G)
{
    char place[500], name[50], choice = 'y';
    int i;
    FILE *fp;
    
    printf("\033[2J\033[33m\033[3;0H");
    printf("\t\t\t\t\t\033[31m+\033[0m   地点信息查询...\n\n\n\n\n\033[0m");
    for(i = 1; i <= G->vexnum; i++)
        printf("%s  ", G->vex[i].name);
    printf("\n");
    while(choice == 'y' || choice == 'Y'){
        printf("\t\t\t\t\t请输入需要了解的景点名：");
        scanf("%s", name);
        if((fp = fopen(name, "rt")) == NULL){
            printf("\t\t\t\t\t抱歉，文件未正常打开！\n");
            return;
        }
        while((fgets(place, 500, fp)) != NULL){
            printf("%s", place);
        }
        fclose(fp);
        getchar();
        printf("\n\n\t\t\t\t\t是否要继续(y || n)：");
        scanf("%c", &choice);
    }
}

//menu1菜单的对应功能
void switch1(AdjMatrix G)
{
    int choice;
    printf("\t\t\t\t\t\t请输入您需要的功能：");
    scanf("%d", &choice);
        switch(choice){
            case 1:Create_AdjMatrix(&G); break;  //创建新地图
            case 2:Add_Place(&G);   break;  //添加新地点
            case 3:Del_Place(&G);   break;  //撤销旧地点
            case 4:Add_Route(&G);   break;  //添加新路线
            case 5:Del_Route(&G);   break;  //撤销旧路线
            case 6:DFSTrave(G); break;       //深度优先遍历所有景点
            case 0:menu(G);  break;
            default:
                   printf("\033[31m\t\t\t\t\t抱歉，输入有误!!!\n");
        }
  
      if ( choice !=0 ){
        getchar();
        printf("\n\n\t\t\t\t\t\033[33m按enter键返回......");
        getchar();
        menu1();
        switch1(G);
     }
}

//menu2菜单的对应功能
void switch2()
{
    int choice,k;
    AdjMatrix G;
    FILE *fp;

    if((fp = fopen("message", "rt")) == NULL){
        printf("\033[31m\t\t\t\t\t抱歉，不能打开文件！\n\033[0m");
        return;
    }
    fread(&G, sizeof(AdjMatrix), 1, fp);
    fclose(fp);
    printf("\t\t\t\t\t请输入您需要的功能：");
    scanf("%d", &choice);
 
        switch(choice){
            case 1: map(); break; //查看校园平面图
            case 2: plcae(&G); break; //地点信息查询
            case 3: Dij_Short_Path(&G); break; //最短路径
            case 4: All_Path(&G);break;       //所有路径
            case 5: Prim_MiniSpanTree(&G); break; //最短连通图
            case 0: menu(G); break;   //退出
            default:
                    printf("\033[31m\t\t\t\t\t\t抱歉，您的输入有误！！！\n");
        }
      if(choice!=0){
        getchar();
        printf("\033[33m\n\n\t\t\t\t\t按enter键返回......\n");
        getchar();
        menu2();
        switch2();
      }
}
