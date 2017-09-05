// Copyright (c) 2012 DotNetAnywhere
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
// THE SOFTWARE.

#include "Compat.h"
#include "Sys.h"

#include "MetaData.h"

#include "Types.h"
#include "Type.h"
#include "RVA.h"

#include <stddef.h>

#define EXPAND_(X) X

//
// the F# script used to generate the following macros (can be reduced!) :
//
// let genTypeOffset n =
//     printf "#define TYPE_ARG_N("
//     for i in 1..n do
//         printf "_%d, " i
//     printfn "N, ...) N\n"
// 
//     for i in 1..n do
//         printf "#define TYPE_OFFSET_%d(S, " i
//         for j in 0..i - 1 do
//             if j = i - 1
//             then printf "_%d" j
//             else printf "_%d, " j
//         printf ") { .size = sizeof(S), .offsets = { "
//         for j in 0..i - 1 do
//             if j = i - 1
//             then printf "offsetof(S, _%d)" j
//             else printf "offsetof(S, _%d), " j
//         printfn " } }\n"
// 
//     printf "#define TYPE_OFFSET_LIST() "
//     for i in n.. -1 ..1 do
//         if i = 1 
//         then printf "TYPE_OFFSET_%d" i
//         else printf "TYPE_OFFSET_%d, " i
//     printfn ""
//
#define TYPE_ARG_N(_1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17, _18, _19, _20, _21, _22, _23, _24, _25, _26, _27, _28, _29, _30, _31, _32, _33, _34, _35, _36, _37, _38, _39, _40, _41, _42, _43, _44, _45, _46, _47, _48, _49, _50, _51, _52, _53, _54, _55, _56, _57, _58, _59, _60, _61, _62, _63, _64, N, ...) N

