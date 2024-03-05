#include "node_pool.h"

void NodePool::_bind_methods() {
	ClassDB::bind_method(D_METHOD("register_prefab", "type", "node", "amount"), &NodePool::register_prefab);
	ClassDB::bind_method(D_METHOD("retrieve_prefab", "type"), &NodePool::retrieve_prefab);
	ClassDB::bind_method(D_METHOD("return_prefab", "type", "node"), &NodePool::return_prefab);
}

void NodePool::register_prefab(const String &type, Node3D *node, int amount) {
	String ascii = type.ascii();
	std::map<String, std::queue<Node3D *> *>::iterator iterator = poolMap.find(type);
	if (iterator != poolMap.end() || node == nullptr) {
		print_error("Can't register");
		return;
	}
	//print_line("Register " + ascii);
	std::queue<Node3D *> *newQueue = new std::queue<Node3D *>();
	for (int i = 0; i < amount; i++) {
		Node3D *newNode = (Node3D *)(node->duplicate());
		if (newNode) {
			newNode->set_name(type + String::num_int64((static_cast<int64_t>(i) + 1)));
			newNode->set_visible(false);
			this->add_child(newNode);
			newQueue->push(newNode);
		}
	}
	poolMap.insert(std::pair<String, std::queue<Node3D *> *>(type, newQueue));
}

Node3D *NodePool::retrieve_prefab(const String &type) {
	String ascii = type.ascii();
	//print_line("Retrieve " + ascii);
	std::map<String, std::queue<Node3D *> *>::iterator iterator = poolMap.find(type);
	if (iterator != poolMap.end() && iterator->second->size() > 0) {
		Node3D *node = iterator->second->front();

		iterator->second->pop();
		remove_child(node);
		return node;
	}
	print_error("no prefab found");
	return nullptr;
}

void NodePool::return_prefab(const String &type, Node3D *node) {
	std::map<String, std::queue<Node3D *> *>::iterator iterator = poolMap.find(type);
	if (iterator != poolMap.end() && node != nullptr) {
		node->set_visible(false);
		iterator->second->push(node);
	}
}

NodePool::NodePool() {
}

NodePool::~NodePool() {
	for (auto &pair : poolMap) {
		delete pair.second;
	}
	poolMap.clear();
}
