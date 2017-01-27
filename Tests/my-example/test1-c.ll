; ModuleID = './test1.c'
source_filename = "./test1.c"
target datalayout = "e-m:e-i64:64-f80:128-n8:16:32:64-S128"
target triple = "x86_64-unknown-linux-gnu"

; Function Attrs: nounwind uwtable
define i32 @foo(i32) #0 {
  %2 = alloca i32, align 4
  %3 = alloca i32, align 4
  store volatile i32 %0, i32* %2, align 4
  store volatile i32 10, i32* %3, align 4
  %4 = load volatile i32, i32* %2, align 4
  %5 = icmp ugt i32 %4, 5
  br i1 %5, label %6, label %9

; <label>:6:                                      ; preds = %1
  %7 = load volatile i32, i32* %3, align 4
  %8 = add i32 %7, 5
  store volatile i32 %8, i32* %3, align 4
  br label %12

; <label>:9:                                      ; preds = %1
  %10 = load volatile i32, i32* %3, align 4
  %11 = add i32 %10, 50
  store volatile i32 %11, i32* %3, align 4
  br label %12

; <label>:12:                                     ; preds = %9, %6
  %13 = load volatile i32, i32* %3, align 4
  %14 = load volatile i32, i32* %2, align 4
  %15 = add i32 %13, %14
  ret i32 %15
}

attributes #0 = { nounwind uwtable "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-jump-tables"="false" "no-nans-fp-math"="false" "no-signed-zeros-fp-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2,+x87" "unsafe-fp-math"="false" "use-soft-float"="false" }

!llvm.ident = !{!0}

!0 = !{!"clang version 3.9.1 (branches/release_39 291077)"}
