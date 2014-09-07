#ifndef PASS_GEN_CHAIN
#define PASS_GEN_CHAIN

#include "chain.hpp"

namespace mgen
{

template <class T>
class PassGenChain : public Chain<T>
{
public:
	PassGenChain(T from, T to);

	virtual void buildTransitions() final;
};

} //::mgen

#endif
