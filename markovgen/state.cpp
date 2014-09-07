#include <array>
#include <algorithm>
#include <chrono>
#include <iostream>
#include <limits>
#include <random>

#include "state.hpp"

namespace mgen
{

const double DOUBLE_EPSILON = 0.000001;

template <class T>

std::mt19937 State<T>::randomGen(
    std::chrono::high_resolution_clock::now().time_since_epoch().count());

template <class T>
std::vector<State<T>*> State<T>::definedStates = std::vector<State<T>*>();

template <class T>
State<T> State<T>::construct(const T& state)
{
    State<T>* duplicate = nullptr;

    //Linear search should be fine for now. State spaces should not be too big.
    for_each (State<T>::definedStates.begin(), State<T>::definedStates.end(),
        [&] (State<T>* definedState) {
            if (definedState->get() == state)
                duplicate = definedState;
        }
    );

    if (!duplicate)
        return State<T>(state);
        
    return *duplicate;
}

template <class T>
T State<T>::get() const { return state; }

template <class T>
T State<T>::next()
{
    if (transitions.size() <= 0 || transitions.back().second <= DOUBLE_EPSILON)
        return ++state;

    double prob = std::generate_canonical<double, 64>(randomGen);

    auto pair = std::make_pair(T(), prob);
    auto it = std::lower_bound(transitions.begin(), transitions.end(), pair,
        [] (const std::pair<T, double>& left 
          , const std::pair<T, double>& right) -> bool {
            return left.second < right.second;
        }
    );

    return it->first;
}

template <class T>
void State<T>::setTransitions(std::vector<std::pair<T, double> > trans)
{
    transitions = trans;

    //zero out probabilities
    for_each (transitions.begin(), transitions.end(),
        [] (std::pair<T, double>& trans) {
            trans.second = 0.0;
        }
    );

    //make probability ranges by summing probabilities of all previous elements
    for (int i = 0; i < transitions.size(); ++i)
    {
        for (int j = 0; j <= i; ++j)
        {
            transitions[i].second += trans[j].second;
        }
    }
    double total = transitions.back().second;

    //normalize the vector (make it add to 1)
    if (total >= DOUBLE_EPSILON)
    {
        std::for_each (transitions.begin(), transitions.end(),
            [&] (std::pair<T, double>& trans) {
                trans.second /= total;
            }
        );
    }
}

template <class T>
State<T>::~State()
{
    for (auto it =  State<T>::definedStates.begin()
            ; it != State<T>::definedStates.end()
          ; ++it)
    {
        if (*it == this)
        {
            State<T>::definedStates.erase(it);
            break;
        }
    }
}

template <class T>
State<T>::State(const T& state)
    : state{state}
{
    definedStates.push_back(this);
}

//More template definitions should be added if more types are needed.
template class State<char>;

} //mgen::
