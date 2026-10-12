#include "llvm/IR/LLVMContext.h"
#include "llvm/IR/Module.h"
#include "llvm/IR/Constants.h"
#include "llvm/IR/GlobalVariable.h"
#include "llvm/Support/raw_ostream.h"
#include "llvm/IR/Function.h"

int
main() {
  llvm::LLVMContext Context;
  llvm::Module MyModule("Module", Context);

  llvm::Type *IntType = llvm::Type::getInt32Ty(Context);
  llvm::Constant *Initializer = llvm::ConstantInt::get(IntType, 42);

  new llvm::GlobalVariable(
    MyModule,
    IntType,
    false,
    llvm::GlobalValue::ExternalLinkage,
    Initializer,
    "Value"
  );

  llvm::FunctionType *Template = llvm::FunctionType::get(llvm::Type::getVoidTy(Context), false);

  llvm::Function *Foo = llvm::Function::Create(Template, llvm::GlobalValue::ExternalLinkage, "foo", MyModule);

  for (llvm::Function &MyFunction : MyModule) {
    llvm::outs() << "Function = " << MyFunction.getName() << "\n";
    llvm::outs() << "Return type = ";
    MyFunction.getReturnType()->print(llvm::outs());
    llvm::outs() << "\n";
    llvm::outs() << "Is empty = " << (MyFunction.empty() ? "Y" : "N") << "\n";
    llvm::outs() << "Is Declaration = " << (MyFunction.isDeclaration() ? "Y" : "N") << "\n";
    llvm::outs() << "Function Module = " << MyFunction.getParent()->getName() << "\n\n";
  }

  MyModule.print(llvm::outs(), nullptr);
}