--Test Bench for Four-Bit Full Adder

library IEEE; use IEEE.std_logic_1164.all;
use IEEE.numeric_std.all;
use work.all;

entity adder_tb is

end;

architecture adder_tb of adder_tb is
	signal A, B, S: std_logic_vector (3 downto 0); -- 4bit vectors
	signal Cout: std_logic; -- carry out
	signal clk: std_logic := '0'; -- clock signal

	component fourbit_fa is 
		port ( A,B: in std_logic_vector(3 downto 0);
	       clk: in std_logic;
	       S: out std_logic_vector(3 downto 0); 
	       Cout: out std_logic);
	end component;

begin	
	uut: component fourbit_fa port map(A,B,clk,S,Cout);
	clock: clk <= not clk after 10 ns;
	process 
		variable error_count: integer:=0;
	begin
		
		A <= "0111"; -- 7
		B <= "0110"; -- 6

    assert(S = "1101") report "ADDER ERROR!" severity error; -- test for sum = 13
		if(S /="1101") then
			error_count := error_count +1;
		end if;
		
		report "Done with test. There were " & integer'image(error_count)&" errors.";
		wait;
	end process;
	
end architecture;