#define TYPE_OFFSET_1(S, _0) { .size = sizeof(S), .offsets = { offsetof(S, _0) } }
#define TYPE_OFFSET_2(S, _0, _1) { .size = sizeof(S), .offsets = { offsetof(S, _0), offsetof(S, _1) } }
#define TYPE_OFFSET_3(S, _0, _1, _2) { .size = sizeof(S), .offsets = { offsetof(S, _0), offsetof(S, _1), offsetof(S, _2) } }
#define TYPE_OFFSET_4(S, _0, _1, _2, _3) { .size = sizeof(S), .offsets = { offsetof(S, _0), offsetof(S, _1), offsetof(S, _2), offsetof(S, _3) } }
#define TYPE_OFFSET_5(S, _0, _1, _2, _3, _4) { .size = sizeof(S), .offsets = { offsetof(S, _0), offsetof(S, _1), offsetof(S, _2), offsetof(S, _3), offsetof(S, _4) } }
#define TYPE_OFFSET_6(S, _0, _1, _2, _3, _4, _5) { .size = sizeof(S), .offsets = { offsetof(S, _0), offsetof(S, _1), offsetof(S, _2), offsetof(S, _3), offsetof(S, _4), offsetof(S, _5) } }
#define TYPE_OFFSET_7(S, _0, _1, _2, _3, _4, _5, _6) { .size = sizeof(S), .offsets = { offsetof(S, _0), offsetof(S, _1), offsetof(S, _2), offsetof(S, _3), offsetof(S, _4), offsetof(S, _5), offsetof(S, _6) } }
#define TYPE_OFFSET_8(S, _0, _1, _2, _3, _4, _5, _6, _7) { .size = sizeof(S), .offsets = { offsetof(S, _0), offsetof(S, _1), offsetof(S, _2), offsetof(S, _3), offsetof(S, _4), offsetof(S, _5), offsetof(S, _6), offsetof(S, _7) } }
#define TYPE_OFFSET_9(S, _0, _1, _2, _3, _4, _5, _6, _7, _8) { .size = sizeof(S), .offsets = { offsetof(S, _0), offsetof(S, _1), offsetof(S, _2), offsetof(S, _3), offsetof(S, _4), offsetof(S, _5), offsetof(S, _6), offsetof(S, _7), offsetof(S, _8) } }
#define TYPE_OFFSET_10(S, _0, _1, _2, _3, _4, _5, _6, _7, _8, _9) { .size = sizeof(S), .offsets = { offsetof(S, _0), offsetof(S, _1), offsetof(S, _2), offsetof(S, _3), offsetof(S, _4), offsetof(S, _5), offsetof(S, _6), offsetof(S, _7), offsetof(S, _8), offsetof(S, _9) } }
#define TYPE_OFFSET_11(S, _0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10) { .size = sizeof(S), .offsets = { offsetof(S, _0), offsetof(S, _1), offsetof(S, _2), offsetof(S, _3), offsetof(S, _4), offsetof(S, _5), offsetof(S, _6), offsetof(S, _7), offsetof(S, _8), offsetof(S, _9), offsetof(S, _10) } }
#define TYPE_OFFSET_12(S, _0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11) { .size = sizeof(S), .offsets = { offsetof(S, _0), offsetof(S, _1), offsetof(S, _2), offsetof(S, _3), offsetof(S, _4), offsetof(S, _5), offsetof(S, _6), offsetof(S, _7), offsetof(S, _8), offsetof(S, _9), offsetof(S, _10), offsetof(S, _11) } }
#define TYPE_OFFSET_13(S, _0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12) { .size = sizeof(S), .offsets = { offsetof(S, _0), offsetof(S, _1), offsetof(S, _2), offsetof(S, _3), offsetof(S, _4), offsetof(S, _5), offsetof(S, _6), offsetof(S, _7), offsetof(S, _8), offsetof(S, _9), offsetof(S, _10), offsetof(S, _11), offsetof(S, _12) } }
#define TYPE_OFFSET_14(S, _0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13) { .size = sizeof(S), .offsets = { offsetof(S, _0), offsetof(S, _1), offsetof(S, _2), offsetof(S, _3), offsetof(S, _4), offsetof(S, _5), offsetof(S, _6), offsetof(S, _7), offsetof(S, _8), offsetof(S, _9), offsetof(S, _10), offsetof(S, _11), offsetof(S, _12), offsetof(S, _13) } }
#define TYPE_OFFSET_15(S, _0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14) { .size = sizeof(S), .offsets = { offsetof(S, _0), offsetof(S, _1), offsetof(S, _2), offsetof(S, _3), offsetof(S, _4), offsetof(S, _5), offsetof(S, _6), offsetof(S, _7), offsetof(S, _8), offsetof(S, _9), offsetof(S, _10), offsetof(S, _11), offsetof(S, _12), offsetof(S, _13), offsetof(S, _14) } }
#define TYPE_OFFSET_16(S, _0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15) { .size = sizeof(S), .offsets = { offsetof(S, _0), offsetof(S, _1), offsetof(S, _2), offsetof(S, _3), offsetof(S, _4), offsetof(S, _5), offsetof(S, _6), offsetof(S, _7), offsetof(S, _8), offsetof(S, _9), offsetof(S, _10), offsetof(S, _11), offsetof(S, _12), offsetof(S, _13), offsetof(S, _14), offsetof(S, _15) } }
#define TYPE_OFFSET_17(S, _0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16) { .size = sizeof(S), .offsets = { offsetof(S, _0), offsetof(S, _1), offsetof(S, _2), offsetof(S, _3), offsetof(S, _4), offsetof(S, _5), offsetof(S, _6), offsetof(S, _7), offsetof(S, _8), offsetof(S, _9), offsetof(S, _10), offsetof(S, _11), offsetof(S, _12), offsetof(S, _13), offsetof(S, _14), offsetof(S, _15), offsetof(S, _16) } }
#define TYPE_OFFSET_18(S, _0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17) { .size = sizeof(S), .offsets = { offsetof(S, _0), offsetof(S, _1), offsetof(S, _2), offsetof(S, _3), offsetof(S, _4), offsetof(S, _5), offsetof(S, _6), offsetof(S, _7), offsetof(S, _8), offsetof(S, _9), offsetof(S, _10), offsetof(S, _11), offsetof(S, _12), offsetof(S, _13), offsetof(S, _14), offsetof(S, _15), offsetof(S, _16), offsetof(S, _17) } }
#define TYPE_OFFSET_19(S, _0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17, _18) { .size = sizeof(S), .offsets = { offsetof(S, _0), offsetof(S, _1), offsetof(S, _2), offsetof(S, _3), offsetof(S, _4), offsetof(S, _5), offsetof(S, _6), offsetof(S, _7), offsetof(S, _8), offsetof(S, _9), offsetof(S, _10), offsetof(S, _11), offsetof(S, _12), offsetof(S, _13), offsetof(S, _14), offsetof(S, _15), offsetof(S, _16), offsetof(S, _17), offsetof(S, _18) } }
#define TYPE_OFFSET_20(S, _0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17, _18, _19) { .size = sizeof(S), .offsets = { offsetof(S, _0), offsetof(S, _1), offsetof(S, _2), offsetof(S, _3), offsetof(S, _4), offsetof(S, _5), offsetof(S, _6), offsetof(S, _7), offsetof(S, _8), offsetof(S, _9), offsetof(S, _10), offsetof(S, _11), offsetof(S, _12), offsetof(S, _13), offsetof(S, _14), offsetof(S, _15), offsetof(S, _16), offsetof(S, _17), offsetof(S, _18), offsetof(S, _19) } }
#define TYPE_OFFSET_21(S, _0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17, _18, _19, _20) { .size = sizeof(S), .offsets = { offsetof(S, _0), offsetof(S, _1), offsetof(S, _2), offsetof(S, _3), offsetof(S, _4), offsetof(S, _5), offsetof(S, _6), offsetof(S, _7), offsetof(S, _8), offsetof(S, _9), offsetof(S, _10), offsetof(S, _11), offsetof(S, _12), offsetof(S, _13), offsetof(S, _14), offsetof(S, _15), offsetof(S, _16), offsetof(S, _17), offsetof(S, _18), offsetof(S, _19), offsetof(S, _20) } }
#define TYPE_OFFSET_22(S, _0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17, _18, _19, _20, _21) { .size = sizeof(S), .offsets = { offsetof(S, _0), offsetof(S, _1), offsetof(S, _2), offsetof(S, _3), offsetof(S, _4), offsetof(S, _5), offsetof(S, _6), offsetof(S, _7), offsetof(S, _8), offsetof(S, _9), offsetof(S, _10), offsetof(S, _11), offsetof(S, _12), offsetof(S, _13), offsetof(S, _14), offsetof(S, _15), offsetof(S, _16), offsetof(S, _17), offsetof(S, _18), offsetof(S, _19), offsetof(S, _20), offsetof(S, _21) } }
#define TYPE_OFFSET_23(S, _0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17, _18, _19, _20, _21, _22) { .size = sizeof(S), .offsets = { offsetof(S, _0), offsetof(S, _1), offsetof(S, _2), offsetof(S, _3), offsetof(S, _4), offsetof(S, _5), offsetof(S, _6), offsetof(S, _7), offsetof(S, _8), offsetof(S, _9), offsetof(S, _10), offsetof(S, _11), offsetof(S, _12), offsetof(S, _13), offsetof(S, _14), offsetof(S, _15), offsetof(S, _16), offsetof(S, _17), offsetof(S, _18), offsetof(S, _19), offsetof(S, _20), offsetof(S, _21), offsetof(S, _22) } }
#define TYPE_OFFSET_24(S, _0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17, _18, _19, _20, _21, _22, _23) { .size = sizeof(S), .offsets = { offsetof(S, _0), offsetof(S, _1), offsetof(S, _2), offsetof(S, _3), offsetof(S, _4), offsetof(S, _5), offsetof(S, _6), offsetof(S, _7), offsetof(S, _8), offsetof(S, _9), offsetof(S, _10), offsetof(S, _11), offsetof(S, _12), offsetof(S, _13), offsetof(S, _14), offsetof(S, _15), offsetof(S, _16), offsetof(S, _17), offsetof(S, _18), offsetof(S, _19), offsetof(S, _20), offsetof(S, _21), offsetof(S, _22), offsetof(S, _23) } }
#define TYPE_OFFSET_25(S, _0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17, _18, _19, _20, _21, _22, _23, _24) { .size = sizeof(S), .offsets = { offsetof(S, _0), offsetof(S, _1), offsetof(S, _2), offsetof(S, _3), offsetof(S, _4), offsetof(S, _5), offsetof(S, _6), offsetof(S, _7), offsetof(S, _8), offsetof(S, _9), offsetof(S, _10), offsetof(S, _11), offsetof(S, _12), offsetof(S, _13), offsetof(S, _14), offsetof(S, _15), offsetof(S, _16), offsetof(S, _17), offsetof(S, _18), offsetof(S, _19), offsetof(S, _20), offsetof(S, _21), offsetof(S, _22), offsetof(S, _23), offsetof(S, _24) } }
#define TYPE_OFFSET_26(S, _0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17, _18, _19, _20, _21, _22, _23, _24, _25) { .size = sizeof(S), .offsets = { offsetof(S, _0), offsetof(S, _1), offsetof(S, _2), offsetof(S, _3), offsetof(S, _4), offsetof(S, _5), offsetof(S, _6), offsetof(S, _7), offsetof(S, _8), offsetof(S, _9), offsetof(S, _10), offsetof(S, _11), offsetof(S, _12), offsetof(S, _13), offsetof(S, _14), offsetof(S, _15), offsetof(S, _16), offsetof(S, _17), offsetof(S, _18), offsetof(S, _19), offsetof(S, _20), offsetof(S, _21), offsetof(S, _22), offsetof(S, _23), offsetof(S, _24), offsetof(S, _25) } }
#define TYPE_OFFSET_27(S, _0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17, _18, _19, _20, _21, _22, _23, _24, _25, _26) { .size = sizeof(S), .offsets = { offsetof(S, _0), offsetof(S, _1), offsetof(S, _2), offsetof(S, _3), offsetof(S, _4), offsetof(S, _5), offsetof(S, _6), offsetof(S, _7), offsetof(S, _8), offsetof(S, _9), offsetof(S, _10), offsetof(S, _11), offsetof(S, _12), offsetof(S, _13), offsetof(S, _14), offsetof(S, _15), offsetof(S, _16), offsetof(S, _17), offsetof(S, _18), offsetof(S, _19), offsetof(S, _20), offsetof(S, _21), offsetof(S, _22), offsetof(S, _23), offsetof(S, _24), offsetof(S, _25), offsetof(S, _26) } }
#define TYPE_OFFSET_28(S, _0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17, _18, _19, _20, _21, _22, _23, _24, _25, _26, _27) { .size = sizeof(S), .offsets = { offsetof(S, _0), offsetof(S, _1), offsetof(S, _2), offsetof(S, _3), offsetof(S, _4), offsetof(S, _5), offsetof(S, _6), offsetof(S, _7), offsetof(S, _8), offsetof(S, _9), offsetof(S, _10), offsetof(S, _11), offsetof(S, _12), offsetof(S, _13), offsetof(S, _14), offsetof(S, _15), offsetof(S, _16), offsetof(S, _17), offsetof(S, _18), offsetof(S, _19), offsetof(S, _20), offsetof(S, _21), offsetof(S, _22), offsetof(S, _23), offsetof(S, _24), offsetof(S, _25), offsetof(S, _26), offsetof(S, _27) } }
#define TYPE_OFFSET_29(S, _0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17, _18, _19, _20, _21, _22, _23, _24, _25, _26, _27, _28) { .size = sizeof(S), .offsets = { offsetof(S, _0), offsetof(S, _1), offsetof(S, _2), offsetof(S, _3), offsetof(S, _4), offsetof(S, _5), offsetof(S, _6), offsetof(S, _7), offsetof(S, _8), offsetof(S, _9), offsetof(S, _10), offsetof(S, _11), offsetof(S, _12), offsetof(S, _13), offsetof(S, _14), offsetof(S, _15), offsetof(S, _16), offsetof(S, _17), offsetof(S, _18), offsetof(S, _19), offsetof(S, _20), offsetof(S, _21), offsetof(S, _22), offsetof(S, _23), offsetof(S, _24), offsetof(S, _25), offsetof(S, _26), offsetof(S, _27), offsetof(S, _28) } }
#define TYPE_OFFSET_30(S, _0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17, _18, _19, _20, _21, _22, _23, _24, _25, _26, _27, _28, _29) { .size = sizeof(S), .offsets = { offsetof(S, _0), offsetof(S, _1), offsetof(S, _2), offsetof(S, _3), offsetof(S, _4), offsetof(S, _5), offsetof(S, _6), offsetof(S, _7), offsetof(S, _8), offsetof(S, _9), offsetof(S, _10), offsetof(S, _11), offsetof(S, _12), offsetof(S, _13), offsetof(S, _14), offsetof(S, _15), offsetof(S, _16), offsetof(S, _17), offsetof(S, _18), offsetof(S, _19), offsetof(S, _20), offsetof(S, _21), offsetof(S, _22), offsetof(S, _23), offsetof(S, _24), offsetof(S, _25), offsetof(S, _26), offsetof(S, _27), offsetof(S, _28), offsetof(S, _29) } }
#define TYPE_OFFSET_31(S, _0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17, _18, _19, _20, _21, _22, _23, _24, _25, _26, _27, _28, _29, _30) { .size = sizeof(S), .offsets = { offsetof(S, _0), offsetof(S, _1), offsetof(S, _2), offsetof(S, _3), offsetof(S, _4), offsetof(S, _5), offsetof(S, _6), offsetof(S, _7), offsetof(S, _8), offsetof(S, _9), offsetof(S, _10), offsetof(S, _11), offsetof(S, _12), offsetof(S, _13), offsetof(S, _14), offsetof(S, _15), offsetof(S, _16), offsetof(S, _17), offsetof(S, _18), offsetof(S, _19), offsetof(S, _20), offsetof(S, _21), offsetof(S, _22), offsetof(S, _23), offsetof(S, _24), offsetof(S, _25), offsetof(S, _26), offsetof(S, _27), offsetof(S, _28), offsetof(S, _29), offsetof(S, _30) } }
#define TYPE_OFFSET_32(S, _0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17, _18, _19, _20, _21, _22, _23, _24, _25, _26, _27, _28, _29, _30, _31) { .size = sizeof(S), .offsets = { offsetof(S, _0), offsetof(S, _1), offsetof(S, _2), offsetof(S, _3), offsetof(S, _4), offsetof(S, _5), offsetof(S, _6), offsetof(S, _7), offsetof(S, _8), offsetof(S, _9), offsetof(S, _10), offsetof(S, _11), offsetof(S, _12), offsetof(S, _13), offsetof(S, _14), offsetof(S, _15), offsetof(S, _16), offsetof(S, _17), offsetof(S, _18), offsetof(S, _19), offsetof(S, _20), offsetof(S, _21), offsetof(S, _22), offsetof(S, _23), offsetof(S, _24), offsetof(S, _25), offsetof(S, _26), offsetof(S, _27), offsetof(S, _28), offsetof(S, _29), offsetof(S, _30), offsetof(S, _31) } }
#define TYPE_OFFSET_33(S, _0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17, _18, _19, _20, _21, _22, _23, _24, _25, _26, _27, _28, _29, _30, _31, _32) { .size = sizeof(S), .offsets = { offsetof(S, _0), offsetof(S, _1), offsetof(S, _2), offsetof(S, _3), offsetof(S, _4), offsetof(S, _5), offsetof(S, _6), offsetof(S, _7), offsetof(S, _8), offsetof(S, _9), offsetof(S, _10), offsetof(S, _11), offsetof(S, _12), offsetof(S, _13), offsetof(S, _14), offsetof(S, _15), offsetof(S, _16), offsetof(S, _17), offsetof(S, _18), offsetof(S, _19), offsetof(S, _20), offsetof(S, _21), offsetof(S, _22), offsetof(S, _23), offsetof(S, _24), offsetof(S, _25), offsetof(S, _26), offsetof(S, _27), offsetof(S, _28), offsetof(S, _29), offsetof(S, _30), offsetof(S, _31), offsetof(S, _32) } }
#define TYPE_OFFSET_34(S, _0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17, _18, _19, _20, _21, _22, _23, _24, _25, _26, _27, _28, _29, _30, _31, _32, _33) { .size = sizeof(S), .offsets = { offsetof(S, _0), offsetof(S, _1), offsetof(S, _2), offsetof(S, _3), offsetof(S, _4), offsetof(S, _5), offsetof(S, _6), offsetof(S, _7), offsetof(S, _8), offsetof(S, _9), offsetof(S, _10), offsetof(S, _11), offsetof(S, _12), offsetof(S, _13), offsetof(S, _14), offsetof(S, _15), offsetof(S, _16), offsetof(S, _17), offsetof(S, _18), offsetof(S, _19), offsetof(S, _20), offsetof(S, _21), offsetof(S, _22), offsetof(S, _23), offsetof(S, _24), offsetof(S, _25), offsetof(S, _26), offsetof(S, _27), offsetof(S, _28), offsetof(S, _29), offsetof(S, _30), offsetof(S, _31), offsetof(S, _32), offsetof(S, _33) } }
#define TYPE_OFFSET_35(S, _0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17, _18, _19, _20, _21, _22, _23, _24, _25, _26, _27, _28, _29, _30, _31, _32, _33, _34) { .size = sizeof(S), .offsets = { offsetof(S, _0), offsetof(S, _1), offsetof(S, _2), offsetof(S, _3), offsetof(S, _4), offsetof(S, _5), offsetof(S, _6), offsetof(S, _7), offsetof(S, _8), offsetof(S, _9), offsetof(S, _10), offsetof(S, _11), offsetof(S, _12), offsetof(S, _13), offsetof(S, _14), offsetof(S, _15), offsetof(S, _16), offsetof(S, _17), offsetof(S, _18), offsetof(S, _19), offsetof(S, _20), offsetof(S, _21), offsetof(S, _22), offsetof(S, _23), offsetof(S, _24), offsetof(S, _25), offsetof(S, _26), offsetof(S, _27), offsetof(S, _28), offsetof(S, _29), offsetof(S, _30), offsetof(S, _31), offsetof(S, _32), offsetof(S, _33), offsetof(S, _34) } }
#define TYPE_OFFSET_36(S, _0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17, _18, _19, _20, _21, _22, _23, _24, _25, _26, _27, _28, _29, _30, _31, _32, _33, _34, _35) { .size = sizeof(S), .offsets = { offsetof(S, _0), offsetof(S, _1), offsetof(S, _2), offsetof(S, _3), offsetof(S, _4), offsetof(S, _5), offsetof(S, _6), offsetof(S, _7), offsetof(S, _8), offsetof(S, _9), offsetof(S, _10), offsetof(S, _11), offsetof(S, _12), offsetof(S, _13), offsetof(S, _14), offsetof(S, _15), offsetof(S, _16), offsetof(S, _17), offsetof(S, _18), offsetof(S, _19), offsetof(S, _20), offsetof(S, _21), offsetof(S, _22), offsetof(S, _23), offsetof(S, _24), offsetof(S, _25), offsetof(S, _26), offsetof(S, _27), offsetof(S, _28), offsetof(S, _29), offsetof(S, _30), offsetof(S, _31), offsetof(S, _32), offsetof(S, _33), offsetof(S, _34), offsetof(S, _35) } }
#define TYPE_OFFSET_37(S, _0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17, _18, _19, _20, _21, _22, _23, _24, _25, _26, _27, _28, _29, _30, _31, _32, _33, _34, _35, _36) { .size = sizeof(S), .offsets = { offsetof(S, _0), offsetof(S, _1), offsetof(S, _2), offsetof(S, _3), offsetof(S, _4), offsetof(S, _5), offsetof(S, _6), offsetof(S, _7), offsetof(S, _8), offsetof(S, _9), offsetof(S, _10), offsetof(S, _11), offsetof(S, _12), offsetof(S, _13), offsetof(S, _14), offsetof(S, _15), offsetof(S, _16), offsetof(S, _17), offsetof(S, _18), offsetof(S, _19), offsetof(S, _20), offsetof(S, _21), offsetof(S, _22), offsetof(S, _23), offsetof(S, _24), offsetof(S, _25), offsetof(S, _26), offsetof(S, _27), offsetof(S, _28), offsetof(S, _29), offsetof(S, _30), offsetof(S, _31), offsetof(S, _32), offsetof(S, _33), offsetof(S, _34), offsetof(S, _35), offsetof(S, _36) } }
#define TYPE_OFFSET_38(S, _0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17, _18, _19, _20, _21, _22, _23, _24, _25, _26, _27, _28, _29, _30, _31, _32, _33, _34, _35, _36, _37) { .size = sizeof(S), .offsets = { offsetof(S, _0), offsetof(S, _1), offsetof(S, _2), offsetof(S, _3), offsetof(S, _4), offsetof(S, _5), offsetof(S, _6), offsetof(S, _7), offsetof(S, _8), offsetof(S, _9), offsetof(S, _10), offsetof(S, _11), offsetof(S, _12), offsetof(S, _13), offsetof(S, _14), offsetof(S, _15), offsetof(S, _16), offsetof(S, _17), offsetof(S, _18), offsetof(S, _19), offsetof(S, _20), offsetof(S, _21), offsetof(S, _22), offsetof(S, _23), offsetof(S, _24), offsetof(S, _25), offsetof(S, _26), offsetof(S, _27), offsetof(S, _28), offsetof(S, _29), offsetof(S, _30), offsetof(S, _31), offsetof(S, _32), offsetof(S, _33), offsetof(S, _34), offsetof(S, _35), offsetof(S, _36), offsetof(S, _37) } }
#define TYPE_OFFSET_39(S, _0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17, _18, _19, _20, _21, _22, _23, _24, _25, _26, _27, _28, _29, _30, _31, _32, _33, _34, _35, _36, _37, _38) { .size = sizeof(S), .offsets = { offsetof(S, _0), offsetof(S, _1), offsetof(S, _2), offsetof(S, _3), offsetof(S, _4), offsetof(S, _5), offsetof(S, _6), offsetof(S, _7), offsetof(S, _8), offsetof(S, _9), offsetof(S, _10), offsetof(S, _11), offsetof(S, _12), offsetof(S, _13), offsetof(S, _14), offsetof(S, _15), offsetof(S, _16), offsetof(S, _17), offsetof(S, _18), offsetof(S, _19), offsetof(S, _20), offsetof(S, _21), offsetof(S, _22), offsetof(S, _23), offsetof(S, _24), offsetof(S, _25), offsetof(S, _26), offsetof(S, _27), offsetof(S, _28), offsetof(S, _29), offsetof(S, _30), offsetof(S, _31), offsetof(S, _32), offsetof(S, _33), offsetof(S, _34), offsetof(S, _35), offsetof(S, _36), offsetof(S, _37), offsetof(S, _38) } }
#define TYPE_OFFSET_40(S, _0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17, _18, _19, _20, _21, _22, _23, _24, _25, _26, _27, _28, _29, _30, _31, _32, _33, _34, _35, _36, _37, _38, _39) { .size = sizeof(S), .offsets = { offsetof(S, _0), offsetof(S, _1), offsetof(S, _2), offsetof(S, _3), offsetof(S, _4), offsetof(S, _5), offsetof(S, _6), offsetof(S, _7), offsetof(S, _8), offsetof(S, _9), offsetof(S, _10), offsetof(S, _11), offsetof(S, _12), offsetof(S, _13), offsetof(S, _14), offsetof(S, _15), offsetof(S, _16), offsetof(S, _17), offsetof(S, _18), offsetof(S, _19), offsetof(S, _20), offsetof(S, _21), offsetof(S, _22), offsetof(S, _23), offsetof(S, _24), offsetof(S, _25), offsetof(S, _26), offsetof(S, _27), offsetof(S, _28), offsetof(S, _29), offsetof(S, _30), offsetof(S, _31), offsetof(S, _32), offsetof(S, _33), offsetof(S, _34), offsetof(S, _35), offsetof(S, _36), offsetof(S, _37), offsetof(S, _38), offsetof(S, _39) } }
#define TYPE_OFFSET_41(S, _0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17, _18, _19, _20, _21, _22, _23, _24, _25, _26, _27, _28, _29, _30, _31, _32, _33, _34, _35, _36, _37, _38, _39, _40) { .size = sizeof(S), .offsets = { offsetof(S, _0), offsetof(S, _1), offsetof(S, _2), offsetof(S, _3), offsetof(S, _4), offsetof(S, _5), offsetof(S, _6), offsetof(S, _7), offsetof(S, _8), offsetof(S, _9), offsetof(S, _10), offsetof(S, _11), offsetof(S, _12), offsetof(S, _13), offsetof(S, _14), offsetof(S, _15), offsetof(S, _16), offsetof(S, _17), offsetof(S, _18), offsetof(S, _19), offsetof(S, _20), offsetof(S, _21), offsetof(S, _22), offsetof(S, _23), offsetof(S, _24), offsetof(S, _25), offsetof(S, _26), offsetof(S, _27), offsetof(S, _28), offsetof(S, _29), offsetof(S, _30), offsetof(S, _31), offsetof(S, _32), offsetof(S, _33), offsetof(S, _34), offsetof(S, _35), offsetof(S, _36), offsetof(S, _37), offsetof(S, _38), offsetof(S, _39), offsetof(S, _40) } }
#define TYPE_OFFSET_42(S, _0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17, _18, _19, _20, _21, _22, _23, _24, _25, _26, _27, _28, _29, _30, _31, _32, _33, _34, _35, _36, _37, _38, _39, _40, _41) { .size = sizeof(S), .offsets = { offsetof(S, _0), offsetof(S, _1), offsetof(S, _2), offsetof(S, _3), offsetof(S, _4), offsetof(S, _5), offsetof(S, _6), offsetof(S, _7), offsetof(S, _8), offsetof(S, _9), offsetof(S, _10), offsetof(S, _11), offsetof(S, _12), offsetof(S, _13), offsetof(S, _14), offsetof(S, _15), offsetof(S, _16), offsetof(S, _17), offsetof(S, _18), offsetof(S, _19), offsetof(S, _20), offsetof(S, _21), offsetof(S, _22), offsetof(S, _23), offsetof(S, _24), offsetof(S, _25), offsetof(S, _26), offsetof(S, _27), offsetof(S, _28), offsetof(S, _29), offsetof(S, _30), offsetof(S, _31), offsetof(S, _32), offsetof(S, _33), offsetof(S, _34), offsetof(S, _35), offsetof(S, _36), offsetof(S, _37), offsetof(S, _38), offsetof(S, _39), offsetof(S, _40), offsetof(S, _41) } }
#define TYPE_OFFSET_43(S, _0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17, _18, _19, _20, _21, _22, _23, _24, _25, _26, _27, _28, _29, _30, _31, _32, _33, _34, _35, _36, _37, _38, _39, _40, _41, _42) { .size = sizeof(S), .offsets = { offsetof(S, _0), offsetof(S, _1), offsetof(S, _2), offsetof(S, _3), offsetof(S, _4), offsetof(S, _5), offsetof(S, _6), offsetof(S, _7), offsetof(S, _8), offsetof(S, _9), offsetof(S, _10), offsetof(S, _11), offsetof(S, _12), offsetof(S, _13), offsetof(S, _14), offsetof(S, _15), offsetof(S, _16), offsetof(S, _17), offsetof(S, _18), offsetof(S, _19), offsetof(S, _20), offsetof(S, _21), offsetof(S, _22), offsetof(S, _23), offsetof(S, _24), offsetof(S, _25), offsetof(S, _26), offsetof(S, _27), offsetof(S, _28), offsetof(S, _29), offsetof(S, _30), offsetof(S, _31), offsetof(S, _32), offsetof(S, _33), offsetof(S, _34), offsetof(S, _35), offsetof(S, _36), offsetof(S, _37), offsetof(S, _38), offsetof(S, _39), offsetof(S, _40), offsetof(S, _41), offsetof(S, _42) } }
#define TYPE_OFFSET_44(S, _0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17, _18, _19, _20, _21, _22, _23, _24, _25, _26, _27, _28, _29, _30, _31, _32, _33, _34, _35, _36, _37, _38, _39, _40, _41, _42, _43) { .size = sizeof(S), .offsets = { offsetof(S, _0), offsetof(S, _1), offsetof(S, _2), offsetof(S, _3), offsetof(S, _4), offsetof(S, _5), offsetof(S, _6), offsetof(S, _7), offsetof(S, _8), offsetof(S, _9), offsetof(S, _10), offsetof(S, _11), offsetof(S, _12), offsetof(S, _13), offsetof(S, _14), offsetof(S, _15), offsetof(S, _16), offsetof(S, _17), offsetof(S, _18), offsetof(S, _19), offsetof(S, _20), offsetof(S, _21), offsetof(S, _22), offsetof(S, _23), offsetof(S, _24), offsetof(S, _25), offsetof(S, _26), offsetof(S, _27), offsetof(S, _28), offsetof(S, _29), offsetof(S, _30), offsetof(S, _31), offsetof(S, _32), offsetof(S, _33), offsetof(S, _34), offsetof(S, _35), offsetof(S, _36), offsetof(S, _37), offsetof(S, _38), offsetof(S, _39), offsetof(S, _40), offsetof(S, _41), offsetof(S, _42), offsetof(S, _43) } }
#define TYPE_OFFSET_45(S, _0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17, _18, _19, _20, _21, _22, _23, _24, _25, _26, _27, _28, _29, _30, _31, _32, _33, _34, _35, _36, _37, _38, _39, _40, _41, _42, _43, _44) { .size = sizeof(S), .offsets = { offsetof(S, _0), offsetof(S, _1), offsetof(S, _2), offsetof(S, _3), offsetof(S, _4), offsetof(S, _5), offsetof(S, _6), offsetof(S, _7), offsetof(S, _8), offsetof(S, _9), offsetof(S, _10), offsetof(S, _11), offsetof(S, _12), offsetof(S, _13), offsetof(S, _14), offsetof(S, _15), offsetof(S, _16), offsetof(S, _17), offsetof(S, _18), offsetof(S, _19), offsetof(S, _20), offsetof(S, _21), offsetof(S, _22), offsetof(S, _23), offsetof(S, _24), offsetof(S, _25), offsetof(S, _26), offsetof(S, _27), offsetof(S, _28), offsetof(S, _29), offsetof(S, _30), offsetof(S, _31), offsetof(S, _32), offsetof(S, _33), offsetof(S, _34), offsetof(S, _35), offsetof(S, _36), offsetof(S, _37), offsetof(S, _38), offsetof(S, _39), offsetof(S, _40), offsetof(S, _41), offsetof(S, _42), offsetof(S, _43), offsetof(S, _44) } }
#define TYPE_OFFSET_46(S, _0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17, _18, _19, _20, _21, _22, _23, _24, _25, _26, _27, _28, _29, _30, _31, _32, _33, _34, _35, _36, _37, _38, _39, _40, _41, _42, _43, _44, _45) { .size = sizeof(S), .offsets = { offsetof(S, _0), offsetof(S, _1), offsetof(S, _2), offsetof(S, _3), offsetof(S, _4), offsetof(S, _5), offsetof(S, _6), offsetof(S, _7), offsetof(S, _8), offsetof(S, _9), offsetof(S, _10), offsetof(S, _11), offsetof(S, _12), offsetof(S, _13), offsetof(S, _14), offsetof(S, _15), offsetof(S, _16), offsetof(S, _17), offsetof(S, _18), offsetof(S, _19), offsetof(S, _20), offsetof(S, _21), offsetof(S, _22), offsetof(S, _23), offsetof(S, _24), offsetof(S, _25), offsetof(S, _26), offsetof(S, _27), offsetof(S, _28), offsetof(S, _29), offsetof(S, _30), offsetof(S, _31), offsetof(S, _32), offsetof(S, _33), offsetof(S, _34), offsetof(S, _35), offsetof(S, _36), offsetof(S, _37), offsetof(S, _38), offsetof(S, _39), offsetof(S, _40), offsetof(S, _41), offsetof(S, _42), offsetof(S, _43), offsetof(S, _44), offsetof(S, _45) } }
#define TYPE_OFFSET_47(S, _0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17, _18, _19, _20, _21, _22, _23, _24, _25, _26, _27, _28, _29, _30, _31, _32, _33, _34, _35, _36, _37, _38, _39, _40, _41, _42, _43, _44, _45, _46) { .size = sizeof(S), .offsets = { offsetof(S, _0), offsetof(S, _1), offsetof(S, _2), offsetof(S, _3), offsetof(S, _4), offsetof(S, _5), offsetof(S, _6), offsetof(S, _7), offsetof(S, _8), offsetof(S, _9), offsetof(S, _10), offsetof(S, _11), offsetof(S, _12), offsetof(S, _13), offsetof(S, _14), offsetof(S, _15), offsetof(S, _16), offsetof(S, _17), offsetof(S, _18), offsetof(S, _19), offsetof(S, _20), offsetof(S, _21), offsetof(S, _22), offsetof(S, _23), offsetof(S, _24), offsetof(S, _25), offsetof(S, _26), offsetof(S, _27), offsetof(S, _28), offsetof(S, _29), offsetof(S, _30), offsetof(S, _31), offsetof(S, _32), offsetof(S, _33), offsetof(S, _34), offsetof(S, _35), offsetof(S, _36), offsetof(S, _37), offsetof(S, _38), offsetof(S, _39), offsetof(S, _40), offsetof(S, _41), offsetof(S, _42), offsetof(S, _43), offsetof(S, _44), offsetof(S, _45), offsetof(S, _46) } }
#define TYPE_OFFSET_48(S, _0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17, _18, _19, _20, _21, _22, _23, _24, _25, _26, _27, _28, _29, _30, _31, _32, _33, _34, _35, _36, _37, _38, _39, _40, _41, _42, _43, _44, _45, _46, _47) { .size = sizeof(S), .offsets = { offsetof(S, _0), offsetof(S, _1), offsetof(S, _2), offsetof(S, _3), offsetof(S, _4), offsetof(S, _5), offsetof(S, _6), offsetof(S, _7), offsetof(S, _8), offsetof(S, _9), offsetof(S, _10), offsetof(S, _11), offsetof(S, _12), offsetof(S, _13), offsetof(S, _14), offsetof(S, _15), offsetof(S, _16), offsetof(S, _17), offsetof(S, _18), offsetof(S, _19), offsetof(S, _20), offsetof(S, _21), offsetof(S, _22), offsetof(S, _23), offsetof(S, _24), offsetof(S, _25), offsetof(S, _26), offsetof(S, _27), offsetof(S, _28), offsetof(S, _29), offsetof(S, _30), offsetof(S, _31), offsetof(S, _32), offsetof(S, _33), offsetof(S, _34), offsetof(S, _35), offsetof(S, _36), offsetof(S, _37), offsetof(S, _38), offsetof(S, _39), offsetof(S, _40), offsetof(S, _41), offsetof(S, _42), offsetof(S, _43), offsetof(S, _44), offsetof(S, _45), offsetof(S, _46), offsetof(S, _47) } }
#define TYPE_OFFSET_49(S, _0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17, _18, _19, _20, _21, _22, _23, _24, _25, _26, _27, _28, _29, _30, _31, _32, _33, _34, _35, _36, _37, _38, _39, _40, _41, _42, _43, _44, _45, _46, _47, _48) { .size = sizeof(S), .offsets = { offsetof(S, _0), offsetof(S, _1), offsetof(S, _2), offsetof(S, _3), offsetof(S, _4), offsetof(S, _5), offsetof(S, _6), offsetof(S, _7), offsetof(S, _8), offsetof(S, _9), offsetof(S, _10), offsetof(S, _11), offsetof(S, _12), offsetof(S, _13), offsetof(S, _14), offsetof(S, _15), offsetof(S, _16), offsetof(S, _17), offsetof(S, _18), offsetof(S, _19), offsetof(S, _20), offsetof(S, _21), offsetof(S, _22), offsetof(S, _23), offsetof(S, _24), offsetof(S, _25), offsetof(S, _26), offsetof(S, _27), offsetof(S, _28), offsetof(S, _29), offsetof(S, _30), offsetof(S, _31), offsetof(S, _32), offsetof(S, _33), offsetof(S, _34), offsetof(S, _35), offsetof(S, _36), offsetof(S, _37), offsetof(S, _38), offsetof(S, _39), offsetof(S, _40), offsetof(S, _41), offsetof(S, _42), offsetof(S, _43), offsetof(S, _44), offsetof(S, _45), offsetof(S, _46), offsetof(S, _47), offsetof(S, _48) } }
#define TYPE_OFFSET_50(S, _0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17, _18, _19, _20, _21, _22, _23, _24, _25, _26, _27, _28, _29, _30, _31, _32, _33, _34, _35, _36, _37, _38, _39, _40, _41, _42, _43, _44, _45, _46, _47, _48, _49) { .size = sizeof(S), .offsets = { offsetof(S, _0), offsetof(S, _1), offsetof(S, _2), offsetof(S, _3), offsetof(S, _4), offsetof(S, _5), offsetof(S, _6), offsetof(S, _7), offsetof(S, _8), offsetof(S, _9), offsetof(S, _10), offsetof(S, _11), offsetof(S, _12), offsetof(S, _13), offsetof(S, _14), offsetof(S, _15), offsetof(S, _16), offsetof(S, _17), offsetof(S, _18), offsetof(S, _19), offsetof(S, _20), offsetof(S, _21), offsetof(S, _22), offsetof(S, _23), offsetof(S, _24), offsetof(S, _25), offsetof(S, _26), offsetof(S, _27), offsetof(S, _28), offsetof(S, _29), offsetof(S, _30), offsetof(S, _31), offsetof(S, _32), offsetof(S, _33), offsetof(S, _34), offsetof(S, _35), offsetof(S, _36), offsetof(S, _37), offsetof(S, _38), offsetof(S, _39), offsetof(S, _40), offsetof(S, _41), offsetof(S, _42), offsetof(S, _43), offsetof(S, _44), offsetof(S, _45), offsetof(S, _46), offsetof(S, _47), offsetof(S, _48), offsetof(S, _49) } }
#define TYPE_OFFSET_51(S, _0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17, _18, _19, _20, _21, _22, _23, _24, _25, _26, _27, _28, _29, _30, _31, _32, _33, _34, _35, _36, _37, _38, _39, _40, _41, _42, _43, _44, _45, _46, _47, _48, _49, _50) { .size = sizeof(S), .offsets = { offsetof(S, _0), offsetof(S, _1), offsetof(S, _2), offsetof(S, _3), offsetof(S, _4), offsetof(S, _5), offsetof(S, _6), offsetof(S, _7), offsetof(S, _8), offsetof(S, _9), offsetof(S, _10), offsetof(S, _11), offsetof(S, _12), offsetof(S, _13), offsetof(S, _14), offsetof(S, _15), offsetof(S, _16), offsetof(S, _17), offsetof(S, _18), offsetof(S, _19), offsetof(S, _20), offsetof(S, _21), offsetof(S, _22), offsetof(S, _23), offsetof(S, _24), offsetof(S, _25), offsetof(S, _26), offsetof(S, _27), offsetof(S, _28), offsetof(S, _29), offsetof(S, _30), offsetof(S, _31), offsetof(S, _32), offsetof(S, _33), offsetof(S, _34), offsetof(S, _35), offsetof(S, _36), offsetof(S, _37), offsetof(S, _38), offsetof(S, _39), offsetof(S, _40), offsetof(S, _41), offsetof(S, _42), offsetof(S, _43), offsetof(S, _44), offsetof(S, _45), offsetof(S, _46), offsetof(S, _47), offsetof(S, _48), offsetof(S, _49), offsetof(S, _50) } }
#define TYPE_OFFSET_52(S, _0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17, _18, _19, _20, _21, _22, _23, _24, _25, _26, _27, _28, _29, _30, _31, _32, _33, _34, _35, _36, _37, _38, _39, _40, _41, _42, _43, _44, _45, _46, _47, _48, _49, _50, _51) { .size = sizeof(S), .offsets = { offsetof(S, _0), offsetof(S, _1), offsetof(S, _2), offsetof(S, _3), offsetof(S, _4), offsetof(S, _5), offsetof(S, _6), offsetof(S, _7), offsetof(S, _8), offsetof(S, _9), offsetof(S, _10), offsetof(S, _11), offsetof(S, _12), offsetof(S, _13), offsetof(S, _14), offsetof(S, _15), offsetof(S, _16), offsetof(S, _17), offsetof(S, _18), offsetof(S, _19), offsetof(S, _20), offsetof(S, _21), offsetof(S, _22), offsetof(S, _23), offsetof(S, _24), offsetof(S, _25), offsetof(S, _26), offsetof(S, _27), offsetof(S, _28), offsetof(S, _29), offsetof(S, _30), offsetof(S, _31), offsetof(S, _32), offsetof(S, _33), offsetof(S, _34), offsetof(S, _35), offsetof(S, _36), offsetof(S, _37), offsetof(S, _38), offsetof(S, _39), offsetof(S, _40), offsetof(S, _41), offsetof(S, _42), offsetof(S, _43), offsetof(S, _44), offsetof(S, _45), offsetof(S, _46), offsetof(S, _47), offsetof(S, _48), offsetof(S, _49), offsetof(S, _50), offsetof(S, _51) } }
#define TYPE_OFFSET_53(S, _0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17, _18, _19, _20, _21, _22, _23, _24, _25, _26, _27, _28, _29, _30, _31, _32, _33, _34, _35, _36, _37, _38, _39, _40, _41, _42, _43, _44, _45, _46, _47, _48, _49, _50, _51, _52) { .size = sizeof(S), .offsets = { offsetof(S, _0), offsetof(S, _1), offsetof(S, _2), offsetof(S, _3), offsetof(S, _4), offsetof(S, _5), offsetof(S, _6), offsetof(S, _7), offsetof(S, _8), offsetof(S, _9), offsetof(S, _10), offsetof(S, _11), offsetof(S, _12), offsetof(S, _13), offsetof(S, _14), offsetof(S, _15), offsetof(S, _16), offsetof(S, _17), offsetof(S, _18), offsetof(S, _19), offsetof(S, _20), offsetof(S, _21), offsetof(S, _22), offsetof(S, _23), offsetof(S, _24), offsetof(S, _25), offsetof(S, _26), offsetof(S, _27), offsetof(S, _28), offsetof(S, _29), offsetof(S, _30), offsetof(S, _31), offsetof(S, _32), offsetof(S, _33), offsetof(S, _34), offsetof(S, _35), offsetof(S, _36), offsetof(S, _37), offsetof(S, _38), offsetof(S, _39), offsetof(S, _40), offsetof(S, _41), offsetof(S, _42), offsetof(S, _43), offsetof(S, _44), offsetof(S, _45), offsetof(S, _46), offsetof(S, _47), offsetof(S, _48), offsetof(S, _49), offsetof(S, _50), offsetof(S, _51), offsetof(S, _52) } }
#define TYPE_OFFSET_54(S, _0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17, _18, _19, _20, _21, _22, _23, _24, _25, _26, _27, _28, _29, _30, _31, _32, _33, _34, _35, _36, _37, _38, _39, _40, _41, _42, _43, _44, _45, _46, _47, _48, _49, _50, _51, _52, _53) { .size = sizeof(S), .offsets = { offsetof(S, _0), offsetof(S, _1), offsetof(S, _2), offsetof(S, _3), offsetof(S, _4), offsetof(S, _5), offsetof(S, _6), offsetof(S, _7), offsetof(S, _8), offsetof(S, _9), offsetof(S, _10), offsetof(S, _11), offsetof(S, _12), offsetof(S, _13), offsetof(S, _14), offsetof(S, _15), offsetof(S, _16), offsetof(S, _17), offsetof(S, _18), offsetof(S, _19), offsetof(S, _20), offsetof(S, _21), offsetof(S, _22), offsetof(S, _23), offsetof(S, _24), offsetof(S, _25), offsetof(S, _26), offsetof(S, _27), offsetof(S, _28), offsetof(S, _29), offsetof(S, _30), offsetof(S, _31), offsetof(S, _32), offsetof(S, _33), offsetof(S, _34), offsetof(S, _35), offsetof(S, _36), offsetof(S, _37), offsetof(S, _38), offsetof(S, _39), offsetof(S, _40), offsetof(S, _41), offsetof(S, _42), offsetof(S, _43), offsetof(S, _44), offsetof(S, _45), offsetof(S, _46), offsetof(S, _47), offsetof(S, _48), offsetof(S, _49), offsetof(S, _50), offsetof(S, _51), offsetof(S, _52), offsetof(S, _53) } }
#define TYPE_OFFSET_55(S, _0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17, _18, _19, _20, _21, _22, _23, _24, _25, _26, _27, _28, _29, _30, _31, _32, _33, _34, _35, _36, _37, _38, _39, _40, _41, _42, _43, _44, _45, _46, _47, _48, _49, _50, _51, _52, _53, _54) { .size = sizeof(S), .offsets = { offsetof(S, _0), offsetof(S, _1), offsetof(S, _2), offsetof(S, _3), offsetof(S, _4), offsetof(S, _5), offsetof(S, _6), offsetof(S, _7), offsetof(S, _8), offsetof(S, _9), offsetof(S, _10), offsetof(S, _11), offsetof(S, _12), offsetof(S, _13), offsetof(S, _14), offsetof(S, _15), offsetof(S, _16), offsetof(S, _17), offsetof(S, _18), offsetof(S, _19), offsetof(S, _20), offsetof(S, _21), offsetof(S, _22), offsetof(S, _23), offsetof(S, _24), offsetof(S, _25), offsetof(S, _26), offsetof(S, _27), offsetof(S, _28), offsetof(S, _29), offsetof(S, _30), offsetof(S, _31), offsetof(S, _32), offsetof(S, _33), offsetof(S, _34), offsetof(S, _35), offsetof(S, _36), offsetof(S, _37), offsetof(S, _38), offsetof(S, _39), offsetof(S, _40), offsetof(S, _41), offsetof(S, _42), offsetof(S, _43), offsetof(S, _44), offsetof(S, _45), offsetof(S, _46), offsetof(S, _47), offsetof(S, _48), offsetof(S, _49), offsetof(S, _50), offsetof(S, _51), offsetof(S, _52), offsetof(S, _53), offsetof(S, _54) } }
#define TYPE_OFFSET_56(S, _0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17, _18, _19, _20, _21, _22, _23, _24, _25, _26, _27, _28, _29, _30, _31, _32, _33, _34, _35, _36, _37, _38, _39, _40, _41, _42, _43, _44, _45, _46, _47, _48, _49, _50, _51, _52, _53, _54, _55) { .size = sizeof(S), .offsets = { offsetof(S, _0), offsetof(S, _1), offsetof(S, _2), offsetof(S, _3), offsetof(S, _4), offsetof(S, _5), offsetof(S, _6), offsetof(S, _7), offsetof(S, _8), offsetof(S, _9), offsetof(S, _10), offsetof(S, _11), offsetof(S, _12), offsetof(S, _13), offsetof(S, _14), offsetof(S, _15), offsetof(S, _16), offsetof(S, _17), offsetof(S, _18), offsetof(S, _19), offsetof(S, _20), offsetof(S, _21), offsetof(S, _22), offsetof(S, _23), offsetof(S, _24), offsetof(S, _25), offsetof(S, _26), offsetof(S, _27), offsetof(S, _28), offsetof(S, _29), offsetof(S, _30), offsetof(S, _31), offsetof(S, _32), offsetof(S, _33), offsetof(S, _34), offsetof(S, _35), offsetof(S, _36), offsetof(S, _37), offsetof(S, _38), offsetof(S, _39), offsetof(S, _40), offsetof(S, _41), offsetof(S, _42), offsetof(S, _43), offsetof(S, _44), offsetof(S, _45), offsetof(S, _46), offsetof(S, _47), offsetof(S, _48), offsetof(S, _49), offsetof(S, _50), offsetof(S, _51), offsetof(S, _52), offsetof(S, _53), offsetof(S, _54), offsetof(S, _55) } }
#define TYPE_OFFSET_57(S, _0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17, _18, _19, _20, _21, _22, _23, _24, _25, _26, _27, _28, _29, _30, _31, _32, _33, _34, _35, _36, _37, _38, _39, _40, _41, _42, _43, _44, _45, _46, _47, _48, _49, _50, _51, _52, _53, _54, _55, _56) { .size = sizeof(S), .offsets = { offsetof(S, _0), offsetof(S, _1), offsetof(S, _2), offsetof(S, _3), offsetof(S, _4), offsetof(S, _5), offsetof(S, _6), offsetof(S, _7), offsetof(S, _8), offsetof(S, _9), offsetof(S, _10), offsetof(S, _11), offsetof(S, _12), offsetof(S, _13), offsetof(S, _14), offsetof(S, _15), offsetof(S, _16), offsetof(S, _17), offsetof(S, _18), offsetof(S, _19), offsetof(S, _20), offsetof(S, _21), offsetof(S, _22), offsetof(S, _23), offsetof(S, _24), offsetof(S, _25), offsetof(S, _26), offsetof(S, _27), offsetof(S, _28), offsetof(S, _29), offsetof(S, _30), offsetof(S, _31), offsetof(S, _32), offsetof(S, _33), offsetof(S, _34), offsetof(S, _35), offsetof(S, _36), offsetof(S, _37), offsetof(S, _38), offsetof(S, _39), offsetof(S, _40), offsetof(S, _41), offsetof(S, _42), offsetof(S, _43), offsetof(S, _44), offsetof(S, _45), offsetof(S, _46), offsetof(S, _47), offsetof(S, _48), offsetof(S, _49), offsetof(S, _50), offsetof(S, _51), offsetof(S, _52), offsetof(S, _53), offsetof(S, _54), offsetof(S, _55), offsetof(S, _56) } }
#define TYPE_OFFSET_58(S, _0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17, _18, _19, _20, _21, _22, _23, _24, _25, _26, _27, _28, _29, _30, _31, _32, _33, _34, _35, _36, _37, _38, _39, _40, _41, _42, _43, _44, _45, _46, _47, _48, _49, _50, _51, _52, _53, _54, _55, _56, _57) { .size = sizeof(S), .offsets = { offsetof(S, _0), offsetof(S, _1), offsetof(S, _2), offsetof(S, _3), offsetof(S, _4), offsetof(S, _5), offsetof(S, _6), offsetof(S, _7), offsetof(S, _8), offsetof(S, _9), offsetof(S, _10), offsetof(S, _11), offsetof(S, _12), offsetof(S, _13), offsetof(S, _14), offsetof(S, _15), offsetof(S, _16), offsetof(S, _17), offsetof(S, _18), offsetof(S, _19), offsetof(S, _20), offsetof(S, _21), offsetof(S, _22), offsetof(S, _23), offsetof(S, _24), offsetof(S, _25), offsetof(S, _26), offsetof(S, _27), offsetof(S, _28), offsetof(S, _29), offsetof(S, _30), offsetof(S, _31), offsetof(S, _32), offsetof(S, _33), offsetof(S, _34), offsetof(S, _35), offsetof(S, _36), offsetof(S, _37), offsetof(S, _38), offsetof(S, _39), offsetof(S, _40), offsetof(S, _41), offsetof(S, _42), offsetof(S, _43), offsetof(S, _44), offsetof(S, _45), offsetof(S, _46), offsetof(S, _47), offsetof(S, _48), offsetof(S, _49), offsetof(S, _50), offsetof(S, _51), offsetof(S, _52), offsetof(S, _53), offsetof(S, _54), offsetof(S, _55), offsetof(S, _56), offsetof(S, _57) } }
#define TYPE_OFFSET_59(S, _0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17, _18, _19, _20, _21, _22, _23, _24, _25, _26, _27, _28, _29, _30, _31, _32, _33, _34, _35, _36, _37, _38, _39, _40, _41, _42, _43, _44, _45, _46, _47, _48, _49, _50, _51, _52, _53, _54, _55, _56, _57, _58) { .size = sizeof(S), .offsets = { offsetof(S, _0), offsetof(S, _1), offsetof(S, _2), offsetof(S, _3), offsetof(S, _4), offsetof(S, _5), offsetof(S, _6), offsetof(S, _7), offsetof(S, _8), offsetof(S, _9), offsetof(S, _10), offsetof(S, _11), offsetof(S, _12), offsetof(S, _13), offsetof(S, _14), offsetof(S, _15), offsetof(S, _16), offsetof(S, _17), offsetof(S, _18), offsetof(S, _19), offsetof(S, _20), offsetof(S, _21), offsetof(S, _22), offsetof(S, _23), offsetof(S, _24), offsetof(S, _25), offsetof(S, _26), offsetof(S, _27), offsetof(S, _28), offsetof(S, _29), offsetof(S, _30), offsetof(S, _31), offsetof(S, _32), offsetof(S, _33), offsetof(S, _34), offsetof(S, _35), offsetof(S, _36), offsetof(S, _37), offsetof(S, _38), offsetof(S, _39), offsetof(S, _40), offsetof(S, _41), offsetof(S, _42), offsetof(S, _43), offsetof(S, _44), offsetof(S, _45), offsetof(S, _46), offsetof(S, _47), offsetof(S, _48), offsetof(S, _49), offsetof(S, _50), offsetof(S, _51), offsetof(S, _52), offsetof(S, _53), offsetof(S, _54), offsetof(S, _55), offsetof(S, _56), offsetof(S, _57), offsetof(S, _58) } }
#define TYPE_OFFSET_60(S, _0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17, _18, _19, _20, _21, _22, _23, _24, _25, _26, _27, _28, _29, _30, _31, _32, _33, _34, _35, _36, _37, _38, _39, _40, _41, _42, _43, _44, _45, _46, _47, _48, _49, _50, _51, _52, _53, _54, _55, _56, _57, _58, _59) { .size = sizeof(S), .offsets = { offsetof(S, _0), offsetof(S, _1), offsetof(S, _2), offsetof(S, _3), offsetof(S, _4), offsetof(S, _5), offsetof(S, _6), offsetof(S, _7), offsetof(S, _8), offsetof(S, _9), offsetof(S, _10), offsetof(S, _11), offsetof(S, _12), offsetof(S, _13), offsetof(S, _14), offsetof(S, _15), offsetof(S, _16), offsetof(S, _17), offsetof(S, _18), offsetof(S, _19), offsetof(S, _20), offsetof(S, _21), offsetof(S, _22), offsetof(S, _23), offsetof(S, _24), offsetof(S, _25), offsetof(S, _26), offsetof(S, _27), offsetof(S, _28), offsetof(S, _29), offsetof(S, _30), offsetof(S, _31), offsetof(S, _32), offsetof(S, _33), offsetof(S, _34), offsetof(S, _35), offsetof(S, _36), offsetof(S, _37), offsetof(S, _38), offsetof(S, _39), offsetof(S, _40), offsetof(S, _41), offsetof(S, _42), offsetof(S, _43), offsetof(S, _44), offsetof(S, _45), offsetof(S, _46), offsetof(S, _47), offsetof(S, _48), offsetof(S, _49), offsetof(S, _50), offsetof(S, _51), offsetof(S, _52), offsetof(S, _53), offsetof(S, _54), offsetof(S, _55), offsetof(S, _56), offsetof(S, _57), offsetof(S, _58), offsetof(S, _59) } }
#define TYPE_OFFSET_61(S, _0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17, _18, _19, _20, _21, _22, _23, _24, _25, _26, _27, _28, _29, _30, _31, _32, _33, _34, _35, _36, _37, _38, _39, _40, _41, _42, _43, _44, _45, _46, _47, _48, _49, _50, _51, _52, _53, _54, _55, _56, _57, _58, _59, _60) { .size = sizeof(S), .offsets = { offsetof(S, _0), offsetof(S, _1), offsetof(S, _2), offsetof(S, _3), offsetof(S, _4), offsetof(S, _5), offsetof(S, _6), offsetof(S, _7), offsetof(S, _8), offsetof(S, _9), offsetof(S, _10), offsetof(S, _11), offsetof(S, _12), offsetof(S, _13), offsetof(S, _14), offsetof(S, _15), offsetof(S, _16), offsetof(S, _17), offsetof(S, _18), offsetof(S, _19), offsetof(S, _20), offsetof(S, _21), offsetof(S, _22), offsetof(S, _23), offsetof(S, _24), offsetof(S, _25), offsetof(S, _26), offsetof(S, _27), offsetof(S, _28), offsetof(S, _29), offsetof(S, _30), offsetof(S, _31), offsetof(S, _32), offsetof(S, _33), offsetof(S, _34), offsetof(S, _35), offsetof(S, _36), offsetof(S, _37), offsetof(S, _38), offsetof(S, _39), offsetof(S, _40), offsetof(S, _41), offsetof(S, _42), offsetof(S, _43), offsetof(S, _44), offsetof(S, _45), offsetof(S, _46), offsetof(S, _47), offsetof(S, _48), offsetof(S, _49), offsetof(S, _50), offsetof(S, _51), offsetof(S, _52), offsetof(S, _53), offsetof(S, _54), offsetof(S, _55), offsetof(S, _56), offsetof(S, _57), offsetof(S, _58), offsetof(S, _59), offsetof(S, _60) } }
#define TYPE_OFFSET_62(S, _0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17, _18, _19, _20, _21, _22, _23, _24, _25, _26, _27, _28, _29, _30, _31, _32, _33, _34, _35, _36, _37, _38, _39, _40, _41, _42, _43, _44, _45, _46, _47, _48, _49, _50, _51, _52, _53, _54, _55, _56, _57, _58, _59, _60, _61) { .size = sizeof(S), .offsets = { offsetof(S, _0), offsetof(S, _1), offsetof(S, _2), offsetof(S, _3), offsetof(S, _4), offsetof(S, _5), offsetof(S, _6), offsetof(S, _7), offsetof(S, _8), offsetof(S, _9), offsetof(S, _10), offsetof(S, _11), offsetof(S, _12), offsetof(S, _13), offsetof(S, _14), offsetof(S, _15), offsetof(S, _16), offsetof(S, _17), offsetof(S, _18), offsetof(S, _19), offsetof(S, _20), offsetof(S, _21), offsetof(S, _22), offsetof(S, _23), offsetof(S, _24), offsetof(S, _25), offsetof(S, _26), offsetof(S, _27), offsetof(S, _28), offsetof(S, _29), offsetof(S, _30), offsetof(S, _31), offsetof(S, _32), offsetof(S, _33), offsetof(S, _34), offsetof(S, _35), offsetof(S, _36), offsetof(S, _37), offsetof(S, _38), offsetof(S, _39), offsetof(S, _40), offsetof(S, _41), offsetof(S, _42), offsetof(S, _43), offsetof(S, _44), offsetof(S, _45), offsetof(S, _46), offsetof(S, _47), offsetof(S, _48), offsetof(S, _49), offsetof(S, _50), offsetof(S, _51), offsetof(S, _52), offsetof(S, _53), offsetof(S, _54), offsetof(S, _55), offsetof(S, _56), offsetof(S, _57), offsetof(S, _58), offsetof(S, _59), offsetof(S, _60), offsetof(S, _61) } }
#define TYPE_OFFSET_63(S, _0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17, _18, _19, _20, _21, _22, _23, _24, _25, _26, _27, _28, _29, _30, _31, _32, _33, _34, _35, _36, _37, _38, _39, _40, _41, _42, _43, _44, _45, _46, _47, _48, _49, _50, _51, _52, _53, _54, _55, _56, _57, _58, _59, _60, _61, _62) { .size = sizeof(S), .offsets = { offsetof(S, _0), offsetof(S, _1), offsetof(S, _2), offsetof(S, _3), offsetof(S, _4), offsetof(S, _5), offsetof(S, _6), offsetof(S, _7), offsetof(S, _8), offsetof(S, _9), offsetof(S, _10), offsetof(S, _11), offsetof(S, _12), offsetof(S, _13), offsetof(S, _14), offsetof(S, _15), offsetof(S, _16), offsetof(S, _17), offsetof(S, _18), offsetof(S, _19), offsetof(S, _20), offsetof(S, _21), offsetof(S, _22), offsetof(S, _23), offsetof(S, _24), offsetof(S, _25), offsetof(S, _26), offsetof(S, _27), offsetof(S, _28), offsetof(S, _29), offsetof(S, _30), offsetof(S, _31), offsetof(S, _32), offsetof(S, _33), offsetof(S, _34), offsetof(S, _35), offsetof(S, _36), offsetof(S, _37), offsetof(S, _38), offsetof(S, _39), offsetof(S, _40), offsetof(S, _41), offsetof(S, _42), offsetof(S, _43), offsetof(S, _44), offsetof(S, _45), offsetof(S, _46), offsetof(S, _47), offsetof(S, _48), offsetof(S, _49), offsetof(S, _50), offsetof(S, _51), offsetof(S, _52), offsetof(S, _53), offsetof(S, _54), offsetof(S, _55), offsetof(S, _56), offsetof(S, _57), offsetof(S, _58), offsetof(S, _59), offsetof(S, _60), offsetof(S, _61), offsetof(S, _62) } }
#define TYPE_OFFSET_64(S, _0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17, _18, _19, _20, _21, _22, _23, _24, _25, _26, _27, _28, _29, _30, _31, _32, _33, _34, _35, _36, _37, _38, _39, _40, _41, _42, _43, _44, _45, _46, _47, _48, _49, _50, _51, _52, _53, _54, _55, _56, _57, _58, _59, _60, _61, _62, _63) { .size = sizeof(S), .offsets = { offsetof(S, _0), offsetof(S, _1), offsetof(S, _2), offsetof(S, _3), offsetof(S, _4), offsetof(S, _5), offsetof(S, _6), offsetof(S, _7), offsetof(S, _8), offsetof(S, _9), offsetof(S, _10), offsetof(S, _11), offsetof(S, _12), offsetof(S, _13), offsetof(S, _14), offsetof(S, _15), offsetof(S, _16), offsetof(S, _17), offsetof(S, _18), offsetof(S, _19), offsetof(S, _20), offsetof(S, _21), offsetof(S, _22), offsetof(S, _23), offsetof(S, _24), offsetof(S, _25), offsetof(S, _26), offsetof(S, _27), offsetof(S, _28), offsetof(S, _29), offsetof(S, _30), offsetof(S, _31), offsetof(S, _32), offsetof(S, _33), offsetof(S, _34), offsetof(S, _35), offsetof(S, _36), offsetof(S, _37), offsetof(S, _38), offsetof(S, _39), offsetof(S, _40), offsetof(S, _41), offsetof(S, _42), offsetof(S, _43), offsetof(S, _44), offsetof(S, _45), offsetof(S, _46), offsetof(S, _47), offsetof(S, _48), offsetof(S, _49), offsetof(S, _50), offsetof(S, _51), offsetof(S, _52), offsetof(S, _53), offsetof(S, _54), offsetof(S, _55), offsetof(S, _56), offsetof(S, _57), offsetof(S, _58), offsetof(S, _59), offsetof(S, _60), offsetof(S, _61), offsetof(S, _62), offsetof(S, _63) } }

