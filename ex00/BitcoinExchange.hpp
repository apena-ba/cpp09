/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apena-ba <apena-ba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/04 16:55:15 by apena-ba          #+#    #+#             */
/*   Updated: 2023/05/13 19:58:48 by apena-ba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BITCOINEXCHANGE_HPP
#define BITCOINEXCHANGE_HPP

#include <iostream>
#include <map>
#include <fstream>
#include <string>
#include <cstdlib>
#include <sstream>
# include <limits.h>

class BitcoinExchange{
    private:
        std::map<std::string, std::string>  _map;
        std::string                         *_file;
        unsigned int                        _fileSize;
        void formatDate(std::string &key);
    public:
        BitcoinExchange();
        BitcoinExchange(BitcoinExchange const &to_copy);
        ~BitcoinExchange();
        
        BitcoinExchange &operator=(BitcoinExchange const &to_equal);

        // UTILS METHODS
        void takeDateBack(std::string &to_change);
        // SETUP METHODS
        bool setUp(int argc, char **argv);
        bool getDataBase(std::string const &name);
        bool getFile(std::ifstream &infile);
        
        // RUN METHODS
        bool checkLine(std::string const &line);
        void showExchange(std::string const &line);
        void runExchange();

        // STATIC METHODS
        static bool checkKey(std::string const &key, std::string const &line);
        static bool checkValue(std::string const &value);
};

#endif