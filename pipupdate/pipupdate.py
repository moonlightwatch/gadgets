#coding=utf-8
'''
自动化pip工具的检查更新和更新操作
'''

import os
import json


print("开始解析已过时的包")
CHECK_RESULT = os.popen("pip list --format=json --outdated").read()

PACKAGE_LIST = []



for item in json.loads(CHECK_RESULT):
    packageName = item["name"]
    print("发现待更新内容: " + packageName)
    PACKAGE_LIST.append(packageName)

print("总共需更新 " + str(len(PACKAGE_LIST)) + "个包")

for package in PACKAGE_LIST:
    print("更新: " + package, end="\t")
    installEcho = os.popen("pip install --upgrade " + package).read()
    if "Successfully installed" in installEcho:
        print("成功")
    else:
        print("失败")

print("完成")
