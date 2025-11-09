# Super Rotation System

0 = spawn state
R = state resulting from a clockwise rotation
L = state resulting from a counterclockwise rotation
2 = state resulting from 2 successive rotations in either direction from spawn.

---

# J, L, S, T, Z Offset Data

|   | Test 1   | Test 2   | Test 3   | Test 4   | Test 5   |
|---|----------|----------|----------|----------|----------|
| 0 | ( 0,  0) | ( 0,  0) | ( 0,  0) | ( 0,  0) | ( 0,  0) |
| R | ( 0,  0) | (+1,  0) | (+1, -1) | ( 0, +2) | (+1, +2) |
| 2 | ( 0,  0) | ( 0,  0) | ( 0,  0) | ( 0,  0) | ( 0,  0) |
| L | ( 0,  0) | (-1,  0) | (-1, -1) | ( 0, +2) | (-1, +2) |

---

# I Offset Data

|   | Test 1   | Test 2   | Test 3   | Test 4   | Test 5   |
|---|----------|----------|----------|----------|----------|
| 0 | ( 0,  0) | (-1,  0) | (+2,  0) | (-1,  0) | (+2,  0) |
| R | (-1,  0) | ( 0,  0) | ( 0,  0) | ( 0, +1) | ( 0, -2) |
| 2 | (-1, +1) | (+1, +1) | (-2, +1) | (+1,  0) | (-2,  0) |
| L | ( 0, +1) | ( 0, +1) | ( 0, +1) | ( 0, -1) | ( 0, +2) |

---

# O Offset Data

|   | Test 1   |
|---|----------|
| 0 | ( 0,  0) |
| R | ( 0, -1) |
| 2 | (-1, -1) |
| L | (-1,  0) |

