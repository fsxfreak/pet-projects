#include <iostream>

#include "state.hpp"
#include "chain.hpp"
#include "passGenChain.hpp"

int main(int argc, char* argv[]) 
{
    mgen::PassGenChain<char> chain(' ', 'z');
    chain.buildTransitions();
    for (int i = 0; i < 50000; i++)
    {
        std::cout << chain.advance();
        //if (i % 5 == 0)
        //    std::cout << " ";
    }
    return 0;
}