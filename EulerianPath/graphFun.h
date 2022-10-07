#pragma once
#include"graph.h"
#include<vector>
using namespace std;

//返回data顶点在邻接表中的位置
int LocateVex(ALGraph& G, char data_);
//返回v的第一个邻接顶点
int FirstAdjVex(ALGraph& G, int v);
//返回v的相对于w的下一个节点
int NextAdjVex(AlGraph& G, int v, int w);
//删除边
void DeleteArch(ALGraph& G, char v1, char v2);
//增加边
void InsertArch(ALGraph& G, char v1, char v2);
//DFS算法
void DFS(ALGraph& G, int v, vector<int>& visit);
//判断删除边后子图的连通性
bool IsBridge(ALGraph& G, int v, vector<int>& visit, vector<int>& pre_visit);
//构造欧拉回路
vector<char> Euler(ALGraph& G, int v);