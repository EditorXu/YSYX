module shift(
input [7:0] din,
input [2:0] shamt,
input L_R,
input A_L,
output [7:0] dout
);

wire out_0_0,out_1_0;
wire out_0_1,out_1_1;
wire out_0_2,out_1_2;
wire out_0_3,out_1_3;
wire out_0_4,out_1_4;
wire out_0_5,out_1_5;
wire out_0_6,out_1_6;
wire out_0_7,out_1_7;
wire out_A_L;

mux_2_1 i_mux_2_1(
.s	(A_L),
.in	(din[7]),
.out(out_A_L)
);

mux_4_1 i_mux_4_1_0_0(
.a		(din[0]),
.b		(din[1]),
.c		(din[0]),
.d		(1'b0),
.s0		(shamt[0]),
.s1		(L_R),
.out	(out_0_0)
);

mux_4_1 i_mux_4_1_0_1(
.a		(din[1]),
.b		(din[2]),
.c		(din[1]),
.d		(din[0]),
.s0		(shamt[0]),
.s1		(L_R),
.out	(out_0_1)
);

mux_4_1 i_mux_4_1_0_2(
.a		(din[2]),
.b		(din[3]),
.c		(din[2]),
.d		(din[1]),
.s0		(shamt[0]),
.s1		(L_R),
.out	(out_0_2)
);

mux_4_1 i_mux_4_1_0_3(
.a		(din[3]),
.b		(din[4]),
.c		(din[3]),
.d		(din[2]),
.s0		(shamt[0]),
.s1		(L_R),
.out	(out_0_3)
);

mux_4_1 i_mux_4_1_0_4(
.a		(din[4]),
.b		(din[5]),
.c		(din[4]),
.d		(din[3]),
.s0		(shamt[0]),
.s1		(L_R),
.out	(out_0_4)
);

mux_4_1 i_mux_4_1_0_5(
.a		(din[5]),
.b		(din[6]),
.c		(din[5]),
.d		(din[4]),
.s0		(shamt[0]),
.s1		(L_R),
.out	(out_0_5)
);

mux_4_1 i_mux_4_1_0_6(
.a		(din[6]),
.b		(din[7]),
.c		(din[6]),
.d		(din[5]),
.s0		(shamt[0]),
.s1		(L_R),
.out	(out_0_6)
);

mux_4_1 i_mux_4_1_0_7(
.a		(din[7]),
.b		(out_A_L),
.c		(din[7]),
.d		(din[6]),
.s0		(shamt[0]),
.s1		(L_R),
.out	(out_0_7)
);

mux_4_1 i_mux_4_1_1_0(
.a		(out_0_0),
.b		(out_0_2),
.c		(out_0_0),
.d		(1'b0),
.s0		(shamt[1]),
.s1		(L_R),
.out	(out_1_0)
);

mux_4_1 i_mux_4_1_1_1(
.a		(out_0_1),
.b		(out_0_3),
.c		(out_0_1),
.d		(1'b0),
.s0		(shamt[1]),
.s1		(L_R),
.out	(out_1_1)
);

mux_4_1 i_mux_4_1_1_2(
.a		(out_0_2),
.b		(out_0_4),
.c		(out_0_2),
.d		(out_0_0),
.s0		(shamt[1]),
.s1		(L_R),
.out	(out_1_2)
);

mux_4_1 i_mux_4_1_1_3(
.a		(out_0_3),
.b		(out_0_5),
.c		(out_0_3),
.d		(out_0_1),
.s0		(shamt[1]),
.s1		(L_R),
.out	(out_1_3)
);

mux_4_1 i_mux_4_1_1_4(
.a		(out_0_4),
.b		(out_0_6),
.c		(out_0_4),
.d		(out_0_2),
.s0		(shamt[1]),
.s1		(L_R),
.out	(out_1_4)
);

mux_4_1 i_mux_4_1_1_5(
.a		(out_0_5),
.b		(out_0_7),
.c		(out_0_5),
.d		(out_0_3),
.s0		(shamt[1]),
.s1		(L_R),
.out	(out_1_5)
);

mux_4_1 i_mux_4_1_1_6(
.a		(out_0_6),
.b		(out_A_L),
.c		(out_0_6),
.d		(out_0_4),
.s0		(shamt[1]),
.s1		(L_R),
.out	(out_1_6)
);

mux_4_1 i_mux_4_1_1_7(
.a		(out_0_7),
.b		(out_A_L),
.c		(out_0_7),
.d		(out_0_5),
.s0		(shamt[1]),
.s1		(L_R),
.out	(out_1_7)
);

mux_4_1 i_mux_4_1_2_0(
.a		(out_0_0),
.b		(out_0_4),
.c		(out_0_0),
.d		(1'b0),
.s0		(shamt[2]),
.s1		(L_R),
.out	(dout[0])
);

mux_4_1 i_mux_4_1_2_1(
.a		(out_0_1),
.b		(out_0_5),
.c		(out_0_1),
.d		(1'b0),
.s0		(shamt[2]),
.s1		(L_R),
.out	(dout[1])
);

mux_4_1 i_mux_4_1_2_2(
.a		(out_0_2),
.b		(out_0_6),
.c		(out_0_2),
.d		(1'b0),
.s0		(shamt[2]),
.s1		(L_R),
.out	(dout[2])
);

mux_4_1 i_mux_4_1_2_3(
.a		(out_0_3),
.b		(out_0_7),
.c		(out_0_3),
.d		(1'b0),
.s0		(shamt[2]),
.s1		(L_R),
.out	(dout[3])
);

mux_4_1 i_mux_4_1_2_4(
.a		(out_0_4),
.b		(out_A_L),
.c		(out_0_4),
.d		(out_1_0),
.s0		(shamt[2]),
.s1		(L_R),
.out	(dout[4])
);

mux_4_1 i_mux_4_1_2_5(
.a		(out_0_5),
.b		(out_A_L),
.c		(out_0_5),
.d		(out_1_1),
.s0		(shamt[2]),
.s1		(L_R),
.out	(dout[5])
);

mux_4_1 i_mux_4_1_2_6(
.a		(out_0_6),
.b		(out_A_L),
.c		(out_0_3),
.d		(out_1_2),
.s0		(shamt[2]),
.s1		(L_R),
.out	(dout[6])
);

mux_4_1 i_mux_4_1_2_7(
.a		(out_0_7),
.b		(out_A_L),
.c		(out_0_7),
.d		(out_1_3),
.s0		(shamt[2]),
.s1		(L_R),
.out	(dout[7])
);

endmodule

