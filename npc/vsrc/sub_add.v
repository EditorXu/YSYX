module sub_add(
	input	 [3:0]  a,
	input  [3:0]  b,
	input					cin,
	output				carry,
	output				zero,
	output				overflow,
	output [3:0]  result
);
	
	wire [3:0] bin;
	
	assign bin = ({4{cin}}^b) + {3'b000,cin};
	assign {carry,result} = a + bin;
	assign overflow = (a[2] == bin[2]) && (result[2] != a[2]);
	assign zero = (!(| result[3:0]) || result[3:0] == 4'b1000);

endmodule

