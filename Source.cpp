#include <iostream>
using namespace std;

void nhapArr(int a[], int &n)
{
	cout << "Nhap n: ";
	cin >> n;
	cout << "Nhap danh sach: ";
	for (int i = 0; i < n; i++)
		cin >> a[i];
}

void xuatArr(int a[], int n)
{
	for (int i = 0; i < n; i++)
		cout << a[i] << " ";
	cout << endl;
}

void xoa(int a[], int& n, int vt)
{
	if (vt >= 0 && vt < n) {
		for (int i = vt; i < n - 1; i++)
			a[i] = a[i + 1];
		n--;
	}
}

void them(int a[], int &n, int x, int vt)
{
	if (vt == n) {
		n++;
		a[vt] = x;
	}
	else if (vt >= 0 && vt < n) {
		n++;
		for (int i = n - 1; i > vt; i--)
			a[i] = a[i - 1];
		a[vt] = x;
	}
}
//chen mot phan tu vao danh sach co thu tu
void chenPhanTu(int a[], int& n, int x)
{
	if (x < a[0])
		them(a, n, x, 0);
	else if (x > a[n - 1])
		them(a, n, x, n);
	else {
		for (int i = 0; i < n - 1; i++) {
			if (a[i] < x && x < a[i + 1]) {
				them(a, n, x, i + 1);
				return;
			}
		}
	}
}
int main()
{
	int a[100], n, x;
	nhapArr(a, n);
	xuatArr(a, n);
	chenPhanTu(a, n, 10);
	chenPhanTu(a, n, 60);
	chenPhanTu(a, n, 40);
	cout << "Danh sach sau khi them: ";
	xuatArr(a, n);
	system("pause");
	return 0;
}