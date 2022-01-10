# ToCMake
ToCMake - Make a copy of .sln-based project, but with using of CMake, instead of sln in easy way.

# Build and Run
## Build ToCMake with 'build' script
```console
build
```
## Run example of use with 'run' script
```console
run
```
### In this repo you can find 'example' folder with an example of basic Visual Studio projects.

# TODO:
- [x] Flag '-y/--yes', if there is only one .sln file in folder and it's 100% right file.
- [x] Flag '-V/--verbose', toggle verbosity, at this moment it logs all what it can, but it need to be like that only in "verbose" mode.
- [x] Creating directories inside project(test/test.cpp won't be created in current version kinda like BUG, but just 'test.cpp' will be.)
- [ ] In project settings there can be TWO targets like 'application' and 'static library', because by default it changes only for X86/X64 platforms by not for both. So, need to fetch all targets for all platforms and if there're few of them make a choice between them with user input.
- [ ] Support for 'utility' project type
