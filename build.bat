::
:: $Notice: Xander Studios @ 2024
:: $Author: Amélie Heinrich
:: $Create Time: 2024-11-21 12:56:59
::
@echo off

where cl
if %ERRORLEVEL% neq 0 (
    call vcvarsall x64
)

if not exist run_tree (
    mkdir run_tree
)

set rootDir=%cd%

set sources=%rootDir%/src/*.cpp

set outputExe=BuckshotAI.exe

set buildFlags=/EHsc /std:c++20

set includeDirs=/I%rootDir%/include

pushd run_tree
cl %sources% %buildFlags% %includeDirs% -Fe%outputExe%
popd
