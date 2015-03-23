module BRD_PACKET_ENGINE (

  // input signals
  input CLK,
  input OUT_TICK,
  input ETH_WR_DONE,
  input ETH_WR_BUSY,
  input ETH_RD_DONE,
  input ETH_RD_BUSY,
  input ETH_RD_READY,

  // input vectors
  input [9:0] IN_ETH_STREAM,
  input [23:0] PROCESS_TIME,
  input [15:0] TEMPERATURE,
  input [15:0] V_VCCINT,
  input [15:0] V_VCCAUX,
  input [7:0] BUTTONS,
  input [23:0] ETH_RD_PIX,
  input [127:0] USER_STATUS,

  // output signals
  output ETH_WR_CLK,
  output ETH_WR_STB,
  output ETH_RD_CLK,

  // output vectors
  output [9:0] OUT_ETH_STREAM,

  // registered output signals
  output reg ETH_BUSY,
  output reg CTRL_BUSY,
  output reg CTRL_STRB,
  output reg ETH_WR_GO,
  output reg ETH_RD_GO,
  output reg ETH_RD_STB,

  // registered output vectors
  output reg [15:0] CTRL_ENABLES,
  output reg [15:0] IMG_SIZE_X,
  output reg [15:0] IMG_SIZE_Y,
  output reg [399:0] CTRL_COEFF,
  output reg [15:0] ETH_WR_START_X,
  output reg [15:0] ETH_WR_LINE,
  output reg [15:0] ETH_WR_NUM_PIXELS,
  output reg [23:0] ETH_WR_PIX,
  output reg [15:0] ETH_RD_START_X,
  output reg [15:0] ETH_RD_LINE,
  output reg [15:0] ETH_RD_NUM_PIXELS,
  output reg [7:0] USER_CTRL_EN,
  output reg [15:0] USER_CTRL
);

/*******************************************************************
*    Parameters
*******************************************************************/

  parameter [7:0] FIRMWARE_VERSION = 8'hff;
  parameter [39:0] BOARD_TYPE = 40'h53_50_36_30_31;
  parameter SERVER_MAC = 	48'h00_10_8B_F1_F5_7D;
  parameter MY_MAC = 	48'h00_10_8B_F1_F5_7E;
  parameter OP_CONTROL = 	8'h01;
  parameter OP_STATUS = 	8'h02;
  parameter OP_WRITE = 	8'h03;
  parameter OP_READ = 	8'h04;
  parameter OP_USER_CONTROL = 	8'h05;
  parameter MAX_PAYLOAD = 	8'd56;

/*******************************************************************
*    Local Signal Declarations
*******************************************************************/

  // scalar signals
  wire in_cke;
  wire in_frm;
  wire e_rd_stb;

  // scalar registers
  reg opcode_is_control;
  reg snd_ctrl_ack;
  reg snd_status_ack;
  reg wr_dat_en;
  reg snd_wr_ack;
  reg rd_rdy_lat;
  reg snd_rd_ack;
  reg snd_user_ctrl_ack;
  reg tx_frm;

  // vector signals
  wire [7:0] in_dat;

  // vector registers
  reg [10:0] rx_cnt;
  reg [7:0] rx_opcode;
  reg [MAX_PAYLOAD:1] pyld_byte_en;
  reg [2:0] wr_1_every_3_sr;
  reg [10:0] wr_cnt;
  reg [15:0] rd_pyld_len;
  reg [15:0] rd_tx_cnt;
  reg [2:0] rd_1_every_3_sr;
  reg [10:0] rd_cnt;
  reg [10:0] tx_cnt;
  reg [567:0] tx_shift;

/*******************************************************************
*    Initial Values
*******************************************************************/

  initial begin
    rx_cnt = 0;
    rx_opcode = 0;
    pyld_byte_en = 0;
    opcode_is_control = 0;
    snd_ctrl_ack = 0;
    snd_status_ack = 0;
    wr_dat_en =  0;
    wr_1_every_3_sr = 0;
    wr_cnt =  0;
    snd_wr_ack = 0;
    rd_pyld_len = 0;
    rd_tx_cnt = 0;
    rd_rdy_lat = 0;
    snd_rd_ack = 0;
    rd_1_every_3_sr = 0;
    rd_cnt =  0;
    snd_user_ctrl_ack = 0;
    tx_cnt =  0;
    tx_frm =  0;
    tx_shift = 0;
  end

/*******************************************************************
*    Static Assignments
*******************************************************************/

  assign ETH_WR_CLK = CLK;
  assign ETH_WR_STB =  wr_1_every_3_sr[2];
  assign ETH_RD_CLK = CLK;

endmodule 
