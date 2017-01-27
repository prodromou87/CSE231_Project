#include "llvm/Pass.h"
#include "llvm/IR/Function.h"
#include "llvm/Support/raw_ostream.h"
#include "llvm/IR/InstIterator.h"

using namespace llvm;

namespace {
	struct CountStaticInstructions : public FunctionPass {	
		static char ID;
		CountStaticInstructions() : FunctionPass(ID) {}

		bool runOnFunction(Function &F) override {
			std::map<std::string, int> map;
			int count = 0;

			for (inst_iterator fi = inst_begin(F), fe = inst_end(F); fi != fe; fi++) {
				count++;
				map[fi->getOpcodeName()]++;
			}

			for (std::map<std::string,int>::iterator it = map.begin(), ie = map.end(); it != ie; it++) {
				if (it->second != 0) {
					errs() << it->first << "\t" << it->second << "\n";
				}
			}

			return false;
		}
	}; // end of struct CountStaticInstructions
}  // end of anonymous namespace

char CountStaticInstructions::ID = 0;
static RegisterPass<CountStaticInstructions> X("cse231-csi", "Developed to test LLVM and docker",
                             false /* Only looks at CFG */,
                             false /* Analysis Pass */);
