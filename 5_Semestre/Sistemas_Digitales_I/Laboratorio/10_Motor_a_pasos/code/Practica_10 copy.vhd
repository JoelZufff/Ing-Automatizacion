-- FALTA
    -- Ponerle entrada de RST a todos los componentes, y hacer que reinicie las señales y  maquinas de estado de forma asincrona

    -- Componentes pendientes
        -- LCD  (putstring y putchar)
        -- UART (TX y RX)
        -- Motor a pasos

    -- Ya teniendo los componentes creados, crear maquina de estados que manipula las señales globales para enviar y recibir datos con estos componentes

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
        i_RST               : in STD_LOGIC;         -- Reinicio total
        
        i_ST                : in STD_LOGIC;
        o_RDY               : out STD_LOGIC;
        
        -- LCD
        o_RS, o_E, o_RW     : out STD_LOGIC;
        o_LCD_DATA          : out std_logic_vector(7 downto 0)      -- 8 Bits ASCII
    );
end Practica_10;

architecture rtl of Practica_10 is
    -- DIVISION DE RELOJ --
        component CLK_DIV is
            generic 
            (
                clk_freq    : INTEGER          -- Frecuencia interna de FPGA (Hz)
            );
            port
            (
                i_out_freq      : INTEGER;              -- Frequencia deseada
                
                i_FPGA_clk      : in STD_LOGIC;         -- Señal de reloj base
                o_clk           : out STD_LOGIC    
            );
        end component;
        signal LCD_CLK : STD_LOGIC;
    
    -- LCD -- 
        component LCD_putstring
            port 
            (
                i_RST : in STD_LOGIC;
                i_CLK : in STD_LOGIC;
                o_RS : out STD_LOGIC;
                o_E : out STD_LOGIC;
                o_RW : out STD_LOGIC;
                o_LCD_DATA : out std_logic_vector(7 downto 0);
                i_ST : in STD_LOGIC;
                i_string : in STD_LOGIC_VECTOR(255 downto 0);
                o_RDY : out STD_LOGIC
            );
        end component;
        
        signal LCD_string : STD_LOGIC_VECTOR(255 downto 0) := STD_LOGIC_VECTOR(to_unsigned(0, 256)); -- 33 caracteres (32 char y un salto de linea) 
        signal RDY : STD_LOGIC;     -- TEMPORAL

    -- MAQUINA DE ESTADOS FINITOS --
        type states is (IDLE, S0, S1, S2, S3, S4);
        signal act_state, next_state: states := IDLE;

    -- ABECEDARIO --
        constant l_AA : STD_LOGIC_VECTOR(7 downto 0) := X"41";
        constant l_BB : STD_LOGIC_VECTOR(7 downto 0) := X"42";
        constant l_CC : STD_LOGIC_VECTOR(7 downto 0) := X"43";
        constant l_DD : STD_LOGIC_VECTOR(7 downto 0) := X"44";
        constant l_EE : STD_LOGIC_VECTOR(7 downto 0) := X"45";
        constant l_FF : STD_LOGIC_VECTOR(7 downto 0) := X"46";
        constant l_GG : STD_LOGIC_VECTOR(7 downto 0) := X"47";
        constant l_HH : STD_LOGIC_VECTOR(7 downto 0) := X"48";
        constant l_II : STD_LOGIC_VECTOR(7 downto 0) := X"49";
        constant l_JJ : STD_LOGIC_VECTOR(7 downto 0) := X"4A";
        constant l_KK : STD_LOGIC_VECTOR(7 downto 0) := X"4B";
        constant l_LL : STD_LOGIC_VECTOR(7 downto 0) := X"4C";
        constant l_MM : STD_LOGIC_VECTOR(7 downto 0) := X"4D";
        constant l_NN : STD_LOGIC_VECTOR(7 downto 0) := X"4E";
        constant l_OO : STD_LOGIC_VECTOR(7 downto 0) := X"4F";
        constant l_PP : STD_LOGIC_VECTOR(7 downto 0) := X"50";
        constant l_QQ : STD_LOGIC_VECTOR(7 downto 0) := X"51";
        constant l_RR : STD_LOGIC_VECTOR(7 downto 0) := X"52";
        constant l_SS : STD_LOGIC_VECTOR(7 downto 0) := X"53";
        constant l_TT : STD_LOGIC_VECTOR(7 downto 0) := X"54";
        constant l_UU : STD_LOGIC_VECTOR(7 downto 0) := X"55";
        constant l_VV : STD_LOGIC_VECTOR(7 downto 0) := X"56";
        constant l_WW : STD_LOGIC_VECTOR(7 downto 0) := X"57";
        constant l_XX : STD_LOGIC_VECTOR(7 downto 0) := X"58";
        constant l_YY : STD_LOGIC_VECTOR(7 downto 0) := X"59";
        constant l_ZZ : STD_LOGIC_VECTOR(7 downto 0) := X"5A";

        constant l_a : STD_LOGIC_VECTOR(7 downto 0) := X"61";
        constant l_b : STD_LOGIC_VECTOR(7 downto 0) := X"62";
        constant l_c : STD_LOGIC_VECTOR(7 downto 0) := X"63";
        constant l_d : STD_LOGIC_VECTOR(7 downto 0) := X"64";
        constant l_e : STD_LOGIC_VECTOR(7 downto 0) := X"65";
        constant l_f : STD_LOGIC_VECTOR(7 downto 0) := X"66";
        constant l_g : STD_LOGIC_VECTOR(7 downto 0) := X"67";
        constant l_h : STD_LOGIC_VECTOR(7 downto 0) := X"68";
        constant l_i : STD_LOGIC_VECTOR(7 downto 0) := X"69";
        constant l_j : STD_LOGIC_VECTOR(7 downto 0) := X"6A";
        constant l_k : STD_LOGIC_VECTOR(7 downto 0) := X"6B";
        constant l_l : STD_LOGIC_VECTOR(7 downto 0) := X"6C";
        constant l_m : STD_LOGIC_VECTOR(7 downto 0) := X"6D";
        constant l_n : STD_LOGIC_VECTOR(7 downto 0) := X"6E";
        constant l_o : STD_LOGIC_VECTOR(7 downto 0) := X"6F";
        constant l_p : STD_LOGIC_VECTOR(7 downto 0) := X"70";
        constant l_q : STD_LOGIC_VECTOR(7 downto 0) := X"71";
        constant l_r : STD_LOGIC_VECTOR(7 downto 0) := X"72";
        constant l_s : STD_LOGIC_VECTOR(7 downto 0) := X"73";
        constant l_t : STD_LOGIC_VECTOR(7 downto 0) := X"74";
        constant l_u : STD_LOGIC_VECTOR(7 downto 0) := X"75";
        constant l_v : STD_LOGIC_VECTOR(7 downto 0) := X"76";
        constant l_w : STD_LOGIC_VECTOR(7 downto 0) := X"77";
        constant l_x : STD_LOGIC_VECTOR(7 downto 0) := X"78";
        constant l_y : STD_LOGIC_VECTOR(7 downto 0) := X"79";
        constant l_z : STD_LOGIC_VECTOR(7 downto 0) := X"7A";

        constant l_sp : STD_LOGIC_VECTOR(7 downto 0) := X"20";

begin
    o_RDY <= not RDY;
    
    c_LCD_CLK : CLK_DIV
        generic map ( clk_freq => clk_freq )
        port map ( i_out_freq => 1000, i_FPGA_clk => i_FPGA_clk, o_clk => LCD_CLK );

    LCD_string <=
        l_HH & l_o & l_l & l_a & l_sp & l_s & l_o & l_y & l_sp & l_JJ & l_o & l_e & l_l &  l_sp & l_sp & l_sp
        & l_SS & l_II & l_UU & l_UU & l_UU & l_sp & l_sp & l_sp & l_sp & l_sp & l_sp & l_sp & l_sp &  l_sp & l_sp & l_sp;

    LCD : LCD_putstring
        port map ( i_RST => not i_RST, i_CLK => LCD_CLK, o_RS => o_RS, o_E => o_E, o_RW => o_RW, o_LCD_DATA => o_LCD_DATA, i_ST => i_ST, i_string => LCD_string, o_RDY => RDY );

end architecture;


-- NOTA USAR SIEMPRE LA MISMA FRECUENCIA DE TRABAJO EN TODO lo que se comunique entre si