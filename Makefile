build:
	gcc -c -o main.o main.c 
	gcc -c -o e1.o e1.c 
	gcc -c -o e23.o e23.c
	gcc -c -o c.o c.c
	gcc -c -o u.o u.c
	gcc -c -o st.o st.c
	gcc -o tema1 main.o e1.o e23.o c.o u.o st.o -lm 

clean:
	rm -f *.o tema1
