# x86_64 Conversion Report

Generated: 2026-02-25 02:26 UTC  
Source: current uncommitted workspace changes (`git diff`, `git status`)

## Scope

This report summarizes the changes made to run the DotNetAnywhere fork correctly on 64-bit hosts, with emphasis on pointer-width correctness and managed/native layout consistency.

## Core x86_64 fixes

### 1) JIT code generation: pointer-width aware IL lowering

Files:
- `src/DNA/native/src/JIT.c`

Key fixes:
- Replaced 32-bit assumptions for reference/object operations with pointer-size logic (`sizeof(void*)`).
- `stind.ref` now carries an explicit reference payload size (`PushOpParam(JIT_STOREINDIRECT_REF, ...)`) instead of always using 32-bit stores.
- `ldelem.ref`/`stelem.ref` now emit pointer-sized element ops.
- Object/pointer comparisons and branches now choose 32-bit vs 64-bit compare opcodes based on platform.
- Added mixed-width comparison handling (`PTR` vs `INT32`) by inserting conversion ops where needed (notably important for patterns like native-int compared to zero).

### 2) JIT opcode stream and memory sizing updated for 64-bit op payloads

Files:
- `src/DNA/native/src/JIT.c`
- `src/DNA/native/src/JIT_Execute.c`

Key fixes:
- Runtime op arrays are consumed as `size_t*` (`pOps`, `pOpSequencePoints`, `pCurOp`) to match pointer-sized operands.
- Byte movement/copy for op arrays now uses `sizeof(size_t)` (was effectively 4-byte assumptions in places).
- Final op buffer sizing switched from `ops.ofs * sizeof(U32)` to `ops.ofs * sizeof(size_t)`.

### 3) JIT execution stack/value handling made native-size safe

Files:
- `src/DNA/native/src/JIT_Execute.c`

Key fixes:
- `PUSH_O` / `POP_O` now use `sizeof(HEAP_PTR)` instead of fixed 4 bytes.
- Added `POP_SIZET` and native-size value paths in load/store op handlers.
- `JIT_LOADPARAMLOCAL_*` / `JIT_STOREPARAMLOCAL_*` now read/write native-size values for pointer/intnative cases on x64.
- `JIT_LOADINDIRECT_REF` and dedicated `JIT_STOREINDIRECT_REF` logic now support 64-bit references.
- `JIT_LOADFUNCTION` pushes pointer-sized function tokens.
- Field and static-field load/store paths now use native-size accesses for object/intnative/ptr variants.
- `JIT_LOADSTATICFIELDADDRESS_CHECKTYPEINIT` now pushes a real pointer (`PUSH_PTR`) rather than truncating to `U32`.
- `JIT_BOX_INTNATIVE` boxes native ints as pointer-sized on 64-bit.
- Native-call `this` offset changed from `4` to `sizeof(void*)`.

### 4) Metadata table and RVA handling widened to pointer size

Files:
- `src/DNA/native/src/MetaData.c`
- `src/DNA/native/src/MetaDataTables.h`
- `src/DNA/native/src/MetaData_Fill.c`

Key fixes:
- `FieldRVA` table destination encoding updated from 32-bit to pointer-sized storage (`"^p..."`).
- `tMD_FieldRVA.rva` changed from `U32` to `PTR`.
- Field memory assignment now preserves pointer width (removed narrowing cast).
- Implicit `this` parameter sizing in method metadata fill now uses `sizeof(void*)` (was fixed at 4).

### 5) Managed/native type layout and stack metadata updated

Files:
- `src/DNA/native/src/Type.c`
- `src/DNA/native/src/Thread.h`

Key fixes:
- Introduced `REF_STACK_SIZE` (`sizeof(void*)`) and replaced hardcoded `4` for many reference-like core types.
- Runtime handle types (`RuntimeFieldHandle`, `RuntimeTypeHandle`, `RuntimeMethodHandle`) now use pointer-sized value-type stack/memory sizing.
- `tThread` managed-synced fields are now packed in a dedicated layout union to prevent host-ABI padding from breaking managed field offsets on x64.

### 6) InternalCall ABI fixes for mixed pointer/int parameter layouts

Files:
- `src/DNA/native/src/System.Array.c`
- `src/DNA/native/src/System.String.c`

Key fixes:
- Replaced many direct `((U32*)pParams)[i]`/typed-cast indexing patterns with `INTERNALCALL_PARAM(...)` using `sizeof(void*)`-aware offsets.
- Array reference get/set paths now use `HEAP_PTR` width (no 32-bit truncation).
- String internal calls now decode pointer + integer argument layouts correctly on x64.

### 7) Stack frame hygiene during calls/constructors

Files:
- `src/DNA/native/src/MethodState.c`
- `src/DNA/native/src/JIT_Execute.c`

Key fixes:
- Added locals clearing for fresh method frames (`ClearLocals` path) to avoid stale stack data in params/locals regions.
- Applied locals clearing during direct/delegate/constructor invocation setup.

## Supporting changes (not strictly x86_64 conversion)

These changes appear to support broader runtime/library compatibility while validating the 64-bit port:

- Reflection API surface expansion:
  - `src/DNA/corlib/System/Type.cs`
  - `src/DNA/corlib/System.Reflection/*.cs` additions/updates (`BindingFlags`, `MemberTypes`, `Binder`, overloads).
- Threading/cancellation/context support additions:
  - `src/DNA/corlib/System.Threading/*.cs`
  - `src/DNA/corlib/System/OperationCanceledException.cs`
- Additional BCL compatibility stubs:
  - `src/DNA/corlib/System.Collections.Concurrent/ConcurrentDictionary.cs`
  - `src/DNA/corlib/System.Resources/ResourceManager.cs`
  - `src/DNA/corlib/System.Runtime.ExceptionServices/ExceptionDispatchInfo.cs`
- Build/project alignment changes:
  - `global.json` moved to .NET 8 SDK settings.
  - `dna-redux.sln`, `src/appfs/appfs.fsproj`, `src/libfs/libfs.fsproj`, sample app files updated.

## Untracked files coverage

Included in analysis:
- New/untracked corlib source additions under:
  - `src/DNA/corlib/System.Collections.Concurrent/`
  - `src/DNA/corlib/System.Reflection/` (`BindingFlags.cs`, `MemberTypes.cs`, `Binder.cs`, `ParameterModifier.cs`)
  - `src/DNA/corlib/System.Resources/`
  - `src/DNA/corlib/System.Runtime.ExceptionServices/`
  - `src/DNA/corlib/System.Threading/` (cancellation/threadpool/context delegate additions)

Not treated as x86_64 conversion fixes:
- `src/DNA/native/dna`
- `src/DNA/native/dna-debug`
- `.vscode/tasks.json.old`

Report artifact itself:
- `x86_64-conversion-report.md`

## Net effect

The runtime’s critical 32-bit assumptions around pointer/ref size, eval-stack slot width, metadata field layout, and internal call argument decoding were systematically removed or guarded, enabling correct execution semantics on x86_64.
