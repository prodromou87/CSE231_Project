/LLVM_ROOT/build/bin/clang -c -O0 ./test1.c -emit-llvm -S -o ./test1-c.ll
/LLVM_ROOT/build/bin/clang++ -c -O0 ./test1.cpp -emit-llvm -S -o ./test1.ll
/LLVM_ROOT/build/bin/clang++ -c /lib231/lib231.cpp -emit-llvm -S -o ./lib231.ll
/LLVM_ROOT/build/bin/clang++ -c ./test1-main.cpp -emit-llvm -S -o ./test1-main.ll

/solution/opt -cse231-cdi < ./test1.ll -o ./test1-cdi.bc > /dev/null
/LLVM_ROOT/build/bin/llvm-dis ./test1-cdi.bc
/LLVM_ROOT/build/bin/clang++ ./test1-cdi.ll ./lib231.ll ./test1-main.ll -o ./cdi_test1

ret	1
br	2
add	2
alloca	2
load	4
store	3
icmp	1
====================
ret	1
br	2
add	2
alloca	2
load	4
store	3
icmp	1

opt -load /LLVM_ROOT/build/lib/CSE231.so -cse231-cdi < ./test1.ll -o ./test1-cdi.bc > /dev/null
/LLVM_ROOT/build/bin/llvm-dis ./test1-cdi.bc
/LLVM_ROOT/build/bin/clang++ ./test1-cdi.ll ./lib231.ll ./test1-main.ll -o ./cdi_test1

updateInstrInfo
printOutInstrInfo