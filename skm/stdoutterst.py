import os
import sys
import subprocess

cmd = "ls -l"
#cmd = "ruby returntest.rb"
runcmd = subprocess.check_output(cmd)
