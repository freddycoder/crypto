#include "pch.h"
#include "CppUnitTest.h"
#include "..//Crypto/Matrix.h"
#include "..//Crypto/CryptoUtil.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest
{
	TEST_CLASS(CryptoSimple)
	{
	public:
		TEST_METHOD(ConstructeurDimmession)
		{
			Matrix<int> a(5, 5);

			Assert::AreEqual(25, a.NbElement());

			for (int i = 0; i < a.NbElement(); i++) {
				Assert::AreEqual(0, a[i]);
				Assert::AreEqual('\0', (char)a[i]);
				Assert::AreEqual(NULL, a[i]);
			}

			Assert::AreEqual(25, (int)a.obtenirMessage().length());
		}

		TEST_METHOD(ConstructeurText)
		{
			Matrix<int> a(2, "IL FAIT BEAU");

			Assert::AreEqual(12, a.NbElement());

			Assert::AreEqual(std::string("IL FAIT BEAU"), a.obtenirMessage());

			Assert::AreEqual('U', (char)a[a.NbElement() - 1]);
		}

		TEST_METHOD(ConstructeurText2)
		{
			Matrix<int> a(2, "sixsix");

			Assert::AreEqual(6, a.NbElement());

			Assert::AreEqual(std::string("sixsix"), a.obtenirMessage());

			Assert::AreEqual(std::string("115 105 120 115 105 120"), a.obtenirChiffres());

			Assert::AreEqual('x', (char)a[a.NbElement() - 1]);
		}

		TEST_METHOD(ConstructeurList) 
		{
			Matrix<int> a{ { 2, -1 }, { -3, 1 } };

			Assert::AreEqual(4, a.NbElement());
		}

		TEST_METHOD(MultiplierParIdentite)
		{
			Matrix<int> a{ { 2, -1 }, { -3, 1 } };

			Matrix<int> b{ { 1, 0 }, { 0, 1 } };

			Matrix<int>* ab = a * b;

			Assert::AreEqual(2, (*ab)[0]);
			Assert::AreEqual(-1, (*ab)[1]);
			Assert::AreEqual(-3, (*ab)[2]);
			Assert::AreEqual(1, (*ab)[3]);

			delete ab;
		}

		TEST_METHOD(Multiplication)
		{
			Matrix<int> a{ { 2, 3 }, { -1, 5 } };

			Matrix<int> b{ { 5, -4 }, { -6, 7 } };

			Matrix<int>* ab = a * b;

			Assert::AreEqual(-8, (*ab)[0]);
			Assert::AreEqual(13, (*ab)[1]);
			Assert::AreEqual(-35, (*ab)[2]);
			Assert::AreEqual(39, (*ab)[3]);

			delete ab;
		}

		TEST_METHOD(Multiplication2)
		{
			Matrix<int> a{ { 9, 13, 49, 6, 1, 9 }, 
						   { 22, 49, 2, 5, 1, 23 } };

			Matrix<int> b{ { 2, -1 }, 
						   { -3, 1 } };

			Matrix<int>* ba = b * a;

			Assert::AreEqual(-4, (*ba)[0]);
			Assert::AreEqual(-23, (*ba)[1]);
			Assert::AreEqual(96, (*ba)[2]);
			Assert::AreEqual(7, (*ba)[3]);
			Assert::AreEqual(1, (*ba)[4]);
			Assert::AreEqual(-5, (*ba)[5]);
			Assert::AreEqual(-5, (*ba)[6]);
			Assert::AreEqual(10, (*ba)[7]);
			Assert::AreEqual(-145, (*ba)[8]);
			Assert::AreEqual(-13, (*ba)[9]);
			Assert::AreEqual(-2, (*ba)[10]);
			Assert::AreEqual(-4, (*ba)[11]);

			delete ba;
		}

		TEST_METHOD(ObtenirChiffres) {
			Matrix<int> a(2, "ABCD");

			Assert::AreEqual(std::string("65 66 67 68"), a.obtenirChiffres());
		}

		TEST_METHOD(ObtenirChiffres2) {
			Matrix<int> a(2, "AAAAAA      ");

			Assert::AreEqual(12, a.NbElement());

			Assert::AreEqual(std::string("65 65 65 65 65 65 32 32 32 32 32 32"), a.obtenirChiffres());
		}

		TEST_METHOD(DepuisStringInt) {
			Matrix<int>* a = matriceDepuisStringInt<int>("65 66 67 68");

			Assert::AreEqual(4, a->NbElement());

			Assert::AreEqual(std::string("ABCD"), a->obtenirMessage());
		}

		TEST_METHOD(Senario1)
		{
			Matrix<int> message(2, "IL FAIT BEAU");

			Matrix<int>* messageCoder = coderMessage(message);

			Matrix<int>* messageDecoder = decoderMessage(*messageCoder);

			Assert::AreEqual(std::string("IL FAIT BEAU"), messageDecoder->obtenirMessage());

			delete messageCoder;
			delete messageDecoder;
		}

		TEST_METHOD(Senario1_2)
		{
			Matrix<int> message(2, "IL FAIT BEAU");

			Matrix<int>* messageCoder = coderMessage(message);

			Matrix<int>* messageCoderB = matriceDepuisStringInt<int>(messageCoder->obtenirChiffres());

			delete messageCoder;

			Matrix<int>* messageDecoder = decoderMessage(*messageCoderB);

			Assert::AreEqual(std::string("IL FAIT BEAU"), messageDecoder->obtenirMessage());

			delete messageCoderB;
			delete messageDecoder;
		}

		TEST_METHOD(SenarioFred)
		{
			Matrix<int> message(2, "Fred");

			Matrix<int>* messageCoder = coderMessage(message);

			Matrix<int>* messageDecoder = decoderMessage(*messageCoder);

			Assert::AreEqual(std::string("Fred"), messageDecoder->obtenirMessage());

			delete messageCoder;
			delete messageDecoder;
		}

		TEST_METHOD(SenarioFred2)
		{
			Matrix<int> message(2, "Fred");

			Matrix<int>* messageCoder = coderMessage(message);

			Matrix<int>* messageCoderB = matriceDepuisStringInt<int>(messageCoder->obtenirChiffres());

			delete messageCoder;

			Matrix<int>* messageDecoder = decoderMessage(*messageCoderB);

			Assert::AreEqual(std::string("Fred"), messageDecoder->obtenirMessage());

			delete messageCoderB;
			delete messageDecoder;
		}
	};
}
