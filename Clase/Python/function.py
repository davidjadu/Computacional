import numpy as np


n_points=5
a=np.arange(n_points)
b=2.0*a

a=np.random.random(n_points)
b=np.random.random(n_points)

def print_message(message):
    print 'I am here to tell you this:', message

def volume(radius):
    vol= (4.0/3.0)*np.pi*radius**3
    area = 4.0*np.pi*radius**2
    objeto = "esfera"
    return vol, area, objeto

print_message('I will be back in 5 minutes')
v,a,o = volume (5.0)
print "volumen:", v
print "area:", a
print "objeto:", o

print zip(a,b)
for itema, itemb in zip(a,b):
    print itema,itemb
    

n_points=1000
a= np.random.random(1000)
print "siz", np.size(a)
print "mean", np.mean(a)
print "standard deviation", np.std(a)
