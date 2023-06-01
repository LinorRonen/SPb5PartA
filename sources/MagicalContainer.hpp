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
        void addElement(int element)
        {
            elements.push_back(element);
        }

        void removeElement(int element)
        {
            elements.erase(std::remove(elements.begin(), elements.end(), element), elements.end());
        }

        size_t size() const
        {
            return elements.size();
        }

        std::vector<int> &get_vector()
        {
            return elements;
        }

        void Setelements(std::vector<int> &container)
        {
            elements = container;
        }

        class AscendingIterator
        {
        private:
            MagicalContainer &container;

            std::vector<int *> sortedElements; // Vector of pointers to elements

            size_t currentIndex;

        public:
            AscendingIterator(MagicalContainer &cont) : container(cont), currentIndex(0)
            {
                sortedElements.reserve(container.size());
                for (int &element : container.get_vector())
                {
                    sortedElements.push_back(&element); // Store pointer to each element
                }
                std::sort(sortedElements.begin(), sortedElements.end(), [](const int *num1, const int *num2)
                          { return *num1 < *num2; });
            }

            AscendingIterator(const AscendingIterator &other) : container(other.container), sortedElements(other.sortedElements), currentIndex(other.currentIndex) {}

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

            int operator*() const
            {
                return *sortedElements[currentIndex]; // Dereference the pointer to get the value
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
            MagicalContainer &container;
            size_t curr_index = 0;
            std::vector<int *> cross;

        public:
            SideCrossIterator(MagicalContainer &container) : container(container)
            {
                size_t begin = 0;
                size_t end = container.get_vector().size() - 1;
                cross.reserve(container.size());
                std::vector<int> sortedElements = container.get_vector();
                std::sort(sortedElements.begin(), sortedElements.end());

                int num = 0;
                while (begin <= end)
                {
                    if (begin == end)
                    {
                        cross.push_back(&(container.get_vector()[begin]));
                        break;
                    }
                    if (num % 2 == 0)
                    {
                        cross.push_back(&(container.get_vector()[begin]));
                        begin++;
                    }
                    else
                    {
                        cross.push_back(&(container.get_vector()[end]));
                        end--;
                    }
                    num++;
                }

                container.Setelements(sortedElements);
            }

            SideCrossIterator(const SideCrossIterator &other) : container(other.container), curr_index(other.curr_index), cross(other.cross) {}

            SideCrossIterator &operator=(const SideCrossIterator &other)
            {
                if (this != &other)
                {
                    container = other.container;
                    curr_index = other.curr_index;
                    cross = other.cross;
                }
                return *this;
            }

            ~SideCrossIterator() {}

            // Default move constructor
            SideCrossIterator(SideCrossIterator &&other) noexcept;

            SideCrossIterator &operator=(SideCrossIterator &&other) noexcept
            {
                if (this != &other)
                {
                    container = std::move(other.container);
                    curr_index = other.curr_index;
                }
                return *this;
            }

            SideCrossIterator &operator++()
            {
                // Increment the index
                curr_index++;
                return *this;
            }

            int operator*() const
            {
                return *cross[curr_index];
            }

            bool operator==(const SideCrossIterator &other) const
            {
                return curr_index == other.curr_index;
            }

            bool operator!=(const SideCrossIterator &other) const
            {
                return curr_index != other.curr_index;
            }

            SideCrossIterator begin() const
            {
                return SideCrossIterator(container);
            }

            SideCrossIterator end() const
            {
                SideCrossIterator iter(container);
                iter.curr_index = cross.size();
                return iter;
            }
        };

        class PrimeIterator
        {
        private:
            MagicalContainer &container;
            std::vector<int *> primeNumbers; // Vector of pointers to prime numbers in the container
            size_t currentIndex;

        public:
            PrimeIterator(MagicalContainer &cont) : container(cont), currentIndex(0)
            {
                for (int &element : container.get_vector())
                {
                    if (isPrime(element))
                    {
                        primeNumbers.push_back(&element); // Store pointer to prime number element
                    }
                }

                std::sort(primeNumbers.begin(), primeNumbers.end(), [](const int *num1, const int *num2)
                          {
                              return *num1 < *num2; // Sort based on the values pointed by the elements
                          });
            }

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
