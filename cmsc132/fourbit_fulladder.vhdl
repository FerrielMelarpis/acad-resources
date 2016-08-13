library IEEE; use IEEE.std_logic_1164.all;

entity fourbit_fa is 
	port ( A,B: in std_logic_vector(3 downto 0);
	clk: in std_logic;
	S: out std_logic_vector(3 downto 0); 
	Cout: out std_logic);
end entity;

architecture fourbit_fa_struct of fourbit_fa is
	
	signal wire0,wire1,wire2: std_logic_vector(1 downto 0);
	signal dff0 : std_logic_vector (1 downto 0);
	signal dff1 : std_logic_vector (3 downto 0);
	signal dff2 : std_logic_vector (4 downto 0);
	signal dff3 : std_logic_vector (6 downto 0);
	signal initial_cin :std_logic := '0';
	component fullAdd is
	    port(s, cout: out std_logic; a,b,cin:in std_logic);
	end component;
	
	component dff_moore is
	port (q : out std_logic; -- output 
		clk: in std_logic; -- clock signal
		d: in std_logic); -- input
	end component dff_moore;
begin 
	
	g0: component fullAdd port map (wire0(0),wire0(1),A(0),B(0),initial_cin); --first full adder
	g1: component dff_moore port map (dff0(0), clk, wire0(0)); --delay for S0
	g2: component dff_moore port map (dff0(1), clk, dff0(0)); --delay for S0
	g3: component dff_moore port map (S(0), clk, dff0(1)); --last delay for S0 output

	g4: component dff_moore port map (dff1(0), clk, A(1)); --A1 dff 
	g5: component dff_moore port map (dff1(1), clk, B(1)); --B1 dff
	g6: component dff_moore port map (dff1(2), clk, wire0(1)); --carry out dff

	g7: component fullAdd port map (wire1(0),wire1(1), dff1(0),dff1(1),dff1(2)); --second full adder

	g8: component dff_moore port map (dff1(3), clk, wire1(0)); --delay for S1
	g9: component dff_moore port map (S(1), clk, dff1(3)); -- last delay for S1 output

	g10: component dff_moore port map (dff2(0), clk, A(2)); --delay for A2
	g11: component dff_moore port map (dff2(1), clk, dff2(0)); --delay for A2

	g12: component dff_moore port map (dff2(2), clk, B(2)); --delay for B2
	g13: component dff_moore port map (dff2(3), clk, dff2(2)); --delay for B2

	g14: component dff_moore port map (dff2(4) , clk, wire1(1)); --delay for carry out of second full adder

	g15: component fullAdd port map (wire2(0), wire2(1), dff2(1), dff2(3), dff2(4)); --third full adder

	g16: component dff_moore port map (S(2), clk, wire2(0)); --delay for S2 output

	g17: component dff_moore port map (dff3(0), clk, A(3)); --delay for A3
	g18: component dff_moore port map (dff3(1), clk, dff3(0)); --delay for A3
	g19: component dff_moore port map (dff3(2), clk, dff3(1)); --delay for A3

	g20: component dff_moore port map (dff3(3), clk, B(3)); --delay for B3
	g21: component dff_moore port map (dff3(4), clk, dff3(3)); --delay for B3
	g22: component dff_moore port map (dff3(5), clk, dff3(4)); --delay for B3

	g23: component dff_moore port map (dff3(6), clk, wire2(1)); -- delay for carry out of third full adder

	g24: component fullAdd port map (S(3), Cout, dff3(2), dff3(5), dff3(6));

end fourbit_fa_struct;
