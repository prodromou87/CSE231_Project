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
	struct BranchBias: public ModulePass {
		static char ID;
		BranchBias(): ModulePass(ID){}
		
		bool runOnModule(Module &M)   {
			Function *countFunc = cast<Function>(M.getOrInsertFunction("updateBranchInfo", Type::getVoidTy(M.getContext()), Type::getInt1Ty(M.getContext()), NULL));
			Function *printFunc = cast<Function>(M.getOrInsertFunction("printOutBranchInfo", Type::getVoidTy(M.getContext()), NULL));
			IRBuilder<> builder(M.getContext());

			for(Module::iterator func = M.begin(); func != M.end(); func++){
				for(Function::iterator block = func->begin(); block != func->end(); block++){
					map<unsigned, unsigned> countMap;

					TerminatorInst* term = block->getTerminator();
					BranchInst* branchInst = (BranchInst*)(term);

            		builder.SetInsertPoint(term);
					vector<Value *> argsV;

					// Value *taken = branchInst->getCondition();
					// argsV.push_back(taken);
					// builder.CreateCall(countFunc, argsV);	

					if (branchInst->isConditional()) {
						vector<Value *> argsV;
						Value *taken = ConstantInt::get(Type::getInt1Ty(M.getContext()), true);
						argsV.push_back(taken);
						builder.CreateCall(countFunc, argsV);
					} else {
						vector<Value *> argsV;
						Value *taken = ConstantInt::get(Type::getInt1Ty(M.getContext()), false);
						argsV.push_back(taken);
						builder.CreateCall(countFunc, argsV);	
					}

					for(BasicBlock::iterator it = block->begin(); it != block->end(); it++){
						if(func->getName() == "main" && ((string)it->getOpcodeName()) == "ret"){
							builder.SetInsertPoint(func->back().getInstList().back().getPrevNode()->getNextNode());
							vector<Value *> argsV;
							builder.CreateCall(printFunc, argsV);
						}
					}
				}
			}
			return true;
		}
	};  // end of struct BranchBias
}  // end of anonymous namespace

char BranchBias::ID = 0;
static RegisterPass<BranchBias> X("cse231-bb", "Developed to test LLVM and docker",
	                            false /* Only looks at CFG */,
	                            false /* Analysis Pass */);
