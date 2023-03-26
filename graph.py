import matplotlib.pyplot as plt
import os
import platform
import subprocess
from subprocess import Popen, PIPE, check_output
import time

myfile = open("spinnysquare.txt", "r")
print(myfile.read())

for line in myfile:
        currentline = line.split(",")
        user = str(currentline[0])
        damage = int(currentline[1])
        kills = int(currentline[2])
        
`graphx = {'Damage dealt':damage, 'Kills':kills}
ax = plt.subplot(111)
ax.bar(graphx, height=300, width=300, color='r', align='center')
plt.gcf().canvas.manager.set_window_title('Open Ended')
plt.title('Stats for ' +user)
plt.xlabel('Stats for '+user)
plt.xticks(graphx)
plt.ylabel('Points received')
plt.savefig('Stats.png')
plt.show()
myfile.close()

