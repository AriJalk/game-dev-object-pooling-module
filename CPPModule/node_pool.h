#ifndef NODE_POOL_H
#define NODE_POOL_H

#include <scene/main/node.h>
#include <string.h>
#include <map>
#include <queue>

class NodePool : public Node {
	GDCLASS(NodePool, Node);

private:
	std::map<String, std::queue<Node *>*> poolMap;

protected:
	static void _bind_methods();

public:
	void register_prefab(const String &type, Node *node, int amount);
	Node *retrieve_prefab(const String &type);
	void return_prefab(const String &type, Node *node);

	NodePool();
	~NodePool();
};

#endif
