library IEEE;
use IEEE.std_logic_1164.all;
use IEEE.numeric_std.all;

entity Palabras is
   port
	(
        i_buttons 		: in 	std_logic_vector(3 downto 0); 		-- Entrada de 4 bits para escoger palabras 
		o_segmentos1    : out 	std_logic_vector(7 downto 0);   	-- Salida para el display de 7 segmentos 
		o_segmentos2    : out 	std_logic_vector(7 downto 0);   	-- Salida para el display de 7 segmentos
		o_segmentos3    : out 	std_logic_vector(7 downto 0);   	-- Salida para el display de 7 segmentos
		o_segmentos4    : out 	std_logic_vector(7 downto 0);   	-- Salida para el display de 7 segmentos
		o_comunes       : out 	std_logic_vector(3 downto 0)   	    -- Salida para comun de cada display
	);
end Palabras;

architecture Multiplexado of Palabras is					   

    -- Las señales son variables que no tienen un pin asignado
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
	 
begin
	
    -- Deteccion de combinatoria de botones
    button_detection : process (i_buttons)
    begin
        if i_buttons = "1111" then -- Ningun boton apretado
            o_segmentos1 <= E_Letter;
            o_segmentos2 <= S_Letter;
            o_segmentos3 <= T_Letter;
            o_segmentos4 <= E_Letter;
        elsif i_buttons = "1110" then
            o_segmentos1 <= P_Letter;
            o_segmentos2 <= A_Letter;
            o_segmentos3 <= T_Letter;
            o_segmentos4 <= O_Letter;
        elsif i_buttons = "1101" then
            o_segmentos1 <= N_Letter;
            o_segmentos2 <= A_Letter;
            o_segmentos3 <= D_Letter;
            o_segmentos4 <= A_Letter;
        elsif i_buttons = "1100" then
            o_segmentos1 <= S_Letter;
            o_segmentos2 <= O_Letter;
            o_segmentos3 <= L_Letter;
            o_segmentos4 <= O_Letter;
        elsif i_buttons = "1011" then
            o_segmentos1 <= O_Letter;
            o_segmentos2 <= T_Letter;
            o_segmentos3 <= R_Letter;
            o_segmentos4 <= O_Letter;
        elsif i_buttons = "1010" then
            o_segmentos1 <= G_Letter;
            o_segmentos2 <= A_Letter;
            o_segmentos3 <= T_Letter;
            o_segmentos4 <= O_Letter;
        elsif i_buttons = "1001" then
            o_segmentos1 <= B_Letter;
            o_segmentos2 <= E_Letter;
            o_segmentos3 <= B_Letter;
            o_segmentos4 <= E_Letter;
        elsif i_buttons = "1000" then
            o_segmentos1 <= A_Letter;
            o_segmentos2 <= G_Letter;
            o_segmentos3 <= U_Letter;
            o_segmentos4 <= A_Letter;
        elsif i_buttons = "0111" then
            o_segmentos1 <= L_Letter;
            o_segmentos2 <= U_Letter;
            o_segmentos3 <= I_Letter;
            o_segmentos4 <= S_Letter;
        elsif i_buttons = "0110" then
            o_segmentos1 <= H_Letter;
            o_segmentos2 <= A_Letter;
            o_segmentos3 <= C_Letter;
            o_segmentos4 <= E_Letter;
        elsif i_buttons = "0101" then
            o_segmentos1 <= T_Letter;
            o_segmentos2 <= O_Letter;
            o_segmentos3 <= D_Letter;
            o_segmentos4 <= O_Letter;
        elsif i_buttons = "0100" then
            o_segmentos1 <= B_Letter;
            o_segmentos2 <= I_Letter;
            o_segmentos3 <= E_Letter;
            o_segmentos4 <= N_Letter;
        elsif i_buttons = "0011" then
            o_segmentos1 <= C_Letter;
            o_segmentos2 <= A_Letter;
            o_segmentos3 <= D_Letter;
            o_segmentos4 <= A_Letter;
        elsif i_buttons = "0010" then
            o_segmentos1 <= C_Letter;
            o_segmentos2 <= A_Letter;
            o_segmentos3 <= S_Letter;
            o_segmentos4 <= A_Letter;
        elsif i_buttons = "0001" then
            o_segmentos1 <= E_Letter;
            o_segmentos2 <= S_Letter;
            o_segmentos3 <= T_Letter;
            o_segmentos4 <= A_Letter;
        elsif i_buttons = "0000" then
            o_segmentos1 <= S_Letter;
            o_segmentos2 <= O_Letter;
            o_segmentos3 <= L_Letter;
            o_segmentos4 <= A_Letter;
        end if;

    end process;


end Multiplexado;