#define TYPE_OFFSET_LIST() TYPE_OFFSET_64, TYPE_OFFSET_63, TYPE_OFFSET_62, TYPE_OFFSET_61, TYPE_OFFSET_60, TYPE_OFFSET_59, TYPE_OFFSET_58, TYPE_OFFSET_57, TYPE_OFFSET_56, TYPE_OFFSET_55, TYPE_OFFSET_54, TYPE_OFFSET_53, TYPE_OFFSET_52, TYPE_OFFSET_51, TYPE_OFFSET_50, TYPE_OFFSET_49, TYPE_OFFSET_48, TYPE_OFFSET_47, TYPE_OFFSET_46, TYPE_OFFSET_45, TYPE_OFFSET_44, TYPE_OFFSET_43, TYPE_OFFSET_42, TYPE_OFFSET_41, TYPE_OFFSET_40, TYPE_OFFSET_39, TYPE_OFFSET_38, TYPE_OFFSET_37, TYPE_OFFSET_36, TYPE_OFFSET_35, TYPE_OFFSET_34, TYPE_OFFSET_33, TYPE_OFFSET_32, TYPE_OFFSET_31, TYPE_OFFSET_30, TYPE_OFFSET_29, TYPE_OFFSET_28, TYPE_OFFSET_27, TYPE_OFFSET_26, TYPE_OFFSET_25, TYPE_OFFSET_24, TYPE_OFFSET_23, TYPE_OFFSET_22, TYPE_OFFSET_21, TYPE_OFFSET_20, TYPE_OFFSET_19, TYPE_OFFSET_18, TYPE_OFFSET_17, TYPE_OFFSET_16, TYPE_OFFSET_15, TYPE_OFFSET_14, TYPE_OFFSET_13, TYPE_OFFSET_12, TYPE_OFFSET_11, TYPE_OFFSET_10, TYPE_OFFSET_9, TYPE_OFFSET_8, TYPE_OFFSET_7, TYPE_OFFSET_6, TYPE_OFFSET_5, TYPE_OFFSET_4, TYPE_OFFSET_3, TYPE_OFFSET_2, TYPE_OFFSET_1

