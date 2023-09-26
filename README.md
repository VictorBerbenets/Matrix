# Calculation of the determinant of the matrix
### About
this program calculates the determinant of the matrix
## Requirements
**cmake** version must be 3.15 or higher
## How to build
you have two options to build this project: 
### 1) for calculating integer matrix (set ON instead of **Switch**)
### 2) for calculating floating point matrix(set OFF instead of **Switch**)
```bash
git clone git@github.com:VictorBerbenets/Matrix.git
cd Matrix/
git submodule init
git submodule update
cmake -S ./ -B build/ -DCMAKE_BUILD_TYPE=Release .. -DINTEGRAL_MATRIX=<Switch>
cd build/
cmake --build .
```
The programm will be waiting for input data in stdin in such way:  
```bash
<matrix size> <elem1> <elem2> ... 
```
Number of elements should be exactly equal to product = **matrix size** * **matrix**
size.  
There are two working algorithms in this project. One of them is the Gauss algorithm - using for any types except integers.  
Another one is the Bareiss algorithm - using for only integer(not unsigned) types.
## How to run tests:
### You can run unit tests:
```bash
./tests/unit
```
### Or you can run end2end tests:
```bash
bash ../tests/end2end/test_runner.sh <tests_number> <matrix_size> <max_determinant>
```
**tests_number** - the number of tests you want to generate.  
**matrix_size**  - dimensions of the matrices to be generated.  
**max_determinant** - the max determinant of generated matrices.  
After running you can see a generated directory - tests/end2end/resources/.  
There will be the tests themselves and the answers to them.
