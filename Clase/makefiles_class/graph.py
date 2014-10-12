import numpy as np
import matplotlib.pyplot as plt

data = np.loadtxt("random.data")

ax=plt.axes()
plt.plot(data)
ax.set_title('Random')
plt.savefig('graph'+'.pdf', format = 'pdf', transparent= True)
plt.close()
