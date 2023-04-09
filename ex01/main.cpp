/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apena-ba <apena-ba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/09 05:46:11 by apena-ba          #+#    #+#             */
/*   Updated: 2023/04/09 07:48:20 by apena-ba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RPN.hpp"

int returnErr(void){
    std::cerr << "Error" << std::endl;
    return(1);
}

// void ft(void){system("leaks -q RPN");}

int main(int argc, char **argv){
    // atexit(ft);
    RPN converter;

    if(converter.setUp(argc, argv) == false)
        return(returnErr());
    else if(converter.run() == false)
        return(returnErr());

    return(0);
}
