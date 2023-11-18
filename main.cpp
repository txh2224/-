#include <iostream>
#include <vector>
#include<time.h>
#include <algorithm>
using namespace std;

// 定义卷积函数
void show(vector<vector<int>> output)
{
	for (int i = 0; i < output.size(); i++) {
		for (int j = 0; j < output[0].size(); j++) {
			printf("%-5d", output[i][j]);
		}
		cout << endl;
	}
}
vector<vector<int>> juan(vector<vector<int>> input, vector<vector<int>> kernel)
{
	int inputrows = input.size();
	int inputcols = input[0].size();
	int kernelrows = kernel.size();
	int kernelcols = kernel[0].size();
	int outputrows = inputrows - kernelrows + 1;
	int outputcols = inputcols - kernelcols + 1;
	vector<vector<int>> output(outputrows, vector<int>(outputcols, 0));
	for (int i = 0; i < outputrows; i++) {
		for (int j = 0; j < outputcols; j++) {
			int sum = 0;
			for (int k = 0; k < kernelrows; k++) {
				for (int l = 0; l < kernelcols; l++) {
					sum += input[i + k][j + l] * kernel[k][l];
				}
			}
			output[i][j] = sum;
		}
	}
	return output;
}
int max(vector<int> a)
{
	int max = a[0];
	for (int i = 1; i < a.size(); i++){
		if (a[i] > max)max = a[i];
	}
	return max;
}
int min(int a, int b)
{
	if (a < b)return a;
	else return b;
}
vector<vector<int>> chi(vector<vector<int>> input, int a, int b)
{
	int x=0, y=0;
	int inputrows = input.size();
	int inputcols = input[0].size();
	int outputrows = inputrows / a + (inputrows%a != 0);
	int outputcols = inputcols / b + (inputcols%b != 0);
	vector<vector<int>> output(outputrows, vector<int>(outputcols, 0));
	for (int i = 0; i < inputrows; i = i + a,y++)
	{
		if (i > inputrows)y--;
		vector<int> temp;
		x = 0;
		for (int j = 0; j < inputcols; j = j + b,x++){
			if (j > inputcols)x--;
			for (int k = j; k < min(inputrows , j + b); k++){
				for (int l = i; l < min(inputcols , i + a); l++){
					temp.push_back(input[k][l]);
				}
			}
			output[x][y] = max(temp);
			temp.clear();
		}
	}
	return output;
}
int main() {
	srand((unsigned)time(NULL));
	int rows = 10;
	int cols = 10;
	vector<int> a;
	vector<vector<int>> input;
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < cols; j++) {
			a.push_back(rand() % 100);
		}
		input.push_back(a);
		a.clear();
	}
	vector<vector<int>> kernel = { {1, 0}, {0, 1} };//卷积核
	vector<vector<int>> output = juan(input, kernel);
	show(input);
	cout << "---------------" << endl;
	show(output);
	cout << "---------------" << endl;
	output = chi(output, 2, 2);
	show(output);

	return 0;
}