@REM Build for Visual Studio compiler. Run your copy of vcvars32.bat or vcvarsall.bat to Setup command-line compiler.
@set OUT_DIR=Debug
@set OUT_EXE=example_sdl2_opengl2
@set INCLUDES=/I..\.. /I..\..\backends /I%SDL2_DIR%\include
@set SOURCES=main.cpp ..\..\backends\imgui_impl_sdl2.cpp ..\..\backends\imgui_impl_opengl2.cpp ..\..\imgui*.cpp
@set LIBS=/LIBPATH:%SDL2_DIR%\lib\x86 SDL2.lib SDL2main.lib opengl32.lib shell32.lib
mkdir %OUT_DIR%
cl /nologo /Zi /MD /utf-8 %INCLUDES% %SOURCES% /Fe%OUT_DIR%/%OUT_EXE%.exe /Fo%OUT_DIR%/ /link %LIBS% /subsystem:console
