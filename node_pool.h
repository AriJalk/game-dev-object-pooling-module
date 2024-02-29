#ifndef NODE_POOL_H
#define NODE_POOL_H

#include <scene/3d/node_3d.h>
#include <string.h>
#include <map>
#include <queue>

class NodePool : public Node {
	GDCLASS(NodePool, Node);

private:
	std::map<String, std::queue<Node3D *>*> poolMap;

protected:
	static void _bind_methods();

public:
	void register_prefab(const String &type, Node3D *node, int amount);
	Node3D *retrieve_prefab(const String &type);
	void return_prefab(const String &type, Node3D *node);

	NodePool();
	~NodePool();
};

#endif
