#!/bin/bash

OBJECT_COPY="/Users/kammce/.conan2/p/b/arm-g788a41ed25167/p/bin/bin/arm-none-eabi-objcopy"
LIB_PREFIX="/Users/kammce/.conan2/p/b/arm-g788a41ed25167/p/bin/lib/gcc/arm-none-eabi/12.2.1"
LIST=(
"thumb/v7e-m+fp/softfp/libgcc.a"
"thumb/v7e-m+fp/hard/libgcc.a"
"thumb/v7e-m/nofp/libgcc.a"
"thumb/v7/nofp/libgcc.a"
"thumb/v8-a/nofp/libgcc.a"
"thumb/v8-a+simd/softfp/libgcc.a"
"thumb/v8-a+simd/hard/libgcc.a"
"thumb/v7ve+simd/softfp/libgcc.a"
"thumb/v7ve+simd/hard/libgcc.a"
"thumb/v7-a+fp/softfp/libgcc.a"
"thumb/v7-a+fp/hard/libgcc.a"
"thumb/nofp/libgcc.a"
"thumb/v8-m.main+fp/softfp/libgcc.a"
"thumb/v8-m.main+fp/hard/libgcc.a"
"thumb/v7-m/nofp/libgcc.a"
"thumb/v7+fp/softfp/libgcc.a"
"thumb/v7+fp/hard/libgcc.a"
"thumb/v7-a+simd/softfp/libgcc.a"
"thumb/v7-a+simd/hard/libgcc.a"
"thumb/v8-m.base/nofp/libgcc.a"
"thumb/v7-r+fp.sp/softfp/libgcc.a"
"thumb/v7-r+fp.sp/hard/libgcc.a"
"thumb/v6-m/nofp/libgcc.a"
"thumb/v8-m.main+dp/softfp/libgcc.a"
"thumb/v8-m.main+dp/hard/libgcc.a"
"thumb/v8-m.main/nofp/libgcc.a"
"thumb/v7e-m+dp/softfp/libgcc.a"
"thumb/v7e-m+dp/hard/libgcc.a"
"thumb/v8.1-m.main+mve/hard/libgcc.a"
"thumb/v7-a/nofp/libgcc.a"
"arm/v5te/softfp/libgcc.a"
"arm/v5te/hard/libgcc.a"
"libgcc.a"
)

SYMBOL_TO_WEAKEN="search_EIT_table"

for library in ${LIST[@]}; do
  $OBJECT_COPY $LIB_PREFIX/$library --globalize-symbol=$SYMBOL_TO_WEAKEN --weaken-symbol=$SYMBOL_TO_WEAKEN $LIB_PREFIX/$library
done
