import numpy as np
import matplotlib.pyplot as plt

n_x=1024
n_y=512

a=np.random.random((n_x,n_y))

fig=plt.figure()
ax=plt.axes()

index = np.where(a<0.5)
a[index]=0.0
index = np.where(a>=0.5)
a[index]=1.0

ax.set_title("Random Values")
plt.imshow(a, cmap="bone")

filename = "random_plane2"
plt.savefig(filename+'.pdf', format = 'pdf', transparent= True)
plt.close()