#ifdef __GNUC__
#define TYPE_OFFSET_N_(...) EXPAND_(TYPE_ARG_N(__VA_ARGS__))
#define TYPE_OFFSET_SELECT(...) TYPE_OFFSET_N_(__VA_ARGS__, TYPE_OFFSET_LIST())
#define TYPE_OFFSET(S, ...) TYPE_OFFSET_SELECT(__VA_ARGS__)(S, __VA_ARGS__)
#else
#define TYPE_OFFSET_N_(...) EXPAND_(TYPE_ARG_N(__VA_ARGS__))
#define TYPE_OFFSET_ARGS(...) EXPAND_(__VA_ARGS__)
#define TYPE_OFFSET_SELECT(...) TYPE_OFFSET_N_(__VA_ARGS__, TYPE_OFFSET_LIST())
#define TYPE_OFFSET_CALL(X, Y) X Y
#define TYPE_OFFSET(S, ...) TYPE_OFFSET_CALL(TYPE_OFFSET_SELECT(__VA_ARGS__),(S, TYPE_OFFSET_ARGS(__VA_ARGS__)))
#endif
typedef struct {
    size_t          size;
#ifdef _MSC_VER
    size_t          offsets[];
#else
    const size_t*   offsets;
#endif
} tTable;

tTable t = TYPE_OFFSET(tTable, size, offsets);


