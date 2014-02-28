md  ..\build\data
del /s /q ..\build\data\*.*

for %%i in (core\*.shader) do (
copy %%i ..\build\data\core_%%~ni%%~xi
)

call python make_textures.py
