#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct estudante_{
	int matricula;//chave
	char nome[30];//valor
}estudante;

typedef struct hash_{
	int qtd, TABLE_SIZE;//qtd = quantidade de elementos inseridos,
	//TABLE_SIZE = tamanho da tabela.
	estudante ** estudantes;//vetor de estudantes.
}hash;


/**
 * Gera a posicao a ser gravada na hash usando o metodo da divisao.
 * @param chave
 * @param TABLE_SIZE
 * @return indice do vetor onde a informação será gravada.
 */
int chave_divisao(int chave, int TABLE_SIZE) {
	if (chave < 0)
		chave *= -1;
	return chave % TABLE_SIZE;
}

/**
 * Gera a posicao a ser gravada na hash usando o metodo da multiplicacao.
 * @param chave
 * @param TABLE_SIZE
 * @return indice do vetor onde a informação será gravada.
 */
int chave_multiplicacao(int chave, int TABLE_SIZE) {
	if (chave < 0)
		chave *= -1;
	double A = 0.7834729723;
	double val = chave * A;
	val = val - (int) val;
	return (int) (val * TABLE_SIZE);
}

/**
 * Gera a posicao a ser gravada na hash usando o metodo da dobra.
 * @param chave
 * @param TABLE_SIZE
 * @return indice do vetor onde a informação será gravada.
 */
int chave_dobra(int chave, int TABLE_SIZE) {
	if (chave < 0)
		chave *= -1;
	if (chave < TABLE_SIZE)
		return chave;

	int numeros[10];
	int inicio = 0;
	int fim = 0;
	int div = chave;
	do {
		int resto = div % 10;
		numeros[inicio] = resto;
		if (numeros[inicio])
			fim = inicio;
		inicio++;
		div = div / 10;
	} while (inicio < 10);
	inicio = 0;

	while (chave > TABLE_SIZE) {
		while (fim > inicio) {
			numeros[inicio] = (numeros[inicio] + numeros[fim]) % 10;
			numeros[fim] = 0;
			inicio++;
			fim--;
		}
		inicio = 0;
		chave = 0;
		int fator = 1;
		while (inicio <= fim) {
			chave += numeros[inicio] * fator;
			fator *= 10;
			inicio++;
		}
		inicio = 0;
	}

	return chave;
}

/**
 * Gera a partir da string um valor inteiro, de modo a poder
 * ser usada em alguma das outras funcoes de hashing.
 * @param str string que se deseja obter a chave.
 * @return valor inteiro obtido à partir da string passada.
 */
int valor_string(char * str){
	int i, valor = 7;
	int tam = strlen(str);
	for(i = 0; i < tam; i++){
		valor = 31 * valor + (int) str[i];
	}
	return valor;
}


estudante * cria_estudante(char * nome, int matricula) {
	estudante *e = malloc(sizeof (estudante));
	e->matricula = matricula;
	strncpy(e->nome, nome, strlen(nome));
	return e;
}

hash * cria_hash(int TABLE_SIZE) {
	hash *ha = malloc(sizeof (hash));

	if (ha != NULL) {
		int i;
		ha->estudantes = malloc(TABLE_SIZE * sizeof (estudante *));
		if (ha->estudantes == NULL) {
			free(ha);
			return NULL;
		}
		ha->TABLE_SIZE = TABLE_SIZE;
		ha->qtd = 0;
		for (i = 0; i < TABLE_SIZE; i++) {
			ha->estudantes[i] = NULL;
		}
	}
	return ha;
}

void libera_hash(hash * ha) {
	if (ha != NULL) {
		int i;

		for (i = 0; i < ha->TABLE_SIZE; i++) {
			if (ha->estudantes[i] != NULL)
				free(ha->estudantes[i]);
		}
		free(ha->estudantes);
		free(ha);
	}
}

int insere_hash_s_colisao(hash * ha, estudante * e) {
	if (ha == NULL || ha->qtd == ha->TABLE_SIZE) {
		return 0;
	}
	int pos = chave_divisao(e->matricula, ha->TABLE_SIZE);

	ha->estudantes[pos] = e;
	ha->qtd++;
	return 1;
}

char* busca_hash_s_colisao(hash * ha, int matricula) {
	int pos = chave_divisao(matricula, ha->TABLE_SIZE);
	return &(ha->estudantes[pos]->nome[0]);
}

/**
 * Tratamento de colisoes desse ponto para baixo.
 */

/**
 * Realiza a sondagem linear na tabela.
 * @param pos posicao atual que se deseja inserir na Hash.
 * @param i deslocamento para se fazer a sondagem em relacao à posição atual.
 * @param TABLE_SIZE tamanho da tabela.
 * @return nova posição calculada.
 */
