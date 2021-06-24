/*
    Author: Jose Carlos da Silva Filho
    University: Universidade Estadual do Mato Grosso do Sul
    Course: Computer Science
    Github: https://github.com/josefilho
*/

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/******************************************************************************/
/*                            FUNÇÕES UTILIZADAS                              */
/******************************************************************************/

//Utilização: AlocaMatriz(int lenght)
//            lenght - Tamanho que deverá ser alocado
//Retorno: Retorna a Matriz alocada
double** AlocaMatriz(int);

//Utilização: LiberaMatriz(double** Matriz, int lenght)
//            Matriz - Matriz que será desalocada
//            lenght - Tamanho da matriz a ser desalocada
//Retorno: Void
void LiberaMatriz(double**, int);

//Utilização: OrganizaMatriz(double** Matriz, int lenght)
//            Matriz - Matriz a ser organizada
//            lenght - Tamanho da matriz que será organizada
//Retorno: Retorna quantas mudanças de linha foram realizadas
int OrganizaMatriz(double**, int);

//Utilização: ImprimeMatriz(double** Matriz, int lenght)
//            Matriz - Matriz a ser exibida
//            lenght - Tamanho da matriz que será exibida
//Retorno: Void
void ImprimeMatriz(double**, int);

//Utilização: Gauss(double** Matriz, int lenght)
//            Matriz - Matriz a ser para ser resolvida
//            lenght - Tamanho da matriz que será resolvida
//Retorno: Retorna o Determinante de uma matriz
double Gauss(double**, int);

//Utilização: ArredondaDouble(double N)
//            N - Double a ser arredondado
//Retorno: Retorna um double arredondado em 2 casas decimais
double ArredondaDouble(double);


/******************************************************************************/
/*                                  MAIN                                      */
/******************************************************************************/

int main(){
    int lenght;
    printf("Tamanho da matriz: ");
    do{
        scanf("%d", &lenght);
        if(lenght < 1 || lenght > 10) printf("Insira o dado corretamente!\n");
    }while(lenght < 1 || lenght > 10);
    
    double** matriz = AlocaMatriz(lenght);
    
    printf("\t\tDADOS DA MATRIZ\n");
    for(int i = 0; i < lenght; ++i){
        for(int j = 0; j < lenght; ++j){
            printf("Matriz(%dx%d): ", i+1, j+1);
            scanf("%lf", &matriz[i][j]);
        }
    }
    printf("------------- Matriz Entrada -------------\n");
    ImprimeMatriz(matriz, lenght);
    printf("------------------------------------------\n\n");
    double determinante = Gauss(matriz, lenght);
    
    printf("\nDeterminante: %.2lf\n", determinante);
    printf("\n");
    LiberaMatriz(matriz, lenght);
    return 0;
}

/******************************************************************************/
/*                        IMPLEMENTAÇÃO DAS FUNÇÕES                           */
/******************************************************************************/

double** AlocaMatriz(int lenght){
    if(lenght > 0){
        double** M;
        
        M = (double**) malloc(sizeof(double*) * lenght);
        if(M == NULL){
            printf("Memoria insuficiente.\n");
            exit(1);
        }
        for(int i = 0; i < lenght; i++){
            M[i] = (double*) malloc(sizeof(double) * lenght);
            if(M[i] == NULL){
              printf("Memoria insuficiente.\n");
              exit(1);
            }
        }
        return M;
    } else return NULL;
}

void LiberaMatriz(double **M, int lenght){
  for(int i = 0; i < lenght; i++)
    free(M[i]);
  free(M);
}

void ImprimeMatriz(double** matriz,int lenght){
    for(int i = 0; i < lenght; ++i){
        for(int j = 0; j < lenght; ++j){
            printf("%.2lf\t", matriz[i][j]);
        }
        printf("\n");
    }
}

int OrganizaMatriz(double** Matriz, int lenght){
    int j;
    int changes = 0;
    double* MKey = (double*) malloc(sizeof(double) * lenght);
    for(int i = 1; i < lenght; ++i){
        MKey = Matriz[i];
        j = i - 1;
        while(j >= 0 && Matriz[j][0] < MKey[0]){
            Matriz[j+1] = Matriz[j];
            --j;
            ++changes;
        }
        Matriz[j+1] = MKey;
    }
    return changes;
}

double ArredondaDouble(double N){
    char buffer[256];
    sprintf(buffer, "%.2lf", N);
    if(!strcmp(buffer, "-0.00")) N = 0;
    else{
        sscanf(buffer, "%lf", &N);
    }
    return N;
}

double Gauss(double** matriz, int lenght){
	double divisao, det = 1;
	
    int s = OrganizaMatriz(matriz, lenght);
	
	for(int i = 0; i < lenght-1; ++i)
	{
		for(int j = i+1; j < lenght; ++j)
		{
			divisao = - matriz[j][i] / matriz[i][i];
			for(int k = 0; k < lenght; ++k) {
			    printf("MATRIZ[%d][%d] = %.2lf + (%.2lf * %.2lf)\n", 
			    j,
			    k, 
			    matriz[j][k], 
			    matriz[i][k], 
			    divisao);
		        
		        matriz[j][k] = ArredondaDouble(
		            matriz[j][k] + 
		            (matriz[i][k] * divisao)
		        );
			}
			printf("\n==========================================\n");
			ImprimeMatriz(matriz, lenght);
			printf("==========================================\n");
		}
	}

	for (int i = 0; i < lenght; i++) det = det * matriz[i][i];
	if(s % 2 != 0) det = det * (-1);
	if(fabs(det) < 1E-12) return 0;
	return ArredondaDouble(det);
} 
