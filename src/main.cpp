#include <Arduino.h>

#include <OneButton.h>

#include "TimedProcess.h"
#include <RaceController.h>		// https://github.com/Rafdal/ieee-alv-lap-chrono
#include <RaceSensor.h>
#include <Menu.h>				// https://github.com/Rafdal/lib-menu-arduino
#include <NumForm.h>
#include "Display.h"
#include "ALVLedsAsync.h"


#define RACE_LAP_DISTANCE_CM	245
#define RACE_MAX_LAPS			12
#define DISABLE_LEDS false

// **************************
// *		PIN SETUP 		*
// **************************
const uint8_t PIN_BUTTON_NEXT = A5;
const uint8_t PIN_BUTTON_SELECT = A3;
const uint8_t PIN_LEDS = 8;
const uint8_t PIN_DISPLAY_CS = 10;
const uint8_t PIN_DISPLAY_DATA = 11;
const uint8_t PIN_DISPLAY_CLK = 13;


Display disp; // 7 segment 8 digit display
OneButton btnNext(PIN_BUTTON_NEXT);
OneButton btnSelect(PIN_BUTTON_SELECT);

// TEST
// TODO: REMOVER ESTO
OneButton btnIR(2);

#define NUM_LEDS 21
ALVLedsAsync leds(NUM_LEDS, PIN_LEDS);


RaceController raceControl;
RaceSensor sensor1(A1);
RaceSensor sensor2(A0);
Menu main_menu(3, "Main menu");

#define NUM_FORM_LAPS_MEM_POS 0
NumForm numFormLaps("Number", NUM_FORM_LAPS_MEM_POS); // Parametro de prueba (Dev feature)

void read_menu_buttons();
void update_menu_display();

void start_race_option();
void show_race_results();

void sensor_read_loop();

bool hayAuto = false;

void setup()
{
	Serial.begin(115200);

	leds.begin(); // NeoPixel LEDS

	disp.printMsg("IEEEItba");
	Serial.println(F("IEEE ALV STARTING..."));
	delay(2000);
	
	// Configurar event listeners globales para todos los menues
	menu_set_event_listener_display(read_menu_buttons, update_menu_display);
	menu_set_real_time_loop(sensor_read_loop);

	// Interfaz del menu principal
	main_menu.set_option(0, "Correr", start_race_option);
	main_menu.set_option(1, "LAPS", [](){ numFormLaps.run(); });
	main_menu.set_option(2, "INf0", show_race_results );

	// TEST: Nueva feature menu
	numFormLaps.begin(1, RACE_MAX_LAPS);
	numFormLaps.enable_option_roll = true;

	// Estas opciones sirven para poder usar los menues solo con dos botones
	// En efectos practicos, con un solo boton se puede recorrer todas las opciones de forma ciclica
	main_menu.enable_option_roll = true;

	// Set menu buttons callbacks
	btnNext.attachClick([](){
		menu_go_down(); // Ir a la opcion siguiente
		// Serial.println(F("down"));
	});
	btnSelect.attachClick([](){
		menu_go_select(); // Seleccionar la opcion
	});

	// milisegundos para considerar un long press (Se usa para detener la carrera)
	btnNext.setPressTicks(1200);
	btnSelect.setPressTicks(1200);


	// TODO: Remover esto
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
	Serial.print("inicio RACE CTRL: ");
	Serial.println((int)raceControl.active());


	// +1 porque la primera vuelta es para marcar el inicio de la carrera
	raceControl.setupRace(numFormLaps.get(), RACE_LAP_DISTANCE_CM);

	// Animacion
	Serial.println("Start Race");
	#if !DISABLE_LEDS
	leds.initRace();
	#endif
	Serial.println("Race Starting...");

	// disp.printMsg("3");
	// delay(1000);
	// disp.printMsg("2");
	// delay(1000);
	// disp.printMsg("1");
	// delay(1000);

	raceControl.prepareRace();

	// Bucle bloqueante, hay que leer sensores y botones aca adentro
	// Tiene que ser lo mas eficiente posible en velocidad para que el sensado sea optimo

	TimedProcessMillis chronoLoop;
	TimedProcessMicros sensorLoop;

	sensorLoop.set(1500, [](){	// T = 1ms (1KHz)
		sensor_read_loop();

		// Serial.print((int)hayAuto);
		// Serial.print((int)raceControl.active());
		// Serial.println("asdasd");
		// BOKEEEEE
		if( hayAuto && raceControl.state() == RaceStarting)
		{
			raceControl.startRace(); 
		}
	});

	Serial.print("antes RACE CTRL: ");
	Serial.println((int)raceControl.active());


	chronoLoop.set(100, [](){	// T = 100ms (10 FPS)
		unsigned long time = raceControl.getTime();
		disp.printTime(time);

		#if !DISABLE_LEDS

		#endif
	});
	
	while (1)
	{
		raceControl.run();
		sensorLoop.run();

		// TODO: Medir cuanto delay mete el chronoLoop.run()
		// 			Afectara el sensado?

		chronoLoop.run();

		read_menu_buttons();
		if(btnNext.isLongPressed() || btnSelect.isLongPressed()) // Forzar detencion de carrera
		{
			Serial.println(F("FORCE STOP"));
			disp.printMsg("CL0SE");
			raceControl.stop();
			delay(1000);
		}

		if(raceControl.finished())
		{
			break;
		}
	}

	#if !DISABLE_LEDS

	#endif

	// FINISHED ANIMATION (No hay)

	if(raceControl.finished()) // (we have a winner)
	{
		Serial.println("We have a Winner");
		show_race_results();
	}
	else
	{
		Serial.println("NO HAY WINNER");
	}
}

