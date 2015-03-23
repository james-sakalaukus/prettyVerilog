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
)

/*******************************************************************
*    Local Signal Declarations
*******************************************************************/
wire in_cke;
wire in_frm;
wire e_rd_stb;
wire test_cke;
wire status_cke;
wire stat_frm;
wire ETH_WR_CLK;
wire ETH_WR_GO;
wire ETH_WR_DONE;
wire ETH_WR_BUSY;
wire ETH_WR_STB;
wire ETH_RD_CLK;
wire ETH_RD_GO;
wire ETH_RD_DONE;
wire ETH_RD_BUSY;
wire ETH_RD_STB;
wire ETH_RD_READY;
wire ETH_BUSY;
wire phy_cke;
wire phy_frm;
reg rx_cnt;
reg rx_opcode;
reg pyld_byte_en;
reg opcode_is_control;
reg snd_ctrl_ack;
reg snd_status_ack;
reg wr_dat_en;
reg wr_1_every_3_sr;
reg wr_cnt;
reg snd_wr_ack;
reg rd_pyld_len;
reg rd_tx_cnt;
reg rd_rdy_lat;
reg snd_rd_ack;
reg rd_1_every_3_sr;
reg rd_cnt;
reg snd_user_ctrl_ack;
reg tx_cnt;
reg tx_frm;
reg tx_shift;
reg CLK;
reg out_cnt;
reg out_cke;
reg test_frm;
reg test_dat;
reg test_pkt_size;
reg test_cnt;
reg rd_dly;
wire [7:0] in_dat;
wire [1:0] speed;
wire [9:0] IN_TEST_STREAM;
wire [9:0] OUT_TEST_STREAM;
wire [7:0] stat_dat;
wire [15:0] CTRL_ENABLES;
wire [15:0] IMG_SIZE_X;
wire [15:0] IMG_SIZE_Y;
wire [399:0] CTRL_COEFF;
wire [23:0] PROCESS_TIME;
wire [15:0] TEMPERATURE;
wire [15:0] V_VCCINT;
wire [15:0] V_VCCAUX;
wire [15:0] ETH_WR_START_X;
wire [15:0] ETH_WR_LINE;
wire [15:0] ETH_WR_NUM_PIXELS;
wire [23:0] ETH_WR_PIX;
wire [15:0] ETH_RD_START_X;
wire [15:0] ETH_RD_LINE;
wire [15:0] ETH_RD_NUM_PIXELS;
wire [23:0] ETH_RD_PIX;
wire [9:0] TX_ETH_STREAM;
wire [7:0] phy_dat;
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
reg [3:0] out_cnt;
reg [7:0] test_dat;
reg [10:0] test_pkt_size;
reg [10:0] test_cnt;
reg [29:0] rd_dly;
/*******************************************************************
*    Initial Values
*******************************************************************/
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
CLK =  0;
out_cnt = 4;
out_cke = 0;
test_frm =  0;
test_dat = ;
test_pkt_size =  1054;
test_cnt =  11;
rd_dly = 0;

endmodule 
