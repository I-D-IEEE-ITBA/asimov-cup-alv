#include <Arduino.h>

#include <OneButton.h>

#include <RaceController.h>		// https://github.com/Rafdal/ieee-alv-lap-chrono
#include <Menu.h>				// https://github.com/Rafdal/lib-menu-arduino
#include <NumForm.h>

OneButton btnNext(4);
OneButton btnSelect(6);

OneButton btnIR(2);

#define RACE_LAPS 3
#define RACE_LAP_DISTANCE_CM	245 // TODO: Remover estas funcionalidades (segun Mati no aportan)
RaceController raceControl(RACE_LAPS, RACE_LAP_DISTANCE_CM);


Menu main_menu(4, "Main menu");
Menu pause_menu(2, "Pause menu");

NumForm numForm("Number"); // Parametro de prueba (Dev feature)

void read_menu_buttons();
void update_menu_display();

void start_race_option();

void sensor_read_loop();

void setup()
{
	Serial.begin(115200);

  // Configurar event listeners globales para todos los menues
	menu_set_event_listener_display(read_menu_buttons, update_menu_display);
	menu_set_real_time_loop(sensor_read_loop);

	main_menu.set_option(0, "Start Race", start_race_option);
	main_menu.set_option(1, "See Stats", [](){ raceControl.showResults(); });
	main_menu.set_option(2, "Laps", [](){ numForm.run(); });
	main_menu.set_option(3, "Option3", NULL);

	pause_menu.set_option(0, "Resume", menu_force_close_current);
	pause_menu.set_option(1, "Stop", [](){ raceControl.stop(); pause_menu.force_close(); });

  // TEST: Nueva feature menu
	numForm.begin(0, 12);
	numForm.enable_option_roll = true;

  // Estas opciones sirven para poder usar los menues solo con dos botones
  // En efectos practicos, con un solo boton se puede recorrer todas las opciones de forma ciclica
	pause_menu.enable_option_roll = true;
	main_menu.enable_option_roll = true;

	// Set menu buttons callbacks
	btnNext.attachClick([](){
		menu_go_down(); // Ir a la opcion siguiente
		// Serial.println(F("down"));
	});

	btnSelect.attachClick([](){
		menu_go_select(); // Seleccionar la opcion
		// Serial.println(F("select"));
	});


	// Sensor de velocista TEST (emulador)
	btnIR.attachClick([](){
		Serial.println("P1 lap");
		raceControl.lap(0);
	});

	// Sensor de velocista TEST (emulador)
	btnIR.attachLongPressStart([](){
		Serial.println("P2 lap");
		raceControl.lap(1);
	});


  // TODO: Implementar el autoajuste de sensores al inicio (ajustar a luz ambiental)
}

void loop()
{
	main_menu.run(); // Bloqueante, ejecuta el programa principal
}


void start_race_option()
{
	raceControl.startWithAnimation(); // TODO: Agregar animacion

	while (raceControl.active())
	{
		raceControl.run();
		sensor_read_loop(); 

		read_menu_buttons();
		if(btnNext.isLongPressed() || btnSelect.isLongPressed())
		{
			Serial.println(F("Race STOP!"));
			raceControl.stop();
		}
	}

	// FINISHED ANIMATION  // milisegundos para considerar un long press
	btnNext.setPressTicks(1200);
	btnSelect.setPressTicks(1200);

  // TODO: Agregar animacion de finalizacion
	raceControl.showResults();

	if(raceControl.finished()) // (we have a winner)
	{
		raceControl.showWinnerStats();
	}
}

void sensor_read_loop()
{
	btnIR.tick(); // SENSOR EMULATOR 
  // TODO: Agregar el codigo de los filtros
}

void read_menu_buttons()
{
	btnNext.tick();
	btnSelect.tick();
}

// TODO: Agregar codigo para el display
void update_menu_display()
{
	MenuData menuData = menu_get_current_data();

	Serial.print(F("title: "));
	Serial.println(menuData.title); // Esto no lo vamos a poder mostrar en el display
	for (uint8_t i = 0; i < menuData.n_options; i++)
	{
		if(menuData.current_option == i) // Lo que más interesa mostrar es la current option
			Serial.print(F(" >"));
		else
			Serial.print(F("  "));
		
		Serial.println( menuData.option_titles[i]);
	}
}