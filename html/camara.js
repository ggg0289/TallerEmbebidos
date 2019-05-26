var status_button = document.getElementById("status");


function mouseDown(pin) {
 	var data = 0;

	var request = new XMLHttpRequest();
	// Enviando estado y pin a Movimiento.php
	request.open( "GET" , "Movimiento.php?rotate=1&pin="+pin, true); 
	request.send(null);
	// Recibiendo informacion
	request.onreadystatechange = function () {
		if (request.readyState == 4 && request.status == 200) {
			data = request.responseText;		
			
			if ( data==1 ){
				status_button.src = "data/OFF.png";
			}
			else if ( data == 0 ) {
				status_button.src = "data/ON.png";
			}
			else if ( !(data.localeCompare("fail"))) {
				alert ("La salida no es ni 1, ni 0, ni falla" );
				return ("fail");			
			}
			else {
				alert ("Algo salio mal!! "+data );
				return ("fail"); 
			}
		}
		//if fail
		else if (request.readyState == 4 && request.status == 500) {
			alert ("Error del servidor");
			return ("Falla");
		}
		//else 
		else if (request.readyState == 4 && request.status != 200 && request.status != 500 ) { 
			alert ("Algo salio mal!");
			return ("fail"); }
	}	
	return 0;
}

function mouseUp(pin) {
	var data = 0;

	var request = new XMLHttpRequest();
	// Enviando estado y pin a Movimiento.php
	request.open( "GET" , "Movimiento.php?rotate=0&pin="+pin, true);
	request.send(null);
	// Recibiendo informacion
	request.onreadystatechange = function () {
		if (request.readyState == 4 && request.status == 200) {
			data = request.responseText;		
			
			if ( data==1 ){
				status_button.src = "data/OFF.png";
			}
			else if ( data == 0 ) {
				status_button.src = "data/ON.png";
			}
			else if ( !(data.localeCompare("fail"))) {
				alert ("La salida no es ni 1, ni 0, ni falla" );
				return ("fail");			
			}
			else {
				alert ("Algo salio mal!! "+data );
				return ("fail"); 
			}
		}
		//if fail
		else if (request.readyState == 4 && request.status == 500) {
			alert ("Error del servidor");
			return ("fail");
		}
		//else 
		else if (request.readyState == 4 && request.status != 200 && request.status != 500 ) { 
			alert ("Algo salio mal!");
			return ("fail"); }
	}	
	return 0;
}