void show_race_results()
{
	int winnerID = -1;
	unsigned long winnerTime = 0;
	raceControl.showWinnerStats(winnerID, winnerTime);

	if (winnerID != -1)
	{
		raceControl.showResults();

		char buf[10];

		sprintf(buf, "P%d  GANO", winnerID);
		disp.printMsg(buf);
		delay(300);

		// Esperar a que se presione un boton
		while(btnNext.getNumberClicks() == 0 && btnSelect.getNumberClicks() == 0)
		{
			btnNext.tick();
			btnSelect.tick();
		}

		sprintf(buf, "t=%lu.%u", winnerTime/100UL, (int)(winnerTime%100));
		disp.printMsg(buf);
		delay(400);
		btnNext.tick();
		btnSelect.tick();


		// Esperar a que se presione un boton
		while(btnNext.getNumberClicks() == 0 && btnSelect.getNumberClicks() == 0)
		{
			btnNext.tick();
			btnSelect.tick();
		}

		// Clear display
		disp.printMsg("");
		delay(300);
		// Flush buttons (Esto es para que los botones no ejecuten nada al salir de la funcion)
		btnNext.tick();
		btnSelect.tick();
	}
	else
	{
		disp.printMsg("Sin DAtA");
		delay(1000);
	}
}

void sensor_read_loop()
{
	// Si la carrera no está activa, los sensores se autocalibran todo el tiempo
	bool calibrationMode = !raceControl.active();
	// bool calibrationMode = false;

	// if(raceControl.state() == Race)
	
	hayAuto = false;

	if (sensor1.read(calibrationMode))
	{
		raceControl.lap(0);
		Serial.print(F("S1 Lap: "));
		Serial.println(raceControl.getLap(0));
		hayAuto = true;
	}
	if (sensor2.read(calibrationMode))
	{
		raceControl.lap(1);
		Serial.print(F("S2 Lap: "));
		Serial.println(raceControl.getLap(1));
		hayAuto = true;
	}
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

	disp.printMsg(menuData.option_titles[menuData.current_option]);
}