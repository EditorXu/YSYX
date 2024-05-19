#include<stdio.h>
#include<stdlib.h>
#include<assert.h>
#include<verilated.h>
#include<verilated_vcd_c.h>
#include"Vsub_add.h"
#include"Vsub_add___024root.h"

#define MAX_SIM_TIME 20

vluint64_t sim_time = 0;

int main()
{
	Vsub_add* sub_add = new Vsub_add;

//	Verilated::commandArgs(argc, argv);
	Verilated::traceEverOn(true);
	VerilatedVcdC *m_trace = new VerilatedVcdC;
	sub_add->trace(m_trace, 5);
	m_trace->open("waveform.vcd");

	while(sim_time < MAX_SIM_TIME) {
		int a = (rand() % 16) - 8;
		int b = (rand() % 16) - 8;
		int cin = rand() % 2;

		sub_add->a	 = a;
		sub_add->b	 = b;
		sub_add->cin = cin;
		sub_add->eval();
		m_trace->dump(sim_time);
		sim_time++;
	}

	m_trace->close();
	delete sub_add;
	exit(EXIT_SUCCESS);
}

