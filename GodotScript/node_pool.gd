class_name NodePool

const default_pool_size = 50

var _pools : Dictionary

## Register a packed scene and instantiate copies for the pool
## type: Prefab identifier for the dictionary
## scene: The loaded Packed scene to be used as template
## count: How many to create
func register_node(type : String, scene : PackedScene, count : int = default_pool_size) -> bool:
	if !_pools.has(type) && scene != null:
		var pool = Pool.new()
		for i in count:
			pool.array.append(scene.instantiate())
		_pools[type] = pool
		return true
	push_error("Can't register node")
	return false
	
## Returns a node of the specified type from the pool if registered and exists.
## type: Prefab identifier
func retrieve_node(type : String) -> Node:
	var pool
	if _pools.has(type):
		pool = _pools[type]
	if pool != null && pool.array.size() > 0:
		var node = pool.array.pop_front()
		var parent = node.get_parent() as Node
		if node != null:
			return node
	push_error("Can't retrieve node")
	return null

## Return nodes retrieves from the pool using this function
## type: Prefab identifier
func return_node(type : String, node : Node) -> bool:
	var pool = _pools[type] as Pool
	if pool != null && node != null:
		var parent = node.get_parent()
		if parent != null:
			parent.remove_child(node)
		pool.array.append(node)
		return true
	push_error("Can't return node")
	return false

func _test_pool():
	var result = register_node("test", PackedScene.new(), 10)
	if result == true:
		print("Register OK")
		var retrieve = retrieve_node("test")
		if retrieve != null:
			print("Retrieve OK")
			result = return_node("test", retrieve)
			if result == true:
				print("Return OK")
			else:
				print("Return Failed")
		else:
			print("Retrive Failed")
	else:
		print("Register Failed")
	
	
		

class Pool:
	var array : Array[Node] = []

