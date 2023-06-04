#ifndef MAGICALCONTAINER_HPP
#define MAGICALCONTAINER_HPP

#include <vector>
#include <algorithm>
#include <cmath>
#include <iostream>
#include <functional>

using namespace std;
namespace ariel
{
    class MagicalContainer
    {
    private:
        std::vector<int> elements;

    public:
        // Add an element to the container
        void addElement(int element)
        {
            elements.push_back(element);
        }

        // Remove an element from the container
        void removeElement(int element)
        {
            auto iter = std::find(elements.begin(), elements.end(), element);
            if (iter == elements.end())
            {
                throw std::runtime_error("The specified element was not found in the container");
            }
            elements.erase(std::remove(elements.begin(), elements.end(), element), elements.end());
        }

        // Get the size of the container
        size_t size() const
        {
            return elements.size();
        }

        // Get the underlying vector of elements
        std::vector<int> &getElemnets()
        {
            return elements;
        }

        // Set the elements of the container from a given vector
        void Setelements(std::vector<int> &container)
        {
            elements = container;
        }

        class AscendingIterator
        {
        private:
            MagicalContainer &container;       // Reference to the MagicalContainer
            std::vector<int *> sortedElements; // Vector of pointers to elements
            size_t currentIndex;               // Current index in the sortedElements vector

        public:
            AscendingIterator(MagicalContainer &cont) : container(cont), currentIndex(0)
            {
                // Reserve space for sortedElements vector
                sortedElements.reserve(container.size());

                // Populate sortedElements vector with pointers to elements
                for (int &element : container.getElemnets())
                {
                    sortedElements.push_back(&element);
                }

                // Sort the sortedElements vector in ascending order
                std::sort(sortedElements.begin(), sortedElements.end(), [](const int *num1, const int *num2)
                          { return *num1 < *num2; });
            }

            // Copy constructor
            AscendingIterator(const AscendingIterator &other) : container(other.container), sortedElements(other.sortedElements), currentIndex(other.currentIndex) {}

            // Destructor
            ~AscendingIterator() {}

            // Default move constructor
            AscendingIterator(AscendingIterator &&other) noexcept;

            // Default move assignment operator
            AscendingIterator &operator=(AscendingIterator &&other) noexcept;

            AscendingIterator &operator=(const AscendingIterator &other) noexcept
            {
                if (this != &other)
                {
                    container = other.container;
                    sortedElements = other.sortedElements;
                    currentIndex = other.currentIndex;
                }
                return *this;
            }

            bool operator==(const AscendingIterator &other) const
            {
                return &container == &other.container && currentIndex == other.currentIndex;
            }

            bool operator!=(const AscendingIterator &other) const
            {
                return !(*this == other);
            }

            bool operator>(const AscendingIterator &other) const
            {
                return currentIndex > other.currentIndex;
            }

            bool operator<(const AscendingIterator &other) const
            {
                return currentIndex < other.currentIndex;
            }

            int operator*() const
            {
                return *sortedElements[currentIndex];
            }

            AscendingIterator &operator++()
            {
                ++currentIndex;
                return *this;
            }

            AscendingIterator begin()
            {
                AscendingIterator iter(container);
                return iter;
            }

            AscendingIterator end() const
            {
                AscendingIterator iter(container);
                iter.currentIndex = sortedElements.size();
                return iter;
            }
        };

        class SideCrossIterator
        {
        private:
            MagicalContainer &container; // Reference to the MagicalContainer
            std::vector<int *> cross;    // Vector of pointers to elements
            size_t currIndex = 0;        // Current index in the cross vector

        public:
            // Constructor
            SideCrossIterator(MagicalContainer &container) : container(container)
            {
                size_t thebegin = 0;
                size_t theend = container.getElemnets().size() - 1;
                cross.reserve(container.size());
                std::vector<int> sortedElements = container.getElemnets();
                std::sort(sortedElements.begin(), sortedElements.end());

                int num = 0;
                while (thebegin <= theend)
                {
                    if (thebegin == theend)
                    {
                        cross.push_back(&(container.getElemnets()[thebegin]));
                        break;
                    }
                    if (num % 2 == 0)
                    {
                        cross.push_back(&(container.getElemnets()[thebegin]));
                        thebegin++;
                    }
                    else
                    {
                        cross.push_back(&(container.getElemnets()[theend]));
                        theend--;
                    }
                    num++;
                }

                container.Setelements(sortedElements);
            }

