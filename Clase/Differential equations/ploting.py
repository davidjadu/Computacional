import matplotlib.pyplot as plt
import numpy as np
from mpl_toolkits.mplot3d import Axes3D

for i in range(20):
    fig=plt.figure()
    ax=fig.gca(projection='3d')
    filename = 'Data/datos'+`i`
    data = np.loadtxt(filename +'.dat')
    ax.plot(data[:,0],data[:,1],data[:,2])
    plt.savefig(filename+'.pdf', format = 'pdf', transparent= True)
