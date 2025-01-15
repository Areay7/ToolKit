#!/bin/bash

# 创建目标文件夹，如果它们不存在
mkdir -p include src ui

# 移动.h 文件到 include 文件夹
find . -maxdepth 1 -type f -name "*.h" -exec mv {} include/ \;

# 移动.cpp 文件到 src 文件夹
find . -maxdepth 1 -type f -name "*.cpp" -exec mv {} src/ \;

# 移动.ui 文件到 ui 文件夹
find . -maxdepth 1 -type f -name "*.ui" -exec mv {} ui/ \;