            // Copy constructor
            SideCrossIterator(const SideCrossIterator &other) : container(other.container), currIndex(other.currIndex), cross(other.cross) {}

            // copy assignment operator
            SideCrossIterator &operator=(const SideCrossIterator &other)
            {
                if (this != &other)
                {
                    container = other.container;
                    currIndex = other.currIndex;
                    cross = other.cross;
                }
                return *this;
            }

            // Destructor
            ~SideCrossIterator() {}

            // move constructor
            SideCrossIterator(SideCrossIterator &&other) noexcept;

            // move assignment operator
            SideCrossIterator &operator=(SideCrossIterator &&other) noexcept
            {
                if (this != &other)
                {
                    container = std::move(other.container);
                    currIndex = other.currIndex;
                }
                return *this;
            }
            bool operator>(const SideCrossIterator &other) const
            {
                return currIndex > other.currIndex;
            }

            bool operator<(const SideCrossIterator &other) const
            {
                return currIndex < other.currIndex;
            }

            SideCrossIterator &operator++()
            {
                // Increment the index
                currIndex++;
                return *this;
            }

            int operator*() const
            {
                return *cross[currIndex];
            }

            bool operator==(const SideCrossIterator &other) const
            {
                return currIndex == other.currIndex;
            }

            bool operator!=(const SideCrossIterator &other) const
            {
                return currIndex != other.currIndex;
            }

            SideCrossIterator begin() const
            {
                return SideCrossIterator(container);
            }

            SideCrossIterator end() const
            {
                SideCrossIterator iter(container);
                iter.currIndex = cross.size();
                return iter;
            }
        };

        class PrimeIterator
        {
        private:
            MagicalContainer &container;     // Reference to the MagicalContainer
            std::vector<int *> primeNumbers; // Vector of pointers to prime numbers in the container
            size_t currentIndex;             // Current index in the primeNumbers vector

        public:
            PrimeIterator(MagicalContainer &cont) : container(cont), currentIndex(0)
            {
                for (int &element : container.getElemnets())
                {
                    if (isPrime(element))
                    {
                        primeNumbers.push_back(&element); // Store pointer to prime number element
                    }
                }

                std::sort(primeNumbers.begin(), primeNumbers.end(), [](const int *num1, const int *num2)
                          { return *num1 < *num2; });
            }
            // Destructor
            ~PrimeIterator() {}

            // copy constructor
            PrimeIterator(const PrimeIterator &other) : container(other.container), primeNumbers(other.primeNumbers), currentIndex(other.currentIndex) {}

            // copy assignment operator
            PrimeIterator &operator=(const PrimeIterator &other)
            {
                if (this != &other)
                {
                    primeNumbers = other.primeNumbers;
                    currentIndex = other.currentIndex;
                }
                return *this;
            }
            PrimeIterator(PrimeIterator &&other) noexcept : container(other.container), primeNumbers(std::move(other.primeNumbers)), currentIndex(other.currentIndex)
            {
                other.currentIndex = 0;
            }

            PrimeIterator &operator=(PrimeIterator &&other) noexcept
            {
                if (this != &other)
                {
                    container = other.container;
                    primeNumbers = std::move(other.primeNumbers);
                    currentIndex = other.currentIndex;
                    other.currentIndex = 0;
                }
                return *this;
            }

            bool operator==(const PrimeIterator &other) const
            {
                return &container == &other.container && currentIndex == other.currentIndex;
            }

            bool operator!=(const PrimeIterator &other) const
            {
                return !(*this == other);
            }

            int operator*() const
            {
                return *primeNumbers[currentIndex];
            }

            bool operator>(const PrimeIterator &other) const
            {
                return currentIndex > other.currentIndex;
            }

            bool operator<(const PrimeIterator &other) const
            {
                return currentIndex < other.currentIndex;
            }
            static bool isPrime(int num)
            {
                if (num < 2)
                {
                    return false;
                }

                int sqrtNum = static_cast<int>(std::sqrt(num));
                for (int i = 2; i <= sqrtNum; ++i)
                {
                    if (num % i == 0)
                    {
                        return false;
                    }
                }
                return true;
            }

            PrimeIterator &operator++()
            {
                ++currentIndex;
                return *this;
            }

            PrimeIterator begin() const
            {
                PrimeIterator iter(container);
                iter.currentIndex = 0;
                return iter;
            }

            PrimeIterator end() const
            {
                PrimeIterator iter(container);
                iter.currentIndex = primeNumbers.size();
                return iter;
            }
        };
    };
}
#endif // MAGICALCONTAINER_HPP
