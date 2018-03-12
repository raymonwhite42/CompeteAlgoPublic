/*
 * =========================================================================
 * Copyright (c) 2018, Raymon White - All Rights Reserved
 * Author:  Raymon White (ray), rayaxiom42 AT gmail DOT com
 * =========================================================================
 */

// This tells Catch to provide a main() - only do this in one cpp file
#define CATCH_CONFIG_MAIN  
#include "./../catch.hpp"

#include<iostream>
using std::cout; using std::endl;

// This is used as my own debug output. I need to set RAYDEBUG=false/true
#define rcout if(RAYDEBUG) cout 
static bool RAYDEBUG=false;
#define RDEBUG(x) cout << '>' << #x << ':' << x << '\n';

////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////
// Question here.
// 1.6 String Compression: Implement a method to perform basic string
// compression using the counts of repeated characters. For example, the 
// string aabcccccaaa would become a2b1c5a3. If the ``compressed'' string
// would not become smaller than the original string, your method should 
// return the original string. You can assume the string has only uppercase
// and lowercase letters (a-z).
//
// Hints:
// 
// #92: Do the easy thing first. Compress the string, then compare the 
//      lengths.
// #110: Be careful that you aren't repeatedly concatenating strings 
//       together. This can be very inefficient.
//
// I wrote down pseudocode first, then I just implemented it. Seems easy. 
// Let's see what the book has to say.

////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////
// #include here
#include<string>

////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////
// Implementation here


////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////
TEST_CASE("Testing ", "[]" )
{
  SECTION("Sec Testing ")
  {
    {
      string s1{"aabcccccaaa"};
      string a1{"a2b1c5a3"};
      REQUIRE(strCompress(s1)==a1);
    }
    {
      string s1{""};
      string a1{""};
      REQUIRE(strCompress(s1)==a1);
    }
    {
      string s1{"a"};
      string a1{"a"};
      REQUIRE(strCompress(s1)==a1);
    }
  }
}

//auto main()->int
//{
//  return 0;
//}

