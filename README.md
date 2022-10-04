## Build instructions

```shell script
git clone https://github.com/kleroop/TechCourse_2022_12.git
cd TechCourse_2022_12
git clone https://github.com/Microsoft/vcpkg
vcpkg/bootstrap-vcpkg.sh  #.bat on windows
```

# There are three ways of installing Qt5:

## 1. Debian-based distro (e.g. Ubuntu) way:

```shell script
sudo apt install qtbase5-dev
```

## 2. Qt5 installer:

Download [qt installer](https://www.qt.io/offline-installers) and check option to install libraries for
whatever compiler/toolchain you're using

## 3. vcpkg source-based install (very slow)

```shell script
vcpkg/vcpkg install qt5
```

# Build instructions and cmake options:

`-DCMAKE_TOOLCHAIN_FILE="vcpkg/scripts/buildsystems/vcpkg.cmake"` \
And in case of Qt5 installer add: \
`-DCMAKE_PREFIX_PATH=<QtInstallDir>/5.x.x/<your_compiler>/lib/cmake` \
in the "CMake options" field.

### In CLion you can set options here:

File/Settings/Build, Execution, Deployment/CMake -> CMake options

### cli:

```shell script
cmake -S . -B <cmake options>
cmake --build build
```

## Code Style
All project PRs must follow [Qt coding style](https://wiki.qt.io/Qt_Coding_Style) 
and format each edited file with clang-format before committing.
## Contribution
In order to sync fork with main repo for PR, read [how to sync a forked repo](https://docs.github.com/en/pull-requests/collaborating-with-pull-requests/working-with-forks/syncing-a-fork).
