-- FALTA
    -- Ponerle entrada de RST a todos los componentes, y hacer que reinicie las señales y  maquinas de estado de forma asincrona

    -- Crear componente de LCD para enviar cadenas de caracteres
    -- Crear componente motor a pasos


    -- 1 switch de inicio y 1 de paro
        -- Cuando se presione paro, volvera a la posicion inicial y eliminar la cola de distancias
    -- 1 switches que modifiquen la velocidad del motor (0 = Baja, 1 = Alta)
    -- Comunicacion UART para seleccionar distancia

    -- IDLE: En espera de distancia deseada y presion de boton de start
        -- Mandar mensaje en la LCD cada vez que se detecte una distancia deseada
            -- Si solo se presiona un boton, mostrar en LCD el valor de la distancia de ese boton
        -- Detectara las distancias deseadas en funcion de los 3 botones de seleccion
        -- Si se presiona start y solo se detecta la presion de un boton (Ver funcion booleana XOR), almacenar distancia deseada y pasar a estado de COUPLING
    -- COUPLING: Acomplamiento de distancia actual con distancia deseada (Contar pasos recorridos)
        -- Se mantiene en este estado hasta recorrer los pasos de la distancia deseada
        -- Si se detecta una recepcion de distancia en este estado, se almacenara la distancia deseada en un arreglo de distancias proximas con un maximo de n distancias
    -- RESTING: Estado que pone distancia deseada en 0, espera 2 segundos en distancia deseada, y vuelve al estado de COUPLING

library IEEE;
use IEEE.std_logic_1164.all;
use IEEE.numeric_std.all;
------------------------------------------------------------------------------
entity Practica_10 is
    generic 
    (
        clk_freq        : INTEGER := 50000000   
    );
    port
    (
        i_FPGA_clk          : in STD_LOGIC;         -- Señal de reloj base
        i_RST               : in STD_LOGIC;
        
        -- LCD
        i_ST                : in STD_LOGIC;                         -- Señal de start
        o_RS, o_E, o_RW     : out STD_LOGIC;
        o_LCD_DATA          : out std_logic_vector(7 downto 0)      -- 8 Bits ASCII

    );
end Practica_10;

architecture rtl of Practica_10 is
    
    -- LCD --
    component LCD is
        generic 
        (
            clk_freq        : INTEGER    
        );
        port
        (
            i_FPGA_CLK          : in STD_LOGIC;
            i_RST               : in STD_LOGIC;
    
            i_ST                : in STD_LOGIC;                         -- Señal de start
            --i_DATA              : in STD_LOGIC_VECTOR(7 downto 0);
            i_text              : STRING(1 to 32);                      -- Cadena a escribir
            
            o_RS, o_E, o_RW     : out STD_LOGIC;
            o_LCD_DATA          : out std_logic_vector(7 downto 0)      -- 8 Bits ASCII
        ); 
    end component;

    signal DATA : STD_LOGIC_VECTOR(7 downto 0) := X"4F";

    -- FSM --
    type states is (IDLE, START_BIT, DATA_BITS, PARITY_BIT, STOP_BIT);
    signal act_state, next_state: states := IDLE;

begin

    c_LCD : LCD 
        generic map ( clk_freq => clk_freq )
        port map ( i_FPGA_CLK  => i_FPGA_CLK, i_RST => i_RST, i_ST => i_ST, i_text => "012345678901234567890123456789012", o_RS => o_RS, o_E => o_E, o_RW => o_RW, o_LCD_DATA => o_LCD_DATA );

end architecture;