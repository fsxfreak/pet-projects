#ifndef STATE_HPP
#define STATE_HPP

#include <vector>
#include <utility>
#include <random>

namespace mgen 
{

template <class T>
class State 
{
public:
    /**
     * No duplicate states are allowed. Will check against definedStates,
     * before calling constructor.
     */
    static State construct(const T& state);
    T get() const;

    /**
     * Determines the next state by looking through the probabilities in the
     * State<T>::transitions vector and selecting one at random. 
     */
    T next();

    /**
     * Transitions should be built for this object before it is used. If no
     * transitions are present, when State<T>::next() is called, for example,
     * the class will return a default value.
     */
    void setTransitions(std::vector<std::pair<T, double> > transitions);
    ~State();
    
    /**
     * Ensures no duplicate states.
     */
    static std::vector<State<T>*> definedStates;

    /**
     * Stores the ranges of probabilities to go to a different state.
     * transitions[i].second stores the *maximum* range of the probability.
     * e.g. transition[0].second == 0.05; Probability range - [0 - 0.05)
     */
    std::vector<std::pair<T, double> > transitions;
private:
    State(const T& state);

    /**
     * Stores one state of the state space.
     */
    T state;

    /**
     * Source of randomness.
     */
    static std::mt19937 randomGen;
};

} //mgen:: 

#endif