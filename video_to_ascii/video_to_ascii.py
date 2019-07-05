import os
import sys
import numpy

import cv2  # opencv 计算机视觉，我们用于读取视频。python3 -m pip install opencv-python

gray_num = list(
    "$@B%8&WM#*oahkbdpqwmZO0QLCJUYXzcvunxrjft/\|()1{}[]?-_+~<>i!lI;:,\"^`'. ")


def main(videoPath: str):
    # 读取视频
    # 获取视频帧 -> 一张图片
    # 循环处理视频帧 -> 图片to字符画
    # 输出
    cap = cv2.VideoCapture(videoPath)  # 读取视频

    while True:
        success, frame = cap.read()  # 读取视频帧
        if not success:
            break
        # 转换灰度图
        grayFrame = cv2.cvtColor(frame, cv2.COLOR_RGB2GRAY)
        # 调整尺寸
        tsize = os.get_terminal_size()
        fixFrame = cv2.resize(grayFrame, (tsize.columns, int(tsize.lines/2)))
        img_array = numpy.array(fixFrame, "f")
        asciiFrame = ""
        for line in img_array:
            for p in line:
                # p 浮点数数字
                n = (p/255)*(len(gray_num)-1)  # 灰度像素在字符列表中的位置
                index = int(n)  # 转换为整数
                asciiFrame += gray_num[index]  # 从字符列表取得字符加入字符画帧
            asciiFrame += "\n"  # 字符画帧换行
        print(asciiFrame)  # 输出

    cap.release()


if __name__ == "__main__":
    if len(sys.argv) > 1 and os.path.exists(sys.argv[1]):
        main(sys.argv[1])
    else:
        print("File not found.")
