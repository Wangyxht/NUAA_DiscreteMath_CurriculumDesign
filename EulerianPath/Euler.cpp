#include"graph.h"
#include"graphFun.h"
#include<iostream>
#include<vector>
#include<ctime>
using namespace std;


int main(int argv, char* argc[]) {
	ALGraph G;

	clock_t t1 = clock();

	//输入顶点数、边数：
	cout << "请输入顶点数:";
	cin >> G.vexNum;

	cout << "请输入边数：";
	cin >> G.arcNum;

	cout << "确认1为有向图，0为无向图：";
	cin >> G.kind;

	//输入顶点表
	G.vertices = new VNode[G.vexNum];
	for (int i = 0; i < G.vexNum; ++i) {
		cout << "请输入第" << i + 1 << "个顶点的信息:";
		cin >> G.vertices[i].data;
		G.vertices[i].firstArc = nullptr;
	}
	//输入边节点
	for (int i = 0; i < G.arcNum; ++i) {
		char vexData1, vexData2;
		cout << "请输入第" << i + 1 << "条边的起点与终点:";
		cin >> vexData1 >> vexData2;

		int v1 = LocateVex(G, vexData1);
		int v2 = LocateVex(G, vexData2);
		if (v1 != -1 && v2 != -1 && G.kind == 0) {//建立无向邻接表，需要存储两个节点
			ArcNode* p1 = new ArcNode;
			ArcNode* p2 = new ArcNode;
			p1->adjvex = v2;
			p1->nextArc = G.vertices[v1].firstArc;
			G.vertices[v1].firstArc = p1;

			p2->adjvex = v1;
			p2->nextArc = G.vertices[v2].firstArc;
			G.vertices[v2].firstArc = p2;

		}

		if (v1 != -1 && v2 != -1 && G.kind == 1) {//建立有向图出度邻接表，仅仅存储一个节点
			ArcNode* p1 = new ArcNode;
			p1->adjvex = v2;
			p1->nextArc = G.vertices[v1].firstArc;
			G.vertices[v1].firstArc = p1;

		}

	}

	//构造欧拉回路
	vector<char> euler = Euler(G, 0);

	system("cls");
	//显示欧拉回路：
	if (euler.empty()) {
		cout << "此图无欧拉回路" << endl;
	}

	else {
		for (auto it = euler.cbegin(); it != euler.cend(); it++) {
			cout << (*it);
			if (it != euler.cend() - 1) {
				cout << "——>";
			}
		}
		cout << endl;
	}

	clock_t t2 = clock();
	cout << "执行时间：" << (double)(t2 - t1) / CLOCKS_PER_SEC << "ms" << endl;

	system("pause");
	return EXIT_SUCCESS;

}