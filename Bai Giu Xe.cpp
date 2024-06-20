/*CHUONG TRINH QUAN LI HE THONG BAI GIU XE
SINH VIEN: HUYNH NGOC TIEN , NGUYEN_DOAN_VAN_SONG.
LOP: DH23IT01 */

#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <fstream>
#include <string>
#include <ctime>
using namespace std;

//tạo kiểu dữ liệu "xe" để lưu trữ các thông tin của xe.
struct xe
{
	string bienso;
	time_t thgianVao;
	time_t thgianRa;
	tm*ngayGioVao;
	tm*ngayGioRa;
	int tienphaitra, vitri;
};
//tạo hai mảng 2 chiều, mỗi mảng là một bãi giữ xe.
xe baixe1[10][20];
xe baixe2[10][20];

//hàm tạo biển số ngẫu nhiên dùng để nhập xe vào bãi.
string taoBienSo()
{
	srand(time(0));
	string bienso;
	for (int i = 1; i <= 9; i++)
	{
		if (i == 3)
			bienso += '-';
		else if (i == 4)
			bienso += 'A' + rand() % 26;
		else
			bienso += '0' + rand() % 10;
	}
	return bienso;
}

//hàm tính tiền giữ xe khi biết thời gian vào và thời gian ra của 1 xe.
double tinhTienGiuXe(time_t thgianvao, time_t thgianra)
{
	double sophut = difftime(thgianra, thgianvao) / 60 - 30;
	double tien = 50000;

	if (sophut <= 0)
		tien += 0;
	else if ((sophut / 30) > int(sophut / 30))
		tien += int((sophut / 30) + 1) * 30000;
	else if ((sophut / 30) == int(sophut / 30))
		tien += int(sophut / 30) * 30000;
	return tien;
}

/*hàm tìm chỗ trống của 1 bãi xe với input là một trong hai mảng 2 chiều đã tạo,
  nếu còn chỗ trống thì cho xe vào chỗ trống đó.*/
void timChoTrong(xe baixe[10][20])
{
	bool conTrong = false;

	for (int i = 0; i <= 9; i++)
	{
		for (int j = 0; j <= 19; j++)
		{
			if (baixe[i][j].bienso == "")
			{
				baixe[i][j].bienso = taoBienSo();
				baixe[i][j].vitri = i * 20 + j + 1;
				baixe[i][j].thgianVao = time(nullptr);
				baixe[i][j].ngayGioVao = localtime(&baixe[i][j].thgianVao);
				cout << "Xe co bien so " << baixe[i][j].bienso << " da vao bai." << endl;
				conTrong = true; return;
			}
		}
	}
	if (conTrong == false)
		cout << "Bai xe nay da het cho trong!" << endl;
}

//hàm nhập xe vào 1 trong 2 bãi xe.
void nhapXe()
{
	int bx;
	do
	{
		cout << "-----------------------------------------" << endl;
		cout << "1.Bai xe 1." << endl;
		cout << "2.Bai xe 2." << endl;
		cout << "0.Tro lai MENU." << endl;
		cout << "Nhap xe vao bai nao? : ";

		while (!(cin >> bx))
		{
			cout << "Khong hop le." << endl;
			cout << "Nhap xe vao bai nao? : ";
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
		}
		cout << "-----------------------------------------" << endl;

		if (bx == 1)
			timChoTrong(baixe1);
		else if (bx == 2)
			timChoTrong(baixe2);
		else if (bx == 0) break;

		else cout << "Nhap sai." << endl; continue;

	} while (bx != 0);
}

