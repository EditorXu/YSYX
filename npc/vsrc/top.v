module top (
    input clk,
    input rst,
		input [10:0] cin,
    output VGA_CLK,
    output VGA_HSYNC,
    output VGA_VSYNC,
    output VGA_BLANK_N,
    output [7:0] VGA_R,
    output [7:0] VGA_G,
    output [7:0] VGA_B,
    output [7:0] seg0,
    output [7:0] seg1,
		output [6:0] out
);

wire carry,zero,overflow;

assign out[4] = (!cin[9] && !cin[10] && carry);
assign out[5] = (!cin[9] && !cin[10] && zero);
assign out[6] = (!cin[9] && !cin[10] && overflow);
assign seg1 = (!cin[9] && !cin[10]) ? ((((carry && overflow) || (out[3] && (!overflow))) && (!zero)) ? 8'b11111101 : 8'b11111111) : 8'b00000000;

alu i_alu(
.sel			(cin[10:8]),
.b				(cin[7:4]),
.a				(cin[3:0]),
.out			(out[3:0]),
.carry		(carry),
.zero			(zero),
.overflow	(overflow)
);

wire [3:0] dout;

assign dout = ({4{out[3]}}^out[3:0]) + {3'b000,out[3]};

myseg mu_seg0(
		.x({1'b0,dout[2:0]}),
		.en(1'b1),
    .HEX0(seg0)
);
assign VGA_CLK = clk;

wire [9:0] h_addr;
wire [9:0] v_addr;
wire [23:0] vga_data;

vga_ctrl my_vga_ctrl(
    .pclk(clk),
    .reset(rst),
    .vga_data(vga_data),
    .h_addr(h_addr),
    .v_addr(v_addr),
    .hsync(VGA_HSYNC),
    .vsync(VGA_VSYNC),
    .valid(VGA_BLANK_N),
    .vga_r(VGA_R),
    .vga_g(VGA_G),
    .vga_b(VGA_B)
);

vmem my_vmem(
    .h_addr(h_addr),
    .v_addr(v_addr[8:0]),
    .vga_data(vga_data)
);

endmodule

module vmem (
    input [9:0] h_addr,
    input [8:0] v_addr,
    output [23:0] vga_data
);

reg [23:0] vga_mem [524287:0];

initial begin
    $readmemh("resource/picture.hex", vga_mem);
end

assign vga_data = vga_mem[{h_addr, v_addr}];

endmodule
