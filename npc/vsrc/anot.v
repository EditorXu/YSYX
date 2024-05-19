module anot(
	input  [3:0] a,
	output [3:0] result
); 
	
	assign result = a ^ 4'b1111;

endmodule

