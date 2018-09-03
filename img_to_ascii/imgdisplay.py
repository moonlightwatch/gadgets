#!/usr/bin/python3
# coding=utf-8

from PIL import Image
import numpy
import sys
import os

gray_num = list(
    "$@B%8&WM#*oahkbdpqwmZO0QLCJUYXzcvunxrjft/\|()1{}[]?-_+~<>i!lI;:,\"^`'. ")


def main(filepath: str, width: int=80, height: int=40):
    img = Image.open(filepath)  # 读取图片
    img = img.resize((width, height), Image.ANTIALIAS)
    img_gray = img.convert("L")  # 转换为灰度图
    img_array = numpy.array(img_gray, "f")  # 灰度矩阵

    numlen = len(gray_num)
    for line in img_array:
        char_line = []
        for pf in line:
            n = ((pf/255) * (numlen-1))
            index = int(n)
            char_line.append(gray_num[index])
        print("".join(char_line))


if __name__ == "__main__":
    if len(sys.argv) > 1 and os.path.exists(sys.argv[1]):
        path = sys.argv[1]
        width = 80
        if len(sys.argv) >= 3:
            width = int(sys.argv[2])
        height = 40
        if len(sys.argv) >= 4:
            height = int(sys.argv[3])
        main(filepath=path, width=width, height=height)
    else:
        print("ERROR: 缺少参数\n")
        print(f"完整命令： {sys.argv[0]} filepath [width] [height]")
        print("filepath: 图片文件路径，支持多数图片格式")
        print("width: 输出宽度 （可选，默认80）")
        print("height: 输出高度 （可选，默认40）")
        print()
