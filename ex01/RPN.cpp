/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RPN.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apena-ba <apena-ba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/09 05:52:32 by apena-ba          #+#    #+#             */
/*   Updated: 2023/04/09 07:47:26 by apena-ba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RPN.hpp"

// CONSTRUCTORS AND DESTRUCTORS

RPN::RPN(){
    this->_tokens = NULL;
    this->_nTokens = 0;
}

RPN::RPN(RPN const &to_copy){
    this->_nTokens = 0;
    *this = to_copy;
}

RPN::~RPN(){
    if(this->_tokens != NULL)
        delete [] this->_tokens;
}

// OVERLOADING

RPN &RPN::operator=(RPN const &to_copy){
    this->_stack = to_copy._stack;
    if(this->_nTokens > 0)
        delete [] this->_tokens;
    this->_nTokens = 0;
    if(to_copy._nTokens > 0){
        this->_tokens= new std::string[to_copy._nTokens + 1];
        for(unsigned int i = 0; i < to_copy._nTokens; i++)
            this->_tokens[i] = to_copy._tokens[i];
        this->_nTokens = to_copy._nTokens;
    }
    else
        this->_tokens = NULL;
    return(*this);
}

// STATIC FUNCTIONS

bool RPN::isValidToken(std::string const &s){
    if(s.size() > 1)
        return false;
    if((s[0] < '0' || s[0] > '9')
        && isOperand(s) == false)
        return false;
    return true;
}

bool RPN::isOperand(std::string const &s){
    if(s[0] != '+' && s[0] != '-' 
        && s[0] != '*' && s[0] != '/')
        return false;
    return true;
}

std::string RPN::operate(int first, int second, std::string const &operand){
    int result = 0;
    if(operand == "-")
        result = first - second;
    else if(operand == "+")
        result = first + second;
    else if(operand == "*")
        result = first * second;
    else if(operand == "/")
        result = first / second;
    return std::to_string(result);
}

// METHODS

bool RPN::setUp(int argc, char **argv){
    unsigned int nArgs = 0;

    // Check setup
    if(argc != 2)
        return false;
    if(this->_nTokens > 0)
        delete [] this->_tokens;
    this->_nTokens = 0;

    // Read arguments
    std::string buff(argv[1]);
    std::stringstream args(buff);
    unsigned int x = 0;
    while(x < buff.size()){
        while(buff[x] == ' ')
            x++;
        while(buff[x] != ' ' && buff[x])
            x++;
        nArgs++;
    }

    // Create tokens
    this->_tokens = new std::string[nArgs + 1];
    unsigned int count = 0;
    buff.clear();
    while(1){
        std::getline(args, buff, ' ');
        if(buff.size() > 0){
            this->_nTokens++;
            this->_tokens[count++] = buff;
        }
        if(args.eof())
            break;
    }

    // Check valid tokens
    for (unsigned int i = 0; i < this->_nTokens; i++){
        if(RPN::isValidToken(this->_tokens[i]) == false)
            return false;
    }

    // Check number of operands and numbers
    unsigned int nOperands = 0;
    unsigned int nNumbers = 0;
    for (unsigned int i = 0; i < this->_nTokens; i++){
        if(this->_tokens[i] == "+" || this->_tokens[i] == "-"
            || this->_tokens[i] == "*" || this->_tokens[i] == "/")
            nOperands++;
        else
            nNumbers++;
    }
    if(nOperands + 1 != nNumbers)
        return false;
    return true;
}

bool RPN::run(void){
    int first;
    int second;

    for (unsigned int i = 0; i < this->_nTokens; i++){
        if(isOperand(this->_tokens[i]) == true){
            if(this->_stack.size() < 2)
                return false;
            first = atoi((this->_stack.top()).c_str());
            this->_stack.pop();
            second = atoi((this->_stack.top()).c_str());
            this->_stack.pop();
            this->_stack.push(RPN::operate(second, first, this->_tokens[i]));
        }
        else
            this->_stack.push(this->_tokens[i]);
    }
    std::cout << this->_stack.top() << std::endl;
    return true;
}
