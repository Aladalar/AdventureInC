@echo off
setlocal enabledelayedexpansion

REM class.bat - Class management tool for AdventureInC project
REM Usage: class.bat <command> [flags] <ClassName> <path>

REM ============================================
REM UTILITY FUNCTIONS (implemented as labels)
REM ============================================

goto :main

:capitalize
    set "str=%~1"
    set "first=!str:~0,1!"
    set "rest=!str:~1!"
    
    REM Convert first char to uppercase
    if /i "!first!"=="a" set "first=A"
    if /i "!first!"=="b" set "first=B"
    if /i "!first!"=="c" set "first=C"
    if /i "!first!"=="d" set "first=D"
    if /i "!first!"=="e" set "first=E"
    if /i "!first!"=="f" set "first=F"
    if /i "!first!"=="g" set "first=G"
    if /i "!first!"=="h" set "first=H"
    if /i "!first!"=="i" set "first=I"
    if /i "!first!"=="j" set "first=J"
    if /i "!first!"=="k" set "first=K"
    if /i "!first!"=="l" set "first=L"
    if /i "!first!"=="m" set "first=M"
    if /i "!first!"=="n" set "first=N"
    if /i "!first!"=="o" set "first=O"
    if /i "!first!"=="p" set "first=P"
    if /i "!first!"=="q" set "first=Q"
    if /i "!first!"=="r" set "first=R"
    if /i "!first!"=="s" set "first=S"
    if /i "!first!"=="t" set "first=T"
    if /i "!first!"=="u" set "first=U"
    if /i "!first!"=="v" set "first=V"
    if /i "!first!"=="w" set "first=W"
    if /i "!first!"=="x" set "first=X"
    if /i "!first!"=="y" set "first=Y"
    if /i "!first!"=="z" set "first=Z"
    
    set "result=!first!!rest!"
    exit /b

:lowercase
    set "str=%~1"
    set "result="
    for /l %%i in (0,1,100) do (
        set "char=!str:~%%i,1!"
        if not "!char!"=="" (
            for %%a in (a b c d e f g h i j k l m n o p q r s t u v w x y z) do (
                if /i "!char!"=="%%a" set "char=%%a"
            )
            set "result=!result!!char!"
        )
    )
    exit /b

:confirm
    echo %~1 [y/N]
    set /p response=
    if /i "!response!"=="y" exit /b 0
    if /i "!response!"=="yes" exit /b 0
    echo Cancelled.
    exit /b 1

:create_header
    set "class_name=%~1"
    set "path=%~2"
    
    REM Strip trailing slashes/backslashes
    if "!path:~-1!"=="\" set "path=!path:~0,-1!"
    if "!path:~-1!"=="/" set "path=!path:~0,-1!"
    
    call :lowercase "!class_name!"
    set "filename=!result!"
    
    call :capitalize "!class_name!"
    set "capitalized=!result!"
    
    REM Create header guard (uppercase)
    set "header_guard="
    for /l %%i in (0,1,100) do (
        set "char=!class_name:~%%i,1!"
        if not "!char!"=="" (
            if /i "!char!"=="a" set "char=A"
            if /i "!char!"=="b" set "char=B"
            if /i "!char!"=="c" set "char=C"
            if /i "!char!"=="d" set "char=D"
            if /i "!char!"=="e" set "char=E"
            if /i "!char!"=="f" set "char=F"
            if /i "!char!"=="g" set "char=G"
            if /i "!char!"=="h" set "char=H"
            if /i "!char!"=="i" set "char=I"
            if /i "!char!"=="j" set "char=J"
            if /i "!char!"=="k" set "char=K"
            if /i "!char!"=="l" set "char=L"
            if /i "!char!"=="m" set "char=M"
            if /i "!char!"=="n" set "char=N"
            if /i "!char!"=="o" set "char=O"
            if /i "!char!"=="p" set "char=P"
            if /i "!char!"=="q" set "char=Q"
            if /i "!char!"=="r" set "char=R"
            if /i "!char!"=="s" set "char=S"
            if /i "!char!"=="t" set "char=T"
            if /i "!char!"=="u" set "char=U"
            if /i "!char!"=="v" set "char=V"
            if /i "!char!"=="w" set "char=W"
            if /i "!char!"=="x" set "char=X"
            if /i "!char!"=="y" set "char=Y"
            if /i "!char!"=="z" set "char=Z"
            set "header_guard=!header_guard!!char!"
        )
    )
    set "header_guard=!header_guard!_H"
    
    set "header_path=include\!path!\!filename!.h"
    
    REM Create directory
    if not exist "include\!path!" mkdir "include\!path!"
    
    REM Generate header content
    (
        echo #ifndef !header_guard!
        echo #define !header_guard!
        echo.
        echo /* TODO: Auto-generated */
        echo.
        echo class !capitalized! {
        echo public:
        echo     !capitalized!^(^);
        echo     ~!capitalized!^(^);
        echo };
        echo.
        echo #endif
    ) > "!header_path!"
    
    echo Created !header_path!
    exit /b

