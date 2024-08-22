library IEEE;
use IEEE.std_logic_1164.all;

entity P3 is
   port 
	(
		buttons 		: in 	std_logic_vector(4 downto 0); 		-- Entrada de 5 bits para codificar la letra
		display 		: out 	std_logic_vector(7 downto 0);   	-- Salida para el display de 7 segmentos
		common 		: out 	std_logic_vector(3 downto 0)   	-- Salida para el display de 7 segmentos
	);
end P3;

architecture ABC of P3 is
begin
	common <= "1110";

	with buttons select
	display <=	"10001000" when "11111", -- A
				"10000011" when "11110", -- B
				"11000110" when "11101", -- C
				"10100001" when "11100", -- D
				"10000110" when "11011", -- E
				"10001110" when "11010", -- F
				"10000010" when "11001", -- G
				"10001001" when "11000", -- H
				"11001111" when "10111", -- I
				"11100001" when "10110", -- J
				"10000101" when "10101", -- K
				"11000111" when "10100", -- L 
				"10110000" when "10011", -- M 
				"11001000" when "10010", -- N
				"10101010" when "10001", -- Ñ
				"11000000" when "10000", -- O
				"10001100" when "01111", -- P 
				"10011000" when "01110", -- Q 
				"11001110" when "01101", -- R 
				"10010010" when "01100", -- S 
				"10000111" when "01011", -- T 
				"11000001" when "01010", -- U 
				"10000110" when "01001", -- W  
				"10100100" when "01000", -- Z
				"00000000" when others;
end ABC;