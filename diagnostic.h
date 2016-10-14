#pragma once

#include "solver.h"
#include "literal.h"
#include "true.h"
#include "false.h"

class Diagnostic : public Solver
{

	public:

		
		Diagnostic (const std::set <std::string> & knowledge, critere _critere=aucun):
			Solver (knowledge, std::set<Rule> (), _critere)
		{
			// REGLES A DEFINIR
			// REGLES DANS FICHIER ??? (ifstream)
			
			std::set <Boolean *> premises_r0;
			premises_r0.insert (new Literal ("asthénie", true));
			premises_r0.insert (new Literal ("fievre", true));
			Rule r0 ("GRIPPE TYPE A", premises_r0, new Literal ("grippe",true));
			
			std::set <Boolean *> premises_r1;
			premises_r1.insert (new Literal ("température_elevée", true));
			Rule r1 ("FIEVRE DÛE A REPONSE IMMUNITAIRE", premises_r1, new Literal ("fievre",true));
			
			std::set <Boolean *> premises_r2;
			premises_r2.insert (new True());
			Rule r2 ("SUJET SAIN", premises_r2, new Literal ("sain", true));

			std::set <Boolean *> premises_r3;
			premises_r3.insert (new Literal ("sain",true));
			Rule r3 ("?", premises_r3, new Literal ("malade", false));

			std::set <Boolean *> premises_r4;
			premises_r4.insert (new Literal ("malade", true));
			Rule r4 ("??", premises_r4, new Literal ("sain", false));


			insert_rule (r0);
			insert_rule (r1);
			insert_rule(r2);
			insert_rule (r3);
			insert_rule (r4);

			addRuleToPacket(0,r0);
			addRuleToPacket(0,r1);
			addRuleToPacket(1,r2);
			addRuleToPacket(1,r3);
			addRuleToPacket(2,r4);

		}
};