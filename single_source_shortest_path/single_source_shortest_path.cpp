// single_source_shortest_path.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>
#include <queue>
#include <algorithm>
#include <fstream>
#define pa std::pair<int,int>

const int MAXN = 100; //图中点的最大数目
const int DATA_NUM = 2; //数据组数

struct graph { //图结构体
    double e[MAXN][MAXN]; //邻接矩阵
    int id[MAXN]; //每个点的编号
    int n; //图中顶点数目
};
graph g[DATA_NUM]; //储存各个图的数据

std::priority_queue<pa, std::vector<pa>, std::greater<pa>>q; //用来优化dijkstra算法的堆，pair的两个值分别为当前路径长度和点的序号
double dis[MAXN] = {}; //记录最短路长度
int next[MAXN] = {}; //记录每个点的最短路上的前一个点
int vis[MAXN] = {}; //堆优化的dijkstra过程中判断某个点是否访问过
int road[MAXN] = {};//用来向前搜索输出最短路径

void getData(int num); //从文件读入数据，参数为数据组数
void Dijkstra(double e[][MAXN], int size, int s); //堆优化的dijkstra算法，三个参数分别为：邻接矩阵，图中点的数目，最短路的源点

void getData(int num) {
    std::fstream data;
    for (int k = 0; k < num; ++k) {
        std::string name = "graph";
        char id = '1' + k;
        name = name + id;
        name = name + ".txt";
        data.open(name);
        data >> g[k].n;
        for (int i = 0; i < g[k].n; ++i) {
            data >> g[k].id[i];
            for (int j = 0; j < g[k].n; ++j) {
                data >> g[k].e[i][j];
                if (g[k].e[i][j] == 99999)g[k].e[i][j] = -1;
            }
        }
        data.close();
    }
}
void Dijkstra(double e[][MAXN], int size, int s) {
    while (!q.empty())q.pop();
    for (int i = 0; i < size; ++i) dis[i] = -1;
    memset(vis, 0, sizeof(vis));
    int x;
    dis[s] = 0;
    q.push(std::make_pair(0, s));
    while (!q.empty()) {
        x = q.top().second;
        q.pop();
        if (vis[x]) {
            continue;
        }
        vis[x] = 1;
        for (int i = 0; i < size; ++i) {
            if (e[x][i] < 0)continue;
            if (dis[i] < 0 || dis[i] > dis[x] + e[x][i]) {
                next[i] = x;
                dis[i] = dis[x] + e[x][i];
                vis[i] = 0;
                q.push(std::make_pair(dis[i], i));
            }
        }
    }
}
int main()
{
    std::cout << "开始读入数据\n\n";
    getData(DATA_NUM);
    for (int i = 0; i < DATA_NUM; ++i) {
        std::cout << "开始计算第" << i+1 << "组数据的最短路\n";
        std::cout << "图中共" << g[i].n << "个点\n";
        std::cout << "起始点为" << g[i].id[0] << "\n";
        Dijkstra(g[i].e, g[i].n, 0);
        for (int j = 0; j < g[i].n; ++j) {
            if (dis[j] < 0) {
                std::cout << "到第" << j+1 << "个点" << g[i].id[j] << "没有路" << std::endl;
            }
            else {
                std::cout << "到第" << j + 1 << "个点" << g[i].id[j] << "的最短距离为" << dis[j];
                if (j > 0) {
                    std::cout << ",最短路径为：";
                    int k = 0, x = j;
                    while (x!=0) {
                        road[k++] = x;
                        x = next[x];
                    }
                    road[k] = 0;
                    for (; k > 0; k--) {
                        std::cout << road[k] + 1 << "->";
                    }std::cout << road[k] + 1 << std::endl;
                }
                else std::cout << "，该点为起点" << std::endl;
            }
        }
        std::cout << std::endl;
    }
    return 0;
}

// 运行程序: Ctrl + F5 或调试 >“开始执行(不调试)”菜单
// 调试程序: F5 或调试 >“开始调试”菜单

// 入门使用技巧: 
//   1. 使用解决方案资源管理器窗口添加/管理文件
//   2. 使用团队资源管理器窗口连接到源代码管理
//   3. 使用输出窗口查看生成输出和其他消息
//   4. 使用错误列表窗口查看错误
//   5. 转到“项目”>“添加新项”以创建新的代码文件，或转到“项目”>“添加现有项”以将现有代码文件添加到项目
//   6. 将来，若要再次打开此项目，请转到“文件”>“打开”>“项目”并选择 .sln 文件
