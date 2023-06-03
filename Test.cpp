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

    // Check the initial size of the container
    CHECK_EQ(container.size(), 3);

    // Remove an element from the container and check if no exception is thrown
    CHECK_NOTHROW(container.removeElement(2));

    // Try to remove a non-existing element and check if an exception is thrown
    CHECK_THROWS_AS(container.removeElement(9), std::exception);

    // Check the size of the container after removing an element
    CHECK_EQ(container.size(), 2);

    // Add an existing element to the container and check if no exception is thrown
    CHECK_NOTHROW(container.addElement(17));

    // Try to add an element of invalid type and check if an exception is thrown
    CHECK_THROWS_AS(container.addElement(3.0), std::runtime_error);
}

TEST_CASE("AscendingIterator")
{
    MagicalContainer container1;

    // Add elements to the container
    container1.addElement(17);
    container1.addElement(2);
    container1.addElement(25);

    // Define the expected and actual results
    std::vector<int> expected = {2, 17, 25};
    std::vector<int> actual;

    MagicalContainer::AscendingIterator ascIter(container1);

    // Iterate over the container using AscendingIterator and increment the iterator (++ operator)
    for (auto it = ascIter.begin(); it != ascIter.end(); ++it)
    {
        actual.push_back(*it);
    }

    CHECK(actual == expected);

    SUBCASE("Individual element access and end condition")
    {

        MagicalContainer container2;
        container2.addElement(17);
        container2.addElement(2);
        container2.addElement(25);
        container2.addElement(9);
        container2.addElement(3);

        MagicalContainer::AscendingIterator ascIter(container2);

        CHECK(*ascIter == 2);
        ++ascIter; // Move to the next element
        CHECK(*ascIter == 3);
        ++ascIter; // Move to the next element
        CHECK(*ascIter == 9);
        ++ascIter; // Move to the next element
        CHECK(*ascIter == 17);
        ++ascIter; // Move to the next element
        CHECK(*ascIter == 25);
        ++ascIter;                       // Move to the next element
        CHECK(ascIter == ascIter.end()); // Check if the iterator has reached the end
    }

    SUBCASE("EmptyContainer")
    {
        MagicalContainer container3;

        MagicalContainer::AscendingIterator ascIter(container3);

        CHECK(ascIter == ascIter.end()); // Empty container, the iterator should be at the end
    }

    SUBCASE("IncrementOperator")
    {
        MagicalContainer container4;
        container4.addElement(1);
        container4.addElement(3);

        MagicalContainer::AscendingIterator ascIter(container4);

        CHECK_NOTHROW(++ascIter); // Increment once
        CHECK_NOTHROW(++ascIter); // Increment again

        // Attempt to increment beyond the end
        CHECK_THROWS_AS(++ascIter, std::runtime_error);
    }

    SUBCASE("After increments comparing three iterators")
    {
        MagicalContainer container5;
        container5.addElement(1);
        container5.addElement(3);
        container5.addElement(7);
        container5.addElement(10);
        container5.addElement(12);

        MagicalContainer::AscendingIterator it1(container5);
        MagicalContainer::AscendingIterator it2(container5);
        MagicalContainer::AscendingIterator it3(container5);

        ++it1;
        ++it2;
        ++it2;
        ++it3;
        ++it3;
        ++it3;

        CHECK(it1 != it2);
        CHECK(it2 != it3);
        CHECK(it1 != it3);
        CHECK(it1 < it2);
        CHECK(it2 < it3);
        CHECK(it1 < it3);
        CHECK(it2 > it1);
        CHECK(it3 > it2);
        CHECK(it3 > it1);
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

    SUBCASE("IncrementOperator")
    {
        MagicalContainer container2;
        container2.addElement(1);
        container2.addElement(3);

        // Create and initialize the SideCrossIterator
        MagicalContainer::SideCrossIterator iter(container2);

        // Increment the iterator
        ++iter;

        // Check if the iterator has moved to the next element
        CHECK(*iter == 3);
    }
    SUBCASE("After increments comparing three iterators")
    {
        MagicalContainer container3;
        container3.addElement(1);
        container3.addElement(3);
        container3.addElement(7);
        container3.addElement(10);
        container3.addElement(12);

        // Create three SideCrossIterators
        MagicalContainer::SideCrossIterator iter1(container3);
        MagicalContainer::SideCrossIterator iter2(container3);
        MagicalContainer::SideCrossIterator iter3(container3);

        // Increment the iterators
        ++iter1;
        ++iter2;
        ++iter2;
        ++iter3;
        ++iter3;
        ++iter3;

        // Compare the iterators
        CHECK(iter1 != iter2);
        CHECK(iter2 != iter3);
        CHECK(iter1 != iter3);
        CHECK(iter1 < iter2);
        CHECK(iter2 < iter3);
        CHECK(iter1 < iter3);
        CHECK(iter2 > iter1);
        CHECK(iter3 > iter2);
        CHECK(iter3 > iter1);
    }
    SUBCASE("Try to.....")
    {
        MagicalContainer container4;
        container4.addElement(1);
        container4.addElement(3);

        MagicalContainer::SideCrossIterator crossIter(container4);

        CHECK_NOTHROW(++crossIter); // Increment once
        CHECK_NOTHROW(++crossIter); // Increment again

        // Attempt to increment beyond the end
        CHECK_THROWS_AS(++crossIter, std::runtime_error);
    }
}

TEST_CASE("PrimeIterator")
{
    SUBCASE("EmptyContainer")
    {
        MagicalContainer container;

        std::vector<int> expected;
        std::vector<int> actual;

        MagicalContainer::PrimeIterator primeIter(container);

        for (auto it = primeIter.begin(); it != primeIter.end(); ++it)
        {
            actual.push_back(*it);
        }

        CHECK(actual == expected);
    }

    SUBCASE("ContainerWithPrimes")
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

    SUBCASE("ContainerWithoutPrimes")
    {
        MagicalContainer container;

        container.addElement(4);
        container.addElement(10);
        container.addElement(25);

        std::vector<int> expected;
        std::vector<int> actual;

        MagicalContainer::PrimeIterator primeIter(container);

        for (auto it = primeIter.begin(); it != primeIter.end(); ++it)
        {
            actual.push_back(*it);
        }

        CHECK(actual == expected);
    }

    SUBCASE("IncrementOperator")
    {
        MagicalContainer container;

        container.addElement(3);
        container.addElement(7);
        container.addElement(5);

        std::vector<int> expected = {3, 5, 7};
        std::vector<int> actual;

        MagicalContainer::PrimeIterator primeIter(container);

        auto it = primeIter.begin();
        ++it; // Increment once
        ++it; // Increment again

        actual.push_back(*it); // Should be the third prime number (7)

        CHECK(actual == expected);
    }

    SUBCASE("After increments comparing three iterators")
    {
        MagicalContainer container;
        container.addElement(1);
        container.addElement(3);
        container.addElement(7);
        container.addElement(10);
        container.addElement(12);

        MagicalContainer::PrimeIterator it1(container);
        MagicalContainer::PrimeIterator it2(container);

        CHECK((it1 == it2));
        CHECK_FALSE((it1 != it2));
        CHECK_FALSE((it1 > it2));
        CHECK_FALSE((it1 < it2));

        ++it1;
        CHECK_FALSE((it1 == it2));
        CHECK((it1 != it2));
        CHECK((it1 > it2));
        CHECK_FALSE((it1 < it2));

        ++it2;
        CHECK((it1 == it2));
        CHECK_FALSE((it1 > it2));
        CHECK_FALSE((it1 < it2));

        ++it1;
        CHECK_FALSE((it1 == it2));
        CHECK((it1 != it2));
        CHECK((it1 > it2));

        ++it2;
        CHECK((it1 == it2));
        CHECK_FALSE((it1 != it2));

        ++it2;
        ++it2;
        ++it2;
        CHECK((it2 > it1));
        CHECK((it1 != it2));

        CHECK(it1 == it1.end());
        CHECK(it2 == it2.end());
    }
    SUBCASE("Try to.....")
    {
        MagicalContainer container4;
        container4.addElement(1);
        container4.addElement(3);

        MagicalContainer::PrimeIterator primeIter(container4);

        CHECK_NOTHROW(++primeIter); // Increment again

        // Attempt to increment beyond the end
        CHECK_THROWS_AS(++primeIter, std::runtime_error);
    }
}
