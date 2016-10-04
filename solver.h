#pragma once

#include <set>
#include <algorithm>
#include "rule.h"
class Solver
{
	private:
		std::set <std::string> m_knowledge;
		std::set <Rule> m_rules;

	public:
		Solver (const std::set <std::string> & knowledge, const std::set <Rule> & rules):
			m_knowledge (knowledge),
			m_rules (rules)
		{}

		Solver (const Solver & s):
			m_knowledge (s.m_knowledge),
			m_rules (s.m_rules)
		{}

		~Solver()
		{}

		void forward_chaining ()
		{
			int nbinf = 0;
			bool dec;

			/*while ( inf )
			{*/
				//inf = false;
				
				for (auto r : m_rules ) // pour toute règle dans la B.R.
				{
				
					dec = true;
					for (auto p : r.get_premises() ) // pour chaque prémisse de la règle
					{
						
						if ( std::find ( m_knowledge.begin(), m_knowledge.end(), p->to_string()) == m_knowledge.end() )
							// si la prémisse n'est pas dans la base de faits
								dec = false;
							
						if ( dec )
						{
							auto c = r.get_conclusion();
							
							auto is_in_conclusion = std::find ( m_knowledge.begin(), m_knowledge.end(), c->to_string() );
							if ( is_in_conclusion == m_knowledge.end() )
								m_knowledge. insert (c->to_string());	// insertion de la conclusion dans la base de faits
							

							++nbinf;

						}// fin si
					} // fin pour prémisses
			
				}

				/**
				 * AFFICHAGE B.F.
				 */
				for (auto k : m_knowledge )
				{
					std::cout << k << std::endl;
				}
				
				// fin pour règles

			//}
		}
	

		bool backward_chaining (const std::string & conclusion)
		{
			bool dem;
			if ( std::find ( m_knowledge.begin(), m_knowledge.end(), conclusion ) != m_knowledge.end() )
			// la conclusion est dans la base des faits
				dem = true;

			for (auto r : m_rules)
			{
				auto c = r.get_conclusion();
				if ( c->to_string() == conclusion )
				// si la règle a la même conclusion
				{
					dem = true;
					
				}

				if ( !dem )
				{
					std::string valuation;
					std::cout << "valuation ? (vrai, faux, inconnu)" << std::endl;
					std::cin >> valuation;
					
					if (valuation == "faux")
					{
						dem = false;
					}

					if (valuation == "inconnu" )
						return false;
				}

				if ( dem )
					m_knowledge.insert ((dem ? "": "-")+conclusion);
			}
		
			for (auto k : m_knowledge)
			{
				std::cout << k << std::endl;
			}
			
			return dem;
		}


		void insert_rule (const Rule & r) 
		{
			m_rules.insert (r);
		}
};