unsigned int MetaData_DecodeSigEntry(SIG *pSig) {
	return MetaData_DecodeSigEntryExt(pSig, 1);
}

unsigned int MetaData_DecodeSigEntryExt(SIG *pSig, int coerceFFToZero) {
	unsigned char a,b,c,d;
	a = *(*pSig)++;
	if ((a & 0x80) == 0) {
		// 1-byte entry
		return a;
	}
	// Special case
	if (a == 0xff) {
		return coerceFFToZero == 1 ? 0 : 0xffffffff;
	}

	b = *(*pSig)++;
	if ((a & 0xc0) == 0x80) {
		// 2-byte entry
		return ((int)(a & 0x3f)) << 8 | b;
	}
	// 4-byte entry
	c = *(*pSig)++;
	d = *(*pSig)++;
	return ((int)(a & 0x1f)) << 24 | ((int)b) << 16 | ((int)c) << 8 | d;
}

IDX_TABLE MetaData_DecodeSigEntryToken(SIG *pSig) {
	static U8 tableID[4] = {MD_TABLE_TYPEDEF, MD_TABLE_TYPEREF, MD_TABLE_TYPESPEC, 0};

	U32 entry = MetaData_DecodeSigEntry(pSig);
	return MAKE_TABLE_INDEX(tableID[entry & 0x3], entry >> 2);
}

