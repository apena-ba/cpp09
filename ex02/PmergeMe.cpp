/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apena-ba <apena-ba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/09 08:08:04 by apena-ba          #+#    #+#             */
/*   Updated: 2023/04/10 19:57:47 by apena-ba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PmergeMe.hpp"

// UTILS FUNCTIONS

void trimStr(std::string &to_change, char c){
    unsigned int i = 0;
    while(to_change[i] == c)
        i++;
    if(i > 0)
        to_change.erase(0, i);
}

bool isNumber(std::string const &s){
    if(s.size() < 1)
        return false;
    for(unsigned int i = 0; s[i]; i++){
        if(s[i] < '0' || s[i] > '9')
            return false;
    }
    return true;
}

// UTILS METHODS

void PmergeMe::printSequence(std::string const &line){
    std::cout << line;
    unsigned int limit = 5;

    if(this->_nArgs > 5)
        limit = 4;
    for(unsigned int i = 0; i < limit; i++)
        std::cout << this->_args[i] << " ";
    if(limit == 4)
        std::cout << "[...]";
    std::cout << std::endl;
}

// CONSTRUCTORS AND DESTRUCOR

PmergeMe::PmergeMe(){
    this->_args = NULL;
    this->_nArgs = 0;
}

PmergeMe::PmergeMe(PmergeMe const &to_copy){
    this->_nArgs = 0;
    this->_args = NULL;
    *this = to_copy;
}

PmergeMe::~PmergeMe(){
    if(this->_args != NULL)
        delete [] this->_args;
}

// OVERLOADING

PmergeMe &PmergeMe::operator=(PmergeMe const &to_equal){
    if(this->_nArgs > 0)
        delete [] this->_args;
    this->_list = to_equal._list;
    this->_vector = to_equal._vector;
    this->_nArgs = 0;
    if(to_equal._nArgs > 0){
        this->_args = new std::string[to_equal._nArgs + 1];
        for(unsigned int i = 0; i < to_equal._nArgs; i++)
            this->_args[i] = to_equal._args[i];
        this->_nArgs = to_equal._nArgs;
    }
    else
        this->_args = NULL;
    return(*this);
}

// ALGORITHMS

std::vector<unsigned int> PmergeMe::mergeInsert(std::vector<unsigned int> to_sort){
    // Insert algorithm
    if(to_sort.size() < 180){
        unsigned int len = to_sort.size();
        for(unsigned int i = 0; i < len; i++){
            unsigned int key = to_sort[i];
            int j = i - 1;
            while(j >= 0 && to_sort[j] > key){
                to_sort[j + 1] = to_sort[j];
                j--;
            }
            to_sort[j + 1] = key;
        }
        return to_sort;
    }

    // Merge algorithm
    std::vector<unsigned int>::iterator half = to_sort.begin() + (to_sort.size() / 2);
    std::vector<unsigned int> left(to_sort.begin(), half);
    std::vector<unsigned int> right(half, to_sort.end());

    // Split in two recursively
    left = PmergeMe::mergeInsert(left);
    right = PmergeMe::mergeInsert(right);

    // Merges the two vectors recursively
    std::vector<unsigned int> result(to_sort.size());
    std::merge(left.begin(), left.end(), right.begin(), right.end(), result.begin());

    return result;
}

std::list<unsigned int> PmergeMe::mergeInsert(std::list<unsigned int> to_sort){
    // Insert algorithm
    if(to_sort.size() < 180){
        std::list<unsigned int>::iterator i, j, k;
        for(i = ++to_sort.begin(); i != to_sort.end(); i++){
            unsigned int key = *i;
            j = i;
            k = i;
            --j;
            while(k != to_sort.begin() && *j > key){
                *k = *j;
                j--;
                k--;
            }
            *k = key;
        }
        return to_sort;
    }

    // Merge algorithm
    std::list<unsigned int>::iterator half = to_sort.begin();
    std::advance(half, to_sort.size() / 2);
    std::list<unsigned int> left(to_sort.begin(), half);
    std::list<unsigned int> right(half, to_sort.end());

    // Split in two recursively
    left = PmergeMe::mergeInsert(left);
    right = PmergeMe::mergeInsert(right);

    // Merges the two lists recursively
    std::list<unsigned int> result(to_sort.size());
    std::merge(left.begin(), left.end(), right.begin(), right.end(), result.begin());

    return result;
}

// METHODS

bool PmergeMe::setUp(int argc, char **argv){
    if(argc < 2)
        return false;

    // Create arguments
    if(this->_nArgs > 0)
        delete [] this->_args;
    this->_args = new std::string[argc];
    for(int i = 1; i < argc; i++){
        std::string token(argv[i]);
        this->_args[i - 1] = token;
        this->_nArgs++;
    }

    // Check arguments
    for(unsigned int i = 0; i < this->_nArgs; i++){
        trimStr(this->_args[i], '0');
        if(isNumber(this->_args[i]) == false
            || this->_args[i].size() > 10
            || static_cast<long>(atol(this->_args[i].c_str())) > std::numeric_limits<int>::max())
            return false;
    }

    return true;
}

void PmergeMe::run(void){
    this->printSequence("Before: ");
    if(this->_nArgs < 2){
        this->printSequence("After: ");
        return ;
    }

    // Fill vector and list
    for(unsigned int i = 0; i < this->_nArgs; i++){
        this->_vector.push_back((unsigned int)atoi(this->_args[i].c_str()));
        this->_list.push_back((unsigned int)atoi(this->_args[i].c_str()));
    }

    // Sort vector with merge
    clock_t vec_start = clock();
    this->_vector = PmergeMe::mergeInsert(this->_vector);
    clock_t vec_end = clock();

    // Sort list with merge
    clock_t list_start = clock();
    this->_list = PmergeMe::mergeInsert(this->_list);
    clock_t list_end = clock();

    // Update arguments to print them
    for(unsigned int i = 0; i < this->_nArgs; i++){
        std::string token(std::to_string(static_cast<int>(this->_vector[i])));
        this->_args[i] = token;
    }
    this->printSequence("After: ");

    // PRINT TIME OF VECTOR
    std::cout << "Time to process a range of " << this->_nArgs;
    std::cout << " elements with std::vector<unsigend int> : ";
    std::cout << std::fixed << std::setprecision(5) << (static_cast<double>(vec_end - vec_start) / CLOCKS_PER_SEC * 1000000.0);
    std::cout << " us" << std::endl;

    // PRINT TIME OF LIST
    std::cout << "Time to process a range of " << this->_nArgs;
    std::cout << " elements with std::list<unsigend int> : ";
    std::cout << std::fixed << std::setprecision(5) << (static_cast<double>(list_end - list_start) / CLOCKS_PER_SEC * 1000000.0);
    std::cout << " us" << std::endl;

    return ;
}
