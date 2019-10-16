#pragma once
#include <string>
#include "Matrix.h"

template <typename T>
Matrix<T>* coderMessage(const Matrix<T>& message) {
	Matrix<T> matriceDeCodage({ { 2, -1 }, 
								{ -3, 1 } });
	return matriceDeCodage * message;
}
template <typename T>
Matrix<T>* decoderMessage(const Matrix<T>& message) {
	Matrix<T> matriceDeDecodage({ { -1, -1 }, 
								  {-3, -2} });
	return matriceDeDecodage * message;
}
template <typename T>
Matrix<T>* matriceDepuisStringInt(const std::string& s) {
	int nbChiffre = 0;
	for (char c : s) {
		if (isdigit(c) || c == '-') {

		}
		else {
			nbChiffre++;
		}
	}
	nbChiffre++;
	Matrix<T>* matrice = new Matrix<T>(2, nbChiffre / 2);
	std::string ss;
	int index = 0;
	for (char c : s) {
		if (isdigit(c) || c == '-') {
			ss = ss + c;
		}
		if (c == ' ') {
			matrice->set(index++, stol(ss));
			ss.clear();
		}
	}
	matrice->set(index, stol(ss));
	return matrice;
}