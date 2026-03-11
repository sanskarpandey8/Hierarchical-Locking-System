# Hierarchical Locking System 

## Overview

This project implements a **Hierarchical Locking System** on an **M-ary Tree** to manage concurrent access to resources arranged in a hierarchical structure.

Such locking mechanisms are widely used in:

* File systems
* Database management systems
* Distributed systems
* Resource management systems

The system ensures that **no two conflicting locks occur between ancestors and descendants**.

---

##  Operations Supported

### 1️⃣ `lock(node, userId)`

Grants exclusive access to a node if:

* The node is **not already locked**
* **No ancestor is locked**
* **No descendant is locked**

---

### 2️⃣ `unlock(node, userId)`

Unlocks a node only if:

* The node is **currently locked**
* The **same user** previously locked it

---

### 3️⃣ `upgradeLock(node, userId)`

Upgrades locks from descendants to an ancestor node if:

* The ancestor node is **not already locked**
* The node has **at least one locked descendant**
* **All locked descendants belong to the same user**

After upgrading:

* All descendant locks are released
* The ancestor node becomes locked

---

##  Data Structures Used

* **M-ary Tree**
* **Hash Map (unordered_map)**
* **Queue (BFS traversal)**
* **Counters for ancestor/descendant locks**

---

##  Time Complexity

| Operation | Complexity      |
| --------- | --------------- |
| Lock      | O(H)            |
| Unlock    | O(H)            |
| Upgrade   | O(N) worst case |

Where:

* **H** = height of the tree
* **N** = number of nodes

---

##  Input Format

1. **N** → Number of nodes in the tree `(1 < N < 500000)`
2. **M** → Maximum number of children per node `(1 < M < 30)`
3. **Q** → Number of queries `(1 < Q < 500000)`
4. **Node names** → Unique names representing nodes
5. **Queries**

```
1 nodeName userId → Lock
2 nodeName userId → Unlock
3 nodeName userId → UpgradeLock
```

---

## Example

### Input

```
7
2
5
Root
A
B
C
D
E
F
1 C 9
1 D 9
3 A 9
2 D 9
2 A 9
```

### Output

```
true
true
true
false
true
```

---

##  How to Run

Compile the program:

```
g++ main.cpp -o lockSystem
```

Run the program:

```
./lockSystem
```

---

## Concepts Demonstrated

* Tree Data Structure
* BFS Traversal
* Locking Mechanisms
* Efficient State Tracking
* Hash-based Node Lookup

---

## Author

**Sanskar Pandey**

B.Tech Student | Software Development Enthusiast
