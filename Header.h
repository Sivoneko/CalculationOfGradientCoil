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
	Count();
	Count(int number);
	void CalculateDlinu(const int, const double, const int, const int);
	void CalculateOpir(const double, const int);
	void CalculateStrum(const int);
	void CalculateNapruga(const int);
	void CalculatePot(const int);
	void CalculateArea(const double, const int, const int);
	void CalculateRoss(const int);
	void SetAnswerOut(const char);
	void SetAnswerSort(const char);
	void Check(const int);
	void SetKolShir(const int);

	vector<double>* GetDlina();
	vector<double>* GetOpir();
	vector<double>* GetStrum();
	vector<double>* GetPot();
	vector<double>* GetNapruga();
	vector<double>* GetArea();
	vector<double>* GetRoss();
	vector<int>* GetGood();
	vector<int>* GetVitki();
	vector<double>* GetRad();
	vector<double>* GetRadMin();
	vector<double>* GetInducyion();
	int GetKolVitkov();
	int GetShirKat();
	double* GetSech();
	int GetNumberDiam();

	friend istream& operator>>(istream&, Count&);
	friend ostream& operator<<(ostream&, Count&);

	virtual ~Count();
};

class CheckClass : public Count
{
protected:
	vector<int>* NewGood;
public:
	CheckClass();
	CheckClass(int);
	void NewCheck(double, double, double);

	char getAnswerSort();
	char getAnswerOut();
	vector<int>* GetNewGood();

	friend istream& operator>>(istream&, CheckClass*);
	friend ostream& operator<<(ostream&, CheckClass&);

	virtual ~CheckClass();
};
