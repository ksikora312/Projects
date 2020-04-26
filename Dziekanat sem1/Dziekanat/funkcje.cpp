#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <iomanip>

#include "struktury.h"

void dodajOcene(mark *&pMark, float ocena, const std::string &przedmiot, const std::string &prowadzacy, const std::string &dat) {
	//lista pusta
	if (pMark == nullptr) {
		pMark = new mark{ ocena, przedmiot, prowadzacy, dat };
	}
	else if (pMark->subject > przedmiot) {
		mark * pom = new mark{ ocena, przedmiot, prowadzacy, dat, pMark };
		pMark = pom;
		
	}
	//lista ma wiecej niz 1 element
	else {
		//iteruje po elementach listy, az znajde taki element, ze przedmiot jest wiekszy od niego, ale przedmiot jest mniejszy, niz nastepny element listy, albo gdy nastepny element jest nullem
		mark * pom = pMark;
		while (pom) {
			if (pom->subject < przedmiot && (pom->next->subject > przedmiot || pom->next == nullptr)) {
				mark * element = new mark{ ocena, przedmiot, prowadzacy, dat, pom->next };
				pom->next = element;
				pom = nullptr;
			}
			else
				pom = pom->next;
			}
		}
}

student * znajdz(student * pRoot, int nr_albumu) {
	if (!pRoot || pRoot->album_number == nr_albumu) {
		return pRoot;
	}
	else {
		student * pom = pRoot;
		while (pom) {
			if (pom->album_number == nr_albumu) {
				return pom;
			}
			if (pom->album_number > nr_albumu)
				pom = pom->next;
			else
				pom = pom->nextP;
		}
		return nullptr;
	}
}

void dodajStudenta(student *& pRoot, const std::string &imie, const std::string &nazwisko,
	int nr_albumu, float ocena, const std::string &przedmiot,
	const std::string &prowadzacy, const std::string &data) {
	//istnial juz taki student, wiec dodaje mu tylko oceny
	if (znajdz(pRoot, nr_albumu)) {
		student * pom = znajdz(pRoot, nr_albumu);
		dodajOcene(pom->oceny, ocena, przedmiot, prowadzacy, data);
	}
	//nie istnial taki student, wiec dodaje studenta i jego oceny
	else {
		student * pom = pRoot;
		while (pom) {
			if (nr_albumu < pom->album_number) {
				if (pom->next)
					pom = pom->next;
				else {
					mark * oc = new mark{ ocena, przedmiot, prowadzacy, data, nullptr };
					pom->next = new student{ imie, nazwisko, nr_albumu, nullptr, nullptr, oc };
					pom = nullptr;
				}
			}
			else {
				if (pom->nextP)
					pom = pom->nextP;
				else {
					mark * oc = new mark{ ocena, przedmiot, prowadzacy, data, nullptr };
					pom->nextP = new student{ imie, nazwisko, nr_albumu, nullptr, nullptr, oc };
					pom = nullptr;
				}
			}
		}
	}
}

void dodajDoStruktury(student *& pRoot, const std::string &imie, const std::string &nazwisko,
	int nr_albumu, float ocena, const std::string &przedmiot,
	const std::string &prowadzacy, const std::string &data) {

	if (pRoot == nullptr) {
		mark * mr = new mark{ ocena, przedmiot, prowadzacy, data, nullptr };
		student * st = new student{ imie, nazwisko, nr_albumu, nullptr, nullptr, mr };
		pRoot = st;
	}
	else {
		dodajStudenta(pRoot, imie, nazwisko, nr_albumu, ocena, przedmiot, prowadzacy, data);
	}
}

void wczytaj(const std::string &nazwa, student *& pRoot) {
	std::ifstream plik(nazwa);
	if (plik) {
		std::string plik_przedmiot;
		std::string plik_prowadzacy;
		std::string plik_imie;
		std::string plik_nazwisko;
		int plik_nr_albumu;
		float plik_ocena;
		std::string data;
		if (!getline(plik, plik_przedmiot))
			std::cout << "Nieprawidlowe dane w pliku " << nazwa << std::endl;
			if (!getline(plik, plik_prowadzacy))
				std::cout << "Nieprawidlowe dane w pliku " << nazwa << std::endl;
				while (plik >> plik_imie >> plik_nazwisko >> plik_nr_albumu >> plik_ocena >> data) {
					dodajDoStruktury(pRoot, plik_imie, plik_nazwisko, plik_nr_albumu, plik_ocena, plik_przedmiot, plik_prowadzacy, data);
					//std::cout << plik_przedmiot << std::endl;
					//std::cout << plik_prowadzacy << std::endl;
					//std::cout << plik_imie << " " << plik_nazwisko << " " << plik_nr_albumu << " " << plik_ocena << " " << data << std::endl;
				}
	}
	else
		std::cout << "Nie udalo sie otworzyc pliku " << nazwa << std::endl;
	plik.close();
}



void generujPlik(const student * pRoot) {
	if (pRoot) {
		std::string nazwa = std::to_string(pRoot->album_number) + ".txt";
		std::ofstream plik(nazwa);
		if (plik) {
			plik << pRoot->name << " " << pRoot->surname << std::endl;
			plik << "nr albumu: " << pRoot->album_number << std::endl;
			mark * pomOceny = pRoot->oceny;
			while (pomOceny) {
				plik.setf(std::ios::showpoint);
				plik << std::setprecision(2) << std::setw(30) << std::left << pomOceny->teacher << std::setw(40) << pomOceny->subject << std::setw(5) << pomOceny->ocena << std::setw(3) << pomOceny->data << std::endl;
				pomOceny = pomOceny->next;
			}
			plik.close();
		}
	}
}

void usunOcene(mark *&pOcena) {
	while (pOcena) {
		mark * pom = pOcena->next;
		delete pOcena;
		pOcena = pom;
	}
}
/*
void usun(student *&glowa) {
	while (glowa)
	{
		generujPlik(glowa);
		mark * pomOceny = glowa->oceny;
		student * pom = glowa->next;
		if (pomOceny)
			usunOcene(pomOceny);
		delete glowa;
		glowa = pom;
	}
}
*/
void usun(student *&pRoot) {
	if (pRoot) {
		mark * pom = pRoot->oceny;
		usunOcene(pom);
		usun(pRoot->next);
		usun(pRoot->nextP);
		delete pRoot;
		pRoot = nullptr;
	}
}
void zapisz(const student *pRoot) {
	if (pRoot) {
		zapisz(pRoot->next);
		generujPlik(pRoot);
		zapisz(pRoot->nextP);
	}
}