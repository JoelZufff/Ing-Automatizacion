-- 1. Ponemos CS en bajo
-- 2. Enviamos pulso en bajo a WR (min 100 ns)
-- 2. Ponemos CD en alto
-- 3. Al detectar flanco de bajada de WR, el pin de interrupcion (INTR) tiene un flanco de subida
-- 4. Al detectar finalizacion de pulso bajo en WR, comienza la conversion y al finalizar el pin INTR tendra un flanco de bajada
------------------------------------------------------------------------------
library IEEE;
use IEEE.std_logic_1164.all;
use IEEE.numeric_std.all;
------------------------------------------------------------------------------
entity P12_ADC is
    generic 
    (
        CLK_FREQ    : INTEGER := 50000000
    );
    port
    (
        i_CLK       : in STD_LOGIC;                         -- Señal de reloj base
        i_RST       : in STD_LOGIC;                         -- Reinicio total

        i_GET       : in STD_LOGIC;                         -- Boton para solicitar una conversion
        i_READ      : in STD_LOGIC;                         -- Boton para solicitar una lectura

        -- I/O fisicos ADC0804
        i_INTR      : in STD_LOGIC;                         -- Interrupcion
        i_DATA      : in STD_LOGIC_VECTOR(7 downto 0);      -- 8 Bits de datos
        o_CS        : out STD_LOGIC;                        -- Chip select
        o_RD        : out STD_LOGIC;                        -- Lectura
        o_WR        : out STD_LOGIC;                        -- Escritura
        o_CLK_IN    : out STD_LOGIC;                        -- Clock

        -- I/O fisicos display
        o_DISP_SEG  : out std_logic_vector(7 downto 0);     -- 7 segmentos
		o_DISP_COM  : out std_logic_vector(3 downto 0)      -- 4 comunes
    );
end P12_ADC;

architecture rtl of P12_ADC is
    
    signal RDY : STD_LOGIC := '0';

    -- DIVISOR DE RELOJ --
        component CLK_DIV
            generic 
            (
                clk_freq : INTEGER
            );
            port 
            (
                i_out_freq :  INTEGER;
                i_FPGA_clk : in STD_LOGIC;
                o_clk : out STD_LOGIC
            );
        end component;
        signal ADC_CLK : STD_LOGIC;

    -- MAQUINA DE ESTADOS FINITOS --
        type states is (IDLE);
        signal act_state : states := IDLE;
    
    -- DISPLAY CON DECODER BCD DE 8 BITS --
        component DISPLAY_BCD
            generic 
            (
                CLK_FREQ : INTEGER
            );
            port 
            (
                i_CLK : in STD_LOGIC;
                i_DATA : in STD_LOGIC_VECTOR(7 downto 0);
                o_DISP_SEG : out STD_LOGIC_VECTOR(7 downto 0);
                o_DISP_COM : out STD_LOGIC_VECTOR(3 downto 0)
            );
        end component;

    -- Modulo ADC0804LCN --
        component ADC_0804LCN
            generic 
            (
                CLK_FREQ : INTEGER
            );
            port 
            (
                i_CLK : in STD_LOGIC;
                i_RST : in STD_LOGIC;
                i_GET : in STD_LOGIC;
                i_READ : in STD_LOGIC;
                o_DATA : out STD_LOGIC_VECTOR(7 downto 0);
                i_INTR : in STD_LOGIC;
                i_DATA : in STD_LOGIC_VECTOR(7 downto 0);
                o_CS : out STD_LOGIC;
                o_RD : out STD_LOGIC;
                o_WR : out STD_LOGIC;
                o_CLK_IN : out STD_LOGIC
            );
        end component;

        signal DATA : STD_LOGIC_VECTOR(7 downto 0);

begin

    ------------------------------------------------------------------------------
                -- IMPRESION DE BITS DE ADC EN DISPLAY DE 7 SEG --
    ------------------------------------------------------------------------------
    c_DISPLAY_BCD : DISPLAY_BCD
        generic map ( clk_freq => CLK_FREQ )
        port map ( i_CLK => i_CLK, i_DATA => DATA, o_DISP_SEG => o_DISP_SEG, o_DISP_COM => o_DISP_COM);

    ------------------------------------------------------------------------------
                                -- MODULO ADC0804LCN --
    ------------------------------------------------------------------------------
    c_ADC_0804LCN : ADC_0804LCN
        generic map ( CLK_FREQ => CLK_FREQ )
        port map ( i_CLK => i_CLK, i_RST => not i_RST, i_GET => i_GET, i_READ => i_READ, o_DATA => DATA, i_INTR => i_INTR, i_DATA => i_DATA, o_CS => o_CS, o_RD => o_RD, o_WR => o_WR, o_CLK_IN => o_CLK_IN );
    
end architecture;