tMetaData* MetaData() {
	tMetaData *pRet = TCALLOCFOREVER(1, tMetaData);
	//memset(pRet, 0, sizeof(tMetaData));
	return pRet;
}

void MetaData_LoadStrings(tMetaData *pThis, void *pStream, unsigned int streamLen) {
	pThis->strings.pStart = (unsigned char*)pStream;

	log_f(1, "Loaded strings\n");
}

unsigned int MetaData_DecodeHeapEntryLength(unsigned char **ppHeapEntry) {
	return MetaData_DecodeSigEntry((SIG*)ppHeapEntry);
}

void MetaData_LoadBlobs(tMetaData *pThis, void *pStream, unsigned int streamLen) {
	pThis->blobs.pStart = (unsigned char*)pStream;

	log_f(1, "Loaded blobs\n");

}

void MetaData_LoadUserStrings(tMetaData *pThis, void *pStream, unsigned int streamLen) {
	pThis->userStrings.pStart = (unsigned char*)pStream;

	log_f(1, "Loaded User Strings\n");

}

void MetaData_LoadGUIDs(tMetaData *pThis, void *pStream, unsigned int streamLen) {
	pThis->GUIDs.numGUIDs = streamLen / 16;

	// This is stored -16 because numbering starts from 1. This means that a simple indexing calculation
	// can be used, as if it started from 0
	pThis->GUIDs.pGUID1 = (unsigned char*)pStream;

	log_f(1, "Read %d GUIDs\n", pThis->GUIDs.numGUIDs);
}

