import cv2
import glob
import shutil
import os
<<<<<<< HEAD:data/sokutei_2/png2mp4.py
=======

print("測定データフォルダ:")#sokutei_5　とか
data_dir = input()
#print(data_dir)
os.chdir(data_dir)
os.makedirs("fig", exist_ok=True)
>>>>>>> 5c016e6701666063fcd05a01e0ae1908c48090be:data/png2mp4.py

size=(640,480)#サイズ指定
fourcc = cv2.VideoWriter_fourcc('m','p','4','v')#保存形式
str = "sokutei_"
save = cv2.VideoWriter(str + '.mp4',fourcc,5.0,size)#動画を保存する形を作成

print("保存中...")

#0フォルダ

pic_data=glob.glob(str + "*.png")#取り出す
print(pic_data)
for i in range(len(pic_data)):#n回繰り返す
    img=pic_data[i]
    img=cv2.imread(img)#画像を読み込む
    img=cv2.resize(img,(640,480))#上でサイズを指定していますが、念のため
    save.write(img)#保存
print(len(pic_data))
print("保存しました")

save.release() # ファイルを閉じる

<<<<<<< HEAD:data/sokutei_2/png2mp4.py
print("測定データフォルダ:")
new_dir = input()
print(new_dir)
os.makedirs("%s" % new_dir, exist_ok=True)
=======
list1 = os.listdir()
list_png = [s for s in list1 if ((".PNG") in s) or ((".png") in s)]
#print(list_png)
for i in range(len(list_png)):
    #shutil.move(list_png[i], "fig/%s" % list_png[i])
>>>>>>> 5c016e6701666063fcd05a01e0ae1908c48090be:data/png2mp4.py