int sondagem_linear(int pos, int i, int TABLE_SIZE) {
	return ((pos + i) % TABLE_SIZE);
}

/**
 * Realiza a sondagem quadratica na tabela.
 * @param pos posicao atual que se deseja inserir na Hash.
 * @param i deslocamento para se fazer a sondagem em relacao à posição atual.
 * @param TABLE_SIZE tamanho da tabela.
 * @return nova posição calculada.
 */
int sondagem_quadratica(int pos, int i, int TABLE_SIZE) {
	pos = pos + 2 * i + 5 * i*i;
	return (pos % TABLE_SIZE);
}

/**
 * Realiza o duplo hash.
 * @param H1 Valor obtido da primeira funcao de hashing.
 * @param chave chave, que sera usada para se obter o novo índice.
 * @param i tentativa, observe que na primeira vez, somente o valor de H1 é considerado.
 * @param TABLE_SIZE tamanho da tabela.
 * @return nova posição calculada.
 */
int duplo_hash(int H1, int chave, int i, int TABLE_SIZE) {
	//garantindo que a funcao chave_divisao nao retorne 0
	int H2 = chave_divisao(chave, TABLE_SIZE - 1) + 1;
	return ((H1 + i * H2) % TABLE_SIZE);
}

/**
 * Metodo de inserção e busca desse ponto para baixo.
 * Considerando o tratamento de colisões por endereçamento aberto.
 */

/**
 * Insere na hash, considerando a tecnica de endereçamento
 * aberto na hora de resolver colisões.
 * @param ha hash.
 * @param e estudante, a ser inserido.
 * @return 1 caso consiga inserir, e 0 caso contrário.
 */
int insere_hash_end_aberto(hash * ha, estudante * e) {
	if (ha == NULL || ha->qtd == ha->TABLE_SIZE) {
		return 0;
	}
	int pos, i;
	//pos = chave_divisao(e->matricula, ha->TABLE_SIZE);
	//pos = chave_multiplicacao(e->matricula, ha->TABLE_SIZE);
	pos = chave_dobra(e->matricula, ha->TABLE_SIZE);

	for (i = 0; i < ha->TABLE_SIZE; i++) {
		//pos = sondagem_linear(pos, i, ha->TABLE_SIZE);
		//pos = sondagem_quadratica(pos, i, ha->TABLE_SIZE);
		pos = duplo_hash(pos, e->matricula, i, ha->TABLE_SIZE);
		if (ha->estudantes[pos] == NULL) {
			ha->estudantes[pos] = e;
			ha->qtd++;
			return 1;
		}
	}
	return 0;
}

/**
 * Busca na hash, considerando que na inserção foi usada 
 * a técnica de endereçamento aberto na hora de resolver colisões.
 * @param ha hash.
 * @param matricula matrícula do estudante, que se deseja buscar.
 * @return ponteiro para o nome do estudante, caso ele esteja na hash,
 * ou NULL caso contrário.
 */
char* busca_hash_end_aberto(hash * ha, int matricula) {
	int i, pos;
	//pos = chave_divisao(matricula, ha->TABLE_SIZE);
	//pos = chave_multiplicacao(e->matricula, ha->TABLE_SIZE);
	pos = chave_dobra(matricula, ha->TABLE_SIZE);

	for (i = 0; i < ha->TABLE_SIZE; i++) {
		//pos = sondagem_linear(pos, i, ha->TABLE_SIZE);
		//pos = sondagem_quadratica(pos, i, ha->TABLE_SIZE);
		pos = duplo_hash(pos, matricula, i, ha->TABLE_SIZE);
		if (ha->estudantes[pos] == NULL) {
			return NULL;
		} else if (ha->estudantes[pos]->matricula == matricula) {
			return &(ha->estudantes[pos]->nome[0]);
		}
	}
	return NULL;
}

int main() {
	hash * ha = cria_hash(1000);

	estudante * e = cria_estudante("Flavio Barbieri\0", 125);
	insere_hash_end_aberto(ha, e);

	e = cria_estudante("Joao das Couves\0", 1125);
	insere_hash_end_aberto(ha, e);

	char * a = busca_hash_end_aberto(ha, 125);
	if (a != NULL)
		printf("%s\n", a);
	else
		printf("Aluno nao encontrado.\n");

	a = busca_hash_end_aberto(ha, 1125);
	if (a != NULL)
		printf("%s\n", a);
	else
		printf("Aluno nao encontrado.");

	libera_hash(ha);
	return (EXIT_SUCCESS);
}