/*
Format of definition strings:
Always 2 characters to togther. 1st character defines source, 2nd defines destination.
Sources:
	c: 8-bit value
	s: 16-bit short
	i: 32-bit int
	S: Index into string heap
	G: Index into GUID heap
	B: Index into BLOB heap
	0: Coded index: TypeDefOrRef
	1: Coded index: HasConstant
	2: Coded index: HasCustomAttribute
	3: Coded index: HasFieldMarshall
	4: Coded index: HasDeclSecurity
	5: Coded index: MemberRefParent
	6: Coded index: HasSemantics
	7: Coded index: MethodDefOrRef
	8: Coded index: MemberForwarded
	9: Coded index: Implementation
	:: Coded index: CustomAttributeType
	;: Coded index: ResolutionScope
	<: Coded index: TypeOrMethodDef
	\x00 - \x2c: Simple indexes into the respective table
	^: RVA: Convert to pointer
	x: Nothing, use 0
	m: This metadata pointer
	l: (lower case L) Boolean, is this the last entry in this table?
	I: The original table index for this table item
Destination:
	x: nowhere, ignore
	*: 32-bit index into relevant heap;
		Or coded index - MSB = which table, other 3 bytes = table index
		Or 32-bit int
	p: pointer (also RVA)
	s: 16-bit value
	c: 8-bit value
*/
static const char* tableDefs[] = {
	// 0x00
	"sxSpGpGxGx",
	// 0x01
	"xp;*SpSp",
	// 0x02
	"xpmpi*SpSp0*\x04*\x06*xclcxcxcx*xpxpx*xpxcxcxcxcxpx*x*x*xpI*xpxpxpxpx*xpx*x*xpxpxpxp",
	// 0x03
	NULL,
	// 0x04
	"x*m*ssxsS*B*x*x*x*x*I*x*",
	// 0x05
	NULL,
	// 0x06
	"x*m*^*ssssS*B*\x08*x*x*x*x*x*x*I*x*x*x*"
#ifdef GEN_COMBINED_OPCODES
	"x*x*x*x*x*x*"
#endif
#ifdef DIAG_METHOD_CALLS
	"x*x*x*"
#endif
	,
	// 0x07
	NULL,
	// 0x08
	"ssssS*",
	// 0x09
	"\x02*0*",
	// 0x0A
	"x*5*S*B*",
	// 0x0B
	"ccccxs1*B*",
	// 0x0C
	"2*:*B*",
	// 0x0D
	NULL,
	// 0x0E
	"ssxs4*B*",
	// 0x0F
	"ssxsi*\x02*",
	// 0x10
	"i*\x04*",
	// 0x11
	"B*",
	// 0x12
	"\x02*\x14*",
	// 0x13
	NULL,
	// 0x14
	"ssxsS*0*",
	// 0x15
	"\x02*\x17*",
	// 0x16
	NULL,
	// 0x17
	"ssxsS*B*",
	// 0x18
	"ssxs\06*6*",
	// 0x19
	"\x02*7*7*",
	// 0x1A
	"S*",
	// 0x1B
	"x*m*B*",
	// 0x1C
	"ssxs8*S*\x1a*",
	// 0x1D
	"^*\x04*",
	// 0x1E
	NULL,
	// 0x1F
	NULL,
	// 0x20
	"i*ssssssssi*B*S*S*",
	// 0x21
	NULL,
	// 0x22
	NULL,
	// 0x23
	"ssssssssi*B*S*S*B*",
	// 0x24
	NULL,
	// 0x25
	NULL,
	// 0x26
	NULL,
	// 0x27
	"i*i*S*S*9*",
	// 0x28
	"i*i*S*9*",
	// 0x29
	"\x02*\x02*",
	// 0x2A
	"ssss<*S*",
	// 0x2B
	"x*m*7*B*",
	// 0x2C
	"\x2a*0*",
};

// Coded indexes use this lookup table.
// Note that the extra 'z' characters are important!
// (Because of how the lookup works each string must be a power of 2 in length)
static const char* codedTags[] = {
	// TypeDefOrRef
	"\x02\x01\x1Bz",
	// HasConstant
	"\x04\x08\x17z",
	// HasCustomAttribute
	"\x06\x04\x01\x02\x08\x09\x0A\x00\x0E\x17\x14\x11\x1A\x1B\x20\x23\x26\x27\x28\x2A\x2C\x2Bzzzzzzzzzz",
	// HasFieldMarshall
	"\x04\x08",
	// HasDeclSecurity
	"\x02\x06\x20z",
	// MemberRefParent
	"z\x01\x1A\x06\x1Bzzz",
	// HasSemantics
	"\x14\x17",
	// MethodDefOrRef
	"\x06\x0A",
	// MemberForwarded
	"\x04\x06",
	// Implementation
	"\x26\x23\x27z",
	// CustomAttributeType
	"zz\x06\x0Azzzz",
	// ResolutionScope
	"\x00\x1A\x23\x01",
	// TypeOrMethodDef
	"\x02\x06",
};

static unsigned char codedTagBits[] = {
	2, 2, 5, 1, 2, 3, 1, 1, 1, 2, 3, 2, 1
};

static unsigned int tableRowSize[MAX_TABLES];

void MetaData_Init() {
	U32 i;
	for (i=0; i<MAX_TABLES; i++) {
		tableRowSize[i] = 0;
	}
}

static unsigned int GetU16(unsigned char *pSource) {
	unsigned int a,b;

	a = pSource[0];
	b = pSource[1];
	return a | (b << 8);
}