:create_cpp
    set "class_name=%~1"
    set "path=%~2"
    
    REM Strip trailing slashes/backslashes
    if "!path:~-1!"=="\" set "path=!path:~0,-1!"
    if "!path:~-1!"=="/" set "path=!path:~0,-1!"
    
    call :lowercase "!class_name!"
    set "filename=!result!"
    
    call :capitalize "!class_name!"
    set "capitalized=!result!"
    
    set "cpp_path=src\!path!\!filename!.cpp"
    set "include_path=!path:\=/!/!filename!.h"
    
    REM Create directory
    if not exist "src\!path!" mkdir "src\!path!"
    
    REM Generate cpp content
    (
        echo #include "!include_path!"
        echo #include "utilities/logger.h"
        echo.
        echo /* TODO: Auto-generated */
        echo.
        echo !capitalized!::!capitalized!^(^) {
        echo }
        echo.
        echo !capitalized!::~!capitalized!^(^) {
        echo }
    ) > "!cpp_path!"
    
    echo Created !cpp_path!
    set "return_cpp_path=!cpp_path!"
    exit /b

:add_to_cmake
    set "cpp_path=%~1"
    set "cmake_file=CMakeLists.txt"
    
    REM Convert backslashes to forward slashes for CMake
    set "cmake_cpp_path=!cpp_path:\=/!"
    
    REM Check if already in CMakeLists
    find "!cmake_cpp_path!" "!cmake_file!" >nul 2>&1
    if !errorlevel! equ 0 (
        echo Already in CMakeLists.txt
        exit /b
    )
    
    echo Please manually add to CMakeLists.txt: !cmake_cpp_path!
    exit /b

:remove_from_cmake
    set "cpp_path=%~1"
    set "cmake_file=CMakeLists.txt"
    set "cmake_cpp_path=!cpp_path:\=/!"
    
    (for /f "delims=" %%a in (!cmake_file!) do (
        echo %%a | find "!cmake_cpp_path!" >nul
        if errorlevel 1 echo %%a
    )) > "!cmake_file!.tmp"
    
    move /y "!cmake_file!.tmp" "!cmake_file!" >nul
    echo Removed from CMakeLists.txt
    exit /b

REM ============================================
REM COMMAND FUNCTIONS
REM ============================================

:cmd_add
    set "flag=%~1"
    set "class_name=%~2"
    set "path=%~3"
    
    if "!class_name!"=="" (
        echo Error: Missing arguments
        echo Usage: class.bat add [-h^|-cpp] ClassName path\to\location
        exit /b 1
    )
    
    if "!path!"=="" (
        set "path=!class_name!"
        set "class_name=!flag!"
        set "flag="
    )
    
    set "create_h=true"
    set "create_cpp=true"
    
    if "!flag!"=="-h" set "create_cpp=false"
    if "!flag!"=="-cpp" set "create_h=false"
    
    if "!create_h!"=="true" call :create_header "!class_name!" "!path!"
    
    if "!create_cpp!"=="true" (
        call :create_cpp "!class_name!" "!path!"
        call :add_to_cmake "!return_cpp_path!"
    )
    
    echo Done!
    exit /b

