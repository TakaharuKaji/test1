#!/usr/bin/env python3

import os
import time
import sys

n = 60 #測定回数
m = 200 #一回の移動で動かす距離1mm
init = 34000 #初期位置
HV = 53.5
N = 100000
stage = "/home/sc2021/workdir/controller_20170425/stage.py"
contr = "/home/sc2021/workdir/controller_20170425"
data = "/home/sc2021/workdir/controller_20170425/data"
dir = "/home/sc2021/workdir/controller_20170425/data/sokutei_20" #保存ディレクトリの指定(測定1回ごとにかえる)
test1 = "/home/sc2021/workdir/test1"

def check_makedirs(path):
    if not os.path.isdir(path):
        os.system("mkdir -p {}".format(path))
    else:
        print("!! dir already exists !!") #同名のディレクトリを作成しようとしました
        sys.exit()

check_makedirs(dir) #保存するディレクトリを作る

#os.system("mkdir -p {}".format(dir))

###保存フォルダ(ディレクトリ）の作成と初期位置設定
os.system("{} -o".format(stage)) #原点に戻す
time.sleep(6)#一時停止
os.system("{0} -ml {1}".format(stage,init)) #初期位置に動かす

###データ取得>MPPC動かす>
for i in range (1,n+1):
    os.chdir("{}".format(contr)) #contollerに移動
    os.system('./Controller.rb  192.168.10.102 -e "increaseHV {}; statusHV ;read {} sokutei_{}; setHV 0 ;quit"'.format(HV,N,i) )
    #increaseHV > status HV #測定（エントリー数:N回）#controllerから抜ける

    os.chdir("{}".format(data)) #contorollerからdataに移動
    os.system("mv sokutei_{}.dat {}".format(i,dir)) #datファイルを保存ディレクトリに移動
    os.system("mv sokutei_{}.root {}".format(i,dir)) #rootファイルを保存ディレクトリに移動

    os.system("{} -ml {}".format(stage,m)) #mだけMPPC動かす

os.chdir("{}".format(test1)) #初めのディレクトリに移動


##githubにいれるまでもforにくみこんでいいかも
#終了 （編集済み）