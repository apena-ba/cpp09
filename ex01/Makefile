NAME = RPN

CXX = c++

CXXFLAGS = -Wall -Wextra -Werror -std=c++98

SRC = main.cpp RPN.cpp

OBJ = $(SRC:.cpp=.o)

all: $(NAME)

$(NAME): $(OBJ)
	@$(CXX) $(CXXFLAGS) -o $(NAME) $(OBJ)
	@echo "\n ℂ✚✚ Program compiled ✅ \n"

$(OBJ): $(SRC)
	@$(CXX) $(CXXFLAGS) -c $(SRC)
	@echo "\n ⚙️  Objects made ✅ \n"

clean:
	@rm -rf $(OBJ)
	@echo "\n 🧨 Objects cleaned ✅ \n"

fclean: clean
	@rm -rf $(NAME)
	@echo "\n 💥 Executable destroyed ✅ \n"

re: fclean all

.PHONY: all fclean clean re