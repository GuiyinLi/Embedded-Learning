'''
Author: Ken Kaneki
Date: 2021-06-24 01:50:44
LastEditTime: 2021-06-24 02:04:27
Description: README
FilePath: \Embedded\SSH Keeplive.py
'''
import os
import time
count = 0
while True:

    os.system('ssh -T git@github.com')
    count = count+1
    print('ssh keeplive', count)
    time.sleep(10)
