#ifndef CHAIN_HPP
#define CHAIN_HPP

#include <memory>
#include <random>
#include <vector>
#include "state.hpp"

namespace mgen 
{

template <class T>
class Chain
{
public:
    /**
     * Constructs the state space [from, to]. Types must have operator< and ++.
     */
    Chain(const T& from, const T& to);

    /**
     * Assigns the probability vectors to every state in the stateSpace.
     */
    virtual void buildTransitions() = 0;

    /**
     * Calls on the current state to advance to the next state.
     */
    virtual T advance() final;
protected:
    std::vector<State<T> > stateSpace;
    State<T>* currentState;
    static std::mt19937 randomGen;
};

} //mgen::

#endif
