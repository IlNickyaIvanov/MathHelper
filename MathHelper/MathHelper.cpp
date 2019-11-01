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
		for (int i = 0; i <= line.size(); i++) {
			if ((line[i] == ' ' || i == line.size())) {
				l.push_back(stof(num));
				num = "";
			}
			else
				num += line[i];
		}
		mx.push_back(l);
	}
}
void make(vector<float> &mx) {
	cout << "Input vector: \n";
	string line;
	getline(cin, line);
	string num;
	for (int i = 0; i <= line.size(); i++) {
		if ((line[i] == ' ' || i == line.size() )) {
			mx.push_back(stof(num));
			num = "";
		}
		else
			num += line[i];
	}
}

void show(vector<vector<float>>& a) {
	for (int i = 0; i < a.size(); i++) {
		for (int j = 0; j < a[i].size(); j++)
			cout << a[i][j]<< " ";
		cout << endl;
	}
}

//умножение матриц
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
//транспонирование матрицы
void transpose(vector<vector<float>>& m, vector<vector<float>>& mt) {
	for (int i = 0; i < m[0].size(); i++) {
		vector<float> line;
		for (int j = 0; j < m.size(); j++)
			line.push_back(m[j][i]);
		mt.push_back(line);
	}
}

//алгоритмическое дополнение по i j элементу
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
// матрица из дополнений
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
//обратная матрица
void inverse(vector<vector<float>>& a, vector<vector<float>>& b) {
	attached(a, b);
	cout << 1.0 / (det(a)) << "determinant";
	cout << endl;
}
//умножение матрицы на число
void mult(vector<vector<float>>& a, float b) {
	for (int i = 0; i < a.size(); i++) {
		for (int j = 0; j < a[0].size(); j++) {
			a[i][j] *= b;
		}
	}
}
//умножение vec на число
void mult(vector<float>& a, float b) {
	for (int i = 0; i < a.size(); i++) {
		a[i] *= b;
	}
}
//вычетание vec a-b i начало вычетания
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
//a = (x - x)b + ost, где a принимает значение b
float horner(vector<float> &a, float x) {
	vector<float> b;
	b.push_back(a[0]);
	float ost = 0;
	for (int i = 1; i < a.size() - 1; i++) {
		b.push_back(a[i] + x * (b[i-1]));
	}
	ost = a[a.size() - 1] + x * (b[b.size()-1]);
	if (a.size() == 1)
		a = {};
	else
		a = b;
	b.push_back(ost);
	return ost;
}
//перевод десятичной дроби < 1 в обычную дробь a/b
string convert(float num) {
	float eps = 0.000000001;
	int ch = 0;
	int zn = 0;
	int a = 1; int b = 1;
	int mn = 2; // множитель для начального приближения
	int iter = 0;
	ch = a; zn = b;
	// Поиск начального приближения
	float c = 1;
	do {
		b++;
		c = (double)a / b;
	} while ((num - c) < 0);
	if ((num - c) < eps)
	{
		ch = a; zn = b;
		return to_string(a) + "/" + to_string(b);
	}
	b--;
	c = (double)a / b;
	if ((num - c) > -eps)
	{
		ch = a; zn = b;
		return to_string(a) + "/" + to_string(b);
	}
	// Уточнение
	while (iter < 20000)
	{
		int cc = a * mn, zz = b * mn;
		iter++;
		do {
			zz++;
			c = (double)cc / zz;
		} while ((num - c) < 0);
		if ((num - c) < eps)
		{
			ch = cc; zn = zz;
			return to_string(a) + "/" + to_string(b);
		}
		zz--;
		c = (double)cc / zz;
		if ((num - c) > -eps)
		{
			ch = cc; zn = zz;
			return to_string(a) + "/" + to_string(b);
		}
		mn++;
	}
	return to_string(a) + "/" +to_string(b);
}

//полином корень остатки в процессе деления процесс деления
void allHorner(vector<float> &a,float b, vector <float>&osts,vector<vector<float>> &res) {
	
	while (a.size() > 0) {
		res.push_back(a);
		if (osts.size() > 0)
			res[res.size() - 1].push_back(osts[osts.size() - 1]);
		if(a.size()==1)
			res.push_back(a);
		osts.push_back(horner(a, b));		
	}
}

void show(vector<float>& a) {
	for (int i = 0; i < a.size(); i++) {
		cout << a[i] << " ";
	}
	cout << endl;
}
float stPDevision(vector<float> &a, vector<float> &b) {
	float quotient = a[0] / b[0];
	mult(b,quotient);
	substraction(a, b,0);
	while (a.size() > 0 && a[0] == 0)
		a.erase(a.begin()+0);
	return quotient;
}
//делимое делитель процесс результат
void pDevision(vector<float> a, vector<float> b, vector<vector<float>>& div, vector<float>& res) {
	for (int i = 0; i <= a.size() - b.size(); i++) {
		res.push_back(0);
	}
	while (a.size() >= b.size()) {
		int c = (a.size() - b.size() + 1);
		res[res.size() - c] = stPDevision(a, b);
		div.push_back(b);
		if (a.size() == 0)
			div.push_back({ 0 });
		else
			div.push_back(a);
		mult(b, 1 / res[res.size() - c]);
	}
}
//делитель делимое результат остаток
void pDevision( vector<float> a, vector<float> b, vector<float> &res, vector<float> &remainder) {
	for (int i = 0; i <= a.size() - b.size(); i++) {
		res.push_back(0);
	}
	while (a.size() >= b.size()) {
		int c = (a.size() - b.size() + 1);
		res[res.size() - c] = stPDevision(a, b);
	}
	if (a.size() > 0)
		remainder = a;
	else
		remainder = { 0 };
}
void NOD(vector<float> a, vector<float> b, vector<vector<float>>&res, vector<float> &nod) {
	vector<float>remainder1 = a;
	vector<float>remainder2 = b;
	while (remainder1.size() > 1 && remainder2.size() > 1) {
		vector<float> r;
		if (remainder1.size() >= remainder2.size()) {
			pDevision(remainder1, remainder2, r, remainder1);
		}
		else {
			pDevision(remainder2, remainder1, r, remainder2);
		}
		res.push_back(r);
	}
	if (remainder1.size() == 1)
		nod = remainder2;
	else
		nod = remainder1;
}
int main()
{
	vector<vector<vector <float>>> matrices;
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
			make(matrix);
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
		else if(comand.substr(0, 6) == "horner"){
			vector<float> osts;
			vector<vector<float>> devision;
			vector<float> polinom;
			make(polinom);
			float b; cout << "Input divider "; cin >> b; cout << endl;
			allHorner(polinom, b, osts, devision); cout << endl;
			cout << "Horner"; cout << endl;
			show(devision);
		}
		else if (comand.substr(0, 3) == "div") {
			vector<float> a; make(a);
			vector<float> b; make(b);
			vector<vector<float>> div;
			vector<float> res;
			pDevision(a, b, div, res);
			cout << "Res" << endl;
			show(res);
			cout << "Proc"<< endl;
			show(div);
		}
		else if (comand.substr(0, 3) == "nod") {
			vector<float> a; make(a);
			vector<float> b; make(b);
			vector<vector<float>> res;
			vector<float> nod;
			NOD(a, b, res, nod);
			show(res);
			show(nod);
		}
		else if (comand != "")
			cout << "\nIncorrect command";
	}
	
}
