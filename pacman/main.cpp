#include<fstream>
#include<array>
#include<stdlib.h>
#include<iostream>

class Pacman {
private:
	int m, n;
	int** Matrix;
	int fi, fj;
	int posi, posj;
	int point;
	bool check;
public:
	Pacman() {
		point = 0;
		check = false;
		std::ifstream file;
		file.open("map1.txt");
		file >> m >> n;
		Matrix = new int*[m];
		for (int i = 0; i < m; i++) {
			Matrix[i] = new int[n];
			for (int j = 0; j < n; j++) {
				file >> Matrix[i][j];
				std::cout << Matrix[i][j];
			}
			std::cout << std::endl;
		}
		std::cout << std::endl;
		file >> posi >> posj;
		file.close();
	}
	~Pacman() {
		for (int i = 0; i < m; i++) {
			delete[] Matrix[i];
		}
		delete[]Matrix;
	}
	void Output() {
		std::cout << "point = " << point << std::endl;
		for (int i = 0; i < m; i++) {
			for (int j = 0; j < n; j++) {
				std::cout << Matrix[i][j];
			}
			std::cout << std::endl;
		}
		std::cout << std::endl;
	}

	void remap() {
		int **map = Matrix;
		for (int i = 0; i < m; i++)
			for (int j = 0; j < n; j++)
				if (Matrix[i][j] == -1) Matrix[i][j] = 0;
	}

	void level1() {
		int nQ = 0, l = 0;
		int *Qi, *Qj, *Qk, path[11];
		int Q = m * n;
		Qi = new int[Q];
		Qj = new int[Q];
		Qk = new int[Q];
		Qi[nQ++] = posi;
		Qj[nQ - 1] = posj;
		Qk[nQ - 1] = 0;
		int count = 0;
		Matrix[posi][posj] = -1;
		while (Matrix[Qi[count]][Qj[count]] != 2) {
			if ((Matrix[Qi[count] - 1][Qj[count]] == 0) || (Matrix[Qi[count] - 1][Qj[count]] == 2)) {
				Qi[nQ++] = Qi[count] - 1;
				Qj[nQ - 1] = Qj[count];
				Qk[nQ - 1] = count;
				if (Matrix[Qi[count] - 1][Qj[count]] == 0) Matrix[Qi[count] - 1][Qj[count]] = -1;
			}
			if ((Matrix[Qi[count] + 1][Qj[count]] == 0) || (Matrix[Qi[count] + 1][Qj[count]] == 2)) {
				Qi[nQ++] = Qi[count] + 1;
				Qj[nQ - 1] = Qj[count];
				Qk[nQ - 1] = count;
				if (Matrix[Qi[count] + 1][Qj[count]] == 0) Matrix[Qi[count] + 1][Qj[count]] = -1;
			}
			if ((Matrix[Qi[count]][Qj[count] - 1] == 0) || (Matrix[Qi[count]][Qj[count] - 1] == 2)) {
				Qi[nQ++] = Qi[count];
				Qj[nQ - 1] = Qj[count] - 1;
				Qk[nQ - 1] = count;
				if (Matrix[Qi[count]][Qj[count] - 1] == 0) Matrix[Qi[count]][Qj[count] - 1] = -1;
			}
			if ((Matrix[Qi[count]][Qj[count] + 1] == 0) || (Matrix[Qi[count]][Qj[count] + 1] == 2)) {
				Qi[nQ++] = Qi[count];
				Qj[nQ - 1] = Qj[count] + 1;
				Qk[nQ - 1] = count;
				if (Matrix[Qi[count]][Qj[count] + 1] == 0)	Matrix[Qi[count]][Qj[count] + 1] = -1;
			}
			count++;
		}
		remap();
		while (count != 0) {
			l++;
			if (l > 10) {
				std::cout << "GAME OVER" << std::endl;
				delete[]Qi;
				delete[]Qj;
				delete[]Qk;
				return;
			}
			path[l - 1] = count;
			count = Qk[count];
		}
		path[l] = 0;
		for (; l > 0; l--) {
			Matrix[Qi[path[l - 1]]][Qj[path[l - 1]]] = 4;
			Matrix[Qi[path[l]]][Qj[path[l]]] = 0;
			point++;
			Output();
		}
		delete[]Qi;
		delete[]Qj;
		delete[]Qk;
	}
	void level2() {
		int nQ = 0, l = 0;
		int *Qi, *Qj, *Qk, path[11];
		int Q = m * n;
		Qi = new int[Q];
		Qj = new int[Q];
		Qk = new int[Q];
		Qi[nQ++] = posi;
		Qj[nQ - 1] = posj;
		Qk[nQ - 1] = 0;
		int count = 0;
		Matrix[posi][posj] = -1;
		while (Matrix[Qi[count]][Qj[count]] != 2) {
			if ((Matrix[Qi[count] - 1][Qj[count]] == 0) || (Matrix[Qi[count] - 1][Qj[count]] == 2)) {
				Qi[nQ++] = Qi[count] - 1;
				Qj[nQ - 1] = Qj[count];
				Qk[nQ - 1] = count;
				if (Matrix[Qi[count] - 1][Qj[count]] == 0) Matrix[Qi[count] - 1][Qj[count]] = -1;
			}
			if ((Matrix[Qi[count] + 1][Qj[count]] == 0) || (Matrix[Qi[count] + 1][Qj[count]] == 2)) {
				Qi[nQ++] = Qi[count] + 1;
				Qj[nQ - 1] = Qj[count];
				Qk[nQ - 1] = count;
				if (Matrix[Qi[count] + 1][Qj[count]] == 0) Matrix[Qi[count] + 1][Qj[count]] = -1;
			}
			if ((Matrix[Qi[count]][Qj[count] - 1] == 0) || (Matrix[Qi[count]][Qj[count] - 1] == 2)) {
				Qi[nQ++] = Qi[count];
				Qj[nQ - 1] = Qj[count] - 1;
				Qk[nQ - 1] = count;
				if (Matrix[Qi[count]][Qj[count] - 1] == 0) Matrix[Qi[count]][Qj[count] - 1] = -1;
			}
			if ((Matrix[Qi[count]][Qj[count] + 1] == 0) || (Matrix[Qi[count]][Qj[count] + 1] == 2)) {
				Qi[nQ++] = Qi[count];
				Qj[nQ - 1] = Qj[count] + 1;
				Qk[nQ - 1] = count;
				if (Matrix[Qi[count]][Qj[count] + 1] == 0)	Matrix[Qi[count]][Qj[count] + 1] = -1;
			}
			count++;
		}
		remap();
		while (count != 0) {
			l++;
			if (l > 10) {
				std::cout << "GAME OVER" << std::endl;
				delete[]Qi;
				delete[]Qj;
				delete[]Qk;
				return;
			}
			path[l - 1] = count;
			count = Qk[count];
		}
		path[l] = 0;
		for (; l > 0; l--) {
			Matrix[Qi[path[l - 1]]][Qj[path[l - 1]]] = 4;
			Matrix[Qi[path[l]]][Qj[path[l]]] = 0;
			point--;
			Output();
		}
		point += 10;
		std::cout << "GAME OVER" << std::endl;
		delete[]Qi;
		delete[]Qj;
		delete[]Qk;
	}
	int countPredict(int **matrix3, int posi_, int posj_) {
		int c = 0;
		if (((matrix3[posi_ - 1][posj_]) == 0) && ((Matrix[posi_ - 1][posj_]) == 2)) {
			c += 10;
			matrix3[posi_ - 1][posj_] = 1;
		}
		if (((matrix3[posi_ + 1][posj_]) == 0) && ((Matrix[posi_ + 1][posj_]) == 2)) {
			c += 10;
			matrix3[posi_ + 1][posj_] = 1;
		}
		if (((matrix3[posi_][posj_ - 1]) == 0) && ((Matrix[posi_][posj_ - 1]) == 2)) {
			c += 10;
			matrix3[posi_][posj_ - 1] = 1;
		}
		if (((matrix3[posi_][posj_ + 1]) == 0) && ((Matrix[posi_][posj_ + 1]) == 2)) {
			c += 10;
			matrix3[posi_][posj_ + 1] = 1;
		}
		return c;
	}