//hàm xuất một xe ra khỏi 1 trong 2 bãi xe khi nhập biển số.
void xuatXeRaBai()
{
	string nhapbs;
	cout << "Nhap bien so xe: "; 
	cin >> nhapbs;
	bool xuatXe = false;

	for (int i = 0; i < 10; i++)
	{
		for (int j = 0; j < 20; j++)
		{
			if (baixe1[i][j].bienso == nhapbs)
			{
				baixe1[i][j].thgianRa = time(nullptr);
				baixe1[i][j].ngayGioRa = localtime(&baixe1[i][j].thgianRa);
				baixe1[i][j].tienphaitra = tinhTienGiuXe(baixe1[i][j].thgianVao, baixe1[i][j].thgianRa);
				cout << "So tien phai tra la: " << baixe1[i][j].tienphaitra << " VND." << endl;
				cout << "Xe co bien so " << nhapbs << " da ra khoi bai so 1." << endl;

				//ghi lại thông tin xe đã rời bãi 1.
				ofstream danhSach1;
				danhSach1.open("Danh Sach Cac Xe Da Roi Bai 1.txt", ios::app);
				danhSach1 <<"\n"<< baixe1[i][j].bienso <<"    "<< baixe1[i][j].vitri<<"          " 
					<< baixe1[i][j].ngayGioVao->tm_hour << ":" << baixe1[i][j].ngayGioVao->tm_min << ":" << baixe1[i][j].ngayGioVao->tm_sec << ". "
					<< baixe1[i][j].ngayGioVao->tm_mday << "/" << baixe1[i][j].ngayGioVao->tm_mon + 1 << "/" << baixe1[i][j].ngayGioVao->tm_year + 1900 
					<<"     "<< baixe1[i][j].ngayGioRa->tm_hour << ":" << baixe1[i][j].ngayGioRa->tm_min << ":" << baixe1[i][j].ngayGioRa->tm_sec << ". "
					<< baixe1[i][j].ngayGioRa->tm_mday << "/" << baixe1[i][j].ngayGioRa->tm_mon + 1 << "/" << baixe1[i][j].ngayGioRa->tm_year + 1900 
					<<"     "<< baixe1[i][j].tienphaitra << endl;
				danhSach1.close();

				baixe1[i][j].bienso = "";

				xuatXe = true; return;
			}

			else if (baixe2[i][j].bienso == nhapbs)
			{
				baixe2[i][j].thgianRa = time(nullptr);
				baixe2[i][j].ngayGioRa = localtime(&baixe2[i][j].thgianRa);
				baixe2[i][j].tienphaitra = tinhTienGiuXe(baixe2[i][j].thgianVao, baixe2[i][j].thgianRa);
				cout << "So tien phai tra la: " << baixe2[i][j].tienphaitra << " VND." << endl;
				cout << "Xe co bien so " << nhapbs << "  da ra khoi bai so 2." << endl;

				//ghi lại thông tin xe đã rời bãi 2.
				ofstream danhSach2;
				danhSach2.open("Danh Sach Cac Xe Da Roi Bai 2.txt", ios::app);
				danhSach2 <<"\n" <<baixe2[i][j].bienso <<"    "<< baixe2[i][j].vitri <<"          "
					<< baixe2[i][j].ngayGioVao->tm_hour << ":" << baixe2[i][j].ngayGioVao->tm_min << ":" << baixe2[i][j].ngayGioVao->tm_sec << ". "
					<< baixe2[i][j].ngayGioVao->tm_mday << "/" << baixe2[i][j].ngayGioVao->tm_mon + 1 << "/" << baixe2[i][j].ngayGioVao->tm_year + 1900 
					<< "     "<< baixe2[i][j].ngayGioRa->tm_hour << ":" << baixe2[i][j].ngayGioRa->tm_min << ":" << baixe2[i][j].ngayGioRa->tm_sec << ". "
					<< baixe2[i][j].ngayGioRa->tm_mday << "/" << baixe2[i][j].ngayGioRa->tm_mon + 1 << "/" << baixe2[i][j].ngayGioRa->tm_year + 1900 
					<< "     "<< baixe2[i][j].tienphaitra << endl;
				danhSach2.close();

				baixe2[i][j].bienso = "";

				xuatXe = true; return;
			}
		}
	}
	if (xuatXe == false) 
		cout << "Khong tim thay xe co bien so " << nhapbs << endl;
}

//hàm xuất danh sách các xe đã rời đi của 1 trong 2 bãi xe
void xuatThongTinXeDaRa()
{
	string thongtin;
	int chon;
	do
	{
		cout << "-----------------------------------------" << endl;
		cout << "1.Bai xe 1." << endl;
		cout << "2.Bai xe 2." << endl;
		cout << "0.Tro lai menu." << endl;
		cout << "Chon bai xe de xuat thong tin: ";
		while (!(cin >> chon))
		{
			cout << "Khong hop le." << endl;
			cout << "Chon bai xe de xuat thong tin: ";
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
		}
		if (chon == 1)
		{
			ifstream xuatDanhSach1;
			xuatDanhSach1.open("Danh Sach Cac Xe Da Roi Bai 1.txt");

			while (xuatDanhSach1.eof() == false)
			{
				getline(xuatDanhSach1, thongtin);
				cout << thongtin;
				cout << endl;
			}
			cout << endl;
			xuatDanhSach1.close();
		}
		else if (chon == 2)
		{
			ifstream xuatDanhSach2;
			xuatDanhSach2.open("Danh Sach Cac Xe Da Roi Bai 2.txt");

			while (xuatDanhSach2.eof() == false)
			{
				getline(xuatDanhSach2, thongtin);
				cout << thongtin;
				cout << endl;
			}
			cout << endl;
			xuatDanhSach2.close();
		}
		else if (chon == 0) break;

		else cout << "Khong hop le." << endl; continue;

	} while (chon != 0);
}

