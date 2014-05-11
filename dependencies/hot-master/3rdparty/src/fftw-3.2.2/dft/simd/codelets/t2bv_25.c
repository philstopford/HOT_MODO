/*
 * Copyright (c) 2003, 2007-8 Matteo Frigo
 * Copyright (c) 2003, 2007-8 Massachusetts Institute of Technology
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 *
 */

/* This file was automatically generated --- DO NOT EDIT */
/* Generated on Sun Jul 12 06:42:54 EDT 2009 */

#include "codelet-dft.h"

#ifdef HAVE_FMA

/* Generated by: ../../../genfft/gen_twiddle_c -fma -reorder-insns -schedule-for-pipeline -simd -compact -variables 4 -pipeline-latency 8 -n 25 -name t2bv_25 -include t2b.h -sign 1 */

/*
 * This function contains 248 FP additions, 241 FP multiplications,
 * (or, 67 additions, 60 multiplications, 181 fused multiply/add),
 * 208 stack variables, 67 constants, and 50 memory accesses
 */
#include "t2b.h"

static void t2bv_25(R *ri, R *ii, const R *W, stride rs, INT mb, INT me, INT ms)
{
     DVK(KP792626838, +0.792626838241819413632131824093538848057784557);
     DVK(KP876091699, +0.876091699473550838204498029706869638173524346);
     DVK(KP617882369, +0.617882369114440893914546919006756321695042882);
     DVK(KP803003575, +0.803003575438660414833440593570376004635464850);
     DVK(KP242145790, +0.242145790282157779872542093866183953459003101);
     DVK(KP968583161, +0.968583161128631119490168375464735813836012403);
     DVK(KP999544308, +0.999544308746292983948881682379742149196758193);
     DVK(KP916574801, +0.916574801383451584742370439148878693530976769);
     DVK(KP904730450, +0.904730450839922351881287709692877908104763647);
     DVK(KP809385824, +0.809385824416008241660603814668679683846476688);
     DVK(KP447417479, +0.447417479732227551498980015410057305749330693);
     DVK(KP894834959, +0.894834959464455102997960030820114611498661386);
     DVK(KP867381224, +0.867381224396525206773171885031575671309956167);
     DVK(KP683113946, +0.683113946453479238701949862233725244439656928);
     DVK(KP559154169, +0.559154169276087864842202529084232643714075927);
     DVK(KP958953096, +0.958953096729998668045963838399037225970891871);
     DVK(KP831864738, +0.831864738706457140726048799369896829771167132);
     DVK(KP829049696, +0.829049696159252993975487806364305442437946767);
     DVK(KP860541664, +0.860541664367944677098261680920518816412804187);
     DVK(KP897376177, +0.897376177523557693138608077137219684419427330);
     DVK(KP876306680, +0.876306680043863587308115903922062583399064238);
     DVK(KP681693190, +0.681693190061530575150324149145440022633095390);
     DVK(KP560319534, +0.560319534973832390111614715371676131169633784);
     DVK(KP855719849, +0.855719849902058969314654733608091555096772472);
     DVK(KP237294955, +0.237294955877110315393888866460840817927895961);
     DVK(KP949179823, +0.949179823508441261575555465843363271711583843);
     DVK(KP904508497, +0.904508497187473712051146708591409529430077295);
     DVK(KP997675361, +0.997675361079556513670859573984492383596555031);
     DVK(KP763932022, +0.763932022500210303590826331268723764559381640);
     DVK(KP690983005, +0.690983005625052575897706582817180941139845410);
     DVK(KP992114701, +0.992114701314477831049793042785778521453036709);
     DVK(KP952936919, +0.952936919628306576880750665357914584765951388);
     DVK(KP998026728, +0.998026728428271561952336806863450553336905220);
     DVK(KP262346850, +0.262346850930607871785420028382979691334784273);
     DVK(KP570584518, +0.570584518783621657366766175430996792655723863);
     DVK(KP669429328, +0.669429328479476605641803240971985825917022098);
     DVK(KP923225144, +0.923225144846402650453449441572664695995209956);
     DVK(KP945422727, +0.945422727388575946270360266328811958657216298);
     DVK(KP522616830, +0.522616830205754336872861364785224694908468440);
     DVK(KP956723877, +0.956723877038460305821989399535483155872969262);
     DVK(KP906616052, +0.906616052148196230441134447086066874408359177);
     DVK(KP772036680, +0.772036680810363904029489473607579825330539880);
     DVK(KP845997307, +0.845997307939530944175097360758058292389769300);
     DVK(KP951056516, +0.951056516295153572116439333379382143405698634);
     DVK(KP921078979, +0.921078979742360627699756128143719920817673854);
     DVK(KP912575812, +0.912575812670962425556968549836277086778922727);
     DVK(KP982009705, +0.982009705009746369461829878184175962711969869);
     DVK(KP734762448, +0.734762448793050413546343770063151342619912334);
     DVK(KP494780565, +0.494780565770515410344588413655324772219443730);
     DVK(KP447533225, +0.447533225982656890041886979663652563063114397);
     DVK(KP269969613, +0.269969613759572083574752974412347470060951301);
     DVK(KP244189809, +0.244189809627953270309879511234821255780225091);
     DVK(KP667278218, +0.667278218140296670899089292254759909713898805);
     DVK(KP603558818, +0.603558818296015001454675132653458027918768137);
     DVK(KP522847744, +0.522847744331509716623755382187077770911012542);
     DVK(KP578046249, +0.578046249379945007321754579646815604023525655);
     DVK(KP987388751, +0.987388751065621252324603216482382109400433949);
     DVK(KP893101515, +0.893101515366181661711202267938416198338079437);
     DVK(KP120146378, +0.120146378570687701782758537356596213647956445);
     DVK(KP132830569, +0.132830569247582714407653942074819768844536507);
     DVK(KP869845200, +0.869845200362138853122720822420327157933056305);
     DVK(KP786782374, +0.786782374965295178365099601674911834788448471);
     DVK(KP066152395, +0.066152395967733048213034281011006031460903353);
     DVK(KP059835404, +0.059835404262124915169548397419498386427871950);
     DVK(KP559016994, +0.559016994374947424102293417182819058860154590);
     DVK(KP250000000, +0.250000000000000000000000000000000000000000000);
     DVK(KP618033988, +0.618033988749894848204586834365638117720309180);
     INT m;
     R *x;
     x = ii;
     for (m = mb, W = W + (mb * ((TWVL / VL) * 48)); m < me; m = m + VL, x = x + (VL * ms), W = W + (TWVL * 48), MAKE_VOLATILE_STRIDE(rs)) {
	  V T25, T1B, T2y, T1K, T2s, T23, T1S, T26, T20, T1X;
	  {
	       V T1O, T2X, Te, T3L, Td, T3Q, T3j, T3b, T2R, T2M, T2f, T27, T1y, T1H, T3M;
	       V TW, TR, TK, T2B, T3n, T3e, T2U, T2F, T2i, T2a, Tz, T1C, T3N, TQ, T11;
	       V T1b, T1c, T16;
	       {
		    V T1, T1g, T1i, T1p, T1k, T1m, Tb, T1N, T6, T1M;
		    {
			 V T7, T9, T2, T4, T1f, T1h, T1o;
			 T1 = LD(&(x[0]), ms, &(x[0]));
			 T7 = LD(&(x[WS(rs, 10)]), ms, &(x[0]));
			 T9 = LD(&(x[WS(rs, 15)]), ms, &(x[WS(rs, 1)]));
			 T2 = LD(&(x[WS(rs, 5)]), ms, &(x[WS(rs, 1)]));
			 T4 = LD(&(x[WS(rs, 20)]), ms, &(x[0]));
			 T1f = LD(&(x[WS(rs, 3)]), ms, &(x[WS(rs, 1)]));
			 T1h = LD(&(x[WS(rs, 8)]), ms, &(x[0]));
			 T1o = LD(&(x[WS(rs, 18)]), ms, &(x[0]));
			 {
			      V T8, Ta, T3, T5, T1j;
			      T1j = LD(&(x[WS(rs, 23)]), ms, &(x[WS(rs, 1)]));
			      T8 = BYTW(&(W[TWVL * 18]), T7);
			      Ta = BYTW(&(W[TWVL * 28]), T9);
			      T3 = BYTW(&(W[TWVL * 8]), T2);
			      T5 = BYTW(&(W[TWVL * 38]), T4);
			      T1g = BYTW(&(W[TWVL * 4]), T1f);
			      T1i = BYTW(&(W[TWVL * 14]), T1h);
			      T1p = BYTW(&(W[TWVL * 34]), T1o);
			      T1k = BYTW(&(W[TWVL * 44]), T1j);
			      T1m = LD(&(x[WS(rs, 13)]), ms, &(x[WS(rs, 1)]));
			      Tb = VADD(T8, Ta);
			      T1N = VSUB(T8, Ta);
			      T6 = VADD(T3, T5);
			      T1M = VSUB(T3, T5);
			 }
		    }
		    {
			 V T1v, T1l, Th, Tj, T1w, T1q, Tq, Tk, Tn, Tg;
			 Tg = LD(&(x[WS(rs, 1)]), ms, &(x[WS(rs, 1)]));
			 {
			      V Tc, Ti, T1n, Tp;
			      Ti = LD(&(x[WS(rs, 6)]), ms, &(x[0]));
			      T1v = VSUB(T1i, T1k);
			      T1l = VADD(T1i, T1k);
			      T1n = BYTW(&(W[TWVL * 24]), T1m);
			      Tp = LD(&(x[WS(rs, 16)]), ms, &(x[0]));
			      T1O = VFMA(LDK(KP618033988), T1N, T1M);
			      T2X = VFNMS(LDK(KP618033988), T1M, T1N);
			      Te = VSUB(T6, Tb);
			      Tc = VADD(T6, Tb);
			      Th = BYTW(&(W[0]), Tg);
			      Tj = BYTW(&(W[TWVL * 10]), Ti);
			      T1w = VSUB(T1n, T1p);
			      T1q = VADD(T1n, T1p);
			      Tq = BYTW(&(W[TWVL * 30]), Tp);
			      Tk = LD(&(x[WS(rs, 21)]), ms, &(x[WS(rs, 1)]));
			      T3L = VADD(T1, Tc);
			      Td = VFNMS(LDK(KP250000000), Tc, T1);
			      Tn = LD(&(x[WS(rs, 11)]), ms, &(x[WS(rs, 1)]));
			 }
			 {
			      V T1x, T2K, TM, TB, Tw, Tm, Tx, Tr, TI, T2L, T1u, TD, TF, TL;
			      TL = LD(&(x[WS(rs, 4)]), ms, &(x[0]));
			      {
				   V T1t, Tl, To, TH, T1s, T1r, TA, TC;
				   TA = LD(&(x[WS(rs, 24)]), ms, &(x[0]));
				   T1r = VADD(T1l, T1q);
				   T1t = VSUB(T1q, T1l);
				   T1x = VFMA(LDK(KP618033988), T1w, T1v);
				   T2K = VFNMS(LDK(KP618033988), T1v, T1w);
				   Tl = BYTW(&(W[TWVL * 40]), Tk);
				   To = BYTW(&(W[TWVL * 20]), Tn);
				   TM = BYTW(&(W[TWVL * 6]), TL);
				   TB = BYTW(&(W[TWVL * 46]), TA);
				   TH = LD(&(x[WS(rs, 14)]), ms, &(x[0]));
				   T1s = VFNMS(LDK(KP250000000), T1r, T1g);
				   T3Q = VADD(T1g, T1r);
				   TC = LD(&(x[WS(rs, 9)]), ms, &(x[WS(rs, 1)]));
				   Tw = VSUB(Tj, Tl);
				   Tm = VADD(Tj, Tl);
				   Tx = VSUB(Tq, To);
				   Tr = VADD(To, Tq);
				   TI = BYTW(&(W[TWVL * 26]), TH);
				   T2L = VFMA(LDK(KP559016994), T1t, T1s);
				   T1u = VFNMS(LDK(KP559016994), T1t, T1s);
				   TD = BYTW(&(W[TWVL * 16]), TC);
				   TF = LD(&(x[WS(rs, 19)]), ms, &(x[WS(rs, 1)]));
			      }
			      {
				   V Tu, Ty, T2E, TE, TN, TG, Tt, TV, Ts;
				   TV = LD(&(x[WS(rs, 2)]), ms, &(x[0]));
				   Ts = VADD(Tm, Tr);
				   Tu = VSUB(Tm, Tr);
				   Ty = VFNMS(LDK(KP618033988), Tx, Tw);
				   T2E = VFMA(LDK(KP618033988), Tw, Tx);
				   T3j = VFNMS(LDK(KP059835404), T2K, T2L);
				   T3b = VFMA(LDK(KP066152395), T2L, T2K);
				   T2R = VFNMS(LDK(KP786782374), T2K, T2L);
				   T2M = VFMA(LDK(KP869845200), T2L, T2K);
				   T2f = VFMA(LDK(KP132830569), T1u, T1x);
				   T27 = VFNMS(LDK(KP120146378), T1x, T1u);
				   T1y = VFNMS(LDK(KP893101515), T1x, T1u);
				   T1H = VFMA(LDK(KP987388751), T1u, T1x);
				   TE = VSUB(TB, TD);
				   TN = VADD(TD, TB);
				   TG = BYTW(&(W[TWVL * 36]), TF);
				   Tt = VFNMS(LDK(KP250000000), Ts, Th);
				   T3M = VADD(Th, Ts);
				   TW = BYTW(&(W[TWVL * 2]), TV);
				   {
					V TJ, TO, Tv, T2D, TY, T15, T10, T13, TP;
					{
					     V TX, T14, TZ, T12;
					     TX = LD(&(x[WS(rs, 7)]), ms, &(x[WS(rs, 1)]));
					     T14 = LD(&(x[WS(rs, 17)]), ms, &(x[WS(rs, 1)]));
					     TZ = LD(&(x[WS(rs, 22)]), ms, &(x[0]));
					     T12 = LD(&(x[WS(rs, 12)]), ms, &(x[0]));
					     TJ = VSUB(TG, TI);
					     TO = VADD(TI, TG);
					     Tv = VFMA(LDK(KP559016994), Tu, Tt);
					     T2D = VFNMS(LDK(KP559016994), Tu, Tt);
					     TY = BYTW(&(W[TWVL * 12]), TX);
					     T15 = BYTW(&(W[TWVL * 32]), T14);
					     T10 = BYTW(&(W[TWVL * 42]), TZ);
					     T13 = BYTW(&(W[TWVL * 22]), T12);
					}
					TP = VADD(TN, TO);
					TR = VSUB(TN, TO);
					TK = VFMA(LDK(KP618033988), TJ, TE);
					T2B = VFNMS(LDK(KP618033988), TE, TJ);
					T3n = VFMA(LDK(KP578046249), T2D, T2E);
					T3e = VFNMS(LDK(KP522847744), T2E, T2D);
					T2U = VFNMS(LDK(KP987388751), T2D, T2E);
					T2F = VFMA(LDK(KP893101515), T2E, T2D);
					T2i = VFNMS(LDK(KP603558818), Ty, Tv);
					T2a = VFMA(LDK(KP667278218), Tv, Ty);
					Tz = VFNMS(LDK(KP244189809), Ty, Tv);
					T1C = VFMA(LDK(KP269969613), Tv, Ty);
					T3N = VADD(TM, TP);
					TQ = VFMS(LDK(KP250000000), TP, TM);
					T11 = VADD(TY, T10);
					T1b = VSUB(TY, T10);
					T1c = VSUB(T15, T13);
					T16 = VADD(T13, T15);
				   }
			      }
			 }
		    }
	       }
	       {
		    V T2z, Tf, T3W, T3O, T1d, T2H, T3m, T2j, T2b, TT, T1D, T2G, T35, T2V, T2Z;
		    V T3A, T3g, T2I, T1a, T3R, T3X;
		    T2z = VFNMS(LDK(KP559016994), Te, Td);
		    Tf = VFMA(LDK(KP559016994), Te, Td);
		    {
			 V TS, T2A, T17, T19;
			 TS = VFNMS(LDK(KP559016994), TR, TQ);
			 T2A = VFMA(LDK(KP559016994), TR, TQ);
			 T3W = VSUB(T3M, T3N);
			 T3O = VADD(T3M, T3N);
			 T1d = VFNMS(LDK(KP618033988), T1c, T1b);
			 T2H = VFMA(LDK(KP618033988), T1b, T1c);
			 T17 = VADD(T11, T16);
			 T19 = VSUB(T16, T11);
			 {
			      V T3f, T2T, T2C, T18, T3P;
			      T3m = VFMA(LDK(KP447533225), T2B, T2A);
			      T3f = VFNMS(LDK(KP494780565), T2A, T2B);
			      T2T = VFNMS(LDK(KP132830569), T2A, T2B);
			      T2C = VFMA(LDK(KP120146378), T2B, T2A);
			      T2j = VFNMS(LDK(KP786782374), TK, TS);
			      T2b = VFMA(LDK(KP869845200), TS, TK);
			      TT = VFNMS(LDK(KP667278218), TS, TK);
			      T1D = VFMA(LDK(KP603558818), TK, TS);
			      T18 = VFNMS(LDK(KP250000000), T17, TW);
			      T3P = VADD(TW, T17);
			      T2G = VFMA(LDK(KP734762448), T2F, T2C);
			      T35 = VFNMS(LDK(KP734762448), T2F, T2C);
			      T2V = VFNMS(LDK(KP734762448), T2U, T2T);
			      T2Z = VFMA(LDK(KP734762448), T2U, T2T);
			      T3A = VFMA(LDK(KP982009705), T3f, T3e);
			      T3g = VFNMS(LDK(KP982009705), T3f, T3e);
			      T2I = VFMA(LDK(KP559016994), T19, T18);
			      T1a = VFNMS(LDK(KP559016994), T19, T18);
			      T3R = VADD(T3P, T3Q);
			      T3X = VSUB(T3P, T3Q);
			 }
		    }
		    {
			 V T2n, T2t, T1V, T22, T2l, T2d, T1Q, T1I, T2w, T1A, T1F, T2q;
			 {
			      V T2k, T1G, T28, T2g, T3K, T3E, T3a, T34, T3x, T3H, T2c, TU, T1T, T1U, T1z;
			      V T3o, T3t;
			      T2n = VFNMS(LDK(KP912575812), T2j, T2i);
			      T2k = VFMA(LDK(KP912575812), T2j, T2i);
			      T3o = VFNMS(LDK(KP921078979), T3n, T3m);
			      T3t = VFMA(LDK(KP921078979), T3n, T3m);
			      {
				   V T3c, T2Q, T2J, T3k, T1e;
				   T3c = VFNMS(LDK(KP667278218), T2I, T2H);
				   T2Q = VFNMS(LDK(KP059835404), T2H, T2I);
				   T2J = VFMA(LDK(KP066152395), T2I, T2H);
				   T3k = VFMA(LDK(KP603558818), T2H, T2I);
				   T1G = VFMA(LDK(KP578046249), T1a, T1d);
				   T1e = VFNMS(LDK(KP522847744), T1d, T1a);
				   T28 = VFNMS(LDK(KP494780565), T1a, T1d);
				   T2g = VFMA(LDK(KP447533225), T1d, T1a);
				   {
					V T3U, T3S, T40, T3Y;
					T3U = VSUB(T3O, T3R);
					T3S = VADD(T3O, T3R);
					T40 = VMUL(LDK(KP951056516), VFNMS(LDK(KP618033988), T3W, T3X));
					T3Y = VMUL(LDK(KP951056516), VFMA(LDK(KP618033988), T3X, T3W));
					{
					     V T3s, T3l, T2N, T36;
					     T3s = VFNMS(LDK(KP845997307), T3k, T3j);
					     T3l = VFMA(LDK(KP845997307), T3k, T3j);
					     T2N = VFNMS(LDK(KP772036680), T2M, T2J);
					     T36 = VFMA(LDK(KP772036680), T2M, T2J);
					     {
						  V T30, T2S, T3d, T3z, T3T;
						  T30 = VFNMS(LDK(KP772036680), T2R, T2Q);
						  T2S = VFMA(LDK(KP772036680), T2R, T2Q);
						  T3d = VFNMS(LDK(KP845997307), T3c, T3b);
						  T3z = VFMA(LDK(KP845997307), T3c, T3b);
						  ST(&(x[0]), VADD(T3S, T3L), ms, &(x[0]));
						  T3T = VFNMS(LDK(KP250000000), T3S, T3L);
						  {
						       V T3C, T3p, T2O, T37;
						       T3C = VFMA(LDK(KP906616052), T3o, T3l);
						       T3p = VFNMS(LDK(KP906616052), T3o, T3l);
						       T2O = VFMA(LDK(KP956723877), T2N, T2G);
						       T37 = VFMA(LDK(KP522616830), T2V, T36);
						       {
							    V T31, T2W, T3u, T3h;
							    T31 = VFNMS(LDK(KP522616830), T2G, T30);
							    T2W = VFMA(LDK(KP945422727), T2V, T2S);
							    T3u = VFNMS(LDK(KP923225144), T3g, T3d);
							    T3h = VFMA(LDK(KP923225144), T3g, T3d);
							    {
								 V T3I, T3B, T3V, T3Z;
								 T3I = VFNMS(LDK(KP669429328), T3z, T3A);
								 T3B = VFMA(LDK(KP570584518), T3A, T3z);
								 T3V = VFMA(LDK(KP559016994), T3U, T3T);
								 T3Z = VFNMS(LDK(KP559016994), T3U, T3T);
								 {
								      V T3y, T3q, T2P, T38;
								      T3y = VFMA(LDK(KP262346850), T3p, T2X);
								      T3q = VMUL(LDK(KP998026728), VFNMS(LDK(KP952936919), T2X, T3p));
								      T2P = VFMA(LDK(KP992114701), T2O, T2z);
								      T38 = VFNMS(LDK(KP690983005), T37, T2S);
								      {
									   V T32, T2Y, T3v, T3F;
									   T32 = VFMA(LDK(KP763932022), T31, T2N);
									   T2Y = VMUL(LDK(KP998026728), VFMA(LDK(KP952936919), T2X, T2W));
									   T3v = VFNMS(LDK(KP997675361), T3u, T3t);
									   T3F = VFNMS(LDK(KP904508497), T3u, T3s);
									   {
										V T3i, T3r, T3J, T3D;
										T3i = VFMA(LDK(KP949179823), T3h, T2z);
										T3r = VFNMS(LDK(KP237294955), T3h, T2z);
										T3J = VFNMS(LDK(KP669429328), T3C, T3I);
										T3D = VFMA(LDK(KP618033988), T3C, T3B);
										ST(&(x[WS(rs, 20)]), VFNMSI(T3Y, T3V), ms, &(x[0]));
										ST(&(x[WS(rs, 5)]), VFMAI(T3Y, T3V), ms, &(x[WS(rs, 1)]));
										ST(&(x[WS(rs, 15)]), VFMAI(T40, T3Z), ms, &(x[WS(rs, 1)]));
										ST(&(x[WS(rs, 10)]), VFNMSI(T40, T3Z), ms, &(x[0]));
										{
										     V T39, T33, T3w, T3G;
										     T39 = VFMA(LDK(KP855719849), T38, T35);
										     T33 = VFNMS(LDK(KP855719849), T32, T2Z);
										     ST(&(x[WS(rs, 3)]), VFMAI(T2Y, T2P), ms, &(x[WS(rs, 1)]));
										     ST(&(x[WS(rs, 22)]), VFNMSI(T2Y, T2P), ms, &(x[0]));
										     T3w = VFMA(LDK(KP560319534), T3v, T3s);
										     T3G = VFNMS(LDK(KP681693190), T3F, T3t);
										     ST(&(x[WS(rs, 2)]), VFMAI(T3q, T3i), ms, &(x[0]));
										     ST(&(x[WS(rs, 23)]), VFNMSI(T3q, T3i), ms, &(x[WS(rs, 1)]));
										     T3K = VMUL(LDK(KP951056516), VFNMS(LDK(KP876306680), T3J, T3y));
										     T3E = VMUL(LDK(KP951056516), VFNMS(LDK(KP949179823), T3D, T3y));
										     T3a = VMUL(LDK(KP951056516), VFNMS(LDK(KP992114701), T39, T2X));
										     T34 = VFMA(LDK(KP897376177), T33, T2z);
										     T3x = VFNMS(LDK(KP949179823), T3w, T3r);
										     T3H = VFNMS(LDK(KP860541664), T3G, T3r);
										     T2t = VFNMS(LDK(KP912575812), T2b, T2a);
										     T2c = VFMA(LDK(KP912575812), T2b, T2a);
										     TU = VFMA(LDK(KP829049696), TT, Tz);
										     T1T = VFNMS(LDK(KP829049696), TT, Tz);
										     T1U = VFNMS(LDK(KP831864738), T1y, T1e);
										     T1z = VFMA(LDK(KP831864738), T1y, T1e);
										}
									   }
								      }
								 }
							    }
						       }
						  }
					     }
					}
				   }
			      }
			      {
				   V T2o, T2h, T29, T2u, T2v, T2p;
				   T2o = VFNMS(LDK(KP958953096), T2g, T2f);
				   T2h = VFMA(LDK(KP958953096), T2g, T2f);
				   ST(&(x[WS(rs, 17)]), VFNMSI(T3a, T34), ms, &(x[WS(rs, 1)]));
				   ST(&(x[WS(rs, 8)]), VFMAI(T3a, T34), ms, &(x[0]));
				   ST(&(x[WS(rs, 13)]), VFMAI(T3E, T3x), ms, &(x[WS(rs, 1)]));
				   ST(&(x[WS(rs, 12)]), VFNMSI(T3E, T3x), ms, &(x[0]));
				   ST(&(x[WS(rs, 7)]), VFNMSI(T3K, T3H), ms, &(x[WS(rs, 1)]));
				   ST(&(x[WS(rs, 18)]), VFMAI(T3K, T3H), ms, &(x[0]));
				   T1V = VFMA(LDK(KP559154169), T1U, T1T);
				   T22 = VFNMS(LDK(KP683113946), T1T, T1U);
				   T29 = VFNMS(LDK(KP867381224), T28, T27);
				   T2u = VFMA(LDK(KP867381224), T28, T27);
				   T2l = VFMA(LDK(KP894834959), T2k, T2h);
				   T2v = VFMA(LDK(KP447417479), T2k, T2u);
				   T2d = VFNMS(LDK(KP809385824), T2c, T29);
				   T2p = VFMA(LDK(KP447417479), T2c, T2o);
				   T1Q = VFMA(LDK(KP831864738), T1H, T1G);
				   T1I = VFNMS(LDK(KP831864738), T1H, T1G);
				   T2w = VFNMS(LDK(KP763932022), T2v, T2h);
				   T1A = VFMA(LDK(KP904730450), T1z, TU);
				   T1F = VFNMS(LDK(KP904730450), T1z, TU);
				   T2q = VFMA(LDK(KP690983005), T2p, T29);
			      }
			 }
			 {
			      V T2e, T1E, T1P, T2m;
			      T2e = VFNMS(LDK(KP992114701), T2d, Tf);
			      T1E = VFMA(LDK(KP916574801), T1D, T1C);
			      T1P = VFNMS(LDK(KP916574801), T1D, T1C);
			      T2m = VMUL(LDK(KP951056516), VFNMS(LDK(KP992114701), T2l, T1O));
			      {
				   V T1J, T2r, T1R, T1W, T1Z, T2x;
				   T2x = VFNMS(LDK(KP999544308), T2w, T2t);
				   T1J = VFNMS(LDK(KP904730450), T1I, T1F);
				   T25 = VFMA(LDK(KP968583161), T1A, Tf);
				   T1B = VFNMS(LDK(KP242145790), T1A, Tf);
				   T2r = VFNMS(LDK(KP999544308), T2q, T2n);
				   T1R = VFMA(LDK(KP904730450), T1Q, T1P);
				   T1W = VFNMS(LDK(KP904730450), T1Q, T1P);
				   T1Z = VADD(T1E, T1F);
				   ST(&(x[WS(rs, 21)]), VFMAI(T2m, T2e), ms, &(x[WS(rs, 1)]));
				   ST(&(x[WS(rs, 4)]), VFNMSI(T2m, T2e), ms, &(x[0]));
				   T2y = VMUL(LDK(KP951056516), VFNMS(LDK(KP803003575), T2x, T1O));
				   T1K = VFNMS(LDK(KP618033988), T1J, T1E);
				   T2s = VFNMS(LDK(KP803003575), T2r, Tf);
				   T23 = VFMA(LDK(KP617882369), T1W, T22);
				   T1S = VFNMS(LDK(KP242145790), T1R, T1O);
				   T26 = VMUL(LDK(KP951056516), VFMA(LDK(KP968583161), T1R, T1O));
				   T20 = VFNMS(LDK(KP683113946), T1Z, T1I);
				   T1X = VFMA(LDK(KP559016994), T1W, T1V);
			      }
			 }
		    }
	       }
	  }
	  {
	       V T1L, T24, T21, T1Y;
	       T1L = VFNMS(LDK(KP876091699), T1K, T1B);
	       ST(&(x[WS(rs, 16)]), VFMAI(T2y, T2s), ms, &(x[0]));
	       ST(&(x[WS(rs, 9)]), VFNMSI(T2y, T2s), ms, &(x[WS(rs, 1)]));
	       T24 = VMUL(LDK(KP951056516), VFNMS(LDK(KP876306680), T23, T1S));
	       ST(&(x[WS(rs, 24)]), VFNMSI(T26, T25), ms, &(x[0]));
	       ST(&(x[WS(rs, 1)]), VFMAI(T26, T25), ms, &(x[WS(rs, 1)]));
	       T21 = VFMA(LDK(KP792626838), T20, T1B);
	       T1Y = VMUL(LDK(KP951056516), VFMA(LDK(KP968583161), T1X, T1S));
	       ST(&(x[WS(rs, 11)]), VFMAI(T24, T21), ms, &(x[WS(rs, 1)]));
	       ST(&(x[WS(rs, 14)]), VFNMSI(T24, T21), ms, &(x[0]));
	       ST(&(x[WS(rs, 19)]), VFNMSI(T1Y, T1L), ms, &(x[WS(rs, 1)]));
	       ST(&(x[WS(rs, 6)]), VFMAI(T1Y, T1L), ms, &(x[0]));
	  }
     }
}

