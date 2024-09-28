library IEEE;
use IEEE.std_logic_1164.all;

entity Codificador_BCD is
port(
	B : in std_logic_vector(3 downto 0);
	C : out std_logic_vector(3 downto 0)
	);
end Codificador_BCD;	   

architecture Codificador of Codificador_BCD is
begin
	C <= "0000" when (B = "0000") else
	"0001" when (B = "0001") else
	"0010" when (B = "0010") else
	"0011" when (B = "0011") else
	"0100" when (B = "0100") else
	"1000" when (B = "0101") else
	"1001" when (B = "0110") else
	"1010" when (B = "0111") else
	"1011" when (B = "1000") else
"1100" when (B = "1001") else "1111";
end Codificador;