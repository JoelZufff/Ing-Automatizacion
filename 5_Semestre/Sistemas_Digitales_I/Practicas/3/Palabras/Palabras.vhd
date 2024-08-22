library IEEE;
use IEEE.std_logic_1164.all;
use IEEE.numeric_std.all;

entity Palabras is
   port 
	(
        clock           : in    std_logic;
        i_buttons 		: in 	std_logic_vector(3 downto 0); 		-- Entrada de 4 bits para escoger palabras 
		o_segmentos     : out 	std_logic_vector(7 downto 0);   	-- Salida para el display de 7 segmentos
		o_comunes       : out 	std_logic_vector(3 downto 0)   	    -- Salida para comun de cada display
	);
end Palabras;

architecture Multiplexado of Palabras is
    -- Las señales son variables que no tienen un pin asignado
    signal count        : integer range 0 to 10000;
    signal comun_index  : integer range 0 to 4;

    constant A_Letter   : std_logic_vector(7 downto 0) := "10001000";
    constant B_Letter   : std_logic_vector(7 downto 0) := "10000011";
    constant C_Letter   : std_logic_vector(7 downto 0) := "11000110";
    constant D_Letter   : std_logic_vector(7 downto 0) := "10100001";
    constant E_Letter   : std_logic_vector(7 downto 0) := "10000110";
    constant F_Letter   : std_logic_vector(7 downto 0) := "10001110";
    constant G_Letter   : std_logic_vector(7 downto 0) := "10000010";
    constant H_Letter   : std_logic_vector(7 downto 0) := "10001001";
    constant I_Letter   : std_logic_vector(7 downto 0) := "11001111";
    constant J_Letter   : std_logic_vector(7 downto 0) := "11100001";
    constant K_Letter   : std_logic_vector(7 downto 0) := "10000101";
    constant L_Letter   : std_logic_vector(7 downto 0) := "11000111"; 
    constant M_Letter   : std_logic_vector(7 downto 0) := "10110000"; 
    constant N_Letter   : std_logic_vector(7 downto 0) := "11001000";
    constant N2_Letter  : std_logic_vector(7 downto 0) := "10101010";
    constant O_Letter   : std_logic_vector(7 downto 0) := "11000000";
    constant P_Letter   : std_logic_vector(7 downto 0) := "10001100"; 
    constant Q_Letter   : std_logic_vector(7 downto 0) := "10011000"; 
    constant R_Letter   : std_logic_vector(7 downto 0) := "11001110"; 
    constant S_Letter   : std_logic_vector(7 downto 0) := "10010010"; 
    constant T_Letter   : std_logic_vector(7 downto 0) := "10000111"; 
    constant U_Letter   : std_logic_vector(7 downto 0) := "11000001"; 
    constant W_Letter   : std_logic_vector(7 downto 0) := "10000110";  
    constant Z_Letter   : std_logic_vector(7 downto 0) := "10100100";

    signal letter1       : std_logic_vector(7 downto 0) := H_Letter; -- H
    signal letter2       : std_logic_vector(7 downto 0) := O_Letter; -- O
    signal letter3       : std_logic_vector(7 downto 0) := L_Letter; -- L
    signal letter4       : std_logic_vector(7 downto 0) := A_Letter; -- A

