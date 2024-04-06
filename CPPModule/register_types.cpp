/* register_types.cpp */


#include "core/object/class_db.h"
#include "node_pool.h"
#include "register_types.h"

void initialize_node_pool_module(ModuleInitializationLevel p_level) {
	if (p_level != MODULE_INITIALIZATION_LEVEL_SCENE) {
		return;
	}
	ClassDB::register_class<NodePool>();
}

void uninitialize_node_pool_module(ModuleInitializationLevel p_level) {
	if (p_level != MODULE_INITIALIZATION_LEVEL_SCENE) {
		return;
	}
}
