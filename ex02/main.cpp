/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apena-ba <apena-ba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/09 08:39:46 by apena-ba          #+#    #+#             */
/*   Updated: 2023/04/09 19:30:14 by apena-ba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PmergeMe.hpp"

int returnErr(void){
    std::cerr << "Error" << std::endl;
    return(1);
}

// void ft(void){system("leaks -q PmergeMe");}

int main(int argc, char **argv){
    // atexit(ft);
    PmergeMe sorter;

    if(sorter.setUp(argc, argv) == false)
        return(returnErr());
    sorter.run();

    return 0;
}