begin
	
    -- Reloj para delay de multiplexado
    delay_clock : process (clock)
    begin
        if rising_edge(clock) then
            if count < 10000 then
                count <= count + 1;
            else
                if comun_index < 4 then
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
            when 0 => 
                o_comunes   <= "0111";
                o_segmentos <= letter1; 
            when 1 => 
                o_comunes <= "1011";
                o_segmentos <= letter2; 
            when 2 => 
                o_comunes <= "1101";
                o_segmentos <= letter3; 
            when 3 => 
                o_comunes <= "1110";
                o_segmentos <= letter4; 
            when others => 
                o_comunes <= "1111"; 
        end case;            
    end process;

    -- Deteccion de combinatoria de botones
    button_detection : process (i_buttons)
    begin
        if i_buttons = "1111" then -- Ningun boton apretado
            letter1 <= E_Letter;
            letter2 <= S_Letter;
            letter3 <= T_Letter;
            letter4 <= E_Letter;
        elsif i_buttons = "1110" then
            letter1 <= P_Letter;
            letter2 <= A_Letter;
            letter3 <= T_Letter;
            letter4 <= O_Letter;
        elsif i_buttons = "1101" then
            letter1 <= N_Letter;
            letter2 <= A_Letter;
            letter3 <= D_Letter;
            letter4 <= A_Letter;
        elsif i_buttons = "1100" then
            letter1 <= S_Letter;
            letter2 <= O_Letter;
            letter3 <= L_Letter;
            letter4 <= O_Letter;
        elsif i_buttons = "1011" then
            letter1 <= O_Letter;
            letter2 <= T_Letter;
            letter3 <= R_Letter;
            letter4 <= O_Letter;
        elsif i_buttons = "1010" then
            letter1 <= G_Letter;
            letter2 <= A_Letter;
            letter3 <= T_Letter;
            letter4 <= O_Letter;
        elsif i_buttons = "1001" then
            letter1 <= B_Letter;
            letter2 <= E_Letter;
            letter3 <= B_Letter;
            letter4 <= E_Letter;
        elsif i_buttons = "1000" then
            letter1 <= A_Letter;
            letter2 <= G_Letter;
            letter3 <= U_Letter;
            letter4 <= A_Letter;
        elsif i_buttons = "0111" then
            letter1 <= L_Letter;
            letter2 <= U_Letter;
            letter3 <= I_Letter;
            letter4 <= S_Letter;
        elsif i_buttons = "0110" then
            letter1 <= H_Letter;
            letter2 <= A_Letter;
            letter3 <= C_Letter;
            letter4 <= E_Letter;
        elsif i_buttons = "0101" then
            letter1 <= T_Letter;
            letter2 <= O_Letter;
            letter3 <= D_Letter;
            letter4 <= O_Letter;
        elsif i_buttons = "0100" then
            letter1 <= B_Letter;
            letter2 <= I_Letter;
            letter3 <= E_Letter;
            letter4 <= N_Letter;
        elsif i_buttons = "0011" then
            letter1 <= C_Letter;
            letter2 <= A_Letter;
            letter3 <= D_Letter;
            letter4 <= A_Letter;
        elsif i_buttons = "0010" then
            letter1 <= C_Letter;
            letter2 <= A_Letter;
            letter3 <= S_Letter;
            letter4 <= A_Letter;
        elsif i_buttons = "0001" then
            letter1 <= E_Letter;
            letter2 <= S_Letter;
            letter3 <= T_Letter;
            letter4 <= A_Letter;
        elsif i_buttons = "0000" then
            letter1 <= S_Letter;
            letter2 <= O_Letter;
            letter3 <= L_Letter;
            letter4 <= A_Letter;
        end if;

    end process;


end Multiplexado;


-- display <=	"10001000" when "11111", -- A
--            "10000011" when "11110", -- B
--            "11000110" when "11101", -- C
--            "10100001" when "11100", -- D
--            "10000110" when "11011", -- E
--            "10001110" when "11010", -- F
--            "10000010" when "11001", -- G
--            "10001001" when "11000", -- H
--            "11001111" when "10111", -- I
--            "11100001" when "10110", -- J
--            "10000101" when "10101", -- K
--            "11000111" when "10100", -- L 
--            "10110000" when "10011", -- M 
--            "11001000" when "10010", -- N
--            "10101010" when "10001", -- Ñ
--            "11000000" when "10000", -- O
--            "10001100" when "01111", -- P 
--            "10011000" when "01110", -- Q 
--            "11001110" when "01101", -- R 
--            "10010010" when "01100", -- S 
--            "10000111" when "01011", -- T 
--            "11000001" when "01010", -- U 
--            "10000110" when "01001", -- W  
--            "10100100" when "01000", -- Z
--            "00000000" when others;