all: ./Data/datos0.pdf

./Data/datos0.pdf: ploting.py ./Data/datos0.dat
	python ploting.py

./Data/datos0.dat: ./a.out
	./a.out 

./a.out: ODE_SecondOrder.c
	cc ODE_SecondOrder.c

clear:
	rm -f ./Data/datos*
	rm -f a.out