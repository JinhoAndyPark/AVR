-- Copyright (C) 1991-2012 Altera Corporation
-- Your use of Altera Corporation's design tools, logic functions 
-- and other software and tools, and its AMPP partner logic 
-- functions, and any output files from any of the foregoing 
-- (including device programming or simulation files), and any 
-- associated documentation or information are expressly subject 
-- to the terms and conditions of the Altera Program License 
-- Subscription Agreement, Altera MegaCore Function License 
-- Agreement, or other applicable license agreement, including, 
-- without limitation, that your use is for the sole purpose of 
-- programming logic devices manufactured by Altera and sold by 
-- Altera or its authorized distributors.  Please refer to the 
-- applicable agreement for further details.

-- VENDOR "Altera"
-- PROGRAM "Quartus II 32-bit"
-- VERSION "Version 12.0 Build 263 08/02/2012 Service Pack 2 SJ Web Edition"

-- DATE "12/08/2012 17:15:52"

-- 
-- Device: Altera EP3C16F484C6 Package FBGA484
-- 

-- 
-- This VHDL file should be used for ModelSim-Altera (VHDL) only
-- 

LIBRARY ALTERA;
LIBRARY CYCLONEIII;
LIBRARY IEEE;
USE ALTERA.ALTERA_PRIMITIVES_COMPONENTS.ALL;
USE CYCLONEIII.CYCLONEIII_COMPONENTS.ALL;
USE IEEE.STD_LOGIC_1164.ALL;

ENTITY 	test IS
    PORT (
	clk : IN std_logic;
	key : IN std_logic;
	reset : IN std_logic;
	seg1 : OUT std_logic_vector(7 DOWNTO 0);
	seg2 : OUT std_logic_vector(7 DOWNTO 0);
	seg3 : OUT std_logic_vector(7 DOWNTO 0);
	seg4 : OUT std_logic_vector(7 DOWNTO 0)
	);
END test;

-- Design Ports Information
-- seg1[0]	=>  Location: PIN_E11,	 I/O Standard: 2.5 V,	 Current Strength: Default
-- seg1[1]	=>  Location: PIN_F11,	 I/O Standard: 2.5 V,	 Current Strength: Default
-- seg1[2]	=>  Location: PIN_H12,	 I/O Standard: 2.5 V,	 Current Strength: Default
-- seg1[3]	=>  Location: PIN_H13,	 I/O Standard: 2.5 V,	 Current Strength: Default
-- seg1[4]	=>  Location: PIN_G12,	 I/O Standard: 2.5 V,	 Current Strength: Default
-- seg1[5]	=>  Location: PIN_F12,	 I/O Standard: 2.5 V,	 Current Strength: Default
-- seg1[6]	=>  Location: PIN_F13,	 I/O Standard: 2.5 V,	 Current Strength: Default
-- seg1[7]	=>  Location: PIN_D13,	 I/O Standard: 2.5 V,	 Current Strength: Default
-- seg2[0]	=>  Location: PIN_A13,	 I/O Standard: 2.5 V,	 Current Strength: Default
-- seg2[1]	=>  Location: PIN_B13,	 I/O Standard: 2.5 V,	 Current Strength: Default
-- seg2[2]	=>  Location: PIN_C13,	 I/O Standard: 2.5 V,	 Current Strength: Default
-- seg2[3]	=>  Location: PIN_A14,	 I/O Standard: 2.5 V,	 Current Strength: Default
-- seg2[4]	=>  Location: PIN_B14,	 I/O Standard: 2.5 V,	 Current Strength: Default
-- seg2[5]	=>  Location: PIN_E14,	 I/O Standard: 2.5 V,	 Current Strength: Default
-- seg2[6]	=>  Location: PIN_A15,	 I/O Standard: 2.5 V,	 Current Strength: Default
-- seg2[7]	=>  Location: PIN_B15,	 I/O Standard: 2.5 V,	 Current Strength: Default
-- seg3[0]	=>  Location: PIN_D15,	 I/O Standard: 2.5 V,	 Current Strength: Default
-- seg3[1]	=>  Location: PIN_A16,	 I/O Standard: 2.5 V,	 Current Strength: Default
-- seg3[2]	=>  Location: PIN_B16,	 I/O Standard: 2.5 V,	 Current Strength: Default
-- seg3[3]	=>  Location: PIN_E15,	 I/O Standard: 2.5 V,	 Current Strength: Default
-- seg3[4]	=>  Location: PIN_A17,	 I/O Standard: 2.5 V,	 Current Strength: Default
-- seg3[5]	=>  Location: PIN_B17,	 I/O Standard: 2.5 V,	 Current Strength: Default
-- seg3[6]	=>  Location: PIN_F14,	 I/O Standard: 2.5 V,	 Current Strength: Default
-- seg3[7]	=>  Location: PIN_A18,	 I/O Standard: 2.5 V,	 Current Strength: Default
-- seg4[0]	=>  Location: PIN_B18,	 I/O Standard: 2.5 V,	 Current Strength: Default
-- seg4[1]	=>  Location: PIN_F15,	 I/O Standard: 2.5 V,	 Current Strength: Default
-- seg4[2]	=>  Location: PIN_A19,	 I/O Standard: 2.5 V,	 Current Strength: Default
-- seg4[3]	=>  Location: PIN_B19,	 I/O Standard: 2.5 V,	 Current Strength: Default
-- seg4[4]	=>  Location: PIN_C19,	 I/O Standard: 2.5 V,	 Current Strength: Default
-- seg4[5]	=>  Location: PIN_D19,	 I/O Standard: 2.5 V,	 Current Strength: Default
-- seg4[6]	=>  Location: PIN_G15,	 I/O Standard: 2.5 V,	 Current Strength: Default
-- seg4[7]	=>  Location: PIN_G16,	 I/O Standard: 2.5 V,	 Current Strength: Default
-- clk	=>  Location: PIN_P22,	 I/O Standard: 2.5 V,	 Current Strength: Default
-- reset	=>  Location: PIN_H2,	 I/O Standard: 2.5 V,	 Current Strength: Default
-- key	=>  Location: PIN_P21,	 I/O Standard: 2.5 V,	 Current Strength: Default


