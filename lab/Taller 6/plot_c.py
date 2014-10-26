import numpy as np
import matplotlib.pyplot as plt

data=np.loadtxt("data_c.dat")

fig=plt.figure()
ax=plt.axes()

ax.plot(data[-1, 1:])
ax.set_title("diffusion equation c")

filename = "graph_c"
plt.savefig(filename+'.pdf', format = 'pdf', transparent= True)
plt.close()
