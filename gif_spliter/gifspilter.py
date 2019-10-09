# 这是一个GIF动态图片分割器
import os # 用于创建文件夹，处理文件路径
import sys # 用于读取命令行参数
from PIL import Image # 用于打开、读取和保存图片

def main(gifpath:str):
    # 判断gif图像存在性
    if not os.path.exists(gifpath):
        print("gif图像不存在")
        return

    # 根据文件名创建输出目录
    # 取得不带目录、不带后缀的文件名，当作输出目录名
    gitfilename = os.path.split(gifpath)[1] # spite 可以将一个路径分为：（目录 , 文件名.后缀）
    filename = os.path.splitext(gitfilename)[0] # splitext 可以将文件名分割成： （文件名 , 目录）
    output_folder = os.path.join(".", f"{filename}_images")
    if not os.path.exists(output_folder):
        os.makedirs(output_folder)

    # 打开gif图像
    gif_obj = Image.open(gifpath)

    # 循环读取每一帧
    frame_num = 0
    while True:
        try:
            # 将图像定位到指定帧
            gif_obj.seek(frame_num) 
        except EOFError:
            # 若到达文件末尾，则跳出
            break
        # 将帧输出到输出目录
        gif_obj.save(os.path.join(output_folder, f"{filename}_{frame_num}.png")) # 将当前帧，输出到指定文件

        # 指向下一帧
        frame_num += 1

    # 提示完成
    print(f"获得 {frame_num} 张图片")

if __name__ == "__main__":
    # 从命令行参数读取gif路径
    if len(sys.argv) == 2:
        gif_path = sys.argv[1]
        main(gif_path)
    else:
        print("需要gif图像路径")
