#include "node_pool.h"

void NodePool::_bind_methods() {
	ClassDB::bind_method(D_METHOD("register_prefab", "type", "node", "amount"), &NodePool::register_prefab);
	ClassDB::bind_method(D_METHOD("retrieve_prefab", "type"), &NodePool::retrieve_prefab);
	ClassDB::bind_method(D_METHOD("return_prefab", "type", "node"), &NodePool::return_prefab);
}

void NodePool::register_prefab(const String &type, Node *node, int amount) {
	String ascii = type.ascii();
	std::map<String, std::queue<Node *> *>::iterator iterator = poolMap.find(type);
	if (iterator != poolMap.end() || node == nullptr) {
		print_error("Can't register");
		return;
	}
	//print_line("Register " + ascii);
	std::queue<Node *> *newQueue = new std::queue<Node *>();
	for (int i = 0; i < amount; i++) {
		Node *newNode = (Node *)(node->duplicate());
		if (newNode) {
			newNode->set_name(type + String::num_int64((static_cast<int64_t>(i) + 1)));
			newQueue->push(newNode);
		}
	}
	poolMap.insert(std::pair<String, std::queue<Node *> *>(type, newQueue));
}

Node *NodePool::retrieve_prefab(const String &type) {
	String ascii = type.ascii();
	//print_line("Retrieve " + ascii);
	std::map<String, std::queue<Node *> *>::iterator iterator = poolMap.find(type);
	if (iterator != poolMap.end() && iterator->second->size() > 0) {
		Node *node = iterator->second->front();

		iterator->second->pop();
		return node;
	}
	print_error("no prefab found");
	return nullptr;
}

void NodePool::return_prefab(const String &type, Node *node) {
	std::map<String, std::queue<Node *> *>::iterator iterator = poolMap.find(type);
	if (iterator != poolMap.end() && node != nullptr) {
		Node* parent = node->get_parent();
		if (parent != nullptr) {
			parent->remove_child(node);
		}
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
