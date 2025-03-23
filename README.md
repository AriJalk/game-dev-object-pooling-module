# ⚠️ No Longer Maintained


# ObjectPoolModule

Object Pooling modules for Godot and Unity.

## Godot

### CPP Module 

The node-pool as an internal Godot Module to be built with Godot source code.
To be used if high-performance is needed, but requires a custom engine build to be used.
Module files should be placed in a folder inside Godot's source-code Module folder and then build.

### Godot GD file

The module implemented as standard GDScript.
A bit slower performance than the CPP module but should be unnoticeable for most uses as the margin is quite small.


### Usage

Types are identifiable by their name string:

- `register_node(type: String, scene: PackedScene, count: int = default_pool_size) -> bool`: Provide a packed scene and instantiate the wanted amount.
  
- `retrieve_node(type: String) -> Node`: Retrieve a node of the required type if it exists.
  
- `return_node(type: String, node: Node) -> bool`: This function is used instead of destroying the object.

## Unity

### Usage

Types are identifiable by their defining MonoBehaviour class.
Prefabs are placed in Resources/Prefabs/[PREFAB_2D / PREFAB_3D].

- `public void RegisterPrefab<T>(GameObject prefab, int poolSize = INITIAL_POOL_SIZE) where T : Component`: Provide a saved prefab file along with its defining MonoBehaviour class as `T` to instantiate plus an optional pool size.
  
- `public void LoadAndRegisterPrefab<T>(PrefabFolder folder, string prefabName, int poolSize) where T : Component`: Provide the name and folder (PREFAB_2D / PREFAB_3D) of the prefab plus an optional pool size to register, can be used instead of RegisterPrefab<T>.
  
- `public T RetrievePoolObject<T>() where T : Component, new()`: Get an instance of the needed prefab type from a registered prefab pool if it exists.
  
- `public void ReturnPoolObject<T>(T obj) where T : Component`: Return an instance instead of destroying it.

