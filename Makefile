CFLAGS= -lstdc++ -std=c++17 -Wall -Werror -Wextra
TEST= -lgtest tests.cc
NAME_TEST=-o tests
CC=gcc

all: install

install:
	@cd calc_2/ && qmake && make && make clean && rm -rf MakeFile
	@open calc_2/calc_2.app

uninstall:
	@rm -rf calc_2/calc_2.app

clean:
	@rm -rf tests
	@rm -rf Archive_Calc_v2.0
	@rm -rf Archive_Calc_v2.0.tgz

dvi:
	@open dvi.txt

dist:
	@rm -rf Archive_Calc_v2.0/
	@mkdir Archive_Calc_v2.0/
	@mv ./calc_2/calc_2.app Archive_Calc_v2.0/
	@tar cvzf Archive_Calc_v2.0.tgz Archive_Calc_v2.0/
	@rm -rf Archive_Calc_v2.0/

tests: clean
	@$(CC) $(CFLAGS) $(TEST) calc_2/modelcalc.cc calc_2/modelvalidation.cc $(NAME_TEST)
	@./tests
