[settings]
os=Windows
arch=x86_64
build_type=Release

compiler=clang
compiler.version=15
compiler.cppstd=20
compiler.runtime=dynamic
compiler.runtime_type=Release
compiler.runtime_version=v143

[buildenv]
PATH=+(path)C:/Program Files/LLVM/bin
PATH=+(path)C:/Users/tobias/scoop/apps/llvm/current/bin

[conf]
tools.env.virtualenv:auto_use=True
tools.cmake.cmaketoolchain:generator=Ninja
tools.build:cxxflags=['-march=haswell', '-mtune=skylake']
