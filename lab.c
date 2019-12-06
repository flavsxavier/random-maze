#include <stdio.h>
#include <stdlib.h>
#include <time.h>

/**
 * Função: startLab(caractere: matriz, inteiro: linha inicial, inteiro: linha final, inteiro: coluna inicial, inteiro: coluna final)
 * Preenche o labirinto de forma recursiva.
*/
void carveLab(char **mtz, int m0, int m, int n0, int n) {
  if ((m - m0 != 2) && (n - n0 != 2)) {
    if ((m - m0) > (n - n0)) {
      int i, pos = (m + m0) / 2;

      // Corrige a posição da linha
      if (pos % 2 == 1) {
        pos++;
      }

      // Traça a linha
      for (i = n0; i <= n; i++) {
        if (i % 2 == 0) {
          mtz[pos][i] = '+';
        }
        if (i % 2 == 1) {
          mtz[pos][i] = '-';
        }
      }

      // Faz a abertura
      int aber;
      do {
        aber = rand() % n;
      } while (aber <= n0 || aber % 2 == 0);
      mtz[pos][aber] = ' ';
      carveLab(mtz, m0, pos, n0, n);
      carveLab(mtz, pos, m, n0, n);
    } else {
      int i, pos = (n + n0) / 2;

      // Corrige a posição da coluna
      if (pos % 2 == 1) {
        pos++;
      }

      // Traça a coluna
      for (i = m0; i <= m; i++) {
        if (i % 2 == 0) {
          mtz[i][pos] = '+';
        }
        if (i % 2 == 1) {
          mtz[i][pos] = '|';
        }
      }

      // Faz a abertura
      int aber;
      do {
        aber = rand() % m;
      } while (aber <= m0 || aber % 2 == 0);
      mtz[aber][pos] = ' ';
      carveLab(mtz, m0, m, n0, pos);
      carveLab(mtz, m0, m, pos, n);
    }
  }
}

/**
 * Função: startLab(caractere: matriz, inteiro: linha inicial, inteiro: linha final, inteiro: coluna inicial, inteiro: coluna final)
 * Inicia o labirinto com uma cruz e chama a função de preenchimento do labirinto.
*/
void startLab(char **mtz, int m0, int m, int n0, int n) {
  int i, j, p = ((m + m0) / 2), q = ((n + n0) / 2);
    
  // Corrige a posição das paredes
  if (p % 2 == 1) {
    p++;
  }
  if (q % 2 == 1) {
    q++;
  }

  // Traçar as linhas
  for (i = m0; i <= m; i++) {
    for (j = n0; j <= n; j++) {
      // Cria a linha
      if (j % 2 == 0) {
        mtz[p][j] = '+';
      }
      if (j % 2 == 1) {
        mtz[p][j] = '-';
      }
      
      // Cria a coluna
      if (i % 2 == 0) {
        mtz[i][q] = '+';
      }
      if (i % 2 == 1) {
        mtz[i][q] = '|';
      }
    }
  }
  
  // Declara um vetor auxiliar e a variável contendo a linha
  int aux[3], linha, pos;
  
  // Preenche o vetor auxiliar
  for (i = 0; i < 3; i++) {
    aux[i] = 4;
  }
  
  // Defini as linhas e cria as aberturas
  for (i = 0; i < 3; i++) {
    // Defini qual a linha
    linha = rand() % 4;
    
    // Verifica se a linha já foi escolhida anteriormente
    while (linha == aux[0] || linha == aux[1] || linha == aux[2]) {
      linha = rand() % 4;
    }
    aux[i] = linha;
    
    // Faz a abertura
    switch (linha) {
      case 0:
        while (pos <= m0 || pos > p) {
          pos = rand() % p;
        }
        if (pos % 2 == 0) {
          pos++;
        }
        mtz[pos][q] = ' ';
        break;
      case 1:
        while (pos <= q) {
          pos = rand() % n;
        }
        if (pos % 2 == 0) {
          pos++;
        }
        mtz[p][pos] = ' ';
        break;
      case 2:
        while (pos <= p) {
          pos = rand() % m;
        }
        if (pos % 2 == 0) {
          pos++;
        }
        mtz[pos][q] = ' ';
        break;
      case 3:
        while (pos <= n0 || pos > q) {
          pos = rand() % q;
        }
        if (pos % 2 == 0) {
          pos++;
        }
        mtz[p][pos] = ' ';
        break;
    }
  }

  // Preenchendo matriz
  carveLab(mtz, m0, p, n0, q);
  carveLab(mtz, m0, p, q, n);
  carveLab(mtz, p, m, n0, q);
  carveLab(mtz, p, m, q, n);

  // Imprimindo status
  puts("[50%]  Labirinto criado e preenchido.");
}

