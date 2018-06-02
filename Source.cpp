#include "stdafx.h"
#include "Header.h"


//----------------------------------------------------------------------------------------------------------------
//class Count
Count::Count() {
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
Count::Count(int number)
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

void Count::CalculateDlinu(const int KolVitkov, const double DiamProv, const int ShirKat, const int j)
{
	double  Storona = 0.04; // â ìåòðàõ
	double DlinaVitka = 0;
	double MinStorona = 0; // â ìåòðàõ

	for (int i(1); i < KolVitkov; i += ShirKat) 
	{
		MinStorona = Storona - ((i * DiamProv) / ShirKat); // Îïðåäåëÿåì âíóòðåííþþ ñòîðîíó êîòóøêè
		Storona = MinStorona; // îïðåäåëÿåì ñòîðîíó êîòóøêè ïðè i-ì êîëè÷åñòâî âèòêîâ
		DlinaVitka = 6.28 * Storona;//Storona * ShirKat; // ñ÷èòàåì íà÷àëüíóþ äëèíó íóæíîãî ïðîâîäà äëÿ 1 ñòîðîíû êîòóøêè (çäåñü øèðèíà êîòóøêè â êîëè÷åñòâå âèòêîâ)  

		if (MinStorona > 0)
		{
			Vitki[j].push_back(i); // ïðîñòî çàïèñûâàåì  âèòêè, ïðè êîòîðûõ âîçìîæíî ñìîòàòü êîòóøêó

			for (double j(0); j < (i / ShirKat); j++)
			{
				Storona += DiamProv;  // óçíàåì íà ñêîëüêî óâåëè÷èòñÿ ñòîðîíà êîòóøêè äëÿ êàæäîãî íîâîãî ñëîÿ
				DlinaVitka += 6.28 * ShirKat * Storona; // òàêæå óçíàåì äëèíó âèòêà óæå ïîëíîñòüþ ãîòîâîé êîòóøêè
			}
			double Sech = 0.785 * DiamProv * DiamProv;
			double Ind = 0.018 * KolVitkov * KolVitkov * (Sech / DlinaVitka) * 1000;
			Induction[j].push_back(Ind);
			Rad[j].push_back(Storona);  // çàïèñûâàåì ñòîðîíó êîòóøêè 
			RadMin[j].push_back(MinStorona);
			DlinaProvoda[j].push_back(DlinaVitka); // çàïèñûâàåì  äëèíó ïðîâîäà	
			Storona = 0.04;
		}
	}

}
void Count::CalculateOpir(const double Sech, const int j)
{
	double opir;
	for (unsigned i(0); i < DlinaProvoda[j].size(); i++)
	{
		opir = (0.018 * DlinaProvoda[j][i]) / Sech; // 0.018 ïèòîìà ïðîâ³äí³ñòü 
		Opir[j].push_back(opir);
	}

}
void Count::CalculateStrum(const int j)
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
void Count::CalculateNapruga(const int j)
{
	for (unsigned i(0); i < Strum[j].size(); i++)
	{
		double napruga = Strum[j][i] * Opir[j][i];
		Napruga[j].push_back(napruga);
	}
}
void Count::CalculatePot(const int j)
{
	for (unsigned i(0); i < Strum[j].size(); i++)
	{
		double pot = (Strum[j][i] * Strum[j][i]) * Opir[j][i];
		Pot[j].push_back(pot);
	}
}
void Count::CalculateArea(const double DiamProv, const int ShirKat, const int j)
{
	for (unsigned i(0); i < Vitki[j].size(); i++)
	{
		double area = 0.32 * DiamProv * ((Vitki[j][i] + (ShirKat * ShirKat)) / ShirKat);
		Area[j].push_back(area);
	}
}
void Count::CalculateRoss(const int j)
{
	for (unsigned i(0); i < Area[j].size(); i++)
	{
		double ross = Area[j][i] * 20 * 401;
		Ross[j].push_back(ross);
	}
}
void Count::SetAnswerOut(const char Answer)
{
	answerOut = Answer;
}
void Count::SetAnswerSort(const char Answer)
{
	answerSort = Answer;
}
void Count::Check(const int j)
{
	for (unsigned i(0); i < Ross[j].size(); i++)
	{
		if ((Pot[j][i] <= Ross[j][i]) && (Rad[j][i] <= 0.2) && RadMin[j][i] >= 0)
		{
			Good[j].push_back(i);
		}
	}
}
void Count::SetKolShir(const int j)
{
	KolShirini = j;
}

vector<double>* Count::GetDlina()
{
	return DlinaProvoda;
}
vector<double>* Count::GetOpir()
{
	return Opir;
}
vector<double>* Count::GetStrum()
{
	return Strum;
}
vector<double>* Count::GetPot()
{
	return Pot;
}
vector<double>* Count::GetNapruga()
{
	return Napruga;
}
vector<double>* Count::GetArea()
{
	return Area;
}
vector<double>* Count::GetRoss()
{
	return Ross;
}
vector<int>* Count::GetGood()
{
	return Good;
}
vector<int>* Count::GetVitki()
{
	return Vitki;
}
vector<double>* Count::GetRad()
{
	return Rad;
}
vector<double>* Count::GetRadMin()
{
	return RadMin;
}
vector<double>* Count::GetInducyion()
{
	return Induction;
}
int Count::GetKolVitkov()
{
	return KolVitkov;
}
int Count::GetShirKat()
{
	return ShirKat;
}
double* Count::GetSech()
{
	return sech;
}
int Count::GetNumberDiam()
{
	return numberDiam;
}

istream& operator>>(istream& is, Count& vvod)
{
	cout << "Ââåäèòå êîëè÷åñâòî âèòêîâ: ";
	is >> vvod.KolVitkov;
	cout << "Ââåäè øèðèíó êîòóøêè (â êîëè÷åñòâå âèòêîâ): ";
	is >> vvod.ShirKat;

	for (int i(0); i < vvod.numberDiam; i++)
	{
		cout << "Ââåäèòå äèàìåòð ïðîâîäà: ";
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
ostream& operator<<(ostream& os, Count& vivod)
{
	for (int i(0); i < vivod.numberDiam; i++)
	{
		os << "********************************* Ñå÷åíèå" << vivod.sech[i] << " *********************************" << endl;
		if (vivod.answerOut == 'y')
		{
			for (unsigned j(0); j < vivod.Good[i].size(); j++)
			{
				int k = vivod.GetGood()[i][j];
				os << "Âèòêè: " << vivod.GetVitki()[i][k] << "  \tÑîïðîòèâëåíèå: : " << vivod.GetOpir()[i][k] << " \tÄëèíà: " << vivod.GetDlina()[i][k] << " \tÒîê: " <<
					vivod.GetStrum()[i][k] << " \tÂûäåëåíèå òåïëà: " << vivod.GetPot()[i][k] << " \tÐàññåèâàíèå òåïëà: " << vivod.GetRoss()[i][k] << "\t Êàðêàñ: " << vivod.GetRadMin()[i][k] << endl;
			}
		}
		else if (vivod.answerOut == 'n')
		{
			for (unsigned j(0); j < vivod.DlinaProvoda[i].size(); j++)
			{
				os << "Âèòêè: " << vivod.GetVitki()[i][j] << "  \tÑîïðîòèâëåíèå: " << vivod.GetOpir()[i][j] << " \tÄëèíà: " << vivod.GetDlina()[i][j] << " \tÒîê: " <<
					vivod.GetStrum()[i][j] << " \tÂûäåëåíèå òåïëà: " << vivod.GetPot()[i][j] << " \tÐàññåèâàíèå òåïëà: " << vivod.GetRoss()[i][j] << "\t Êàðêàñ: " << vivod.GetRadMin()[i][j] << endl;
			}
		}
		os << endl;
	}
	return os;
}

Count::~Count()
{
	if (numberDiam != 0)
		delete[] sech, Vitki, DlinaProvoda, Opir, Strum, Napruga, Pot, Area, Ross, Good, Rad, DiamProv, RadMin;
}

//----------------------------------------------------------------------------------------------------------------
//class CheckClass

CheckClass::CheckClass() :Count() { NewGood = NULL; }
CheckClass::CheckClass(int number) :Count(number) { NewGood = new vector<int>[number]; }
void CheckClass::NewCheck(double raznica = 0, double strum1 = 1, double strum2 = 10)
{
	int k;  // äëÿ ïîëó÷åíèÿ èíäåêñîâ ðåçóëüòàòîâ, êîòîðûå ïðîøëè îñíîâíóþ ñîðòèðîâêó
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

char CheckClass::getAnswerSort()
{
	return answerSort;
}
char CheckClass::getAnswerOut()
{
	return answerOut;
}
vector<int>* CheckClass::GetNewGood()
{
	return NewGood;
}

istream& operator>>(istream& is, CheckClass* vvod)
{
	int KolVit;
	cout << "Ââåäèòå êîëè÷åñòâî âèòêîâ: ";
	is >> KolVit;

	int NumberForAll; // êîëè÷åñòâî âàðèàíòîâ ñå÷åíèÿ ñðàçó äëÿ âñåõ âàðèàíòîâ øèðèíû êîòóøêè
	double* DiamProvoda = NULL; // ÷òîáû ñðàçó ïðèìåíèòü äëÿ âñåõ âàðèàíòîâ ñå÷åíèÿ ïðîâîäà
	char TheSameForAll = 'n';
	//ââîäèì äàííûå äëÿ ðàñ÷åòîâ äëÿ âñåõ âàðèàíòîâ øèðèíû êîòóøêè
	if (vvod->KolShirini > 1)
	{
		cout << "Ïðîñ÷èòàòü äëÿ âñåõ âàðèàíòîâ øèðèíû  ñ îäèíàêîâûìè ïàðàìåòðàìè? y/n: ";
		cin >> TheSameForAll;

		if (TheSameForAll == 'y')
		{
			cout << "Ââåäèòå êëè÷åñòâî âàðèàíòîâ ñå÷åíèÿ ïðîâîäà: ";
			is >> NumberForAll;
			DiamProvoda = new double[NumberForAll];

			for (int i(0); i < NumberForAll; i++)
			{
				cout << "Ââåäèòå äèàìåòð ïðîâîäà: ";
				is >> DiamProvoda[i];
			}
		}
	}

	double strum1, strum2, raznica;
	system("cls");
	cout << "Ââåäèòå ïàðàìåòðû ñîðòèðîâêè: " << endl;
	cout << "Íà÷àëüíîå çíà÷åíèå òîêà: ";
	cin >> strum1;
	cout << "Îêîí÷àòåëüíîå çíà÷åíèå òîêà: ";
	cin >> strum2;
	cout << "Ââåäèòå ðàçíèó ìîùíîñòè ðàññåèâàíèÿ è ìîùíîñòè âûäåëåíèÿ òåïëà: ";
	cin >> raznica;


	//Äëÿ êàæäîãî âàðèàíòà øèðèíû ïðîñ÷èòàåì âñ¸
	for (int k(0); k < vvod->KolShirini; k++)
	{
		vvod[k].KolVitkov = KolVit;
		cout << "Ââåäèòå øèðèíó êàòóøêè (â êîëè÷åñòâå âèòêîâ): ";
		is >> vvod[k].ShirKat;

		int number;
		//Ââîäèì êîëè÷åñòâî âàðèàíòîâ ñå÷åíèÿ
		if (TheSameForAll == 'y')
		{
			vvod[k].numberDiam = NumberForAll;
			number = NumberForAll;
		}
		else
		{
			cout << "Ââåäèòå êëè÷åñòâî âàðèàíòîâ ñå÷åíèÿ ïðîâîäà: ";
			is >> vvod[k].numberDiam;

			number = vvod[k].numberDiam;
		}

		//ïîñêîëüêó ó íàñ íåñêîëüêî îáüåêòîâ, òî òàê óäîáíåå âûäåëòü ïàìÿòü
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


		//Ââîäèì äèàìåòð ïðîâîäà
		for (int i(0); i < vvod[k].numberDiam; i++)
		{
			if (TheSameForAll == 'y')
			{
				vvod[k].DiamProv[i] = DiamProvoda[i];
			}
			else
			{
				cout << "Ââåäèòå äèàìåòð ïðîâîäà: ";
				is >> vvod[k].DiamProv[i];
			}

			vvod[k].sech[i] = 1000000 * (0.785 * vvod[k].DiamProv[i] * vvod[k].DiamProv[i]);
		}

		//ïðîâîäèì âñå ðàñ÷åòû
		vvod[k].answerOut = 'n'; // äëÿ òîãî, ÷òîáû èçíà÷àëüíî âûâîäèëî íåîòñîðòèðîâàííûå
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
		//ñîðòèðóåì
		vvod[k].NewCheck(raznica, strum1, strum2);
	}
	return is;
}
ostream& operator<<(ostream& os, CheckClass& vivod)
{
	for (int i(0); i < vivod.numberDiam; i++)
	{
		os << "********************************* Ñå÷åíèå: " << vivod.sech[i] << " *********************************" << endl;
		if (vivod.answerOut == 'y')
		{
			for (unsigned j(0); j < vivod.NewGood[i].size(); j++)
			{
				int k = vivod.GetNewGood()[i][j];
				os << "N: " << vivod.GetVitki()[i][k] << " \tR, Îì: " << vivod.GetOpir()[i][k] << " \tl,ì: " << vivod.GetDlina()[i][k] << " \tI,À: " <<
					vivod.GetStrum()[i][k] << " \tP,Âò: " << vivod.GetPot()[i][k] << "\tQ,Âò: " << vivod.GetRoss()[i][k] << " \t Ind,ìÃí: " << vivod.GetInducyion()[i][k] << "\tÊàðêàñ,ì: " << vivod.GetRadMin()[i][k] << "\t Ìàêñ ñòîðîíà,ì: " << vivod.GetRad()[i][k] << endl;
			}
		}
		else if (vivod.answerOut == 'n')
		{
			for (unsigned j(0); j < vivod.Good[i].size(); j++)
			{
				int k = vivod.Good[i][j];
				os << "N: " << vivod.GetVitki()[i][k] << " \tR, Îì: " << vivod.GetOpir()[i][k] << " \tl,ì: " << vivod.GetDlina()[i][k] << " \tI,À: " <<
					vivod.GetStrum()[i][k] << " \tP,Âò: " << vivod.GetPot()[i][k] << "\tQ,Âò: " << vivod.GetRoss()[i][k] << " \t Ind,ìÃí: " << vivod.GetInducyion()[i][k] << "\tÊàðêàñ,ì: " << vivod.GetRadMin()[i][k] << "\t Ìàêñ ñòîðîíà,ì: " << vivod.GetRad()[i][k] << endl;
			}
		}
		os << endl;
	}
	return os;
}

CheckClass::~CheckClass()
{
	delete[] NewGood;
}

//----------------------------------------------------------------------------------------------------------------
