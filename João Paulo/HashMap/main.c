#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct estudante_ {
    int matricula;
    char nome[30];
} estudante;

typedef struct  hash_ {
    int qtd, TABLE_SIZE;
    estudante ** estudantes;
}hash;


/**FUNÇÕES DE HASHING**/

int chave_divisao(int chave, int TABLE_SIZE) {
    if (chave < 0) {
        chave *= -1;
    }

    return chave % TABLE_SIZE;
}

int chave_multiplicacao(int chave, int TABLE_SIZE) {
    if (chave < 0) {
        chave *= -1;
    }

    double A = 0.7834729723;
    double val = chave * A;
    val = val - (int) val;
    return (int) (val * TABLE_SIZE);
}

int chave_dobra(int chave, int TABLE_SIZE) {
    if (chave < 0) {
        chave *= -1;
    }

    if (chave < TABLE_SIZE) {
        return chave;
    }

    int numeros[10];
    int inicio = 0;
    int fim = 0;
    int div = chave;
    
    do {
        int resto = div % 10;
        numeros[inicio] = resto;
        if (numeros[inicio])
            fim = inicio;
        inicio ++;
        div = div / 10;
    } while (inicio < 10);

    inicio = 0;

    while (chave > TABLE_SIZE) {
        while (fim > inicio) {
            numeros[inicio] = (numeros[inicio] + numeros[fim]) % 10;
            numeros[fim] = 0;
            inicio++;
            fim --;
        }
        inicio = 0;
        chave = 0;
        int fator = 1;
        while (inicio <= fim) {
            chave += numeros[inicio] * fator;
            fator *= 10;
            inicio ++;
        }
        inicio = 0;
    }
    return chave;
}

int valor_string(char * str) {
    int i, valor = 7;
    int tam = strlen(str);
    for(i = 0; i < tam; i++) {
        valor = 31 * valor + (int) str[i];
    }
    return valor;
}

/**CÓDIGO PRINCIPAL**/

estudante * cria_estudante(char * nome, int matricula) {
    estudante * e = malloc(sizeof(estudante));
    e->matricula = matricula;
    strncpy(e->nome, nome, strlen(nome));
    return e;
};

hash * cria_hash(int TABLE_SIZE) {
    hash *ha = malloc(sizeof (hash) );

    if (ha != NULL) {
        int i;
        ha->estudantes = malloc(TABLE_SIZE * sizeof(estudante *));
        if(ha->estudantes == NULL) {
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
};

void libera_hash(hash * ha) {
    if (ha != NULL) {
        int i;


        for(i = 0; i < ha->TABLE_SIZE; i++) {
            if (ha->estudantes != NULL) {
                free(ha->estudantes[i]);
            }

            free(ha->estudantes);
            free(ha);
        }
    }
};

/**SEM TRATAMENTO DE COLISÃO DE HASH**/

int insere_hash_s_colisao(hash * ha, estudante * e) {
    if (ha == NULL || ha->qtd == ha->TABLE_SIZE) {
        return 0;
    }

    int pos = chave_divisao(e->matricula, ha->TABLE_SIZE);
    ha->estudantes [pos] = e;
    ha->qtd++;
    return 1;
}

char * busca_hash_s_colisao(hash * ha, int matricula) {
    int pos = chave_divisao(matricula, ha->TABLE_SIZE);
    return &(ha->estudantes[pos]->nome[0]);
}

/**COM TRATAMENTO DE COLISÃO DE HASH**/

int sondagem_linear(int pos, int i, int TABLE_SIZE) {
    return ((pos + i) % TABLE_SIZE);
}

int sondagem_quadratica(int pos, int i, int TABLE_SIZE) {
    pos = pos + 2 * i + 5 * i * i; // 2 & 5 são escolhidos com aleatoriedade, porém, é "bom" ser números primos
    return (pos % TABLE_SIZE);
}

int duplo_hash(int H1, int chave, int i, int TABLE_SIZE) {
    int H2 = chave_divisao(chave, TABLE_SIZE - 1) + 1;
    return ((H1 + i * H2) % TABLE_SIZE);
}

int insere_hash_end_aberto(hash * ha, estudante * e) {
    if (ha == NULL || ha->qtd == ha->TABLE_SIZE) {
        return 0;
    }

    int pos, i;

    pos = chave_dobra(e->matricula, ha->TABLE_SIZE); //pode ser chave_divisao ou chave_multiplicacao

    for(i = 0; i < ha->TABLE_SIZE; i++) {
        pos = duplo_hash(pos, e->matricula, i, ha->TABLE_SIZE); //pode ser sondagem_linear ou sondagem_quadratica
        if (ha->estudantes[pos] == NULL) {
            ha->estudantes[pos] = e;
            ha->qtd++;
            return 1;
        }
    }
    return 0;
}

char * busca_hash_end_aberto(hash * ha, int matricula) {
    int i, pos;

    pos = chave_dobra(matricula, ha->TABLE_SIZE); //tem que ser o mesmo metodo do insere_hash_end_aberto
    for (i = 0; i < ha->TABLE_SIZE; i++) {
        pos = duplo_hash(pos, matricula, i, ha->TABLE_SIZE); //tem que ser o mesmo metodo do insere_hash_end_aberto
        if (ha->estudantes[pos] == NULL) {
            return NULL;
        } else if (ha->estudantes[pos]->matricula == matricula) {
            return &(ha->estudantes[pos]->nome[0]);
        }
    }

    return NULL;
}

int main(void) {
    hash * ha = cria_hash(1000);

    estudante * e = cria_estudante("João Paulo\0", 125);
    insere_hash_end_aberto(ha, e);

    e = cria_estudante("Maggie oi\0", 1125);
    insere_hash_end_aberto(ha, e);

    char * a = busca_hash_end_aberto(ha, 1125);

    if (a != NULL) {
        printf("%s\n", a);
    } else {
        printf("Aluno não encontrado!");
    }
}