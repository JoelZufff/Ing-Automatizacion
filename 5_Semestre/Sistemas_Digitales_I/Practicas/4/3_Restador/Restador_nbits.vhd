library	IEEE;
use	IEEE.std_logic_1164.all;
use IEEE.numeric_std.all;

entity Restador_nbits is
	generic ( 
		n: integer := 2		-- Especificamos bits del sumador 
	);
	port 
	(
		-- Entrada y salida de bits
		A, B		: in std_logic_vector(n-1 downto 0);		-- Entradas de bits para operaciones
        neg_LED     : out std_logic;                            -- Booleano para saber si es negativo
		LEDS		: out std_logic_vector(n-1 downto 0);		-- Salida en binario

		-- Displays de 7 seg 
	    clock       : in    std_logic;
		display		: out 	std_logic_vector(7 downto 0);   	-- Salida para el display de 7 segmentos
		common 		: out 	std_logic_vector(3 downto 0)   		-- Salida para el display de 7 segmentos
	);
end Restador_nbits;	 

Architecture Restador_nbits of Restador_nbits is	 
	
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
	component Restador_1bit is
		port 
		(
			A 	: in std_logic;	
			B 	: in std_logic;	
			Ci 	: in std_logic;		-- Acarreo de entrada
			Co 	: out std_logic;  	-- Acarreo de salida
			S	: out std_logic	-- Resultado
		);
	end component;

	-- Señales para multiplexado de display
    signal count        : integer range 0 to 10000;
    signal comun_index  : integer range 0 to 4;
    
    -- Señales para sumador de n bits
	signal S	: std_logic_vector(n-1 downto 0);	    -- Salida de suma de n bits
	signal C	: std_logic;						    -- Acarreo de primer bit
    signal neg  : std_logic;                            -- Booleano para saber si es negativo
begin
	
	-- Generamos sumas completas de cada bit, y los ponemos en cascada con el acarreo de salida entrando al acarreo de entrada del sig

	Res0: Restador_1bit port map(A(0), B(0), '0', C, S(0));		-- Suma del bit 0
	Res1: Restador_1bit port map(A(1), B(1), C, neg, S(1));		-- Suma del bit 1
    
    neg_LED <= not neg;

    -- Reloj para delay de multiplexado
    delay_clock : process (clock)
    begin
        if rising_edge(clock) then
            if count < 10000 then
                count <= count + 1;
            else
                if comun_index < 2 then
                    comun_index <= comun_index + 1;
                else
                    comun_index <= 0;
                end if;
                count <= 0;
            end if;
        end if;
    end process;

    -- Impresion de display individual
    display_print : process (comun_index)
    begin	
        case comun_index is
            when 1 => 
                if neg = '1' then             -- Si es negativo imprimimos el signo
                    common <= "1101";
                    display <= "10111111";
                end if;
            when 2 => 
                common <= "1110";
                if neg = '1' then             -- Si es negativo aplicamos complemento a 2 al imprimir numero
	                display <=	numbers(to_integer(unsigned(not S) + 1));    
                    LEDS <= not std_logic_vector(unsigned(not S) + 1);
                else
                    display <=	numbers(to_integer(unsigned(S)));    
                    LEDS <= not S;
                end if;
            when others =>
                common <= "1111";
        end case;            
    end process;
	
end Restador_nbits;
