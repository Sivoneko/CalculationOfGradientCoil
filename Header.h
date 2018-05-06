#pragma once
#include <iostream>
#include <vector>
using namespace std;

class Count
{
protected:
	int KolShirini;
	double* DiamProv;
	int KolVitkov;
	int ShirKat;
	char answerSort;
	char answerOut;
	double* sech;
	int numberDiam;
	vector<double>* Induction;
	vector<int>* Vitki;
	vector<double>* DlinaProvoda;
	vector<double>* Opir;
	vector<double>* Strum;
	vector<double>* Napruga;
	vector<double>* Pot;
	vector<double>* Area;
	vector<double>* Ross;
	vector<int>* Good;
	vector<double>* Rad;
	vector<double>* RadMin;
public:
	Count() {
		KolShirini = 0;
		numberDiam = 0;
		DiamProv = NULL;
		sech = NULL;
		Vitki = NULL;
		DlinaProvoda = NULL;
		Opir = NULL;
		Strum = NULL;
		Napruga = NULL;
		Pot = NULL;
		Area = NULL;
		Ross = NULL;
		Good = NULL;
		Rad = NULL;
		RadMin = NULL;
		Induction = NULL;
	}
	Count(int number)
	{
		numberDiam = number;
		DiamProv = new double[number];
		sech = new double[number];
		Vitki = new vector<int>[numberDiam];
		DlinaProvoda = new vector<double>[numberDiam];
		Opir = new vector<double>[numberDiam];
		Strum = new vector<double>[numberDiam];
		Napruga = new vector<double>[numberDiam];
		Pot = new vector<double>[numberDiam];
		Area = new vector<double>[numberDiam];
		Ross = new vector<double>[numberDiam];
		Good = new vector<int>[numberDiam];
		Rad = new vector<double>[numberDiam];
		RadMin = new vector<double>[numberDiam];
		Induction = new vector<double>[numberDiam];
	};
	void CalculateDlinu(const int KolVitkov, const double DiamProv, const int ShirKat, const int j)
	{
		double  Storona = 0.04; // � ������
		double DlinaVitka = 0;
		double MinStorona = 0; // � ������

		for (int i(1); i < KolVitkov; i += ShirKat)
		{
			MinStorona = Storona - ((i * DiamProv) / ShirKat); // ���������� ���������� ������� �������
			Storona = MinStorona; // ���������� ������� ������� ��� i-� ���������� ������
			DlinaVitka = Storona * ShirKat; // ������� ��������� ����� ������� ������� ��� 1 ������� ������� (����� ������ ������� � ���������� ������)  

			if (MinStorona > 0)
			{
				Vitki[j].push_back(i); // ������ ����������  �����, ��� ������� �������� ������� �������

				for (double j(0); j < (i / ShirKat); j++)
				{
					Storona += (DiamProv * 2);  // ������ �� ������� ���������� ������� ������� ��� ������� ������ ����
					DlinaVitka += 4 * ShirKat * Storona; // ����� ������ ����� ����� ��� ��������� ������� �������
				}
				double Sech = 0.785 * DiamProv * DiamProv;
				double Ind = 0.018 * KolVitkov * KolVitkov * (Sech / DlinaVitka) * 1000;
				Induction[j].push_back(Ind);
				Rad[j].push_back(Storona);  // ���������� ������� ������� 
				RadMin[j].push_back(MinStorona);
				DlinaProvoda[j].push_back(DlinaVitka); // ����������  ����� �������	
				Storona = 0.04;
			}
		}

	}
	void CalculateOpir(const double Sech, const int j)
	{
		double opir;
		for (unsigned i(0); i < DlinaProvoda[j].size(); i++)
		{
			opir = (0.018 * DlinaProvoda[j][i]) / Sech; // 0.018 ������ ��������� 
			Opir[j].push_back(opir);
		}

	}
	void CalculateStrum(const int j)
	{
		for (unsigned i(0); i < DlinaProvoda[j].size(); i++)
		{
			if (DlinaProvoda[j][i] != 0)
			{
				double strum = 1000.00 / Vitki[j][i];
				Strum[j].push_back(strum);
			}
		}
	}
	void CalculateNapruga(const int j)
	{
		for (unsigned i(0); i < Strum[j].size(); i++)
		{
			double napruga = Strum[j][i] * Opir[j][i];
			Napruga[j].push_back(napruga);
		}
	}
	void CalculatePot(const int j)
	{
		for (unsigned i(0); i < Strum[j].size(); i++)
		{
			double pot = (Strum[j][i] * Strum[j][i]) * Opir[j][i];
			Pot[j].push_back(pot);
		}
	}
	void CalculateArea(const double DiamProv, const int ShirKat, const int j)
	{
		for (unsigned i(0); i < Vitki[j].size(); i++)
		{
			double area = 0.32 * DiamProv * ((Vitki[j][i] + (ShirKat * ShirKat)) / ShirKat);
			Area[j].push_back(area);
		}
	}
	void CalculateRoss(const int j)
	{
		for (unsigned i(0); i < Area[j].size(); i++)
		{
			double ross = Area[j][i] * 20 * 401;
			Ross[j].push_back(ross);
		}
	}
	void SetAnswerOut(const char Answer)
	{
		answerOut = Answer;
	}
	void SetAnswerSort(const char Answer)
	{
		answerSort = Answer;
	}
	void Check(const int j)
	{
		for (unsigned i(0); i < Ross[j].size(); i++)
		{
			if ((Pot[j][i] <= Ross[j][i]) && (Rad[j][i] <= 0.2) && RadMin[j][i] >= 0)
			{
				Good[j].push_back(i);
			}
		}
	}
	void SetKolShir(const int j)
	{
		KolShirini = j;
	}

