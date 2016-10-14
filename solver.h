#pragma once

#include <set>
#include <algorithm>
#include <map>
#include "rule.h"

enum critere{aucun, complexite_premisses, plus_de_premisses, recence_utilisation_regle, faits_plus_recents};

class Solver
{
	private:
		std::set <std::string> m_knowledge;
		std::map<unsigned int, std::set<Rule> > m_packedRules;
		std::set <Rule> m_rules;
		std::vector <Rule> m_subRules;
	public:
		Solver (const std::set <std::string> & knowledge, const std::set <Rule> & rules, critere _critere):
			m_knowledge (knowledge),
			m_rules (rules)
		{
			set_critere(aucun);
		}

		void addRuleToPacket(unsigned int _i, Rule _rule){
			m_packedRules[_i].insert(_rule);
		}

		Solver (const Solver & s):
			m_knowledge (s.m_knowledge),
			m_rules (s.m_rules)
		{}

		~Solver()
		{}

		void set_critere(critere _c){
			m_subRules.clear();
			switch (_c){
				case aucun:{
					for(auto it = m_rules.begin(); it!=m_rules.end();++it){
						m_subRules.push_back(*it);
					}
					break;
				}
				case complexite_premisses:{

					break;
				}
				case plus_de_premisses:{
					for(auto it = m_rules.begin(); it!=m_rules.end();++it){
						
					}
					for(auto it = m_subRules.begin();it!=m_subRules.end();++it){
						std::cout << (*it).get_premises().size() << *it << std::endl;
					}
					break;

				}
				case recence_utilisation_regle:{

					break;
				}
				case faits_plus_recents:{
						
					break;
				}

			}
		}

		void forward_chaining ()
		{
			int nbinf = 0;
			bool dec,inf=true;

			while ( inf ){
				inf = false;
				for (auto r : m_subRules ) // pour toute règle dans la B.R.
				{
				
					dec = true;
					for (auto p : r.get_premises() ) // pour chaque prémisse de la règle
					{
						
						if ( std::find ( m_knowledge.begin(), m_knowledge.end(), p->to_string()) == m_knowledge.end() ){
							// si la prémisse n'est pas dans la base de faits
								dec = false;
							}
						if ( dec )
						{
							auto c = r.get_conclusion();
							
							auto is_in_conclusion = std::find ( m_knowledge.begin(), m_knowledge.end(), c->to_string() );
							if ( is_in_conclusion == m_knowledge.end() )
								inf = m_knowledge.insert(c->to_string()).second ? true : inf;	// insertion de la conclusion dans la base de faits

							++nbinf;

						}// fin si
					} // fin pour prémisses
			
				}

				/**
				 * AFFICHAGE B.F.
				 */
				std::cout << "Knowledge base after forward chaining:" << std::endl;
				for (auto k : m_knowledge )
				{
					std::cout << k << std::endl;
				}
				
				// fin pour règles

			}
		}
		/*
		void forward_chaining_packet ()
		{
			int nbinf = 0;
			bool dec,inf=true;

			while ( inf ){
			inf = false;
				
				for(auto s: m_packedRules){
					for (auto r : s.second ) // pour toute règle dans la B.R.
					{
					
						dec = true;
						for (auto p : r.get_premises() ) // pour chaque prémisse de la règle
						{
							
							if ( std::find ( m_knowledge.begin(), m_knowledge.end(), p->to_string()) == m_knowledge.end() ){
								// si la prémisse n'est pas dans la base de faits
									dec = false;
								}

						} // fin pour prémisses
						if ( dec ){
							auto c = r.get_conclusion();							
							auto is_in_conclusion = std::find ( m_knowledge.begin(), m_knowledge.end(), c->to_string() );
							if ( is_in_conclusion == m_knowledge.end()){
								inf =m_knowledge.insert(c->to_string()).second	// insertion de la conclusion dans la base de faits
							}
							++nbinf;

						}// fin si				
					}


					std::cout << "Knoweledge base after forward chaining:" << std::endl;
					for (auto k : m_knowledge )
					{
						std::cout << k << std::endl;
					}
					
					std::cout << "Fin de traitement pour le packet de règles" << std::endl;
					// fin pour règles
				}
			}
		}
		*/
		bool backward_chaining (const std::string & conclusion)
		{
			if ( std::find ( m_knowledge.begin(), m_knowledge.end(), conclusion ) != m_knowledge.end() ){
			// la conclusion est dans la base des faits
				return true;
			}
			bool dem=false,inf=true;
			m_knowledge.insert(conclusion);
			std::set<std::string> Kcopy = m_knowledge,K2=m_knowledge;
			while(inf && !K2.empty()){
				inf=false;
				for (auto r : m_subRules){
					dem = false;
					auto c = r.get_conclusion();
					if ( c->to_string() == *(K2.begin()) )
					// si la règle a la même conclusion
					{
						std::cout << "regle trouvé avec la conclusion " << *(K2.begin()) << std::endl << "Premisses:";
						for(auto p : r.get_premises()){
							std::cout << p->to_string() << " ";
						}
						std::cout << std::endl;
						dem = true;
						
					}
					if ( !dem )
					{
					/*	std::string valuation;
						std::cout << "valuation ? (vrai, faux, inconnu)" << std::endl;
						std::cin >> valuation;
						
						if (valuation == "faux")
						{
							dem = false;
						}

						if (valuation == "inconnu" )
							return false;
							*/
					}else{
						auto prems = r.get_premises();
						for(auto prem: prems){
							//std::cout << "inserting k = " << prem->to_string() << " using rule " << r.get_name() << " depuis la conclusion " << r.get_conclusion()->to_string() << std::endl;
							inf = (m_knowledge.insert(prem->is_true() ? prem->to_string() : "-" + prem->to_string()).second) ? true : inf;
							K2.insert(prem->is_true() ? prem->to_string() : "-" + prem->to_string());
						}
					}
				}
				K2.erase(K2.begin());
				
			}
			std::cout << "New knowledge backward_chaining-deduced from the conclusion \"" << *(K2.begin()) << "\":" << std::endl;
			std::vector<std::string> newK;
			std::set_difference(m_knowledge.begin(),m_knowledge.end(),Kcopy.begin(),Kcopy.end(), back_inserter(newK));
			for (auto k : newK)
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
