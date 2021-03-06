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


// #include here
#include<string>
#include<vector>
#include<unordered_map>

// Question here.
// 1.4 Palindrome Permutation: Given a string, write a function to check if 
// it is a permutation of a palindrome. A palindrome is a word or phrase 
// that is the same forwards and backwards. A permutation is a rearrangement
// of letters. The palindrome does not need to be limited to just dictionary
// words.
//
//EXAMPLE
//Input: Tact Coa
//Output: True (permutations: "taco cat", "atco cta", etc.)

////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////

std::vector<int> buildCharFrequencyVec(const std::string&);
bool checkMaxOneOdd(const std::vector<int>&);

// Implementation here
bool isPermutationOfPalinVec(const std::string& phrase)
{
  std::vector<int> table = buildCharFrequencyVec(phrase);
  return checkMaxOneOdd(table);
}

// Map each character to a number. a->0, b->1, c->2, etc...
// This is case insensitive. Non-letter characters map to -1.
int getCharNumber(char c)
{
  constexpr int a = 'a';
  constexpr int z = 'z';
  int val = static_cast<int>(c);
  if(a <= val && val <= z)
  {
    return val-a;
  }
  return -1;
}

std::vector<int> buildCharFrequencyVec(const std::string& str)
{
  std::vector<int> table(((int)'z') - ((int)'a')+1,0);

  // Loop through str and update the entries
  for(const auto& c : str)
  {
    int i = getCharNumber(c);
    if(i != -1)
    {
      ++table[i];
    }
  }
  return table;
}

bool checkMaxOneOdd(const std::vector<int>& table)
{
  bool foundOdd = false;
  for(const auto& count : table)
  {
    // Check if this count is odd.
    if(count%2 == 1)
    {
      // Has an odd number been previously found?
      if(foundOdd)
        return false;

      // No off number has been previously found. This is the first one, so
      // we update the flag.
      foundOdd = true;
    }
  }
  // If we get out of the above loop, it means that we've found at most one
  // odd number.
  return true;
}

////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////

std::unordered_map<char,int> buildCharFrequencyMap(const std::string&);
bool checkMaxOneOdd(const std::unordered_map<char,int>&);

bool isPermutationOfPalinHash(const std::string& phrase)
{
  // map of char and count
  std::unordered_map<char,int> charcountmap = buildCharFrequencyMap(phrase);
  return checkMaxOneOdd(charcountmap);
}

std::unordered_map<char,int> buildCharFrequencyMap(const std::string& str)
{
  std::unordered_map<char,int> umap{};
  for(const auto& c:str)
  {
    if(getCharNumber(c)!= -1)
    {
      ++umap[c];
    }
  }
  return umap;
}

bool checkMaxOneOdd(const std::unordered_map<char,int>& charfreq_map)
{
  bool foundOdd = false;
  for(const auto p:charfreq_map)
  {
    int count = p.second;
    // Check if it's odd
    if(count%2==1)
    {
      // Has an odd been found?
      if(foundOdd) return false;

      // We have found an odd.
      foundOdd = true;
    }
  }
  return true;
}

////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////

// Optimized - count number of odd as you loop through, as opposed to a 
// final loop at the end after constructing the table. Is it really more 
// optimal?
bool isPermutationOfPalinOpt(const std::string& phrase)
{
  // vector table holding running count.
  std::vector<int> table(static_cast<int>('z')-static_cast<int>('a')+1,0);

  // Loop through the phrase and keep a running count of the odd occurrences
  int oddCount = 0;
  for(const auto& c : phrase)
  {
    // First update the count of c, then update the odd count.
    int ci = getCharNumber(c);
    if(ci != -1)
    {
      ++table[ci];
      if(table[ci]%2==1)
      {
        ++oddCount;
      }
      else
      {
        --oddCount;
      }
    }
  }

  // If there is one or less oddCount left, then it is a permutation of a 
  // palindrome
  return oddCount <= 1;
}

////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////

int createBitVector(const std::string& phrase);
bool checkExactlyOneBitSet(int);

// Space optimization - using a bit vector.
bool isPermutationOfPalinBit(const std::string& phrase)
{
  int bitVector = createBitVector(phrase);
  return bitVector == 0 || checkExactlyOneBitSet(bitVector);
}


int toggle(int,int);

int createBitVector(const std::string& str)
{
  int bitvec = 0;
  for(const auto& c: str)
  {
    int x = getCharNumber(c);
    bitvec = toggle(bitvec,x);
  }
  return bitvec;
}

int toggle(int bitvec, int index)
{
  if(index < 0) return bitvec;

  int mask = 1 << index;

  // Check if the position index in bitvec is zero, if so, we need to toggle
  // it on. We can check this by (bitvec&mask) == 0, since mask will have 1
  // only at position index and zero everywhere else.
  if((bitvec&mask)==0) // this means the value at position index is 0
  {
    bitvec |= mask; // toggle it on
  }
  else
  {
    bitvec &= ~mask; // toggle it off, i.e. ~mask = 1111011111
  }
  return bitvec;
}

// Check that exactly one bit is set by subtracting one from the integer 
// and ANDing it with the original integer. E.g.
// 00010000 - 1 = 00001111
// 00010000 & 00001111 = 0, since there is no overlap between the new value
//                          and the original number
bool checkExactlyOneBitSet(int bitvec)
{
  return ((bitvec-1)&bitvec) == 0;
}

////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////


TEST_CASE("Testing ", "[]" )
{
  SECTION("Sec Testing ")
  {
    REQUIRE(isPermutationOfPalinVec("")==true);
    REQUIRE(isPermutationOfPalinVec("a")==true);
    REQUIRE(isPermutationOfPalinVec("aa")==true);
    REQUIRE(isPermutationOfPalinVec("aaa")==true);
    REQUIRE(isPermutationOfPalinVec("ab")==false);
    REQUIRE(isPermutationOfPalinVec("abb")==true);
  }
  SECTION("Sec Testing ")
  {
    REQUIRE(isPermutationOfPalinHash("")==true);
    REQUIRE(isPermutationOfPalinHash("a")==true);
    REQUIRE(isPermutationOfPalinHash("aa")==true);
    REQUIRE(isPermutationOfPalinHash("aaa")==true);
    REQUIRE(isPermutationOfPalinHash("ab")==false);
    REQUIRE(isPermutationOfPalinHash("abb")==true);
  }
  SECTION("Sec Testing ")
  {
    REQUIRE(isPermutationOfPalinOpt("")==true);
    REQUIRE(isPermutationOfPalinOpt("a")==true);
    REQUIRE(isPermutationOfPalinOpt("aa")==true);
    REQUIRE(isPermutationOfPalinOpt("aaa")==true);
    REQUIRE(isPermutationOfPalinOpt("ab")==false);
    REQUIRE(isPermutationOfPalinOpt("abb")==true);
  }
  SECTION("Sec Testing ")
  {
    REQUIRE(isPermutationOfPalinBit("")==true);
    REQUIRE(isPermutationOfPalinBit("a")==true);
    REQUIRE(isPermutationOfPalinBit("aa")==true);
    REQUIRE(isPermutationOfPalinBit("aaa")==true);
    REQUIRE(isPermutationOfPalinBit("ab")==false);
    REQUIRE(isPermutationOfPalinBit("abb")==true);
  }
}

//auto main()->int
//{
//  return 0;
//}

