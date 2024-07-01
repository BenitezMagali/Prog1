/*### Ejercicio 1

Escriba un programa corto en `C` (no hace falta que este resuelto con funciones) que declare e inicialice a cualquier valor deseado, sin ser necesario que sea ingresado por el usuario, 
variables de tipo `double`, `int` y `char`.  A continuación, declare e inicialice un puntero a cada una de las tres variables. Su programa debe imprimir la dirección y el valor almacenado 
y el tamaño de la memoria (en bytes) de cada una de las seis variables.

Utilice el especificador de formato "%p" para imprimir direcciones de punteros (las cuales están en hexadecimal). 

Para obtener los tamaños en memoria de las variables, utilice el 
operador `sizeof` para determinar el tamaño de memoria 
asignado para cada variable.

Para armar la salida en columnas, pueden usar tabuladores `\t` en el string del `printf`.

**Salida esperada**

```
La direccion del char			____ es 0x______
La direccion del int			____ es 0x______
La direccion del double			____ es 0x______
La direccion del char*			____ es 0x______
La direccion del int*			____ es 0x______
La direccion del double*		____ es 0x______

La valor del char				____ es   ______
La valor del int			    ____ es   ______
La valor del double				____ es   ______
La valor del char*				____ es 0x______
La valor del int*				____ es 0x______
La valor del double*			____ es 0x______

El tamaño del char				es ______ bytes
El tamaño del int				es ______ bytes
El tamaño del double			es ______ bytes
El tamaño del char*				es ______ bytes
El tamaño del int*				es ______ bytes
El tamaño del double*			es ______ bytes
```
La notación `0x` se utiliza para indicar que el número a continuación está en base 16, hexadecimal. De la misma manera que los literales
para números enteros en esta base.

En donde el primer espacio es para el nombre de la variable*/
#include <stdio.h>

void imprimoDireccion(void* puntero, char* tipo);
void imprimoValor(char a, int b, double c, char* p_a, int* p_2, double* p_3);
void imprimoTamanio(int tamanio, char* tipo);

int main (){
	double doble = 3.14;
	int inti = 101;
	char caracter = 'x';

	double * p_doble = &doble;
	int* p_inti = &inti;
	char* p_caracter = &caracter;

	imprimoDireccion(&caracter, "char");
	imprimoDireccion(&inti, "int");
	imprimoDireccion(&doble, "double");
	imprimoDireccion(&p_caracter,"char*");
	imprimoDireccion(&p_inti,"int*");
	imprimoDireccion(&p_doble,"double*");

	imprimoValor(caracter,inti,doble,p_caracter,p_inti,p_doble);

	imprimoTamanio(sizeof(caracter),"char");
	imprimoTamanio(sizeof(inti),"int");
	imprimoTamanio(sizeof(doble),"doble");

	imprimoTamanio(sizeof(p_caracter),"char*");
	imprimoTamanio(sizeof(p_inti),"int");
	imprimoTamanio(sizeof(p_doble),"double");


}

void imprimoDireccion (void* puntero, char* tipo){
	//printf("La direccion del %s es %p\t \n",tipo, puntero);
	//Usamos %-12s en el formato de printf para asegurar que el tipo se imprima en una columna de ancho fijo.
	printf("La direccion del %-12s es %p\n", tipo, puntero);
}

void imprimoValor(char a, int b, double c, char* p_a, int* p_2, double* p_3){
	printf("El valor del char\t es %c \n", a);
	printf("El valor del int\t es %i \n", b);
	printf("El valor del double\t es %f \n", c);
	// Convertimos los punteros a void* en las impresiones de direcciones para asegurar la compatibilidad con %p.
	printf("El valor del char*\t es %p \n", (void*)p_a);
	printf("El valor del int*\t es %p \n", (void*)p_2);
	printf("El valor del double*\t es %p \n", (void*)p_3);
}

void imprimoTamanio (int tamanio, char* tipo){
	printf("El tamanio del %-12s es %d\t \n",tipo, tamanio);
}