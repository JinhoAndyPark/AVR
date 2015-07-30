library ieee;

use ieee.std_logic_1164.all;
use ieee.std_logic_arith.all;
use ieee.std_logic_unsigned.all;

entity Timer is 
	port(
		 clk : in std_logic;
		 mSELECT : in std_logic;
		 mENTER	  : in std_logic;
		 UPDOWN	  : in std_logic;
		 sVALUE 	  : in std_logic;
		 DIS24	  : in std_logic;
		 ALRAM	  : in std_logic;
		 STMODE 	  : in std_logic;
		 STSTART   : in std_logic;
		 LAPTIME1  : in std_logic;
		 LAPTIME2  : in std_logic;
		 LAPTIME3  : in std_logic;
		 seg1: out std_logic_vector(6 downto 0);
		 seg2: out std_logic_vector(6 downto 0);
		 seg3: out std_logic_vector(6 downto 0);
		 seg4: out std_logic_vector(6 downto 0)
		 );
end Timer;

architecture arc of Timer is
-----------------------------------------------
--CLOCK SIGNAL---------------------------------
signal cnt 	: integer range 0 to 499999 :=0;
signal ms	: integer range 0 to 99 :=0;
signal sec	: integer range 0 to 59 :=0;
signal min	: integer range 0 to 59 :=0;
signal hor	: integer range 0 to 23 :=0;
signal day	: integer range 1 to 31 :=21;
signal mon	: integer range 1 to 12 :=11;
signal year	: integer range 0 to 3000 :=0;

signal mday : integer range 1 to 31 :=1;

--signal dis24 : std_logic;

signal setms  : integer range 0 to 99 :=0;
signal setsec : integer range 0 to 59 :=0;
signal setmin : integer range 0 to 59 :=0;
signal sethor : integer range 0 to 23 :=0;
signal setday : integer range 1 to 31 :=1;
signal setmon : integer range 1 to 12 :=1;
signal setyear: integer	range 0 to 3000 :=0;

signal nms	: integer range 0 to 99 :=0;
signal nsec	: integer range 0 to 59 :=0;
signal nmin	: integer range 0 to 59 :=0;
signal nhor	: integer range 0 to 23 :=0;
signal nday	: integer range 1 to 31 :=1;
signal nmon	: integer range 1 to 12 :=1;
signal nyear	: integer range 0 to 3000 :=0;

signal setflag : std_logic :='0';

signal digit  : integer range 0 to 1 :=0;

--ALRAM SIGNAL---------------------------------
signal almin	:integer range 0 to 59;
signal alhor	:integer range 0 to 23;

signal alflag	:integer range 0 to 2;

--STOP SIGNAL----------------------------------
signal stms		:integer range 0 to 99;
signal stsec	:integer range 0 to 59;
signal stmin	:integer range 0 to 59;
signal sthor	:integer range 0 to 23;

signal lapms1,lapsec1,lapmin1,laphor1	:integer range 0 to 99;
signal lapms2,lapsec2,lapmin2,laphor2	:integer range 0 to 99;
signal lapms3,lapsec3,lapmin3,laphor3	:integer range 0 to 99;

signal stflag	:integer range 0 to 1;
signal lapcnt	:integer range 0 to 2 :=0;

--DISPLAY--------------------------------------
signal ms1,ms2,sec1,sec2,min1,min2,hor1,hor2 : integer range 0 to 9;
signal day1,day2,mon1,mon2,year1,year2,year3,year4 : integer range 0 to 9;
signal almin1,almin2,alhor1,alhor2 : integer range 0 to 9;
signal stms1,stms2,stsec1,stsec2,stmin1,stmin2,sthor1,sthor2 : integer range 0 to 9;
signal lapms11,lapms12,lapsec11,lapsec12,lapmin11,lapmin12,laphor11,laphor12 : integer range 0 to 9;
signal lapms21,lapms22,lapsec21,lapsec22,lapmin21,lapmin22,laphor21,laphor22 : integer range 0 to 9;
signal lapms31,lapms32,lapsec31,lapsec32,lapmin31,lapmin32,laphor31,laphor32 : integer range 0 to 9;
signal nFND1,nFND2,nFND3,nFND4 : integer range 0 to 10;

