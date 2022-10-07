#ifndef Graph_H
#define Graph_H

#define UN_DIRECTED 0//无向图类型为1
#define DIRECTED 1//有向图类型为0
//边 结点
struct arcNode {
	int adjvex;//该边指向顶点位置
	arcNode* nextArc;//指向下一条边节点的指针	
};

using ArcNode = arcNode;
//头 结点
struct Vnode {
	char data;//顶点的信息
	ArcNode* firstArc;//指向第一条边的指针

};
using VNode = Vnode;
using AdjList = Vnode*;

struct AlGraph {
	AdjList vertices;//顶点
	int arcNum;//边数
	int vexNum;//节点数
	int kind;//图的种类
	AlGraph() :vertices(nullptr), arcNum(0), vexNum(0), kind(0) {};
};

using ALGraph = AlGraph;


#endif // !Graph_H

