#include <iostream>
#include <vector>
#include <string>

using namespace std;

//алгоритм Нарайаны
///////////////////////////////////////////////////////////////////
int swap(int* a, int i, int j)
{
	int s = a[i];
	a[i] = a[j];
	a[j] = s;
	return 1;
}
bool NextSet(int* a, int n, int* c)
{
	int j = n - 2;
	while (j != -1 && a[j] >= a[j + 1]) j--;
	if (j == -1)
		return false; // больше перестановок нет
	int k = n - 1;
	while (a[j] >= a[k]) k--;
	*c += swap(a, j, k);
	int l = j + 1, r = n - 1; // сортируем оставшуюся часть последовательности
	while (l < r)
		*c += swap(a, l++, r--);
	return true;
}

int det(vector<vector<float>>& m)
{
	if (m.size() != m[0].size()) {
		cout << "Matrix isn't square. You are fool!";
		return -1;
	}
	int n, * a;
	n = m[0].size();
	a = new int[n];
	int determenant = 0;
	for (int i = 0; i < n; i++)
		a[i] = i;
	int count = 0;
	while (true) {
		int b = 1;//один из сумматоров 
		for (int i = 0; i < n; i++)
			b *= m[i][a[i]];
		determenant += pow(-1, count) * b;
		if (!NextSet(a, n, &count))
			break;
	}
	return determenant;
}
///////////////////////////////////////////////////////////////////

void make(vector<vector<float>>& mx) {
	cout << "Input matrix: \n";
	string line;
	getline(cin, line);
	while (line != "") {
		vector<float> l;
		string num;
		for (int i = 0; i < line.size(); i++) {
			if (line[i] == ' ')
				l.push_back(stof(num));
		}
		mx.push_back(l);
	}
}

void show(vector<vector<float>>& a) {
	for (int i = 0; i < a.size(); i++) {
		for (int j = 0; j < a[0].size(); j++)
			cout << a[i][j] << '\t' << " ";
		cout << endl;
	}
}

bool mult(vector<vector<float>>& m1, vector<vector<float>>& m2, vector<vector<float>>& r) {
	if (m1[0].size() != m2.size()) {
		cout << "Incorrect size for mult \n";
		return false;
	}
	for (int i = 0; i < m1.size(); i++) {
		vector<float> line;
		for (int j = 0; j < m2[0].size(); j++) {
			int num = 0;
			for (int k = 0; k < m2.size(); k++)
				num += m1[i][k] * m2[k][j];
			line.push_back(num);
		}
		r.push_back(line);
	}
	return true;
}

void transpose(vector<vector<float>>& m, vector<vector<float>>& mt) {
	for (int i = 0; i < m[0].size(); i++) {
		vector<float> line;
		for (int j = 0; j < m.size(); j++)
			line.push_back(m[j][i]);
		mt.push_back(line);
	}
}


void algAdition(vector<vector<float>>& a, int k, int m) {
	for (int i = 0; i < a.size(); i++) {
		if (i == k)
			for (int j = 0; j < a[0].size(); j++) {
				if (i == k && j == m)
					a[i][j] = 1;
				else
					a[i][j] = 0;
			}
		else
			a[i][m] = 0;
	}
}
void copy(vector<vector<float>>& a, vector<vector<float>>& b) {
	for (int i = 0; i < a.size(); i++) {
		vector<float> c;
		for (int j = 0; j < a[0].size(); j++) {
			c.push_back(0);
			c[j] = a[i][j];
		}
		b.push_back(c);
	}
}

void attached(vector<vector<float>>& a, vector<vector<float>>& b) {
	for (int i = 0; i < a.size(); i++) {
		vector<float> c;
		for (int j = 0; j < a[0].size(); j++) {
			vector<vector<float>> a2;
			copy(a, a2);
			algAdition(a2, i, j);
			c.push_back(int(det(a2)));
		}
		b.push_back(c);
	}
	vector<vector<float>> b2;
	transpose(b, b2);
	b = b2;
}

void inverse(vector<vector<float>>& a, vector<vector<float>>& b) {
	attached(a, b);
	cout << 1.0 / (det(a)) << "determinant";
	cout << endl;
}

