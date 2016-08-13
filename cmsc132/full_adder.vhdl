library IEEE; use IEEE.std_logic_1164.all;
-- xor2 gate
entity xor2 is
    port(o0:out std_logic; i0,i1:in std_logic);
end entity xor2;

architecture xor2 of xor2 is begin
    o0 <= i0 xor i1;
end architecture xor2;


library IEEE; use IEEE.std_logic_1164.all;
-- or2 gate
entity or2 is
    port (o0:out std_logic; i0,i1: in std_logic);
end entity or2;

architecture or2 of or2 is begin
    o0 <= i0 or i1;
end architecture or2;


library IEEE; use IEEE.std_logic_1164.all;
-- and2 gate
entity and2 is 
    port (o0:out std_logic; i0,i1: in std_logic);
end entity and2;

architecture and2 of and2 is begin
    o0 <= i0 and i1;
end architecture and2;


library IEEE; use IEEE.std_logic_1164.all;
entity fullAdd is
    port(s, cout: out std_logic; a,b,cin:in std_logic);
end entity;

architecture full_add_struct of fullAdd is
    signal d,e,f : std_logic;

component xor2 is
    port(o0: out std_logic; i0,i1:in std_logic);
end component xor2;

component or2 is
    port(o0: out std_logic; i0,i1:in std_logic);
end component or2;

component and2
    port(o0: out std_logic; i0,i1:in std_logic);
end component and2;

begin
    g0: component xor2 port map (d,a,b);
    g1: component xor2 port map (s,d,cin);
    g2: component and2 port map (e,d,cin);
    g3: component and2 port map (f,a,b);
    g4: component or2 port map (cout,e,f);
end architecture full_add_struct;
    

