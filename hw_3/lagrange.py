import numpy as np

M_EARTH = 1
M_SUN = 332948.6 
ITERATIONS = 100000

mass_center = 1.0/(M_SUN + M_EARTH)*(M_EARTH)
mu = M_EARTH*M_SUN/(M_EARTH+M_SUN)

x = []
y = []

def newton(func,func_prime, inicio):
    sol = inicio
    delta = 0
    for n in range(ITERATIONS):
        if (func(sol)==0):
            break
        else :
            delta = - func(sol)/func_prime(sol)
            sol += delta
    return sol

def f_lagrange_1(r):
    return M_SUN/r**2 - M_EARTH/(1.0-r)**2 - (r-mass_center)*(M_EARTH+M_SUN)

def f_lagrange_1_prime(r):
    return -2*M_SUN/r**3 - 2*M_EARTH/(1.0-r)**3 - (M_EARTH+M_SUN)
    
y.append(0) #L1 is clearly in y=0
x.append(newton(f_lagrange_1, f_lagrange_1_prime, 0.8))

def f_lagrange_2(r):
    return M_SUN/r**2 + M_EARTH/(1.0-r)**2 - (r-mass_center)*(M_EARTH+M_SUN)

def f_lagrange_2_prime(r):
    return -2*M_SUN/r**3 + 2*M_EARTH/(1.0-r)**3 - (M_EARTH+M_SUN)

y.append(0) #L2 is clearly in y=0
x.append(newton(f_lagrange_2, f_lagrange_2_prime, 1.1))

def f_lagrange_3(r):
    return M_SUN/r**2 + M_EARTH/(1.0-r)**2 - (M_EARTH+M_SUN)*(mass_center -r)

def f_lagrange_3_prime(r):
    return -2*M_SUN/r**3 + 2*M_EARTH/(-r+1.0)**3 + (M_EARTH+M_SUN)

y.append(0) #L3 is clearly in y=0
x.append(newton(f_lagrange_3, f_lagrange_3_prime, -0.9))

x.append(0.5) #L4 is clearly in x=0.5



x.append(0.5) #L5 is clearly in x=0.5
y.append(-np.sqrt(1-0.25)) #Pitagoras theorem

fileout = open("puntos_lagrange.dat","w")
for i in range(len(x)):
    fileout.write("%f %f \n" % (x[i],y[i]))
fileout.close()
