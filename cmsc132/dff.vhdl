--Rahmat Peter Dabalos | Ferriel Lisandro B. Melarpis
--CMSC 132 T-2L
library IEEE; use IEEE.std_logic_1164.all;
entity d_latch is
	port (q : out std_logic; 		
		clk: in std_logic; 
		d: in std_logic); 
end entity d_latch;
-- architecture of d latch 
architecture behavior of d_latch is
begin
	process(clk) is
	begin 		
		if rising_edge(clk) then
			q <= d;
		end if;
	end process;
end behavior;
