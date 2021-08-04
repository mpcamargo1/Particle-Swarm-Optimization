#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<string.h>
#include<math.h>
#include"mtwister.h"			// Biblioteca para gerar valores aleatórios -> Implementação em https://github.com/ESultanik/mtwister

// Para facilitar a visualização, configure a largura de tabulação = 4

#define MAX_IT 		1000		// Máximo de Iterações
#define BIRD 		50			// Número de "pássaros"/soluções
#define DIMENSION 	2			// Número de variáveis da função a ser minimizada
#define MIN_VEL 	-3			// Velocidade mínima	
#define MAX_VEL 	3			// Velocidade máxima
#define AC1			2.05		// Valor AC1
#define AC2			2.05		// Valor AC2


// Protótipo da funções
int pso(double position[BIRD][DIMENSION],double velocity[BIRD][DIMENSION]);
void best_individual(double position[BIRD][DIMENSION],double best_ind[BIRD][DIMENSION]);
void best_neighborhood(double position[BIRD][DIMENSION],double best_neigh[BIRD][DIMENSION], double best_ind[][DIMENSION]); 
void init_position(double position[BIRD][DIMENSION]); 
void init_velocity(double velocity[BIRD][DIMENSION]); 
void update(double position[][DIMENSION],double velocity[][DIMENSION],double best_ind[][DIMENSION],double best_neigh[][DIMENSION]);
void report(double position[][DIMENSION],FILE *fp_mean,FILE *fp_min,int iteration);
int index_neighborhood(int n);

double function(double position[DIMENSION]);
double randomizer();
double get_magnitude();
void displaybest(double position[][DIMENSION]);
MTRand r;

int main(void){
    
    clock_t start;
	
    // Vetor de Posição
    double position[BIRD][DIMENSION];
    // Vetor Velocidade
    double velocity[BIRD][DIMENSION];
    
    srand(time(NULL));
    // Inicializa a semente
    r = seedRand(rand());   

    start = clock();
    // Chama a função PSO
    pso(position,velocity);
    fprintf(stderr,"%lf segundos decorridos\n",((double)(clock() - start)) / CLOCKS_PER_SEC);
    
}

double get_random(int M,int N){

	return (M + rand() / (RAND_MAX / (N - M + 1) + 1));

}


double randomizer(){
	// Aleatório entre 0 e AC1;
	return genRand(&r)*AC1;
}

int pso(double position[][DIMENSION],double velocity[][DIMENSION]){
	int t=0;
	// Ponteiro de arquivo
	FILE *fp_mean = fopen("report_mean.txt","w");
	FILE *fp_min = fopen("report_min.txt","w");
	// Vetor de melhor individual
	double best_ind[BIRD][DIMENSION];
	// Vetor melhor vizinho do indíviduo
	double best_neigh[BIRD][DIMENSION];
	// Inicializa as posições
	init_position(position);
	// Os valores da posição inicial é o atual melhor individual
	memcpy(best_ind, position, sizeof best_ind);
	// Inicia a velocidade
	init_velocity(velocity);

	// Laço principal
	while(t < MAX_IT){
		// Atualiza o melhor individual
		best_individual(position,best_ind);
		// Atualiza a melhor vizinhança
		best_neighborhood(position,best_neigh,best_ind);
		// Atualiza as posições
		update(position,velocity,best_ind,best_neigh);
		// Escreve no arquivo o valor médio e o menor valor encontrada na iteração
		report(best_ind,fp_mean,fp_min,t);
		// Incremento		
		t++;
	}
	// Imprime o melhor
	displaybest(best_ind);

	// Fecha os arquivos
	fclose(fp_mean);
	fclose(fp_min);
}

void report(double position[][DIMENSION],FILE *fp_mean,FILE *fp_min,int iteration){
	double mean = function(position[0]);
	double best = function(position[0]);
	int best_index=0;
	for(int i=1;i<BIRD;i++){
			mean += function(position[i]);
			if(function(position[i]) < best){
				best = function(position[i]);
			}

	}
	// Escrever a média da iteração
	if(iteration % 100 == 0){
		fprintf(fp_mean,"%d %lf\n",iteration,mean/BIRD);
		fprintf(fp_min,"%d %lf\n",iteration,best);
	}

}

