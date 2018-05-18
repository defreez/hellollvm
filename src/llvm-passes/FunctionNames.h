#ifndef FUNCTIONNAMES_H
#define FUNCTIONNAMES_H

#include "llvm/Pass.h"
#include "llvm/IR/Module.h"

struct FunctionNames : public llvm::ModulePass {
  static char ID;

 FunctionNames() : llvm::ModulePass(ID) {}

  virtual bool runOnModule(llvm::Module &M) override;

  virtual void getAnalysisUsage(llvm::AnalysisUsage &AU) const;
};

#endif
