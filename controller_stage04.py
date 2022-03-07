#!/usr/bin/env python3

import os
import time

n = 2 #測定回数
m = 500 #一回の移動で動かす距離1mm
init = 28000 #初期位置
HV = 0
N = 10000
stage = "/home/sc2021/workdir/controller_20170425/stage.py"
contr = "/home/sc2021/workdir/controller_20170425"
data = "/home/sc2021/workdir/controller_20170425/data"
dir = "/home/sc2021/workdir/controller_20170425/data/dir5" #保存ディレクトリの指定(測定1回ごとにかえる)
test1 = "/home/sc2021/workdir/test1"

###保存フォルダ(ディレクトリ）の作成と初期位置設定
os.system("{} -o".format(stage)) #原点に戻す
time.sleep(2)#一時停止
os.system("{0} -ml {1}".format(stage,init)) #初期位置に動かす
os.system("mkdir -p {}".format(dir)) #保存するディレクトリを作る

###データ取得>MPPC動かす>
for i in range (1,n):
    os.chdir("{}".format(contr)) #contollerに移動
    os.system('./Controller.rb  192.168.10.102 -e "increaseHV {}; statusHV ;read {} sokutei_{} ;quit"'.format(HV,N,i) )
    #increaseHV > status HV #測定（エントリー数:N回）#controllerから抜ける

    os.chdir("{}".format(data)) #contorollerからdataに移動
    os.system("mv sokutei_{}.root {}".format(i,dir)) #rootファイルを保存ディレクトリに移動

    os.system("{} -ml {}".format(stage,m)) #mだけMPPC動かす

os.chdir("{}".format(test1)) #初めのディレクトリに移動

##githubにいれるまでもforにくみこんでいいかも
#終了 （編集済み） 

"""
os.system("{} -o".format(stage)) #原点に戻す
time.sleep(2)#一時停止
os.system("{0} -ml {1}".format(stage,init)) #初期位置にいく
os.system("mkdir -p {}/data/dir1".format(contr)) #保存するディレクトリを作る
"""
os.chdir("{}".format(contr))

for i in range (1,n):
    os.system('./Controller.rb  192.168.10.102 -e "statusHV ; increaseHV {}"'.format(HV))
   # os.system('./Controller.rb  192.168.10.102 -e "increaseHV {} ".format(HV)#')

    os.system("quit") #controllerから抜ける
    """

    os.system("read N sokutei_str(i)" ) #測定
    os.system("quit") #controllerから抜ける

    os.system("cd data") #contorollerからdataに移動
    os.system("mv sokutei_str(i).root dir1") #rootファイルを保存ディレクトリに移動
    os.system("cd ..") #dataからcontorollerに移動
    os.system("./stage.py -ml m") #移動
#終了
"""
