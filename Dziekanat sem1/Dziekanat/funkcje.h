/** @file */
#ifndef FUNKCJE_H
#define FUNKCJE_H

#include "struktury.h"

/**
Funkcja dodaje studenta do struktury drzewa, oraz wywoluje funkcje dodajaca ocene dla danego studenta, dlatego jako parametry przyjmuje dane dotyczace ocen. Funkcja Przyjmuje 8 parametrow
@param[in, out] pRoot wskaznik na korzen drzewa.
@param[in] imie imie studenta.
@param[in] nazwisko nazwisko studenta.
@param[in] nr_albumu numer albumu studenta.
@param[in] ocena ocena uzyskana przez studenta.
@param[in] przedmiot nazwa przedmiotu z ktorego student otrzymal ocene.
@param[in] prowadzacy dane prowadzacego dany przedmiot, z ktorego student otrzymal ocene.
@param[in] data data wpisu oceny.
*/
void dodajStudenta(student *& pRoot, const std::string &imie, const std::string &nazwisko,
	int nr_albumu, float ocena, const std::string &przedmiot,
	const std::string &prowadzacy, const std::string &data);


/**
Funkcja otwiera plik wejsciowy, probuje otworzyc dany plik, jesli sie uda, oraz dane wejsciowe sa poprawne, to wywoluje funkcje dodajaca dane do struktury.
@param[in] nazwa nazwa pliku wejsciowego.
@param[in, out] pRoot wskaznik na korzen drzewa
*/
void wczytaj(const std::string &nazwa, student *& pRoot);

/**
Funkcja sprawdza czy student o numerze albumu przyjmowanym jako parametr istnieje juz w strukturze drzewa, ktorej wskaznik na korzen jest przekazywany jako argument o zmiennej pRoot
@param[in] pRoot wskaznik na korzen drzewa
@param[in] nr_albumu numer albumu studenta
@return student * znaleziony jesli istnieje element o podanym numerze albumu w strukturze, nullptr jeœli nie odnaleziono takiego elementu.
*/

student * znajdz(student * pRoot, int nr_albumu);


/**
Kazdy student ma swoja liste ocen. Funkcja ta dodaje ocene do listy ocen studenta w porzadku alfabetycznym wedlug nazwy przedmiotu, z ktorego student otrzymal ocene
@param[in, out] pMark wskaznik na poczatek listy ocen(danego studenta).
@param[in] ocena ocena uzyskana przez studenta.
@param[in] przedmiot nazwa przedmiotu z ktorego student otrzymal ocene.
@param[in] prowadzacy dane prowadzacego dany przedmiot, z ktorego student otrzymal ocene.
@param[in] dat data wpisu oceny.
*/
void dodajOcene(mark *&pMark, float ocena, const std::string &przedmiot, const std::string &prowadzacy, const std::string &dat);

/**
Funkcja dodaje odczytane dane do struktury. Jesli wskaznik na korzen drzewa wskazuje na null, w funkcji tworzony jest obiekt mark z ocenami studenta, oraz obiekt student z danymi studenta. 
W innym wypadku funkcja wywoluje funkcje dodajaca studenta, ktora zajmuje sie obsluga innych wypadkow
@param[in, out] pRoot wskaznik na korzen drzewa.
@param[in] imie imie studenta.
@param[in] nazwisko nazwisko studenta.
@param[in] nr_albumu numer albumu studenta.
@param[in] ocena ocena uzyskana przez studenta.
@param[in] przedmiot nazwa przedmiotu z ktorego student otrzymal ocene.
@param[in] prowadzacy dane prowadzacego dany przedmiot, z ktorego student otrzymal ocene.
@param[in] data data wpisu oceny.
*/

void dodajDoStruktury(student *& pRoot, const std::string &imie, const std::string &nazwisko, int nr_albumu, float ocena, const std::string &przedmiot, const std::string &prowadzacy, const std::string &data);

/**
Funkcja generuje plik tekstowy o nazwie wedlug schematu: numer albumu + ".txt". Do pliku tekstowego wypisuje dane z elementu drzewa na ktory wskazuje wskaznik pRoot, oraz wszystkie elementy posortowanej
listy, ktorej wskaznik na poczatek jest w pRoot->ocena.
@param[in] pRoot wskaznik na korzen drzewa.
*/

void generujPlik(const student *pRoot);

/**
Funkcja usuwa zaalokowane dynamicznie elementy struktury mark
@param[in, out] pOcena wskaznik na poczatek listy ocen.
*/

void usunOcene(mark *&pOcena);

/**
Funkcja usuwa zaalokowane dynamicznie elementy struktury student. Przed usunieciem elementu struktury student, wywolywana jest funkcja usunOcene, z parametrem pRoot->oceny, kasujaca wszystkie oceny danego studenta.
@param[in, out] pRoot wskaznik na korzen drzewa.
*/

void usun(student *&pRoot);

/**
Funkcja iteruje po kolejnych elementach struktury drzewa, wywolujac dla kazdego elementu funkcje generujaca plik - generujPlik.
@param[in] pRoot wskaznik na korzen drzewa.
*/

void zapisz(const student *pRoot);


#endif
