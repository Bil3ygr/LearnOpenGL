@echo off

set BUILD_DIR=build
set RES_DIR=res
set GENERATOR="Visual Studio 16 2019"

pushd %~dp0

@REM if exist %BUILD_DIR% (
@REM 	call:LogWithTime "Build folder exists, remove first..."
@REM 	rmdir /S /Q %BUILD_DIR%
@REM 	if %ERRORLEVEL% equ 0 ( mkdir %BUILD_DIR% )
@REM ) else (
@REM 	mkdir %BUILD_DIR%
@REM )

if not exist %BUILD_DIR% (
	mkdir %BUILD_DIR%
)

if not exist %RES_DIR% (
	mkdir %RES_DIR%
)

pushd %BUILD_DIR%

call:LogWithTime "Start generate solution"
cmake -G %GENERATOR% ..

popd
popd

@REM pause

@REM start build\LearningOpenGL.sln

exit /b 0

:LogWithTime
echo [%TIME%] %1
goto:eof
