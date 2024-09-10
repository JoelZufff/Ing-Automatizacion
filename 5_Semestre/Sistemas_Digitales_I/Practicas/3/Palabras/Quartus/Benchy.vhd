    library IEEE;
    use IEEE.std_logic_1164.all;
    use IEEE.numeric_std.all;

    architecture TB of P3_TB is
        component Palabras
            port
            (
                clock           : in    std_logic;
                i_buttons 		: in 	std_logic_vector(3 downto 0); 		-- Entrada de 4 bits para escoger palabras
                o_segmentos     : out 	std_logic_vector(7 downto 0);   	-- Salida para el display de 7 segmentos
                o_comunes       : out 	std_logic_vector(3 downto 0)   	    -- Salida para comun de cada display
            );
        end component;

    -- We simulate de input and output values
    signal clock        : std_logic;
    signal i_buttons    : std_logic_vector(3 downto 0);     -- Inputs
    signal o_segmentos  : std_logic_vector(7 downto 0);     -- Outputs
    signal o_comunes    : std_logic_vector(3 downto 0);     -- Outputs

    begin
        inicio: P1 port map 
            (
                clock <= clock,
                i_buttons <= i_buttons,
                o_segmentos <= o_segmentos,
                o_comunes <= o_comunes
            );
        
        Simulation : process
        begin
            i_buttons <= "1111"; wait for 10ns;
            i_buttons <= "1110"; wait for 10ns;
            i_buttons <= "1101"; wait for 10ns;
            i_buttons <= "1100"; wait for 10ns;
            i_buttons <= "1011"; wait for 10ns;
            i_buttons <= "1010"; wait for 10ns;
            i_buttons <= "1001"; wait for 10ns;
            i_buttons <= "1000"; wait for 10ns;
            i_buttons <= "0111"; wait for 10ns;
            i_buttons <= "0110"; wait for 10ns;
            i_buttons <= "0101"; wait for 10ns;
            i_buttons <= "0100"; wait for 10ns;
            i_buttons <= "0011"; wait for 10ns;
            i_buttons <= "0010"; wait for 10ns;
            i_buttons <= "0001"; wait for 10ns;
            i_buttons <= "0000"; wait for 10ns;
        end	process Simulation;
    end TB;