#include<stdio.h>
#include<stdlib.h>
#include<assert.h>
#include<verilated.h>
#include<verilated_vcd_c.h>
#include"Vcompare.h"
#include"Vcompare___024root.h"

#define MAX_SIM_TIME 20

vluint64_t sim_time = 0;

int main()
{
	Vcompare* compare = new Vcompare;

//	Verilated::commandArgs(argc, argv);
	Verilated::traceEverOn(true);
	VerilatedVcdC *m_trace = new VerilatedVcdC;
	compare->trace(m_trace, 5);
	m_trace->open("waveform.vcd");

	while(sim_time < MAX_SIM_TIME) {
		int a = (rand() % 16) - 8;
		int b = (rand() % 16) - 8;
		int cin = rand() % 2;

		compare->a	 = a;
		compare->b	 = b;
		compare->cin = cin;
		compare->eval();
		m_trace->dump(sim_time);
		sim_time++;
	}

	m_trace->close();
	delete compare;
	exit(EXIT_SUCCESS);
}

