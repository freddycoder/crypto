#pragma once
#include <iostream>
#include <sstream>

template <typename T>
class Matrix {
public:
	Matrix(int pNbLignes, int pNbColonne) {
		nbLigne = pNbLignes;
		nbColonne = pNbColonne;
		nbElement = pNbLignes * pNbColonne;
		matrice = new T[nbElement];
		for (int i = 0; i < nbElement; i++) {
			matrice[i] = 0;
		}
	}
	Matrix(int pNbLignes, const std::string& text) {
		nbLigne = pNbLignes;
		nbElement = text.length();
		while (nbElement % pNbLignes) {
			nbElement++;
		}
		nbColonne = nbElement / nbLigne;
		matrice = new T[nbElement];
		for (int i = 0; i < nbElement; i++) {
			matrice[i] = (int)text[i];
		}
		if (nbElement % 2) {
			matrice[nbElement - 1] = (int)' ';
		}
	}
	Matrix(std::initializer_list<std::initializer_list<T>> pInitList) {
		nbLigne = pInitList.size();
		nbColonne = (*pInitList.begin()).size();
		nbElement = nbLigne * nbColonne;
		matrice = new T[nbElement];
		for (int i = 0; i < nbLigne; i++) {
			for (int j = 0; j < nbColonne; j++) {
				matrice[i * nbColonne + j] = pInitList.begin()[i].begin()[j];
			}
		}
	}
	~Matrix() {
		delete[] matrice;
	}
	void set(int index, int valeur) {
		matrice[index] = valeur;
	}
	int NbElement() const {
		return nbElement;
	}
	T operator[](int index) const {
		return matrice[index];
	}
	Matrix<T>* operator*(const Matrix<T>& b) const {
		Matrix<T>* matriceProduit = nullptr;
		if (nbColonne == b.nbLigne) {
			matriceProduit = new Matrix<T>(nbLigne, b.nbColonne);
			for (int l = 0; l < matriceProduit->nbLigne; l++) {
				for (int c = 0; c < matriceProduit->nbColonne; c++) {
					T dotProduct = 0;
					for (int idot = 0; idot < b.nbLigne; idot++) {
						dotProduct += matrice[(l * nbColonne) + idot] * b.matrice[(idot * b.nbColonne) + c];
					}
					matriceProduit->matrice[(l * matriceProduit->nbColonne) + c] = dotProduct;
				}
			}
		}
		return matriceProduit;
	}
	std::string obtenirMessage() const {
		std::stringstream ss;
		for (int i = 0; i < nbElement; i++) {
			ss << (char)matrice[i];
		}
		return ss.str();
	}
	std::string obtenirChiffres() const {
		std::stringstream ss;
		for (int i = 0; i < nbElement; i++) {
			ss << matrice[i];

			if (i < nbElement - 1) {
				ss << ' ';
			}
		}
		return ss.str();
	}
	Matrix<T>* augmenter(const Matrix& b) const {
		Matrix<T>* ab = new Matrix(nbLigne, nbColonne + b.nbColonne);

		for (int i = 0; i < ab->nbLigne; i++) {
			for (int j = 0; j < ab->nbColonne; j++) {
				if (j < nbColonne) {
					ab->set((i * ab->nbColonne) + j, matrice[(i * nbColonne) + j]);
				}
				else {
					ab->set((i * ab->nbColonne) + j, b.matrice[(i * b.nbColonne) + j-nbColonne]);
				}
			}
		}

		return ab;
	}
	Matrix<double>* echelonner() const {
		Matrix<double>* ae = new Matrix<double>(nbLigne, nbColonne);

		for (int i = 0; i < nbElement; i++) {
			ae->set(i, matrice[i]);
		}

		/*for (int i = 1; i < nbLigne; i++) {
			for (int j = 0; j < nbColonne && j < i; j++) {
				double val = -(*ae)[(i * nbColonne) + j];

				for (int k = 0; k < nbColonne; k++) {
					ae->set((i * nbColonne) + k, (*ae)[(i * nbColonne) + k] * val);
				}
			}
		}*/

		return ae;
	}
private:
	int nbElement;
	int nbLigne;
	int nbColonne;
	T* matrice;
};