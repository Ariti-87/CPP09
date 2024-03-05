NAME		:= stl

#SOURCES_____________________________________________________________

SRCS		:=	main.cpp

#OBJECT______________________________________________________________

BUILD_DIR	:= .build
OBJS		:= $(SRCS:%.cpp=$(BUILD_DIR)/%.o)
DEPS		:= $(OBJS:.o=.d)

#FLAGS_______________________________________________________________

CXX			:= c++
CXXFLAGS	:= -Wall -Wextra -Werror -std=c++98 -g3 -MMD -MP
RM			:= rm -f
MAKEFLAGS	+= --no-print-directory
DIR_DUP		= mkdir -p $(@D)

#COLORS______________________________________________________________

GREEN	=	\033[0;32m
RED		=	\033[0;31m
WHITE	=	\033[0;97m
RESET	=	\033[0m
YELLOW 	=	\033[0;93m


#MAIN_RULE___________________________________________________________

all: $(NAME)

$(NAME): $(OBJS)
	@echo -n "$(YELLOW)Compiling	${WHITE}→	$(YELLOW)$(NAME)$(RESET) "
	@echo "$(GREEN)[ok]✓$(RESET)"
	$(CXX) $(OBJS) -o $(NAME)

#OBJECT_RULE_________________________________________________________

$(BUILD_DIR)/%.o: %.cpp
	$(DIR_DUP)
	$(CXX) $(CXXFLAGS) -c -o $@ $<

-include $(DEPS)

#CLEAN_RULE__________________________________________________________

clean:
	@echo -n "$(RED)Deleting	${WHITE}→	$(RED)$(NAME) object$(RESET) "
	$(RM) -r $(BUILD_DIR)
	@echo "$(GREEN)[ok]$(RED)✗$(RESET)"

fclean: clean
	@echo -n "$(RED)Deleting	${WHITE}→	$(RED)$(NAME) executable$(RESET) "
	$(RM) $(NAME)
	@echo "$(GREEN)[ok]$(RED)✗$(RESET)"

re: fclean all

#SPEC________________________________________________________________

.PHONY: all clean fclean re
.SILENT:
