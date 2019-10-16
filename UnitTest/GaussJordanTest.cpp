#include "pch.h"
#include "CppUnitTest.h"
#include "..//Crypto/Matrix.h"
#include "..//Crypto/CryptoUtil.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest
{
	TEST_CLASS(GaussJordanTest)
	{
	public:
		TEST_METHOD(Augmenter)
		{
			Matrix<int> a({ { 1, -2 }, { 3, 5 } });
			Matrix<int> b({ { -8 }, { 9 } });

			Matrix<int>* ab = a.augmenter(b);

			Assert::AreEqual(6, ab->NbElement());

			Assert::AreEqual(1, (*ab)[0]);
			Assert::AreEqual(-2, (*ab)[1]);
			Assert::AreEqual(-8, (*ab)[2]);
			Assert::AreEqual(3, (*ab)[3]);
			Assert::AreEqual(5, (*ab)[4]);
			Assert::AreEqual(9, (*ab)[5]);

			delete ab;
		}

		TEST_METHOD(Echelonner)
		{
			Matrix<int> a({ { 1, -2 }, { 3, 5 } });
			Matrix<int> b({ { -8 }, { 9 } });

			Matrix<int>* ab = a.augmenter(b);

			Matrix<double>* abe = ab->echelonner();

			Assert::AreEqual(6, abe->NbElement());

			Assert::AreEqual(1, (*ab)[0]);
			Assert::AreEqual(-2, (*ab)[1]);
			Assert::AreEqual(-8, (*ab)[2]);
			Assert::AreEqual(0, (*ab)[3]);
			Assert::AreEqual(11, (*ab)[4]);
			Assert::AreEqual(33, (*ab)[5]);

			delete ab;
			delete abe;
		}
	};
}
