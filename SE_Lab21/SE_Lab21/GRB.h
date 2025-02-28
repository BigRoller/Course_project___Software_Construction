﻿#pragma once
#define GRB_ERROR_SERIES	600
#define NS(n)	GRB::Rule::Chain::N(n)
#define TS(n)	GRB::Rule::Chain::T(n)
#define ISNS(n)	GRB::Rule::Chain::isN(n)
typedef short GRBALPHABET;				// Символы алфавита грамматики(терминалы > 0, нетерминалы < 0)
namespace GRB
{
	struct Rule
	{
		GRBALPHABET nn;
		int iderror;
		short size;
		struct Chain
		{
			short size;
			GRBALPHABET* nt;
			Chain() { size = 0; nt = 0; }
			Chain(short psize, GRBALPHABET s, ...);
			char* getCChain(char* b);
			static GRBALPHABET T(char t) { return GRBALPHABET(t); }
			static GRBALPHABET N(char n) { return -GRBALPHABET(n); }
			static bool isT(GRBALPHABET s) { return s > 0; }
			static bool isN(GRBALPHABET s) { return !isT(s); }
			static char alphabet_to_char(GRBALPHABET s) { return isT(s) ? char(s) : char(-s); }
		}*chains;
		Rule() { nn = 0x00; size = 0; }
		Rule(GRBALPHABET pnn, int iderror, short psize, Chain c, ...);
		char* getCRule(char* b, short nchain);
		short getNextChain(GRBALPHABET t, Rule::Chain& pchain, short j);
	};

	struct Greibach
	{
		short size;
		GRBALPHABET startN;
		GRBALPHABET stbottomT;
		Rule* rules;
		Greibach() { short size = 0; startN = 0; stbottomT = 0; rules = 0; }
		Greibach(GRBALPHABET pstartN, GRBALPHABET pstbottomT, short psize, Rule r, ...);
		short getRule(GRBALPHABET pnn, Rule& prule);
		Rule getRule(short n);
	};

	Greibach getGreibach();
}