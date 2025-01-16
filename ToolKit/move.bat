@echo off

:: 创建目标文件夹（如果不存在）
if not exist "include" mkdir include
if not exist "src" mkdir src
if not exist "ui" mkdir ui

:: 移动 .h 文件到 include 文件夹
for %%f in (*.h) do (
    move "%%f" "include\"
)

:: 移动 .cpp 文件到 src 文件夹
for %%f in (*.cpp) do (
    move "%%f" "src\"
)

:: 移动 .ui 文件到 ui 文件夹
for %%f in (*.ui) do (
    move "%%f" "ui\"
)

echo 文件整理完成！
pause
