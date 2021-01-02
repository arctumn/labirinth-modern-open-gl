#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <chrono>
#include <thread>
#define sized 5
#define pd 5 // Probabilidade de manter a direção
#define pb 4 // probabilidade de criar um branch
#define GREEN     "\033[32m"      /* Red */
#define GREENEND  "\033[0m"


//       1              <- CIMA
//     0   2            <- ESQUERDA E DIREITA
//       3              <- BAIXO

void VerGrelha(int a[sized][sized]) {
	int x = 0;
	while (x < 3) {
		std::cout << "\n";
		x++;
	}
	for (size_t i = 0; i < sized; i++)
	{
		std::cout << "     |";
		for (size_t j = 0; j < sized; j++)
		{
			if (a[i][j] == 0)
				std::cout << GREEN << "C|" << GREENEND;
			else if (a[i][j] == 1)
				std::cout << "O|";
			else
				std::cout << "P|";
		}
		std::cout << "\n";
	}
}

void PreencheGrelha(int(&a)[sized][sized]) {
	for (size_t i = 0; i < sized; i++)
		for (size_t j = 0; j < sized; j++)
			a[i][j] = 1;
}

int AddDirecao(int a) {
	a++;
	if (a > 3)
		a = 0;
	return a;
}

int SubDirecao(int a) {
	a--;
	if (a < 0)
		a = 3;
	return a;
}

int EscolheDirecao(int d, bool limitado) {

	if (!limitado)
		if ((rand() % 10) > pd)
			return d;

	if ((rand() % 10) < 5)
		d = AddDirecao(d);
	else
		d = SubDirecao(d);
	return d;
}

bool VerificaDirecao(int a[sized][sized], int d, int i, int j) {
	if (d == 0) {
		if (a[i][j - 1] == 0 || j - 1 == 0) {
			return true;
		}
	}
	else if (d == 1) {
		if (a[i - 1][j] == 0 || i - 1 == 0) {
			return true;
		}
	}
	else if (d == 2) {
		if (a[i][j + 1] == 0 || j + 1 == (sized - 1)) {
			return true;
		}
	}
	else if (d == 3) {
		if (a[i + 1][j] == 0 || i + 1 == (sized - 1)) {
			return true;
		}
	}
	return false;
}

bool VerificaConexao(int a[sized][sized], int d, int i, int j) {
	if (d == 0) {
		if (a[i][j - 1] == 0 || a[i][j - 2] == 0 || a[i + 1][j - 1] == 0 || a[i - 1][j - 1] == 0) {
			return true;
		}
	}
	else if (d == 1) {
		if (a[i - 1][j] == 0 || a[i - 2][j] == 0 || a[i - 1][j - 1] == 0 || a[i - 1][j + 1] == 0) {
			return true;
		}
	}
	else if (d == 2) {
		if (a[i][j + 1] == 0 || a[i][j + 2] == 0 || a[i - 1][j + 1] == 0 || a[i + 1][j + 1] == 0) {
			return true;
		}
	}
	else if (d == 3) {
		if (a[i + 1][j] == 0 || a[i + 2][j] == 0 || a[i + 1][j - 1] == 0 || a[i + 1][j + 1] == 0) {
			return true;
		}
	}
	return false;
}

