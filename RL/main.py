
# -*- coding: utf-8 -*-
"""
Created on Fri Jun 26 11:46:18 2020

@author: 86159
"""

import os
import json
import time
import subprocess

loadlist = []
resultlist = []
for i in range(10):
    ltpstr = 'Data/Person' + str(i) + '_main.json'
    rtpstr = 'Data/Result' + str(i) + '_MAIN___'
    loadlist.append(ltpstr)
    resultlist.append(rtpstr)


start = 0
end = 9
# times = 1
for i in range(start, end+1):
    print(loadlist[i])
    for j in range(1):
        fpath = "C:/Users/flh/Documents/Unreal Projects/ToolMan/Data/FileName.json"
        loadfilestr = loadlist[i]
        resultfilestr = resultlist[i] + '_' + str(j) + '.json'
        filename = [loadfilestr, resultfilestr]

        if not os.path.isfile(resultfilestr):
            with open(fpath, 'w') as file_obj:
                json.dump(filename, file_obj)


            # os.popen("C:/Users/flh/Desktop/ToolMan/ToolMan.lnk")
            child = subprocess.Popen(["C:/Program Files/Epic Games/UE_4.25/Engine/Binaries/Win64/UE4Editor.exe", "C:/Users/flh/Documents/Unreal Projects/ToolMan/ToolMan.uproject", "-game", "-windowed"])

            cond = 2
            rpath = "C:/Users/flh/Documents/Unreal Projects/ToolMan/Data/" + filename[1]
            while True:
                if os.access(rpath, os.F_OK):
                    cond -= 1
                if cond == 0:
                    os.system("TASKKILL /F /IM UE4Editor.exe")
                    break
                time.sleep(20)
            print("finish:%d", j)
