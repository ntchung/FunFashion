md  ..\build\data
del /s /q ..\build\data\*.*

for %%i in (core\*.shader) do (
copy %%i ..\build\data\core_%%~ni%%~xi
)

copy shaders\*.shader ..\build\data

call python make_textures.py
