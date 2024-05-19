module compare(
	input  [3:0] a,
	input  [3:0] b,
	output			 result
);

	wire carry,zero,overflow;
	wire [3:0] out;
	
	sub_add compare_sub_add(
	.a			(a),
	.b			(b),
	.cin		(1),
	.carry	(carry),
	.zero		(zero),
	.overflow(overflow),
	.result	(out)
);

	assign result = ((carry && overflow) || (out[3] && (!overflow)) &&  (!zero));

endmodule

