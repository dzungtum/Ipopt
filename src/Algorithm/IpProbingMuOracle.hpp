// Copyright (C) 2004, 2006 International Business Machines and others.
// All Rights Reserved.
// This code is published under the Eclipse Public License.
//
// Authors:  Carl Laird, Andreas Waechter     IBM    2004-08-13

#ifndef __IPPROBINGMUORACLE_HPP__
#define __IPPROBINGMUORACLE_HPP__

#include "IpMuOracle.hpp"
#include "IpPDSystemSolver.hpp"

namespace Ipopt
{

/** Implementation of the probing strategy for computing the
 *  barrier parameter.
 */
class ProbingMuOracle: public MuOracle
{
public:
   /**@name Constructors/Destructors */
   ///@{
   /** Constructor */
   ProbingMuOracle(
      const SmartPtr<PDSystemSolver>& pd_solver
   );

   /** Destructor */
   virtual ~ProbingMuOracle();
   ///@}

   /** overloaded from AlgorithmStrategyObject */
   virtual bool InitializeImpl(
      const OptionsList& options,
      const std::string& prefix
   );

   /** Method for computing the value of the barrier parameter that
    *  could be used in the current iteration (using Mehrotra's
    *  probing heuristic).
    */
   virtual bool CalculateMu(
      Number  mu_min,
      Number  mu_max,
      Number& new_mu
   );

   static void RegisterOptions(
      SmartPtr<RegisteredOptions> roptions
   );

private:
   /**@name Default Compiler Generated Methods
    * (Hidden to avoid implicit creation/calling).
    *
    * These methods are not implemented and
    * we do not want the compiler to implement
    * them for us, so we declare them private
    * and do not define them. This ensures that
    * they will not be implicitly created/called.
    */
   ///@{
   /** Default Constructor */
   ProbingMuOracle();

   /** Copy Constructor */
   ProbingMuOracle(
      const ProbingMuOracle&
   );

   /** Default Assignment Operator */
   void operator=(
      const ProbingMuOracle&
   );
   ///@}

   /** Pointer to the object that should be used to solve the
    *  primal-dual system.
    */
   SmartPtr<PDSystemSolver> pd_solver_;

   /** Auxiliary function for computing the average complementarity
    *  at a point, given step sizes and step
    */
   Number CalculateAffineMu(
      Number                alpha_primal,
      Number                alpha_dual,
      const IteratesVector& step
   );

   /** @name Algorithmic parameters */
   ///@{
   /** safeguarding upper bound on centering parameter sigma */
   Number sigma_max_;
   ///@}
};

} // namespace Ipopt

#endif
