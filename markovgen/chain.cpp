#include <algorithm>
#include <chrono>
#include <iostream>
#include <vector>
#include <utility>

#include "chain.hpp"
#include "state.hpp"

namespace mgen
{

template <class T>
std::mt19937 Chain<T>::randomGen(
    std::chrono::high_resolution_clock::now().time_since_epoch().count() - 20);

template <class T>
Chain<T>::Chain(const T& from, const T& to)
    : currentState()
{
    for (T i = from; i <= to; i++)
    {
        stateSpace.push_back(State<T>::construct(i));
    }
}

template <class T>
T Chain<T>::advance()
{
    if (!currentState) 
    {
        //just start with a random state for now
        //TODO start by starting probabilities
        double prob = std::generate_canonical<double, 64>(randomGen);
        int index = static_cast<int>(prob * stateSpace.size());
        currentState = &stateSpace[index];

        return currentState->get();
    }
    T next = currentState->next();
    
    for (int i = 0; i < stateSpace.size(); i++)
    {
        if (stateSpace[i].get() == next)
        {
            currentState = &stateSpace[i];
            break;
        }
    }

    return next;   
}

template class Chain<char>;

} //mgen::