:cmd_remove
    set "flag=%~1"
    set "class_name=%~2"
    set "path=%~3"
    
    if "!class_name!"=="" (
        echo Error: Missing arguments
        echo Usage: class.bat remove [-h^|-cpp] ClassName path\to\location
        exit /b 1
    )
    
    if "!path!"=="" (
        set "path=!class_name!"
        set "class_name=!flag!"
        set "flag="
    )
    
    REM Strip trailing slashes
    if "!path:~-1!"=="\" set "path=!path:~0,-1!"
    if "!path:~-1!"=="/" set "path=!path:~0,-1!"
    
    set "remove_h=true"
    set "remove_cpp=true"
    
    if "!flag!"=="-h" set "remove_cpp=false"
    if "!flag!"=="-cpp" set "remove_h=false"
    
    call :lowercase "!class_name!"
    set "filename=!result!"
    set "header_path=include\!path!\!filename!.h"
    set "cpp_path=src\!path!\!filename!.cpp"
    
    echo Will remove:
    if "!remove_h!"=="true" if exist "!header_path!" echo   - !header_path!
    if "!remove_cpp!"=="true" if exist "!cpp_path!" echo   - !cpp_path!
    if "!remove_cpp!"=="true" echo   - Entry in CMakeLists.txt
    
    call :confirm "Are you sure?"
    if !errorlevel! neq 0 exit /b 0
    
    if "!remove_h!"=="true" if exist "!header_path!" (
        del "!header_path!"
        echo Removed !header_path!
    )
    
    if "!remove_cpp!"=="true" (
        if exist "!cpp_path!" (
            del "!cpp_path!"
            echo Removed !cpp_path!
        )
        call :remove_from_cmake "!cpp_path!"
    )
    
    echo Done!
    exit /b

:cmd_move
    set "class_name=%~1"
    set "old_path=%~2"
    set "new_path=%~3"
    
    if "!new_path!"=="" (
        echo Error: Missing arguments
        echo Usage: class.bat move ClassName old\path new\path
        exit /b 1
    )
    
    REM Strip trailing slashes
    if "!old_path:~-1!"=="\" set "old_path=!old_path:~0,-1!"
    if "!old_path:~-1!"=="/" set "old_path=!old_path:~0,-1!"
    if "!new_path:~-1!"=="\" set "new_path=!new_path:~0,-1!"
    if "!new_path:~-1!"=="/" set "new_path=!new_path:~0,-1!"
    
    call :lowercase "!class_name!"
    set "filename=!result!"
    
    set "old_header=include\!old_path!\!filename!.h"
    set "old_cpp=src\!old_path!\!filename!.cpp"
    set "new_header=include\!new_path!\!filename!.h"
    set "new_cpp=src\!new_path!\!filename!.cpp"
    
    if not exist "!old_header!" if not exist "!old_cpp!" (
        echo No files found at !old_path!
        exit /b 1
    )
    
    echo Will move:
    if exist "!old_header!" echo   !old_header! -^> !new_header!
    if exist "!old_cpp!" echo   !old_cpp! -^> !new_cpp!
    
    call :confirm "Continue?"
    if !errorlevel! neq 0 exit /b 0
    
    if not exist "include\!new_path!" mkdir "include\!new_path!"
    if not exist "src\!new_path!" mkdir "src\!new_path!"
    
    if exist "!old_header!" (
        move "!old_header!" "!new_header!" >nul
        echo Moved header
    )
    
    if exist "!old_cpp!" (
        REM Update include path in cpp
        set "old_include=!old_path:\=/!"
        set "new_include=!new_path:\=/!"
        powershell -Command "(gc '!old_cpp!') -replace '!old_include!', '!new_include!' | sc '!old_cpp!'"
        
        move "!old_cpp!" "!new_cpp!" >nul
        echo Moved cpp
        
        call :remove_from_cmake "!old_cpp!"
        call :add_to_cmake "!new_cpp!"
    )
    
    echo Done!
    exit /b

