library	IEEE;
use	IEEE.std_logic_1164.all;	 

entity P2 is
	port
	(
		A: in std_logic;
		B: in std_logic;
		C: in std_logic;
		S1: out std_logic;
		S2: out std_logic;
		S3: out std_logic
	);
end P2;	  

Architecture PArch2 of P2 is 		 
begin						
	S1<= not C or (A and B and C);
	S2<= A and C;					
	S3<= ((not B and C) or B) and A;
end PArch2;