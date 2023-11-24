@echo off

setlocal enabledelayedexpansion

for %%s in (32 64 128 256 512 1024) do (
    for %%b in (1 2 4 8 16) do (
        cl /DMATW=%%s /DLOCALSIZE=%%b /Fe:proj06 proj06.cpp /link /LIBPATH:"C:\path\to\libOpenCL.lib" /openmp
        proj06.exe
    )
)
 pause