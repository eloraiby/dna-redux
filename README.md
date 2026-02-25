# dna-redux

Playground for running C#/F# code in Node.js, Browsers, or Native binaries.

- The CIL is running in a portable .NET runtime called DotNetAnywhere (DNA).
- For Node.js/Browser targets it's compiled to WebAssembly with Emscripten.

Based on the excellent works of:
- @chrisdunelm https://github.com/chrisdunelm/DotNetAnywhere
- @SteveSanderson https://github.com/SteveSanderson/Blazor
- and contributors

Features:
- Supports both C# and F#.
- Runs in Node.js, Browsers, and Native.
- Native runtime has been updated for 64-bit host correctness (x86_64 conversion work).
- Managed projects are built with the .NET SDK pinned in `global.json` (currently `8.0.407` with roll-forward).
- the BCL (corlib) implementation is somewhat minimal.

Changes vs stock DNA/Blazor:
- added F# support.
- Performance updates.
- JIT updates and fixes.
- corlib updates and fixes.
- JavaScript interop updates.
- Razor/SPA removed for clarity.

Disclaimer:
- This is just an experiment to see how far can this be taken without too much effort and what the performance looks like. Obviously it would be nice to have faster GC or highly optimized JIT like RyuJIT to target WebAssembly, but you can still have fun with this now and see what the future of web development may look like.

Building:
- `dotnet build`
- `npm install`
- `npm run build`
- or just use `build.cmd` to build, VS Code to edit/run.

Native runtime build (Linux):
- 64-bit:
  - `gcc -O2 -g -o src/DNA/native/dna src/DNA/native/src/*.c -lm -ldl`
- 32-bit:
  - install multilib toolchain (`gcc-multilib`, `libc6-dev-i386`)
  - `gcc -m32 -O2 -g -o src/DNA/native/dna-32 src/DNA/native/src/*.c -lm -ldl`

Running:
- Running in Node.js: `npm start`
- Running in Browser: `npm run server` to start a web server, then go to localhost:5000 (hint: look in the Console output)
- Running as Native:
  - run from `wwwroot/bin` (where `corlib.dll` and app assemblies are copied)
  - 64-bit:
    - `cd wwwroot/bin && ../../src/DNA/native/dna appcs.dll`
    - `cd wwwroot/bin && ../../src/DNA/native/dna appfs.dll`
  - 32-bit:
    - `cd wwwroot/bin && ../../src/DNA/native/dna-32 appcs.dll`
    - `cd wwwroot/bin && ../../src/DNA/native/dna-32 appfs.dll`

x86_64 conversion notes:
- Detailed change log is tracked in `x86_64-conversion-report.md`.

- You can run it in VS Code, just select a debug config and hit F5.
- The C#, C/C++, Ionide-fsharp, Debugger for Chrome and TSLint extensions for VS Code are highly recommended, but optional.

Further reading:
- [DotNetAnywhere: An Alternative .NET Runtime](http://mattwarren.org/2017/10/19/DotNetAnywhere-an-Alternative-.NET-Runtime/).