	vector<double>* GetDlina()
	{
		return DlinaProvoda;
	}
	vector<double>* GetOpir()
	{
		return Opir;
	}
	vector<double>* GetStrum()
	{
		return Strum;
	}
	vector<double>* GetPot()
	{
		return Pot;
	}
	vector<double>* GetNapruga()
	{
		return Napruga;
	}
	vector<double>* GetArea()
	{
		return Area;
	}
	vector<double>* GetRoss()
	{
		return Ross;
	}
	vector<int>* GetGood()
	{
		return Good;
	}
	vector<int>* GetVitki()
	{
		return Vitki;
	}
	vector<double>* GetRad()
	{
		return Rad;
	}
	vector<double>* GetRadMin()
	{
		return RadMin;
	}
	vector<double>* GetInducyion()
	{
		return Induction;
	}
	int GetKolVitkov()
	{
		return KolVitkov;
	}
	int GetShirKat()
	{
		return ShirKat;
	}
	double* GetSech()
	{
		return sech;
	}
	int GetNumberDiam()
	{
		return numberDiam;
	}

	friend istream& operator>>(istream& is, Count& vvod)
	{
		cout << "������� ���������� ������: ";
		is >> vvod.KolVitkov;
		cout << "����� ������ ������� (� ���������� ������): ";
		is >> vvod.ShirKat;

		for (int i(0); i < vvod.numberDiam; i++)
		{
			cout << "������� ������� �������: ";
			is >> vvod.DiamProv[i];
			vvod.sech[i] = 0.785 * (1000000 * vvod.DiamProv[i] * vvod.DiamProv[i]);
		}
		for (int i(0); i < vvod.numberDiam; i++)
		{
			vvod.CalculateDlinu(vvod.KolVitkov, vvod.DiamProv[i], vvod.ShirKat, i);
			vvod.CalculateOpir(vvod.sech[i], i);
			vvod.CalculateStrum(i);
			vvod.CalculateNapruga(i);
			vvod.CalculateArea(vvod.DiamProv[i], vvod.ShirKat, i);
			vvod.CalculatePot(i);
			vvod.CalculateRoss(i);
			vvod.Check(i);
		}
		return is;
	}
	friend ostream& operator<<(ostream& os, Count& vivod)
	{
		for (int i(0); i < vivod.numberDiam; i++)
		{
			os << "********************************* �������" << vivod.sech[i] << " *********************************" << endl;
			if (vivod.answerOut == 'y')
			{
				for (unsigned j(0); j < vivod.Good[i].size(); j++)
				{
					int k = vivod.GetGood()[i][j];
					os << "�����: " << vivod.GetVitki()[i][k] << "  \t�������������: : " << vivod.GetOpir()[i][k] << " \t�����: " << vivod.GetDlina()[i][k] << " \t���: " <<
						vivod.GetStrum()[i][k] << " \t��������� �����: " << vivod.GetPot()[i][k] << " \t����������� �����: " << vivod.GetRoss()[i][k] << "\t ������: " << vivod.GetRadMin()[i][k] << endl;
				}
			}
			else if (vivod.answerOut == 'n')
			{
				for (unsigned j(0); j < vivod.DlinaProvoda[i].size(); j++)
				{
					os << "�����: " << vivod.GetVitki()[i][j] << "  \t�������������: " << vivod.GetOpir()[i][j] << " \t�����: " << vivod.GetDlina()[i][j] << " \t���: " <<
						vivod.GetStrum()[i][j] << " \t��������� �����: " << vivod.GetPot()[i][j] << " \t����������� �����: " << vivod.GetRoss()[i][j] << "\t ������: " << vivod.GetRadMin()[i][j] << endl;
				}
			}
			os << endl;
		}
		return os;
	}

