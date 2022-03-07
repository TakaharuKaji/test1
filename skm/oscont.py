#!/usr/bin/env python3
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
time.sleep(2)#一時停止
os.system("{0} -ml {1}".format(stage,init)) #初期位置に動かす
os.system("mkdir -p {}".format(dir)) #保存するディレクトリを作る
os.chdir("{}".format(contr)) #contollerに移動
###データ取得>MPPC動かす>
for i in range (1,n):
    os.system('./Controller.rb  192.168.10.102 -e "increaseHV {}"'.format(HV) ; statusHV ) #increaseHV > status HV
    os.system('./Controller.rb  192.168.10.102 -e "read {} sokutei_str(i) ".format(N)') #測定（エントリー数:N回）#iは{}とかにしなくてもうごくのか疑問？？？？
    os.system("quit") #controllerから抜ける
    os.system("{}".format(data)) #contorollerからdataに移動
    os.system("mv sokutei_str(i).root {}".format(dir)) #rootファイルを保存ディレクトリに移動
    os.system("{} -ml {}".format(stage,m)) #mだけMPPC動かす
##githubにいれるまでもforにくみこんでいいかも
#終了
