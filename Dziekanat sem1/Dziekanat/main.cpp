#include <iostream>
#include <string>
//#include "vld.h"

#include "struktury.h"
#include "funkcje.h"

int main(int argc, char* argv[]) {
	student * root = nullptr;
	int pom = 0;

	
	if (argc > 1) {
		std::string przelacznik = "-i";
		for (int i = 1; i < argc; i++) {
			if (argv[i] == przelacznik) {
				pom = i;
				break;
			}
		}
		if(pom != 0)
		for (int i = pom + 1; i < argc; i++) {
			wczytaj(argv[i], root);
		}
	}
	zapisz(root);
	usun(root);

	return 0;
}
