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
std::string compressStr(std::string str)
{
  // Check for empty string and string of 1 char, since any compression 
  // cannot be shorter than this.
  if(str.size() == 0 || str.size() == 1) 
    return str;

  // There is at least two characters. So initialize an empty string, and 
  // a count of the consecutive characters.
  std::string ret{};
  int consecCount = 0;

  // Now, since we have to compare str[i] against str[i+1], 
  // where i=0..str.size()-1, we need a way to end the comparison. The best
  // way I can think of doing this is to use a sentinel. I shall use "$".
  str+="$";

  // index into the container, starting at 0.
  int index = 0;

  // character to compare against, initialized to the first char in str.
  char char_to_compare = str[0];

  // Loop from p=0..str.size()-1
  while(index < static_cast<int>(str.size()))
  {
    // If this is the same a char_to_compare, we simply increment both the
    // count and index.
    if(str[index]==char_to_compare)
    {
      ++index;
      ++consecCount;
    }
    // If we get one which is not the same, this means we can add
    // char_to_compare to the result along with the count.
    else
    {
      ret+=char_to_compare+std::to_string(consecCount);

      // Now reset the count and set the new char_to_compare
      consecCount = 0;
      char_to_compare = str[index];

      // Do not increment the index, since we need to count the new char at
      // this index.
    }
  }

  // Note that we never actually put the sentinel in the ret string, but we
  // have put it in the input str, so we need to get rid of it.
  str.pop_back();
   
  return str.size() < ret.size() ? str : ret;
}

////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////
TEST_CASE("Testing ", "[]" )
{
  SECTION("Sec Testing ")
  {
    {
      std::string s1{"aabcccccaaa"};
      std::string a1{"a2b1c5a3"};
      REQUIRE(compressStr(s1)==a1);
    }
    {
      std::string s1{""};
      std::string a1{""};
      REQUIRE(compressStr(s1)==a1);
    }
    {
      std::string s1{"a"};
      std::string a1{"a"};
      REQUIRE(compressStr(s1)==a1);
    }
    {
      std::string s1{"aa"};
      std::string a1{"a2"};
      REQUIRE(compressStr(s1)==a1);
    }
    {
      std::string s1{"abc"};
      std::string a1{"abc"};
      REQUIRE(compressStr(s1)==a1);
    }
  }
}

//auto main()->int
//{
//  return 0;
//}

