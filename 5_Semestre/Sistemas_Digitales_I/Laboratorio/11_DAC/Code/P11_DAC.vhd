------------------------------------------------------------------------------
library IEEE;
use IEEE.std_logic_1164.all;
use IEEE.numeric_std.all;
------------------------------------------------------------------------------
entity P11_DAC is
    generic 
    (
        CLK_FREQ    : INTEGER := 50000000
    );
    port
    (
        i_CLK       : in STD_LOGIC;                         -- Señal de reloj base
        i_RST       : in STD_LOGIC;                         -- Reinicio total

        i_SEL       : in STD_LOGIC_VECTOR(1 downto 0);      -- Botones de seleccion
        i_ST        : in STD_LOGIC;                         -- Boton de start

        o_RDY       : out STD_LOGIC;                        -- Ready

        -- I/O fisicos MCP4802
        o_SDI       : out STD_LOGIC;                        -- Datos seriales
        o_SCK       : out STD_LOGIC;                        -- Señal de reloj
        o_CS        : out STD_LOGIC;                        -- Chip select
        o_LDAC      : out STD_LOGIC;                        -- Latch DAC

        -- I/O fisicos display
        o_DISP_SEG  : out std_logic_vector(7 downto 0);     -- 7 segmentos
		o_DISP_COM  : out std_logic_vector(1 downto 0)      -- 4 comunes
    );
end P11_DAC;

architecture rtl of P11_DAC is
    
    signal RDY : STD_LOGIC := '0';
    
    -- DAC MCP4802 --
        component DAC_MCP4802 is
            generic 
            (
                CLK_FREQ    : INTEGER
            );
            port
            (
                i_CLK       : in STD_LOGIC;                         -- Señal de reloj base
                i_RST       : in STD_LOGIC;                         -- Reinicio total
                
                i_ST        : in STD_LOGIC;                         -- Señal de start
                i_DAC_CONF  : in STD_LOGIC_VECTOR(3 downto 0);      -- 4 Bits para configuracion de DAC
                i_DAC_VOLT  : in STD_LOGIC_VECTOR(7 downto 0);      -- 8 Bits para resolucion de voltaje analogico
                
                o_RDY       : out STD_LOGIC;                        -- Ready
        
                -- Salidas fisicas MCP4802
                o_SDI       : out STD_LOGIC;                        -- Datos seriales
                o_SCK       : out STD_LOGIC;                        -- Señal de reloj
                o_CS        : out STD_LOGIC;                        -- Chip select
                o_LDAC      : out STD_LOGIC                        	-- Latch DAC
            );
        end component;

        type array_4 is array(0 to 3) of std_logic_vector(7 downto 0);
        constant DAC_VOLT : array_4 := ( "11111111", "10100000", "01000000", "00100000" );  -- 5 | 2.5 | 1.0 | 0.5

    -- DISPLAY --
        component DISPLAY_PRINT is
            generic 
            (
                CLK_FREQ    : INTEGER
            );
            port
            (
                i_CLK       : in STD_LOGIC;                         -- Señal de reloj base
                i_RST       : in STD_LOGIC;                         -- Reinicio total
        
                i_NUM0      : in STD_LOGIC_VECTOR(7 downto 0);
                i_NUM1      : in STD_LOGIC_VECTOR(7 downto 0);
        
                -- I/O fisicos display
                o_DISP_SEG  : out STD_LOGIC_VECTOR(7 downto 0);     -- 7 segmentos
                o_DISP_COM  : out STD_LOGIC_VECTOR(1 downto 0)      -- 2 comunes
            );
        end component;

        type array_2 is array(0 to 1) of std_logic_vector(7 downto 0);
        signal DISP_NUM : array_2 := ( "01000000", "11000000" );            -- 0.0
        
        type array_4_2 is array (0 to 3) of array_2;
        constant VOLTAGES : array_4_2 := ( ( "00011001", "11000000" ), ( "00100100", "10010010" ), ( "01111001", "11000000" ), ( "01000000", "10010010" ) );   -- 4.0 | 2.5 | 1.0 | 0.5

begin
    ------------------------------------------------------------------------------
                            -- DISPLAY DE 7 SEGMENTOS --
    ------------------------------------------------------------------------------
    c_DISP_PRINT : DISPLAY_PRINT
        generic map ( CLK_FREQ => CLK_FREQ )
        port map ( i_CLK => i_CLK, i_RST => not i_RST, i_NUM0 => DISP_NUM(0), i_NUM1 => DISP_NUM(1), o_DISP_SEG => o_DISP_SEG, o_DISP_COM => o_DISP_COM );

    ------------------------------------------------------------------------------
                            -- DIGITAL TO ANALOG CONVERTER --
    ------------------------------------------------------------------------------
    process (i_ST)                                  -- Actualizacion de Display
    begin
        if(falling_edge(i_ST)) then
            DISP_NUM <= VOLTAGES(to_integer(unsigned(i_SEL)));
        end if;
    end process;
    o_RDY <= not RDY;           -- El led es anodo
    
    c_DAC_MCP4802 : DAC_MCP4802
        generic map ( CLK_FREQ => CLK_FREQ )
        port map ( i_CLK => i_CLK, i_RST => not i_RST, i_ST => i_ST, i_DAC_CONF => "0001", i_DAC_VOLT => DAC_VOLT(to_integer(unsigned(i_SEL))), o_RDY => RDY, o_SDI => o_SDI, o_SCK => o_SCK, o_CS => o_CS, o_LDAC => o_LDAC );

end architecture;