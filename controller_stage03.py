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
ruby = "/home/sc2021/workdir/controller_20170425/Controller.rb 192.168.10.102"
#os.system("cd /home/sc2021/workdir/controller_20170425") #作業場へ移動

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