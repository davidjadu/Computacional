import numpy as np
import matplotlib.pyplot as plt

data=np.loadtxt("data_python.dat")

fig=plt.figure()
ax=plt.axes()

ax.plot(data[698, 1:])
ax.set_title("diffusion equation python")

filename = "graph_python"
plt.savefig(filename+'.pdf', format = 'pdf', transparent= True)
plt.close()
