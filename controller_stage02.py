#!/usr/bin/env python3

import os

n = 5 #測定回数
m = 500 #一回の移動で動かす距離1mm
l = 28000 #初期位置

os.system("cd /home/sc2021/workdir/controller_20170425") #作業場へ移動
os.system("./stage.py -o") #原点に戻す
os.system("./stage.py -ml l") #初期位置にいく
os.system("mkdir -p data/dir1") #保存するディレクトリを作る

for i in range (n):
    os.system("./Controller.rb 192.168.10.102")
    os.system("statusHV")
    os.system("cd /home/sc2021/workdir; ls") #測定
    os.system("cd /home/sc2021/workdir; ls") #contorollerからdataに移動
    os.system("cd /home/sc2021/workdir; ls") #rootファイルを保存ディレクトリに移動

    os.system("cd /home/sc2021/workdir; ls") #controllerから抜ける
    os.system("cd /home/sc2021/workdir; ls") #移動
#終了


os.system("cd /home/sc2021/workdir; ls")
os.system("cd /home/sc2021/workdir; ls")
os.system("cd /home/sc2021/workdir; ls")
os.system("cd /home/sc2021/workdir; ls")
os.system("cd /home/sc2021/workdir; ls")

args = ['ls', '-l', '-a']
try:
    res = subprocess.run("")
#=> "ls -l -a" の実行結果
