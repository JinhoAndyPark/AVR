library ieee;

use ieee.std_logic_1164.all;
use ieee.std_logic_arith.all;
use ieee.std_logic_unsigned.all;



entity test is 

       port(

		 clk, set, reset : in std_logic;

		 seg1: out std_logic_vector(6 downto 0);
		 seg2: out std_logic_vector(6 downto 0)

		 );
		 end test;

architecture arc of test is 
signal count : integer range 0 to 49999999;
signal reg : std_logic_vector(3 downto 0);
begin

	process(set,reset,clk)
	begin
		if(set='0') THEN
			reg<="1111";
		elsif(reset='0') THEN
			reg<="0000";
		elsif rising_edge(clk)then
			if count = 49999999 then
				count <= 0;
				reg(3)<=reg(2);
				reg(2)<=reg(1);
				reg(1)<=reg(0);
				reg(0)<=not reg(3);
			else
				count <= count + 1;				
			end if;
		end if;
	end process;
	
	process(reg)
	begin
		case reg is
			when "0000" =>seg1 <="1000000";	--0
							  seg2 <="1000000";	--0
			when "0001" =>seg1 <="1111001";	--1
							  seg2 <="1000000";	--0
			when "0010" =>seg1 <="0100100";	--2
							  seg2 <="1000000";	--0
			when "0011" =>seg1 <="0110000";	--3
							  seg2 <="1000000";	--0
			when "0100" =>seg1 <="0011001";	--4
							  seg2 <="1000000";	--0
			when "0101" =>seg1 <="0010010";	--5
							  seg2 <="1000000";	--0
			when "0110" =>seg1 <="0000010";	--6
							  seg2 <="1000000";	--0
			when "0111" =>seg1 <="1011000";	--7
							  seg2 <="1000000";	--0
			when "1000" =>seg1 <="0000000";	--8
							  seg2 <="1000000";	--0
			when "1001" =>seg1 <="0011000";	--9
							  seg2 <="1000000";	--0
			when "1010" =>seg1 <="1000000";	--0
							  seg2 <="1111001";	--1
			when "1011" =>seg1 <="1111001";	--1
							  seg2 <="1111001";	--1
			when "1100" =>seg1 <="0100100";	--2
							  seg2 <="1111001";	--1
			when "1101" =>seg1 <="0110000";	--3
							  seg2 <="1111001";	--1
			when "1110" =>seg1 <="0011001";	--4
							  seg2 <="1111001";	--1
			when "1111" =>seg1 <="0010010";	--5
							  seg2 <="1111001";	--1
			when others => seg1 <="1000000";	--0
							   seg2 <="1000000";	--0
		end case;
	end process;

end arc;