static const tw_instr twinstr[] = {
     VTW(0, 1),
     VTW(0, 2),
     VTW(0, 3),
     VTW(0, 4),
     VTW(0, 5),
     VTW(0, 6),
     VTW(0, 7),
     VTW(0, 8),
     VTW(0, 9),
     VTW(0, 10),
     VTW(0, 11),
     VTW(0, 12),
     VTW(0, 13),
     VTW(0, 14),
     VTW(0, 15),
     VTW(0, 16),
     VTW(0, 17),
     VTW(0, 18),
     VTW(0, 19),
     VTW(0, 20),
     VTW(0, 21),
     VTW(0, 22),
     VTW(0, 23),
     VTW(0, 24),
     {TW_NEXT, VL, 0}
};

static const ct_desc desc = { 25, "t2bv_25", twinstr, &GENUS, {67, 60, 181, 0}, 0, 0, 0 };

void X(codelet_t2bv_25) (planner *p) {
     X(kdft_dit_register) (p, t2bv_25, &desc);
}
#else				/* HAVE_FMA */

/* Generated by: ../../../genfft/gen_twiddle_c -simd -compact -variables 4 -pipeline-latency 8 -n 25 -name t2bv_25 -include t2b.h -sign 1 */

/*
 * This function contains 248 FP additions, 188 FP multiplications,
 * (or, 171 additions, 111 multiplications, 77 fused multiply/add),
 * 100 stack variables, 40 constants, and 50 memory accesses
 */
