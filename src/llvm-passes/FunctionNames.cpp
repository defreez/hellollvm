#include "llvm/Pass.h"
#include "llvm/IR/Function.h"
#include "llvm/Support/raw_ostream.h"
#include "llvm/IR/DebugInfo.h"
#include "llvm/IR/InstIterator.h"
#include <iostream>
#include <string>
#include "FunctionNames.h"

using namespace llvm;
using namespace std;

bool FunctionNames::runOnModule(llvm::Module &M) {
}

void FunctionNames::getAnalysisUsage(AnalysisUsage &AU) const {
  AU.setPreservesAll();
}

char FunctionNames::ID = 0;
static RegisterPass<FunctionNames> X("function-names",
                                        "Hello LLVM world!",
                                        false, false);
