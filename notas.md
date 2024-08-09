install:
    cmake -> install pre-built binaries for windows (https://cmake.org/download/)
    winlibs gcc/make -> standalone build of gcc and mingw-w64 for windows
    update powershell to 7.1 -> winget install --id Microsoft.Powershell --source winget
setup:
    change PATH to add bin folder of winlibs download

build:
    cmake -> cmake .. -G "MinGW Makefiles"

https://stackoverflow.com/questions/15736398/building-simple-dll-with-mingw
create .dll and .dll.a:
    gcc sorting.c -Wl,--export-all -shared -o libsorting.dll -Wl,--out-implib,libsorting.dll.a
link against .dll and .dll.a:
    gcc sorting_plot.c -L . -lsorting
    cmake:
        https://stackoverflow.com/questions/63912743/compile-app-with-linked-dll-with-cmake-need-to-see-a-working-sample
        switch:
            set_property(TARGET vector PROPERTY IMPORTED_LOCATION "../../sizes/build/libvector.so")
        to:
            set_property(TARGET vector PROPERTY IMPORTED_LOCATION "../../sizes/build/libvector.dll")
            set_property(TARGET vector PROPERTY IMPORTED_IMPLIB "../../sizes/build/libvector.dll.a")
    big note:
        WINDOWS DON'T HAVE RPATH, SO THE EXE CAN'T FIND THE .DLL IF IT'S NOT IN THE PATH
        https://stackoverflow.com/questions/107888/is-there-a-windows-msvc-equivalent-to-the-rpath-linker-flag
        Add to path in your current powershell session:
            $env:Path += ";C:\Users\felip\Downloads\e-learning-main\examples\list_vs_vector\build"
        Reset path:
            $env:Path = [System.Environment]::GetEnvironmentVariable("Path","Machine") + ";" + [System.Environment]::GetEnvironmentVariable("Path","User") 
        target_link_libraries:
            DLLs that depends on other DLLs must have this dependencies explicitly set by `target_link_libraries`
    ansi:
        in admin powershell: `Set-ItemProperty HKCU:\Console VirtualTerminalLevel -Type DWORD 1
        works with $([char])27 in powershell, but not with an actual string
