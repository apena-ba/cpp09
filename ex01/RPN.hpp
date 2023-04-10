/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RPN.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apena-ba <apena-ba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/09 05:47:17 by apena-ba          #+#    #+#             */
/*   Updated: 2023/04/09 20:03:36 by apena-ba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RPN_HPP
#define RPN_HPP

#include <stack>
#include <iostream>
#include <string>
#include <sstream>

class RPN{
    private:
        std::stack<std::string> _stack;
        std::string             *_tokens;
        unsigned int            _nTokens;
    public:
        RPN();
        RPN(RPN const &to_copy);
        ~RPN();

        RPN &operator=(RPN const &to_equal);

        // METHODS
        bool setUp(int argc, char **argv);
        bool run(void);

        // STATIC METHODS
        static bool isValidToken(std::string const &s);
        static bool isOperand(std::string const &s);
        static std::string operate(int first, int second, std::string const &operand);
};

#endif