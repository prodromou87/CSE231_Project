#include "llvm/Pass.h"
#include "llvm/IR/Function.h"
#include "llvm/Support/raw_ostream.h"
#include "llvm/IR/Module.h"

using namespace llvm;

namespace {
	struct LLVMCountStatic : public ModulePass {	
		static char ID;
		LLVMCountStatic() : ModulePass(ID) {}

		bool runOnModule(Module &M) override {
			std::map<std::string, int> map;
			int count = 0;

			for (Module::iterator mi = M.begin(), me = M.end(); mi != me; mi++) {
				for (Function::iterator fi = mi->begin(), fe = mi->end(); fi != fe; fi++) {
					for (BasicBlock::iterator bi = fi->begin(), be = fi->end(); bi != be; bi++) {
						count++;
						// add into the map
						// errs() << bi->getOpcodeName() << "\n";
						map[bi->getOpcodeName()]++;
					}
				}
			}

			for (std::map<std::string,int>::iterator it = map.begin(), ie = map.end(); it != ie; it++) {
				if (it->second != 0) {
					errs() << it->first << "\t" << it->second << "\n";
				}
			}

		    return false;
		}
	}; // end of struct LLVMCountStatic
}  // end of anonymous namespace

char LLVMCountStatic::ID = 0;
static RegisterPass<LLVMCountStatic> X("cse231-csi", "Developed to test LLVM and docker",
                             false /* Only looks at CFG */,
                             false /* Analysis Pass */);