/**
 * Função: generateLab(inteiro: linhas, inteiro: colunas)
 * Gera a estrutura a inicial (paredes do labirinto).
*/
char** generateLab(int m, int n) {
	int i, j;

	// Cria a matriz e preenche com espaço vazio
	char **mtz = (char**) malloc(m * sizeof(char*));
	for (i = 0; i < m; i++) {
		mtz[i] = (char*) malloc(n * sizeof(char));
    for (j = 0; j < n; j++) {
      mtz[i][j] = ' ';
    }
	}

	// Cria a parede da 1° e da última linha
	for (i = 0; i < m; i++) {
		for (j = 0; j < n; j++) {
			// Cria a parede da 1° linha
      if (i == 0 && (j % 2 == 0)) {
        mtz[0][j] = '+';
      }
      if (i == 0 && (j % 2 == 1)) {
        mtz[0][j] = '-';
      }

      // Cria a parede da última linha
      if (i == (m - 1) && (j % 2 == 0)) {
        mtz[i][j] = '+';
      }
      if (i == (m - 1) && (j % 2 == 1)) {
        mtz[i][j] = '-';
      }
		}
	}

  // Cria a parede da 1° e da última coluna
	for (j = 0; j < n; j++) {
		for (i = 0; i < m; i++) {
			// Cria a parede da 1° coluna
      if (j == 0 && i % 2 == 0) {
        mtz[i][0] = '+';
      }
      if (j == 0 && i % 2 == 1) {
        mtz[i][0] = '|';
      }

      // Cria a parede da última coluna
      if (j == (n - 1) && i % 2 == 0) {
        mtz[i][j] = '+';
      }
      if (j == (n - 1) && i % 2 == 1) {
        mtz[i][j] = '|';
      }

      // Cria o começo e o fim do labirinto
      mtz[1][0] = ' ';
      mtz[m - 2][n - 1] = ' ';
		}
	}
	
  // Exibe o status
  puts("[25%]  Criando labirinto...");

	// Retorna o labirinto
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
 * Função: arqLab(caractere: matriz, inteiro: linhas, inteiro: colunas)
 * Arquiva o labirinto completo.
*/
void arqLab(char **mtz, int m, int n) {
  int i, j;
  FILE *arq = fopen("lab.txt", "w");
  if (arq == NULL) {
    puts("[Erro] Não foi possível armazenar o labirinto.");
    exit(1);
  }
  for (i = 0; i < m; i++) {
    for (j = 0; j < n; j++) {
      fprintf(arq, "%c", mtz[i][j]);
    }
    fprintf(arq, "\n");
  }
  fclose(arq);
  puts("[75%]  Labirinto arquivado em \'lab.txt\'.");
}

/**
 * Função: arqTamLab(inteiro: linhas, inteiro: colunas)
 * Arquiva o tamanho do labirinto.
*/
void arqTamLab(int m, int n) {
  FILE *arq = fopen("tamLab.txt", "w");
  if (arq == NULL) {
    puts("Erro: não foi possível armazenar o tamanho do labirinto.");
    exit(1);
  }
  fprintf(arq, "%d %d\n", m, n);
  fclose(arq);
  puts("[100%] Tamanho do labirinto arquivado em \'tamLab.txt\'.");
}


int main() {
  srand(time(NULL));
	int alt, larg, i, j;
	char** lab;
  do {
    printf("Informe o tamanho do labirinto (altura mínima: 10) (largura mínima: 10): ");
	  scanf("%d %d", &alt, &larg);
  } while (alt < 10 || larg < 10);
	alt = (alt * 2) + 1; larg = (larg * 2) + 1;
	lab = generateLab(alt, larg);
  startLab(lab, 0, (alt - 1), 0, (larg - 1));
  arqLab(lab, alt, larg);
  arqTamLab(alt, larg);
	// printLab(lab, alt, larg);
  free(lab);
	return 0;
}