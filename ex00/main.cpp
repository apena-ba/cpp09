/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apena-ba <apena-ba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/04 16:54:46 by apena-ba          #+#    #+#             */
/*   Updated: 2023/04/09 05:06:09 by apena-ba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "BitcoinExchange.hpp"

//void ft(void){system("leaks -q btc");}

int main(int argc, char **argv)
{
    //atexit(ft);
    BitcoinExchange exchanger;
    BitcoinExchange teo(exchanger);

    if(exchanger.setUp(argc, argv) == false)
        return(1);
    exchanger.runExchange();
}
