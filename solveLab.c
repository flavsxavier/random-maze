#include <stdio.h>
#include <stdlib.h>

/**
 * Função: loadLab(caractere: matriz, inteiro: linhas, inteiro: colunas)
 * Carrega o labirinto do arquivo.
*/
void loadLab(char **mtz, int m, int n) {
  int i, j;

  // Exibe o status
  puts("[25%]  Carregando labirinto...");

  // Carrega a matriz arquivada
  FILE *arq = fopen("lab.txt", "r");
  char arqTemp;
  for (i = 0; i < m; i++) {
    for (j = 0; j <= n; j++) {
      arqTemp = fgetc(arq);
      if (arqTemp == '+') {
        mtz[i][j] = '+';
      } else if (arqTemp == '-') {
        mtz[i][j] = '-';
      } else if (arqTemp == '|') {
        mtz[i][j] = '|';
      } else {
        mtz[i][j] = ' ';
      }
    }
  }
  fclose(arq);

  // Exibe o status
  puts("[50%]  Labirinto carregado.");
}

/**
 * Função: solveLab(caractere: matriz, inteiro: linhas, inteiro: colunas)
 * Resolve o labirinto.
*/
char** solveLab(char **mtz, int m, int n, int i, int j) {
  mtz[1][0] = '#';
  if (i != m - 2 || j != n - 1) {
    mtz[i][j] = '#';
    if (mtz[i + 1][j] == ' ') {
      i++;
    } else if (mtz[i][j + 1] == ' ') {
      j++;
    } else if (mtz[i - 1][j] == ' '){
      i--;
    } else if (mtz[i][ j - 1] == ' '){
      j--;
    } else {
      mtz[i][j] = '\\';
      if (mtz[i + 1][j] == '#'){
        i++;
      } else if (mtz[i][j + 1] == '#'){
        j++;
      } else if (mtz[i - 1][j] == '#'){
        i--;
      } else if (mtz[i][j - 1] == '#'){
        j--;
      }
    }
    return solveLab(mtz, m, n, i, j);
  }
  mtz[i][j] = '#';
  // Exibe o status
  puts("[75%]  Labirinto resolvido.");
  return mtz;
}

/**
 * Função: generateMtz(inteiro: linhas, inteiro: colunas)
 * Gera a matriz que armazena o labirinto.
*/
char** generateMtz(int m, int n){
  int i, j;
  
  // Cria a matriz e preenche com espaço vazio
	char **mtz = (char**) malloc(m * sizeof(char*));
	for (i = 0; i < m; i++) {
		mtz[i] = (char*) malloc(n * sizeof(char));
    for (j = 0; j < n; j++) {
      mtz[i][j] = ' ';
    }
	}
  return mtz;
}

/**
 * Função: printLab(caractere: matriz, inteiro: linhas, inteiro: colunas)
 * Imprime o labirinto completo.
*/
void printLab(char** mtz, int m, int n) {
	int i, j;

  // Percorre e imprime o labirinto
	for (i = 0; i < m; i++) {
		for (j = 0; j < n; j++) {
			printf("%c", mtz[i][j]);
		}
		puts(" ");
	}
}

/**
 * Função: solveLab(caractere: matriz, inteiro: linhas, inteiro: colunas)
 * Resolve o labirinto.
*/
void resolvedLab(char **mtz, int m, int n) {
  int i,j;

  // Arquiva o labirinto resolvido
  FILE *arq = fopen("lab.txt", "a+");
  fprintf(arq, "\n");
  for (i = 0; i < m; i++) {
    for (j = 0; j < n; j++) {
      fprintf(arq, "%c", mtz[i][j]);
    }
    fprintf(arq, "\n");
  }
  fclose(arq);

  // Exibe o status
  puts("[100%]  Labirinto adiciano ao arquivo \'lab.txt\'.");
}

int main(){
  int m, n;
  FILE *arq = fopen("tamLab.txt","r");
  fscanf(arq, "%d %d", &m, &n);
  fclose(arq);
  char **mtz = generateMtz(m, n);
  loadLab(mtz, m, n);
  mtz = solveLab(mtz, m, n, 1, 1);
  resolvedLab(mtz, m, n);
  printLab(mtz, m, n);
  free(mtz);
  return 0;
}