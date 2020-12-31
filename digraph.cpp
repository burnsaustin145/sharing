#include <string>
#include <iostream>
#include <vector>
#include <forward_list>
const std::string emptyString;

class Graph
{
public:
	typedef unsigned int NodeID;
	typedef unsigned int EdgeID;
	typedef int NodeWeight;
	typedef int EdgeWeight;
	
	struct Edge
	{
		Edge(NodeID nid, EdgeWeight wt, 
		const std::string & lb)
		:v(nid), w(wt), label(lb) {};
	
		const NodeID v;
		const EdgeWeight w;
		const std::string label;
	};
	
	struct Node 
	{
		Node(NodeWeight wt, const std::string & l):
			w(wt), label(l){};

		NodeWeight w;
		std::string label;
	};
	
	// all nodes
	typedef std::vector<Node> Nodes;
	// edges from a node
	typedef std::forward_list<Edge> EdgesList;
	// all edges (id -> edgeList)
	typedef std::vector<EdgesList> Edges;
	
	// allocate |V| lists of edges
	Graph(NodeID V = 0, EdgeID E = 0)
	{
		if(V)
		{
			_nodes.reserve(V);_outdegree.reserve(V);
		}
		if (E)
			_edges.reserve(E);
	};
	
	void reserveNodes(NodeID n)
	{ _nodes.reserve(n);_outdegree.reserve(n);}
	void reserveEdges(EdgeID n)
	{ _edges.reserve(n);}
	
	//we can have multiple edges (v1, v2)
	void addEdge(NodeID v1, 
				 NodeID v2, 
				 EdgeWeight w = 0, 
				 const std::string & label = emptyString)
	{
		if (v1 > _nodes.size() || v2 > _nodes.size())
							return;
		Edge e(v2, w, label);
		_edges[v1].push_front(e);
		_outdegree[v1]++;
	}
	
	// nodes are unique
	void addNode(NodeWeight w = 0, const std::string & label = emptyString)
	{
		EdgesList el;
		Node n(w, label);
		_nodes.push_back(n);
		_edges.push_back(el);
		_outdegree.push_back(0);
	}
	
	const EdgesList & edges(NodeID v) const
	{return _edges[v]; };
	
	Graph::NodeID outdegree(NodeID v) const
	{return _outdegree[v];};
	
	const Nodes & nodes() const
	{return _nodes; };
	
	NodeID numNodes() const
	{return _nodes.size(); };
	
	EdgeID numEdges() const
	{return _edges.size(); };

private:
	Edges _edges;
	Nodes _nodes;
	std::vector<Graph::NodeID> _outdegree;
	
	Graph(const Graph& g) = delete;
	Graph& operator=(const Graph& g) = delete;
};

std::ostream & operator << (std::ostream & os, const Graph & g)
{
	Graph::NodeID id = 0;
	for (const auto & n: g.nodes())
	{
		os<<" node=" << id <<" weight=" <<n.w<<" label=" << n.label << std::endl;

		for (const auto & e : g.edges(id))
			os << "->" << e.v << "w=" << e.w << " label=" << n.label << " labelEdge="<< e.label << std::endl;
		++id;
	}
	return os;
}

int main()
{
	Graph G;
	G.addNode(10, "donald duck");
	G.addNode(1, "daisy duck");
	G.addNode(1, "antonio");
	G.addNode(1, "melinena");
	G.addNode(1, "lorena");
	G.addNode(1, "mambo");
	G.addNode(1, "salsa");
	G.addNode(1, "adriana");
	
	G.addEdge(0, 2);
	G.addEdge(1, 2, 10, "important");
	G.addEdge(1, 3);
	G.addEdge(2, 3);
	G.addEdge(2, 5);
	G.addEdge(2, 6);
	G.addEdge(4, 5);
	G.addEdge(5, 5);
	G.addEdge(5, 4);
	G.addEdge(5, 100);
	std::cout << G;
	return 0;
}
	
		
