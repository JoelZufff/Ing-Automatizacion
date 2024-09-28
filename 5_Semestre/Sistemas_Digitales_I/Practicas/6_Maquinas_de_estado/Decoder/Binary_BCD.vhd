library IEEE;
use IEEE.std_logic_1164.all;
use IEEE.numeric_std.all;

entity Binary_BCD is
    port 
    (
        CLK     : in std_logic;
        -- Displays de 7 seg 
		display		: out 	std_logic_vector(7 downto 0);   	-- Salida para el display de 7 segmentos
		common 		: out 	std_logic_vector(3 downto 0)   		-- Salida para el display de 7 segmentos
    );
end entity;

architecture bin_bcd of Binary_BCD is
    -- Variables y señales para multiplexado de display
    signal disp_clk             : std_logic;                       -- Señal del reloj para impresion de display
    signal disp_clk_count       : integer range 0 to (50000 * 2 - 1);    -- Contador para dividir el reloj cada 1 ms
	signal comun_index          : integer range 0 to 4;
    
    type int_array is array (0 to 3) of integer;
    signal numbers : int_array := (0, 0, 0, 0);
    
    type array_4_t is array (0 to 3) of std_logic_vector(3 downto 0); -- Tipo para manejar los comunes
    constant com_array : array_4_t := 
    (
       "1110",
       "1101",
       "1011",
       "0111"
    );

    type array_10_t is array (0 to 9) of std_logic_vector(7 downto 0); -- Tipo para los números de display de 7 segmentos
    constant num_array : array_10_t := 
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
    
     -- Componentes y señales para decoder de 8 bits
    signal bcd_clk              : std_logic;
    signal bcd_clk_count        : integer range 0 to (2000000 - 1);    -- Contador para dividir el reloj cada 1 ms
    
    signal suma         : std_logic_vector(9 downto 0) := "0000000000";     -- 2 BMS en 0
    signal suma_dec     : std_logic_vector(9 downto 0) := "0000000000";     -- Salida de decoder

begin

    -- Divisor de reloj
    divisor_frecuencia : process (CLK)
    begin
        if rising_edge(CLK) then
            -- Divisor de reloj para sumador
            if bcd_clk_count = (2000000 - 1) then -- Cada 250 millones de ciclos del reloj de 50 MHz = 5 segundos
                bcd_clk_count  <= 0;            -- Reiniciar el contador
                bcd_clk        <= not bcd_clk;  -- Cambia el estado del reloj dividido
            else
                bcd_clk_count <= bcd_clk_count + 1;
            end if;

            -- Divisor de reloj para multiplexado de display
            if disp_clk_count = (50000 * 2 - 1) then -- Cada 250 millones de ciclos del reloj de 50 MHz = 5 segundos
                disp_clk_count  <= 0;               -- Reiniciar el contador
                disp_clk        <= not disp_clk;    -- Cambia el estado del reloj dividido
            else
                disp_clk_count <= disp_clk_count + 1;
            end if;
        end if;
    end process;

    multiplexado : process (disp_clk)
    begin
        if rising_edge(disp_clk) then
            -- Seleccionamos display para impresion
            if comun_index < 3 then
                comun_index <= comun_index + 1;
            else
                comun_index <= 0;
            end if;

            -- Enviamos informacion a display seleccionado
            common  <= com_array(comun_index);
            display <= num_array(numbers(comun_index));
        end if;
    end process;

    Sumador : process (bcd_clk)
        variable aux1     : std_logic_vector(9 downto 0);
        variable BCD_aux  : std_logic_vector(3 downto 0);
        variable BCD_aux2 : std_logic_vector(3 downto 0);
    begin
        if rising_edge(bcd_clk) then
            -- Aumentamos sumador
            if unsigned(suma) + 1 > 255 then
                suma <= "0000000000";
            else
                suma <= std_logic_vector(unsigned(suma) + 1);
            end if;

            -- Utilizamos decodificador
            aux1 := suma;

            BCD_aux := aux1(8 downto 5);
            
            if (unsigned(BCD_aux) >= 5) then
                BCD_aux2 := std_logic_vector(unsigned(BCD_aux) + 3);
                aux1(8 downto 5) := BCD_aux2;
            end if;
            
            BCD_aux := aux1(7 downto 4);
            
            if (unsigned(BCD_aux) >= 5) then
                BCD_aux2 := std_logic_vector(unsigned(BCD_aux) + 3);
                aux1(7 downto 4) := BCD_aux2;
            end if;

            BCD_aux := aux1(6 downto 3);
            
            if (unsigned(BCD_aux) >= 5) then
                BCD_aux2 := std_logic_vector(unsigned(BCD_aux) + 3);
                aux1(6 downto 3) := BCD_aux2;
            end if;

            BCD_aux := aux1(9 downto 6);
            
            if (unsigned(BCD_aux) >= 5) then
                BCD_aux2 := std_logic_vector(unsigned(BCD_aux) + 3);
                aux1(9 downto 6) := BCD_aux2;
            end if;

            BCD_aux := aux1(5 downto 2);
            
            if (unsigned(BCD_aux) >= 5) then
                BCD_aux2 := std_logic_vector(unsigned(BCD_aux) + 3);
                aux1(5 downto 2) := BCD_aux2;
            end if;

            BCD_aux := aux1(8 downto 5);
            
            if (unsigned(BCD_aux) >= 5) then
                BCD_aux2 := std_logic_vector(unsigned(BCD_aux) + 3);
                aux1(8 downto 5) := BCD_aux2;
            end if;

            BCD_aux := aux1(4 downto 1);
            
            if (unsigned(BCD_aux) >= 5) then
                BCD_aux2 := std_logic_vector(unsigned(BCD_aux) + 3);
                aux1(4 downto 1) := BCD_aux2;
            end if;

            suma_dec <= aux1;
        end if;
    end process;

    numbers(0) <= to_integer(unsigned(suma_dec(3 downto 0)));
    numbers(1) <= to_integer(unsigned(suma_dec(7 downto 4)));
    numbers(2) <= to_integer(unsigned(suma_dec(9 downto 8)));
end bin_bcd;