ARCHITECTURE structure OF test IS
SIGNAL gnd : std_logic := '0';
SIGNAL vcc : std_logic := '1';
SIGNAL unknown : std_logic := 'X';
SIGNAL devoe : std_logic := '1';
SIGNAL devclrn : std_logic := '1';
SIGNAL devpor : std_logic := '1';
SIGNAL ww_devoe : std_logic;
SIGNAL ww_devclrn : std_logic;
SIGNAL ww_devpor : std_logic;
SIGNAL ww_clk : std_logic;
SIGNAL ww_key : std_logic;
SIGNAL ww_reset : std_logic;
SIGNAL ww_seg1 : std_logic_vector(7 DOWNTO 0);
SIGNAL ww_seg2 : std_logic_vector(7 DOWNTO 0);
SIGNAL ww_seg3 : std_logic_vector(7 DOWNTO 0);
SIGNAL ww_seg4 : std_logic_vector(7 DOWNTO 0);
SIGNAL \Mux2~3clkctrl_INCLK_bus\ : std_logic_vector(3 DOWNTO 0);
SIGNAL \Mux2~2_combout\ : std_logic;
SIGNAL \Equal0~6_combout\ : std_logic;
SIGNAL \reg[5]~6_combout\ : std_logic;
SIGNAL \count[3]~14_combout\ : std_logic;
SIGNAL \count[1]~15_combout\ : std_logic;
SIGNAL \clk~input_o\ : std_logic;
SIGNAL \vkey[5]~feeder_combout\ : std_logic;
SIGNAL \seg1[0]~output_o\ : std_logic;
SIGNAL \seg1[1]~output_o\ : std_logic;
SIGNAL \seg1[2]~output_o\ : std_logic;
SIGNAL \seg1[3]~output_o\ : std_logic;
SIGNAL \seg1[4]~output_o\ : std_logic;
SIGNAL \seg1[5]~output_o\ : std_logic;
SIGNAL \seg1[6]~output_o\ : std_logic;
SIGNAL \seg1[7]~output_o\ : std_logic;
SIGNAL \seg2[0]~output_o\ : std_logic;
SIGNAL \seg2[1]~output_o\ : std_logic;
SIGNAL \seg2[2]~output_o\ : std_logic;
SIGNAL \seg2[3]~output_o\ : std_logic;
SIGNAL \seg2[4]~output_o\ : std_logic;
SIGNAL \seg2[5]~output_o\ : std_logic;
SIGNAL \seg2[6]~output_o\ : std_logic;
SIGNAL \seg2[7]~output_o\ : std_logic;
SIGNAL \seg3[0]~output_o\ : std_logic;
SIGNAL \seg3[1]~output_o\ : std_logic;
SIGNAL \seg3[2]~output_o\ : std_logic;
SIGNAL \seg3[3]~output_o\ : std_logic;
SIGNAL \seg3[4]~output_o\ : std_logic;
SIGNAL \seg3[5]~output_o\ : std_logic;
SIGNAL \seg3[6]~output_o\ : std_logic;
SIGNAL \seg3[7]~output_o\ : std_logic;
SIGNAL \seg4[0]~output_o\ : std_logic;
SIGNAL \seg4[1]~output_o\ : std_logic;
SIGNAL \seg4[2]~output_o\ : std_logic;
SIGNAL \seg4[3]~output_o\ : std_logic;
SIGNAL \seg4[4]~output_o\ : std_logic;
SIGNAL \seg4[5]~output_o\ : std_logic;
SIGNAL \seg4[6]~output_o\ : std_logic;
SIGNAL \seg4[7]~output_o\ : std_logic;
SIGNAL \key~input_o\ : std_logic;
SIGNAL \count[2]~13_combout\ : std_logic;
SIGNAL \reset~input_o\ : std_logic;
SIGNAL \count~8_combout\ : std_logic;
SIGNAL \count~9_combout\ : std_logic;
SIGNAL \count[0]~10_combout\ : std_logic;
SIGNAL \count[1]~11_combout\ : std_logic;
SIGNAL \LessThan0~0_combout\ : std_logic;
SIGNAL \count[3]~12_combout\ : std_logic;
SIGNAL \Equal0~1_combout\ : std_logic;
SIGNAL \reg[2]~1_combout\ : std_logic;
SIGNAL \vkey[2]~feeder_combout\ : std_logic;
SIGNAL \vkey[7]~0_combout\ : std_logic;
SIGNAL \vkey[7]~1_combout\ : std_logic;
SIGNAL \Equal0~3_combout\ : std_logic;
SIGNAL \reg[4]~3_combout\ : std_logic;
SIGNAL \vkey[4]~feeder_combout\ : std_logic;
SIGNAL \Equal0~2_combout\ : std_logic;
SIGNAL \reg[3]~2_combout\ : std_logic;
SIGNAL \vkey[3]~feeder_combout\ : std_logic;
SIGNAL \Mux11~0_combout\ : std_logic;
SIGNAL \Equal0~0_combout\ : std_logic;
SIGNAL \reg[6]~0_combout\ : std_logic;
SIGNAL \Mux11~1_combout\ : std_logic;
SIGNAL \Equal0~4_combout\ : std_logic;
SIGNAL \reg[0]~4_combout\ : std_logic;
SIGNAL \vkey[0]~feeder_combout\ : std_logic;
SIGNAL \Equal0~5_combout\ : std_logic;
SIGNAL \reg[7]~5_combout\ : std_logic;
SIGNAL \Mux2~0_combout\ : std_logic;
SIGNAL \Equal0~7_combout\ : std_logic;
SIGNAL \reg[1]~7_combout\ : std_logic;
SIGNAL \vkey[1]~feeder_combout\ : std_logic;
SIGNAL \Mux2~1_combout\ : std_logic;
SIGNAL \Mux2~3_combout\ : std_logic;
SIGNAL \Mux2~3clkctrl_outclk\ : std_logic;
SIGNAL \Mux3~0_combout\ : std_logic;
SIGNAL \Mux3~1_combout\ : std_logic;
SIGNAL \Mux1~0_combout\ : std_logic;
SIGNAL \Mux1~1_combout\ : std_logic;
SIGNAL \Mux0~0_combout\ : std_logic;
SIGNAL \Mux0~1_combout\ : std_logic;
SIGNAL \Mux10~0_combout\ : std_logic;
SIGNAL \Mux9~0_combout\ : std_logic;
SIGNAL \Mux8~0_combout\ : std_logic;
SIGNAL \Mux7~0_combout\ : std_logic;
SIGNAL \Mux6~0_combout\ : std_logic;
SIGNAL \Mux5~0_combout\ : std_logic;
SIGNAL \Mux4~0_combout\ : std_logic;
SIGNAL vkey : std_logic_vector(7 DOWNTO 0);
SIGNAL reg : std_logic_vector(7 DOWNTO 0);
SIGNAL digit : std_logic_vector(3 DOWNTO 0);
SIGNAL count : std_logic_vector(3 DOWNTO 0);
SIGNAL \ALT_INV_clk~input_o\ : std_logic;
SIGNAL \ALT_INV_Mux4~0_combout\ : std_logic;

BEGIN

ww_clk <= clk;
ww_key <= key;
ww_reset <= reset;
seg1 <= ww_seg1;
seg2 <= ww_seg2;
seg3 <= ww_seg3;
seg4 <= ww_seg4;
ww_devoe <= devoe;
ww_devclrn <= devclrn;
ww_devpor <= devpor;

\Mux2~3clkctrl_INCLK_bus\ <= (vcc & vcc & vcc & \Mux2~3_combout\);
\ALT_INV_clk~input_o\ <= NOT \clk~input_o\;
\ALT_INV_Mux4~0_combout\ <= NOT \Mux4~0_combout\;

-- Location: FF_X38_Y14_N11
\vkey[5]\ : dffeas
-- pragma translate_off
GENERIC MAP (
	is_wysiwyg => "true",
	power_up => "low")
-- pragma translate_on
PORT MAP (
	clk => \ALT_INV_clk~input_o\,
	d => \vkey[5]~feeder_combout\,
	ena => \vkey[7]~1_combout\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	q => vkey(5));

-- Location: LCCOMB_X38_Y14_N26
\Mux2~2\ : cycloneiii_lcell_comb
-- Equation(s):
-- \Mux2~2_combout\ = (!vkey(1) & ((vkey(2) & ((vkey(3)) # (vkey(6)))) # (!vkey(2) & (vkey(3) & vkey(6)))))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "0000111000001000",
	sum_lutc_input => "datac")
-- pragma translate_on
PORT MAP (
	dataa => vkey(2),
	datab => vkey(3),
	datac => vkey(1),
	datad => vkey(6),
	combout => \Mux2~2_combout\);

-- Location: FF_X40_Y14_N13
\reg[5]\ : dffeas
-- pragma translate_off
GENERIC MAP (
	is_wysiwyg => "true",
	power_up => "low")
-- pragma translate_on
PORT MAP (
	clk => \ALT_INV_clk~input_o\,
	d => \reg[5]~6_combout\,
	clrn => \reset~input_o\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	q => reg(5));

-- Location: LCCOMB_X39_Y14_N8
\Equal0~6\ : cycloneiii_lcell_comb
-- Equation(s):
-- \Equal0~6_combout\ = (count(0) & (!count(2) & (count(1) & !count(3))))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "0000000000100000",
	sum_lutc_input => "datac")
-- pragma translate_on
PORT MAP (
	dataa => count(0),
	datab => count(2),
	datac => count(1),
	datad => count(3),
	combout => \Equal0~6_combout\);

-- Location: LCCOMB_X40_Y14_N12
\reg[5]~6\ : cycloneiii_lcell_comb
-- Equation(s):
-- \reg[5]~6_combout\ = (\Equal0~6_combout\ & (\key~input_o\)) # (!\Equal0~6_combout\ & ((reg(5))))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "1100110011110000",
	sum_lutc_input => "datac")
-- pragma translate_on
PORT MAP (
	datab => \key~input_o\,
	datac => reg(5),
	datad => \Equal0~6_combout\,
	combout => \reg[5]~6_combout\);

-- Location: LCCOMB_X39_Y14_N12
\count[3]~14\ : cycloneiii_lcell_comb
-- Equation(s):
-- \count[3]~14_combout\ = (count(2)) # ((count(1) & count(0)))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "1111110011001100",
	sum_lutc_input => "datac")
