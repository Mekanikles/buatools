# The Best UI API Toolset

## Components
- `buacore`: internal core library for all toolset binaries.
- `bualib`: primary retained ui library.
- `buaelements`: standard set of ui components, using `bualib`.
- `imbua`: immediate mode library, using `buaelements`.
- `examples`: example usage of `imbua`, `buaelements`, and `bualib`.
- `buasetup`: python script for setting up environment and dependencies.
- `buacli`: command line interface for generating build files and building binaries.

## How to set up a developer workspace

### Prerequisites
- Conan
- Cmake
- Python 3 (optional)

### Instructions
- Run `buasetup`
- Run `buacli gen Debug` to generate build files for the Debug configuration
- Run `buacli build` to build all binaries
- Run built exectutables from `build/bin`
