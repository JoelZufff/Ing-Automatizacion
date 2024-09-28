library IEEE;
use IEEE.std_logic_1164.all;  

entity Bin_BCD_4b is
port(
	B : in std_logic_vector(3 downto 0);
	D : out std_logic;
	U : out std_logic_vector(3 downto 0)
);
end Bin_BCD_4b;	

architecture Convertidor of Bin_BCD_4b is
	component Codificador_BCD is
	port(
		B : in std_logic_vector(3 downto 0);
		C : out std_logic_vector(3 downto 0)
	);
	end component;	
	
	signal S1, S2 : std_logic_vector(3 downto 0);	
	
	begin
		S1 <= '0' & B(3 downto 1);
		U <= S2(2 downto 0) & B(0);
		D <= S2(3);
		Modulo: Codificador_BCD port map (S1,S2);
end Convertidor;