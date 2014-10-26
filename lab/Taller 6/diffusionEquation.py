import numpy as np


n_x = 80
n_t = 700

c = 1.0
nu = 0.3
sigma = 0.2

x = np.linspace(0, 1.0, n_x)
dx = x[1]-x[0]


dt = sigma*dx**2/nu
alpha = dt/dx**2

u = np.zeros(n_x)

u[np.where((x<0.66) & (x>0.33))] = 1.0

fileout= open ("data_python.dat", "w")

for n in range(n_t):
    u_past = u.copy() 
    fileout.write("%f " % (n*dt))
    for i in range(1,n_x-1):
        u[i] = nu * alpha * u_past[i+1]  + (1.0 - 2.0*nu*alpha)*u_past[i] + nu*alpha*u_past[i-1]
        fileout.write("%f " % (u[i]))
    fileout.write("\n")
                      
        
