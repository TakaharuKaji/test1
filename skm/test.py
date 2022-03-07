import os
import time
import sys

dir = "test_dir2"

def check_makedirs(path):
    if not os.path.isdir(path):
        os.system("mkdir -p {}".format(dir))
    else:
        print("!! dir already exists !!")#同名のディレクトリを作成しようとしました
        sys.exit()
check_makedirs(dir)
print(dir)
#os.system("mkdir -p {}".format(dir))
