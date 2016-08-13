--Rahmat Peter Dabalos | Ferriel Lisandro B. Melarpis
--CMSC 132 T-2L
library IEEE; use IEEE.std_logic_1164.all;
-- adder entity
entity adder is
	port(a, b, cin: in std_logic; s, cout: out std_logic);
end entity adder;

architecture rtl of adder is 
begin
	s <= a xor b xor cin;
	cout <= (a and b) or (a and cin) or (b and cin);
end architecture rtl;

------------------------------------------------
library IEEE; use IEEE.std_logic_1164.all;
-- d-latch entity
entity d_latch is
	port (q : out std_logic; 		
		clk, input: in std_logic;); 
end entity d_latch;
-- architecture of d latch 
architecture behavior of d_latch is
begin
	process(clk) is
	begin 		
		if rising_edge(clk) then
			q <= input;
		end if;
	end process;
end behavior;

------------------------------------------------
library IEEE; use IEEE.std_logic_1164.all;
-- 4bit full adder entity
entity fa_4bit is 
	port (A, B : in std_logic_vector(3 downto 0);
	clk: in std_logic;
	S: out std_logic_vector(3 downto 0); 
	cout: out std_logic);
end entity;
-- 4bit full adder structure
architecture fa_4bit_struct of fa_4bit is 
	-- import adder entity
	component adder is
		port(a,b,cin: in std_logic;
		s, cout: out std_logic);
	end component adder;
	-- import d-latch entity
	component d_latch is
		port(q: out std_logic;
		clk, input: in std_logic);
	end component d_latch;

	signal conn0,conn1,conn2, dl0: std_logic_vector(1 downto 0);
	signal dl1 : std_logic_vector (3 downto 0);
	signal dl2 : std_logic_vector (4 downto 0);
	signal dl3 : std_logic_vector (6 downto 0);
	signal cin_init :std_logic := '0';
	
	begin

		g0: component adder port map (A(0), B(0), cin_init, conn0(0),conn0(1)); --first full adder
		g1: component d_latch port map (dl0(0), clk, conn0(0)); --delay for S0
		g2: component d_latch port map (dl0(1), clk, dl0(0)); --delay for S0
		g3: component d_latch port map (S(0), clk, dl0(1)); --last delay for S0 output

		g4: component d_latch port map (dl1(0), clk, A(1)); --A1 dl 
		g5: component d_latch port map (dl1(1), clk, B(1)); --B1 dl
		g6: component d_latch port map (dl1(2), clk, conn0(1)); --carry out dl

		g7: component adder port map (dl1(0), dl1(1), dl1(2), conn1(0), conn1(1)); --second full adder

		g8: component d_latch port map (dl1(3), clk, conn1(0)); --delay for S1
		g9: component d_latch port map (S(1), clk, dl1(3)); -- last delay for S1 output

		g10: component d_latch port map (dl2(0), clk, A(2)); --delay for A2
		g11: component d_latch port map (dl2(1), clk, dl2(0)); --delay for A2

		g12: component d_latch port map (dl2(2), clk, B(2)); --delay for B2
		g13: component d_latch port map (dl2(3), clk, dl2(2)); --delay for B2

		g14: component d_latch port map (dl2(4) , clk, conn1(1)); --delay for carry out of second full adder

		g15: component adder port map (dl2(1), dl2(3), dl2(4), conn2(0), conn2(1)); --third full adder

		g16: component d_latch port map (S(2), clk, conn2(0)); --delay for S2 output

		g17: component d_latch port map (dl3(0), clk, A(3)); --delay for A3
		g18: component d_latch port map (dl3(1), clk, dl3(0)); --delay for A3
		g19: component d_latch port map (dl3(2), clk, dl3(1)); --delay for A3

		g20: component d_latch port map (dl3(3), clk, B(3)); --delay for B3
		g21: component d_latch port map (dl3(4), clk, dl3(3)); --delay for B3
		g22: component d_latch port map (dl3(5), clk, dl3(4)); --delay for B3

		g23: component d_latch port map (dl3(6), clk, conn2(1)); -- delay for carry out of third full adder

		g24: component adder port map (dl3(2), dl3(5), dl3(6), S(3), cout);
	
end architecture fa_4bit_struct;