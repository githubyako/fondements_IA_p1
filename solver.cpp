#include "solver.h"


bool compNbPremises (Rule const * r1, Rule const * r2){
	return (r1->get_premises().size() > r2->get_premises().size());
}

Solver::Solver (const std::set <std::string> & knowledge, const std::set <Rule> & rules, critere _critere):
m_knowledge (knowledge),m_rules (rules){
	set_critere(aucun);
}

Solver::Solver (Solver const & _s)
:m_knowledge (_s.m_knowledge),m_rules (_s.m_rules){
}

Solver::~Solver(){
}


void Solver::set_critere(critere _c){
	m_critere = _c;
	m_subRules.clear();
	for(auto it=m_rules.begin();it!=m_rules.end();++it){
		Rule const & r = *it;
		m_subRules.push_back(&r);
	}
	switch (_c){
		case aucun:{		
			break;
		}
		case complexite_premisses:{
			break;
		}
		case plus_de_premisses:{
			std::sort(m_subRules.begin(),m_subRules.end(),compNbPremises);
			break;
		}
	}
}

void Solver::insert_rule(Rule const & _r){
	m_rules.insert (_r);
}

void Solver::forward_chaining(){
	set_critere(m_critere);
	bool dec,inf=true;
	while ( inf ){
		std::vector<Boolean*> newfacts;
		inf = false;
		for (auto r=m_subRules.begin();r!=m_subRules.end(); ) // pour toute règle dans la B.R.
		{
			dec = (std::find( m_knowledge.begin(), m_knowledge.end(), (*r)->get_conclusion()->to_string()) == m_knowledge.end()) ? true : false;
			for (auto p : (*r)->get_premises() ) // pour chaque prémisse de la règle
			{
				if ( std::find ( m_knowledge.begin(), m_knowledge.end(), p->to_string()) == m_knowledge.end()){
					// si les prémisses ne sont pas dans la BF ou que la conclusion y est déjà, alors on skip la règle pour cette boucle-ci
					dec = false;
					break;
				}
			}
			if ( dec ){
				auto c = (*r)->get_conclusion();		
				auto c_is_in_K = std::find ( m_knowledge.begin(), m_knowledge.end(), c->to_string() ) == m_knowledge.end();
				if (c_is_in_K){
					inf = m_knowledge.insert(c->to_string()).second ? true : inf;	// insertion de la conclusion dans la base de faits si elle n'y est pas déjà
				}
				switch (m_critere){
					case recence_utilisation_regle:{
						Rule const * rc = *r;
						m_subRules.erase(r);
						m_subRules.insert(m_subRules.begin(),rc);
						break;
					}
					case faits_plus_recents:{
						for(auto it=m_subRules.begin();it!=m_subRules.end();++it){
							if((*it)->get_conclusion()==c){
								Rule const * rc = *it;
								it = m_subRules.erase(it);
								m_subRules.insert(m_subRules.begin(),rc);
							}
						}
						break;
					}
				}
				r = m_subRules.begin();
			}else ++r;
		}
		/**
		 * AFFICHAGE B.F.
		 */

		// fin pour règles
	}
	std::cout << "Knowledge base after forward chaining:" << std::endl;
	for (auto k : m_knowledge )
	{
		std::cout << k << std::endl;
	}
}


bool Solver::backward_chaining (const std::string & conclusion){
	set_critere(m_critere);
	if ( std::find ( m_knowledge.begin(), m_knowledge.end(), conclusion ) != m_knowledge.end() ){
		// la conclusion est dans la base des faits
		return true;
	}

	bool dem=false,inf=true;
	m_knowledge.insert(conclusion);
	std::set<std::string> Kcopy = m_knowledge,K2=m_knowledge;
	
	while(inf && !K2.empty()){
		inf=false;
		for (auto r=m_subRules.begin();r!=m_subRules.end();){
			dem = true;
			auto c = (*r)->get_conclusion();
			if ( c->to_string() == *(K2.begin())){	// si la règle a la même conclusion
				dem = true;
				bool allpr=true;
				for(auto pr : (*r)->get_premises()){
					if(std::find ( m_knowledge.begin(), m_knowledge.end(), pr->to_string()) == m_knowledge.end()){
						allpr=false;
						break;
					}
				}
				dem = !allpr;	
			}else{
				++r;
				continue;
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
				++r;
			}else{
				auto prems = (*r)->get_premises();
				for(auto prem: prems){
					inf = (m_knowledge.insert(prem->is_true() ? prem->to_string() : "-" + prem->to_string()).second) ? true : inf;
					K2.insert(prem->is_true() ? prem->to_string() : "-" + prem->to_string());
				}
				switch (m_critere){
					case recence_utilisation_regle:{
						Rule const * rc = *r;
						m_subRules.erase(r);
						m_subRules.insert(m_subRules.begin(),rc);
						break;
					}
					case faits_plus_recents:{
						for(auto it=m_subRules.begin();it!=m_subRules.end();++it){
							if((*it)->get_conclusion()==c){
								Rule const * rc = *it;
								it = m_subRules.erase(it);
								m_subRules.insert(m_subRules.begin(),rc);
							}
						}
						break;
					}
				}
				r = m_subRules.begin();
			}
		}
		K2.erase(K2.begin());
	}
	std::cout << "New knowledge backward_chaining-deduced from the conclusion \"" << conclusion << "\":" << std::endl;
	std::vector<std::string> newK;
	std::set_difference(m_knowledge.begin(),m_knowledge.end(),Kcopy.begin(),Kcopy.end(), back_inserter(newK));
	for (auto k : newK)
	{
		std::cout << k << std::endl;
	}
	return dem;
}