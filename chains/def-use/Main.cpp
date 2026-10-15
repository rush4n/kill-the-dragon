#include "llvm/IR/Function.h"
#include "llvm/IR/IRBuilder.h"
#include "llvm/IR/LLVMContext.h"
#include "llvm/IR/Module.h"
#include "llvm/IR/Type.h"
#include "llvm/IR/Use.h"
#include "llvm/IR/Value.h"
#include "llvm/Support/Debug.h"

using namespace llvm;

int
main() {
  LLVMContext Context;
  Module MyModule("Module", Context);

  /* TYPES */
  Type *Int32Ty = Type::getInt32Ty(Context);

  /* FUNCTIONS */
  FunctionType *FooTy = FunctionType::get(Int32Ty, ArrayRef({Int32Ty}), false);
  Function *Foo = cast<Function>(MyModule.getOrInsertFunction("foo", FooTy).getCallee());

  /* BASIC BLOCKS */
  BasicBlock *Entry = BasicBlock::Create(Context, "entry", Foo);

  /* POPULATE ENTRY */
  IRBuilder Builder(Entry);
  Value *A = Foo->getArg(0);
  Value *I = Builder.CreateAdd(A, A, "sum1");
  Value *I2 = Builder.CreateAdd(A, I, "sum2");
  Value *I3 = Builder.CreateAdd(I2, A, "sum3");
  Builder.CreateRet(I3);

  for (Use &MyUse : A->uses()) {
    outs() << MyUse.getOperandNo() << "\n";
    MyUse.getUser()->print(outs());
    outs() << "\n";
  }

    MyModule.print(outs(), nullptr);

}