	void algo3(int** matrix3, int posi_, int posj_, int &predict, int &highscore, int back) {
		Matrix[posi_][posj_] = 4;
		Output();
		int c = countPredict(matrix3, posi_, posj_);
		if (c > 10) back = 1;
		predict += c;
		if ((point + predict) > highscore) {
			if (((Matrix[posi_ - 1][posj_]) == 2) && (!check)) {
				Matrix[posi_][posj_] = 0;
				point += 9;
				if (point > highscore) highscore = point;
				predict -= 10;
				back++;
				algo3(matrix3, posi_ - 1, posj_, predict, highscore, back);
				if (!check) {
					Matrix[posi_][posj_] = 4;
					Output();
				}
			}
			if (((Matrix[posi_ + 1][posj_]) == 2) && (!check)) {
				Matrix[posi_][posj_] = 0;
				point += 9;
				if (point > highscore) highscore = point;
				predict-=10;
				back++;
				algo3(matrix3, posi_ + 1, posj_, predict, highscore, back);
				if (!check) {
					Matrix[posi_][posj_] = 4;
					Output();
				}
			}
			if (((Matrix[posi_][posj_ - 1]) == 2) && (!check)) {
				Matrix[posi_][posj_] = 0;
				point += 9;
				if (point > highscore) highscore = point;
				predict-=10;
				back++;
				algo3(matrix3, posi_, posj_ - 1, predict, highscore, back);
				if (!check) {
					Matrix[posi_][posj_] = 4;
					Output();
				}
			}
			if (((Matrix[posi_][posj_ + 1]) == 2) && (!check)) {
				Matrix[posi_][posj_] = 0;
				point += 9;
				if (point > highscore) highscore = point;
				predict-=10;
				back++;
				algo3(matrix3, posi_, posj_ + 1, predict, highscore, back);
				if (!check) {
					Matrix[posi_][posj_] = 4;
					Output();
				}
			}
		}
		if ((back >= predict) || (check)) {
			check = true;
			return;
		}
		point--;
		predict--;
		Matrix[posi_][posj_] = 0;
	}
	void level3() {
		int **matrix3;
		matrix3 = new int*[m];
		for (int i = 0; i < m; i++) {
			matrix3[i] = new int[n];
			for (int j = 0; j < n; j++) {
				matrix3[i][j] = 0;
			}
		}
		int predict = 0, highscore = 0, back = 0;
		algo3(matrix3, posi, posj, predict, highscore, 0);
		for (int i = 0; i < m; i++) {
			delete[]matrix3[i];
		}
		delete[]matrix3;
		std::cout << "GAME OVER" << std::endl;
	}
};

int main() {
	Pacman pacman;
	pacman.level3();
}