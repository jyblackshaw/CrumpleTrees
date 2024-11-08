# CrumpleTree Data Structure

A specialized balanced binary search tree implementation in C++ with unique balancing properties. This data structure maintains balance through level-based rules and specific rebalancing cases.

## Features

- Template-based implementation supporting generic key-value pairs
- Self-balancing operations using level-based rules
- Standard binary search tree operations (insert, remove, find)
- Multiple traversal methods (inOrder, preOrder, postOrder)
- Exception handling for element not found cases

## Key Operations

- insert(key, value): Inserts a new key-value pair and rebalances
- remove(key): Removes a key and rebalances the tree
- find(key): Retrieves the value associated with a key
- contains(key): Checks if a key exists
- getLevel(key): Returns the level of a node in the tree

## Technical Details

- Implements both single and double rotations for balancing
- Maintains level invariants during all operations
- Handles edge cases for root modifications
- Memory management with proper destructor implementation
