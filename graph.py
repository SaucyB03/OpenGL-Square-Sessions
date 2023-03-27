import matplotlib.pyplot as plt
import sys

myfile = open("spinnysquare.txt", "r")
print(myfile.read())

user = sys.argv[1]
info = []

print("what")
for line in myfile:
    print("hello?")
    print(line)
    currentline = line.rstrip().split(",")
    user = str(currentline[0])
    info.append(float(currentline[1]))
    info.append(int(currentline[2]))

# graphx = {'Damage dealt':damage, 'Kills':kills}
graphx = range(100, 100 * len(info), 100)
ax = plt.subplot(111)
ax.bar(graphx, info, width=300, color='r', align='center')
plt.gcf().canvas.manager.set_window_title('Open Ended')
plt.title('Stats for ' + user)
plt.xlabel('Stats for ' + user)
plt.xticks(graphx)
plt.ylabel('Points received')
plt.savefig('Stats.png')
plt.show()
myfile.close()
