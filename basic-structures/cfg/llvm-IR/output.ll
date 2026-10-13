; ModuleID = 'Module'
source_filename = "Module"

declare i32 @baz()

declare i32 @bar(i32)

define void @foo(i32 %0, i32 %1) {
  %3 = alloca i32, align 4
  %4 = alloca i32, align 4
  %5 = alloca i32, align 4
  store i32 %0, ptr %3, align 4
  store i32 %1, ptr %4, align 4
  %6 = load i32, ptr %3, align 4
  %7 = load i32, ptr %4, align 4
  %8 = add i32 %6, %7
  store i32 %8, ptr %5, align 4
  %9 = load i32, ptr %5, align 4
  %10 = icmp eq i32 %9, 255
  br i1 %10, label %11, label %15

11:                                               ; preds = %2
  %12 = load i32, ptr %5, align 4
  %13 = call i32 @bar(i32 %12)
  %14 = call i32 @bar()
  store i32 %14, ptr %5, align 4
  br label %15

15:                                               ; preds = %11, %2
  %16 = load i32, ptr %5, align 4
  %17 = call i32 @bar(i32 %16)
  ret void
}
