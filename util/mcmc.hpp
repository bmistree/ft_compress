#ifndef __MCMC_HPP__
#define __MCMC_HPP__

#include <math.h>
#include <stdlib.h>

#include "cost_functions.hpp"


template <class ToFindCostOfClass>
class MCMC
{
public:
    MCMC(CandidateProducer<ToFindCostOfClass>& candidate_producer,
        float acceptance_parameter)
     : _candidate_producer(candidate_producer),
       _acceptance_parameter(acceptance_parameter)
    {}

    ~MCMC()
    { /** No cleanup to perform */ }
    
    void iterate(int num_iters=1) 
    {
        float current_cost = _candidate_producer.cost_current();

        for (int i = 0; i < num_iters; ++i)
        {
            // generates a number from 0.0 to 1.0
            float random =
                static_cast <float> (rand()) / static_cast <float> (RAND_MAX);

            float candidate_cost =
                _candidate_producer.generate_candidate_get_cost();
            
            // note that we are not guaranteed that acceptance_probability will
            // be < 1.  Order of if statement below handles this case.
            float acceptance_probability =
                exp(-_acceptance_parameter* candidate_cost/current_cost);

            // if random number is less than acceptance_probability, then use
            // candidate as new anchor point.  Note that acceptance_probability
            // may be greater than 1.  Order of statement handles this case
            // correctly.
            if (random < acceptance_probability)
            {
                current_cost = candidate_cost;
                _candidate_producer.accept_candidate();
            }
            else
            {
                _candidate_producer.reject_candidate();
            }
        }
    }
    
private:
    CandidateProducer<ToFindCostOfClass>& _candidate_producer;
    float _acceptance_parameter;
};
#endif
