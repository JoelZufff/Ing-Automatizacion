library IEEE;
use IEEE.std_logic_1164.all;
use IEEE.numeric_std.all;

entity Practica_9 is
    generic 
    (
        clk_freq        : INTEGER := 50000000   
    );
	port
	(
		i_FPGA_CLK      : in STD_LOGIC;     -- Clock
        i_RST           : in STD_LOGIC;     -- Reset

        -- LCD
        i_ST                : in STD_LOGIC;     -- Señal de start
        o_RS, o_E, o_RW     : out STD_LOGIC;
		o_LCD_DATA          : out std_logic_vector(7 downto 0);     -- 8 Bits ASCII

        -- UART_RX
        i_RX            : in STD_LOGIC                         -- Reception PIN
    );
end Practica_9;

architecture Reception of Practica_9 is
    
    -- Componente de recepcion UART
    component UART_RX is
        generic 
        (
            baud_freq       : INTEGER;
            clk_freq        : INTEGER   
        );
        port
        (
            i_FPGA_CLK      : in STD_LOGIC;                         -- Oscilador de placa (50 MHz)
            i_RST           : in STD_LOGIC;                         -- Boton de reset (Para errores de paridad)
    
            i_RX            : in STD_LOGIC;                         -- Reception PIN
            o_NEW           : out STD_LOGIC;                        -- Indica que se recibio un nuevo dato
            o_DATA          : out STD_LOGIC_VECTOR(7 downto 0)      -- Valor de dato receptado
        ); 
    end component;

    signal RX_DATA : STD_LOGIC_VECTOR(7 downto 0) := X"41";   -- A
    signal RX_NEW : STD_LOGIC;   -- A

    -- Componente de LCD
    component LCD is
        port
        (
            i_FPGA_CLK          : in STD_LOGIC;
            i_RST               : in STD_LOGIC;
    
            i_DATA              : in STD_LOGIC_VECTOR(7 downto 0);
            i_ST                : in STD_LOGIC;                         -- Señal de start
            o_RS, o_E, o_RW     : out STD_LOGIC;
            o_LCD_DATA          : out std_logic_vector(7 downto 0)      -- 8 Bits ASCII
    
        ); 
    end component;

begin

    data_receive : UART_RX
        generic map ( baud_freq => 9600, clk_freq => clk_freq )
        port map ( i_FPGA_CLK => i_FPGA_CLK, i_RST => i_RST, i_RX => i_RX, o_NEW => RX_NEW, o_DATA => RX_DATA );
    
    data_printing : LCD port map ( i_FPGA_CLK, i_RST, RX_DATA, i_ST, o_RS, o_E, o_RW, o_LCD_DATA);

end Reception;