//hàm tìm vị trí 1 xe trong 2 bãi xe khi nhập biển số.
void timViTri1Xe()
{
	bool timthay = false;
	string bs;
	cout << "Nhap bien so xe: "; 
	cin >> bs;

	for (int i = 0; i < 10; i++)
	{
		for (int j = 0; j < 20; j++)
		{
			if (baixe1[i][j].bienso == bs)
			{
				cout << "Xe co bien so " << bs << " dang o bai xe so 1:" << endl;
				cout << "Vi tri: " << baixe1[i][j].vitri << endl;
				cout << "Ngay gio vao bai: "
					<< baixe1[i][j].ngayGioVao->tm_hour << ":" << baixe1[i][j].ngayGioVao->tm_min << ":" << baixe1[i][j].ngayGioVao->tm_sec << ". "
					<< baixe1[i][j].ngayGioVao->tm_mday << "/" << baixe1[i][j].ngayGioVao->tm_mon + 1 << "/" << baixe1[i][j].ngayGioVao->tm_year + 1900 << endl;
				cout << "So tien tam tinh: " << tinhTienGiuXe(baixe1[i][j].thgianVao, time(nullptr)) << " VND" << endl;
				timthay = true; return;
			}
			else if (baixe2[i][j].bienso == bs)
			{
				cout << "Xe co bien so " << bs << " dang o bai xe so 2:" << endl;
				cout << "Vi tri: " << baixe2[i][j].vitri << endl;
				cout << "Ngay gio vao bai: " 
					<< baixe2[i][j].ngayGioVao->tm_hour << ":" << baixe2[i][j].ngayGioVao->tm_min << ":" << baixe2[i][j].ngayGioVao->tm_sec << ". "
					<< baixe2[i][j].ngayGioVao->tm_mday << "/" << baixe2[i][j].ngayGioVao->tm_mon + 1 << "/" << baixe2[i][j].ngayGioVao->tm_year + 1900 << endl;
				cout << "So tien tam tinh: " << tinhTienGiuXe(baixe2[i][j].thgianVao, time(nullptr)) << " VND" << endl;
				timthay = true; return;
			}
		}
	}

	if (timthay == false)
		cout << "Khong tim thay xe co bien so: " << bs << endl;
}

//lưu thông tin các xe còn trong bãi số 1, khi tắt chương trình.
void luuThongTinBai1()
{
	for (int i = 0; i < 10; i++)
	{
		for (int j = 0; j < 20; j++)
		{
			if (baixe1[i][j].bienso == "")
				continue;
			else
			{
				ofstream luuBaiXe1;
				luuBaiXe1.open("Danh Dach Cac Xe Con Trong Bai 1.txt", ios::app);
				luuBaiXe1 <<"\n" <<baixe1[i][j].bienso << "    " << baixe1[i][j].vitri << "          "
					<< baixe1[i][j].ngayGioVao->tm_hour << ":" << baixe1[i][j].ngayGioVao->tm_min << ":" << baixe1[i][j].ngayGioVao->tm_sec << ". "
					<< baixe1[i][j].ngayGioVao->tm_mday << "/" << baixe1[i][j].ngayGioVao->tm_mon + 1 << "/" << baixe1[i][j].ngayGioVao->tm_year + 1900 << endl;
				luuBaiXe1.close();

			}
		}
	}
}

//lưu thông tin các xe còn trong bãi số 2, khi tắt chương trình.
void luuThongTinBai2()
{
	for (int i = 0; i < 10; i++)
	{
		for (int j = 0; j < 20; j++)
		{
			if (baixe2[i][j].bienso == "")
				continue;
			else
			{
				ofstream luuBaiXe2;
				luuBaiXe2.open("Danh Dach Cac Xe Con Trong Bai 2.txt", ios::app);
				luuBaiXe2 << "\n"<<baixe2[i][j].bienso << "    " << baixe2[i][j].vitri << "          "
					<< baixe2[i][j].ngayGioVao->tm_hour << ":" << baixe2[i][j].ngayGioVao->tm_min << ":" << baixe2[i][j].ngayGioVao->tm_sec << ". "
					<< baixe2[i][j].ngayGioVao->tm_mday << "/" << baixe2[i][j].ngayGioVao->tm_mon + 1 << "/" << baixe2[i][j].ngayGioVao->tm_year + 1900 << endl;
				luuBaiXe2.close();
			}
		}
	}
}

int main()
{
	int chon;
	do
	{
		cout << "------------------MENU-------------------" << endl;
		cout << "1.Nhap xe vao bai." << endl;
		cout << "2.Xuat xe ra bai." << endl;
		cout << "3.Xuat thong tin cac xe da roi bai." << endl;
		cout << "4.Tim xe trong bai." << endl;
		cout << "0.Thoat chuong trinh." << endl;
		cout << "Chon chuc nang: ";

		while (!(cin >> chon)) 
		{ 
			cout << "Khong hop le." << endl;
			cout << "Chon chuc nang: ";
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
		}

		cout << "-----------------------------------------" << endl;

		switch (chon)
		{
		case 1: nhapXe();
			break;
		case 2: xuatXeRaBai();
			break;
		case 3: xuatThongTinXeDaRa();
			break;
		case 4: timViTri1Xe();
			break;
		case 0: cout << "Da thoat chuong trinh." << endl;
			break;
		default: cout << "Khong hop le." << endl;
			break;
		}

	} while (chon != 0);

	luuThongTinBai1();
	luuThongTinBai2();

	system("pause");
	return 0;
}