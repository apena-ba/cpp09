/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apena-ba <apena-ba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/08 16:49:54 by apena-ba          #+#    #+#             */
/*   Updated: 2023/04/09 05:38:00 by apena-ba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "BitcoinExchange.hpp"

// UTILS FUNCTIONS

void trimStr(std::string &to_change, char c){
    unsigned int i = 0;
    while(to_change[i] == c)
        i++;
    if(i > 0)
        to_change.erase(0, i);
}

void trimStrR(std::string &to_change, char c){
    unsigned int i = to_change.size() - 1;
    while(to_change[i] == c)
        i--;
    if(i < to_change.size() - 1)
        to_change.erase(i + 1, to_change.size() - 1);
}

bool checkInt(std::string const &to_check){
    if(to_check.size() > 10)
        return false;
    long int conv = atol(to_check.c_str());
    if(conv > std::numeric_limits<int>::max())
        return false;
    return true;
}

bool returnErr(std::string const &error){
    std::cerr << "Error: " << error << std::endl;
    return false;
}

bool isNumStr(std::string const &s){
    if(s.size() < 1)
        return false;
    for(unsigned int i = 0; s[i]; i++){
        if(s[i] < '0' || s[i] > '9')
            return false;
    }
    return true;
}

// UTILS METHODS

void BitcoinExchange::takeDateBack(std::string &to_change){
    std::string year = to_change.substr(0, to_change.find("-"));
    //std::string month = to_change.substr(to_change.find("-"), to_change.find("-", to_change.find("-")+1)-1);
    std::string day = to_change.substr(to_change.rfind("-") + 1);

    // Find the two '-' and we extract tbe month using the difference
    // between the two positions -1 to take the '-' out
    unsigned int pos1 = to_change.find('-');
    unsigned int pos2 = to_change.find('-', pos1+1);
    std::string month = to_change.substr(pos1 + 1, pos2 - pos1 - 1);

    // Check if we have to descend year, month or day in a special way
    if(atoi(day.c_str()) == 1){
        if(atoi(month.c_str()) == 1){
            year = std::to_string(atoi(year.c_str()) - 1);
            month = std::to_string(12);
        }
        else
            month = std::to_string(atoi(month.c_str()) - 1);
        day = std::to_string(31);
    }
    else{
        day = std::to_string(atoi(day.c_str()) - 1);
        if((atoi(day.c_str())) > 0 && (atoi(day.c_str())) < 10)
            day.insert(day.begin(), '0');
    }

    // Create the new date
    std::string new_date(year);
    new_date.append("-").append(month).append("-").append(day);
    to_change = new_date;
}

// STATIC MEMBER FUNCTIONS

bool BitcoinExchange::checkKey(std::string const &key, std::string const &line){
    std::stringstream buff(key);
    std::string year;
    std::string month;
    std::string day;

    // Check year
    std::getline(buff, year, '-');
    if(buff.eof())
        return (returnErr("missing month and day => " + line + "."));
    if(isNumStr(year) == false)
        return (returnErr("bad year content => " + line + "."));
    trimStr(year, '0');
    if(checkInt(year) == false)
        return (returnErr("bad year content => " + line + "."));
    long num = static_cast<long>(atol(year.c_str()));
    if(num < 2009 || num > 2022)
        return (returnErr("year out of range [2009 - 2022] => " + line + "."));

    // Check month
    std::getline(buff, month, '-');
    if(buff.eof())
        return (returnErr("missing day => " + line + "."));
    if(isNumStr(month) == false)
        return (returnErr("bad month content => " + line + "."));
    trimStr(month, '0');
    if(checkInt(month) == false)
        return (returnErr("bad month content => " + line + "."));
    num = static_cast<long>(atol(month.c_str()));
    if(num < 1 || num > 12)
        return (returnErr("bad input => " + line + "."));

    // Check day
    std::getline(buff, day, '\0');
    if(isNumStr(day) == false)
        return (returnErr("bad day content => " + line + "."));
    trimStr(day, '0');
    if(checkInt(day) == false)
        return (returnErr("bad day content => " + line + "."));
    num = static_cast<long>(atol(day.c_str()));
    if(num < 1 || num > 31)
        return (returnErr("bad input => " + line + "."));
    return true;
}

bool BitcoinExchange::checkValue(std::string const &value){
    // Count posible meta characters
    unsigned int f_count = 0;
    unsigned int minus_count = 0;
    unsigned int dot_count = 0;
    if(value.size() < 1)
        return (returnErr("not a valid value."));
    for(unsigned int i = 0; value[i]; i++){
        if(value[i] < '0' || value[i] > '9'){
            if(value[i] != 'f' && value[i] != '-' && value[i] != '.')
                return returnErr("not a valid value.");
            else if(value[i] == 'f')
                f_count++;
            else if(value[i] == '-')
                minus_count++;
            else if(value[i] == '.')
                dot_count++;
        }
    }

    // Check possibilities
    if(f_count > 1 || (f_count == 1 && value[value.size() - 1] != 'f') || dot_count > 1)
        return returnErr("not a valid value.");
    else if(minus_count > 1 || (minus_count == 1 && value[0] != '-'))
        return returnErr("not a valid value.");
    else if(minus_count == 1)
        return returnErr("not a positive number.");

    // Check float or int
    if(dot_count > 0 || f_count > 0){
        double num = static_cast<double>(atof(value.c_str()));
        if(num > std::numeric_limits<float>::max())
            return returnErr("too large a number.");
    }
    else{
        long num = static_cast<long>(atol(value.c_str()));
        if(num > std::numeric_limits<int>::max())
            return returnErr("too large a number.");
    }
    return true;
}

// CONSTRUCTORS AND DESTRCUTORS

BitcoinExchange::BitcoinExchange(){
    this->_file = NULL;
    this->_fileSize = 0;
}

BitcoinExchange::BitcoinExchange(BitcoinExchange const &to_copy){*this = to_copy;}

BitcoinExchange::~BitcoinExchange(){
    if(this->_file != NULL)
        delete [] this->_file;
}

// OVERLOADING

BitcoinExchange &BitcoinExchange::operator=(BitcoinExchange const &to_equal){
    this->_map = to_equal._map;
    if(this->_fileSize != 0)
        delete [] this->_file;
    if(to_equal._file != NULL){
        this->_file = new std::string[to_equal._fileSize + 1];
        for(unsigned int i = 0; i < to_equal._fileSize; i++)
            this->_file[i] = to_equal._file[i];
        this->_fileSize = to_equal._fileSize;
    }
    else{
        this->_file = NULL;
        this->_fileSize = 0;
    }
    return(*this);
}

/* METHODS */

