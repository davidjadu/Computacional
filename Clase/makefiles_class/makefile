all: graph.pdf

graph.pdf: random.data graph.py
	python graph.py

random.data: a.out
	./a.out 200 100

a.out: random.c
	cc random.c

clean:
	rm -f random.data
	rm -f graph.pdf
	rm -f a.out