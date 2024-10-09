-- La maquina de estado estara compuesta por: 
    -- 11 estados: 10 estados para el envio de los 10 bits (1 bit de start, 8 bits de datos, 1 bit de paridad), y 1 estado de inactividad perpetuo.
    -- 2 entradas: Char_select -> Botones de seleccion de caracter de envio, ST -> Bit de inicio de transmision
    -- 2 salidas: EOT -> End of transmition y M -> Bit de envio

-- La señal de reloj del cambio de estado, representaran los baudios de transmision, y la sacaremos de una division de reloj del cristal interno.
------------------------------------------------------------------------------
library IEEE;
use IEEE.std_logic_1164.all;
use IEEE.numeric_std.all;

entity UART_TX is
	port
	(
		i_FPGA_clk      : in STD_LOGIC;
        
        -- Señales I/O de maquina de estado de comunicacion serial
        i_char_select   : in STD_LOGIC_VECTOR(2 downto 0);
        i_ST            : in STD_LOGIC;
        
        o_EOT           : out STD_LOGIC;
        o_M             : out STD_LOGIC
	); 
end UART_TX;
------------------------------------------------------------------------------
architecture Transmition of UART_TX is 

    -- Señales para transicion de estados
    type Estados is (S0, S1, S2, S3, S4, S5, S6, S7, S8, S9, S10, IDLE);
    signal act_state, next_state: Estados := IDLE; -- Ponemos en estado inicial la maquina

    -- Señal para division de reloj
    signal count: integer range 0 to (2500000 * 2 - 1);

    -- 7 palabras a enviar
    type array_7_t is array (0 to 6) of std_logic_vector(7 downto 0); -- Tipo para los números de display de 7 segmentos
    constant num_array : array_7_t := 
    (
        "01000001",  -- A
        "01001011",  -- K
        "01010010",  -- R
        "01001001",  -- I
        "01001010",  -- J
        "01101101",  -- m
        "01101111"   -- o
    );
    
begin
------------------------------------------------------------------------------
            -- DIVISION DE RELOJ PARA BAUDIOS DE TRANSMISION --
------------------------------------------------------------------------------
    process (i_FPGA_clk)
    begin
        if rising_edge(i_FPGA_clk) then
            if count = (2500000 * 2 - 1) then   -- 9600 Baudios
                act_state <= next_state;    -- Cambio de estado
                count <= 0;
            else
                count <= count + 1;
            end if;
        end if;
    end process;

------------------------------------------------------------------------------
                        -- TRANSMISION DE DATOS --
------------------------------------------------------------------------------ 
    process (act_state)
    begin
        case act_state  is
            when IDLE =>
                -- Enviamos señales de salida de estado actual

                -- Actualizamos estado futuro en funcion de las entradas
                if(i_ST = '1') then     -- Detectamos boton de inicio de transmision
                    next_state <= E0;
                else
                    next_state <= IDLE;
                end if;
            when S0 =>
                -- Enviamos señales de salida de estado actual

                -- Actualizamos estado futuro en funcion de las entradas

            when S1 =>
                -- Enviamos señales de salida de estado actual

                -- Actualizamos estado futuro en funcion de las entradas
                    
            when S2 =>

            when S3 =>

            when S4 =>

            when S5 =>

            when S6 =>

            when S7 =>

            when S9 =>
            when S10 =>
            when others => null;
        end case;
    end process;

------------------------------------------------------------------------------
                        -- RESETEO DE ESTADOS --
------------------------------------------------------------------------------ 
    
end Transmition;