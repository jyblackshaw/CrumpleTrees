#include "catch_amalgamated.hpp"
#include "CrumpleTree.hpp"

#include <fstream>
#include <string>
#include <sstream>
#include <vector>


namespace{




/* Remember, these are prerequisites to having us grade
    the related part of the assignment.  These are not
    worth points on their own, nor are they comprehensive.

    REMEMBER TO TEST YOUR OWN CODE COMPREHENSIVELY. 

*/

TEST_CASE("FindTheRoot", "[RequiredBasicFunctionality]")
{
    CrumpleTree<int, std::string> tree;
    tree.insert(5, "foo");

    REQUIRE( tree.contains(5) );
}

TEST_CASE("FindOneHop", "[RequiredBasicFunctionality]")
{
    CrumpleTree<int, std::string> tree;
    tree.insert(5, "foo");
    tree.insert(10, "bar");

    REQUIRE( tree.contains(10) );
}

TEST_CASE("FindTwoHops", "[RequiredBasicFunctionality]")
{
    CrumpleTree<int, std::string> tree;
    tree.insert(5, "foo");
    tree.insert(3, "sna");
    tree.insert(10, "bar");
    tree.insert(12, "twelve");

    REQUIRE( tree.contains(12) );
}



TEST_CASE("CanAddAFew", "[RequiredBasicFunctionality]")
{
    CrumpleTree<int, std::string> tree;
    tree.insert(5, "foo");
    tree.insert(3, "sna");
    tree.insert(10, "bar");
    tree.insert(12, "twelve");
    tree.insert(15, "fifteen");

    REQUIRE( tree.size() == 5 );
}


TEST_CASE("DoAPostOrder", "[RequiredBasicFunctionality]")
{
    CrumpleTree<int, std::string> tree;
    tree.insert(5, "foo");
    tree.insert(3, "sna");
    tree.insert(10, "bar");
    auto trav = tree.postOrder();
    std::vector<int> expected = {3, 10, 5};
    REQUIRE(trav == expected);

}



TEST_CASE("RemoveDoesARemove", "[RequiredCrumpleTree]")
{
    CrumpleTree<int, std::string> tree;
    tree.insert(20, "are");
    tree.insert(19, "you");
    tree.insert(18, "following");
    tree.insert(12, "from");
    tree.insert(9, "lecture?");
    REQUIRE( tree.contains( 20 ) );
    REQUIRE( tree.contains( 19 ) );
    REQUIRE( tree.contains( 18 ) );
    REQUIRE( tree.contains( 12 ) );
    REQUIRE( tree.contains( 9 ) );
    tree.remove(9);
    tree.remove(18);
    // What happens?  12 is now a leaf and must fall.  But 19 is a (2,2) and remains at level 3.
    REQUIRE( ! tree.contains(9));
    REQUIRE( ! tree.contains(18));
    REQUIRE( tree.getLevel(20) == 1);
    REQUIRE( tree.getLevel(12) == 1);
    REQUIRE( tree.getLevel(19) == 3);

}









                        
} // end namespace

