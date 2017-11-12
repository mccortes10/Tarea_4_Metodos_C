all: Resultados_hw4.pdf Extremos_fijos.png Perturbada.png sonido.wav Tiempos_Tambor.png Animacion_Tambor.gif Ondaextfijos.txt Ondaperturbada.txt tambor.dat Ondas.x

Resultados_hw4.pdf: Extremos_fijos.png Perturbada.png Tiempos_Tambor.png
	pdflatex Resultados_hw4.tex

Extremos_fijos.png Perturbada.png sonido.wav Tiempos_Tambor.png Animacion_Tambor.gif: Plots.py Ondaextfijos.txt Ondaperturbada.txt tambor.dat
	python Plots.py

Ondaextfijos.txt Ondaperturbada.txt tambor.dat :	Ondas.x
	./Ondas.x

Ondas.x: Ondas.c
	gcc Ondas.c -lm -o Ondas.x

clean: 
	rm *.x *.gif *.png