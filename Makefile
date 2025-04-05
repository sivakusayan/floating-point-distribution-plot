graph:
	$(CC) -O3 -lm main.c -o main.out
	./main.out
	gnuplot plot_script
