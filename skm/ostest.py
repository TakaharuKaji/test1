import os
import time

###定義
n = 2 #測定回数
m = 500 #一回の移動で動かす距離1mm
init = 28000 #初期位置
HV = 0 #EASIROC(MPPC)にかける電圧
N = 10000 #エントリー数

stage = "/home/sc2021/workdir/controller_20170425/stage.py" #絶対パス
contr = "/home/sc2021/workdir/controller_20170425"
data = "/home/sc2021/workdir/controller_20170425/data"
dir = "/home/sc2021/workdir/controller_20170425/data/dir5" #保存ディレクトリの指定(測定1回ごとにかえる) #これも絶対パスであってる？？？？

###保存フォルダ(ディレクトリ）の作成と初期位置設定
os.system("{} -o".format(stage)) #原点に戻す
# -> /home/sc2021/workdir/controller_20170425/stage.py -o

time.sleep(2)#一時停止
os.system("{0} -ml {1}".format(stage,init)) #初期位置に動かす

def my_makedirs(path):
    if not os.path.isdir(path):
        os.makedirs(path)
    else:
        print("!! dir already exsists !!")#同名のディレクトリを作成しようとしました
os.system("mkdir -p {}".format(dir)) #保存するディレクトリを作る
os.chdir("{}".format(contr)) #contollerに移動


#os.system("ls")
