-- Si recibe señal ON junto con la señal DIR, ejecuta movimiento de motor a pasos y devuelve la cantidad de pasos recorridos

------------------------------------------------------------------------------
library IEEE;
use IEEE.std_logic_1164.all;
use IEEE.numeric_std.all;
------------------------------------------------------------------------------
entity Stepper_motor is
    generic 
    (
        clk_freq        : INTEGER
    );
    port
    (
        i_FPGA_clk          : in STD_LOGIC;         -- Señal de reloj base
        i_RST               : in STD_LOGIC;         -- Reinicio total
        
        i_ON                : in STD_LOGIC;         -- Encendido
        i_DIR               : in STD_LOGIC;         -- 0 izquierda | 1 Derecha 
        
        o_STEPS             : out STD_LOGIC_VECTOR(3 downto 0);      -- 4 bobinas del motor a pasos
        o_done_steps        : out INTEGER;          -- Devuelve la cantidad de pasos recorrida

        i_step_freq         : in INTEGER            -- Velocidad de paso en Hz
    );
end Stepper_motor;

architecture rtl of Stepper_motor is

    -- Division de reloj
        component CLK_DIV is
            generic 
            (
                clk_freq    : integer          -- Frecuencia interna de FPGA (Hz)
            );
            port
            (
                i_out_freq      : integer;              -- Frequencia deseada
                i_FPGA_clk      : in STD_LOGIC;         -- Señal de reloj base
                o_clk           : out STD_LOGIC    
            );
        end component;
        
        signal STEP_CLK : STD_LOGIC;

    -- Maquina de estado --
        type States is (IDLE, WAIT_ST, STEPS);
        signal act_state : States := IDLE; -- Ponemos en estado inicial la maquina

    -- Señales de motor a paso --
        type array_4 is array (0 to 3) of STD_LOGIC_VECTOR(3 downto 0);
        signal steps_sequence : array_4;
        signal step_index : INTEGER := 0;
        
        signal done_steps : INTEGER := 0;

begin

    steps_sequence(0) <= "0001";
    steps_sequence(1) <= "0010";
    steps_sequence(2) <= "0100";
    steps_sequence(3) <= "1000";

    o_done_steps <= done_steps;

    ------------------------------------------------------------------------------
                            -- MAQUINA DE ESTADOS FINITOS --
    ------------------------------------------------------------------------------
    c_STEP_CLK : CLK_DIV
        generic map ( clk_freq => clk_freq ) 
        port map ( i_out_freq => i_step_freq, i_FPGA_clk => i_FPGA_clk, o_clk => STEP_CLK );
    
    o_STEPS <= steps_sequence(step_index);

    process (STEP_CLK, i_RST, i_ON)
    begin
        if (i_RST = '1') then                           -- Se presiono RST
            act_state <= IDLE;
            step_index <= 0;
        elsif (rising_edge(STEP_CLK)) then
            case act_state is
                when IDLE =>            -- Esperar señal ST
                    -- Salidas del estado
                    if(i_ON = '1') then
                        act_state <= STEPS;
                    else
                        act_state <= IDLE;
                    end if;

                when STEPS =>                           -- Tengo sentido de giro, hace 1 paso de mas :/
                    -- Salidas del estado                    
                    if(i_DIR = '1') then    -- Giro a la derecha, step_index suma
                        if (step_index = 3) then
                            step_index <= 0;
                        else
                            step_index <= step_index + 1;
                        end if;
                    else                        -- Giro a la izquierda, step_index resta
                        if (step_index = 0) then
                            step_index <= 3;
                        else
                            step_index <= step_index - 1;
                        end if;
                    end if;
                    
                    done_steps <= done_steps + 1;

                    -- Estado proximo
                    if i_ON = '0' then                      -- Si ya no se requieren los pasos
                        done_steps <= 0;                    -- Reiniciamos cuenta de pasos recorridos
                        act_state <= IDLE;
                    else
                        act_state <= STEPS;
                    end if;

                when others =>
                    null;
            end case;
        end if;
    end process;


end rtl;