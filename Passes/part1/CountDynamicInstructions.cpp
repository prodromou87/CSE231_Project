#include "llvm/Pass.h"
#include "llvm/IR/Function.h"
#include "llvm/Support/raw_ostream.h"
#include "llvm/IR/Module.h"
#include "llvm/IR/IRBuilder.h"
#include <map>
#include <vector>

using namespace llvm;
using namespace std;

namespace {
	struct CountDynamicinstructions: public FunctionPass {
		static char ID;
		CountDynamicinstructions(): FunctionPass(ID){}
		
		bool runOnFunction(Function &F)   {
			Module *M = F.getParent();
			Function *countFunc = cast<Function>(M->getOrInsertFunction("updateMap", Type::getVoidTy(M->getContext()), Type::getInt32Ty(M->getContext()), Type::getInt32Ty(M->getContext()), NULL));
			Function *printFunc = cast<Function>(M->getOrInsertFunction("printOutInstrInfo", Type::getVoidTy(M->getContext()), NULL));

			for(Function::iterator block = F.begin(); block != F.end(); block++){
				map<unsigned, unsigned> countMap;

				TerminatorInst* term = block->getTerminator();
				IRBuilder<> builder(term);

				for(BasicBlock::iterator bi = block->begin(); bi != block->end(); bi++){
					countMap[bi->getOpcode()]++;
				}

				// insert count function
				for(map<unsigned, unsigned>::iterator it = countMap.begin(); it != countMap.end(); it++){
					vector<Value *> argsV;
					Value* opCode = ConstantInt::get(Type::getInt32Ty(M->getContext()), it->first);
					Value* opCount = ConstantInt::get(Type::getInt32Ty(M->getContext()), it->second);
					argsV.push_back(opCode);
					argsV.push_back(opCount);
					builder.CreateCall(countFunc, argsV);
				}

          		// insert the print function
				for(BasicBlock::iterator it = block->begin(); it != block->end(); it++){
					if(((string)it->getOpcodeName()) == "ret"){
						vector<Value *> argsV;
						builder.CreateCall(printFunc, argsV);
					}
				} 
			}
			return true;
		}
	};  // end of struct CountDynamicinstructions
}  // end of anonymous namespace

char CountDynamicinstructions::ID = 0;
static RegisterPass<CountDynamicinstructions> X("cse231-cdi", "Developed to test LLVM and docker",
	                            false /* Only looks at CFG */,
	                            false /* Analysis Pass */);