static unsigned int GetU32(unsigned char *pSource) {
	unsigned int a,b,c,d;

	a = pSource[0];
	b = pSource[1];
	c = pSource[2];
	d = pSource[3];
	return a | (b << 8) | (c << 16) | (d << 24);
}

typedef union {
	U32		u;
	PTR		p;
} TempValue;

// Loads a single table, returns pointer to table in memory.
static void* LoadSingleTable(tMetaData *pThis, tRVA *pRVA, int tableID, void **ppTable) {
	int numRows = pThis->tables.numRows[tableID];
	int rowLen = 0; // Number of bytes taken by each row in memory.
	int i, row;
	char *pDef = tableDefs[tableID];
	int defLen = (int)strlen(pDef);
	void *pRet;
	unsigned char *pSource = *ppTable;
	unsigned char *pDest;
	TempValue v;
	U32		  u;

	// Calculate the destination row size from table definition, if it hasn't already been calculated
	if (tableRowSize[tableID] == 0) {
		for (i=0; i<defLen; i += 2) {
			switch (pDef[i+1]) {
			case '*':
				rowLen += 4;
				break;
			case 'p':
				rowLen += sizeof(PTR);
				break;
			case 's':
				rowLen += 2;
				break;
			case 'c':
				rowLen++;
				break;
			case 'x':
				// Do nothing
				break;
			default:
				Crash("Cannot determine length of MetaData destination definition character '%c'\n", pDef[i+1]);
			}
		}
		tableRowSize[tableID] = rowLen;
	} else {
		rowLen = tableRowSize[tableID];
	}

	// Allocate memory for destination table
	pDest = pRet = mallocForever(numRows * rowLen);

	// Load table
	for (row=0; row<numRows; row++) {
		for (i=0; i<defLen; i += 2) {
			unsigned char d = pDef[i];
			if (d < MAX_TABLES) {
				if (pThis->tables.numRows[d] < 0x10000) {
					// Use 16-bit offset
					v.u = GetU16(pSource);
					pSource += 2;
				} else {
					// Use 32-bit offset
					v.u = GetU32(pSource);
					pSource += 4;
				}
				v.u |= d << 24;
			} else {
				switch (d) {
					case 'c': // 8-bit value
						v.u = *(U8*)pSource;
						pSource++;
						break;
					case 's': // 16-bit short
						v.u = GetU16(pSource);
						pSource += 2;
						break;
					case 'i': // 32-bit int
						v.u = GetU32(pSource);
						pSource += 4;
						break;
					case '0':
					case '1':
					case '2':
					case '3':
					case '4':
					case '5':
					case '6':
					case '7':
					case '8':
					case '9':
					case ':':
					case ';':
					case '<':
						{
							int ofs = pDef[i] - '0';
							char* pCoding = codedTags[ofs];
							int tagBits = codedTagBits[ofs];
							unsigned char tag = *pSource & ((1 << tagBits) - 1);
							int idxIntoTableID = pCoding[tag]; // The actual table index that we're looking for
							if (idxIntoTableID < 0 || idxIntoTableID > MAX_TABLES) {
								printf("Error: tableID=%02x, row=%d, i=%d, d=%c, tag=%d : Bad table index: 0x%02x\n", tableID, row, i, d, tag, idxIntoTableID);
								exit(1);
							}
							if (pThis->tables.codedIndex32Bit[ofs]) {
								// Use 32-bit number
								v.u = GetU32(pSource) >> tagBits;
								pSource += 4;
							} else {
								// Use 16-bit number
								v.u = GetU16(pSource) >> tagBits;
								pSource += 2;
							}
							v.u |= idxIntoTableID << 24;
						}
						break;
					case 'S': // index into string heap
						if (pThis->index32BitString) {
							u = GetU32(pSource);
							pSource += 4;
						} else {
							u = GetU16(pSource);
							pSource += 2;
						}
						v.p = (PTR)(pThis->strings.pStart + u);
						break;
					case 'G': // index into GUID heap
						if (pThis->index32BitGUID) {
							u = GetU32(pSource);
							pSource += 4;
						} else {
							u = GetU16(pSource);
							pSource += 2;
						}
						v.p = (PTR)(pThis->GUIDs.pGUID1 + ((u-1) * 16));
						break;
					case 'B': // index into BLOB heap
						if (pThis->index32BitBlob) {
							u = GetU32(pSource);
							pSource += 4;
						} else {
							u = GetU16(pSource);
							pSource += 2;
						}
						v.p = (PTR)(pThis->blobs.pStart + u);
						break;
					case '^': // RVA to convert to pointer
						u = GetU32(pSource);
						pSource += 4;
						v.p = (PTR)RVA_FindData(pRVA, u);
						break;
					case 'm': // Pointer to this metadata
						v.p = (PTR)pThis;
						break;
					case 'l': // Is this the last table entry?
						u = (row == numRows - 1);
						break;
					case 'I': // Original table index
						u = MAKE_TABLE_INDEX(tableID, row + 1);
						break;
					case 'x': // Nothing, use 0
						u = 0;
						break;
					default:
						Crash("Cannot handle MetaData source definition character '%c' (0x%02X)\n", d, d);
				}
			}
			switch (pDef[i+1]) {
			case '*':
				*(unsigned int*)pDest = u;
				pDest += 4;
				break;
			case 'p':
				((PTR*)pDest)[0] = v.p;
				if(pDef[i] == 'S') {
					size_t l = strlen(((PTR*)pDest)[0]);
				for(size_t ii = 0; ii < l; ++ii) {
					fprintf(stderr, "%c", ((char*)(((PTR*)pDest)[0]))[ii]);
				}
				fprintf(stderr, "\n");
				}
				pDest += sizeof(PTR);
				break;

			case 's':
				*(unsigned short*)pDest = (unsigned short)u;
				pDest += 2;
				break;
			case 'c':
				*(unsigned char*)pDest = (unsigned char)u;
				pDest++;
				break;
			case 'x':
				// Do nothing
				break;
			default:
				Crash("Cannot handle MetaData destination definition character '%c'\n", pDef[i+1]);
			}
		}
	}

	log_f(1, "Loaded MetaData table 0x%02X; %d rows\n", tableID, numRows);

	// Update the parameter to the position after this table
	*ppTable = pSource;
	// Return new table information
	return pRet;
}

void MetaData_LoadTables(tMetaData *pThis, tRVA *pRVA, void *pStream, unsigned int streamLen) {
	U64 valid, j;
	unsigned char c;
	int i, k, numTables;
	void *pTable;

	c = *(unsigned char*)&((char*)pStream)[6];
	pThis->index32BitString = (c & 1) > 0;
	pThis->index32BitGUID = (c & 2) > 0;
	pThis->index32BitBlob = (c & 4) > 0;

	valid = *(U64*)&((char*)pStream)[8];

	// Count how many tables there are, and read in all the number of rows of each table.
	numTables = 0;
	for (i=0, j=1; i<MAX_TABLES; i++, j <<= 1) {
		if (valid & j) {
			pThis->tables.numRows[i] = *(unsigned int*)&((char*)pStream)[24 + numTables * 4];
			numTables++;
		} else {
			pThis->tables.numRows[i] = 0;
			pThis->tables.data[i] = NULL;
		}
	}

	// Determine if each coded index lookup type needs to use 16 or 32 bit indexes
	for (i=0; i<13; i++) {
		char* pCoding = codedTags[i];
		int tagBits = codedTagBits[i];
		// Discover max table size
		unsigned int maxTableLen = 0;
		for (k=0; k < (1<<tagBits); k++) {
			unsigned char t = pCoding[k];
			if (t != 'z') {
				if (pThis->tables.numRows[t] > maxTableLen) {
					maxTableLen = pThis->tables.numRows[t];
				}
			}
		}
		if (maxTableLen < (unsigned)(1 << (16 - tagBits))) {
			// Use 16-bit number
			pThis->tables.codedIndex32Bit[i] = 0;
		} else {
			// Use 32-bit number
			pThis->tables.codedIndex32Bit[i] = 1;
		}
	}

	pTable = &((char*)pStream)[24 + numTables * 4];

	for (i=0; i<MAX_TABLES; i++) {
		if (pThis->tables.numRows[i] > 0) {
			if (i*4 >= sizeof(tableDefs) || tableDefs[i] == NULL) {
				printf("No table definition for MetaData table 0x%02x\n", i);
				exit(1);
			}
			pThis->tables.data[i] = LoadSingleTable(pThis, pRVA, i, &pTable);
		}
	}
}

PTR MetaData_GetBlob(BLOB_ blob, U32 *pBlobLength) {
	unsigned int len = MetaData_DecodeHeapEntryLength(&blob);
	if (pBlobLength != NULL) {
		*pBlobLength = len;
	}
	return blob;
}

// Returns length in bytes, not characters
STRING2 MetaData_GetUserString(tMetaData *pThis, IDX_USERSTRINGS index, unsigned int *pStringLength) {
	unsigned char *pString = pThis->userStrings.pStart + (index & 0x00ffffff);
	unsigned int len = MetaData_DecodeHeapEntryLength(&pString);
	if (pStringLength != NULL) {
		// -1 because of extra terminating character in the heap
		*pStringLength = len - 1;
	}
	return (STRING2)pString;
}

void* MetaData_GetTableRow(tMetaData *pThis, IDX_TABLE index) {
	char *pData;

	if (TABLE_OFS(index) == 0) {
		return NULL;
	}
	pData = (char*)pThis->tables.data[TABLE_ID(index)];
	// Table indexes start at one, hence the -1 here.
	return pData + (TABLE_OFS(index) - 1) * tableRowSize[TABLE_ID(index)];
}

void MetaData_GetConstant(tMetaData *pThis, IDX_TABLE idx, PTR pResultMem) {
	tMD_Constant *pConst;

	switch (TABLE_ID(idx)) {
	case MD_TABLE_FIELDDEF:
		{
			tMD_FieldDef *pField = (tMD_FieldDef*)MetaData_GetTableRow(pThis, idx);
			pConst = (tMD_Constant*)pField->pMemory;
		}
		break;
	default:
		Crash("MetaData_GetConstant() Cannot handle idx: 0x%08x", idx);
	}

	switch (pConst->type) {
	case ELEMENT_TYPE_I4:
		//*(U32*)pReturnMem = MetaData_DecodeSigEntry(
		memcpy(pResultMem, pConst->value+1, 4);
		return;
	default:
		Crash("MetaData_GetConstant() Cannot handle value type: 0x%02x", pConst->type);
	}

}

void MetaData_GetHeapRoots(tHeapRoots *pHeapRoots, tMetaData *pMetaData) {
	U32 i, top;
	// Go through all types, getting their static variables.

	top = pMetaData->tables.numRows[MD_TABLE_TYPEDEF];
	for (i=1; i<=top; i++) {
		tMD_TypeDef *pTypeDef;

		pTypeDef = (tMD_TypeDef*)MetaData_GetTableRow(pMetaData, MAKE_TABLE_INDEX(MD_TABLE_TYPEDEF, i));
		if (pTypeDef->isGenericDefinition) {
			Generic_GetHeapRoots(pHeapRoots, pTypeDef);
		} else {
			if (pTypeDef->staticFieldSize > 0) {
				Heap_SetRoots(pHeapRoots, pTypeDef->pStaticFields, pTypeDef->staticFieldSize);
			}
		}
	}
}