-- pragma translate_on
PORT MAP (
	datab => count(2),
	datac => count(1),
	datad => count(0),
	combout => \count[3]~14_combout\);

-- Location: LCCOMB_X39_Y14_N6
\count[1]~15\ : cycloneiii_lcell_comb
-- Equation(s):
-- \count[1]~15_combout\ = (count(3) & (count(1) & ((count(0)) # (count(2)))))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "1100000010000000",
	sum_lutc_input => "datac")
-- pragma translate_on
PORT MAP (
	dataa => count(0),
	datab => count(3),
	datac => count(1),
	datad => count(2),
	combout => \count[1]~15_combout\);

-- Location: IOIBUF_X41_Y11_N1
\clk~input\ : cycloneiii_io_ibuf
-- pragma translate_off
GENERIC MAP (
	bus_hold => "false",
	simulate_z_as => "z")
-- pragma translate_on
PORT MAP (
	i => ww_clk,
	o => \clk~input_o\);

-- Location: LCCOMB_X38_Y14_N10
\vkey[5]~feeder\ : cycloneiii_lcell_comb
-- Equation(s):
-- \vkey[5]~feeder_combout\ = reg(5)

-- pragma translate_off
GENERIC MAP (
	lut_mask => "1111111100000000",
	sum_lutc_input => "datac")
-- pragma translate_on
PORT MAP (
	datad => reg(5),
	combout => \vkey[5]~feeder_combout\);

-- Location: IOOBUF_X21_Y29_N23
\seg1[0]~output\ : cycloneiii_io_obuf
-- pragma translate_off
GENERIC MAP (
	bus_hold => "false",
	open_drain_output => "false")
-- pragma translate_on
PORT MAP (
	i => \Mux10~0_combout\,
	devoe => ww_devoe,
	o => \seg1[0]~output_o\);

-- Location: IOOBUF_X21_Y29_N30
\seg1[1]~output\ : cycloneiii_io_obuf
-- pragma translate_off
GENERIC MAP (
	bus_hold => "false",
	open_drain_output => "false")
-- pragma translate_on
PORT MAP (
	i => \Mux9~0_combout\,
	devoe => ww_devoe,
	o => \seg1[1]~output_o\);

-- Location: IOOBUF_X26_Y29_N2
\seg1[2]~output\ : cycloneiii_io_obuf
-- pragma translate_off
GENERIC MAP (
	bus_hold => "false",
	open_drain_output => "false")
-- pragma translate_on
PORT MAP (
	i => \Mux8~0_combout\,
	devoe => ww_devoe,
	o => \seg1[2]~output_o\);

-- Location: IOOBUF_X28_Y29_N30
\seg1[3]~output\ : cycloneiii_io_obuf
-- pragma translate_off
GENERIC MAP (
	bus_hold => "false",
	open_drain_output => "false")
-- pragma translate_on
PORT MAP (
	i => \Mux7~0_combout\,
	devoe => ww_devoe,
	o => \seg1[3]~output_o\);

-- Location: IOOBUF_X26_Y29_N9
\seg1[4]~output\ : cycloneiii_io_obuf
-- pragma translate_off
GENERIC MAP (
	bus_hold => "false",
	open_drain_output => "false")
-- pragma translate_on
PORT MAP (
	i => \Mux6~0_combout\,
	devoe => ww_devoe,
	o => \seg1[4]~output_o\);

-- Location: IOOBUF_X28_Y29_N23
\seg1[5]~output\ : cycloneiii_io_obuf
-- pragma translate_off
GENERIC MAP (
	bus_hold => "false",
	open_drain_output => "false")
-- pragma translate_on
PORT MAP (
	i => \Mux5~0_combout\,
	devoe => ww_devoe,
	o => \seg1[5]~output_o\);

-- Location: IOOBUF_X26_Y29_N16
\seg1[6]~output\ : cycloneiii_io_obuf
-- pragma translate_off
GENERIC MAP (
	bus_hold => "false",
	open_drain_output => "false")
-- pragma translate_on
PORT MAP (
	i => \ALT_INV_Mux4~0_combout\,
	devoe => ww_devoe,
	o => \seg1[6]~output_o\);

-- Location: IOOBUF_X23_Y29_N9
\seg1[7]~output\ : cycloneiii_io_obuf
-- pragma translate_off
GENERIC MAP (
	bus_hold => "false",
	open_drain_output => "false")
-- pragma translate_on
PORT MAP (
	i => VCC,
	devoe => ww_devoe,
	o => \seg1[7]~output_o\);

-- Location: IOOBUF_X21_Y29_N2
\seg2[0]~output\ : cycloneiii_io_obuf
-- pragma translate_off
GENERIC MAP (
	bus_hold => "false",
	open_drain_output => "false")
-- pragma translate_on
PORT MAP (
	i => GND,
	devoe => ww_devoe,
	o => \seg2[0]~output_o\);

-- Location: IOOBUF_X21_Y29_N9
\seg2[1]~output\ : cycloneiii_io_obuf
-- pragma translate_off
GENERIC MAP (
	bus_hold => "false",
	open_drain_output => "false")
-- pragma translate_on
PORT MAP (
	i => GND,
	devoe => ww_devoe,
	o => \seg2[1]~output_o\);

-- Location: IOOBUF_X23_Y29_N2
\seg2[2]~output\ : cycloneiii_io_obuf
-- pragma translate_off
GENERIC MAP (
	bus_hold => "false",
	open_drain_output => "false")
-- pragma translate_on
PORT MAP (
	i => GND,
	devoe => ww_devoe,
	o => \seg2[2]~output_o\);

-- Location: IOOBUF_X23_Y29_N23
\seg2[3]~output\ : cycloneiii_io_obuf
-- pragma translate_off
GENERIC MAP (
	bus_hold => "false",
	open_drain_output => "false")
-- pragma translate_on
PORT MAP (
	i => GND,
	devoe => ww_devoe,
	o => \seg2[3]~output_o\);

-- Location: IOOBUF_X23_Y29_N30
\seg2[4]~output\ : cycloneiii_io_obuf
-- pragma translate_off
GENERIC MAP (
	bus_hold => "false",
	open_drain_output => "false")
-- pragma translate_on
PORT MAP (
	i => GND,
	devoe => ww_devoe,
	o => \seg2[4]~output_o\);

-- Location: IOOBUF_X28_Y29_N16
\seg2[5]~output\ : cycloneiii_io_obuf
-- pragma translate_off
GENERIC MAP (
	bus_hold => "false",
	open_drain_output => "false")
-- pragma translate_on
PORT MAP (
	i => GND,
	devoe => ww_devoe,
	o => \seg2[5]~output_o\);

-- Location: IOOBUF_X26_Y29_N23
\seg2[6]~output\ : cycloneiii_io_obuf
-- pragma translate_off
GENERIC MAP (
	bus_hold => "false",
	open_drain_output => "false")
-- pragma translate_on
PORT MAP (
	i => VCC,
	devoe => ww_devoe,
	o => \seg2[6]~output_o\);

-- Location: IOOBUF_X26_Y29_N30
\seg2[7]~output\ : cycloneiii_io_obuf
-- pragma translate_off
GENERIC MAP (
	bus_hold => "false",
	open_drain_output => "false")
-- pragma translate_on
PORT MAP (
	i => VCC,
	devoe => ww_devoe,
	o => \seg2[7]~output_o\);

-- Location: IOOBUF_X32_Y29_N30
\seg3[0]~output\ : cycloneiii_io_obuf
-- pragma translate_off
GENERIC MAP (
	bus_hold => "false",
	open_drain_output => "false")
-- pragma translate_on
PORT MAP (
	i => GND,
	devoe => ww_devoe,
	o => \seg3[0]~output_o\);

-- Location: IOOBUF_X30_Y29_N30
\seg3[1]~output\ : cycloneiii_io_obuf
-- pragma translate_off
GENERIC MAP (
	bus_hold => "false",
	open_drain_output => "false")
-- pragma translate_on
PORT MAP (
	i => GND,
	devoe => ww_devoe,
	o => \seg3[1]~output_o\);

-- Location: IOOBUF_X28_Y29_N2
\seg3[2]~output\ : cycloneiii_io_obuf
-- pragma translate_off
GENERIC MAP (
	bus_hold => "false",
	open_drain_output => "false")
-- pragma translate_on
PORT MAP (
	i => GND,
	devoe => ww_devoe,
	o => \seg3[2]~output_o\);

-- Location: IOOBUF_X30_Y29_N2
\seg3[3]~output\ : cycloneiii_io_obuf
-- pragma translate_off
GENERIC MAP (
	bus_hold => "false",
	open_drain_output => "false")
-- pragma translate_on
PORT MAP (
	i => GND,
	devoe => ww_devoe,
	o => \seg3[3]~output_o\);

-- Location: IOOBUF_X30_Y29_N16
\seg3[4]~output\ : cycloneiii_io_obuf
-- pragma translate_off
GENERIC MAP (
	bus_hold => "false",
	open_drain_output => "false")
-- pragma translate_on
PORT MAP (
	i => GND,
	devoe => ww_devoe,
	o => \seg3[4]~output_o\);

-- Location: IOOBUF_X30_Y29_N23
\seg3[5]~output\ : cycloneiii_io_obuf
-- pragma translate_off
GENERIC MAP (
	bus_hold => "false",
	open_drain_output => "false")
-- pragma translate_on
PORT MAP (
	i => GND,
	devoe => ww_devoe,
	o => \seg3[5]~output_o\);

-- Location: IOOBUF_X37_Y29_N2
\seg3[6]~output\ : cycloneiii_io_obuf
-- pragma translate_off
GENERIC MAP (
	bus_hold => "false",
	open_drain_output => "false")
-- pragma translate_on
PORT MAP (
	i => VCC,
	devoe => ww_devoe,
	o => \seg3[6]~output_o\);

-- Location: IOOBUF_X32_Y29_N16
\seg3[7]~output\ : cycloneiii_io_obuf
-- pragma translate_off
GENERIC MAP (
	bus_hold => "false",
	open_drain_output => "false")
-- pragma translate_on
PORT MAP (
	i => VCC,
	devoe => ww_devoe,
	o => \seg3[7]~output_o\);

-- Location: IOOBUF_X32_Y29_N23
\seg4[0]~output\ : cycloneiii_io_obuf
-- pragma translate_off
GENERIC MAP (
	bus_hold => "false",
	open_drain_output => "false")
-- pragma translate_on
PORT MAP (
	i => GND,
	devoe => ww_devoe,
	o => \seg4[0]~output_o\);

-- Location: IOOBUF_X39_Y29_N16
\seg4[1]~output\ : cycloneiii_io_obuf
-- pragma translate_off
GENERIC MAP (
	bus_hold => "false",
	open_drain_output => "false")
-- pragma translate_on
PORT MAP (
	i => GND,
	devoe => ww_devoe,
	o => \seg4[1]~output_o\);

-- Location: IOOBUF_X32_Y29_N9
\seg4[2]~output\ : cycloneiii_io_obuf
-- pragma translate_off
GENERIC MAP (
	bus_hold => "false",
	open_drain_output => "false")
-- pragma translate_on
PORT MAP (
	i => GND,
	devoe => ww_devoe,
	o => \seg4[2]~output_o\);

-- Location: IOOBUF_X32_Y29_N2
\seg4[3]~output\ : cycloneiii_io_obuf
-- pragma translate_off
GENERIC MAP (
	bus_hold => "false",
	open_drain_output => "false")
-- pragma translate_on
PORT MAP (
	i => GND,
	devoe => ww_devoe,
	o => \seg4[3]~output_o\);

-- Location: IOOBUF_X37_Y29_N23
\seg4[4]~output\ : cycloneiii_io_obuf
-- pragma translate_off
GENERIC MAP (
	bus_hold => "false",
	open_drain_output => "false")
-- pragma translate_on
PORT MAP (
	i => GND,
	devoe => ww_devoe,
	o => \seg4[4]~output_o\);

-- Location: IOOBUF_X37_Y29_N30
\seg4[5]~output\ : cycloneiii_io_obuf
-- pragma translate_off
GENERIC MAP (
	bus_hold => "false",
	open_drain_output => "false")
-- pragma translate_on
PORT MAP (
	i => GND,
	devoe => ww_devoe,
	o => \seg4[5]~output_o\);

-- Location: IOOBUF_X39_Y29_N30
\seg4[6]~output\ : cycloneiii_io_obuf
-- pragma translate_off
GENERIC MAP (
	bus_hold => "false",
	open_drain_output => "false")
-- pragma translate_on
PORT MAP (
	i => VCC,
	devoe => ww_devoe,
	o => \seg4[6]~output_o\);

-- Location: IOOBUF_X39_Y29_N23
\seg4[7]~output\ : cycloneiii_io_obuf
-- pragma translate_off
GENERIC MAP (
	bus_hold => "false",
	open_drain_output => "false")
-- pragma translate_on
PORT MAP (
	i => VCC,
	devoe => ww_devoe,
	o => \seg4[7]~output_o\);

-- Location: IOIBUF_X41_Y12_N22
\key~input\ : cycloneiii_io_ibuf
-- pragma translate_off
GENERIC MAP (
	bus_hold => "false",
	simulate_z_as => "z")
-- pragma translate_on
PORT MAP (
	i => ww_key,
	o => \key~input_o\);

-- Location: LCCOMB_X38_Y14_N24
\count[2]~13\ : cycloneiii_lcell_comb
-- Equation(s):
-- \count[2]~13_combout\ = (\count~9_combout\ & ((count(2) $ (\LessThan0~0_combout\)))) # (!\count~9_combout\ & (count(3) & (count(2))))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "0100101011100000",
	sum_lutc_input => "datac")
-- pragma translate_on
PORT MAP (
	dataa => \count~9_combout\,
	datab => count(3),
	datac => count(2),
	datad => \LessThan0~0_combout\,
	combout => \count[2]~13_combout\);

-- Location: IOIBUF_X0_Y21_N8
\reset~input\ : cycloneiii_io_ibuf
-- pragma translate_off
GENERIC MAP (
	bus_hold => "false",
	simulate_z_as => "z")
-- pragma translate_on
PORT MAP (
	i => ww_reset,
	o => \reset~input_o\);

-- Location: FF_X38_Y14_N25
\count[2]\ : dffeas
-- pragma translate_off
GENERIC MAP (
	is_wysiwyg => "true",
	power_up => "low")
-- pragma translate_on
PORT MAP (
	clk => \ALT_INV_clk~input_o\,
	d => \count[2]~13_combout\,
	clrn => \reset~input_o\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	q => count(2));

-- Location: LCCOMB_X38_Y14_N12
\count~8\ : cycloneiii_lcell_comb
-- Equation(s):
-- \count~8_combout\ = (count(2)) # (count(1))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "1111111111110000",
	sum_lutc_input => "datac")
