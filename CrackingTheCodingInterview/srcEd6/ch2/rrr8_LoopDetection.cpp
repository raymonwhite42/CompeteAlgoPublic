/*
 * =========================================================================
 * Copyright (c) 2018, Raymon White - All Rights Reserved
 * Author:  Raymon White (ray), https://ray42.com
 * Contact: rayaxiom42 AT gmail DOT com
 * License: GNU AGPLv3
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
// 2.8: Loop Detection: Given a circular linked list, implement an algorithm
//      that returns the node at the beginning of the loop.
//
// DEFINITION: Circular linked list: A (corrupt) linked list in which a 
//             node's next pointer points to an earlier node, so as to make
//             a loop in the linked list.
//
// EXAMPLE:
// Input: A->B->C->D->E->C[the same C as earlier]
// Output: C
//
// Hints:
//
// #50: There are really two parts to this problem. First, detect if the 
//      linked list has a loop. Second, figure out where the loop starts.
//
// #69: To identify if there's a cycle, try the ``runner'' approach 
//      described in \cref{secIQCh02LinkedListRunner}. Have one pointer move
//      faster than the other.
//
// #83: You can use two pointers, one moving twice as fast as the other. If 
//      there is a cycle, the two pointers will collide. They will land at 
//      the same location at the same time. Where do they land? Why there?
//
// #90: If you haven't identified the pattern of where the two pointers 
//      start, try this: Use the linked list 
//      1->2->3->4->5->6->7->8->9->?,
//      where the ? links to another node. Try making the ? the first node 
//      (that is, the 9 points to the 1 such that the entire linked list is
//      a loop). Then make the ? the node 2. Then the node 3. Then the node
//      4. What is the pattern? Can you explain why this happens?

////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////
// #include here
#include "./../rayheader.h"

////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////
// Implementation here
// NOTE: Read my notes for how this works. I cba to explain it here.
ListNode* find_beginning(ListNode* head)
{
  if(head==nullptr) return nullptr;

  // Find out if contains a cycle.
  ListNode* slow = head;
  ListNode* fast = head;
  
  while(fast && fast->next)
  {
    // we need to advance first, since if we do the checking first, it will
    // always be equal on the first iteration.
    fast = fast->next->next;
    slow = slow->next;

    // check for equality
    if(slow == fast)
    {
      break;
    }


  }

  // if a cycle is not detected, return nullptr
  if(slow != fast)
    return nullptr;

  // Now we know that slow == first, so we place slow back at the head,
  // and walk through, returning the first node which are equal
  slow = head;
  while(slow && fast)
  {
    // Here, we do the opposite, we check first. This is because the head
    // of the linked list and the meeting point (determined by the first
    // while loop) might be the same node, i.e. a fully cyclic list.
    if(slow == fast)
      return slow;

    slow = slow->next;
    fast = fast->next;
  }

  // for what ever reason, if we get here, we just return nullptr to 
  // indicate failure.
  return nullptr;
}

////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////
TEST_CASE("Testing ", "[]" )
{

// nullptr
SECTION("Sec Testing ")
{
  ListNode* l1 = nullptr;

  REQUIRE(find_beginning(l1)==nullptr);
}

// Not linked.
SECTION("Sec Testing ")
{
  ListNode* l1 = new ListNode{1};
  ListNode* l2 = new ListNode{2};
  ListNode* l3 = new ListNode{3};
  ListNode* l4 = new ListNode{4};
  ListNode* l5 = new ListNode{5};
  ListNode* l6 = new ListNode{6};
  ListNode* l7 = new ListNode{7};
  ListNode* l8 = new ListNode{8};
  ListNode* l9 = new ListNode{9};
  l1->next = l2;
  l2->next = l3;
  l3->next = l4;
  l4->next = l5;
  l5->next = l6;
  l6->next = l7;
  l7->next = l8;
  l8->next = l9;
  
  REQUIRE(find_beginning(l1)==nullptr);
}
 
// link l9->l1 
SECTION("Sec Testing ")
{
  ListNode* l1 = new ListNode{1};
  ListNode* l2 = new ListNode{2};
  ListNode* l3 = new ListNode{3};
  ListNode* l4 = new ListNode{4};
  ListNode* l5 = new ListNode{5};
  ListNode* l6 = new ListNode{6};
  ListNode* l7 = new ListNode{7};
  ListNode* l8 = new ListNode{8};
  ListNode* l9 = new ListNode{9};
  l1->next = l2;
  l2->next = l3;
  l3->next = l4;
  l4->next = l5;
  l5->next = l6;
  l6->next = l7;
  l7->next = l8;
  l8->next = l9;
  
  // cycle:
  l9->next = l1;
  REQUIRE(find_beginning(l1)==l1);
}
// link l9->l2
SECTION("Sec Testing ")
{
  ListNode* l1 = new ListNode{1};
  ListNode* l2 = new ListNode{2};
  ListNode* l3 = new ListNode{3};
  ListNode* l4 = new ListNode{4};
  ListNode* l5 = new ListNode{5};
  ListNode* l6 = new ListNode{6};
  ListNode* l7 = new ListNode{7};
  ListNode* l8 = new ListNode{8};
  ListNode* l9 = new ListNode{9};
  l1->next = l2;
  l2->next = l3;
  l3->next = l4;
  l4->next = l5;
  l5->next = l6;
  l6->next = l7;
  l7->next = l8;
  l8->next = l9;
  
  // cycle:
  l9->next = l2;
  REQUIRE(find_beginning(l1)==l2);
}
// link l9->l3
SECTION("Sec Testing ")
{
  ListNode* l1 = new ListNode{1};
  ListNode* l2 = new ListNode{2};
  ListNode* l3 = new ListNode{3};
  ListNode* l4 = new ListNode{4};
  ListNode* l5 = new ListNode{5};
  ListNode* l6 = new ListNode{6};
  ListNode* l7 = new ListNode{7};
  ListNode* l8 = new ListNode{8};
  ListNode* l9 = new ListNode{9};
  l1->next = l2;
  l2->next = l3;
  l3->next = l4;
  l4->next = l5;
  l5->next = l6;
  l6->next = l7;
  l7->next = l8;
  l8->next = l9;
  
  // cycle:
  l9->next = l3;
  REQUIRE(find_beginning(l1)==l3);
}
// link l9->l4
SECTION("Sec Testing ")
{
  ListNode* l1 = new ListNode{1};
  ListNode* l2 = new ListNode{2};
  ListNode* l3 = new ListNode{3};
  ListNode* l4 = new ListNode{4};
  ListNode* l5 = new ListNode{5};
  ListNode* l6 = new ListNode{6};
  ListNode* l7 = new ListNode{7};
  ListNode* l8 = new ListNode{8};
  ListNode* l9 = new ListNode{9};
  l1->next = l2;
  l2->next = l3;
  l3->next = l4;
  l4->next = l5;
  l5->next = l6;
  l6->next = l7;
  l7->next = l8;
  l8->next = l9;
  
  // cycle:
  l9->next = l4;
  REQUIRE(find_beginning(l1)==l4);
}
// link l9->l5
SECTION("Sec Testing ")
{
  ListNode* l1 = new ListNode{1};
  ListNode* l2 = new ListNode{2};
  ListNode* l3 = new ListNode{3};
  ListNode* l4 = new ListNode{4};
  ListNode* l5 = new ListNode{5};
  ListNode* l6 = new ListNode{6};
  ListNode* l7 = new ListNode{7};
  ListNode* l8 = new ListNode{8};
  ListNode* l9 = new ListNode{9};
  l1->next = l2;
  l2->next = l3;
  l3->next = l4;
  l4->next = l5;
  l5->next = l6;
  l6->next = l7;
  l7->next = l8;
  l8->next = l9;
  
  // cycle:
  l9->next = l5;
  REQUIRE(find_beginning(l1)==l5);
}
// link l9->l6
SECTION("Sec Testing ")
{
  ListNode* l1 = new ListNode{1};
  ListNode* l2 = new ListNode{2};
  ListNode* l3 = new ListNode{3};
  ListNode* l4 = new ListNode{4};
  ListNode* l5 = new ListNode{5};
  ListNode* l6 = new ListNode{6};
  ListNode* l7 = new ListNode{7};
  ListNode* l8 = new ListNode{8};
  ListNode* l9 = new ListNode{9};
  l1->next = l2;
  l2->next = l3;
  l3->next = l4;
  l4->next = l5;
  l5->next = l6;
  l6->next = l7;
  l7->next = l8;
  l8->next = l9;
  
  // cycle:
  l9->next = l6;
  REQUIRE(find_beginning(l1)==l6);
}
// link l9->l7
SECTION("Sec Testing ")
{
  ListNode* l1 = new ListNode{1};
  ListNode* l2 = new ListNode{2};
  ListNode* l3 = new ListNode{3};
  ListNode* l4 = new ListNode{4};
  ListNode* l5 = new ListNode{5};
  ListNode* l6 = new ListNode{6};
  ListNode* l7 = new ListNode{7};
  ListNode* l8 = new ListNode{8};
  ListNode* l9 = new ListNode{9};
  l1->next = l2;
  l2->next = l3;
  l3->next = l4;
  l4->next = l5;
  l5->next = l6;
  l6->next = l7;
  l7->next = l8;
  l8->next = l9;
  
  // cycle:
  l9->next = l7;
  REQUIRE(find_beginning(l1)==l7);
}
// link l9->l8
SECTION("Sec Testing ")
{
  ListNode* l1 = new ListNode{1};
  ListNode* l2 = new ListNode{2};
  ListNode* l3 = new ListNode{3};
  ListNode* l4 = new ListNode{4};
  ListNode* l5 = new ListNode{5};
  ListNode* l6 = new ListNode{6};
  ListNode* l7 = new ListNode{7};
  ListNode* l8 = new ListNode{8};
  ListNode* l9 = new ListNode{9};
  l1->next = l2;
  l2->next = l3;
  l3->next = l4;
  l4->next = l5;
  l5->next = l6;
  l6->next = l7;
  l7->next = l8;
  l8->next = l9;
  
  // cycle:
  l9->next = l8;
  REQUIRE(find_beginning(l1)==l8);
}
// link l9->l9
SECTION("Sec Testing ")
{
  ListNode* l1 = new ListNode{1};
  ListNode* l2 = new ListNode{2};
  ListNode* l3 = new ListNode{3};
  ListNode* l4 = new ListNode{4};
  ListNode* l5 = new ListNode{5};
  ListNode* l6 = new ListNode{6};
  ListNode* l7 = new ListNode{7};
  ListNode* l8 = new ListNode{8};
  ListNode* l9 = new ListNode{9};
  l1->next = l2;
  l2->next = l3;
  l3->next = l4;
  l4->next = l5;
  l5->next = l6;
  l6->next = l7;
  l7->next = l8;
  l8->next = l9;
  
  // cycle:
  l9->next = l9;
  REQUIRE(find_beginning(l1)==l9);
}
}

//auto main(int argc, char * argv[])->int
//{
//  return 0;
//}

