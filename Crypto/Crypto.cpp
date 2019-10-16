#include <iostream>
#include <iomanip>
#include <string>
#include "Matrix.h"
#include "CryptoUtil.h"

void Encrypter() {
	std::string m;
	std::cout << "Votre message : ";
	std::getline(std::cin, m);
	Matrix<long> a(2, m);
	Matrix<long>* b = coderMessage(a);

	std::cout << b->obtenirChiffres() << std::endl;
	std::cout << b->obtenirMessage() << std::endl;

	delete b;
	b = nullptr;
}
void Decrypter() {
	std::string m;
	std::cout << "Votre message : ";
	std::getline(std::cin, m);

	Matrix<long>* a = matriceDepuisStringInt<long>(m);
	Matrix<long>* b = decoderMessage(*a);

	std::cout << b->obtenirChiffres() << std::endl;
	std::cout << b->obtenirMessage() << std::endl;

	delete a;
	a = nullptr;
	delete b;
	b = nullptr;
}
int main() {
	while (true) {
		std::cout << "Choisir une option:" << std::endl;
		std::cout << "1.Encrypter" << std::endl;
		std::cout << "2.Decrypter" << std::endl;
		std::cout << "0.Quitter" << std::endl;

		int choix;
		std::cin >> choix; std::cin.ignore();

		std::string m;

		switch (choix)
		{
		case 1:
			Encrypter();
			break;
		case 2:
			Decrypter();
			break;
		case 0:
			return 0;
		default:
			std::cout << "Choix invalide" << std::endl;
		}
	}
}