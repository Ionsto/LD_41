#pragma once
#include <vector>
#include <numeric>
//Alias
struct NodeId {
	int id;
	NodeId(int i = -1) :id(i) {};
};
class Node {
private:
	float SumProbablity = 0;
	std::vector<float> Probablities;
	//IDK some lock structure
	std::vector<bool> Active;
	std::vector<NodeId> Connections;
public:
	NodeId MyId;
	float X, Y;
	bool Target = false;
	Node(float x, float y) :X(x),Y(y)
	{
		
	}
	void AddConnection(NodeId id, float probablity) {
		SumProbablity += probablity;
		Connections.emplace_back(id);
		Probablities.emplace_back(probablity);
		Active.emplace_back(false);
	}
	NodeId GetRandomNextNode(){
		if (Probablities.size() == 0)
		{
			return MyId;
		}
		std::vector<float> Val(Probablities.size());
		std::transform(Probablities.begin(), Probablities.end(), Val.begin(), [](float p) {return (rand() % 100)*p;});
		int position = std::distance(Val.begin(), std::max_element(Val.begin(), Val.end()));
		return Connections[position];
	}
};

class RoadSystem
{
public:
	//Static
	std::vector<Node> NodeMap;
	RoadSystem() {
		AddNode(Node(20,20));
	}
	~RoadSystem() {

	}
	NodeId AddNode(Node && node) {
		NodeId nodeid = NodeId(static_cast<int>(NodeMap.size()));
		node.MyId = nodeid;
		NodeMap.push_back(node);
		return nodeid;
	}
	Node & GetNode(NodeId id) {
		return NodeMap[id.id];
	}
	Node & GetDefaultNode() {
		return NodeMap[0];
	}
	Node & GetRandomNextNode(NodeId & id) {
		auto & CurrentNode = GetNode(id);
		auto nextnode = CurrentNode.GetRandomNextNode();
		return GetNode(nextnode);
	}
};

