<html>
    <head>
        <meta charset="utf-8" />
        <title>Proyecto-Embebidos</title>
    </head>
 
    <body style="background-color: white;">
	<center>
	<img height="240" width = "320" src="http://192.168.1.71:8060/Stream.mjpg" />
	<br>
	<button id="myP" onmousedown="mouseDown(02)" onmouseup="mouseUp(02)">Atras</button>
	<button id="myP" onmousedown="mouseDown(03)" onmouseup="mouseUp(03)">Derecha</button>
	<button id="myP" onmousedown="mouseDown(34)" onmouseup="mouseUp(34)">Adelante</button>
	<button id="myP" onmousedown="mouseDown(24)" onmouseup="mouseUp(24)">Izquierda</button>
	<br>

<!------------------------------------------------ php -->
<?php
	//Define los pines GPIO0, GPIO 2, GPIO3, GPIO4 en modo salida		
	system("gpio mode 0 out");
	system("gpio write 0 0");
	system("gpio mode 2 out");
	system("gpio write 2 0");
	system("gpio mode 3 out");
	system("gpio write 3 0");
	system("gpio mode 4 out");
	system("gpio write 4 0");

	//-----Actualizacion del boton de estado
	$output = shell_exec("cat temp");
	if ($output ==0) {
		echo ("<img id='status' height=48 width = 120 src='data/ON.png'/>");
	}
	else {
		echo ("<img id='status' height=48 width = 120 src='data/OFF.png'/>");
	}	
?>

	</center>
	 
<!------------------------------------------------ javascript -->
<script src="camara.js"></script>

    </body>
</html>



