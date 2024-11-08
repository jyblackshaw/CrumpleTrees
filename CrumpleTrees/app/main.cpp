#include <fstream>
#include <iostream>
#include <CrumpleTree.hpp>
#include <string>

//test declarations:
void test_case_2();
void test_case_3();
void test_case_5();

int main()
{
    // test_case_3();
    // test_case_5();

    CrumpleTree<int, std::string> ct;
    ct.insert(18, "a");
    ct.insert(12, "test"); 
    ct.remove(18);
    
    
    try {
        std::cout << "find: " << ct.contains(12) << std::endl;
    } catch (const ElementNotFoundException& e) {
        std::cerr << "Exception: " << e.what() << std::endl;
    }

     ct.printTree();
    
    return 0;
}

//test definitions:
void test_case_2(){
    //start:
    CrumpleTree<int, int> ct;

    ct.insert(20, 0); //(insert)
    
    //case:
    ct.insert(19, 0); //case 2

    //print:
    ct.printTree();
}

void test_case_3(){
    //start:
    CrumpleTree<int, int> ct;

    ct.insert(20, 0); //(insert)
    ct.insert(19, 0); //case 2
    
    //case (2+3):
    ct.insert(18, 0);

    //print:
    ct.printTree();
}

void test_case_5(){
    //start:
    CrumpleTree<int, int> ct;

    ct.insert(18, 0); //Root
    ct.insert(19, 0); //case2Right
    ct.insert(20, 0); //case3Right
    ct.insert(12, 0); //case2Left
    ct.insert(9, 0);  //case3Left
    ct.insert(17, 0); //case5
    
    //print:
    ct.printTree();
}