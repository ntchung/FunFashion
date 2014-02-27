SETLOCAL EnableDelayedExpansion

call config.bat

cd textures

rem TEXTURES TGA
for %%i in (8888\*.tga) do (
%PVRCOMPRESS8888% -i %%i
del /s /q %BUILD%\%%~ni.*
)
for %%i in (888\*.tga) do (
%PVRCOMPRESS888% -i %%i
del /s /q %BUILD%\%%~ni.*
)
for %%i in (ETC\*.tga) do (
%PVRCOMPRESSETC% -i %%i
del /s /q %BUILD%\%%~ni.*
)
for %%i in (ETCnomipmap\*.tga) do (
%PVRCOMPRESSETCnm% -i %%i
del /s /q %BUILD%\%%~ni.*
)

rem TEXTURES PNG
for %%i in (8888\*.png) do (
%PVRCOMPRESS8888% -i %%i
del /s /q %BUILD%\%%~ni.*
)
for %%i in (888\*.png) do (
%PVRCOMPRESS888% -i %%i
del /s /q %BUILD%\%%~ni.*
)
for %%i in (ETC\*.png) do (
%PVRCOMPRESSETC% -i %%i
del /s /q %BUILD%\%%~ni.*
)
for %%i in (ETCnomipmap\*.png) do (
%PVRCOMPRESSETCnm% -i %%i
del /s /q %BUILD%\%%~ni.*
)

rem FINALIZING
move 888\*.pvr %BUILD%
move 8888\*.pvr %BUILD%
move ETC\*.pvr %BUILD%
move ETCnomipmap\*.pvr %BUILD%

cd ..