signal nMODE		: integer range 0 to 4 :=0;
signal rst			: std_logic :='0';
signal upflag,dwflag : integer range 0 to 99;
-----------------------------------------------
begin
	process(clk,mENTER)
	begin		
		if mon=1 then mday<=31;
		elsif mon=3 then mday<=31;
		elsif mon=4 then mday<=30;
		elsif mon=5 then mday<=31;
		elsif mon=6 then mday<=30;
		elsif mon=7 then mday<=31;
		elsif mon=8 then mday<=31;
		elsif mon=9 then mday<=30;
		elsif mon=10 then mday<=31;
		elsif mon=11 then mday<=30;
		elsif mon=12 then mday<=31;
		elsif mon=2 then
			if (year mod 4) = 0 then
				if (year mod 100) = 0 then
					if (year mod 400) = 0 then
						mday <= 29;
					else
						mday <= 28;
					end if;
				else
					mday <= 29;
				end if;
			else
				mday <= 28;
			end if;
		end if;
		
		if rising_edge(clk) then
			if rst = '0' then
				ms <= 0;
				sec <= 0;
				min <= 0;
				hor <= 0;
				day <= 1;
				mon <= 1;
				year <= 2012;
				rst <= '1';
			end if;
			if cnt = 499999 then
				cnt <= 0;
				ms <= ms + 1;
				if STSTART = '1' then
					stms <= stms + 1;
					if stms = 99 then
						stms <= 0;
						stsec <= stsec + 1;
						if stsec = 59 then
							stsec <= 0;
							stmin <= stmin + 1;
							if stmin = 59 then
								stmin <= 0;
								sthor <= sthor + 1;
								if sthor = 23 then
								sthor <= 0;
								end if;
							end if;
						end if;
					end if;
				end if;
				if ms = 99 then
					ms <= 0;
					sec <= sec + 1;
					if sec = 59 then
						sec <= 0;
						min <= min + 1;
						if min = 59 then
							min <= 0;
							hor <= hor + 1;
							if hor = 23 then
								hor <= 0;
								day <= day + 1;
								if day = mday then
									day <= 1;
									mon <= mon + 1;
									if mon = 12 then
										mon <= 1;
										year <= year + 1;
									end if;
								end if;
							end if;
						end if;
					end if;
				end if;
			else
				cnt <= cnt + 1;
			end if;
		end if;
				
		if setflag = '1' then
			setflag <= '0';
			ms <= setms;
			sec <= setsec;
			min <= setmin;
			hor <= sethor;
			day <= setday;
			mon <= setmon;
			year <= setyear;
		end if;
		
		if rising_edge(mENTER) then
			if (sVALUE='1') and (STMODE='0') then
				digit <= digit + 1;
				if digit = 1 then
					digit <= 0;
				end if;
			elsif (STMODE='1') and (STSTART='0') then
				stflag <= 1;
			elsif (STMODE='1') and (STSTART='1') then
				lapcnt <= lapcnt + 1;
			
				if lapcnt = 2 then
					lapms3 <= stms;
					lapsec3 <= stsec;
					lapmin3 <= stmin;
					laphor3 <= sthor;
					lapcnt <= 0;
					
				elsif lapcnt = 0 then
					lapms1 <= stms;
					lapsec1 <= stsec;
					lapmin1 <= stmin;
					laphor1 <= sthor;
						
				elsif lapcnt = 1 then
					lapms2 <= stms;
					lapsec2 <= stsec;
					lapmin2 <= stmin;
					laphor2 <= sthor;
				end if;
			end if;
		end if;
		
		if stflag = 1 then	--reset
			stms <= 0;
			stsec <= 0;
			stmin <= 0;
			sthor <= 0;
			stflag <= 0;
		end if;

		if sVALUE = '1' then
			setflag <= '1';
		end if;
	end process;
	
	process(mSELECT,ms)
	begin
	if rising_edge(mSELECT) then
		if sVALUE = '0' then
			if UPDOWN = '0' then
				if nMODE = 4 then
					nMODE <= 0;
				else
					nMODE <= nMODE + 1;
				end if;
			else
				if nMODE = 0 then
					nMODE <= 4;
				else
					nMODE <= nMODE - 1;
				end if;
			end if;
		else
			if nMODE = 0 then
				if digit = 0 then
					if UPDOWN = '0' then 
						setmin <= setmin + 1;
						if setmin = 59 then
							setmin <= 0;
						end if;
					else
						setmin <= setmin - 1;
						if setmin = 0 then
							setmin <= 59;
						end if;
					end if;
				else
					if UPDOWN = '0' then
						sethor <= sethor + 1;
						if sethor = 23 then
							sethor <= 0;
						end if;
					else
						sethor <= sethor - 1;
						if sethor = 0 then
							sethor <= 23;
						end if;
					end if;
				end if;
			elsif nMODE = 1 then
				if digit = 0 then
					if UPDOWN = '0' then
						setms <= setms + 1;
						if setms = 99 then
							setms <= 0;
						end if;
					else
						setms <= setms - 1;
						if setms = 0 then
							setms <= 99;
						end if;
					end if;
				else
					if UPDOWN = '0' then
						setsec <= setsec + 1;
						if setsec = 59 then
							setsec <= 0;
						end if;
					else
						setsec <= setsec - 1;
						if setsec = 0 then
							setsec <= 59;
						end if;
					end if;
				end if;
			elsif nMODE = 2 then
				if digit = 0 then
					if UPDOWN = '0' then
						setday <= setday + 1;
						if setday = mday then
							setday <= 1;
						end if;
					else
						setday <= setday - 1;
						if setday = 1 then
							setday <= mday;
						end if;
					end if;
				else
					if UPDOWN = '0' then
						setmon <= setmon + 1;
						if setmon = 12 then
							setmon <= 1;
						end if;
					else
						setmon <= setmon - 1;
						if setmon = 1 then
							setmon <= 12;
						end if;
					end if;
				end if;
				
			elsif nMODE = 3 then
				if UPDOWN = '0' then
					setyear <= setyear + 1;
				else
					setyear <= setyear - 1;
				end if;
				
			elsif nMODE = 4 then
				if digit = 0 then
					if UPDOWN = '0' then
						alhor <= alhor + 1;
						if alhor = 23 then
							alhor <= 0;
						end if;
					else
						alhor <= alhor - 1;
						if alhor = 0 then
							alhor <= 23;
						end if;
					end if;
				else
					if UPDOWN = '0' then
						almin <= almin + 1;
						if almin = 59 then
							almin <= 0;
						end if;
					else
						almin <= almin - 1;
						if almin = 0 then
							almin <= 59;
						end if;
					end if;
				end if;
			end if;
		end if;

	end if;
	
	if sVALUE = '0' then
		setmin <= min;
		sethor <= hor;
		setms <= ms;
		setsec <= sec;
		setday <= day;
		setmon <= mon;
		setyear <= year;
	end if;
	end process;

	process(ms,nMODE)		--display 
	begin
		if (nMODE=0) and (STMODE='0') then			--mode clock(hour:min)
			if sVALUE = '1' then
				nmin <= setmin;
				nhor <= sethor;
			else
				nmin <= min;
				nhor <= hor;
			end if;
			
			if ALRAM = '1' then
				if (nmin = almin) and (nhor = alhor) then
					if ms<50 then
						alflag <= alflag + 1;
						nFND1 <= 10;
						nFND2 <= 10;
						nFND3 <= 10;
						nFND4 <= 10;
					else
						min1 <= nmin mod 10;
						min2 <= nmin / 10;
						hor1 <= nhor mod 10;
						hor2 <= nhor / 10;

						nFND1 <= min1;
						nFND2 <= min2;
						nFND3 <= hor1;
						nFND4 <= hor2;
					end if;
				else
					min1 <= nmin mod 10;
					min2 <= nmin / 10;
					hor1 <= nhor mod 10;
					hor2 <= nhor / 10;

					nFND1 <= min1;
					nFND2 <= min2;
					nFND3 <= hor1;
					nFND4 <= hor2;
				end if;
			else
				if DIS24 = '1' then
					min1 <= nmin mod 10;
					min2 <= nmin / 10;
					hor1 <= (nhor mod 12) mod 10;
					hor2 <= (nhor mod 12) / 10;
					
					nFND1 <= min1;
					nFND2 <= min2;
					nFND3 <= hor1;
					nFND4 <= hor2;
				else
					min1 <= nmin mod 10;
					min2 <= nmin / 10;
					hor1 <= nhor mod 10;
					hor2 <= nhor / 10;

					nFND1 <= min1;
					nFND2 <= min2;
					nFND3 <= hor1;
					nFND4 <= hor2;
				end if;
			end if;
			
		elsif (nMODE=1) and (STMODE='0') then		--mode clock(sec:ms)
			if sVALUE = '1' then
				nms <= setms;
				nsec <= setsec;
			else
				nms <= ms;
				nsec <= sec;
			end if;
			ms1 <= nms mod 10;
			ms2 <= nms / 10;
			sec1 <= nsec mod 10;
			sec2 <= nsec / 10;
			
			nFND1 <= ms1;
			nFND2 <= ms2;
			nFND3 <= sec1;
			nFND4 <= sec2;
			
		elsif (nMODE=2) and (STMODE='0') then		--mode cal(mon:day)
			if sVALUE = '1' then
				nday <= setday;
				nmon <= setmon;
			else
				nday <= day;
				nmon <= mon;
			end if;
			day1 <= nday mod 10;
			day2 <= nday / 10;
			mon1 <= nmon mod 10;
			mon2 <= nmon / 10;
			
			nFND1 <= day1;
			nFND2 <= day2;
			nFND3 <= mon1;
			nFND4 <= mon2;
		elsif (nMODE=3) and (STMODE='0') then		--mode cal(year)
			if sVALUE = '1' then
				nyear <= setyear;
			else
				nyear <= year;
			end if;
			year4 <= nyear / 1000;
			year3 <= (nyear mod 1000) /100 ;
			year2 <= ((nyear mod 1000) mod 100) / 10;
			year1 <= (((nyear mod 1000) mod 100) mod 10);
			
			nFND1 <= year1;
			nFND2 <= year2;
			nFND3 <= year3;
			nFND4 <= year4;
			
		elsif (nMODE=4) and (STMODE='0') then 	--mode alram
			almin1 <= almin mod 10;
			almin2 <= almin / 10;
			alhor1 <= alhor mod 10;
			alhor2 <= alhor / 10;
			
			nFND1 <= almin1;
			nFND2 <= almin2;
			nFND3 <= alhor1;
			nFND4 <= alhor2;
			
		elsif (nMODE mod 2=0) and (STMODE='1') then		--mode stop
			if LAPTIME1='1' then		--laptime1
				lapms11 <= lapms1 mod 10;
				lapms12 <= lapms1 / 10;
				lapsec11 <= lapsec1 mod 10;
				lapsec12 <= lapsec1 / 10;
				nFND1 <= lapms11;
				nFND2 <= lapms12;
				nFND3 <= lapsec11;
				nFND4 <= lapsec12;
				
			elsif LAPTIME2='1' then		--laptime1
				lapms21 <= lapms2 mod 10;
				lapms22 <= lapms2 / 10;
				lapsec21 <= lapsec2 mod 10;
				lapsec22 <= lapsec2 / 10;
				nFND1 <= lapms21;
				nFND2 <= lapms22;
				nFND3 <= lapsec21;
				nFND4 <= lapsec22;
				
			elsif LAPTIME3='1' then		--laptime3
				lapms31 <= lapms3 mod 10;
				lapms32 <= lapms3 / 10;
				lapsec31 <= lapsec3 mod 10;
				lapsec32 <= lapsec3 / 10;
				nFND1 <= lapms31;
				nFND2 <= lapms32;
				nFND3 <= lapsec31;
				nFND4 <= lapsec32;	
			
			else
				stms1 <= stms mod 10;
				stms2 <= stms / 10;
				stsec1 <= stsec mod 10;
				stsec2 <= stsec / 10;
				nFND1 <= stms1;
				nFND2 <= stms2;
				nFND3 <= stsec1;
				nFND4 <= stsec2;
			end if;
			
		elsif (nMODE mod 2=1) and (STMODE='1') then		--mode stop
			if LAPTIME1='1' then		--laptime1
				lapmin11 <= lapmin1 mod 10;
				lapmin12 <= lapmin1 / 10;
				laphor11 <= laphor1 mod 10;
				laphor12 <= laphor1 / 10;
				nFND1 <= lapmin11;
				nFND2 <= lapmin12;
				nFND3 <= laphor11;
				nFND4 <= laphor12;
				
			elsif LAPTIME2='1' then		--laptime2
				lapmin21 <= lapmin2 mod 10;
				lapmin22 <= lapmin2 / 10;
				laphor21 <= laphor2 mod 10;
				laphor22 <= laphor2 / 10;
				nFND1 <= lapmin21;
				nFND2 <= lapmin22;
				nFND3 <= laphor21;
				nFND4 <= laphor22;
				
			elsif LAPTIME3='1' then		--laptime3
				lapmin31 <= lapmin3 mod 10;
				lapmin32 <= lapmin3 / 10;
				laphor31 <= laphor3 mod 10;
				laphor32 <= laphor3 / 10;
				nFND1 <= lapmin31;
				nFND2 <= lapmin32;
				nFND3 <= laphor31;
				nFND4 <= laphor32;
			
			else
				stmin1 <= stmin mod 10;
				stmin2 <= stmin / 10;
				sthor1 <= sthor mod 10;
				sthor2 <= sthor / 10;
				nFND1 <= stmin1;
				nFND2 <= stmin2;
				nFND3 <= sthor1;
				nFND4 <= sthor2;
			end if;
			
		end if;
		
		case nFND1 is
			when 0 =>seg1 <="1000000";		--0
			when 1 =>seg1 <="1111001";		--1
			when 2 =>seg1 <="0100100";		--2
			when 3 =>seg1 <="0110000";		--3
			when 4 =>seg1 <="0011001";		--4
			when 5 =>seg1 <="0010010";		--5
			when 6 =>seg1 <="0000010";		--6
			when 7 =>seg1 <="1011000";		--7
			when 8 =>seg1 <="0000000";		--8
			when 9 =>seg1 <="0011000";		--9
			when 10 =>seg1 <="1111111";	--non
			when others => seg1 <="1000000";	--0
		end case;
			
		case nFND2 is
			when 0 =>seg2 <="1000000";		--0
			when 1 =>seg2 <="1111001";		--1
			when 2 =>seg2 <="0100100";		--2
			when 3 =>seg2 <="0110000";		--3
			when 4 =>seg2 <="0011001";		--4
			when 5 =>seg2 <="0010010";		--5
			when 6 =>seg2 <="0000010";		--6
			when 7 =>seg2 <="1011000";		--7
			when 8 =>seg2 <="0000000";		--8
			when 9 =>seg2 <="0011000";		--9
			when 10 =>seg2 <="1111111";	--non
			when others => seg2 <="1000000";	--0
		end case;
			
		case nFND3 is
			when 0 =>seg3 <="1000000";		--0
			when 1 =>seg3 <="1111001";		--1
			when 2 =>seg3 <="0100100";		--2
			when 3 =>seg3 <="0110000";		--3
			when 4 =>seg3 <="0011001";		--4
			when 5 =>seg3 <="0010010";		--5
			when 6 =>seg3 <="0000010";		--6
			when 7 =>seg3 <="1011000";		--7
			when 8 =>seg3 <="0000000";		--8
			when 9 =>seg3 <="0011000";		--9
			when 10 =>seg3 <="1111111";	--non
			when others => seg3 <="1000000";	--0
		end case;
			
		case nFND4 is
			when 0 =>seg4 <="1000000";		--0	
			when 1 =>seg4 <="1111001";		--1
			when 2 =>seg4 <="0100100";		--2
			when 3 =>seg4 <="0110000";		--3
			when 4 =>seg4 <="0011001";		--4
			when 5 =>seg4 <="0010010";		--5
			when 6 =>seg4 <="0000010";		--6
			when 7 =>seg4 <="1011000";		--7
			when 8 =>seg4 <="0000000";		--8
			when 9 =>seg4 <="0011000";		--9
			when 10 =>seg4 <="1111111";	--non
			when others => seg4 <="1000000";	--0
		end case;
	end process;
end arc;
