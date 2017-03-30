// ConsoleApplication19.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <string>
#include <vector>
#include <queue>
#include <fstream>

using namespace std;




struct osoba
{
	int MBO;
	string ime, prezime;
	vector <string> lijekovi;
};




void noviPacijent(vector <osoba> &sviPacijenti);
void ispisSvih(vector <osoba> &sviPacijenti);
void recepti(vector <osoba> &sviPacijenti, vector <string> &lijekovi);
void sustavCekaonice(queue <osoba> &cekaonica);
void prijava(queue <osoba> &cekaonica);
void odjava(queue <osoba> &cekaonica);
void ljudiUCekaonici(queue <osoba> &cekaonica);
void u_program(vector <osoba> &sviPacijenti, vector <string> &lijekovi);
void u_txt(vector <osoba> &sviPacijenti, vector <string> &lijekovi);
void bubbleSort(vector <osoba> &sviPacijenti);



int main()
{
	vector <osoba> sviPacijenti;
	queue <osoba> cekaonica;
	vector <string> lijekovi;
	
	char i; // 'i' kao izbornik

	u_program(sviPacijenti, lijekovi);
	
	do
	{
		system("CLS");
		cout << "ADMINISTRACIJA PACIJENATA\n\n";
		cout << "1 Unos novog pacijenta \n2 Ispis svih pacijenata \n3 Pretraga pacijenata po MBO\n";
		cout << "4 Cekaonica \n5 Dodavanje recepata \n6 Izlaz\n\n";

		int izbor;
		cout << "Vas izbor je: ";
		cin >> izbor;

		switch (izbor)
		{
		case 1: // UNOS NOVOG PACIJENTA
			noviPacijent(sviPacijenti);
			bubbleSort(sviPacijenti);
			break;
		case 2: // ISPIS SVIH PACIJENATA
			ispisSvih(sviPacijenti);
			break;
		case 3: // PRETRAGA PACIJENATA PO MBO
			break;
		case 4: // CEKAONICA
			sustavCekaonice(cekaonica);
			break;
		case 5: // DODAVANJE RECEPATA
			recepti(sviPacijenti, lijekovi);
			break;
		case 6: // IZLAZ
			break;
		default:
			cout << "Unesite valjan izbor.\n\n";
			break;
		} // kraj switch

		cout << "Unesite slovo 'i' za Izbornik ili bilo koje slovo za izlaz.\n";
		cin >> i;
	} while (i == 'i' || i == 'I');
	
	u_txt(sviPacijenti, lijekovi);

	return 0;
}






void noviPacijent(vector <osoba> &sviPacijenti)
{
	system("CLS");
	char n; // 'n' kao novi pacijent
	char l; // 'l' kao lijek

	osoba pacijent;
	string lijek;

	do
	{
		bool istiPacijent = false;
		cout << "\nUnesite MBO: ";
		cin >> pacijent.MBO;
		cin.ignore();
		for (int i = 0; i < sviPacijenti.size(); i++)
		{
			if (pacijent.MBO == sviPacijenti[i].MBO)
			{
				cout << "ERROR! Vec postoji isti MBO.\n";
				istiPacijent = true;
			}
		}
		if (istiPacijent != true)
		{
			cout << "Unesite ime pacijenta: ";
			getline(cin, pacijent.ime);
			cout << "Unesite prezime pacijenta: ";
			getline(cin, pacijent.prezime);
			cout << "Unesite ime lijeka: ";
			do
			{
				cin >> lijek;
				pacijent.lijekovi.push_back(lijek);
				cout << "\nUnesite slovo 'l' za unos drugog lijeka ili bilo koje drugo slovo za izlaz. ";
				cin >> l;
			} while (l == 'l' || l == 'L');
		}
		sviPacijenti.push_back(pacijent);

		cout << "\nZa unos novog pacijenta unesite slovo 'n' ili bilo koje drugo slovo za izlaz\n. ";
		cin >> n;
	} while (n == 'n' || n == 'N');
}

void ispisSvih(vector <osoba> &sviPacijenti)
{
	system("CLS");

	osoba pacijent;

	for (int i = 0; i < sviPacijenti.size(); i++)
	{
		cout << "MBO " << sviPacijenti[i].MBO << endl;
		cout << "Ime: " << sviPacijenti[i].ime << endl;
		cout << "Prezime: " << sviPacijenti[i].prezime << endl;
		for (int i = 0; i < pacijent.lijekovi.size(); i++)
		{
			cout << "Lijekovi: " << pacijent.lijekovi[i] << endl;
			cout << endl << endl;
		}

	}
}

// popravi na rekurzivno
void pretraga(osoba pacijent, vector <osoba> sviPacijenti)
{
	int MBO;
	cin >> MBO;

	int start = 0;
	int kraj = sviPacijenti.size();
	int sredina = (kraj - start) / 2;

	while (start < kraj && sviPacijenti[sredina].MBO != MBO)
	{
		if (sviPacijenti[sredina].MBO < MBO)
		{
			start = sredina + 1;
		}
		else
		{
			kraj = sredina - 1;
		}
		sredina = (start + kraj) / 2;
	}

	if (sviPacijenti[sredina].MBO == MBO)
	{
		cout << "Pacijent pod  MBO: " << MBO << " je " << sviPacijenti[sredina].ime << " " << sviPacijenti[sredina].prezime << endl << endl;
	}
	else
	{
		cout << "Ne postoji pacijent pod trazenim MBO " << MBO << endl << endl;
	}
}

