library	IEEE;
use	IEEE.std_logic_1164.all;

entity E1 is
end E1;	

architecture TB of E1 is  
component P3
	port(					
		T: in std_logic;
		H: in std_logic;
		F: in std_logic; 
		S: in std_logic;
		S1: out std_logic
		
	);
end component;

	signal T,H,F,S:std_logic;  --Entradas
	signal S1:std_logic; --Salidas

begin
 	inicio: P3 port map (T=>T,H=>H,F=>F,S=>S,S1=>S1);
	Parasimu: process
	begin
	T<='0'; H<='0'; F<='0'; S<='0'; wait for 10ns;
	T<='0'; H<='0'; F<='0'; S<='1'; wait for 10ns;
	T<='0'; H<='0'; F<='1'; S<='0'; wait for 10ns;
	T<='0'; H<='0'; F<='1'; S<='1'; wait for 10ns;
	T<='0'; H<='1'; F<='0'; S<='0'; wait for 10ns;
	T<='0'; H<='1'; F<='0'; S<='1'; wait for 10ns;	
	T<='0'; H<='1'; F<='1'; S<='0'; wait for 10ns;
	T<='0'; H<='1'; F<='1'; S<='1'; wait for 10ns;	  
	T<='1'; H<='0'; F<='0'; S<='0'; wait for 10ns;
	T<='1'; H<='0'; F<='0'; S<='1'; wait for 10ns;	
	T<='1'; H<='0'; F<='1'; S<='0'; wait for 10ns; 
	T<='1'; H<='0'; F<='1'; S<='1'; wait for 10ns; 
	T<='1'; H<='1'; F<='0'; S<='0'; wait for 10ns;
	T<='1'; H<='1'; F<='0'; S<='1'; wait for 10ns;
	T<='1'; H<='1'; F<='1'; S<='0'; wait for 10ns;	
	T<='1'; H<='1'; F<='1'; S<='1'; wait for 10ns;

	wait;
	end	process Parasimu;
end TB;