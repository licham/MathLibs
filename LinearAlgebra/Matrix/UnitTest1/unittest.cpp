#include "stdafx.h"
#include "CppUnitTest.h"
#include "matrix.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace MatrixTest
{		

	TEST_MODULE_INITIALIZE(ModuleInitialize) {
		Logger::WriteMessage("In Module Initialize\n");
	}

	TEST_MODULE_CLEANUP(ModuleCleanup) {
		Logger::WriteMessage("In Module Cleanup\n");
	}

	TEST_CLASS(MatrixTestClass)
	{
	public:
		
		TEST_METHOD(MatrixTestMethod1)
		{
			Logger::WriteMessage("In Method\n");
			ml::Matrix<int> A(3, 3, 1);
			ml::Matrix<int> B(3, 3, 2);
			Assert::AreEqual(B, A + 1);
		}

	};
}