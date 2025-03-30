@echo off
setlocal

REM Define paths to SDL include, library, and DLL directories
set GLFW_INCLUDE_DIR="C:\Users\Cao Khai\Downloads\External_Libraries\glfw\glfw-3.4.bin.WIN64\include"
set GLFW_LIB_DIR="C:\Users\Cao Khai\Downloads\External_Libraries\glfw\glfw-3.4.bin.WIN64\lib-vc2022"
set GLFW_DLL_DIR="C:\Users\Cao Khai\Downloads\External_Libraries\glfw\glfw-3.4.bin.WIN64\lib-vc2022"
set VULKAN_INCLUDE_DIR="C:\VulkanSDK\1.4.304.1\Include"
set VULKAN_LIB_DIR="C:\VulkanSDK\1.4.304.1\Lib"
set VULKAN_INCLUDE_DLL="C:\VulkanSDK\1.4.304.1\Bin"

REM Define source files and output executable
set SRC_FILES=main.cpp
set OUT_EXE=OpenGL_project.exe

if not exist build (
    mkdir build
)

echo folder before pushd : %CD%
pushd build
echo folder after pushd : %CD%
del *.obj *.pdb *.sln %OUT_EXE% 

REM List all .cpp files in the current directory
setlocal enabledelayedexpansion

REM Compile the project
for %%f in (..\*.cpp) do (
   set FILES=!FILES! %%f
 )

REM Add DLL directory to PATH for runtime
set PATH=%DLL_DIR%%VULKAN_INCLUDE_DLL%;%PATH%

REM /subsystem:consoles
REM The reason why the compile the subsystem:consoles may solved the undebug problem.  /FORCE:MULTIPLE /IGNORE:4006
cl %FILES% /FC /Zi /EHsc /I %GLFW_INCLUDE_DIR% /I %VULKAN_INCLUDE_DIR% /link /subsystem:console  /LIBPATH:%GLFW_LIB_DIR% /LIBPATH:%VULKAN_LIB_DIR% glfw3.lib vulkan-1.lib opengl32.lib gdi32.lib user32.lib shell32.lib ucrt.lib vcruntime.lib msvcrt.lib kernel32.lib /NODEFAULTLIB:LIBCMT /FORCE:MULTIPLE /DEBUG /OUT:%OUT_EXE%

if %ERRORLEVEL% EQU 0 (
   @echo Announce: " compilation succeeded (^ w ^) "
) else (
   @echo                                  @   @          
   @echo Announce: " compilation failed \_(-_-)_/ "
)

echo folder before popd: %CD%
popd
echo folder after popd: %CD%

pause
endlocal
