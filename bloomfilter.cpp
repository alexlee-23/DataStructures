//Collaborators: Alex Lee alee23@bu.edu and Dabin Jang djang12@bu.edu
/* HASH REFEERENCES:
hash1 --> https://www.programmingalgorithms.com/algorithm/fnv-hash/
hash2 --> https://dev.to/muiz6/string-hashing-in-c-1np3
*/
/* Description:
For our bloomfilter, we have 2 different hash functions. They give 2 different keys,
which means each string that is inserted, will supposedly have a unique set of 
2 keys. The reason why we are having multiple hash functions is to lower the probability of false positive.

For the bloomfilter array itself, instead of using a bitstream of 0 and 1; 
we mapped 'n' for 0 and 'Y' for 1.
*/

#include "bloomfilter.h"
#include <iostream>
#include <cmath>
#include <string>

using namespace std;

//first hash function
unsigned int hash1(string my_string, int this_length)
{
    const unsigned int prime = 0x811C9DC5;
    unsigned int hash = 0;
    unsigned int i = 0;
    unsigned int c = my_string.length();

    for (i = 0; i < c; i++)
    {
        hash = hash * prime;
        hash ^= (my_string[i]);
    }
    //return hash;
    return hash % this_length;
}

//second hash function
const int PRIME_CONST = 31;
unsigned int hash2(string key, int length)
{
    unsigned int hashCode = 0;
    for (int i = 0; i < key.length(); i++)
    {
        hashCode += key[i] * pow(PRIME_CONST, i);
    }
    return hashCode % length;
}

//third hash function

BloomFilter::BloomFilter(int len)
{
    BloomFilter::length = len;
    bf = new char[len];
    for (int i = 0; i < len; i++)
    {
        bf[i] = 'n';
    }
}

void BloomFilter::insert(string item)
{
    int h1 = hash1(item, this->length);
    bf[h1] = 'Y';
    int h2 = hash2(item, this->length);
    bf[h2] = 'Y';

    /*
    int h3 = hash3(m_Test, this->length);
    bf[h3] = 'Y';
    */

    // cout << "\nh1 is: " << h1 << "\nh2 is: " << h2 << "\nh3 is: " << h3 << endl;
}

/**
 * Checks whether item is in the filter.
 * Returns true if the item is probably in the filter
 *         false if the item is definitely not in the filter
 */
bool BloomFilter::exists(string item)
{
    int h1 = hash1(item, this->length);
    int h2 = hash2(item, this->length);
    /* int h3 = hash3(m_Test, this->length); */

    if (bf[h1] == 'Y' && bf[h2] == 'Y')
        return 1;
    else
        return 0;
}

/**
 * Returns a string of characters representing the Bloom filter
 */
string BloomFilter::output()
{
    return bf;
}