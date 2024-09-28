library IEEE;
use IEEE.std_logic_1164.all;

entity Control_llenado is
	port
	(
		RST: in std_logic; 	-- Reset maestro
		CLK: in std_logic; 	-- Reloj maestro
		T: in std_logic; 	-- Sensor de limite superior (0: NO detecta | 1: Detecta)
		B: in std_logic; 	-- Sensor de limite inferior (0: NO detecta | 1: Detecta)
		M: out std_logic 	-- Encendido de la bomba
	);
end Control_llenado;

architecture FMS of Control_llenado is
signal Qn, Qp: std_logic; 				-- Estados de la maquina (Futuro, presente)
begin
	combinacional: process(Qp,B,T)		-- Se activa cuando cambian los valores de entrada o hubo un ciclo de reloj
	begin
		-- Se actualiza el estado de la bomba en funcion del estado presente
		M <= Qp;

		-- Se actualiza el estado futuro de la bomba en funcion de las entradas actuales
		if (Qp = '0') then			-- Bomba esta apagada
			if(B = '0' and T = '0') then	-- Se detecta un deposito vacio, el estado futuro sera encendido
				Qn <= '1';
			else							-- Se detecta un deposito NO vacio, el estado futuro se conserva
				Qn <= Qp;
			end if;
		else						-- Bomba esta encendida
			if (B = '1' and T = '1') then		-- Se detecta un deposito lleno, el estado futuro sera apagado
				Qn <= '0';
			else								-- Se detecta un deposito NO lleno, el estado futuro se conserva
				Qn <= Qp;
			end if;
		end if;	
	end process combinacional;
	
	secuencial: process(RST,CLK)	-- Se activa cada ciclo de reloj o presion del boton reset
	begin
		if (RST = '0') then
			-- Iniciar en pagado
			Qp <= '0'; -- Inicia en apagado
		elsif (CLK'event and CLK = '1') then
			Qp <= Qn;
		end if;
	end process secuencial;
end FMS;