-- pragma translate_on
PORT MAP (
	datac => count(2),
	datad => count(1),
	combout => \count~8_combout\);

-- Location: LCCOMB_X38_Y14_N22
\count~9\ : cycloneiii_lcell_comb
-- Equation(s):
-- \count~9_combout\ = (count(3) & (((!\count~8_combout\)))) # (!count(3) & (((count(0)) # (\count~8_combout\)) # (!\key~input_o\)))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "0011001111111101",
	sum_lutc_input => "datac")
-- pragma translate_on
PORT MAP (
	dataa => \key~input_o\,
	datab => count(3),
	datac => count(0),
	datad => \count~8_combout\,
	combout => \count~9_combout\);

-- Location: LCCOMB_X39_Y14_N20
\count[0]~10\ : cycloneiii_lcell_comb
-- Equation(s):
-- \count[0]~10_combout\ = (count(0) & (\count[3]~14_combout\ & (count(3) & !\count~9_combout\))) # (!count(0) & (((\count~9_combout\))))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "0000111110000000",
	sum_lutc_input => "datac")
-- pragma translate_on
PORT MAP (
	dataa => \count[3]~14_combout\,
	datab => count(3),
	datac => count(0),
	datad => \count~9_combout\,
	combout => \count[0]~10_combout\);

