#include"graph.h"
#include<iostream>
#include<vector>
#include "graphFun.h"
using namespace std;

//返回data顶点在邻接表中的位置
int LocateVex(ALGraph& G, char data_) {
	for (int i = 0; i < G.vexNum; ++i) {
		if (G.vertices[i].data == data_) {
			return i;
		}
	}
	return -1;
}

//返回v的第一个邻接顶点
int FirstAdjVex(ALGraph& G, int v) {
	if (G.vertices[v].firstArc != nullptr)		return G.vertices[v].firstArc->adjvex;;
	return -1;

}

//返回v的相对于邻接点w的下一个节点
int NextAdjVex(AlGraph& G, int v, int w) {
	for (auto p = G.vertices[v].firstArc; p; p = p->nextArc) {
		if (p->adjvex == w && p->nextArc)	return p->nextArc->adjvex;
	}
	return -1;
}

//删除边
void DeleteArch(ALGraph& G, char v1, char v2) {
	int i = LocateVex(G, v1);
	int j = LocateVex(G, v2);

	//若为无向图，删除对应的两个边节点
	if (G.kind == 0) {
		if (G.vertices[i].firstArc && G.vertices[i].firstArc->adjvex == j) {
			auto temp = G.vertices[i].firstArc->nextArc;
			delete G.vertices[i].firstArc;
			G.vertices[i].firstArc = temp;
		}
		else {
			for (ArcNode* p = G.vertices[i].firstArc; p; p = p->nextArc) {
				if (p->nextArc && p->nextArc->adjvex == j) {
					auto q = p->nextArc;
					p->nextArc = q->nextArc;
					delete q;
					break;
				}
			}
		}


		if (G.vertices[j].firstArc && G.vertices[j].firstArc->adjvex == i) {
			auto temp = G.vertices[j].firstArc->nextArc;;
			delete G.vertices[j].firstArc;
			G.vertices[j].firstArc = temp;
		}
		else {
			for (ArcNode* p = G.vertices[j].firstArc; p; p = p->nextArc) {
				if (p->nextArc && p->nextArc->adjvex == i) {
					auto q = p->nextArc;
					p->nextArc = q->nextArc;
					delete q;
					break;
				}
			}

		}
	}

	//若为有向图，删除对应的一个边节点
	else if (G.kind == 1) {//若为无向图，删除对应的两个边节点
		if (G.vertices[i].firstArc && G.vertices[i].firstArc->adjvex == j) {
			auto temp = G.vertices[i].firstArc->nextArc;
			delete G.vertices[i].firstArc;
			G.vertices[i].firstArc = temp;
		}
		else {
			for (ArcNode* p = G.vertices[i].firstArc; p; p = p->nextArc) {
				if (p->nextArc && p->nextArc->adjvex == j) {
					auto q = p->nextArc;
					p->nextArc = q->nextArc;
					delete q;
					break;
				}
			}
		}


	}

	//边数自减
	--G.arcNum;
}

//图增加（头插）边
void InsertArch(ALGraph& G, char v1, char v2) {
	int i = LocateVex(G, v1);
	int j = LocateVex(G, v2);

	//无向图增加两个边节点
	if (i != -1 && j != -1 && G.kind == 0) {
		ArcNode* p1 = new ArcNode;
		ArcNode* p2 = new ArcNode;
		p1->adjvex = j;
		p1->nextArc = G.vertices[i].firstArc;
		G.vertices[i].firstArc = p1;

		p2->adjvex = i;
		p2->nextArc = G.vertices[j].firstArc;
		G.vertices[j].firstArc = p2;

	}

	//有向图增加一个边节点
	if (i != -1 && j != -1 && G.kind == 1) {
		ArcNode* p1 = new ArcNode;
		p1->adjvex = j;
		p1->nextArc = G.vertices[i].firstArc;
		G.vertices[i].firstArc = p1;

	}
	++G.arcNum;
}

//DFS算法
void DFS(ALGraph& G, int v, vector<int>& visit) {
	if (G.arcNum == 0) {
		return;
	}
	visit[v] = true;
	auto p = G.vertices[v].firstArc;
	for (int w = FirstAdjVex(G, v); p; p = p->nextArc) {
		if (p != nullptr) w = p->adjvex;
		if (visit[w] == false)	DFS(G, w, visit);


	}

}

