# GodotNodePoolModule
A module for object pooling in godot made for use in my personal Godot projects.
An instantiated node is supplied to the Pool initially to insantiate and store the wanted number of objects.

There are 2 variants:

## CPP Module
The node-pool as an internal Godot Module to be built with Godot source code.
To be used if high-performance is needed, but requires a custom engine build to be used.
Module files should be placed in a folder inside Godot's source-code Module folder and then build.

## Godot GD file
The module implemented as standard GDScript.
A bit slower performance than the CPP module but should be unnoticable for most uses as the margin is quite small.