-- Location: FF_X39_Y14_N21
\count[0]\ : dffeas
-- pragma translate_off
GENERIC MAP (
	is_wysiwyg => "true",
	power_up => "low")
-- pragma translate_on
PORT MAP (
	clk => \ALT_INV_clk~input_o\,
	d => \count[0]~10_combout\,
	clrn => \reset~input_o\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	q => count(0));

-- Location: LCCOMB_X39_Y14_N26
\count[1]~11\ : cycloneiii_lcell_comb
-- Equation(s):
-- \count[1]~11_combout\ = (\count[1]~15_combout\) # ((\count~9_combout\ & (count(0) $ (count(1)))))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "1011111010101010",
	sum_lutc_input => "datac")
-- pragma translate_on
PORT MAP (
	dataa => \count[1]~15_combout\,
	datab => count(0),
	datac => count(1),
	datad => \count~9_combout\,
	combout => \count[1]~11_combout\);

-- Location: FF_X39_Y14_N27
\count[1]\ : dffeas
-- pragma translate_off
GENERIC MAP (
	is_wysiwyg => "true",
	power_up => "low")
-- pragma translate_on
PORT MAP (
	clk => \ALT_INV_clk~input_o\,
	d => \count[1]~11_combout\,
	clrn => \reset~input_o\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	q => count(1));

-- Location: LCCOMB_X39_Y14_N16
\LessThan0~0\ : cycloneiii_lcell_comb
-- Equation(s):
-- \LessThan0~0_combout\ = (count(1) & count(0))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "1111000000000000",
	sum_lutc_input => "datac")
-- pragma translate_on
PORT MAP (
	datac => count(1),
	datad => count(0),
	combout => \LessThan0~0_combout\);

-- Location: LCCOMB_X39_Y14_N0
\count[3]~12\ : cycloneiii_lcell_comb
-- Equation(s):
-- \count[3]~12_combout\ = (count(2) & (count(3) $ (((\LessThan0~0_combout\ & \count~9_combout\))))) # (!count(2) & (count(3) & ((\LessThan0~0_combout\) # (\count~9_combout\))))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "0111100011100000",
	sum_lutc_input => "datac")
-- pragma translate_on
PORT MAP (
	dataa => count(2),
	datab => \LessThan0~0_combout\,
	datac => count(3),
	datad => \count~9_combout\,
	combout => \count[3]~12_combout\);

-- Location: FF_X39_Y14_N1
\count[3]\ : dffeas
-- pragma translate_off
GENERIC MAP (
	is_wysiwyg => "true",
	power_up => "low")
-- pragma translate_on
PORT MAP (
	clk => \ALT_INV_clk~input_o\,
	d => \count[3]~12_combout\,
	clrn => \reset~input_o\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	q => count(3));

-- Location: LCCOMB_X39_Y14_N22
\Equal0~1\ : cycloneiii_lcell_comb
-- Equation(s):
-- \Equal0~1_combout\ = (count(1) & (!count(3) & (!count(0) & count(2))))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "0000001000000000",
	sum_lutc_input => "datac")
-- pragma translate_on
PORT MAP (
	dataa => count(1),
	datab => count(3),
	datac => count(0),
	datad => count(2),
	combout => \Equal0~1_combout\);

-- Location: LCCOMB_X40_Y14_N10
\reg[2]~1\ : cycloneiii_lcell_comb
-- Equation(s):
-- \reg[2]~1_combout\ = (\Equal0~1_combout\ & (\key~input_o\)) # (!\Equal0~1_combout\ & ((reg(2))))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "1100110011110000",
	sum_lutc_input => "datac")
-- pragma translate_on
PORT MAP (
	datab => \key~input_o\,
	datac => reg(2),
	datad => \Equal0~1_combout\,
	combout => \reg[2]~1_combout\);

-- Location: FF_X40_Y14_N11
\reg[2]\ : dffeas
-- pragma translate_off
GENERIC MAP (
	is_wysiwyg => "true",
	power_up => "low")
-- pragma translate_on
PORT MAP (
	clk => \ALT_INV_clk~input_o\,
	d => \reg[2]~1_combout\,
	clrn => \reset~input_o\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	q => reg(2));

-- Location: LCCOMB_X37_Y14_N20
\vkey[2]~feeder\ : cycloneiii_lcell_comb
-- Equation(s):
-- \vkey[2]~feeder_combout\ = reg(2)

-- pragma translate_off
GENERIC MAP (
	lut_mask => "1111111100000000",
	sum_lutc_input => "datac")
-- pragma translate_on
PORT MAP (
	datad => reg(2),
	combout => \vkey[2]~feeder_combout\);

-- Location: LCCOMB_X38_Y14_N28
\vkey[7]~0\ : cycloneiii_lcell_comb
-- Equation(s):
-- \vkey[7]~0_combout\ = (\reset~input_o\ & !count(2))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "0000000010101010",
	sum_lutc_input => "datac")
-- pragma translate_on
PORT MAP (
	dataa => \reset~input_o\,
	datad => count(2),
	combout => \vkey[7]~0_combout\);

-- Location: LCCOMB_X38_Y14_N18
\vkey[7]~1\ : cycloneiii_lcell_comb
-- Equation(s):
-- \vkey[7]~1_combout\ = (count(0) & (!count(1) & (count(3) & \vkey[7]~0_combout\)))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "0010000000000000",
	sum_lutc_input => "datac")
-- pragma translate_on
PORT MAP (
	dataa => count(0),
	datab => count(1),
	datac => count(3),
	datad => \vkey[7]~0_combout\,
	combout => \vkey[7]~1_combout\);

-- Location: FF_X37_Y14_N21
\vkey[2]\ : dffeas
-- pragma translate_off
GENERIC MAP (
	is_wysiwyg => "true",
	power_up => "low")
-- pragma translate_on
PORT MAP (
	clk => \ALT_INV_clk~input_o\,
	d => \vkey[2]~feeder_combout\,
	ena => \vkey[7]~1_combout\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	q => vkey(2));

-- Location: LCCOMB_X39_Y14_N30
\Equal0~3\ : cycloneiii_lcell_comb
-- Equation(s):
-- \Equal0~3_combout\ = (!count(1) & (!count(3) & (!count(0) & count(2))))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "0000000100000000",
	sum_lutc_input => "datac")
-- pragma translate_on
PORT MAP (
	dataa => count(1),
	datab => count(3),
	datac => count(0),
	datad => count(2),
	combout => \Equal0~3_combout\);

-- Location: LCCOMB_X40_Y14_N6
\reg[4]~3\ : cycloneiii_lcell_comb
-- Equation(s):
-- \reg[4]~3_combout\ = (\Equal0~3_combout\ & (\key~input_o\)) # (!\Equal0~3_combout\ & ((reg(4))))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "1100110011110000",
	sum_lutc_input => "datac")
-- pragma translate_on
PORT MAP (
	datab => \key~input_o\,
	datac => reg(4),
	datad => \Equal0~3_combout\,
	combout => \reg[4]~3_combout\);

-- Location: FF_X40_Y14_N7
\reg[4]\ : dffeas
-- pragma translate_off
GENERIC MAP (
	is_wysiwyg => "true",
	power_up => "low")
-- pragma translate_on
PORT MAP (
	clk => \ALT_INV_clk~input_o\,
	d => \reg[4]~3_combout\,
	clrn => \reset~input_o\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	q => reg(4));

-- Location: LCCOMB_X37_Y14_N4
\vkey[4]~feeder\ : cycloneiii_lcell_comb
-- Equation(s):
-- \vkey[4]~feeder_combout\ = reg(4)

-- pragma translate_off
GENERIC MAP (
	lut_mask => "1111111100000000",
	sum_lutc_input => "datac")
-- pragma translate_on
PORT MAP (
	datad => reg(4),
	combout => \vkey[4]~feeder_combout\);

-- Location: FF_X37_Y14_N5
\vkey[4]\ : dffeas
-- pragma translate_off
GENERIC MAP (
	is_wysiwyg => "true",
	power_up => "low")
-- pragma translate_on
PORT MAP (
	clk => \ALT_INV_clk~input_o\,
	d => \vkey[4]~feeder_combout\,
	ena => \vkey[7]~1_combout\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	q => vkey(4));