//利用visit数组判桥
bool IsBridge(ALGraph& G, int v, vector<int>& visit, vector<int>& pre_visit)
{
	visit.assign(G.vexNum, 0);
	DFS(G, v, visit);//对于删除边的终点进行深度遍历

	if (pre_visit == visit)  return false;
	return true;
}

//构造欧拉回路
vector<char> Euler(ALGraph& G, int v) {

	//空表，返回空
	if (G.vexNum == 0) return {};

	vector<int> visit(G.vexNum, 0);

	//不连通图，返回空
	DFS(G, v, visit);
	if (find(visit.begin(), visit.end(), 0) != visit.end())	return{};
	visit.assign(G.vexNum, 0);

	//有奇度顶点或出度不等于入度，返回空
	for (int i = 0; i < G.vexNum; ++i) {

		//无向图的判定：无奇度顶点
		if (G.kind == 0) {
			int degree = 0;//度数

			for (auto p = G.vertices[i].firstArc; p; p = p->nextArc) {
				degree++;
			}

			if (degree % 2 == 1) {
				return {};
			}
		}

		//有向图的判定：所有顶点出度==入度
		if (G.kind == 1) {
			int inDegree = 0;//出度
			int outDegree = 0;//入度

			//计算出度
			for (auto p = G.vertices[i].firstArc; p; p = p->nextArc) {
				++outDegree;
			}

			//计算入度
			for (int j = 0; j < G.vexNum; ++j) {
				for (auto p = G.vertices[j].firstArc; p; p = p->nextArc) {
					if (p->adjvex == i) {
						++inDegree;
					}
				}
			}

			if (inDegree != outDegree) {
				return {};
			}
		}

	}


	//存在欧拉回路,开始构造欧拉回路
	
	vector<char> circuit;
	vector<int> pre_visit;
	int allArcNum = G.arcNum;
	int start = v;

	while (circuit.size() <= allArcNum - 1) {//当回路集合不构成回路
				
		circuit.push_back(G.vertices[v].data);
		auto tempv = G.vertices[v].firstArc->adjvex;

		if (G.vertices[v].firstArc != nullptr && (G.vertices[v].firstArc->nextArc) == nullptr) {//如果节点只有一条边
			DeleteArch(G, G.vertices[v].data, G.vertices[tempv].data);
			v = tempv;
			continue;//删除该边后继续到下一节点
		}
		pre_visit.assign(G.vexNum, 0);
		DFS(G, tempv, pre_visit);
		DeleteArch(G, G.vertices[v].data, G.vertices[tempv].data);//删除邻接表中一条边

		if (IsBridge(G, tempv, visit, pre_visit)) {//如果此边为桥
			InsertArch(G, G.vertices[tempv].data, G.vertices[v].data);//重新插入此边

			for (auto p = G.vertices[v].firstArc->nextArc, q = G.vertices[v].firstArc; q && p; p = p->nextArc, q = q->nextArc) {//如果为桥并且边不唯一

				tempv = p->adjvex;

				pre_visit.assign(G.vexNum, 0);
				DFS(G, tempv, pre_visit);

				DeleteArch(G, G.vertices[v].data, G.vertices[p->adjvex].data);//继续删除下一条边

				if (IsBridge(G, tempv, visit, pre_visit)) {//如果为桥
					//在对应位置重新插入该边(无向图）
					if (G.kind == 0) {
						auto pData1 = new ArcNode;
						auto pData2 = new ArcNode;

						pData1->adjvex = tempv;
						pData1->nextArc = q->nextArc;
						q->nextArc = pData1;
						p = q->nextArc;

						pData2->adjvex = G.vertices[v].data;
						pData2->nextArc = G.vertices[tempv].firstArc;
						G.vertices[tempv].firstArc = pData2;
						++G.arcNum;
					}
					//在对应位置重新插入该边(有向图)
					if (G.kind == 1) {
						auto pData1 = new ArcNode;

						pData1->adjvex = tempv;
						pData1->nextArc = q->nextArc;
						q->nextArc = pData1;
						p = q->nextArc;
						++G.arcNum;
					}


				}

				else {//如果不为桥
					v = tempv;//到下一节点
					break;//跳出此节点的边序列
				}
			}
		}

		else {//不为桥，到下一个顶点
			v = tempv;
		}

	}

	circuit.push_back(G.vertices[start].data);
	return circuit;
}
