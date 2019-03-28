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
		file.open("input.txt");
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

	void remap() { //clean the footprint
		for (int i = 0; i < m; i++)
			for (int j = 0; j < n; j++)
				if (Matrix[i][j] == -1) Matrix[i][j] = 0;
	}

	void level1() {
		int nQ = 0, l = 0;
		int *Qi, *Qj, *Qk, path[11];
		int Q = m * n;
		Qi = new int[Q]; //Queue store the coordinates x (row m)
		Qj = new int[Q]; //Queue store the coordinates y (column n)
		Qk = new int[Q]; //Queue store the 
		Qi[nQ++] = posi;
		Qj[nQ - 1] = posj;
		Qk[nQ - 1] = 0;
		int count = 0;
		Matrix[posi][posj] = -1;

		//Check if a tile are adjacent pacman
		while (Matrix[Qi[count]][Qj[count]] != 2) {

			//check if there is an empty path or a food
			if ((Matrix[Qi[count] - 1][Qj[count]] == 0) || (Matrix[Qi[count] - 1][Qj[count]] == 2)) {
				//store it into a queue
				Qi[nQ++] = Qi[count] - 1;
				Qj[nQ - 1] = Qj[count];
				Qk[nQ - 1] = count;
				if (Matrix[Qi[count] - 1][Qj[count]] == 0) Matrix[Qi[count] - 1][Qj[count]] = -1;
			}

			//check if there is an empty path or a food
			if ((Matrix[Qi[count] + 1][Qj[count]] == 0) || (Matrix[Qi[count] + 1][Qj[count]] == 2)) {
				//store it into a queue
				Qi[nQ++] = Qi[count] + 1;
				Qj[nQ - 1] = Qj[count];
				Qk[nQ - 1] = count;
				if (Matrix[Qi[count] + 1][Qj[count]] == 0) Matrix[Qi[count] + 1][Qj[count]] = -1;
			}

			//check if there is an empty path or a food
			if ((Matrix[Qi[count]][Qj[count] - 1] == 0) || (Matrix[Qi[count]][Qj[count] - 1] == 2)) {
				//store it into a queue
				Qi[nQ++] = Qi[count];
				Qj[nQ - 1] = Qj[count] - 1;
				Qk[nQ - 1] = count;
				if (Matrix[Qi[count]][Qj[count] - 1] == 0) Matrix[Qi[count]][Qj[count] - 1] = -1;
			}

			//check if there is an empty path or a food
			if ((Matrix[Qi[count]][Qj[count] + 1] == 0) || (Matrix[Qi[count]][Qj[count] + 1] == 2)) {
				//store it into a queue
				Qi[nQ++] = Qi[count];
				Qj[nQ - 1] = Qj[count] + 1;
				Qk[nQ - 1] = count;
				if (Matrix[Qi[count]][Qj[count] + 1] == 0)	Matrix[Qi[count]][Qj[count] + 1] = -1;
			}
			count++; //position of queue
		}
		remap();
		while (count != 0) {
			l++;
			if (l > 10) { //if the path is longer than 10 then GAME OVER
				std::cout << "GAME OVER" << std::endl;
				delete[]Qi;
				delete[]Qj;
				delete[]Qk;
				return;
			}

			//return the shortest path
			path[l - 1] = count;
			count = Qk[count];
		}
		path[l] = 0;

		//print out the path
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

		//Check if a tile are adjacent pacman
		while (Matrix[Qi[count]][Qj[count]] != 2) {

			//check if there is an empty path or a food			
			if ((Matrix[Qi[count] - 1][Qj[count]] == 0) || (Matrix[Qi[count] - 1][Qj[count]] == 2)) {
				Qi[nQ++] = Qi[count] - 1;
				Qj[nQ - 1] = Qj[count];
				Qk[nQ - 1] = count;
				if (Matrix[Qi[count] - 1][Qj[count]] == 0) Matrix[Qi[count] - 1][Qj[count]] = -1;
			}

			//check if there is an empty path or a food			
			if ((Matrix[Qi[count] + 1][Qj[count]] == 0) || (Matrix[Qi[count] + 1][Qj[count]] == 2)) {
				Qi[nQ++] = Qi[count] + 1;
				Qj[nQ - 1] = Qj[count];
				Qk[nQ - 1] = count;
				if (Matrix[Qi[count] + 1][Qj[count]] == 0) Matrix[Qi[count] + 1][Qj[count]] = -1;
			}

			//check if there is an empty path or a food			
			if ((Matrix[Qi[count]][Qj[count] - 1] == 0) || (Matrix[Qi[count]][Qj[count] - 1] == 2)) {
				Qi[nQ++] = Qi[count];
				Qj[nQ - 1] = Qj[count] - 1;
				Qk[nQ - 1] = count;
				if (Matrix[Qi[count]][Qj[count] - 1] == 0) Matrix[Qi[count]][Qj[count] - 1] = -1;
			}

			//check if there is an empty path or a food			
			if ((Matrix[Qi[count]][Qj[count] + 1] == 0) || (Matrix[Qi[count]][Qj[count] + 1] == 2)) {
				Qi[nQ++] = Qi[count];
				Qj[nQ - 1] = Qj[count] + 1;
				Qk[nQ - 1] = count;
				if (Matrix[Qi[count]][Qj[count] + 1] == 0)	Matrix[Qi[count]][Qj[count] + 1] = -1;
			}
			count++; //position of queue
		}
		remap(); //clean footprint
		while (count != 0) {
			l++;
			if (l > 10) { //if the path is longer than 10 then GAME OVER
				std::cout << "GAME OVER" << std::endl;
				delete[]Qi;
				delete[]Qj;
				delete[]Qk;
				return;
			}

			//return the shortest path
			path[l - 1] = count;
			count = Qk[count];
		}
		path[l] = 0;

		//print out the path
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

	int countPredict(int **matrix3, int posi_, int posj_) { //count the point earned by food(s)
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
		predict += c; //predict the point pacman has not collected yet

		if ((point + predict) > highscore) {
			if (((Matrix[posi_ - 1][posj_]) == 2) && (!check)) { //if the top adjacent tile is a food then pacman move
				Matrix[posi_][posj_] = 0;
				point += 9; //point earned 10 by collecting food and lose 1 point by moving 1 step
				if (point > highscore) highscore = point;
				predict -= 10; //if pacman collect a food, the predict lose 10 point
				back++; //distance from the closest discovered food to pacman
				algo3(matrix3, posi_ - 1, posj_, predict, highscore, back); 
				if (!check) { //comeback
					Matrix[posi_][posj_] = 4;
					Output();
				}
			}
			if (((Matrix[posi_ + 1][posj_]) == 2) && (!check)) { //if the bottom adjacent tile is a food then pacman move
				Matrix[posi_][posj_] = 0;
				point += 9; //point earned 10 by collecting food and lose 1 point by moving 1 step
				if (point > highscore) highscore = point;
				predict-=10; //if pacman collect a food, the predict lose 10 point
				back++; //distance from the closest discovered food to pacman
				algo3(matrix3, posi_ + 1, posj_, predict, highscore, back);
				if (!check) { //comeback
					Matrix[posi_][posj_] = 4;
					Output();
				}
			}
			if (((Matrix[posi_][posj_ - 1]) == 2) && (!check)) { ////if the left adjacent tile is a food then pacman move
				Matrix[posi_][posj_] = 0;
				point += 9; //point earned 10 by collecting food and lose 1 point by moving 1 step
				if (point > highscore) highscore = point;
				predict-=10; //if pacman collect a food, the predict lose 10 point
				back++; //distance from the closest discovered food to pacman
				algo3(matrix3, posi_, posj_ - 1, predict, highscore, back);
				if (!check) { //comeback
					Matrix[posi_][posj_] = 4;
					Output();
				}
			}
			if (((Matrix[posi_][posj_ + 1]) == 2) && (!check)) { //if the right adjacent tile is a food then pacman move
				Matrix[posi_][posj_] = 0;
				point += 9; //point earned 10 by collecting food and lose 1 point by moving 1 step
				if (point > highscore) highscore = point;
				predict-=10; //if pacman collect a food, the predict lose 10 point
				back++; //distance from the closest discovered food to pacman
				algo3(matrix3, posi_, posj_ + 1, predict, highscore, back);
				if (!check) { //comeback
					Matrix[posi_][posj_] = 4;
					Output();
				}
			}
		}
		if ((back >= predict) || (check)) { //if the distance from the closest discovered food to pacman is greater
			check = true;					//than the predict point can collect by going back then stop the game
			return;
		}
		point--; //every comeback step reduces 1 point
		predict--; //every step makes the point earned by collecting food -1 (You move 3 step to collect food, you can only earn 7 point)
		Matrix[posi_][posj_] = 0;
	}
	void level3() {
		int **matrix3; //this matrix declare to check if a food is discovered.
		matrix3 = new int*[m];
		for (int i = 0; i < m; i++) {
			matrix3[i] = new int[n];
			for (int j = 0; j < n; j++) {
				matrix3[i][j] = 0;
			}
		}
		int predict = 0; //predict point can be earned by discovering food(s)
		int highscore = 0; //highest score at the momment
		int back = 0; // distance from the closest discovered food to pacman

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