-- Location: LCCOMB_X39_Y14_N28
\Equal0~2\ : cycloneiii_lcell_comb
-- Equation(s):
-- \Equal0~2_combout\ = (count(0) & (count(2) & (!count(1) & !count(3))))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "0000000000001000",
	sum_lutc_input => "datac")
-- pragma translate_on
PORT MAP (
	dataa => count(0),
	datab => count(2),
	datac => count(1),
	datad => count(3),
	combout => \Equal0~2_combout\);

-- Location: LCCOMB_X40_Y14_N8
\reg[3]~2\ : cycloneiii_lcell_comb
-- Equation(s):
-- \reg[3]~2_combout\ = (\Equal0~2_combout\ & (\key~input_o\)) # (!\Equal0~2_combout\ & ((reg(3))))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "1100110011110000",
	sum_lutc_input => "datac")
-- pragma translate_on
PORT MAP (
	datab => \key~input_o\,
	datac => reg(3),
	datad => \Equal0~2_combout\,
	combout => \reg[3]~2_combout\);

-- Location: FF_X40_Y14_N9
\reg[3]\ : dffeas
-- pragma translate_off
GENERIC MAP (
	is_wysiwyg => "true",
	power_up => "low")
-- pragma translate_on
PORT MAP (
	clk => \ALT_INV_clk~input_o\,
	d => \reg[3]~2_combout\,
	clrn => \reset~input_o\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	q => reg(3));

-- Location: LCCOMB_X37_Y14_N6
\vkey[3]~feeder\ : cycloneiii_lcell_comb
-- Equation(s):
-- \vkey[3]~feeder_combout\ = reg(3)

-- pragma translate_off
GENERIC MAP (
	lut_mask => "1111111100000000",
	sum_lutc_input => "datac")
-- pragma translate_on
PORT MAP (
	datad => reg(3),
	combout => \vkey[3]~feeder_combout\);

-- Location: FF_X37_Y14_N7
\vkey[3]\ : dffeas
-- pragma translate_off
GENERIC MAP (
	is_wysiwyg => "true",
	power_up => "low")
-- pragma translate_on
PORT MAP (
	clk => \ALT_INV_clk~input_o\,
	d => \vkey[3]~feeder_combout\,
	ena => \vkey[7]~1_combout\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	q => vkey(3));

-- Location: LCCOMB_X37_Y14_N30
\Mux11~0\ : cycloneiii_lcell_comb
-- Equation(s):
-- \Mux11~0_combout\ = (vkey(0)) # ((vkey(2) & ((!vkey(3)) # (!vkey(4)))) # (!vkey(2) & ((vkey(4)) # (vkey(3)))))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "1011111111111110",
	sum_lutc_input => "datac")
-- pragma translate_on
PORT MAP (
	dataa => vkey(0),
	datab => vkey(2),
	datac => vkey(4),
	datad => vkey(3),
	combout => \Mux11~0_combout\);

-- Location: LCCOMB_X39_Y14_N10
\Equal0~0\ : cycloneiii_lcell_comb
-- Equation(s):
-- \Equal0~0_combout\ = (!count(0) & (!count(3) & (count(1) & !count(2))))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "0000000000010000",
	sum_lutc_input => "datac")
-- pragma translate_on
PORT MAP (
	dataa => count(0),
	datab => count(3),
	datac => count(1),
	datad => count(2),
	combout => \Equal0~0_combout\);

-- Location: LCCOMB_X40_Y14_N4
\reg[6]~0\ : cycloneiii_lcell_comb
-- Equation(s):
-- \reg[6]~0_combout\ = (\Equal0~0_combout\ & (\key~input_o\)) # (!\Equal0~0_combout\ & ((reg(6))))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "1100110011110000",
	sum_lutc_input => "datac")
-- pragma translate_on
PORT MAP (
	datab => \key~input_o\,
	datac => reg(6),
	datad => \Equal0~0_combout\,
	combout => \reg[6]~0_combout\);

-- Location: FF_X40_Y14_N5
\reg[6]\ : dffeas
-- pragma translate_off
GENERIC MAP (
	is_wysiwyg => "true",
	power_up => "low")
-- pragma translate_on
PORT MAP (
	clk => \ALT_INV_clk~input_o\,
	d => \reg[6]~0_combout\,
	clrn => \reset~input_o\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	q => reg(6));

-- Location: FF_X37_Y14_N19
\vkey[6]\ : dffeas
-- pragma translate_off
GENERIC MAP (
	is_wysiwyg => "true",
	power_up => "low")
-- pragma translate_on
PORT MAP (
	clk => \ALT_INV_clk~input_o\,
	asdata => reg(6),
	sload => VCC,
	ena => \vkey[7]~1_combout\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	q => vkey(6));

-- Location: LCCOMB_X37_Y14_N14
\Mux11~1\ : cycloneiii_lcell_comb
-- Equation(s):
-- \Mux11~1_combout\ = (!\Mux11~0_combout\ & vkey(6))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "0000111100000000",
	sum_lutc_input => "datac")
-- pragma translate_on
PORT MAP (
	datac => \Mux11~0_combout\,
	datad => vkey(6),
	combout => \Mux11~1_combout\);

-- Location: LCCOMB_X39_Y14_N24
\Equal0~4\ : cycloneiii_lcell_comb
-- Equation(s):
-- \Equal0~4_combout\ = (!count(0) & (!count(2) & (!count(1) & count(3))))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "0000000100000000",
	sum_lutc_input => "datac")
-- pragma translate_on
PORT MAP (
	dataa => count(0),
	datab => count(2),
	datac => count(1),
	datad => count(3),
	combout => \Equal0~4_combout\);

-- Location: LCCOMB_X40_Y14_N20
\reg[0]~4\ : cycloneiii_lcell_comb
-- Equation(s):
-- \reg[0]~4_combout\ = (\Equal0~4_combout\ & (\key~input_o\)) # (!\Equal0~4_combout\ & ((reg(0))))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "1100110011110000",
	sum_lutc_input => "datac")
-- pragma translate_on
PORT MAP (
	datab => \key~input_o\,
	datac => reg(0),
	datad => \Equal0~4_combout\,
	combout => \reg[0]~4_combout\);

-- Location: FF_X40_Y14_N21
\reg[0]\ : dffeas
-- pragma translate_off
GENERIC MAP (
	is_wysiwyg => "true",
	power_up => "low")
-- pragma translate_on
PORT MAP (
	clk => \ALT_INV_clk~input_o\,
	d => \reg[0]~4_combout\,
	clrn => \reset~input_o\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	q => reg(0));

-- Location: LCCOMB_X38_Y14_N20
\vkey[0]~feeder\ : cycloneiii_lcell_comb
-- Equation(s):
-- \vkey[0]~feeder_combout\ = reg(0)

-- pragma translate_off
GENERIC MAP (
	lut_mask => "1111111100000000",
	sum_lutc_input => "datac")
-- pragma translate_on
PORT MAP (
	datad => reg(0),
	combout => \vkey[0]~feeder_combout\);

-- Location: FF_X38_Y14_N21
\vkey[0]\ : dffeas
-- pragma translate_off
GENERIC MAP (
	is_wysiwyg => "true",
	power_up => "low")
-- pragma translate_on
PORT MAP (
	clk => \ALT_INV_clk~input_o\,
	d => \vkey[0]~feeder_combout\,
	ena => \vkey[7]~1_combout\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	q => vkey(0));

-- Location: LCCOMB_X39_Y14_N2
\Equal0~5\ : cycloneiii_lcell_comb
-- Equation(s):
-- \Equal0~5_combout\ = (count(0) & (!count(3) & (!count(1) & !count(2))))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "0000000000000010",
	sum_lutc_input => "datac")
-- pragma translate_on
PORT MAP (
	dataa => count(0),
	datab => count(3),
	datac => count(1),
	datad => count(2),
	combout => \Equal0~5_combout\);

-- Location: LCCOMB_X40_Y14_N2
\reg[7]~5\ : cycloneiii_lcell_comb
-- Equation(s):
-- \reg[7]~5_combout\ = (\Equal0~5_combout\ & (\key~input_o\)) # (!\Equal0~5_combout\ & ((reg(7))))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "1100110011110000",
	sum_lutc_input => "datac")
