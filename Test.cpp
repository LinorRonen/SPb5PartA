#include <iostream>
#include <stdexcept>
#include "doctest.h"
#include <fstream>
#include <sstream>
#include <stdexcept>
#include <cassert>
#include <vector>
using namespace std;

#include "sources/MagicalContainer.hpp"

using namespace ariel;

TEST_CASE("MagicalContainer: check the size of the container after addElement() and removeElement() ")
{
    MagicalContainer container;

    container.addElement(17);

    container.addElement(2);

    container.addElement(25);

    CHECK_EQ(container.size(), 3);

    CHECK_NOTHROW(container.removeElement(2));

    CHECK_THROWS_AS(container.removeElement(9), std::exception);

    CHECK_EQ(container.size(), 2);

    // Adding a valid integer, no exception should be thrown
    CHECK_NOTHROW(container.addElement(17));

    // Adding a double number, should throw an exception
    CHECK_THROWS_AS(container.addElement(3.0), std::runtime_error);
}

TEST_CASE("AscendingIterator")
{
    MagicalContainer container1;

    container1.addElement(17);

    container1.addElement(2);

    container1.addElement(25);

    std::vector<int> expected = {2, 17, 25};

    std::vector<int> actual;

    MagicalContainer::AscendingIterator ascIter(container1);

    for (auto it = ascIter.begin(); it != ascIter.end(); ++it)
    {
        actual.push_back(*it);
    }

    CHECK(actual == expected);

    SUBCASE("")
    {

        MagicalContainer container2;
        container2.addElement(17);
        container2.addElement(2);
        container2.addElement(25);
        container2.addElement(9);
        container2.addElement(3);

        MagicalContainer::AscendingIterator ascIter(container2);

        CHECK(*ascIter == 2);
        ++ascIter;
        CHECK(*ascIter == 3);
        ++ascIter;
        CHECK(*ascIter == 9);
        ++ascIter;
        CHECK(*ascIter == 17);
        ++ascIter;
        CHECK(*ascIter == 25);
        ++ascIter;
        CHECK(ascIter == ascIter.end());
    }
}

TEST_CASE("SideCrossIterator")
{
    MagicalContainer container;

    container.addElement(17);

    container.addElement(2);

    container.addElement(25);

    std::vector<int> expected = {2, 25, 17};

    std::vector<int> actual;

    MagicalContainer::SideCrossIterator crossIter(container);

    for (auto it = crossIter.begin(); it != crossIter.end(); ++it)
    {
        actual.push_back(*it);
    }

    CHECK(actual == expected);
}

TEST_CASE("PrimeIterator")
{
    MagicalContainer container;

    container.addElement(17);
    container.addElement(2);
    container.addElement(25);

    std::vector<int> expected = {2, 17};
    std::vector<int> actual;

    MagicalContainer::PrimeIterator primeIter(container);

    for (auto it = primeIter.begin(); it != primeIter.end(); ++it)
    {
        actual.push_back(*it);
    }

    CHECK(actual == expected);
}