#include "t2b.h"

static void t2bv_25(R *ri, R *ii, const R *W, stride rs, INT mb, INT me, INT ms)
{
     DVK(KP497379774, +0.497379774329709576484567492012895936835134813);
     DVK(KP968583161, +0.968583161128631119490168375464735813836012403);
     DVK(KP248689887, +0.248689887164854788242283746006447968417567406);
     DVK(KP1_937166322, +1.937166322257262238980336750929471627672024806);
     DVK(KP809016994, +0.809016994374947424102293417182819058860154590);
     DVK(KP309016994, +0.309016994374947424102293417182819058860154590);
     DVK(KP1_688655851, +1.688655851004030157097116127933363010763318483);
     DVK(KP535826794, +0.535826794978996618271308767867639978063575346);
     DVK(KP425779291, +0.425779291565072648862502445744251703979973042);
     DVK(KP1_809654104, +1.809654104932039055427337295865395187940827822);
     DVK(KP963507348, +0.963507348203430549974383005744259307057084020);
     DVK(KP876306680, +0.876306680043863587308115903922062583399064238);
     DVK(KP844327925, +0.844327925502015078548558063966681505381659241);
     DVK(KP1_071653589, +1.071653589957993236542617535735279956127150691);
     DVK(KP481753674, +0.481753674101715274987191502872129653528542010);
     DVK(KP1_752613360, +1.752613360087727174616231807844125166798128477);
     DVK(KP851558583, +0.851558583130145297725004891488503407959946084);
     DVK(KP904827052, +0.904827052466019527713668647932697593970413911);
     DVK(KP125333233, +0.125333233564304245373118759816508793942918247);
     DVK(KP1_984229402, +1.984229402628955662099586085571557042906073418);
     DVK(KP1_457937254, +1.457937254842823046293460638110518222745143328);
     DVK(KP684547105, +0.684547105928688673732283357621209269889519233);
     DVK(KP637423989, +0.637423989748689710176712811676016195434917298);
     DVK(KP1_541026485, +1.541026485551578461606019272792355694543335344);
     DVK(KP062790519, +0.062790519529313376076178224565631133122484832);
     DVK(KP1_996053456, +1.996053456856543123904673613726901106673810439);
     DVK(KP770513242, +0.770513242775789230803009636396177847271667672);
     DVK(KP1_274847979, +1.274847979497379420353425623352032390869834596);
     DVK(KP125581039, +0.125581039058626752152356449131262266244969664);
     DVK(KP998026728, +0.998026728428271561952336806863450553336905220);
     DVK(KP992114701, +0.992114701314477831049793042785778521453036709);
     DVK(KP250666467, +0.250666467128608490746237519633017587885836494);
     DVK(KP728968627, +0.728968627421411523146730319055259111372571664);
     DVK(KP1_369094211, +1.369094211857377347464566715242418539779038465);
     DVK(KP293892626, +0.293892626146236564584352977319536384298826219);
     DVK(KP475528258, +0.475528258147576786058219666689691071702849317);
     DVK(KP951056516, +0.951056516295153572116439333379382143405698634);
     DVK(KP250000000, +0.250000000000000000000000000000000000000000000);
     DVK(KP587785252, +0.587785252292473129168705954639072768597652438);
     DVK(KP559016994, +0.559016994374947424102293417182819058860154590);
     INT m;
     R *x;
     x = ii;
     for (m = mb, W = W + (mb * ((TWVL / VL) * 48)); m < me; m = m + VL, x = x + (VL * ms), W = W + (TWVL * 48), MAKE_VOLATILE_STRIDE(rs)) {
	  V T1A, T1z, T1R, T1S, T1B, T1C, T1Q, T2L, T1l, T2v, T1i, T3e, T2u, Tb, T2i;
	  V Tj, T3b, T2h, Tv, T2k, TD, T3a, T2l, T11, T2s, TY, T3d, T2r;
	  {
	       V T1v, T1x, T1y, T1q, T1s, T1t, T1P;
	       T1A = LD(&(x[0]), ms, &(x[0]));
	       {
		    V T1u, T1w, T1p, T1r;
		    T1u = LD(&(x[WS(rs, 10)]), ms, &(x[0]));
		    T1v = BYTW(&(W[TWVL * 18]), T1u);
		    T1w = LD(&(x[WS(rs, 15)]), ms, &(x[WS(rs, 1)]));
		    T1x = BYTW(&(W[TWVL * 28]), T1w);
		    T1y = VADD(T1v, T1x);
		    T1p = LD(&(x[WS(rs, 5)]), ms, &(x[WS(rs, 1)]));
		    T1q = BYTW(&(W[TWVL * 8]), T1p);
		    T1r = LD(&(x[WS(rs, 20)]), ms, &(x[0]));
		    T1s = BYTW(&(W[TWVL * 38]), T1r);
		    T1t = VADD(T1q, T1s);
	       }
	       T1z = VMUL(LDK(KP559016994), VSUB(T1t, T1y));
	       T1R = VSUB(T1v, T1x);
	       T1S = VMUL(LDK(KP587785252), T1R);
	       T1B = VADD(T1t, T1y);
	       T1C = VFNMS(LDK(KP250000000), T1B, T1A);
	       T1P = VSUB(T1q, T1s);
	       T1Q = VMUL(LDK(KP951056516), T1P);
	       T2L = VMUL(LDK(KP587785252), T1P);
	  }
	  {
	       V T1f, T19, T1b, T1c, T14, T16, T17, T1e;
	       T1e = LD(&(x[WS(rs, 3)]), ms, &(x[WS(rs, 1)]));
	       T1f = BYTW(&(W[TWVL * 4]), T1e);
	       {
		    V T18, T1a, T13, T15;
		    T18 = LD(&(x[WS(rs, 13)]), ms, &(x[WS(rs, 1)]));
		    T19 = BYTW(&(W[TWVL * 24]), T18);
		    T1a = LD(&(x[WS(rs, 18)]), ms, &(x[0]));
		    T1b = BYTW(&(W[TWVL * 34]), T1a);
		    T1c = VADD(T19, T1b);
		    T13 = LD(&(x[WS(rs, 8)]), ms, &(x[0]));
		    T14 = BYTW(&(W[TWVL * 14]), T13);
		    T15 = LD(&(x[WS(rs, 23)]), ms, &(x[WS(rs, 1)]));
		    T16 = BYTW(&(W[TWVL * 44]), T15);
		    T17 = VADD(T14, T16);
	       }
	       {
		    V T1j, T1k, T1d, T1g, T1h;
		    T1j = VSUB(T14, T16);
		    T1k = VSUB(T19, T1b);
		    T1l = VFMA(LDK(KP475528258), T1j, VMUL(LDK(KP293892626), T1k));
		    T2v = VFNMS(LDK(KP475528258), T1k, VMUL(LDK(KP293892626), T1j));
		    T1d = VMUL(LDK(KP559016994), VSUB(T17, T1c));
		    T1g = VADD(T17, T1c);
		    T1h = VFNMS(LDK(KP250000000), T1g, T1f);
		    T1i = VADD(T1d, T1h);
		    T3e = VADD(T1f, T1g);
		    T2u = VSUB(T1h, T1d);
	       }
	  }
	  {
	       V Tg, T7, T9, Td, T2, T4, Tc, Tf;
	       Tf = LD(&(x[WS(rs, 4)]), ms, &(x[0]));
	       Tg = BYTW(&(W[TWVL * 6]), Tf);
	       {
		    V T6, T8, T1, T3;
		    T6 = LD(&(x[WS(rs, 14)]), ms, &(x[0]));
		    T7 = BYTW(&(W[TWVL * 26]), T6);
		    T8 = LD(&(x[WS(rs, 19)]), ms, &(x[WS(rs, 1)]));
		    T9 = BYTW(&(W[TWVL * 36]), T8);
		    Td = VADD(T7, T9);
		    T1 = LD(&(x[WS(rs, 9)]), ms, &(x[WS(rs, 1)]));
		    T2 = BYTW(&(W[TWVL * 16]), T1);
		    T3 = LD(&(x[WS(rs, 24)]), ms, &(x[0]));
		    T4 = BYTW(&(W[TWVL * 46]), T3);
		    Tc = VADD(T2, T4);
	       }
	       {
		    V T5, Ta, Te, Th, Ti;
		    T5 = VSUB(T2, T4);
		    Ta = VSUB(T7, T9);
		    Tb = VFMA(LDK(KP475528258), T5, VMUL(LDK(KP293892626), Ta));
		    T2i = VFNMS(LDK(KP475528258), Ta, VMUL(LDK(KP293892626), T5));
		    Te = VMUL(LDK(KP559016994), VSUB(Tc, Td));
		    Th = VADD(Tc, Td);
		    Ti = VFNMS(LDK(KP250000000), Th, Tg);
		    Tj = VADD(Te, Ti);
		    T3b = VADD(Tg, Th);
		    T2h = VSUB(Ti, Te);
	       }
	  }
	  {
	       V TA, Tr, Tt, Tx, Tm, To, Tw, Tz;
	       Tz = LD(&(x[WS(rs, 1)]), ms, &(x[WS(rs, 1)]));
	       TA = BYTW(&(W[0]), Tz);
	       {
		    V Tq, Ts, Tl, Tn;
		    Tq = LD(&(x[WS(rs, 11)]), ms, &(x[WS(rs, 1)]));
		    Tr = BYTW(&(W[TWVL * 20]), Tq);
		    Ts = LD(&(x[WS(rs, 16)]), ms, &(x[0]));
		    Tt = BYTW(&(W[TWVL * 30]), Ts);
		    Tx = VADD(Tr, Tt);
		    Tl = LD(&(x[WS(rs, 6)]), ms, &(x[0]));
		    Tm = BYTW(&(W[TWVL * 10]), Tl);
		    Tn = LD(&(x[WS(rs, 21)]), ms, &(x[WS(rs, 1)]));
		    To = BYTW(&(W[TWVL * 40]), Tn);
		    Tw = VADD(Tm, To);
	       }
	       {
		    V Tp, Tu, Ty, TB, TC;
		    Tp = VSUB(Tm, To);
		    Tu = VSUB(Tr, Tt);
		    Tv = VFMA(LDK(KP475528258), Tp, VMUL(LDK(KP293892626), Tu));
		    T2k = VFNMS(LDK(KP475528258), Tu, VMUL(LDK(KP293892626), Tp));
		    Ty = VMUL(LDK(KP559016994), VSUB(Tw, Tx));
		    TB = VADD(Tw, Tx);
		    TC = VFNMS(LDK(KP250000000), TB, TA);
		    TD = VADD(Ty, TC);
		    T3a = VADD(TA, TB);
		    T2l = VSUB(TC, Ty);
	       }
	  }
	  {
	       V TV, TP, TR, TS, TK, TM, TN, TU;
	       TU = LD(&(x[WS(rs, 2)]), ms, &(x[0]));
	       TV = BYTW(&(W[TWVL * 2]), TU);
	       {
		    V TO, TQ, TJ, TL;
		    TO = LD(&(x[WS(rs, 12)]), ms, &(x[0]));
		    TP = BYTW(&(W[TWVL * 22]), TO);
		    TQ = LD(&(x[WS(rs, 17)]), ms, &(x[WS(rs, 1)]));
		    TR = BYTW(&(W[TWVL * 32]), TQ);
		    TS = VADD(TP, TR);
		    TJ = LD(&(x[WS(rs, 7)]), ms, &(x[WS(rs, 1)]));
		    TK = BYTW(&(W[TWVL * 12]), TJ);
		    TL = LD(&(x[WS(rs, 22)]), ms, &(x[0]));
		    TM = BYTW(&(W[TWVL * 42]), TL);
		    TN = VADD(TK, TM);
	       }
	       {
		    V TZ, T10, TT, TW, TX;
		    TZ = VSUB(TK, TM);
		    T10 = VSUB(TP, TR);
		    T11 = VFMA(LDK(KP475528258), TZ, VMUL(LDK(KP293892626), T10));
		    T2s = VFNMS(LDK(KP475528258), T10, VMUL(LDK(KP293892626), TZ));
		    TT = VMUL(LDK(KP559016994), VSUB(TN, TS));
		    TW = VADD(TN, TS);
		    TX = VFNMS(LDK(KP250000000), TW, TV);
		    TY = VADD(TT, TX);
		    T3d = VADD(TV, TW);
		    T2r = VSUB(TX, TT);
	       }
	  }
	  {
	       V T3g, T3o, T3k, T3l, T3j, T3m, T3p, T3n;
	       {
		    V T3c, T3f, T3h, T3i;
		    T3c = VSUB(T3a, T3b);
		    T3f = VSUB(T3d, T3e);
		    T3g = VBYI(VFMA(LDK(KP951056516), T3c, VMUL(LDK(KP587785252), T3f)));
		    T3o = VBYI(VFNMS(LDK(KP951056516), T3f, VMUL(LDK(KP587785252), T3c)));
		    T3k = VADD(T1A, T1B);
		    T3h = VADD(T3a, T3b);
		    T3i = VADD(T3d, T3e);
		    T3l = VADD(T3h, T3i);
		    T3j = VMUL(LDK(KP559016994), VSUB(T3h, T3i));
		    T3m = VFNMS(LDK(KP250000000), T3l, T3k);
	       }
	       ST(&(x[0]), VADD(T3k, T3l), ms, &(x[0]));
	       T3p = VSUB(T3m, T3j);
	       ST(&(x[WS(rs, 10)]), VADD(T3o, T3p), ms, &(x[0]));
	       ST(&(x[WS(rs, 15)]), VSUB(T3p, T3o), ms, &(x[WS(rs, 1)]));
	       T3n = VADD(T3j, T3m);
	       ST(&(x[WS(rs, 5)]), VADD(T3g, T3n), ms, &(x[WS(rs, 1)]));
	       ST(&(x[WS(rs, 20)]), VSUB(T3n, T3g), ms, &(x[0]));
	  }
	  {
	       V T2z, T2M, T2U, T2V, T2W, T34, T35, T36, T2X, T2Y, T2Z, T31, T32, T33, T2n;
	       V T2N, T2E, T2K, T2y, T2H, T2A, T2G, T38, T39;
	       T2z = VSUB(T1C, T1z);
	       T2M = VFNMS(LDK(KP951056516), T1R, T2L);
	       T2U = VFMA(LDK(KP1_369094211), T2k, VMUL(LDK(KP728968627), T2l));
	       T2V = VFNMS(LDK(KP992114701), T2h, VMUL(LDK(KP250666467), T2i));
	       T2W = VADD(T2U, T2V);
	       T34 = VFNMS(LDK(KP125581039), T2s, VMUL(LDK(KP998026728), T2r));
	       T35 = VFMA(LDK(KP1_274847979), T2v, VMUL(LDK(KP770513242), T2u));
	       T36 = VADD(T34, T35);
	       T2X = VFMA(LDK(KP1_996053456), T2s, VMUL(LDK(KP062790519), T2r));
	       T2Y = VFNMS(LDK(KP637423989), T2u, VMUL(LDK(KP1_541026485), T2v));
	       T2Z = VADD(T2X, T2Y);
	       T31 = VFNMS(LDK(KP1_457937254), T2k, VMUL(LDK(KP684547105), T2l));
	       T32 = VFMA(LDK(KP1_984229402), T2i, VMUL(LDK(KP125333233), T2h));
	       T33 = VADD(T31, T32);
	       {
		    V T2j, T2m, T2I, T2C, T2D, T2J;
		    T2j = VFNMS(LDK(KP851558583), T2i, VMUL(LDK(KP904827052), T2h));
		    T2m = VFMA(LDK(KP1_752613360), T2k, VMUL(LDK(KP481753674), T2l));
		    T2I = VADD(T2m, T2j);
		    T2C = VFMA(LDK(KP1_071653589), T2s, VMUL(LDK(KP844327925), T2r));
		    T2D = VFMA(LDK(KP125581039), T2v, VMUL(LDK(KP998026728), T2u));
		    T2J = VADD(T2C, T2D);
		    T2n = VSUB(T2j, T2m);
		    T2N = VADD(T2I, T2J);
		    T2E = VSUB(T2C, T2D);
		    T2K = VMUL(LDK(KP559016994), VSUB(T2I, T2J));
	       }
	       {
		    V T2o, T2p, T2q, T2t, T2w, T2x;
		    T2o = VFNMS(LDK(KP963507348), T2k, VMUL(LDK(KP876306680), T2l));
		    T2p = VFMA(LDK(KP1_809654104), T2i, VMUL(LDK(KP425779291), T2h));
		    T2q = VSUB(T2o, T2p);
		    T2t = VFNMS(LDK(KP1_688655851), T2s, VMUL(LDK(KP535826794), T2r));
		    T2w = VFNMS(LDK(KP1_996053456), T2v, VMUL(LDK(KP062790519), T2u));
		    T2x = VADD(T2t, T2w);
		    T2y = VMUL(LDK(KP559016994), VSUB(T2q, T2x));
		    T2H = VSUB(T2t, T2w);
		    T2A = VADD(T2q, T2x);
		    T2G = VADD(T2o, T2p);
	       }
	       {
		    V T2S, T2T, T30, T37;
		    T2S = VADD(T2z, T2A);
		    T2T = VBYI(VADD(T2M, T2N));
		    ST(&(x[WS(rs, 23)]), VSUB(T2S, T2T), ms, &(x[WS(rs, 1)]));
		    ST(&(x[WS(rs, 2)]), VADD(T2S, T2T), ms, &(x[0]));
		    T30 = VADD(T2z, VADD(T2W, T2Z));
		    T37 = VBYI(VSUB(VADD(T33, T36), T2M));
		    ST(&(x[WS(rs, 22)]), VSUB(T30, T37), ms, &(x[0]));
		    ST(&(x[WS(rs, 3)]), VADD(T30, T37), ms, &(x[WS(rs, 1)]));
	       }
	       T38 = VBYI(VSUB(VFMA(LDK(KP951056516), VSUB(T2U, T2V), VFMA(LDK(KP309016994), T33, VFNMS(LDK(KP809016994), T36, VMUL(LDK(KP587785252), VSUB(T2X, T2Y))))), T2M));
	       T39 = VFMA(LDK(KP309016994), T2W, VFMA(LDK(KP951056516), VSUB(T32, T31), VFMA(LDK(KP587785252), VSUB(T35, T34), VFNMS(LDK(KP809016994), T2Z, T2z))));
	       ST(&(x[WS(rs, 8)]), VADD(T38, T39), ms, &(x[0]));
	       ST(&(x[WS(rs, 17)]), VSUB(T39, T38), ms, &(x[WS(rs, 1)]));
	       {
		    V T2F, T2Q, T2P, T2R, T2B, T2O;
		    T2B = VFNMS(LDK(KP250000000), T2A, T2z);
		    T2F = VFMA(LDK(KP951056516), T2n, VADD(T2y, VFNMS(LDK(KP587785252), T2E, T2B)));
		    T2Q = VFMA(LDK(KP587785252), T2n, VFMA(LDK(KP951056516), T2E, VSUB(T2B, T2y)));
		    T2O = VFNMS(LDK(KP250000000), T2N, T2M);
		    T2P = VBYI(VADD(VFMA(LDK(KP951056516), T2G, VMUL(LDK(KP587785252), T2H)), VADD(T2K, T2O)));
		    T2R = VBYI(VADD(VFNMS(LDK(KP951056516), T2H, VMUL(LDK(KP587785252), T2G)), VSUB(T2O, T2K)));
		    ST(&(x[WS(rs, 18)]), VSUB(T2F, T2P), ms, &(x[0]));
		    ST(&(x[WS(rs, 12)]), VADD(T2Q, T2R), ms, &(x[0]));
		    ST(&(x[WS(rs, 7)]), VADD(T2F, T2P), ms, &(x[WS(rs, 1)]));
		    ST(&(x[WS(rs, 13)]), VSUB(T2Q, T2R), ms, &(x[WS(rs, 1)]));
	       }
	  }
	  {
	       V T1D, T1T, T21, T22, T23, T2b, T2c, T2d, T24, T25, T26, T28, T29, T2a, TF;
	       V T1U, T1I, T1O, T1o, T1L, T1E, T1K, T2f, T2g;
	       T1D = VADD(T1z, T1C);
	       T1T = VADD(T1Q, T1S);
	       T21 = VFMA(LDK(KP1_688655851), Tv, VMUL(LDK(KP535826794), TD));
	       T22 = VFMA(LDK(KP1_541026485), Tb, VMUL(LDK(KP637423989), Tj));
	       T23 = VSUB(T21, T22);
	       T2b = VFMA(LDK(KP851558583), T11, VMUL(LDK(KP904827052), TY));
	       T2c = VFMA(LDK(KP1_984229402), T1l, VMUL(LDK(KP125333233), T1i));
	       T2d = VADD(T2b, T2c);
	       T24 = VFNMS(LDK(KP425779291), TY, VMUL(LDK(KP1_809654104), T11));
	       T25 = VFNMS(LDK(KP992114701), T1i, VMUL(LDK(KP250666467), T1l));
	       T26 = VADD(T24, T25);
	       T28 = VFNMS(LDK(KP1_071653589), Tv, VMUL(LDK(KP844327925), TD));
	       T29 = VFNMS(LDK(KP770513242), Tj, VMUL(LDK(KP1_274847979), Tb));
	       T2a = VADD(T28, T29);
	       {
		    V Tk, TE, T1M, T1G, T1H, T1N;
		    Tk = VFMA(LDK(KP1_071653589), Tb, VMUL(LDK(KP844327925), Tj));
		    TE = VFMA(LDK(KP1_937166322), Tv, VMUL(LDK(KP248689887), TD));
		    T1M = VADD(TE, Tk);
		    T1G = VFMA(LDK(KP1_752613360), T11, VMUL(LDK(KP481753674), TY));
		    T1H = VFMA(LDK(KP1_457937254), T1l, VMUL(LDK(KP684547105), T1i));
		    T1N = VADD(T1G, T1H);
		    TF = VSUB(Tk, TE);
		    T1U = VADD(T1M, T1N);
		    T1I = VSUB(T1G, T1H);
		    T1O = VMUL(LDK(KP559016994), VSUB(T1M, T1N));
	       }
	       {
		    V TG, TH, TI, T12, T1m, T1n;
		    TG = VFNMS(LDK(KP497379774), Tv, VMUL(LDK(KP968583161), TD));
		    TH = VFNMS(LDK(KP1_688655851), Tb, VMUL(LDK(KP535826794), Tj));
		    TI = VADD(TG, TH);
		    T12 = VFNMS(LDK(KP963507348), T11, VMUL(LDK(KP876306680), TY));
		    T1m = VFNMS(LDK(KP1_369094211), T1l, VMUL(LDK(KP728968627), T1i));
		    T1n = VADD(T12, T1m);
		    T1o = VMUL(LDK(KP559016994), VSUB(TI, T1n));
		    T1L = VSUB(T12, T1m);
		    T1E = VADD(TI, T1n);
		    T1K = VSUB(TG, TH);
	       }
	       {
		    V T1Z, T20, T27, T2e;
		    T1Z = VADD(T1D, T1E);
		    T20 = VBYI(VADD(T1T, T1U));
		    ST(&(x[WS(rs, 24)]), VSUB(T1Z, T20), ms, &(x[0]));
		    ST(&(x[WS(rs, 1)]), VADD(T1Z, T20), ms, &(x[WS(rs, 1)]));
		    T27 = VADD(T1D, VADD(T23, T26));
		    T2e = VBYI(VSUB(VADD(T2a, T2d), T1T));
		    ST(&(x[WS(rs, 21)]), VSUB(T27, T2e), ms, &(x[WS(rs, 1)]));
		    ST(&(x[WS(rs, 4)]), VADD(T27, T2e), ms, &(x[0]));
	       }
	       T2f = VBYI(VSUB(VFMA(LDK(KP309016994), T2a, VFMA(LDK(KP951056516), VADD(T21, T22), VFNMS(LDK(KP809016994), T2d, VMUL(LDK(KP587785252), VSUB(T24, T25))))), T1T));
	       T2g = VFMA(LDK(KP951056516), VSUB(T29, T28), VFMA(LDK(KP309016994), T23, VFMA(LDK(KP587785252), VSUB(T2c, T2b), VFNMS(LDK(KP809016994), T26, T1D))));
	       ST(&(x[WS(rs, 9)]), VADD(T2f, T2g), ms, &(x[WS(rs, 1)]));
	       ST(&(x[WS(rs, 16)]), VSUB(T2g, T2f), ms, &(x[0]));
	       {
		    V T1J, T1X, T1W, T1Y, T1F, T1V;
		    T1F = VFNMS(LDK(KP250000000), T1E, T1D);
		    T1J = VFMA(LDK(KP951056516), TF, VADD(T1o, VFNMS(LDK(KP587785252), T1I, T1F)));
		    T1X = VFMA(LDK(KP587785252), TF, VFMA(LDK(KP951056516), T1I, VSUB(T1F, T1o)));
		    T1V = VFNMS(LDK(KP250000000), T1U, T1T);
		    T1W = VBYI(VADD(VFMA(LDK(KP951056516), T1K, VMUL(LDK(KP587785252), T1L)), VADD(T1O, T1V)));
		    T1Y = VBYI(VADD(VFNMS(LDK(KP951056516), T1L, VMUL(LDK(KP587785252), T1K)), VSUB(T1V, T1O)));
		    ST(&(x[WS(rs, 19)]), VSUB(T1J, T1W), ms, &(x[WS(rs, 1)]));
		    ST(&(x[WS(rs, 11)]), VADD(T1X, T1Y), ms, &(x[WS(rs, 1)]));
		    ST(&(x[WS(rs, 6)]), VADD(T1J, T1W), ms, &(x[0]));
		    ST(&(x[WS(rs, 14)]), VSUB(T1X, T1Y), ms, &(x[0]));
	       }
	  }
     }
}

static const tw_instr twinstr[] = {
     VTW(0, 1),
     VTW(0, 2),
     VTW(0, 3),
     VTW(0, 4),
     VTW(0, 5),
     VTW(0, 6),
     VTW(0, 7),
     VTW(0, 8),
     VTW(0, 9),
     VTW(0, 10),
     VTW(0, 11),
     VTW(0, 12),
     VTW(0, 13),
     VTW(0, 14),
     VTW(0, 15),
     VTW(0, 16),
     VTW(0, 17),
     VTW(0, 18),
     VTW(0, 19),
     VTW(0, 20),
     VTW(0, 21),
     VTW(0, 22),
     VTW(0, 23),
     VTW(0, 24),
     {TW_NEXT, VL, 0}
};

static const ct_desc desc = { 25, "t2bv_25", twinstr, &GENUS, {171, 111, 77, 0}, 0, 0, 0 };

void X(codelet_t2bv_25) (planner *p) {
     X(kdft_dit_register) (p, t2bv_25, &desc);
}
#endif				/* HAVE_FMA */