-- pragma translate_on
PORT MAP (
	datab => \key~input_o\,
	datac => reg(7),
	datad => \Equal0~5_combout\,
	combout => \reg[7]~5_combout\);

-- Location: FF_X40_Y14_N3
\reg[7]\ : dffeas
-- pragma translate_off
GENERIC MAP (
	is_wysiwyg => "true",
	power_up => "low")
-- pragma translate_on
PORT MAP (
	clk => \ALT_INV_clk~input_o\,
	d => \reg[7]~5_combout\,
	clrn => \reset~input_o\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	q => reg(7));

-- Location: FF_X38_Y14_N5
\vkey[7]\ : dffeas
-- pragma translate_off
GENERIC MAP (
	is_wysiwyg => "true",
	power_up => "low")
-- pragma translate_on
PORT MAP (
	clk => \ALT_INV_clk~input_o\,
	asdata => reg(7),
	sload => VCC,
	ena => \vkey[7]~1_combout\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	q => vkey(7));

-- Location: LCCOMB_X38_Y14_N4
\Mux2~0\ : cycloneiii_lcell_comb
-- Equation(s):
-- \Mux2~0_combout\ = (vkey(5) & (!vkey(0) & (vkey(7) $ (vkey(6)))))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "0000001000100000",
	sum_lutc_input => "datac")
-- pragma translate_on
PORT MAP (
	dataa => vkey(5),
	datab => vkey(0),
	datac => vkey(7),
	datad => vkey(6),
	combout => \Mux2~0_combout\);

-- Location: LCCOMB_X39_Y14_N14
\Equal0~7\ : cycloneiii_lcell_comb
-- Equation(s):
-- \Equal0~7_combout\ = (count(1) & (!count(3) & (count(0) & count(2))))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "0010000000000000",
	sum_lutc_input => "datac")
-- pragma translate_on
PORT MAP (
	dataa => count(1),
	datab => count(3),
	datac => count(0),
	datad => count(2),
	combout => \Equal0~7_combout\);

-- Location: LCCOMB_X40_Y14_N22
\reg[1]~7\ : cycloneiii_lcell_comb
-- Equation(s):
-- \reg[1]~7_combout\ = (\Equal0~7_combout\ & (\key~input_o\)) # (!\Equal0~7_combout\ & ((reg(1))))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "1100110011110000",
	sum_lutc_input => "datac")
-- pragma translate_on
PORT MAP (
	datab => \key~input_o\,
	datac => reg(1),
	datad => \Equal0~7_combout\,
	combout => \reg[1]~7_combout\);

-- Location: FF_X40_Y14_N23
\reg[1]\ : dffeas
-- pragma translate_off
GENERIC MAP (
	is_wysiwyg => "true",
	power_up => "low")
-- pragma translate_on
PORT MAP (
	clk => \ALT_INV_clk~input_o\,
	d => \reg[1]~7_combout\,
	clrn => \reset~input_o\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	q => reg(1));

-- Location: LCCOMB_X38_Y14_N8
\vkey[1]~feeder\ : cycloneiii_lcell_comb
-- Equation(s):
-- \vkey[1]~feeder_combout\ = reg(1)

-- pragma translate_off
GENERIC MAP (
	lut_mask => "1111111100000000",
	sum_lutc_input => "datac")
-- pragma translate_on
PORT MAP (
	datad => reg(1),
	combout => \vkey[1]~feeder_combout\);

-- Location: FF_X38_Y14_N9
\vkey[1]\ : dffeas
-- pragma translate_off
GENERIC MAP (
	is_wysiwyg => "true",
	power_up => "low")
-- pragma translate_on
PORT MAP (
	clk => \ALT_INV_clk~input_o\,
	d => \vkey[1]~feeder_combout\,
	ena => \vkey[7]~1_combout\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	q => vkey(1));

-- Location: LCCOMB_X37_Y14_N22
\Mux2~1\ : cycloneiii_lcell_comb
-- Equation(s):
-- \Mux2~1_combout\ = (vkey(3) & (((!vkey(1) & vkey(6))))) # (!vkey(3) & (vkey(2) $ ((vkey(1)))))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "0001111000010100",
	sum_lutc_input => "datac")
-- pragma translate_on
PORT MAP (
	dataa => vkey(3),
	datab => vkey(2),
	datac => vkey(1),
	datad => vkey(6),
	combout => \Mux2~1_combout\);

-- Location: LCCOMB_X38_Y14_N30
\Mux2~3\ : cycloneiii_lcell_comb
-- Equation(s):
-- \Mux2~3_combout\ = (\Mux2~0_combout\ & ((vkey(4) & (\Mux2~2_combout\)) # (!vkey(4) & ((\Mux2~1_combout\)))))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "1011000010000000",
	sum_lutc_input => "datac")
-- pragma translate_on
PORT MAP (
	dataa => \Mux2~2_combout\,
	datab => vkey(4),
	datac => \Mux2~0_combout\,
	datad => \Mux2~1_combout\,
	combout => \Mux2~3_combout\);

-- Location: CLKCTRL_G8
\Mux2~3clkctrl\ : cycloneiii_clkctrl
-- pragma translate_off
GENERIC MAP (
	clock_type => "global clock",
	ena_register_mode => "none")
-- pragma translate_on
PORT MAP (
	inclk => \Mux2~3clkctrl_INCLK_bus\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	outclk => \Mux2~3clkctrl_outclk\);

-- Location: LCCOMB_X37_Y14_N8
\digit[3]\ : cycloneiii_lcell_comb
-- Equation(s):
-- digit(3) = (GLOBAL(\Mux2~3clkctrl_outclk\) & ((\Mux11~1_combout\))) # (!GLOBAL(\Mux2~3clkctrl_outclk\) & (digit(3)))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "1111000010101010",
	sum_lutc_input => "datac")
-- pragma translate_on
PORT MAP (
	dataa => digit(3),
	datac => \Mux11~1_combout\,
	datad => \Mux2~3clkctrl_outclk\,
	combout => digit(3));

-- Location: LCCOMB_X37_Y14_N0
\Mux3~0\ : cycloneiii_lcell_comb
-- Equation(s):
-- \Mux3~0_combout\ = (vkey(2) & ((vkey(6) & ((!vkey(3)))) # (!vkey(6) & (vkey(4) & vkey(3))))) # (!vkey(2) & (vkey(6) & (!vkey(4))))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "0010010010001100",
	sum_lutc_input => "datac")
-- pragma translate_on
PORT MAP (
	dataa => vkey(2),
	datab => vkey(6),
	datac => vkey(4),
	datad => vkey(3),
	combout => \Mux3~0_combout\);

-- Location: LCCOMB_X37_Y14_N28
\Mux3~1\ : cycloneiii_lcell_comb
-- Equation(s):
-- \Mux3~1_combout\ = (!vkey(0) & \Mux3~0_combout\)

-- pragma translate_off
GENERIC MAP (
	lut_mask => "0101010100000000",
	sum_lutc_input => "datac")
-- pragma translate_on
PORT MAP (
	dataa => vkey(0),
	datad => \Mux3~0_combout\,
	combout => \Mux3~1_combout\);

-- Location: LCCOMB_X37_Y14_N16
\digit[0]\ : cycloneiii_lcell_comb
-- Equation(s):
-- digit(0) = (GLOBAL(\Mux2~3clkctrl_outclk\) & ((\Mux3~1_combout\))) # (!GLOBAL(\Mux2~3clkctrl_outclk\) & (digit(0)))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "1111110000001100",
	sum_lutc_input => "datac")
-- pragma translate_on
PORT MAP (
	datab => digit(0),
	datac => \Mux2~3clkctrl_outclk\,
	datad => \Mux3~1_combout\,
	combout => digit(0));

