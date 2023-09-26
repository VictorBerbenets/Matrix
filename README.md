# Calculation of the determinant of the matrix
### About
this program calculates the determinant of the matrix
## Requirements
**cmake** version must be 3.15 or higher
## How to build
you have two options to build this project: 
### 1) for calculating integer matrix (set ON instead of *Switch*)
### 2) build the project for calculating floating point matrix(set OFF instead of *Switch*)
```bash
git@github.com:VictorBerbenets/Matrix.git
cd Matrix/
git submodule init
git submodule update
cmake -S ./ -B build/ -DCMAKE_BUILD_TYPE=Release .. -DINTEGRAL_MATRIX=<Switch>
cd build/
cmake --build .
```
