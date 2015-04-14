# Ma Make File
introSeminar: intro.o shaderSetup.o
		gcc -o introSeminar intro.o shaderSetup.o -framework OpenGL -framework GLUT

shaderSetup.o: shaderSetup.c shaderSetup.h
		gcc -c -std=c99 shaderSetup.c

intro.o: intro.c shaderSetup.c shaderSetup.h
		gcc -c -std=c99 intro.c

clean:
		$(RM) introSeminar *.o
