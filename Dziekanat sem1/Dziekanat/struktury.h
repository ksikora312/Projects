/** @file */
#ifndef STRUKTURY_H
#define STRUKTURY_H

/** Struktura mark jest lista jednokierunkowa */
struct mark {
	float ocena;            ///<ocena studenta
	std::string subject;    ///<przedmiot, z ktorego ocene przechowujemy
	std::string teacher;    ///<prowadzacy dany przedmiot, z ktorego ocene przechowujemy
	std::string data;       ///<data wpisu
	mark * next;            ///<wskaznik na nastepny element listy
};

//Drzewo studentow, kazdy student ma liste ocen, sortowana wg nazwy przedmiotu rosnaco
/** Struktura student jest drzewem binarnym. Kazdy element drzewa binarnego zawiera w sobie liste jednokierunkowa mark */
struct student {
	std::string name;        ///<imie studenta
	std::string surname;	 ///<nazwisko studenta
	int album_number;        ///<numer albumu studenta
	student * next;			 ///<wskaznik na lewe dziecko
	student * nextP;         ///<wskaznik na prawe dziecko
	mark * oceny;            ///<wskaznik na liste jednokierunkowa ocen
};

//kazdy student ma liste ocen





#endif
