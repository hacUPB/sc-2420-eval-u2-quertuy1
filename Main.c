#include <stdio.h>
#include <math.h>

float calcula_imc(float,float); //prototipo de la funcion

int main(int argc, char const *argv[])
{
float estatura, peso, IMC;
char nombre [30];

printf("Ingrese su nombre\n");
fgets(nombre, 30, stdin);

printf("Ingrese su peso \n");
scanf("%f", &peso); //pide peso 

printf("Ingrese su estatura \n");
scanf("%f", &estatura); // pide estatura

IMC=calcula_imc(peso, estatura);

printf("%s Su IMC es = %f\n", nombre,IMC); //pone los datos ya entregados 


return 0;
}

float calcula_imc(float peso,float estatura)
{
    float IMC;
    IMC= peso/ pow (estatura,2);
    return IMC;
}
