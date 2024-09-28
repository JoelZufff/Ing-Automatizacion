library	IEEE;
use	IEEE.std_logic_1164.all;

entity E1 is
end E1;	

architecture TB of E1 is  
component P2
	port
	(					
		A: in std_logic;
		B: in std_logic;
		C: in std_logic;
		S1: out std_logic;
		S2: out std_logic;
		S3: out std_logic
	);
end component;

	signal A,B,C:std_logic;  --Entradas
	signal S1,S2,S3:std_logic; --Salidas

begin
 	inicio: P2 port map (A=>A,B=>B,C=>C,S1=>S1,S2=>S2,S3=>S3);
	Parasimu: process
	begin
	A<='0'; B<='0'; C<='0'; wait for 10ns;
	A<='0'; B<='0'; C<='1'; wait for 10ns;
	A<='0'; B<='1'; C<='0'; wait for 10ns;
	A<='0'; B<='1'; C<='1'; wait for 10ns;
	A<='1'; B<='0'; C<='0'; wait for 10ns;
	A<='1'; B<='0'; C<='1'; wait for 10ns;
	A<='1'; B<='1'; C<='0'; wait for 10ns;
	A<='1'; B<='1'; C<='1'; wait for 10ns;

	wait;
	end	process Parasimu;
end TB;