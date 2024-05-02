/**
 * Unit Tests for the class
**/

#include <gtest/gtest.h>
#include "Guesser.h"

class GuesserTest : public ::testing::Test
{
	protected:
		GuesserTest(){} //constructor runs before each test
		virtual ~GuesserTest(){} //destructor cleans up after tests
		virtual void SetUp(){} //sets up before each test (after constructor)
		virtual void TearDown(){} //clean up after each test, (before destructor)
};


TEST(GuesserTest, test_constructor)
{
	Guesser g("test");
	ASSERT_EQ( g.remaining(), 3 );
	ASSERT_EQ( g.match("test"), true );
	ASSERT_EQ( g.remaining(), 3 );
}

TEST(GuesserTest, test_longSecret)
{
	Guesser g("abdefghijklmnopqrstuvwxyz1234567890");
	ASSERT_EQ( g.match("abdefghijklmnopqrstuvwxyz123456"), true );
}

TEST(GuesserTest, test_emptyString)
{
	Guesser g("");
	ASSERT_EQ( g.match(""), true );
}

TEST(GuesserTest, testRemainIsZeroLockout)
{
	Guesser g("test");
	ASSERT_EQ( g.match("tost"), false );
	ASSERT_EQ( g.match("tast"), false );
	ASSERT_EQ( g.match("tQst"), false );
	ASSERT_EQ( g.match("test"), false );
}

TEST(GuesserTest, testBruteforceLockoutByLength)
{
	Guesser g("test");
	ASSERT_EQ( g.match("toastyyyyyyyyyyyyyyy"), false );
	ASSERT_EQ( g.match("test"), false );
}

TEST(GuesserTest, testBruteforceLockoutByLength2)
{
	Guesser g("testttttttttttttttttttttttttttttttttt");
	ASSERT_EQ( g.match("testttt"), false );
	ASSERT_EQ( g.match("testttttttttttttttttttttttttttttttttt"), false );
}

TEST(GuesserTest, testBruteforceLockoutByDifChars)
{
	Guesser g("test");
	ASSERT_EQ( g.match("toad"), false );
	ASSERT_EQ( g.match("test"), false );
}