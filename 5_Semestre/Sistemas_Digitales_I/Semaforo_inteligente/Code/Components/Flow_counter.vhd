-- Componente que recibe sensores de entrada de carril y de salida en otros carriles. Tambien recibe estado de semaforo
-- Regresa una cuenta de coches

------------------------------------------------------------------------------
library IEEE;
use IEEE.std_logic_1164.all;
use IEEE.numeric_std.all;

entity Flow_counter is
    port
	(
        i_CLK               : in STD_LOGIC;
        i_RST               : in STD_LOGIC;                         -- Reinicio de maquina de estados

        i_ENTRY_SENSOR      : in STD_LOGIC;                         -- Sensor de entrada de carril
        i_FORW_SENSOR       : in STD_LOGIC;                         -- Sensor de salida de carril
        i_RIGHT_SENSOR      : in STD_LOGIC;                         -- Sensor de salida de carril

        i_TRLH              : in STD_LOGIC_VECTOR(3 downto 0);      -- Semaforo de carril

        o_CAR_FLOW          : out INTEGER
	);
end Flow_counter;
------------------------------------------------------------------------------
architecture rtl of Flow_counter is
    -- MAQUINA DE ESTADOS FINITOS --
        type states is (IDLE, WAITT);
        signal entry_state : states := IDLE;
        signal out_state : states := IDLE;

    signal CAR_FLOW : INTEGER := 0;
begin

    o_CAR_FLOW <= CAR_FLOW;

    process (i_RST, i_CLK)
    begin        
        if(i_RST = '1') then
            CAR_FLOW    <= 0;
            entry_state <= IDLE;
            out_state   <= IDLE;

        elsif (rising_edge(i_CLK)) then
            case entry_state is
                when IDLE =>
                    -- Estado siguiente
                    if (i_ENTRY_SENSOR = '0') then          -- Detectamos una entrada de coche
                        entry_state <= WAITT;
                    else
                        entry_state <= IDLE;
                    end if;

                when WAITT =>
                    -- Estado siguiente                    
                    if(i_ENTRY_SENSOR = '1') then           -- Detectamos fin de entrada de coche
                        CAR_FLOW <= CAR_FLOW + 1;
                        entry_state <= IDLE;
                    else
                        entry_state <= WAITT;
                    end if;

                when others => null;
            end case;

            if (i_TRLH < "1000") then                       -- Si el semaforo esta en verde o amarillo
                case out_state is
                    when IDLE =>
                        -- Estado siguiente
                        if (i_FORW_SENSOR = '0' or i_RIGHT_SENSOR = '0') then   -- Detectamos una salida de coche
                            out_state <= WAITT;
                        else
                            out_state <= IDLE;
                        end if;
    
                    when WAITT =>
                        -- Estado siguiente                    
                        if(i_FORW_SENSOR = '1' and i_RIGHT_SENSOR = '1') then   -- Detectamos fin de salida de coche
                            if (CAR_FLOW > 0) then
                                CAR_FLOW <= CAR_FLOW - 1;
                            end if;
                            out_state <= IDLE;
                        else
                            out_state <= WAITT;
                        end if;
    
                    when others => null;
                end case;
            else
                out_state <= IDLE;
            end if;

        end if;

    end process;

end architecture;