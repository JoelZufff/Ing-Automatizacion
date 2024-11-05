library IEEE;
use IEEE.std_logic_1164.all;
use IEEE.numeric_std.all;

entity Practica_9 is
	port
	(
		i_FPGA_CLK      : in STD_LOGIC;     -- Clock
        i_RST           : in STD_LOGIC;     -- Reset

        -- LCD
        i_ST                : in STD_LOGIC;     -- Señal de start
        o_RS, o_E, o_RW     : out STD_LOGIC;
		o_LCD_DATA          : out std_logic_vector(7 downto 0);     -- 8 Bits ASCII

        -- UART_RX
        i_RX            : in STD_LOGIC;                         -- Reception PIN
        o_DVD           : out STD_LOGIC
        --o_RDY           : out STD_LOGIC                        -- End Of Reception
    );
end Practica_9;

architecture Reception of Practica_9 is
    
    -- Componente de recepcion UART
    component UART_RX is
        port
        (
            i_FPGA_CLK      : in STD_LOGIC;                         -- Oscilador de placa (50 MHz)
            i_RST           : in STD_LOGIC;                         -- Boton de reset (Para errores de paridad)
    
            i_RX            : in STD_LOGIC;                         -- Reception PIN
            o_DVD           : out STD_LOGIC;
            o_RDY           : out STD_LOGIC;                        -- Bandera de finalizacion
            o_DATA          : out STD_LOGIC_VECTOR(7 downto 0)      -- Valor de dato receptado
        ); 
    end component;
    signal RDY : STD_LOGIC := '0';
    signal DATA : STD_LOGIC_VECTOR(7 downto 0) := "01000001";   -- A

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

    data_receive : UART_RX port map ( i_FPGA_CLK, i_RST, i_RX, o_DVD, RDY, DATA );
    data_printing : LCD port map ( i_FPGA_CLK, i_RST, DATA, i_ST, o_RS, o_E, o_RW, o_LCD_DATA);

end Reception;