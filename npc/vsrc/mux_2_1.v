module mux_2_1(
input s,
input in,
output reg out
);

always@(*)
begin
if(s)
	begin
	out = in;
	end
else
	begin
	out = 1'b0;
	end
end

endmodule

