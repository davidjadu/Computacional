import numpy as np
import sys, string, os

m=int(sys.argv[1])
nd_prom = []
std = []
d = []
nd = []

for i in range(50):
    d.append(10*i+10)
    nd.append([])

def marchar_hasta(parar, x, y, z, n):
    while (x**2+y**2+z**2<= parar**2):
        dx=2.0*np.random.random()-1.0
        dy=2.0*np.random.random()-1.0
        if (dx**2+dy**2>=1):
            n -= 1
        else:
            x+=dx
            y+=dy
            if(np.random.random()<0.5):
                z+= np.sqrt(1-(dx**2+dy**2))
            else:
                z-= np.sqrt(1-(dx**2+dy**2))
        n += 1
    return x,y,z,n

for i in range(m):
    x=0
    y=0
    z=0
    steps=0
    for j in range(50):
        x,y,z, steps = marchar_hasta(d[j],x,y,z,steps)
        nd[j].append(steps)

for i in range(50):
    suma = 0
    dif = 0
    for j in range(m):
        suma += nd[i][j]
    nd_prom.append(suma/(m+0.0))
    for k in range(m):
        dif += (nd[i][k]-nd_prom[i])**2
    std.append(np.sqrt(dif/(m+0.0)))

fileout = open ("final_stats_3D_M.dat", "w")

for i in range(50):
    fileout.write("%f %f %f \n" % (d[i], nd_prom[i], std[i]))