	virtual ~Count()
	{
		if (numberDiam != 0)
			delete[] sech, Vitki, DlinaProvoda, Opir, Strum, Napruga, Pot, Area, Ross, Good, Rad, DiamProv, RadMin;
	}
};

class CheckClass : public Count
{
protected:
	vector<int>* NewGood;
public:
	CheckClass() :Count() { NewGood = NULL; }
	CheckClass(int number) :Count(number) { NewGood = new vector<int>[number]; }
	void NewCheck(double raznica = 0, double strum1 = 1, double strum2 = 10)
	{
		int k;  // ��� ��������� �������� �����������, ������� ������ �������� ����������
		for (int i(0); i < numberDiam; i++)
		{
			for (unsigned j(0); j < Good[i].size(); j++)
			{
				k = Good[i][j];
				if (raznica < (Ross[i][k] - Pot[i][k]))
				{
					if ((Strum[i][k] > strum1) && (Strum[i][k] < strum2))
					{
						NewGood[i].push_back(k);
					}
				}
			}

		}

	}

	char getAnswerSort()
	{
		return answerSort;
	}
	char getAnswerOut()
	{
		return answerOut;
	}
	vector<int>* GetNewGood()
	{
		return NewGood;
	}

	friend istream& operator>>(istream& is, CheckClass* vvod)
	{
		int KolVit;
		cout << "������� ���������� ������: ";
		is >> KolVit;

		int NumberForAll; // ���������� ��������� ������� ����� ��� ���� ��������� ������ �������
		double* DiamProvoda = NULL; // ����� ����� ��������� ��� ���� ��������� ������� �������
		char TheSameForAll = 'n';
		//������ ������ ��� �������� ��� ���� ��������� ������ �������
		if (vvod->KolShirini > 1)
		{
			cout << "���������� ��� ���� ��������� ������  � ����������� �����������? y/n: ";
			cin >> TheSameForAll;

			if (TheSameForAll == 'y')
			{
				cout << "������� ��������� ��������� ������� �������: ";
				is >> NumberForAll;
				DiamProvoda = new double[NumberForAll];

				for (int i(0); i < NumberForAll; i++)
				{
					cout << "������� ������� �������: ";
					is >> DiamProvoda[i];
				}
			}
		}

		double strum1, strum2, raznica;
		system("cls");
		cout << "������� ��������� ����������: " << endl;
		cout << "��������� �������� ����: ";
		cin >> strum1;
		cout << "������������� �������� ����: ";
		cin >> strum2;
		cout << "������� ������ �������� ����������� � �������� ��������� �����: ";
		cin >> raznica;


		//��� ������� �������� ������ ���������� ��
		for (int k(0); k < vvod->KolShirini; k++)
		{
			vvod[k].KolVitkov = KolVit;
			cout << "������� ������ ������� (� ���������� ������): ";
			is >> vvod[k].ShirKat;

			int number;
			//������ ���������� ��������� �������
			if (TheSameForAll == 'y')
			{
				vvod[k].numberDiam = NumberForAll;
				number = NumberForAll;
			}
			else
			{
				cout << "������� ��������� ��������� ������� �������: ";
				is >> vvod[k].numberDiam;

				number = vvod[k].numberDiam;
			}

			//��������� � ��� ��������� ��������, �� ��� ������� ������� ������
			vvod[k].DiamProv = new double[number];
			vvod[k].sech = new double[number];
			vvod[k].Vitki = new vector<int>[number];
			vvod[k].DlinaProvoda = new vector<double>[number];
			vvod[k].Opir = new vector<double>[number];
			vvod[k].Strum = new vector<double>[number];
			vvod[k].Napruga = new vector<double>[number];
			vvod[k].Pot = new vector<double>[number];
			vvod[k].Area = new vector<double>[number];
			vvod[k].Ross = new vector<double>[number];
			vvod[k].Good = new vector<int>[number];
			vvod[k].Rad = new vector<double>[number];
			vvod[k].NewGood = new vector<int>[number];
			vvod[k].RadMin = new vector<double>[number];
			vvod[k].Induction = new vector<double>[number];
			system("cls");


			//������ ������� �������
			for (int i(0); i < vvod[k].numberDiam; i++)
			{
				if (TheSameForAll == 'y')
				{
					vvod[k].DiamProv[i] = DiamProvoda[i];
				}
				else
				{
					cout << "������� ������� �������: ";
					is >> vvod[k].DiamProv[i];
				}

				vvod[k].sech[i] = 1000000 * (0.785 * vvod[k].DiamProv[i] * vvod[k].DiamProv[i]);
			}

			//�������� ��� �������
			vvod[k].answerOut = 'n'; // ��� ����, ����� ���������� �������� �����������������
			for (int i(0); i < vvod[k].numberDiam; i++)
			{
				vvod[k].CalculateDlinu(vvod->KolVitkov, vvod[k].DiamProv[i], vvod[k].ShirKat, i);
				vvod[k].CalculateOpir(vvod[k].sech[i], i);
				vvod[k].CalculateStrum(i);
				vvod[k].CalculateNapruga(i);
				vvod[k].CalculateArea(vvod[k].DiamProv[i], vvod[k].ShirKat, i);
				vvod[k].CalculatePot(i);
				vvod[k].CalculateRoss(i);
				vvod[k].Check(i);
			}
			//���������
			vvod[k].NewCheck(raznica, strum1, strum2);
		}
		return is;
	}
	friend ostream& operator<<(ostream& os, CheckClass& vivod)
	{
		for (int i(0); i < vivod.numberDiam; i++)
		{
			os << "********************************* �������: " << vivod.sech[i] << " *********************************" << endl;
			if (vivod.answerOut == 'y')
			{
				for (unsigned j(0); j < vivod.NewGood[i].size(); j++)
				{
					int k = vivod.GetNewGood()[i][j];
					os << "N: " << vivod.GetVitki()[i][k] << " \tR, ��: " << vivod.GetOpir()[i][k] << " \tl,�: " << vivod.GetDlina()[i][k] << " \tI,�: " <<
						vivod.GetStrum()[i][k] << " \tP,��: " << vivod.GetPot()[i][k] << "\tQ,��: " << vivod.GetRoss()[i][k] << " \t Ind,���: " << vivod.GetInducyion()[i][k] << "\t������,�: " << vivod.GetRadMin()[i][k] << "\t ���� �������,�: " << vivod.GetRad()[i][k] << endl;
				}
			}
			else if (vivod.answerOut == 'n')
			{
				for (unsigned j(0); j < vivod.Good[i].size(); j++)
				{
					int k = vivod.Good[i][j];
					os << "N: " << vivod.GetVitki()[i][k] << " \tR, ��: " << vivod.GetOpir()[i][k] << " \tl,�: " << vivod.GetDlina()[i][k] << " \tI,�: " <<
						vivod.GetStrum()[i][k] << " \tP,��: " << vivod.GetPot()[i][k] << "\tQ,��: " << vivod.GetRoss()[i][k] << " \t Ind,���: " << vivod.GetInducyion()[i][k] << "\t������,�: " << vivod.GetRadMin()[i][k] << "\t ���� �������,�: " << vivod.GetRad()[i][k] << endl;
				}
			}
			os << endl;
		}
		return os;
	}
	virtual ~CheckClass()
	{
		delete[] NewGood;
	}
};
