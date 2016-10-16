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
		std::vector <Rule const *> m_subRules;
		critere m_critere;
	public:
		Solver (const std::set <std::string> & knowledge, const std::set <Rule> & rules, critere _critere);
		Solver (const Solver & _s);
		~Solver();

		void set_critere(critere _c);

		void forward_chaining ();
		bool backward_chaining (const std::string & conclusion);

		void insert_rule (const Rule & r);
};
