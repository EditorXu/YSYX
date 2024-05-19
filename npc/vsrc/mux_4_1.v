module mux_4_1(
input a,
input b,
input c,
input d,
input s0,
input s1,
output reg out
);

always@(*)
begin
if(~s0)
	begin
	out = a;
	end
else
	begin
	if(s1)
		begin
		out = d;
		end
	else
		begin
		out = b;
		end
	end
end

endmodule