void CriaCaminho(int(&a)[sized][sized], int i, int j, int d, int cont, int contd, int contb, bool branch) {
	// while (cont < sized / 2) {
	while (true) {
		// std::this_thread::sleep_for(std::chrono::milliseconds(125)); -> Activar para ver por turnos
		int dAnt = 0;
		if (contd < 1) {
			dAnt = d;
			d = EscolheDirecao(d, false);
			if (d != dAnt) {
				contd = rand() % 4 + 2;
			}
		}
		if (contb < 1) {
			if (!VerificaDirecao(a, AddDirecao(d), i, j) && !VerificaDirecao(a, SubDirecao(d), i, j)) {
				if ((rand() % 10) > 8) {
					CriaCaminho(a, i, j, SubDirecao(d), 0, 3, 3, true);
					CriaCaminho(a, i, j, AddDirecao(d), 0, 3, 3, true);
				}
				else {
					if ((rand() % 10) > 5)
						CriaCaminho(a, i, j, AddDirecao(d), 0, 3, 3, true);
					else
						CriaCaminho(a, i, j, SubDirecao(d), 0, 3, 3, true);
				}
				contb = rand() % 4 + 2;
			}
			else if (!VerificaDirecao(a, AddDirecao(d), i, j)) {
				CriaCaminho(a, i, j, AddDirecao(d), 0, 3, 3, true);
				contb = rand() % 4 + 2;
			}
			else if (!VerificaDirecao(a, SubDirecao(d), i, j)) {
				CriaCaminho(a, i, j, SubDirecao(d), 0, 3, 3, true);
				contb = rand() % 4 + 2;
			}
			//else
				//std::cout << "Não consigo criar branch.";
		}

		// Escolher Branch

		// Verifica avanço
		int cont1 = 0;
		if (branch == false) { // para o caminho principal
			while (VerificaDirecao(a, d, i, j)) {
				if (cont1 == 1) {
					d = AddDirecao(d);
					d = AddDirecao(d);
				}
				if (cont1 == 2) {
					return;
				}
				d = EscolheDirecao(d, true);
				cont1++;
			}
		} // para branches 
		else if (branch == true) {
			while (VerificaDirecao(a, d, i, j)) {
				if (cont1 == 1) {
					d == AddDirecao(d);
					d = AddDirecao(d);
				}
				if (cont1 == 2) {
					return;
				}
				d = EscolheDirecao(d, true);
				cont1++;
			}
			if (VerificaConexao(a, d, i, j)) {
				if ((rand() % 10) > 5) {
					if (!VerificaDirecao(a, AddDirecao(d), i, j) && !VerificaDirecao(a, SubDirecao(d), i, j)) {
						if ((rand() % 10) > 8) {
							CriaCaminho(a, i, j, SubDirecao(d), 0, 3, 3, true);
							CriaCaminho(a, i, j, AddDirecao(d), 0, 3, 3, true);
						}
						else {
							if ((rand() % 10) > 5)
								CriaCaminho(a, i, j, AddDirecao(d), 0, 3, 3, true);
							else
								CriaCaminho(a, i, j, SubDirecao(d), 0, 3, 3, true);
						}
					}
					else if (!VerificaDirecao(a, AddDirecao(d), i, j)) {
						CriaCaminho(a, i, j, AddDirecao(d), 0, 3, 3, true);
					}
					else if (!VerificaDirecao(a, SubDirecao(d), i, j)) {
						CriaCaminho(a, i, j, SubDirecao(d), 0, 3, 3, true);
					}
					return;
				}
				if ((rand() % 10) > 5)
					return; // <- Retirar para não ter becos
			}
		}

		// Avançar
		//std::cout << "D é igual a: %i" << d;
		if (d == 0) {
			if (VerificaConexao(a, d, i, j)) {
				a[i][j - 1] = 0;
				return;
			}
			a[i][j - 1] = 0;
			j = j - 1;
		}
		else if (d == 1) {
			if (VerificaConexao(a, d, i, j)) {
				a[i - 1][j] = 0;
				return;
			}
			a[i - 1][j] = 0;
			i = i - 1;
		}
		else if (d == 2) {
			if (VerificaConexao(a, d, i, j)) {
				a[i][j + 1] = 0;
				return;
			}
			a[i][j + 1] = 0;
			j = j + 1;
		}
		else if (d == 3) {
			if (VerificaConexao(a, d, i, j)) {
				a[i + 1][j] = 0;
				return;
			}
			a[i + 1][j] = 0;
			i = i + 1;
		}
		//VerGrelha(a); -> Activar para ver por turnos
		cont++;
		contd--;
		contb--;
	}
}

void CriaLab(int(&a)[sized][sized]) {
	int i, j = 0;
	PreencheGrelha(a);
	i = rand() % (sized - 3) + 2;
	std::cout << "%i" << i;
	j = rand() % (sized - 3) + 2;
	std::cout << "%i" << j; // Posição para o início do primeiro caminho
	// a[i][j] = 2; // para ver um starting point
	a[i][j] = 0; // para ir a caminho

	CriaCaminho(a, i, j, 0, 0, 3, 3, false);
}

int CriaEMostra() { // Esta função vai criar 1 labirinto
	int grelha[sized][sized];
	srand(time(NULL));
	
	CriaLab(grelha);

	// grelha[i][j] = 2;
	VerGrelha(grelha); // -> Imprime a grelha no ecrã
	return 0;
}
