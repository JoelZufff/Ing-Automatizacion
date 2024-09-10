library IEEE;
use IEEE.std_logic_1164.all;
use IEEE.numeric_std.all;

entity Comparador is
	port
    (
        clock:in std_logic;
        A: in std_logic_vector(1 downto 0);
        B: in std_logic_vector(1 downto 0);
        o_segmentos: out std_logic_vector(7 downto 0);   	-- Salida para el display de 7 segmentos
        o_comunes: out std_logic_vector(3 downto 0)   	    -- Salida para comun de cada display
	);
end Comparador;

architecture Multiplexado of Comparador is					   

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
    constant I_Letter   : std_logic_vector(7 downto 0) := "11111001";
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
	 
	 signal letter1       : std_logic_vector(7 downto 0):=I_Letter; 
    signal letter2       : std_logic_vector(7 downto 0):=G_Letter;
    signal letter3       : std_logic_vector(7 downto 0):=U_Letter;
    signal letter4       : std_logic_vector(7 downto 0):=A_Letter;
	 --Operaciones de señales
	 signal	G0: std_logic;
	 signal	E0: std_logic;
	 signal	L0: std_logic;
	 signal G1:  std_logic;
	 signal E1:  std_logic;
	 signal L1:  std_logic;
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
	 
	process (A,B)
	begin
	-- medio comparador
		G0<= ((A(0) AND (NOT B(0))));
		E0<= (NOT(A(0) xor B(0)));
		L0<= ((NOT A(0))AND B(0)); 
		--Comparador completo
		G1<= G0 or ((A(1) AND (NOT B(1))));
		E1<= E0 and (NOT(A(1) xor B(1)));
		L1<= L0 or ((NOT A(1))AND B(1));
		---resultado
		 if G1 = '1' then
            letter1 <= S_Letter;
            letter2 <= U_Letter;
            letter3 <= P_Letter;
            letter4 <= E_Letter;
        elsif E1 = '1' then
            letter1 <= I_Letter;
            letter2 <= G_Letter;
            letter3 <= U_Letter;
            letter4 <= A_Letter;
        elsif L1 = '1' then
            letter1 <= I_Letter;
            letter2 <= N_Letter;
            letter3 <= F_Letter;
            letter4 <= E_Letter;
        end if;
		  
		end process;
		
	end Multiplexado;