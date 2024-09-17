library IEEE;
use IEEE.std_logic_1164.all;
use IEEE.numeric_std.all;

entity Divisor_Reloj is
	port
	(
		i_CLK	:in std_logic;			-- Cristal de 50Mhz
		o_Q		:out std_logic 		-- Para visualizar la división del reloj
	);
end Divisor_Reloj;

architecture divisor of Divisor_Reloj is
	
	component Flipflop_D is
		port 
		(
			i_LD    : in std_logic;     		-- Señal de reloj
			i_D     : in std_logic;
			o_Q     : out std_logic
		);
	end component;	

	signal Q : std_logic_vector(9 downto 0);	-- Salidas a diferentes frecuencias

begin

	Div1: Flipflop_D port map(i_CLK, '1', Q(0));		
	Div2: Flipflop_D port map(Q(0), '1', Q(1));		
	Div3: Flipflop_D port map(Q(1), '1', Q(2));		
	Div4: Flipflop_D port map(Q(2), '1', Q(3));		
	Div5: Flipflop_D port map(Q(3), '1', Q(4));		
	Div6: Flipflop_D port map(Q(4), '1', Q(5));		
	Div7: Flipflop_D port map(Q(5), '1', Q(6));		
	Div8: Flipflop_D port map(Q(6), '1', Q(7));
	Div9: Flipflop_D port map(Q(7), '1', Q(8));

	o_Q <= Q(8);
end divisor;