void displaybest(double position[][DIMENSION]){

	// Procura o melhor e imprime na tela
	double best = function(position[0]);
	int best_index = 0;
	for(int i=1;i<BIRD;i++){
		if(function(position[i]) < best){
			best = function(position[i]);
			best_index = i;
		}
	}

	printf("Solução encontrada\nf(x,y) = %lf, x = %lf , y = %lf\n",best,position[best_index][0],position[best_index][1]);
}

void init_position(double position[][DIMENSION]){
	
	// Inicia as posições iniciais dos individuos
	for(int i=0;i<BIRD;i++){
		        position[i][0] = get_random(-15,-5); 
		        position[i][1] = get_random(-3,3);     
	}

}

double get_magnitude(){
	double random = (double)rand()/RAND_MAX;
	if(random > 0.5)
		return 1;
	else
		return -1;

}
void init_velocity(double velocity[][DIMENSION]){
	// Inicia as velocidades iniciais dos indivíduos
	for(int i=0;i<BIRD;i++)
		for(int j=0;j<DIMENSION;j++){
			velocity[i][j] = randomizer();

			if (velocity[i][j] < MIN_VEL)
				velocity[i][j] = MIN_VEL;
			else if (velocity[i][j] > MAX_VEL)
				velocity[i][j] = MAX_VEL;

		}

}

void update(double position[][DIMENSION],double velocity[][DIMENSION],double best_ind[][DIMENSION],double best_neigh[][DIMENSION]){
	// Laço principal
	for(int i=0;i<BIRD;i++){
		for(int j=0;j<DIMENSION;j++){
			// Gera um aleatório
			double rand = randomizer();
			// Gera outro aleatório
			double rand1 = randomizer();
			// Atualiza a velocidade
			velocity[i][j] = velocity[i][j] + (rand*(best_ind[i][j] - position[i][j])) + (rand1*(best_neigh[i][j] - position[i][j]));
			
			// Verificar se a velocidade ultrapassa o valor máximo ou se é menor que a velocidade mínima
			if(velocity[i][j] < MIN_VEL)
				velocity[i][j] = MIN_VEL;
			else if(velocity[i][j] > MAX_VEL)
				velocity[i][j] = MAX_VEL;

			// Atualiza a posição		
			position[i][j] = position[i][j] + velocity[i][j];
		}
	}	

}

void best_individual(double position[][DIMENSION],double best_ind[][DIMENSION]){

	for(int i=0;i<BIRD;i++){
		// Verificar se valor da função é menor (Minimização)
		if(function(position[i]) < function(best_ind[i]) ){ 		      // Minimização
		
			// Copia o valor da posição para o vetor de melhor individual 
				memcpy(&best_ind[i],&position[i], sizeof best_ind[i]);
				
		}

	}

}

void best_neighborhood(double position[][DIMENSION],double best_neigh[][DIMENSION],double best_ind[][DIMENSION]){
	
	for(int i=0;i<BIRD;i++){
		// Verificar qual vizinho possui o menor valor da função a ser minimizada
		if( function(best_ind[index_neighborhood(i-1)]) < function(best_ind[index_neighborhood(i+1)])){
			// Copia o valor do melhor individual de (i-1) para o vetor de melhor vizinho de i 
			memcpy(&best_neigh[i],best_ind[index_neighborhood(i-1)],sizeof best_neigh[i]);
		}
		else{
			// Copia o valor do melhor individual de (i+1) para o vetor de melhor vizinho de i 
			memcpy(&best_neigh[i],best_ind[index_neighborhood(i+1)],sizeof best_neigh[i]);
		}
	}

}

	

int index_neighborhood(int n){
	int index_last_bird = BIRD-1;

	// Retorna o índice do vizinho de i
	// Implementado vizinhança circular
	if(n>0 && n<=index_last_bird)
		return n;
	else if(n<0)
		return BIRD-1;
	else if(n>BIRD-1)
		return 0;	

}

double function(double position[DIMENSION]){

	switch(DIMENSION){
		case 2:
			// Função a ser minimizada
			return 100*(sqrt(fabs(position[1] - 0.01*pow(position[0],2)))) + 0.01*fabs(position[0] + 10);
			break;
		
	
	}

}




