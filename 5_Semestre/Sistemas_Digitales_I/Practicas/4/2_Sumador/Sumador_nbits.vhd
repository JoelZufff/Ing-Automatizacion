library	IEEE;
use	IEEE.std_logic_1164.all;
use IEEE.numeric_std.all;

entity Sumador_nbits is
	generic ( 
		n: integer := 2		-- Especificamos bits del sumador 
	);
	port 
	(
		-- Entrada y salida de bits
		A, B		: in std_logic_vector(n-1 downto 0);		-- Entradas de bits para operaciones
		LEDS		: out std_logic_vector(n downto 0);		-- Salida

		-- Displays de 7 seg 
		display		: out 	std_logic_vector(7 downto 0);   	-- Salida para el display de 7 segmentos
		common 		: out 	std_logic_vector(3 downto 0)   		-- Salida para el display de 7 segmentos
	);
end Sumador_nbits;	 

Architecture Sumador_nbits of Sumador_nbits is	 
	
	-- Para impresion de numeros en display
	type num_array is array (0 to 9) of std_logic_vector(7 downto 0);
    constant numbers : num_array := 
    (
        "11000000",  -- 0
        "11111001",  -- 1
        "10100100",  -- 2
        "10110000",  -- 3
        "10011001",  -- 4
        "10010010",  -- 5
        "10000010",  -- 6
        "11111000",  -- 7
        "10000000",  -- 8
        "10011000"   -- 9
    );

	-- Componente con sumador de 1 bit completo
	component Sumador_1bit is
		port 
		(
			A 	: in std_logic;	
			B 	: in std_logic;	
			Ci 	: in std_logic;		-- Acarreo de entrada
			Co 	: out std_logic;  	-- Acarreo de salida
			S	: out std_logic	-- Resultado
		);
	end component;

	-- Señales para sumador de n bits
	signal S	: std_logic_vector(n downto 0);	-- Salida de suma de n bits
	signal C	: std_logic;						-- Acarreo de primer bit
begin
	
	-- Generamos sumas completas de cada bit, y los ponemos en cascada con el acarreo de salida entrando al acarreo de entrada del sig

	Sum0: Sumador_1bit port map(A(0), B(0), '0', C, S(0));		-- Suma del bit 0
	Sum1: Sumador_1bit port map(A(1), B(1), C, S(2), S(1));		-- Suma del bit 1

	common <= "1110";

	-- Impresion de resultado en display
	display <=	numbers(to_integer(unsigned(S)));
	
end Sumador_nbits;
