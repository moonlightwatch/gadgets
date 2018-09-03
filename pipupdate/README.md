
# pip 自动化更新工具

## 功能

使用 pip 工具，自动化更新已过时的 python 包

## 原理

1. 通过 os 包中的 popen 方法执行 `pip list --format=json --outdated` 命令，并获取回显。
2. 从回显中解析已过时的包名
3. 逐个通过 pip 工具执行更新操作

更新：
    将format由legacy更改为json