void mult(vector<vector<float>>& a, float b) {
	for (int i = 0; i < a.size(); i++) {
		for (int j = 0; j < a[0].size(); j++) {
			a[i][j] *= b;
		}
	}
}
void mult(vector<float>& a, float b) {
	for (int i = 0; i < a.size(); i++) {
		a[i] *= b;
	}
}
void substraction(vector<float>& b, vector<float>& a, int i) {
	for (i; i < a.size(); i++) {
		b[i] -= a[i];
	}
}
void gauss(vector<vector<float>>& a, vector<float>& r) {
	for (int i = 0; i < a.size(); i++) {
		int j = i + 1;
		//
		while (a[i][i] == 0) {
			swap(a[i], a[j]);
			j += 1;
			if (j >= a.size())
				break;
		}
		if (a[i][i] == 0)
			continue;
		if (a[i][i] != 1) {
			mult(a[i], 1 / a[i][i]);
		}
		for (int j = i + 1; j < a.size(); j++) {
			mult(a[i], a[j][i]);
			substraction(a[j], a[i], i);
			mult(a[i], 1 / a[i][i]);
		}
		cout << endl;
		show(a);
		cout << endl;
	}
	for (int i = a.size() - 1; i >= 0; i--) {
		float x = a[i][a[i].size() - 1];
		for (int j = a[i].size() - 2; j > i; j--) {
			x -= float(a[i][j] * r[a[0].size() - 2 - j]);
		}
		r.push_back(x);
	}
	reverse(r.begin(), r.end());
}

float horner(vector<int>& a, int x) {
	vector<int> b;
	float ost;
	b.push_back(a[0]);
	for (int i = 1; i < a.size() - 1; i++) {
		b.push_back(a[i] - x * (a[i - 1]));
	}
	return a[a.size() - 1] - x * (a[a.size() - 1 - 1]);
}
void show(vector<float>& a) {
	for (int i = 0; i < a.size(); i++) {
		cout << a[i] << '\t' << " ";
	}
}
int main()
{
	/*vector<vector<vector <float>>> matrices;
	int n, m = 0;
	int count = 0;
	vector<vector<float>> it;

	vector<string> coms = { "add", "del","show *","allshow","mult * *","transpose *","inv *"};
	cout << "Welcome! That is command list:\n";
	for (int i = 0; i < coms.size(); i++) {
		cout << coms[i] << endl;
	}
	cout << "Write your command ";
	while (true) {
		string comand = "";
		getline(cin, comand);
		if (comand == "add") {
			vector<vector <float>> matrix;
			make(matrix, n, m);
			matrices.push_back(matrix);
			cout << "Add sucses\n";
		}
		else if (comand.substr(0, 3) == "del") {
			matrices.erase(matrices.begin() + int(comand[4] - '0'));
			cout << "Del sucses";
		}
		else if (comand.substr(0, 4) == "show") {
			n = ((comand[5] == '*') ? (-1) : int(comand[5] - '0'));
			if (n >= int(matrices.size()))
				cout << "\nIncorrect num\n ";
			else
				show(((n == -1) ? it : matrices[n]));
		}
		else if (comand == "allshow") {
			for (int i = 0; i < matrices.size(); i++) {
				cout << i << endl;
				show(matrices[i]);
			}
		}
		else if (comand.substr(0, 4) == "mult") {
			n = ((comand[5] == '*') ? -1 : int(comand[5] - '0'));
			m = ((comand[7] == '*') ? -1 : int(comand[7] - '0'));
			vector<vector<float>> r;
			mult(((n == -1) ? it : matrices[n]), ((m == -1) ? it : matrices[m]), r);
			it.clear();
			it = r;
			show(it);
		}
		else if (comand.substr(0, 9) == "transpose") {
			n = ((comand[10] == '*') ? -1 : int(comand[10] - '0'));
			vector<vector<float>> r;
			transpose(((n == -1) ? it : matrices[n]), r);
			it.clear();
			it = r;
			show(it);
		}
		else if (comand.substr(0,3) == "det") {
			n = ((comand[4] == '*') ? -1 : int(comand[4] - '0'));
			cout<<det(((n==-1)?it:matrices[n]));
		}
		else if (comand.substr(0, 3) == "inv") {
			n = ((comand[4] == '*') ? -1 : int(comand[4] - '0'));
			vector<vector<float>> r;
			inverse(((n == -1) ? it : matrices[n]), r);
			it.clear();
			it = r;
			show(it);
		}
		else if (comand.substr(0, 5) == "gauss") {
			n = ((comand[6] == '*') ? -1 : int(comand[6] - '0'));
			vector<float> r;
			gauss(((n == -1) ? it : matrices[n]), r);
			show(r);
		}
		else if (comand != "")
			cout << "\nIncorrect command";
	}
	*/
	vector<int>;
	make();
}