// SET UP METHODS

bool BitcoinExchange::getDataBase(std::string const &name){
    // Open the file
    std::ifstream       infile(name);

    if(infile.fail())
        return false;
    
    // Read file
    std::string         buff;
    std::getline(infile, buff, '\0');
    std::stringstream   hole_file(buff);

    // Create and assign keys and values
    while(1){
        std::getline(hole_file, buff, '\n');
        std::stringstream   buff_read(buff);
        std::string key;
        std::getline(buff_read, key, ',');
        if(buff.size() < 1)
            break;
        trimStr(key, ' ');
        trimStrR(key, ' ');
        std::string value;
        std::getline(buff_read, value, '\n');
        trimStr(value, ' ');
        trimStrR(value, ' ');
        this->_map[key] = value;
    }
    return true;
}

bool BitcoinExchange::getFile(std::ifstream &infile){
    std::string buff;
    std::string token;

    // Delete current file
    delete [] this->_file;
    this->_file = NULL;
    this->_fileSize = 0;
    
    // Read the file and check the first line
    std::getline(infile, buff, '\0');
    std::stringstream content(buff);
    std::string hole_file(buff);
    std::getline(content, buff, '\n');
    
    if(infile.fail() || buff != "date | value")
        return false;
    buff.clear();
    
    // Count lines in file
    unsigned int newlines = 0;
    for(unsigned int i = 0; hole_file[i]; i++){
        if(hole_file[i] == '\n')
            newlines++;
    }

    // Fill file content
    this->_file = new std::string[newlines + 1];
    unsigned int i = 0;
    while(i < newlines){
        std::getline(content, buff, '\n');
        this->_file[i] = buff;
        i++;
    }
    this->_fileSize += newlines;

    return true;
}

bool BitcoinExchange::setUp(int argc, char **argv){
    if(argc != 2)
        return (returnErr("could not open file."));
    std::string name = argv[1];
    std::ifstream   infile(name);
    if(!infile.is_open())
        return (returnErr("could not open file."));
    if(this->getFile(infile) == false)
        return (returnErr("error with file provided."));
    if(this->getDataBase("data.csv") == false)
        return (returnErr("error with database file."));
    return true;
}

// RUN METHODS

bool BitcoinExchange::checkLine(std::string const &line){
    std::stringstream buff(line);
    std::string key;
    std::string value;

    // Check key
    std::getline(buff, key, '|');
    if(buff.eof() || key[key.size() - 1] != ' ')
        return (returnErr("bad input => " + line + "."));
    key.erase(key.size() - 1);
    if(BitcoinExchange::checkKey(key, line) == false)
        return false;

    // Check value
    std::getline(buff, value, '\n');
    if(value.size() < 1)
        return (returnErr("missing value => " + line + "."));
    trimStr(value, ' ');
    trimStr(value, '0');
    trimStrR(value, ' ');
    if(BitcoinExchange::checkValue(value) == false)
        return false;
    return true;
}

void BitcoinExchange::showExchange(std::string const &line){
    std::stringstream buff(line);
    std::string key;
    std::string value;

    // Get key line
    std::getline(buff, key, '|');
    trimStr(key, ' ');
    trimStrR(key, ' ');
    std::string original_key(key);

    // Get value from line
    std::getline(buff, value, '\0');
    trimStr(value, ' ');
    trimStrR(value, ' ');

    // Find closest lower date
    std::map<std::string, std::string>::iterator it = this->_map.find(key);
    while(1){
        it = this->_map.find(key);
        if(it != this->_map.end())
            break;
        this->takeDateBack(key);
    }

    // Show exchange
    std::cout << original_key << " => " << value  << " = " << (atof(it->second.c_str()) * atof(value.c_str())) << std::endl;
}

void BitcoinExchange::runExchange(void){
    if(this->_fileSize < 1){
        returnErr("empty file.");
        return ;
    }
    for(unsigned int i = 0; i < this->_fileSize; i++){
        if(this->checkLine(this->_file[i]) == true)
            this->showExchange(this->_file[i]);
    }
}
