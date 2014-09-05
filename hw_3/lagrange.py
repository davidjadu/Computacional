import numpy as np

h=1e-4
M2=1
M1=332948.6
c=M2/(M1+M2) #Centro de Masa

x=[]
y=[]

def newton(x0, y0,h):
    x=x0
    y=y0
    while ((abs(fun1(x,y))>(1e-9) or abs(fun2(x,y))>(1e-9))):
        dx, dy= np.linalg.solve(np.array([[derivate_x(fun1,x,y,h),derivate_y(fun1,x,y,h)],[derivate_x(fun2,x,y,h),derivate_y(fun2,x,y,h)]]), np.array([-fun1(x,y),-fun2(x,y)]))
        x+=dx
        y+=dy
    return x,y

def fun1(x,y):
    return M1/(x**2+y**2)*((x*(c-x)-y**2)/(np.sqrt(x**2+y**2)))+M2/((x-1)**2+y**2)*(((x-1)*(c-x)-y**2)/(np.sqrt((1-x)**2+y**2)))+(M1+M2)*((x-c)**2+y**2)
    
def fun2(x,y):
    return M1/(x**2+y**2)*((c*y)/(np.sqrt(x**2+y**2)))+M2/((1-x)**2+y**2)*((c*y-y)/(np.sqrt((1-x)**2+y**2)))
    
def derivate_x(f,x,y,h):
    return 1/(2.0*h)*(f(x+h,y)-f(x-h,y))

def derivate_y(f,x,y,h):
    return 1/(2.0*h)*(f(x,y+h)-f(x,y-h))


"""    
Un cuerpo que que orbite apenas mas cerca del sol que la tierra tendra una velocidad angular apenas mas grande que la tierra; pero si se encuentra la tierra al otro lado, se tendra que esta reducira levemente esta velocidad haciendola un poco mas lento. Por tanto se espera encontrar un punto entre la tierra y el sol (L1)
"""
x_actual, y_actual = newton(0.5,0,h)
x.append(x_actual)
y.append(y_actual)

"""
Un cuerpo que que orbite apenas mas lejos del sol que la tierra tendra una velocidad angular apenas mas pequena que la tierra; pero si se encuentra la tierra al mismo lado del sol, se tendra que asta aumentara levemente esta velocidad haciandola un poco mayor. Por tanto se espera encontrar un punto en la linea que une el sol y la tierra mas alla de esta ultima (L2)
"""
x_actual, y_actual = newton(1.5,0,h)
x.append(x_actual)
y.append(y_actual)

"""
Un cueerpo que orbite a poco mas que la distancia entre el sol y la tierra tendra una velocidad apenas poco menos que la velocidad angular de la tierra. Pero si la la tierra se encuentra completamnete al otro lado del sol, entonces aumentara un poco la velocidad. Por tanto se espera encontrar un punto cerca de alli (L3)
"""
x_actual, y_actual = newton(-1.0,0,h)
x.append(x_actual)
y.append(y_actual)

"""
Si un cuerpo se encuentra sobre la linea x=0.5 se tiene que debido a que la fuerza gravitacional es proporcional a la masa, asi como el centro de masa del sistema es lineal con la masa, la fuerza ira dirigida al centro de masa. sobre otras lineas, la fuerza no va dirigida al centro de masa, por tanto no pueden haber mas soluciones. Ademas como el problema es totalmente simetrico sobre el eje y se esperan dos soluciones sobre esto linea (L4,L5)
"""
x_actual, y_actual = newton(0.5,1,h)
x.append(x_actual)
y.append(y_actual)

x_actual, y_actual = newton(0.5,-1,h)
x.append(x_actual)
y.append(y_actual)

"""
Por el analisis realizado no se esperan encontrar mas puntos, De igual manera si se ponen otros numeros iniciales, siempre el metodo converge a alguno de los puntos anteriores
Nota: No hay tildes, porque el programa no me compila con tildes
"""


fileout = open("puntos_lagrange.dat","w")
for i in range(len(x)):
    fileout.write("%f %f \n" % (x[i],y[i]))
fileout.close()
