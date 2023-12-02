#include <stdio.h>
#include <vector>
#include <string>

using namespace std;

// Função para construir a tabela de prefixo do padrão (LPS)
void construirTabelaLPS(string padrao, vector<int>& lps) {
    int len = 0; // Comprimento do prefixo atual
    int i = 1;   // Índice no padrão

    while (i < padrao.length()) {
        if (padrao[i] == padrao[len]) {
            len++;
            lps[i] = len;
            i++;
        } else {
            if (len != 0) {
                len = lps[len - 1];
            } else {
                lps[i] = 0;
                i++;
            }
        }
    }
}

// Função para realizar o casamento de padrão usando o algoritmo KMP
void kmpCasamento(string texto, string padrao) {
    int M = padrao.length();
    int N = texto.length();

    vector<int> lps(M, 0); // Tabela de prefixo do padrão (LPS)
    construirTabelaLPS(padrao, lps);

    int i = 0; // Índice no texto
    int j = 0; // Índice no padrão

    while (i < N) {
        if (padrao[j] == texto[i]) {	//padrao parcial encontrado, e incrementa
            j++;
            i++;
        }

        if (j == M) {
            printf("Padrao encontrado na posicao %d\n", i - j);
            j = lps[j - 1]; //recua para n buscar padroes repetidos
        } else if (i < N && padrao[j] != texto[i]) { //caso o padrao e o texto n conincida, e devemos continuar
            if (j != 0) {	//caso tenha alguma correspondencia parcial, mas n totoal
                j = lps[j - 1];	//retrocedemos para continuar
            } else {	// j é 0 ou seja, nenhuma correspondencia encontrada
                i++;
            }
        }
    }
}

int main() {
	//string texto = "ABCAKABCAKABCA";
    string texto = "ABCABCA";
    string padrao = "ABCA";

    printf("Ocorrencias do padrao no texto:\n");
    kmpCasamento(texto, padrao);

    return 0;
}

