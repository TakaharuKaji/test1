import cv2
import glob

size=(640,480)#サイズ指定
fourcc = cv2.VideoWriter_fourcc('m','p','4','v')#保存形式
str = "sokuteitest"
save = cv2.VideoWriter(str + '.mp4',fourcc,1.0,size)#動画を保存する形を作成

print("保存中...")

#0フォルダ
pic_data=glob.glob(str + "*.png")#取り出す
for i in range(len(pic_data)):#n回繰り返す
    img=pic_data[i]
    img=cv2.imread(img)#画像を読み込む
    img=cv2.resize(img,(640,480))#上でサイズを指定していますが、念のため
    save.write(img)#保存

print("保存しました")

save.release() # ファイルを閉じる
