module alu(
	input				[2:0] sel,
	input				[3:0] a,
	input				[3:0] b,
	output	reg [3:0]	out,
	output					  carry,
	output						zero,
	output						overflow
);

	wire [3:0] add_out, sub_out, not_out, xor_out, or_out, and_out;

	wire compare_out, equal_out;	
	wire carry1, zero1, overflow1;
	wire carry2, zero2, overflow2;

	sub_add		iadd_out(
	.a				(a),
	.b				(b),
	.cin			(0),
	.carry		(carry1),
	.zero			(zero1),
	.overflow	(overflow1),
	.result		(add_out)
);

	sub_add		isub_out(
	.a				(a),
	.b				(b),
	.cin			(1),
	.carry		(carry2),
	.zero			(zero2),
	.overflow	(overflow2),
	.result		(sub_out)
);

	anot			inot_out(
	.a				(a),
	.result		(not_out)
);

	aand			iand_out(
	.a				(a),
	.b				(b),
	.result		(and_out)
);

	aor				ior_out(
	.a				(a),
	.b				(b),
	.result		(or_out)
);

	axor			ixor_out(
	.a				(a),
	.b				(b),
	.result		(xor_out)
);

	compare		icompare_out(
	.a				(a),
	.b				(b),
	.result		(compare_out)
);

	equal			iequal_out(
	.a				(a),
	.b				(b),
	.result		(equal_out)
);

	assign zero			= zero1			| zero2;
	assign carry	  = carry1		| carry2;
	assign overflow = overflow1 | overflow2;

	always@(*)
	begin
		case(sel)
			3'b000 : out = add_out;
			3'b001 : out = sub_out;
			3'b010 : out = not_out;
			3'b011 : out = and_out;
			3'b100 : out = or_out;
			3'b101 : out = xor_out;
			3'b110 : out = {3'b000,compare_out};
			3'b111 : out = {3'b000,equal_out};
		endcase
	end

endmodule

