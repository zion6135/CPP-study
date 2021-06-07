#-*-coding:utf-8-*-
#调整first_point和last_point来调节框的位置
#输入图片car.png  输出图片car_rectangle.png


import os
from PIL import Image
from PIL import ImageDraw

first_point = (20, 20)
last_point = (first_point[0] + 50, first_point[1] + 50)

iamge_path = "car.png"
#打开图片并根据坐标画框，并保存图片+显示
img = Image.open(iamge_path)  # 打开图片
a = ImageDraw.ImageDraw(img)  #用a来表示


# 在边界框的两点（左上角、右下角）画矩形，无填充，边框红色，边框像素为5
a.rectangle((first_point,last_point), fill=None, outline='red', width=3)  
img.save("car_rectangle.png")

