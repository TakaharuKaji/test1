import os
import sys

def makeCSV(csvname):
    if not os.path.isfile(csvname):
        f = open(csvname, "w")
    else:
        print("%s already exists" % csvname)
        sys.exit()

def writeCSV(csvname,filename,HV,point):
    with open(csvname, mode="a") as f:
        f.write("%s,%f,%f\n" % (filename, HV, point))


if __name__ == '__main__':
    print("測定No.？:")
    expNo = int(input())
    csvname = "exp%d.csv" % expNo
    makeCSV(csvname)
    for i in range(10):
        filename = "test%d.root" % i
        HV = 50
        point = 3.0
        writeCSV(csvname, filename, HV, point)
