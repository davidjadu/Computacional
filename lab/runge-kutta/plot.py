import matplotlib.pyplot as plt
import numpy as np  

fig=plt.figure()
ax=plt.axes()
filename = "datos"
data = np.loadtxt(filename+'.dat')
ax.plot(data[:,0],data[:,1])
plt.savefig(filename+'.pdf', format = 'pdf', transparent= True)
