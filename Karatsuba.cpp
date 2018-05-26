#include<iostream>
#include<stdio.h>
 
using namespace std;

int multiplicaBit(string bit1, string bit2){  
    return (bit1[0] - '0')*(bit2[0] - '0');  
}

int modificaTamanho(string &string1, string &string2) {
    int tamanho1 = string1.size();
    int tamanho2 = string2.size();
    if (tamanho1 < tamanho2)
    {
        for (int i = 0 ; i < tamanho2 - tamanho1 ; i++)
            string1 = '0' + string1;
        return tamanho2;
    }
    else if (tamanho1 > tamanho2)
    {
        for (int i = 0 ; i < tamanho1 - tamanho2 ; i++)
            string2 = '0' + string2;
    }
    return tamanho1;
}

string adicionaBitString(string primeira, string segunda) {
    string resultado;
 
    int length = modificaTamanho(primeira, segunda);
    int estouro = 0;
 
    for (int i = length-1 ; i >= 0 ; i--)
    {
        int primeiroBit = primeira.at(i) - '0';
        int segundoBit = segunda.at(i) - '0';
 
        int a = (primeiroBit ^ segundoBit ^ estouro)+'0';
 
        resultado = (char)a + resultado;
 
        estouro = (primeiroBit&segundoBit) | (segundoBit&estouro) | (primeiroBit&estouro);
    }
 
    if (estouro)  
	resultado = '1' + resultado;
 
    return resultado;
}

long int multiplicacao(string num1, string num2) {
    int x = modificaTamanho(num1, num2);
 
    if (x == 0) return 0;
    if (x == 1) return multiplicaBit(num1, num2);
 
    int primeiraParte = x/2;
    int segundaParte = (x-primeiraParte);
 
    string num1Esquerda = num1.substr(0, primeiraParte);
    string num1Direita = num1.substr(primeiraParte, segundaParte);
 
    string num2Esquerda = num2.substr(0, primeiraParte);
    string num2Direita = num2.substr(primeiraParte, segundaParte);
 
    long int valorRecursivo1 = multiplicacao(num1Esquerda, num2Esquerda);
    long int valorRecursivo2 = multiplicacao(num1Direita, num2Direita);
    long int valorRecursivo3 = multiplicacao(adicionaBitString(num1Esquerda, num1Direita), adicionaBitString(num2Esquerda, num2Direita));
 
    return valorRecursivo1*(1<<(2*segundaParte)) + (valorRecursivo3 - valorRecursivo1 - valorRecursivo2)*(1<<segundaParte) + valorRecursivo2;
}

int main(){

    //Numero para realizar multiplicacao
    //Devem ser dados em binario
    printf ("%ld\n", multiplicacao("1011", "0010")); //11 * 2
    printf ("%ld\n", multiplicacao("1010", "1111")); //10 * 15
}
