﻿#pragma once
#include "GRB.h"
#include "LT.h"
#include "Log.h"

using namespace std;
#define MFST_TRACE_START(stream) stream << setw(4) << left << "Шаг:"\
							  << setw(20) << left << " Правило" \
							  << setw(30) << left << " Входная лента" \
							  << setw(20) << left << " Стек" << endl;
#define MFST_TRACE1(stream)	stream << setw(4) << left << ++FST_TRACE_n << ": "\
					     << setw(20) << left << rule.getCRule(rbuf, nrulechain)\
					     << setw(30) << left << getCLenta(lbuf, lenta_position)\
					     << setw(20) << left << getCSt(sbuf) << endl;
#define MFST_TRACE2(stream)	 stream << setw(4) << left << FST_TRACE_n << ": "\
					     << setw(20) << left << " "\
					     << setw(30) << left << getCLenta(lbuf, lenta_position)\
					     << setw(20) << left << getCSt(sbuf) << endl;
#define MFST_TRACE3(stream)	stream << setw(4) << left << ++FST_TRACE_n << ": "\
					     << setw(20) << left << " "\
					     << setw(30) << left << getCLenta(lbuf, lenta_position)\
					     << setw(20) << left << getCSt(sbuf) << endl;
#define MFST_TRACE4(c, stream)	stream << setw(4) << left << ++FST_TRACE_n << ": " << setw(20) << left << c << endl;
#define MFST_TRACE5(c, stream)	stream << setw(4) << left << FST_TRACE_n << ": " << setw(20) << left << c << endl;
#define MFST_TRACE6(c, k, stream)	stream << setw(4) << left << FST_TRACE_n << ": " << setw(20) << left << c << k << endl;
#define MFST_TRACE7(stream)	stream << setw(4) << left << state.lenta_position<< ": "\
					     << setw(20) << left << rule.getCRule(rbuf, state.nrulechain) << endl;
#define MFST_DIAGN_MAXSIZE	3*ERROR_MAXSIZE_MESSAGE
#define MFST_DIAGN_NUMBER	3
#define PARAMETER_MAX_SIZE 300	////
#include <stack>
typedef std::stack<short>	MFSTSTSTACK;			// Стек автомата

namespace MFST
{
	struct MfstState
	{
		short lenta_position;
		short nrule;
		short nrulechain;
		MFSTSTSTACK st;
		MfstState();
		MfstState(short pposition, MFSTSTSTACK pst, short pnrulechain);
		MfstState(short pposition, MFSTSTSTACK pst, short pnrule, short pnrulechain);
	};
	
	struct Mfst
	{
		enum RC_STEP
		{
			NS_OK,
			NS_NORULE,
			NS_NORULECHAIN,
			NS_ERROR,
			TS_OK,
			TS_NOK,
			LENTA_END,
			SURPRISE
		};

		struct MfstDiagnosis
		{
			short lenta_position;
			RC_STEP rc_step;
			short nrule;
			short nrule_chain;
			MfstDiagnosis();
			MfstDiagnosis(short plenta_position, RC_STEP prc_step, short pnrule, short pnrule_chain);
		} diagnosis[MFST_DIAGN_NUMBER];

		GRBALPHABET* lenta;
		short lenta_position;
		short nrule;
		short nrulechain;
		short lenta_size;
		GRB::Greibach grebach;
		LT::LexTable lexTable;
		MFSTSTSTACK st;
		std::stack<MfstState> storestate;
		Log::LOG log;

		Mfst();
		Mfst(LT::LexTable plex, GRB::Greibach pgrebach, Log::LOG log);
		char* getCSt(char* buf);
		char* getCLenta(char* buf, short pos, short n = 25);
		char* getDiagnosis(short n, char* buf);
		bool savestate();
		bool reststate();
		bool push_chain(GRB::Rule::Chain chain);
		RC_STEP step();
		bool start(Log::LOG);
		bool savediagnosis(RC_STEP pprc_step);
		void printrules(Log::LOG);

		struct Deducation
		{
			short size;
			short* nrules;
			short* nrulechains;
			Deducation() { size = 0; nrules = 0; nrulechains = 0; }
		} deducation;

		bool savededucation();
	};
}