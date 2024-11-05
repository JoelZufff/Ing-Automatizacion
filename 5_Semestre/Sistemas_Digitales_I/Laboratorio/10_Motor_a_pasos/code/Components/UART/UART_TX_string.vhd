-- Ver como resolver la parte de especificar cuantos caracteres se mandan a la vez
-- Funcionara de esta forma
    -- IDLE: Estado de espera hasta recibir señal de start
    -- STRING_SEND: Estado que enviara caracter por caracter hasta llegar a char_num, entonces volvera a IDLE
        -- Se carga el caracter a la variable de i_data 
        -- Se envia señal de start poniendo byte_ST = '1'
        -- Espera a que RDY = '1' para enviar el siguiente

------------------------------------------------------------------------------
library IEEE;
use IEEE.std_logic_1164.all;
use IEEE.numeric_std.all;
------------------------------------------------------------------------------
entity UART_TX_string is
    generic 
    (
        char_num        : integer := 10        -- Numero de caracteres a transmitir
    );
	port
	(
		i_FPGA_clk      : in STD_LOGIC;         -- Señal de reloj base
        i_ST            : in STD_LOGIC;         -- Incio de transmision

        -- UART_TX_byte
        o_TX             : out STD_LOGIC        -- Pin TX de transmision serial 
	);
end UART_TX_string;
------------------------------------------------------------------------------
architecture data_tx of UART_TX_string is

    -- Señales y componentes para transmision de 1 byte
    component UART_TX_byte is
        generic 
        (
            clk_freq    : integer;          -- Frecuencia del reloj (Hz)
            baud        : integer           -- Baudios de transmision (bit/s)
        );
        port
        (
            i_FPGA_clk      : in STD_LOGIC;                         -- Señal de reloj base
            i_data          : in STD_LOGIC_VECTOR(7 downto 0);      -- Caracter a transmitir
            i_ST            : in STD_LOGIC;                         -- Señal para indicar inicio de transmision
    
            o_RDY           : out STD_LOGIC;        -- Indica si esta listo para transmitir 
            o_TX            : out STD_LOGIC         -- Pin TX de transmision serial 
        );
    end component;

    signal char_buff        : STD_LOGIC_VECTOR(7 downto 0);
    signal byte_ST          : STD_LOGIC := '0';     -- Desactivado
    signal byte_RDY         : STD_LOGIC := '0';

    -- Señales para transicion de estados
    type states is (IDLE, START_BIT, DATA_BITS, PARITY_BIT, STOP_BIT);
    signal act_state, next_state: states := IDLE; 

begin

    data_TX : UART_TX_byte 
        generic map 
        (
            clk_freq    => 50000000,
            baud        => 9600
        )
        port map 
        (
            i_FPGA_clk  => i_FPGA_clk, 
            i_data      => char_buff, 
            i_ST        => byte_ST, 
            o_RDY       => byte_RDY, 
            o_TX        => o_TX
        );
        
------------------------------------------------------------------------------
                            -- DIVISION DE RELOJ --
------------------------------------------------------------------------------
    process (i_FPGA_clk)
    begin
        if rising_edge(i_FPGA_clk) then
            act_state <= next_state;
        end if;
    end process;

------------------------------------------------------------------------------
                        -- MAQUINA DE ESTADOS FINITOS --
------------------------------------------------------------------------------ 
    process (act_state)
    begin
        case act_state  is  
            when others => null;
        end case;
    end process;

end data_tx;