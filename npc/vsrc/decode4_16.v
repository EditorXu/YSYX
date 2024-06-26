module decode4_16(
  input  [3:0] x,
  input  en,
  output reg [15:0]y
 );

  always @(x or en)
    if (en)
    begin
      case (x)
            4'd0 : y = 16'b0000000000000001;
            4'd1 : y = 16'b0000000000000010;
            4'd2 : y = 16'b0000000000000100;
            4'd3 : y = 16'b0000000000001000;
            4'd4 : y = 16'b0000000000010000;
            4'd5 : y = 16'b0000000000100000;
            4'd6 : y = 16'b0000000001000000;
            4'd7 : y = 16'b0000000010000000;
						4'd8 : y = 16'b0000000100000000;
						4'd9 : y = 16'b0000001000000000;
						4'd10: y = 16'b0000010000000000;
						4'd11: y = 16'b0000100000000000;
						4'd12: y = 16'b0001000000000000;
						4'd13: y = 16'b0010000000000000;
						4'd14: y = 16'b0100000000000000;
						4'd15: y = 16'b1000000000000000;
      endcase
    end
    else  y = 16'b0000000000000000;

endmodule
