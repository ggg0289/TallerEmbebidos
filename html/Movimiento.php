<?php

if (isset ( $_GET["rotate"] )) {
	$rotate = strip_tags ($_GET["rotate"]);
	$pin = strip_tags ($_GET["pin"]);
	
	// Prueba si value es un numero
	if ( (is_numeric($rotate)) && ($rotate <= 7) && ($rotate >= 0) ) {
		//--------------------------------------------Atras
		if (($rotate == 1)&&($pin == 02)){
			// Se mueve hacia atras
			shell_exec("echo 0 >temp");
			$rotate = 0;
			system("gpio write 0 1");
			system("gpio write 2 1");
			system("gpio write 3 0");
			system("gpio write 7 0");
		}
		else{
		if (($rotate == 0)&&($pin == 02)){
			// Detienene movimiento
			shell_exec("echo 1 >temp");
			$rotate = 1;
			system("gpio write 0 0");
			system("gpio write 2 0");
			system("gpio write 3 0");
			system("gpio write 7 0");
			}
		}
		//--------------------------------------------Adelante
		if (($rotate == 1)&&($pin == 37)){
			// Se mueve hacia adelante
			shell_exec("echo 0 >temp");
			$rotate = 0;
			system("gpio write 0 0");
			system("gpio write 2 0");
			system("gpio write 3 1");
			system("gpio write 7 1");
		}
		else{
		if (($rotate == 0)&&($pin == 37)){
			// Detiene movimiento
			shell_exec("echo 1 >temp");
			$rotate = 1;
			system("gpio write 0 0");
			system("gpio write 2 0");
			system("gpio write 3 0");
			system("gpio write 7 0");
			}
		}
		//--------------------------------------------Derecha
		if (($rotate == 1)&&($pin == 03)){
			// Gira hacia la derecha
			shell_exec("echo 0 >temp");
			$rotate = 0;
			system("gpio write 0 1");
			system("gpio write 2 0");
			system("gpio write 3 1");
			system("gpio write 7 0");
		}
		else{
		if (($rotate == 0)&&($pin == 03)){
			// Detiene giro
			shell_exec("echo 1 >temp");
			$rotate = 1;
			system("gpio write 0 0");
			system("gpio write 2 0");
			system("gpio write 3 0");
			system("gpio write 7 0");
			}
		}
		//--------------------------------------------Izquierda
		if (($rotate == 1)&&($pin == 27)){
			// Gira hacia la izquierda
			shell_exec("echo 0 >temp");
			$rotate = 0;
			system("gpio write 0 0");
			system("gpio write 2 1");
			system("gpio write 3 0");
			system("gpio write 7 1");
		}
		else{
		if (($rotate == 0)&&($pin == 27)){
			// Detiene giro
			shell_exec("echo 1 >temp");
			$rotate = 1;
			system("gpio write 0 0");
			system("gpio write 2 0");
			system("gpio write 3 0");
			system("gpio write 7 0");
			}
		}


		echo($rotate);
	}
	else { echo ("Falla, no es un numero".$pin); }
} //print fail if cannot use values
else { echo ("Falla"); }


?>
