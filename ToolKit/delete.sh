#!/bin/bash

# 递归删除当前目录及其子目录中的所有 .DS_Store 文件
find . -type f -name ".DS_Store" -exec rm -f {} +

echo "所有 .DS_Store 文件已删除。"
