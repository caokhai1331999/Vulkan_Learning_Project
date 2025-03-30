@echo off
setlocal

set hr=%time:~0,2%
set hr=%hr: =0%

set min=%time:~3,2%
set min=%min: =0%

set sec=%time:~6,2%
set sec=%sec: =0%

set dd=%date:~-7,2%
set dd=%dd: =0%

set mm=%date:~-10,2%
set mm=%mm: =0%

set yy=%date:~-4,4%
set yy=%yy: =0%

REM Define paths to SDL include, library, and DLL directories

set GLFW_INCLUDE_DIR="C:\Users\klove\Downloads\External_Libraries\glfw\glfw-3.4.bin.WIN64\include"
set GLFW_LIB_DIR="C:\Users\klove\Downloads\External_Libraries\glfw\glfw-3.4.bin.WIN64\lib-vc2022"
set GLFW_DLL_DIR="C:\Users\klove\Downloads\External_Libraries\glfw\glfw-3.4.bin.WIN64\lib-vc2022"

rem set
rem VULKAN_INCLUDE_DIR="C:\VulkanSDK\1.4.304.1\Include"
rem set
rem VULKAN_LIB_DIR="C:\VulkanSDK\1.4.304.1\Lib"
rem set
rem VULKAN_INCLUDE_DLL="C:\VulkanSDK\1.4.304.1\Bin"

set COMMON_INHERENT_LIB=glfw3.lib opengl32.lib gdi32.lib user32.lib shell32.lib ucrt.lib vcruntime.lib msvcrt.lib kernel32.lib

set COMMON_COMPILER_OPTION=/FC /MD /Zi /FD /EHsc 

set _EXPORT=/EXPORT:Init /EXPORT:framebuffer_size_callback /EXPORT:mouse_callback /EXPORT:scroll_callback /EXPORT:processInput /EXPORT:LoadTexture

REM Define source files and output executable
set SRC_FILES=main.cpp
set OUT_EXE=OpenGL_project.exe

if not exist build (
    mkdir build
)

echo folder before pushd : %CD%
pushd build
echo folder after pushd : %CD%
del *.obj *.pdb %OUT_EXE% 

REM List all .cpp files in the current directory
setlocal enabledelayedexpansion

REM Compile the project
for %%f in (..\*.cpp) do (
   set FILES=!FILES! %%f
 )

REM Add DLL directory to PATH for runtime
set PATH=%DLL_DIR%;%PATH%
    
REM /subsystem:consoles
REM The reason why the compile the subsystem:consoles may solved the undebug problem.  /FORCE:MULTIPLE /IGNORE:4006 /NODEFAULTLIB:LIBCMT /FORCE:MULTIPLE /fsanitize=address
cl /LD ..\KPlatformG.cpp %COMMON_COMPILER_OPTION% /I %GLFW_INCLUDE_DIR% /link /LIBPATH:%GLFW_LIB_DIR% %COMMON_INHERENT_LIB% /PDB:platform_%dd%%mm%%yy%_%hr%%min%.pdb %_EXPORT% /OUT:Platform.dll

cl ..\main.cpp  %COMMON_COMPILER_OPTION% /I %GLFW_INCLUDE_DIR% /link /subsystem:console /LIBPATH:%GLFW_LIB_DIR% %COMMON_INHERENT_LIB%  /subsystem:console /OUT:%OUT_EXE%

if %ERRORLEVEL% EQU 0 (
   @echo Announce: " compilation succeeded (^ w ^) "
) else (
   @echo                                  @   @          
   @echo Announce: " compilation failed \_(-_-)_/ "
)

echo folder before popd: %CD%
popd
echo folder after popd: %CD%

endlocal
