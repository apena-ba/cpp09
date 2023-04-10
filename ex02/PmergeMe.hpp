/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apena-ba <apena-ba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/09 08:02:46 by apena-ba          #+#    #+#             */
/*   Updated: 2023/04/09 22:03:42 by apena-ba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PMERGEME_HPP
#define PMERGEME_HPP

#include <iomanip>
#include <iostream>
#include <vector>
#include <list>
#include <sstream>
#include <string>
#include <ctime>
#include <iterator>

class PmergeMe{
    private:
        std::vector<unsigned int> _vector;
        std::list<unsigned int> _list;
        std::string *_args;
        unsigned int _nArgs;
    public:
        PmergeMe();
        PmergeMe(PmergeMe const &to_copy);
        ~PmergeMe();
        
        PmergeMe &operator=(PmergeMe const &to_equal);

        // METHODS
        void printSequence(std::string const &line);
        bool setUp(int argc, char **argv);
        void run(void);

        // STATIC METHODS
        static std::vector<unsigned int> mergeInsert(std::vector<unsigned int> to_sort);
        static std::list<unsigned int> mergeInsert(std::list<unsigned int> to_sort);
};

#endif