:cmd_rename
    set "old_name=%~1"
    set "new_name=%~2"
    set "path=%~3"
    
    if "!path!"=="" (
        echo Error: Missing arguments
        echo Usage: class.bat rename OldName NewName path\to\location
        exit /b 1
    )
    
    REM Strip trailing slashes
    if "!path:~-1!"=="\" set "path=!path:~0,-1!"
    if "!path:~-1!"=="/" set "path=!path:~0,-1!"
    
    call :lowercase "!old_name!"
    set "old_filename=!result!"
    call :lowercase "!new_name!"
    set "new_filename=!result!"
    
    call :capitalize "!old_name!"
    set "old_cap=!result!"
    call :capitalize "!new_name!"
    set "new_cap=!result!"
    
    set "old_header=include\!path!\!old_filename!.h"
    set "old_cpp=src\!path!\!old_filename!.cpp"
    set "new_header=include\!path!\!new_filename!.h"
    set "new_cpp=src\!path!\!new_filename!.cpp"
    
    if not exist "!old_header!" if not exist "!old_cpp!" (
        echo No files found for !old_name! at !path!
        exit /b 1
    )
    
    echo Will rename:
    echo   !old_name! -^> !new_name!
    if exist "!old_header!" echo   !old_header! -^> !new_header!
    if exist "!old_cpp!" echo   !old_cpp! -^> !new_cpp!
    
    call :confirm "Continue?"
    if !errorlevel! neq 0 exit /b 0
    
    if exist "!old_header!" (
        powershell -Command "(gc '!old_header!') -replace '!old_cap!', '!new_cap!' | sc '!old_header!'"
        move "!old_header!" "!new_header!" >nul
        echo Renamed header
    )
    
    if exist "!old_cpp!" (
        powershell -Command "(gc '!old_cpp!') -replace '!old_filename!', '!new_filename!' -replace '!old_cap!', '!new_cap!' | sc '!old_cpp!'"
        move "!old_cpp!" "!new_cpp!" >nul
        echo Renamed cpp
        
        call :remove_from_cmake "!old_cpp!"
        call :add_to_cmake "!new_cpp!"
    )
    
    echo Done!
    exit /b

:show_usage
    echo Class Management Tool
    echo.
    echo Usage:
    echo   class.bat add [-h^|-cpp] ClassName path\to\location
    echo   class.bat remove [-h^|-cpp] ClassName path\to\location
    echo   class.bat move ClassName old\path new\path
    echo   class.bat rename OldName NewName path\to\location
    echo.
    echo Commands:
    echo   add       Create new class files
    echo   remove    Delete class files (asks for confirmation^)
    echo   move      Move class to new location
    echo   rename    Rename class files and update references
    echo.
    echo Flags (for add/remove^):
    echo   -h        Header only (.h^)
    echo   -cpp      Implementation only (.cpp^)
    echo   (none^)    Both files
    echo.
    echo Examples:
    echo   class.bat add Input managers
    echo   class.bat add -h Region world
    echo   class.bat remove TestScene world\testRegion\scenes
    echo   class.bat move Input managers\old managers\new
    echo   class.bat rename OldInput Input managers
    echo.
    exit /b

REM ============================================
REM MAIN
REM ============================================

:main
set "command=%~1"

if "!command!"==" goto :show_usage
if "!command!"=="-h" goto :show_usage
if "!command!"=="--help" goto :show_usage
if "!command!"=="help" goto :show_usage

if "!command!"=="add" (
    shift
    call :cmd_add %*
    exit /b
)

if "!command!"=="remove" (
    shift
    call :cmd_remove %*
    exit /b
)

if "!command!"=="move" (
    shift
    call :cmd_move %*
    exit /b
)

if "!command!"=="rename" (
    shift
    call :cmd_rename %*
    exit /b
)

echo Unknown command: !command!
call :show_usage
exit /b 1