void recepti(vector <osoba> &sviPacijenti, vector <string> &lijekovi)
{
	osoba pacijent;
	string lijek;
	cout << "\nUnesite MBO: ";
	cin >> pacijent.MBO;

	for (int i = 0; i < sviPacijenti.size(); i++)
	{
		if (pacijent.MBO == sviPacijenti[i].MBO)
		{
			cout << "Trazeni pacijent je " << sviPacijenti[i].ime << " " << sviPacijenti[i].prezime << endl << endl;
			cout << "Unesite recept za lijek: ";
			cin >> lijek;
			sviPacijenti[i].lijekovi.push_back(lijek);
		}
		else
		{
			cout << "Ne postoji pacijent pod upisanim MBO.\n\n";
		}
	}
}

void sustavCekaonice(queue <osoba> &cekaonica)
{
	char c; // 'c' kao cekaonica

	do
	{
		system("CLS");
		cout << "1 Prijava \n2 Odjava \n3 Pacijenti u cekaonici\n\n";

		int izbor;
		cout << "Vas izbor je: ";
		cin >> izbor;

		switch (izbor)
		{
		case 1: // PRIJAVA
			prijava(cekaonica);
			break;
		case 2: // ODJAVA
			odjava(cekaonica);
			break;
		case 3: // LJUDI U CEKAONICI
			ljudiUCekaonici(cekaonica);
			break;
		default:
			cout << "Unesite valjan izbor.\n\n";
			break;
		}
		cout << "Unesite slovo 'c' za Cekaonicu ili bilo koje slovo za izlaz.\n";
		cin >> c;
	} while (c == 'c' || c == 'C');
}

void prijava(queue <osoba> &cekaonica)
{
	system("CLS");
	char n;
	osoba pacijent;
	do
	{
		cout << "U ambulantu na prijavu je dosao pacijent.\n\n";
		cout << "Unesite MBO: ";
		cin >> pacijent.MBO;
		cin.ignore();
		cout << "Unesite ime pacijenta: ";
		getline(cin, pacijent.ime);
		cout << "Unesite prezime pacijenta: ";
		getline(cin, pacijent.prezime);

		cekaonica.push(pacijent);

		cout << "\nZa unos novog pacijenta unesite slovo 'n' ili bilo koje drugo slovo za izlaz\n. ";
		cin >> n;
	} while (n == 'n' || n == 'N');
}

void odjava(queue <osoba> &cekaonica)
{
	char i; // 'i' kao izlaz
	system("CLS");

	do
	{
		cout << "Odjavljuje se pacijent:\n\n" << cekaonica.front().ime << " " << cekaonica.front().prezime << ", MBO: " << cekaonica.front().MBO << endl;
		cekaonica.pop();
		if (cekaonica.size() == 0) {
			cout << "Nema vise pacijenata." << endl;
			break;
		}
		else
		{
			cout << "\nSlijedeci na redu je pacijent " << cekaonica.front().ime << " " << cekaonica.front().prezime << ", MBO: " << cekaonica.front().MBO << endl << endl;
			cout << "Za odjavu pacijenta unesite slovo 'i'.\n\n";
			cin >> i;
		}
	} while (i == 'i' || i == 'I');
}

void ljudiUCekaonici(queue <osoba> &cekaonica)
{
	int broj = cekaonica.size();
	for (int i = 0; i < broj; i++)
	{
		cout << "U čekaonici jos čekaju pacijenti:\n\n";
		cout << cekaonica.front().ime << " " << cekaonica.front().prezime << endl;
	}
}

void u_program(vector <osoba> &sviPacijenti, vector <string> &lijekovi)
{
	
	ifstream openFile("Baza.txt", ios::app);
	while (openFile)
	{
		osoba pacijent;
		openFile >> pacijent.MBO >> pacijent.ime >> pacijent.prezime;
		openFile.ignore();
		sviPacijenti.push_back(pacijent);
	}
	openFile.close();
}

void u_txt(vector <osoba> &sviPacijenti, vector <string> &lijekovi)
{
	ofstream openFile("Baza.txt", ios::app);
	while (openFile)
	{ 
		for (int i = 0; i < sviPacijenti.size(); i++)
		{
			openFile << to_string(sviPacijenti[i].MBO) << endl;
			openFile << sviPacijenti[i].ime << endl;
			openFile << sviPacijenti[i].prezime << endl;
			for (int j = 0; j < lijekovi.size(); j++)
			{
				openFile << lijekovi[i] << " ";
			}
		}	
	}
	openFile.close();
}

// popravi na shell
void bubbleSort(vector <osoba> &sviPacijenti)
{
	int temp_int;
	string temp_string;
	//vector <string> lijekovi;

	bool bila_zamjena = true;

	for (int i = 0; bila_zamjena == true; i++)
	{
		bila_zamjena = false;
		for (int j = 0; j < sviPacijenti.size() - i - 1; j++)
		{
			if (sviPacijenti[j].MBO > sviPacijenti[j + 1].MBO)
			{
				temp_int = sviPacijenti[j].MBO;
				sviPacijenti[j].MBO = sviPacijenti[j - 1].MBO;
				sviPacijenti[j - 1].MBO = temp_int;

				temp_string = sviPacijenti[j].ime;
				sviPacijenti[j].ime = sviPacijenti[j - 1].ime;
				sviPacijenti[j - 1].ime = temp_string;

				temp_string = sviPacijenti[j].prezime;
				sviPacijenti[j].prezime = sviPacijenti[j - 1].prezime;
				sviPacijenti[j - 1].prezime = temp_string;

				// moras jos dodati lijekove
			}
		}
	}
}

