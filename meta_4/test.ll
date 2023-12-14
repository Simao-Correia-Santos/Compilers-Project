; ModuleID = 'test.c'
source_filename = "test.c"
target datalayout = "e-m:e-p270:32:32-p271:32:32-p272:64:64-i64:64-f80:128-n8:16:32:64-S128"
target triple = "x86_64-pc-linux-gnu"

@global_char = dso_local global i8 0, align 1
@global_char1 = dso_local global i8 -1, align 1
@global_char2 = dso_local global i8 4, align 1
@global_char3 = dso_local global i8 36, align 1
@global_char4 = dso_local global i8 -28, align 1
@global_a = dso_local global i8 65, align 1
@global_b = dso_local global i16 66, align 2
@global_c = dso_local global i32 67, align 4
@global_d = dso_local global double 4.000000e+00, align 8

; Function Attrs: noinline nounwind optnone uwtable
define dso_local i32 @main() #0 {
  %1 = alloca i32, align 4
  %2 = alloca i8, align 1
  %3 = alloca i16, align 2
  %4 = alloca i32, align 4
  %5 = alloca double, align 8
  %6 = alloca i32, align 4
  store i32 0, i32* %1, align 4
  store i8 68, i8* %2, align 1
  store i16 69, i16* %3, align 2
  store i32 70, i32* %4, align 4
  store double 4.000000e+00, double* %5, align 8
  store i32 -2147483648, i32* %6, align 4
  store i32 -2147483648, i32* %6, align 4
  %7 = load i8, i8* %2, align 1
  %8 = sext i8 %7 to i32
  store i32 %8, i32* %6, align 4
  %9 = load i8, i8* @global_a, align 1
  store i8 %9, i8* %2, align 1
  %10 = load i8, i8* %2, align 1
  %11 = sext i8 %10 to i32
  %12 = sub nsw i32 0, %11
  %13 = sub nsw i32 0, %12
  %14 = sub nsw i32 0, %13
  %15 = sub nsw i32 0, %14
  %16 = call i32 (i32, ...) bitcast (i32 (...)* @putchar to i32 (i32, ...)*)(i32 noundef %15)
  %17 = load i32, i32* %6, align 4
  %18 = trunc i32 %17 to i8
  store i8 %18, i8* %2, align 1
  %19 = load i16, i16* %3, align 2
  %20 = sext i16 %19 to i32
  store i32 %20, i32* %6, align 4
  %21 = load i16, i16* @global_b, align 2
  store i16 %21, i16* %3, align 2
  %22 = load i16, i16* %3, align 2
  %23 = sext i16 %22 to i32
  %24 = call i32 (i32, ...) bitcast (i32 (...)* @putchar to i32 (i32, ...)*)(i32 noundef %23)
  %25 = load i32, i32* %6, align 4
  %26 = trunc i32 %25 to i16
  store i16 %26, i16* %3, align 2
  %27 = load i32, i32* %4, align 4
  store i32 %27, i32* %6, align 4
  %28 = load i32, i32* @global_c, align 4
  store i32 %28, i32* %4, align 4
  %29 = load i32, i32* %4, align 4
  %30 = sub nsw i32 0, %29
  %31 = sub nsw i32 0, %30
  %32 = call i32 (i32, ...) bitcast (i32 (...)* @putchar to i32 (i32, ...)*)(i32 noundef %31)
  %33 = load i32, i32* %6, align 4
  store i32 %33, i32* %4, align 4
  %34 = load i8, i8* %2, align 1
  %35 = sext i8 %34 to i32
  %36 = call i32 (i32, ...) bitcast (i32 (...)* @putchar to i32 (i32, ...)*)(i32 noundef %35)
  %37 = load i16, i16* %3, align 2
  %38 = sext i16 %37 to i32
  %39 = call i32 (i32, ...) bitcast (i32 (...)* @putchar to i32 (i32, ...)*)(i32 noundef %38)
  %40 = load i32, i32* %4, align 4
  %41 = call i32 (i32, ...) bitcast (i32 (...)* @putchar to i32 (i32, ...)*)(i32 noundef %40)
  %42 = load i8, i8* %2, align 1
  store i8 %42, i8* %2, align 1
  store i16 -66, i16* %3, align 2
  %43 = load i8, i8* %2, align 1
  %44 = sext i8 %43 to i32
  %45 = sub nsw i32 0, %44
  store i32 %45, i32* %4, align 4
  %46 = load i8, i8* %2, align 1
  %47 = sext i8 %46 to i32
  %48 = call i32 (i32, ...) bitcast (i32 (...)* @putchar to i32 (i32, ...)*)(i32 noundef %47)
  %49 = load i16, i16* %3, align 2
  %50 = sext i16 %49 to i32
  %51 = sub nsw i32 0, %50
  %52 = call i32 (i32, ...) bitcast (i32 (...)* @putchar to i32 (i32, ...)*)(i32 noundef %51)
  %53 = call i32 (i32, ...) bitcast (i32 (...)* @putchar to i32 (i32, ...)*)(i32 noundef 66)
  %54 = call i32 (i32, ...) bitcast (i32 (...)* @putchar to i32 (i32, ...)*)(i32 noundef 66)
  %55 = load i32, i32* %4, align 4
  %56 = sub nsw i32 0, %55
  %57 = sub nsw i32 0, %56
  %58 = sub nsw i32 0, %57
  %59 = sub nsw i32 0, %58
  %60 = sub nsw i32 0, %59
  %61 = sub nsw i32 0, %60
  %62 = sub nsw i32 0, %61
  %63 = call i32 (i32, ...) bitcast (i32 (...)* @putchar to i32 (i32, ...)*)(i32 noundef %62)
  %64 = call i32 (i32, ...) bitcast (i32 (...)* @putchar to i32 (i32, ...)*)(i32 noundef 10)
  %65 = load i32, i32* %4, align 4
  %66 = sub nsw i32 0, %65
  %67 = sub nsw i32 0, %66
  %68 = sub nsw i32 0, %67
  ret i32 %68
}

declare i32 @putchar(...) #1

attributes #0 = { noinline nounwind optnone uwtable "frame-pointer"="all" "min-legal-vector-width"="0" "no-trapping-math"="true" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+cx8,+fxsr,+mmx,+sse,+sse2,+x87" "tune-cpu"="generic" }
attributes #1 = { "frame-pointer"="all" "no-trapping-math"="true" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+cx8,+fxsr,+mmx,+sse,+sse2,+x87" "tune-cpu"="generic" }

!llvm.module.flags = !{!0, !1, !2, !3, !4}
!llvm.ident = !{!5}

!0 = !{i32 1, !"wchar_size", i32 4}
!1 = !{i32 7, !"PIC Level", i32 2}
!2 = !{i32 7, !"PIE Level", i32 2}
!3 = !{i32 7, !"uwtable", i32 1}
!4 = !{i32 7, !"frame-pointer", i32 2}
!5 = !{!"Ubuntu clang version 14.0.0-1ubuntu1.1"}
