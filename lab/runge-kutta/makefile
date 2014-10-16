all: datos.pdf

datos.pdf: datos.dat plot.py
	python plot.py

datos.dat: pendulum.py
	python pendulum.py 10 1 0.5
	echo 'Datos Usados A=10, y_0=1, y_prime_0=0.5'

clear: 
	rm -f datos.dat
	rm -f datos.pdf