-- Location: LCCOMB_X37_Y14_N24
\Mux1~0\ : cycloneiii_lcell_comb
-- Equation(s):
-- \Mux1~0_combout\ = (!vkey(0) & ((vkey(6) & (vkey(4) $ (vkey(2)))) # (!vkey(6) & (vkey(4) & vkey(2)))))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "0001010001000000",
	sum_lutc_input => "datac")
-- pragma translate_on
PORT MAP (
	dataa => vkey(0),
	datab => vkey(6),
	datac => vkey(4),
	datad => vkey(2),
	combout => \Mux1~0_combout\);

-- Location: LCCOMB_X37_Y14_N2
\Mux1~1\ : cycloneiii_lcell_comb
-- Equation(s):
-- \Mux1~1_combout\ = (!vkey(1) & \Mux1~0_combout\)

-- pragma translate_off
GENERIC MAP (
	lut_mask => "0000111100000000",
	sum_lutc_input => "datac")
-- pragma translate_on
PORT MAP (
	datac => vkey(1),
	datad => \Mux1~0_combout\,
	combout => \Mux1~1_combout\);

-- Location: LCCOMB_X37_Y14_N26
\digit[1]\ : cycloneiii_lcell_comb
-- Equation(s):
-- digit(1) = (GLOBAL(\Mux2~3clkctrl_outclk\) & ((\Mux1~1_combout\))) # (!GLOBAL(\Mux2~3clkctrl_outclk\) & (digit(1)))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "1111101000001010",
	sum_lutc_input => "datac")
-- pragma translate_on
PORT MAP (
	dataa => digit(1),
	datac => \Mux2~3clkctrl_outclk\,
	datad => \Mux1~1_combout\,
	combout => digit(1));

-- Location: LCCOMB_X37_Y14_N10
\Mux0~0\ : cycloneiii_lcell_comb
-- Equation(s):
-- \Mux0~0_combout\ = (vkey(0)) # (vkey(6) $ (vkey(4) $ (vkey(3))))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "1110101110111110",
	sum_lutc_input => "datac")
-- pragma translate_on
PORT MAP (
	dataa => vkey(0),
	datab => vkey(6),
	datac => vkey(4),
	datad => vkey(3),
	combout => \Mux0~0_combout\);

-- Location: LCCOMB_X37_Y14_N12
\Mux0~1\ : cycloneiii_lcell_comb
-- Equation(s):
-- \Mux0~1_combout\ = (vkey(2) & !\Mux0~0_combout\)

-- pragma translate_off
GENERIC MAP (
	lut_mask => "0000000011001100",
	sum_lutc_input => "datac")
-- pragma translate_on
PORT MAP (
	datab => vkey(2),
	datad => \Mux0~0_combout\,
	combout => \Mux0~1_combout\);

-- Location: LCCOMB_X37_Y14_N18
\digit[2]\ : cycloneiii_lcell_comb
-- Equation(s):
-- digit(2) = (GLOBAL(\Mux2~3clkctrl_outclk\) & ((\Mux0~1_combout\))) # (!GLOBAL(\Mux2~3clkctrl_outclk\) & (digit(2)))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "1110111001000100",
	sum_lutc_input => "datac")
-- pragma translate_on
PORT MAP (
	dataa => \Mux2~3clkctrl_outclk\,
	datab => digit(2),
	datad => \Mux0~1_combout\,
	combout => digit(2));

-- Location: LCCOMB_X29_Y25_N8
\Mux10~0\ : cycloneiii_lcell_comb
-- Equation(s):
-- \Mux10~0_combout\ = (!digit(3) & (!digit(1) & (digit(0) $ (digit(2)))))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "0000000100000100",
	sum_lutc_input => "datac")
-- pragma translate_on
PORT MAP (
	dataa => digit(3),
	datab => digit(0),
	datac => digit(1),
	datad => digit(2),
	combout => \Mux10~0_combout\);

-- Location: LCCOMB_X29_Y25_N22
\Mux9~0\ : cycloneiii_lcell_comb
-- Equation(s):
-- \Mux9~0_combout\ = (digit(2) & (digit(0) $ (digit(1))))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "0101101000000000",
	sum_lutc_input => "datac")
-- pragma translate_on
PORT MAP (
	dataa => digit(0),
	datac => digit(1),
	datad => digit(2),
	combout => \Mux9~0_combout\);

-- Location: LCCOMB_X29_Y25_N0
\Mux8~0\ : cycloneiii_lcell_comb
-- Equation(s):
-- \Mux8~0_combout\ = (!digit(0) & (digit(1) & !digit(2)))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "0000000001010000",
	sum_lutc_input => "datac")
-- pragma translate_on
PORT MAP (
	dataa => digit(0),
	datac => digit(1),
	datad => digit(2),
	combout => \Mux8~0_combout\);

-- Location: LCCOMB_X29_Y25_N10
\Mux7~0\ : cycloneiii_lcell_comb
-- Equation(s):
-- \Mux7~0_combout\ = (digit(0) & (digit(1) $ (!digit(2)))) # (!digit(0) & (!digit(1) & digit(2)))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "1100001100001100",
	sum_lutc_input => "datac")
-- pragma translate_on
PORT MAP (
	datab => digit(0),
	datac => digit(1),
	datad => digit(2),
	combout => \Mux7~0_combout\);

-- Location: LCCOMB_X29_Y25_N4
\Mux6~0\ : cycloneiii_lcell_comb
-- Equation(s):
-- \Mux6~0_combout\ = (digit(0)) # ((digit(2) & !digit(1)))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "1111111100001100",
	sum_lutc_input => "datac")
-- pragma translate_on
PORT MAP (
	datab => digit(2),
	datac => digit(1),
	datad => digit(0),
	combout => \Mux6~0_combout\);

-- Location: LCCOMB_X29_Y25_N2
\Mux5~0\ : cycloneiii_lcell_comb
-- Equation(s):
-- \Mux5~0_combout\ = (!digit(3) & (!digit(2) & ((digit(0)) # (digit(1)))))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "0000000001010100",
	sum_lutc_input => "datac")
-- pragma translate_on
PORT MAP (
	dataa => digit(3),
	datab => digit(0),
	datac => digit(1),
	datad => digit(2),
	combout => \Mux5~0_combout\);

-- Location: LCCOMB_X29_Y25_N12
\Mux4~0\ : cycloneiii_lcell_comb
-- Equation(s):
-- \Mux4~0_combout\ = (digit(3)) # ((digit(1) & ((!digit(2)) # (!digit(0)))) # (!digit(1) & ((digit(2)))))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "1011111111111010",
	sum_lutc_input => "datac")
-- pragma translate_on
PORT MAP (
	dataa => digit(3),
	datab => digit(0),
	datac => digit(1),
	datad => digit(2),
	combout => \Mux4~0_combout\);

ww_seg1(0) <= \seg1[0]~output_o\;

ww_seg1(1) <= \seg1[1]~output_o\;

ww_seg1(2) <= \seg1[2]~output_o\;

ww_seg1(3) <= \seg1[3]~output_o\;

ww_seg1(4) <= \seg1[4]~output_o\;

ww_seg1(5) <= \seg1[5]~output_o\;

ww_seg1(6) <= \seg1[6]~output_o\;

ww_seg1(7) <= \seg1[7]~output_o\;

ww_seg2(0) <= \seg2[0]~output_o\;

ww_seg2(1) <= \seg2[1]~output_o\;

ww_seg2(2) <= \seg2[2]~output_o\;

ww_seg2(3) <= \seg2[3]~output_o\;

ww_seg2(4) <= \seg2[4]~output_o\;

ww_seg2(5) <= \seg2[5]~output_o\;

ww_seg2(6) <= \seg2[6]~output_o\;

ww_seg2(7) <= \seg2[7]~output_o\;

ww_seg3(0) <= \seg3[0]~output_o\;

ww_seg3(1) <= \seg3[1]~output_o\;

ww_seg3(2) <= \seg3[2]~output_o\;

ww_seg3(3) <= \seg3[3]~output_o\;

ww_seg3(4) <= \seg3[4]~output_o\;

ww_seg3(5) <= \seg3[5]~output_o\;

ww_seg3(6) <= \seg3[6]~output_o\;

ww_seg3(7) <= \seg3[7]~output_o\;

ww_seg4(0) <= \seg4[0]~output_o\;

ww_seg4(1) <= \seg4[1]~output_o\;

ww_seg4(2) <= \seg4[2]~output_o\;

ww_seg4(3) <= \seg4[3]~output_o\;

ww_seg4(4) <= \seg4[4]~output_o\;

ww_seg4(5) <= \seg4[5]~output_o\;

ww_seg4(6) <= \seg4[6]~output_o\;

ww_seg4(7) <= \seg4[7]~output_o\;
END structure;


