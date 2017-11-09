#include "stdafx.h"
#include "matrix.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace MatrixTest {		

	TEST_CLASS(MatrixTestClass) {
	public:
		
		TEST_METHOD(Construct1) {
			ml::Matrix<int> A(3, 5, 0);
			std::vector<std::vector<int>> b = { {0, 0, 0, 0, 0},
												{0, 0, 0, 0, 0},
												{0, 0, 0, 0, 0} };
			ml::Matrix<int> B(b);
			ml::Matrix<int> C(B);
			Assert::AreEqual(A == C, true);
		}

		TEST_METHOD(SetCol) {
			ml::Matrix<int> A(3, 5, 0);
			A.setCol(4, { 1, 2, 3 });
			A.setCol(0, 4);
			std::vector<std::vector<int>> b = { { 4, 0, 0, 0, 1 },
												{ 4, 0, 0, 0, 2 },
												{ 4, 0, 0, 0, 3 } };
			ml::Matrix<int> B(b);
			Assert::AreEqual(A == B, true);
		}

		TEST_METHOD(SetRow) {
			ml::Matrix<int> A(3, 5, 0);
			A.setRow(2, { 1, 2, 3, 4, 5 });
			A.setRow(0, 6);
			std::vector<std::vector<int>> b = { { 6, 6, 6, 6, 6 },
												{ 0, 0, 0, 0, 0 },
												{ 1, 2, 3, 4, 5 } };
			ml::Matrix<int> B(b);
			Assert::AreEqual(A == B, true);
		}

		TEST_METHOD(Divide) {
			std::vector<std::vector<double>> a = {	{ 1, 2, 3 },
													{ 4, 5, 6 },
													{ 1, 6, 4 } };
			ml::Matrix<double> A(a);
			std::vector<std::vector<double>> b = {	{ 6, 7, 8 },
													{ 1, 9, 3 },
													{ 2, 5, 8 } };
			ml::Matrix<double> B(b);
			double det = 3. / 32;
			Assert::AreEqual((A / B).getDeterminant(), det, 0.01);
		}

		TEST_METHOD(AddMethod) {
			ml::Matrix<int> A((size_t)3, (size_t)3, 1),
							B((size_t)3, (size_t)3, 2);
			Assert::AreEqual((A + 1).toString(), B.toString());
		}

		TEST_METHOD(TransposeMethod) {
			std::vector<std::vector<int>> a = { { 6, 6, 6, 6, 6 },
												{ 0, 0, 0, 0, 0 },
												{ 1, 2, 3, 4, 5 } };
			ml::Matrix<int> A(a);
			std::vector<std::vector<int>> b = { { 6, 0, 1 },
												{ 6, 0, 2 },
												{ 6, 0, 3 },
												{ 6, 0, 4 },
												{ 6, 0, 5 } };
			ml::Matrix<int> B(b);
			Assert::AreEqual(A.getTranspose() == B, true);
		}

	};
}