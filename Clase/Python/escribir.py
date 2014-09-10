import numpy as np

n_points =440
x= np.random.random(n_points)
y= np.random.random(n_points)

fileout= open ("random_xy.dat", "w")

for i in range (n_points):
    fileout.write("%f %f \n" % (x[i],y[i]))

fileout.close()
