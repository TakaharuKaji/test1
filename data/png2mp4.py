import cv2
import glob
import shutil
import os

print("測定データフォルダ:")#sokutei_5　とか
data_dir = input()
#print(data_dir)
os.chdir(data_dir)
os.makedirs("fig", exist_ok=True)

size=(640,480)#サイズ指定
fourcc = cv2.VideoWriter_fourcc('m','p','4','v')#保存形式
str = "sokutei_"
save = cv2.VideoWriter(str + '.mp4',fourcc,10.0,size)#動画を保存する形を作成

print("保存中...")

#0フォルダ

pic_data0=glob.glob(str + "*.png")#取り出す
print(pic_data0)
pic_data = []
for i in range(60):
    file = "sokutei_%d.png" % i
    if(os.path.isfile(file)):
        pic_data.append(file)
print(pic_data)

for i in range(len(pic_data)):#n回繰り返す
    img=pic_data[i]
    img=cv2.imread(img)#画像を読み込む
    img=cv2.resize(img,(640,480))#上でサイズを指定していますが、念のため
    save.write(img)#保存
print(len(pic_data))
print("保存しました")

save.release() # ファイルを閉じる

#print(pic_data)
for i in range(len(pic_data)):
    shutil.move(pic_data[i], "fig/%s" % pic_data[i])
