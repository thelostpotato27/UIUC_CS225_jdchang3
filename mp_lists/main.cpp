#include "List.h"
#include "cs225/catch/catch.hpp"
#include "tests/tests_helper.h"

#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

#include "cs225/PNG.h"
#include "cs225/HSLAPixel.h"

int main() {
    using namespace cs225;
    List<int> list;
    std::cout << "flag0" << std::endl;
    list.insertBack(1);
    list.insertBack(2);
    list.insertBack(3);
    list.insertBack(4);
    list.insertFront(5);
    list.insertFront(6);
    list.insertFront(7);
    list.insertFront(8);
    list.print();
    List<int> slist = list.split(2);
    slist.print();

    // REQUIRE( "< 1 2 >" == s1.str() );
    // REQUIRE( "< 3 4 >" == s2.str() );

  return 0;
}
