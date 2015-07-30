library ieee;

use ieee.std_logic_1164.all;
use ieee.std_logic_arith.all;
use ieee.std_logic_unsigned.all;



entity test is 
	port(
		
		clk	: in std_logic;
		key	: in std_logic;
		reset	: in std_logic;
		--reg	: inout std_logic_vector(7 downto 0);
		
		seg1: out std_logic_vector(7 downto 0);
		seg2: out std_logic_vector(7 downto 0);
		seg3: out std_logic_vector(7 downto 0);
		seg4: out std_logic_vector(7 downto 0)
	);
	end test;

architecture arc of test is 
shared variable count: integer range 0 to 10;
signal reg	 : std_logic_vector(7 downto 0);
signal vkey	 : std_logic_vector(7 downto 0);
signal digit : integer range 0 to 9;
signal Enter : std_logic;
signal digit1 : integer range 0 to 9;
signal digit2 : integer range 0 to 9;
signal digit3 : integer range 0 to 9;
signal digit4 : integer range 0 to 9;
signal ndigit : integer range 1 to 4;

begin
	process(clk)
	begin
	if reset='0' then
		reg <= "00000000";
		count := 0;
	else
		if(falling_edge(clk)) then
			if count=0 and key='0' then	count := count +1;	--start bit
			elsif count =1 then reg(7)<=key; count :=count+1;
			elsif count =2 then reg(6)<=key; count :=count+1;
			elsif count =3 then reg(5)<=key; count :=count+1;
			elsif count =4 then reg(4)<=key; count :=count+1;
			elsif count =5 then reg(3)<=key; count :=count+1;
			elsif count =6 then reg(2)<=key; count :=count+1;
			elsif count =7 then reg(1)<=key; count :=count+1;
			elsif count =8 then reg(0)<=key; count :=count+1;
			elsif count =9 then vkey<=reg;	count :=count+1;	--err
			elsif count <=10 then count :=0;	--stop
			end if;
		end if;
	end if;
	
	case vkey is
			when "10100010" =>digit<=0;	--0
			when "01101000" =>digit<=1;	--1
			when "01111000" =>digit<=2;	--2
			when "01100100" =>digit<=3;	--3
			when "10100100" =>digit<=4;	--4	
			when "01110100" =>digit<=5;	--5
			when "01101100" =>digit<=6;	--6			
			when "10111100" =>digit<=7;	--7			
			when "01111100" =>digit<=8;	--8			
			when "01100010" =>digit<=9;	--9
			when "01011010" =>Enter<='1';
			when others =>digit1<=NULL;	--non
	end case;
		
	digit1<=digit;
		
	end process;
	
	process(digit)
	begin
		case digit1 is
			when 0 =>seg1 <="11000000";		--0
			when 1 =>seg1 <="11111001";		--1
			when 2 =>seg1 <="10100100";		--2
			when 3 =>seg1 <="10110000";		--3
			when 4 =>seg1 <="10011001";		--4
			when 5 =>seg1 <="10010010";		--5
			when 6 =>seg1 <="10000010";		--6
			when 7 =>seg1 <="11011000";		--7
			when 8 =>seg1 <="10000000";		--8
			when 9 =>seg1 <="10011000";		--9
			when others => seg1 <="11111111";	--non
		end case;
			
		case digit2 is
			when 0 =>seg2 <="11000000";		--0
			when 1 =>seg2 <="11111001";		--1
			when 2 =>seg2 <="10100100";		--2
			when 3 =>seg2 <="10110000";		--3
			when 4 =>seg2 <="10011001";		--4
			when 5 =>seg2 <="10010010";		--5
			when 6 =>seg2 <="10000010";		--6
			when 7 =>seg2 <="11011000";		--7
			when 8 =>seg2 <="10000000";		--8
			when 9 =>seg2 <="10011000";		--9
			when others => seg2 <="11111111";	--non
		end case;
			
		case digit3 is
			when 0 =>seg3 <="11000000";		--0
			when 1 =>seg3 <="11111001";		--1
			when 2 =>seg3 <="10100100";		--2
			when 3 =>seg3 <="10110000";		--3
			when 4 =>seg3 <="10011001";		--4
			when 5 =>seg3 <="10010010";		--5
			when 6 =>seg3 <="10000010";		--6
			when 7 =>seg3 <="11011000";		--7
			when 8 =>seg3 <="10000000";		--8
			when 9 =>seg3 <="10011000";		--9
			when others => seg3 <="11111111";	--0
		end case;
			
		case digit4 is
			when 0 =>seg4 <="11000000";		--0	
			when 1 =>seg4 <="11111001";		--1
			when 2 =>seg4 <="10100100";		--2
			when 3 =>seg4 <="10110000";		--3
			when 4 =>seg4 <="10011001";		--4
			when 5 =>seg4 <="10010010";		--5
			when 6 =>seg4 <="10000010";		--6
			when 7 =>seg4 <="11011000";		--7
			when 8 =>seg4 <="10000000";		--8
			when 9 =>seg4 <="10011000";		--9
			when others => seg4 <="11111111";	--0
		end case;
	end process;
end arc;