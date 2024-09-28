library	IEEE;
use	IEEE.std_logic_1164.all;	 

entity P3 is
	port
	(
		T: in std_logic;
		H: in std_logic;
		F: in std_logic; 
		S: in std_logic;
		S1: out std_logic
	);
end P3;	  

Architecture PArch2 of P3 is 		 
begin						
	S1<= (T and H) or (F and S) or (H and S) or (T and F);
end PArch2;