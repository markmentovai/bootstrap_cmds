# Cross-Platform Mach Interface Generator (`mig`)

This is a version of Apple’s `mig` tool, adapted to run on other platforms. This
may be useful for cross-development, using non-macOS build systems to target
Apple operating systems.

`mig` takes Mach interface descriptions (`.defs` files) as input, and outputs
headers (`.h` files) and implementations (`.c` files) for both clients and
servers of the Mach RPC interface described.

## Prerequisites

### Build-time prerequisites

 * [Autoconf](https://www.gnu.org/software/autoconf/)
 * [Automake](https://www.gnu.org/software/automake/)
 * `make`. [GNU Make](https://www.gnu.org/software/make/) has been tested.
 * A C compiler and associated toolchain. Both [clang](https://clang.llvm.org/)
   and [gcc](https://gcc.gnu.org/) have been tested.
 * A lexer (`lex`). [flex](https://github.com/westes/flex) has been tested.
 * A parser generator (`yacc`). [Bison](https://www.gnu.org/software/bison/)
   has been tested.

### Run-time prerequisites

 * [bash](https://www.gnu.org/software/bash/)
 * A C preprocessor capable of targeting the desired environment. Both `clang`
   and `gcc` have been tested.

## Getting and building the source

```
% git clone --branch=cross_platform \
    https://github.com/markmentovai/bootstrap_cmds
% cd bootstrap_cmds
% autoreconf --install
% sh configure
% make
```

This will produce `migcom.tproj/migcom`, but don’t use that directly. Instead,
invoke `migcom.tproj/mig.sh` as the front end.

It is also possible to `make install`, which installs `mig.sh` as `mig`,
alongside `migcom` and man pages for both.

## Running `mig`

To use `mig`, you should have:
 * A compiler capable of targeting the intended Apple platform, and
 * a corresponding Apple SDK.

The compiler will typically be `clang`, and `mig` will prefer `clang` to `cc` if
installed. The compiler choice can be influenced by setting the `MIGCC`
environment variable. It is possible, although atypical, to use a `gcc`
cross-compiler targeting an Apple platform.

The SDK must be given in an `-isysroot` argument. This will typically be
required, as the compiler will not likely use the correct SDK for a cross build
without being told what to use.

By the same token, it is highly recommended to use `-arch` or `-target`, as the
compiler default will not likely be correct otherwise. (Exception: in the
unusual `gcc` cross compiler case, the compiler front-end is specific to the
cross-build configuration, so `-arch` and `-target` should not be used, and in
fact must not be used as they will be rejected by the compiler.)

```
% mig -arch x86_64 -isysroot ~/MacOSX11.1.sdk \
    ~/MacOSX11.1.sdk/usr/include/mach/mach_exc.defs
```

This will normally produce `mach_exc.h`, `mach_excServer.c`, and
`mach_excUser.c`.

## Changes from upstream

Upstream `mig` is available from [Apple Open
Source](https://opensource.apple.com/) in the `bootstrap_cmds` project, present
in many macOS and Developer Tools releases. [This
repository](https://github.com/markmentovai) contains full unaltered history on
the [main](https://github.com/markmentovai/bootstrap_cmds/tree/main) branch, on
which this
[cross\_platform](https://github.com/markmentovai/bootstrap_cmds/tree/cross_platform)
branch is based.

These major changes are present:

 * A GNU Autotools-based build system (Automake, Autoconf) is added. Upstream
   `mig` is distributed with only an
   [Xcode](https://developer.apple.com/xcode/)-based build system, and Xcode is
   not available outside of macOS.
 * Source code changes for compatibility with non-Apple systems were added.
   Most of these changes are in the `compat` directory and provide definitions
   of Mach types absent on other systems. `mig.sh` was also changed to allow it
   to find a compiler and invoke it properly outside of macOS. As part of a
   cross toolchain, `mig`’s `-arch` argument is important, but `clang` does not
   understand `-arch` outside of macOS, so `mig -arch` is transformed to an
   appropriate `clang -target`.
 * Although the Autotools-based build works on macOS, if you choose to build
   with the original Xcode-based build system, it will actually build without
   errors, even outside of an Apple-internal build. To ensure the version string
   is set correctly, set `RC_ProjectNameAndSourceVersion`, which can be achieved
   by running:

   ```
   % xcodebuild RC_ProjectNameAndSourceVersion=$(
       sed -Ene 's/^AC_INIT\(\[(.*)], \[(.*)](,.*)?\)$/\1-\2/p' < configure.ac)
   ```

## Additional reading

These links are in decreasing order of freshness, but MIG hasn’t changed much.

 * [The Mach Interface Generator
   (MIG)](http://newosxbook.com/MOXiI.pdf#page=387), from Jonathan Levin’s _Mac
   OS X and iOS Internals: To the Apple’s Core_ (page 351, PDF page 387).
 * MIG, section 9.6 in Amit Singh’s _Mac OS X Internals: A Systems Approach_
   (page 1094, PDF page 1128).
 * [MIG - The MACH Interface
   Generator](http://www.cs.cmu.edu/afs/cs/project/mach/public/doc/unpublished/mig.ps),
   a very old paper describing MIG.

## Questions

### Does this make it possible to use Mach on a non-Mach-based operating system?

No, this is just for cross-building. It’s not possible to use `mig`-generated
interfaces without a functioning Mach IPC system. On Apple operating systems,
Mach IPC is implemented in `xnu`, the kernel.

### What does `bootstrap_cmds` mean? Are there any other cmds?

“Bootstrap commands”. I don’t know for sure. Mach has a bootstrap server, a
directory service for other Mach servers on the system, currently implemented in
`launchd` (itself a part of XPC since OS X 10.10). The bootstrap protocol did
use a `mig`-generated interface internally until the XPC rewrite. Still, there
are many other users of `mig` on the system, so this connection is dubious.

As recently as Mac OS X 10.7, a small assortment of other commands appeared
alongside `mig` in this package: `config`, `decomment`, `relpath`, and
`vers_string`. Since then, it’s just been a lonely `mig`. `config` and
`decomment`, at least, have moved directly into the kernel package, `xnu`. `mig`
is also used to build `xnu`. In this context, “bootstrap” probably refers to
bootstrapping the core operating system, including the kernel.

### What’s `migcom` mean?

**MIG** **Com**piler.

### What’s a `.tproj`, anyway?

It’s a **t**ool **proj**ect, dating to NeXTSTEP’s Project Builder. This is an
ancestor of the Command Line Tool target type in Xcode.

### Isn’t it MiG?

The **M**ach **I**nterface **G**enerator is usually abbreviated as MIG. Some
[old NeXTSTEP
documentation](https://www.nextcomputers.org/NeXTfiles/Docs/NeXTStep/3.3/nd/OperatingSystem/Part1_Mach/02_Messages/Messages.htmld/)
and user-facing strings in the source code do refer to
[MiG](https://wikipedia.org/wiki/Mikoyan), which is cute, but is not usual, and
is not the original (CMU Mach) or modern (Apple) spelling.
