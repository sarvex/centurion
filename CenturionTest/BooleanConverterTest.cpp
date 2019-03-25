#include "stdafx.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using centurion::Centurion;
using centurion::BooleanConverter;

namespace CenturionTest
{
	TEST_CLASS(BooleanConverterTest)
	{
	public:
		TEST_CLASS_INITIALIZE(init)
		{
			Centurion::init();
		}

		TEST_CLASS_CLEANUP(cleanup)
		{
			Centurion::close();
		}

		TEST_METHOD(convert1)
		{
			SDL_bool t = SDL_bool::SDL_TRUE;
			SDL_bool f = SDL_bool::SDL_FALSE;

			bool tConverted = BooleanConverter::convert(t);
			bool fConverted = BooleanConverter::convert(f);

			Assert::IsTrue(tConverted);
			Assert::IsFalse(fConverted);
		}

		TEST_METHOD(convert2)
		{
			bool t = true;
			bool f = false;

			SDL_bool tConverted = BooleanConverter::convert(t);
			SDL_bool fConverted = BooleanConverter::convert(f);

			Assert::IsTrue(tConverted);
			Assert::IsFalse(fConverted);
		}
	};
}