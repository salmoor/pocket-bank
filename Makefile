all: bs

bs: BankingSystem.cpp BankingSystem.h main.cpp
	g++ -Wall main.cpp BankingSystem.cpp BankingSystem.h -o BankingSystem